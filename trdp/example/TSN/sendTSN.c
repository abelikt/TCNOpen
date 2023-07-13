/**********************************************************************************************************************/
/**
 * @file            sendTSN.c
 *
 * @brief           Demo talker for TRDP for DbD
 *
 * @note            Project: Safe4RAIL WP1
 *                  For this demo to work, the library must be compiled with TSN_SUPPORT defined!
 *
 * @author          Bernd Loehr, NewTec GmbH
 *
 * @remarks         Copyright NewTec GmbH, 2018. All rights reserved.
 *
 * $Id$
 *
 *     CWE 2023-03-28: Ticket #342 Updating TSN / VLAN / RT-thread code
 *     CWE 2022-12-21: Ticket #404 Fix compile error - Test does not need to run, it is only used to verify bugfixes. It requires a special network-setup to run
 *      AM 2022-12-01: Ticket #399 Abstract socket type (VOS_SOCK_T, TRDP_SOCK_T) introduced, vos_select function is not anymore called with '+1'
 * 
 */

/***********************************************************************************************************************
 * INCLUDES
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined (POSIX)
#include <unistd.h>
#elif defined (WIN32)
#include "getopt.h"
#endif

#include "trdp_if_light.h"
#include "vos_thread.h"
#include "vos_utils.h"


/***********************************************************************************************************************
 * DEFINITIONS
 */
#define APP_VERSION         "1.0"

#define DATA_MAX            1432u

/* TSN PD sample definition */
#define PD_COMID_TSN        1000u               /* 24byte string as payload                     */
#define PD_COMID_TSN_CYCLE  1000u               /* default in us (1000 = 0.001 sec)             */
#define PD_COMID_TSN_DEST   "239.1.1.3"         /* default target (MC group) for TSN PD         */
#define PD_COMID_TSN_VLAN   10u                 /* default VLAN ID for TSN PD                   */

/* Standard PD sample definition */
#define PD_COMID_STD        10000u              /* 24byte string as payload                     */
#define PD_COMID_STD_CYCLE  100000u             /* default in us (100000 = 0.1 sec)             */
#define PD_COMID_STD_DEST   "239.1.1.2"         /* default target (MC group) for standard PD    */
#define PD_COMID_STD_VLAN   0u                  /* no VLAN  (ID 0) for standard PD              */

/* Payload definition (Timestamp as TIMEDATE64 and in ASCII) */
typedef struct
{
    TIMEDATE64          sentTime;
    UINT64              unused;                 /* align string to next 16 byte boundary for easy tcpdump analysis */
    CHAR8               timeString[16];
} GNU_PACKED LATENCY_PACKET_T;

#define PD_TSN_PAYLOAD_SIZE  sizeof(LATENCY_PACKET_T)
#define PD_STD_PAYLOAD_SIZE  48                 /* Hello world ... string PD */

/* Global variable set definition */
typedef struct fdf_context
{
    TRDP_APP_SESSION_T  appHandle;          /*    Our identifier to the library instance    */
    TRDP_PUB_T          pubHandle;          /*    Our identifier to the publication         */
    TRDP_SUB_T          subHandle;          /*    Our identifier to the subscription        */
    void                *pDataSource;
    UINT32              sourceSize;
    void                *pDataTarget;
    UINT32              targetSize;
} FDF_APP_CONTEXT;

static int      gComThreadTsnRunning = TRUE;
static int      gComThreadStdRunning = TRUE;

static int      gVerbose = FALSE;

UINT8           *gpOutputBufferTsn;
UINT8           *gpOutputBufferStd;
UINT8           gExampleDataTsn[DATA_MAX]  = { 0 };
UINT8           gExampleDataStd[DATA_MAX]  = { 0 };

FDF_APP_CONTEXT gAppContextTsn = {NULL, NULL, NULL, gExampleDataTsn, PD_TSN_PAYLOAD_SIZE, NULL, 0u};
FDF_APP_CONTEXT gAppContextStd = {NULL, NULL, NULL, gExampleDataStd, PD_STD_PAYLOAD_SIZE, NULL, 0u};

/***********************************************************************************************************************
 * PROTOTYPES
 */
static void dbgOut (void *, TRDP_LOG_T, const CHAR8 *, const CHAR8 *, UINT16, const CHAR8 *);
static void usage (const char *);
static void *comThreadTsn (void *arg);
static void *comThreadStd (void *arg);
static void *dataAppThreadTsn (void *arg);

/**********************************************************************************************************************/
/** callback routine for TRDP logging/error output
 *
 *  @param[in]      pRefCon         user supplied context pointer
 *  @param[in]      category        Log category (Error, Warning, Info etc.)
 *  @param[in]      pTime           pointer to NULL-terminated string of time stamp
 *  @param[in]      pFile           pointer to NULL-terminated string of source module
 *  @param[in]      LineNumber      line
 *  @param[in]      pMsgStr         pointer to NULL-terminated string
 *  @retval         none
 */
static void dbgOut (
    void        *pRefCon,
    TRDP_LOG_T  category,
    const CHAR8 *pTime,
    const CHAR8 *pFile,
    UINT16      LineNumber,
    const CHAR8 *pMsgStr)
{
    const char *catStr[] = {"**Error:", "Warning:", "   Info:", "  Debug:", "   User:"};
    CHAR8       *pF = strrchr(pFile, VOS_DIR_SEP);
    if ((category == VOS_LOG_DBG) && !gVerbose)
    {
        return;
    }
    if (category == VOS_LOG_USR)
    {
        printf("%s %s %s",
               strrchr(pTime, '-') + 1,
               catStr[category],
               pMsgStr);
        return;
    }
    printf("%s %s %s:%d %s",
           strrchr(pTime, '-') + 1,
           catStr[category],
           (pF == NULL)? "" : pF + 1,
           LineNumber,
           pMsgStr);
}

/**********************************************************************************************************************/
/* Print a sensible usage message */
/**********************************************************************************************************************/
static void usage (const char *appName)
{
    printf("Usage of %s\n", appName);
    printf("This tool sends TSN PD-PDU and standard PD to 'receiveTSN' (ComId 0 and 1000)\n"
           "TSN PD packets are sent at each cycle with start time offset \n"
           "Standard PD packets are sent every 100ms with ComId 1000\n"
           "Arguments are:\n"
           "-O <own IP address for TSN> (default INADDR_ANY)\n"
           "-o <own IP address for standard PD> (default INADDR_ANY)\n"
           "-T <target (multicast) IP address for TSN> (default 239.1.1.3)\n"
           "-t <target (multicast) IP address for standard PD> (default 239.1.1.2)\n"
           "-V <VLAN-ID for TSN> (default 10)\n"
           "-v <VLAN-ID for standard PD> (default 0 = no VLAN)\n"
           "-P <priority for TSN = PCP: 0..7> (default 7)\n"
           "-p <priority for standard PD = QoS: 0..7> (default 3)\n"
           "-S <start time for TSN> data producer session start delay (default 250000 [µs], max. 999999)\n"
           "-C <cycle time for TSN> (default 1000 [µs])\n"
           "-c <cycle time for standard PD> (default 100000 [µs])\n"
           "-d debug output, be more verbose\n"
           "-h print usage\n"
           );
}

/**********************************************************************************************************************/
/* Communication thread for TSN PD                                                                                    */
/**********************************************************************************************************************/
static void *comThreadTsn (
    void *arg)
{
    TRDP_APP_SESSION_T appHandle = (TRDP_APP_SESSION_T) arg;

    gComThreadTsnRunning = 1;

    while (gComThreadTsnRunning)
    {
        TRDP_FDS_T          rfds;
        INT32               noDesc, rv;
        TRDP_TIME_T         tv;
        const TRDP_TIME_T   max_tv  = {1, 0};
        const TRDP_TIME_T   min_tv  = {0, 10000};

        FD_ZERO(&rfds);

        tlc_getInterval(appHandle, &tv, &rfds, &noDesc);

        if (vos_cmpTime(&tv, &max_tv) > 0)
        {
            tv = max_tv;
        }
        else if (vos_cmpTime(&tv, &min_tv) < 0)
        {
            tv = min_tv;
        }

        rv = vos_select(noDesc, &rfds, NULL, NULL, &tv);

        (void) tlc_process(appHandle, &rfds, &rv);

    }
    vos_printLogStr(VOS_LOG_INFO, "TSN comm thread ran out. \n");
    return NULL;
}

/**********************************************************************************************************************/
/* Communication thread for Standard PD                                                                               */
/**********************************************************************************************************************/
static void *comThreadStd (
    void *arg)
{
    TRDP_APP_SESSION_T appHandle = (TRDP_APP_SESSION_T) arg;

    gComThreadStdRunning = 1;

    while (gComThreadStdRunning)
    {
        TRDP_FDS_T          rfds;
        INT32               noDesc, rv;
        TRDP_TIME_T         tv;
        const TRDP_TIME_T   max_tv  = {1, 0};
        const TRDP_TIME_T   min_tv  = {0, 10000};

        FD_ZERO(&rfds);

        tlc_getInterval(appHandle, &tv, &rfds, &noDesc);

        if (vos_cmpTime(&tv, &max_tv) > 0)
        {
            tv = max_tv;
        }
        else if (vos_cmpTime(&tv, &min_tv) < 0)
        {
            tv = min_tv;
        }

        rv = vos_select(noDesc, &rfds, NULL, NULL, &tv);

        (void) tlc_process(appHandle, &rfds, &rv);

    }
    vos_printLogStr(VOS_LOG_INFO, "Standard comm thread ran out.\n");
    return NULL;
}

/**********************************************************************************************************************/
/* Application TSN cyclic thread                                                                                          */
/**********************************************************************************************************************/
static void *dataAppThreadTsn (
    void *arg)
{
    TRDP_ERR_T          err;
    FDF_APP_CONTEXT     *pContext = (FDF_APP_CONTEXT *) arg;
    VOS_TIMEVAL_T       now;
    LATENCY_PACKET_T    transmittedData = { 0 };
    struct tm           *dataCreationTime;

    /* generate some data */
    vos_getRealTime(&now);
    transmittedData.sentTime.tv_usec  = (INT32) vos_htonl((UINT32)now.tv_usec);
    transmittedData.sentTime.tv_sec   = vos_htonl((UINT32)now.tv_sec);

    dataCreationTime = localtime(&now.tv_sec);
    if (dataCreationTime != NULL)
    {
        snprintf((char *)transmittedData.timeString, 16, "%02d:%02d:%02d.%06d", dataCreationTime->tm_hour, dataCreationTime->tm_min, dataCreationTime->tm_sec, now.tv_usec);
   } else {
        snprintf((char *)transmittedData.timeString, 16, "%8x.%06d", now.tv_sec, now.tv_usec);
    }

    err = tlp_putImmediate(pContext->appHandle, pContext->pubHandle, (UINT8 *) &transmittedData, sizeof(transmittedData), 0);
    if (err != TRDP_NO_ERR)
    {
        vos_printLogStr(VOS_LOG_ERROR, "TSN put PD error\n");
    }
    else{
        vos_printLog(VOS_LOG_USR, "Send TSN PD ComID %d, %s\n", PD_COMID_TSN, transmittedData.timeString);
    }
    return NULL;
}

/**********************************************************************************************************************/
/** main entry
 *
 *  @retval         0        no error
 *  @retval         1        some error
 */
int main (int argc, char *argv[])
{
    unsigned int            ip[4];
    TRDP_ERR_T              err;
    TRDP_PD_CONFIG_T pdConfigTsn = {NULL,
                                    NULL,
                                    {TRDP_PD_DEFAULT_TSN_PRIORITY, TRDP_PD_DEFAULT_TTL, 0u}, 
                                    TRDP_FLAGS_TSN, 
                                    TRDP_PD_DEFAULT_TIMEOUT, 
                                    TRDP_TO_DEFAULT, 
                                    TRDP_PD_UDP_PORT};
    TRDP_PD_CONFIG_T pdConfigStd = {NULL,
                                    NULL, 
                                    TRDP_PD_DEFAULT_SEND_PARAM, 
                                    TRDP_FLAGS_DEFAULT, 
                                    TRDP_PD_DEFAULT_TIMEOUT, 
                                    TRDP_TO_DEFAULT, 
                                    TRDP_PD_UDP_PORT};
    TRDP_PROCESS_CONFIG_T   processConfigTsn     = {"sendTSN", "", "", PD_COMID_TSN_CYCLE, 255, TRDP_OPTION_BLOCK, PD_COMID_TSN_VLAN};
    TRDP_PROCESS_CONFIG_T   processConfigStd     = {"sendSTD", "", "", PD_COMID_STD_CYCLE, 255, TRDP_OPTION_BLOCK, PD_COMID_STD_VLAN};
    UINT32                  ownIPtsn   = VOS_INADDR_ANY;
    UINT32                  ownIPstd   = VOS_INADDR_ANY;
    UINT32                  destIPtsn  = vos_dottedIP(PD_COMID_TSN_DEST);
    UINT32                  destIPstd  = vos_dottedIP(PD_COMID_STD_DEST);
    VOS_THREAD_T            myComThreadTsn, myDataThreadTsn;
    VOS_THREAD_T            myComThreadStd;
    UINT32                  startTimeTsn    = 250000u;
    UINT32                  pdTsn_cycleTime = PD_COMID_TSN_CYCLE;
    UINT32                  pdStd_cycleTime = PD_COMID_STD_CYCLE;
    VOS_TIMEVAL_T           now;
    UINT32                  counter = 0;
    int                     ch;
    CHAR8                   tempIP1[16];
    CHAR8                   tempIP2[16];

    /*    Generate some data, that we want to send */
    gpOutputBufferTsn = gExampleDataTsn;
    gpOutputBufferStd = gExampleDataStd;

    if (argc <= 1)
    {
        usage(argv[0]);
        return 1;
    }

    while ((ch = getopt(argc, argv, "O:o:T:t:V:v:P:p:S:C:c:dh?")) != -1)
    {
        switch (ch)
        {
           case 'O':
           {   /* own IP for TSN PD */
               if (sscanf(optarg, "%u.%u.%u.%u",
                          &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
               {
                   usage(argv[0]);
                   exit(1);
               }
               ownIPtsn = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
               break;
           }
           case 'o':
           {   /* own IP for standard PD */
               if (sscanf(optarg, "%u.%u.%u.%u",
                          &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
               {
                   usage(argv[0]);
                   exit(1);
               }
               ownIPstd = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
               break;
           }           
           case 'T':
           {   /* target (multicast) IP for TSN */
               if (sscanf(optarg, "%u.%u.%u.%u",
                          &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
               {
                   usage(argv[0]);
                   exit(1);
               }
               destIPtsn = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
               break;
           }
           case 't':
           {   /* target (multicast) IP for standard PD */
               if (sscanf(optarg, "%u.%u.%u.%u",
                          &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
               {
                   usage(argv[0]);
                   exit(1);
               }
               destIPstd = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
               break;
           }
           case 'V':
           {   /* VLAN ID for TSN */
               if (sscanf(optarg, "%hu", &processConfigTsn.vlanId) < 1)
               {
                   usage(argv[0]);
                   exit(1);
               }
               break;
           }
           case 'v':
           {   /* VLAN ID for standard PD (0 = no VLAN) */
               if (sscanf(optarg, "%hu", &processConfigStd.vlanId) < 1)
               {
                   usage(argv[0]);
                   exit(1);
               }
               break;
           }
           case 'P':
           {   /* priority (0..7) for TSN */
               if (sscanf(optarg, "%hhu", &pdConfigTsn.sendParam.qos) < 1)
               {
                   usage(argv[0]);
                   exit(1);
               }
               break;
           }
           case 'p':
           {   /* priority (0..7) for standard PD */
               if (sscanf(optarg, "%hhu", &pdConfigStd.sendParam.qos) < 1)
               {
                   usage(argv[0]);
                   exit(1);
               }
               break;
           }
           case 'S':
           {   /* Session start time (µs) for cyclic TSN data producer */
               if ((sscanf(optarg, "%u", &startTimeTsn) < 1) ||
                   (startTimeTsn > 999999))
               {
                   usage(argv[0]);
                   exit(1);
               }
               break;
           }
           case 'C':
           {   /* TSN cycle time (µs) */
               if (sscanf(optarg, "%u", &pdTsn_cycleTime) < 1)
               {
                   usage(argv[0]);
                   exit(1);
               }
               processConfigTsn.cycleTime = pdTsn_cycleTime;
               break;
           }
           case 'c':
           {   /* standard PD cycle time (µs) */
               if (sscanf(optarg, "%u", &pdStd_cycleTime) < 1)
               {
                   usage(argv[0]);
                   exit(1);
               }
               processConfigStd.cycleTime = pdStd_cycleTime;
               break;
           }
           case 'd':
           {   /* enable debug output */
               gVerbose = TRUE;
               break;
           }
           case 'h':
           case '?':
           default:
               printf("%s: Version %s\t(%s - %s)\n",
                      argv[0], APP_VERSION, __DATE__, __TIME__);
               usage(argv[0]);
               return 1;
        }
    }

    if (destIPtsn == 0)
    {
        fprintf(stderr, "No TSN PD destination address given!\n");
        usage(argv[0]);
        return 1;
    }
    if (destIPstd == 0)
    {
        fprintf(stderr, "No standard PD destination address given!\n");
        usage(argv[0]);
        return 1;
    }

    /*    Init the library  */
    if (tlc_init(&dbgOut,                               /* logging    */
                 NULL,
                 NULL) != TRDP_NO_ERR)                  /* Use application supplied memory    */
    {
        fprintf(stderr, "Initialization error\n");
        return 1;
    }

    vos_printLogStr(VOS_LOG_USR, "-----------------------------------------------\n");
    vos_printLog(VOS_LOG_USR, "TSN session start time:  %10uµs\n", startTimeTsn);
    vos_printLog(VOS_LOG_USR, "        TSN cycle time:  %10uµs\n", pdTsn_cycleTime);
    vos_printLog(VOS_LOG_USR, "   Standard cycle time:  %10uµs\n", pdStd_cycleTime);
    memcpy(tempIP1, vos_ipDotted(ownIPtsn), 16);
    memcpy(tempIP2, vos_ipDotted(destIPtsn), 16);
    vos_printLog(VOS_LOG_USR, "Publish       TSN PD (%5u) from IP %s to IP %s, cycle %uµs, prio %u\n", PD_COMID_TSN, tempIP1, tempIP2, pdTsn_cycleTime, pdConfigTsn.sendParam.qos);
    memcpy(tempIP1, vos_ipDotted(ownIPstd), 16);
    memcpy(tempIP2, vos_ipDotted(destIPstd), 16);
    vos_printLog(VOS_LOG_USR, "Publish  Standard PD (%5u) from IP %s to IP %s, cycle %uµs, prio %u\n", PD_COMID_STD, tempIP1, tempIP2, pdStd_cycleTime, pdConfigStd.sendParam.qos);
    struct timespec tempRealTime;
    (void)clock_gettime(CLOCK_REALTIME, &tempRealTime);
#ifdef CLOCK_MONOTONIC
    struct timespec tempMonoTime;
    (void)clock_gettime(CLOCK_MONOTONIC, &tempMonoTime);
#endif
    vos_printLog(VOS_LOG_USR, "CLOCK_REALTIME:  %10usec, %10uns used for TSN and Standard PD\n", tempRealTime.tv_sec, tempRealTime.tv_nsec);
#ifdef CLOCK_MONOTONIC
    vos_printLog(VOS_LOG_USR, "CLOCK_MONOTONIC: %10usec, %10uns not used, info only\n", tempMonoTime.tv_sec, tempMonoTime.tv_nsec);
#endif
    vos_printLogStr(VOS_LOG_USR, "-----------------------------------------------\n");



    /* Open the TSN session with the TRDP stack */
    if (tlc_openSession(&gAppContextTsn.appHandle,
                        ownIPtsn, 0u,           /* use default IP address           */
                        NULL,                   /* no Marshalling                   */
                        &pdConfigTsn, NULL,             /* system defaults for PD and MD    */
                        &processConfigTsn) != TRDP_NO_ERR)
    {
        vos_printLogStr(VOS_LOG_USR, "Initialization error on open TSN session\n");
        return 1;
    }

    /* Open the standard session with the TRDP stack */
    if (tlc_openSession(&gAppContextStd.appHandle,
                        ownIPstd, 0u,           /* use default IP address           */
                        NULL,                   /* no Marshalling                   */
                        &pdConfigStd, NULL,             /* system defaults for PD and MD    */
                        &processConfigStd) != TRDP_NO_ERR)
    {
        vos_printLogStr(VOS_LOG_USR, "Initialization error on open standard session\n");
        return 1;
    }    



    /* create TSN communication thread */
    err = (TRDP_ERR_T) vos_threadCreateSync(&myComThreadTsn, "comThreadTsn",
                                        VOS_THREAD_POLICY_OTHER,
                                        VOS_THREAD_PRIORITY_DEFAULT,
                                        0u,         /*  interval for cyclic thread      */
                                        NULL,       /*  start time for cyclic threads   */
                                        0u,         /*  stack size (default 4 x PTHREAD_STACK_MIN)   */
                                        (VOS_THREAD_FUNC_T) comThreadTsn, gAppContextTsn.appHandle);

    if (err != TRDP_NO_ERR)
    {
        vos_printLog(VOS_LOG_USR, "TSN comThread could not be created (error = %d)\n", err);
        tlc_terminate();
        return 1;
    }

    /* create Standard communication thread */
    err = (TRDP_ERR_T) vos_threadCreateSync(&myComThreadStd, "comThreadStd",
                                        VOS_THREAD_POLICY_OTHER,
                                        VOS_THREAD_PRIORITY_DEFAULT,
                                        0u,         /*  interval for cyclic thread      */
                                        NULL,       /*  start time for cyclic threads   */
                                        0u,         /*  stack size (default 4 x PTHREAD_STACK_MIN)   */
                                        (VOS_THREAD_FUNC_T) comThreadStd, gAppContextStd.appHandle);

    if (err != TRDP_NO_ERR)
    {
        vos_printLog(VOS_LOG_USR, "Standard comThread could not be created (error = %d)\n", err);
        tlc_terminate();
        return 1;
    }



    /****************************************************************************/
    /*   Publish some TSN sample data. Cycle time will not be provided.         */
    /****************************************************************************/

    err = tlp_publish(  gAppContextTsn.appHandle,   /*    our application identifier     */
                        &gAppContextTsn.pubHandle,  /*    our pulication identifier      */
                        NULL, NULL,                 /*    no userRef, no Callback        */
                        0u,                         /*    serviceId                      */
                        PD_COMID_TSN,               /*    ComID to send                  */
                        0u,                         /*    etbTopoCnt                     */
                        0u,                         /*    opTopoCnt                      */
                        ownIPtsn,                   /*    VLAN source IP, if known       */
                        destIPtsn,                  /*    where to send TSN PD to        */
                        0u,                         /*    Cycle time (µs): 0 for TSN     */
                        0u,                         /*    not redundant                  */
                        TRDP_FLAGS_TSN,             /*    use TSN packet header          */
                        (UINT8 *)gpOutputBufferTsn, /*    initial data                   */
                        PD_TSN_PAYLOAD_SIZE         /*    data size                      */
                        );


    if (err != TRDP_NO_ERR)
    {
        vos_printLogStr(VOS_LOG_USR, "TSN publisher error\n");
        tlc_terminate();
        return 1;
    }

    /****************************************************************************/
    /*   Publish some non-TSN sample data. Cycle time will be provided.         */
    /****************************************************************************/
    err = tlp_publish(gAppContextStd.appHandle,     /*    our application identifier     */
                      &gAppContextStd.pubHandle,    /*    our publication identifier     */
                      NULL, NULL,                   /*    no userRef, no Callback        */
                      0u,                           /*    serviceId                      */
                      PD_COMID_STD,                 /*    ComID to send                  */
                      0u,                           /*    etbTopoCnt local consist only  */
                      0u,                           /*    opTopoCnt                      */
                      ownIPstd,                     /*    default source IP              */
                      destIPstd,                    /*    where to send standard PD to   */
                      pdStd_cycleTime,              /*    Cycle time (µs)                */
                      0u,                           /*    not redundant                  */
                      TRDP_FLAGS_NONE,              /*    non TSN packet                 */
                      (UINT8 *)gpOutputBufferStd,   /*    some other data                */
                      PD_STD_PAYLOAD_SIZE           /*    data size                      */
                      );


    if (err != TRDP_NO_ERR)
    {
        vos_printLogStr(VOS_LOG_USR, "publisher error\n");
        tlc_terminate();
        return 1;
    }



    /*******************************************************************************/
    /* We initialised everything: now we can start the synchronized producer tasks */
    /*******************************************************************************/

    /* Start TSN producer with delay given */
    vos_getRealTime(&now);                  // use CLOCK_REALTIME: in most environments the realtime clock runs synchronized to TSN- / PTP-time
    now.tv_usec += (int) startTimeTsn;      // delay the TSN cyclic producer for "startTimeTsn" microseconds from "now"
    if (now.tv_usec >= 1000000) {
        now.tv_usec -= 1000000;
        now.tv_sec += 1;
    }
    err = (TRDP_ERR_T) vos_threadCreateSync(&myDataThreadTsn, "TSN Data Producer",
                                        VOS_THREAD_POLICY_RR,
                                        VOS_THREAD_PRIORITY_HIGHEST,
                                        pdTsn_cycleTime,    /*  interval for cyclic thread      */
                                        &now,               /*  start time for cyclic threads   */
                                        0u,    /*  stack size (default 4 x PTHREAD_STACK_MIN)   */
                                        (VOS_THREAD_FUNC_T) dataAppThreadTsn, &gAppContextTsn);




    /****************************************************************************/
    /* Enter the main loop.                                                     */
    /****************************************************************************/

    vos_printLogStr(VOS_LOG_DBG, "Enter the main loop...\n\n");
    
    while (1)
    {
        /* we change the data of the non-TSN packet every second telegram */
        (void) vos_threadDelay(2 * PD_COMID_STD_CYCLE);

        snprintf((char *) gpOutputBufferStd, PD_STD_PAYLOAD_SIZE, "Hello World, pckt %05u", counter++);
        tlp_put(gAppContextStd.appHandle, gAppContextStd.pubHandle, gpOutputBufferStd, PD_STD_PAYLOAD_SIZE);

        vos_printLog(VOS_LOG_USR, "Prepared new standard PD (%d): %s\n", PD_COMID_STD, gpOutputBufferStd);
    }

    /*
     *    We always clean up behind us!
     */

    gComThreadTsnRunning = FALSE;
    gComThreadStdRunning = FALSE;

    tlp_unpublish(gAppContextTsn.appHandle, gAppContextTsn.pubHandle);
    tlp_unpublish(gAppContextStd.appHandle, gAppContextStd.pubHandle);
    tlc_closeSession(gAppContextTsn.appHandle);
    tlc_closeSession(gAppContextStd.appHandle);
    tlc_terminate();

    return 0;
}
