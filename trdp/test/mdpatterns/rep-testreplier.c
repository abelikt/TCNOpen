/**********************************************************************************************************************/
/**
 * @file            rep-testreplier.c
 *
 * @brief           Replier to Test the Call Repetition Functionality
 *
 * @details
 *
 * @note            Project: TCNOpen TRDP prototype stack
 *
 * @author          Mike
 *
 * @remarks This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 *          If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *          Copyright Alstom SA or its subsidiaries and others, 2013-2023. All rights reserved.
 *
 * $Id$
 * 
 *     AHW 2024-06-26: Ticket #261 MD reply/add listener does not use send parameters
 *     AHW 2024-06.19: Ticket #458 Unify cmd line interfaces of tests
 *     AHW 2024-05-31: Ticket #456 Example crashes with memory fault
 *      PL 2023-07-13: Ticket #435 Cleanup VLAN and TSN for options for Linux systems
 *      AM 2022-12-01: Ticket #399 Abstract socket type (VOS_SOCK_T, TRDP_SOCK_T) introduced, vos_select function is not anymore called with '+1'
 *      SB 2021-08-09: Compiler warnings
 *      BL 2017-11-28: Ticket #180 Filtering rules for DestinationURI does not follow the standard
 *
 */  
 
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>


#if defined (POSIX)
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <time.h>
#endif

#include <stdint.h>
#include <string.h>

#include "vos_types.h"
#include "vos_thread.h"                           
#include "trdp_if_light.h"
#include "printOwnStatistics.h"
#include "getopt.h"

#define APP_VERSION         "1.5"
#define APP_USE             "This tool acts as a replier to execute MD tests continiously."
#define RESERVED_MEMORY     240000
#define PREALLOCATE         {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
#define STATISTICS_CYCLE    50000 /* print statistics after the given number of cycles*/

#define CALLTEST_MR_COMID 0x2000
#define CALLTEST_MQ_COMID 0x2001

/* Status MR/MP tuple */
#define CALLTEST_MR_MP_COMID 0x3000
#define CALLTEST_MP_COMID 0x3001

/* No listener ever - triggers ME */
#define CALLTEST_MR_NOLISTENER_COMID 0x4000
#define CALLTEST_MP_NOLISTENER_COMID 0x4001

/* Moving Topo - triggers ME */
#define CALLTEST_MR_TOPOX_COMID 0x5000
#define CALLTEST_MP_TOPOX_COMID 0x5001

/* Infinity Pair - sound weird, though basically a reply after 0xFFFFFFFE usec, will proof it */
#define CALLTEST_MR_INF_COMID 0x6000
#define CALLTEST_MQ_INF_COMID 0x6001


static TRDP_APP_SESSION_T appSessionReplier = NULL;
static TRDP_LIS_T         listenHandle     = NULL;
static char               dataMQ[0x1000];
static char               dataMP[0x1000];
static TRDP_MEM_CONFIG_T  memcfg = { NULL, RESERVED_MEMORY, PREALLOCATE };

/* --- debug log --------------------------------------------------------------- */
#if (defined (WIN32) || defined (WIN64))
static FILE *pLogFile;
#endif


/******************************************************************************/
/** Routine to put some statistics into the reply message in ASCII
 *  via tcpdump/wireshark no special further code is needed to read these.
 *
 *  @param[out]     data        buffer of reply message
 *  @param[in]      appHandle    the handle returned by tlc_init
 *  @param[in]      countMQ        counter for tlm_replyQuery calls
 *  @param[in]      countMP        counter for tlm_reply calls
 *  @retval         none
 */
static void prepareData(char* data, TRDP_APP_SESSION_T appHandle, UINT32 countMQ, UINT32 countMP)
{
    TRDP_STATISTICS_T   Statistics;
    if ( tlc_getStatistics(appHandle, &Statistics) == TRDP_NO_ERR )
    {
        sprintf(data,"Replier: recvd UDP MD %08d trans UDP MD %08d conTO UDP MD %08d trans MQ %08d trans MP %08d",
                                          Statistics.udpMd.numRcv,
                                          Statistics.udpMd.numSend, 
                                          Statistics.udpMd.numConfirmTimeout,
                                          countMQ,
                                          countMP);
    }
    else
    {
        sprintf(data,"Replier: recvd UDP MD -------- trans UDP MD -------- conTO UDP MD -------- trans MQ -------- trans MP --------");
    }                                               
}

/******************************************************************************/
/** callback routine for receiving TRDP traffic
 *
 *  @param[in]    appHandle  handle returned also by tlc_init
 *  @param[in]    *pRefCon   pointer to user context
 *  @param[in]    *pMsg      pointer to received message information
 *  @param[in]    *pData     pointer to received data
 *  @param[in]    dataSize   size of received data pointer to received data
 */
static  void mdCallback(
                        void                    *pRefCon,
                        TRDP_APP_SESSION_T      appHandle,
                        const TRDP_MD_INFO_T    *pMsg,
                        UINT8                   *pData,
                        UINT32                  dataSize)
{   
    static UINT32 countMQ = 0;
    static UINT32 countMP = 0;
    static UINT32 cycle = 0;

    TRDP_ERR_T    err;

    if ((cycle++) % STATISTICS_CYCLE == 0)
    {
        printOwnStatistics(appHandle, TRUE);
    }

    switch (pMsg->resultCode)
    {
        case TRDP_NO_ERR:
            if (pMsg->comId == CALLTEST_MR_COMID)
            {
                err = tlm_replyQuery(appSessionReplier,                                  /* #261 send params removed */
                                     (const TRDP_UUID_T*)pMsg->sessionId,
                                     CALLTEST_MQ_COMID,
                                     0,
                                     1500000,
                                     (const UINT8*)&dataMQ,
                                     sizeof(dataMQ),
                                     NULL);

                if (err != TRDP_NO_ERR)
                {
                    /* echo unformatted error code */
                    printf("tlm_replyQuery failed - error code %d\n",err);
                }
                countMQ++;
            }
            if (pMsg->comId == CALLTEST_MR_MP_COMID)
            {
                /* This ComID serves as fast statistics server, providing some load also */
                prepareData((char*)&dataMP,appSessionReplier,countMQ,countMP);
                err = tlm_reply(appSessionReplier,                                  /* #261 send params removed */
                                (const TRDP_UUID_T*)pMsg->sessionId,
                                CALLTEST_MP_COMID,
                                0,
                                (const UINT8*)&dataMP,
                                sizeof(dataMP), NULL);
                if (err != TRDP_NO_ERR)
                {
                    /* echo unformatted error code */
                    printf("tlm_reply CALLTEST_MP_COMID failed - error code %d\n",err);
                }
                countMP++;
            }
            if (pMsg->comId == CALLTEST_MR_TOPOX_COMID)
            {
                /* */
                err = tlm_reply(appSessionReplier,                                  /* #261 send params removed */
                                (const TRDP_UUID_T*)pMsg->sessionId,
                                CALLTEST_MP_TOPOX_COMID,
                                0,
                                (const UINT8*)&dataMP,
                                sizeof(dataMP), NULL);
                if (err != TRDP_NO_ERR)
                {
                    /* echo unformatted error code */
                    printf("tlm_reply CALLTEST_MP_TOPOX_COMID failed - error code %d\n",err);
                }

            }
            if (pMsg->comId == CALLTEST_MR_INF_COMID)
            {
                err = tlm_replyQuery(appSessionReplier,
                                     (const TRDP_UUID_T*)pMsg->sessionId,              /* #261 send params removed */
                                     CALLTEST_MQ_INF_COMID,
                                     0,
                                     1500000,
                                     (const UINT8*)&dataMQ,
                                     sizeof(dataMQ), NULL);
                if (err != TRDP_NO_ERR)
                {
                    /* echo unformatted error code */
                    printf("tlm_replyQuery CALLTEST_MQ_INF_COMID failed - error code %d\n",err);
                }                
            }

            break;
        case TRDP_REPLYTO_ERR:
        case TRDP_TIMEOUT_ERR:
            /* The application can decide here if old data shall be invalidated or kept    */
            printf("Packet timed out (ComID 0x%04x, SrcIP: %s)\n", pMsg->comId, vos_ipDotted(pMsg->srcIpAddr));
            break;
        case TRDP_CONFIRMTO_ERR:
            /* confirmation from caller has timed out */
            printf("Confirmation Timed Out (ComID 0x%04x, SrcIP: %s)\n", pMsg->comId, vos_ipDotted(pMsg->srcIpAddr));
            break;
        default:
            break;
    }
}


/**********************************************************************************************************************/
/* Logging function */
static void printLog(
    void* pRefCon,
    VOS_LOG_T   category,
    const CHAR8* pTime,       // timestamp string "yyyymmdd-hh:mm:ss.µs"
    const CHAR8* pFile,
    UINT16      line,
    const CHAR8* pMsgStr)
{
    static const char* cat[] = { "ERR", "WAR", "INF", "DBG" };

#if (defined (WIN32) || defined (WIN64))
    if (pLogFile == NULL)
    {
        char        buf[1024];
        const char* file = strrchr(pFile, '\\');
        _snprintf(buf, sizeof(buf), "%s %s:%d %s",
            cat[category], file ? file + 1 : pFile, line, pMsgStr);
        OutputDebugString((LPCWSTR)buf);
    }
    else
    {
        fprintf(pLogFile, "%s File: %s Line: %d %s\n", cat[category], pFile, (int)line, pMsgStr);
        fflush(pLogFile);
    }
#else
    const char* file = strrchr(pFile, '/');
    fprintf(stderr, "%s %s:%d %s",
        cat[category], file ? file + 1 : pFile, line, pMsgStr);
#endif

}


/**********************************************************************************************************************/
/* Print a sensible usage message */
void usage(const char* appName)
{
    printf("%s: Version %s\t(%s - %s)\n", appName, APP_VERSION, __DATE__, __TIME__);
    printf("Usage of %s\n", appName);
    printf(APP_USE"\n"
        "Arguments are:\n"
        "-o <own IP address>       in dotted decimal (ie. 10.2.24.1)\n"
        "-t <target IP address>    in dotted decimal (ie. 10.2.24.1)\n"
        "-l <logfile>              file name (e.g. test.txt)\n"
        "-v                        print version and quit\n"
    );
}


/******************************************************************************/
/** Main routine
 */
int main(int argc, char** argv)
{
    TRDP_ERR_T       err;
    UINT32           callerIP=0;
    UINT32           replierIP=0; 
    TRDP_FDS_T       rfds;
    TRDP_TIME_T      tv;
    TRDP_SOCK_T      noOfDesc=TRDP_INVALID_SOCKET;   /* #399 #456 */
    struct timeval   tv_null = { 0, 0 };
    int              rv;
    char             filename[TRDP_MAX_FILE_NAME_LEN];
    int              ch;

    TRDP_MD_CONFIG_T mdConfiguration = {mdCallback, 
                                        NULL, 
                                        {0u, 0u, 0u},
                                        TRDP_FLAGS_CALLBACK, 
                                        1000000u,
                                        1000000u,
                                        1000000u,
                                        1000000u,
                                        TRDP_MD_UDP_PORT,
                                        0u,
                                        20u};/*have some space for sessions*/
    TRDP_PROCESS_CONFIG_T   processConfig   = {"MD_REPLIER", "", "", 0, 0, TRDP_OPTION_BLOCK, 0u};

    
    /* get the arguments/options */
    while ((ch = getopt(argc, argv, "t:o:l:h?v")) != -1)
    {
        switch (ch)
        {
        case 'o':
        {    /*  read ip    */
            unsigned int ip[4];

            if (sscanf(optarg, "%u.%u.%u.%u",
                &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
            {
                usage(argv[0]);
                return 1;
            }
            replierIP = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
            break;
        }
        case 't':
        {    /*  read ip    */
            unsigned int ip[4];

            if (sscanf(optarg, "%u.%u.%u.%u",
                &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
            {
                usage(argv[0]);
                return 1;
            }
            callerIP = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
            break;
        }
        case 'v':    /*  version */
        {
            printf("%s: Version %s\t(%s - %s)\n",
                argv[0], APP_VERSION, __DATE__, __TIME__);
            return 0;
            break;
        }
        case 'l':
        {    /*  Log file   */
            strncpy(filename, optarg, sizeof(filename) - 1);
            pLogFile = fopen(optarg, "w");
            break;
        }

        case 'h':
        case '?':
        default:
            usage(argv[0]);
            return 1;
        }
    }

    printf("%s: Version %s\t(%s - %s)\n", argv[0], APP_VERSION, __DATE__, __TIME__);

    if ((callerIP == 0) || (replierIP == 0))
    {
        usage(argv[0]);
        return -1;
    }

    err = tlc_init(printLog, NULL, &memcfg);

    /*    Open a session for callback operation    (MD only) */
    if (tlc_openSession(&appSessionReplier,
                        replierIP, 
                        0,                        
                        NULL,                     
                        NULL, 
                        &mdConfiguration,        
                        &processConfig) != TRDP_NO_ERR)
    {
        printf("OpenSession error\n");
        return 1;
    }
    err = tlm_addListener(appSessionReplier, 
                          &listenHandle, 
                          NULL,
                          NULL,
                          TRUE,
                          CALLTEST_MR_COMID, 
                          0u,
                          0u,
                          VOS_INADDR_ANY,
                          VOS_INADDR_ANY, VOS_INADDR_ANY,
                          TRDP_FLAGS_CALLBACK,
                          NULL, NULL);

    if (err != TRDP_NO_ERR)
    {
        printf("Listening to CALLTEST_MR_COMID failed\n");
        goto CLEANUP;
    }
    err = tlm_addListener(appSessionReplier, 
                          &listenHandle, 
                          NULL,
                          NULL,
                          TRUE,
                          CALLTEST_MR_MP_COMID, 
                          0u,
                          0u,
                          VOS_INADDR_ANY,
                          VOS_INADDR_ANY, VOS_INADDR_ANY,
                          TRDP_FLAGS_CALLBACK,
                          NULL, NULL);

    if (err != TRDP_NO_ERR)
    {
        printf("Listening to CALLTEST_MR_COMID failed\n");
        goto CLEANUP;
    }
    err = tlm_addListener(appSessionReplier, 
                          &listenHandle, 
                          NULL,
                          NULL,
                          TRUE,
                          CALLTEST_MR_TOPOX_COMID, 
                          0u,
                          0u,
                          VOS_INADDR_ANY,
                          VOS_INADDR_ANY, VOS_INADDR_ANY,
                          TRDP_FLAGS_CALLBACK,
                          NULL, NULL);

    if (err != TRDP_NO_ERR)
    {
        printf("Listening to CALLTEST_MR_COMID failed\n");
        goto CLEANUP;
    }
    err = tlm_addListener(appSessionReplier, 
                          &listenHandle, 
                          NULL,
                          NULL,
                          TRUE,
                          CALLTEST_MR_INF_COMID, 
                          0u,
                          0u,
                          VOS_INADDR_ANY,
                          VOS_INADDR_ANY, VOS_INADDR_ANY,
                          TRDP_FLAGS_CALLBACK,
                          NULL, NULL);

    if (err != TRDP_NO_ERR)
    {
        printf("Listening to CALLTEST_MR_COMID failed\n");
        goto CLEANUP;
    }

    while (1)
    {   
        FD_ZERO(&rfds);
        tlc_getInterval(appSessionReplier, &tv, &rfds, &noOfDesc);
        rv = vos_select(noOfDesc, &rfds, NULL, NULL, &tv_null);  /* #399 */
        tlc_process(appSessionReplier, &rfds, &rv);
    }
CLEANUP:
    tlm_delListener(appSessionReplier, listenHandle);
    tlc_closeSession(appSessionReplier);
    return 0;
}
