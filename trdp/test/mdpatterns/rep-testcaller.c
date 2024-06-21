/**********************************************************************************************************************/
/**
 * @file            rep-testcaller.c
 *
 * @brief           Caller for the Test of the Call Repetition Functionality
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
 *     AHW 2024-06-19: Ticket #458 Unify cmd line interfaces of tests
 *      PL 2023-07-13: Ticket #435 Cleanup VLAN and TSN for options for Linux systems
 *      AM 2022-12-01: Ticket #399 Abstract socket type (VOS_SOCK_T, TRDP_SOCK_T) introduced, vos_select function is not anymore called with '+1'
 *      SB 2021-08-09: Compiler warnings
 *      BL 2018-01-29: Ticket #188 Typo in the TRDP_VAR_SIZE definition
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
#define APP_USE             "This tool acts as a caller to execute MD tests continiously."
#define RESERVED_MEMORY     240000
#define PREALLOCATE         {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
#define ERROR_CYCLE         1000  /* generate errors after the given number of cycles */
#define STATISTICS_CYCLE   50000  /* print statistics after the given number of cycles */

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

#define ONESECOND 1000000

static TRDP_APP_SESSION_T appSessionCaller = NULL;
static TRDP_LIS_T         listenHandle     = NULL;
static char               dataMRMQ[0x1000]; /* for CALLTEST_MR_COMID */
static char               dataMRMP[0x1000]; /* for CALLTEST_MR_MP_COMID */
static VOS_MUTEX_T        callMutex        = NULL; /* for the MR MQ tuple */
static VOS_MUTEX_T        callMutexMP      = NULL; /* for the MR MP tuple */
static VOS_MUTEX_T        callMutexME      = NULL; /* for the MR ME tuple */
static VOS_MUTEX_T        callMutexTO      = NULL; /* for the MR MP/ME topo trouble */
static VOS_MUTEX_T        callMutexIN      = NULL; /* for the MR MQ infinity tuple */
static INT32              callFlagMR_MQ    = TRUE;
static INT32              callFlagMR_MP    = TRUE;
static INT32              callFlagME       = TRUE;
static INT32              callFlagTO       = TRUE;
static INT32              callFlagIN       = TRUE;
static TRDP_MEM_CONFIG_T  memcfg = { NULL, RESERVED_MEMORY, PREALLOCATE };


/* --- debug log --------------------------------------------------------------- */
#if (defined (WIN32) || defined (WIN64))
static FILE *pLogFile;
#endif

void print_log (void *pRefCon, VOS_LOG_T category, const CHAR8 *pTime,
                const CHAR8 *pFile, UINT16 line, const CHAR8 *pMsgStr)
{
    static const char *cat[] = { "ERR", "WAR", "INF", "DBG" };
#if (defined (WIN32) || defined (WIN64))
    if (pLogFile == NULL)
    {
        char        buf[1024];
        const char  *file = strrchr(pFile, '\\');
        _snprintf(buf, sizeof(buf), "%s %s:%d %s",
                  cat[category], file ? file + 1 : pFile, line, pMsgStr);
        OutputDebugString((LPCWSTR)buf);
    }
    else
    {
        fprintf(pLogFile, "%s File: %s Line: %d %s\n", cat[category], pFile, (int) line, pMsgStr);
        fflush(pLogFile);
    }
#else
    const char *file = strrchr(pFile, '/');
    fprintf(stderr, "%s %s:%d %s",
            cat[category], file ? file + 1 : pFile, line, pMsgStr);
#endif
}

static void manageMDCall(TRDP_APP_SESSION_T appSession,
                         UINT32 comId,
                         UINT32 replierIP,
                         const UINT8* pData,
                         UINT32 datasize,
                         VOS_MUTEX_T mutex,
                         INT32* callFlag,
                         UINT32 etbTopo,
                         UINT32 opTopo,
                         UINT32 timeOut)
{
    if ( vos_mutexTryLock(mutex) == VOS_NO_ERR )
    {
        if ( *callFlag == TRUE )
        {
            /* call replier */
//            printf("perform tlm_request comId %d\n",comId);
            (void)tlm_request(appSession,
                              NULL,
                              NULL/*default callback fct.*/,
                              NULL,
                              comId,
                              etbTopo,
                              opTopo,
                              0U,
                              replierIP,
                              TRDP_FLAGS_DEFAULT,
                              1,
                              timeOut,
                              NULL,
                              pData,
                              datasize,
                              NULL,
                              NULL);
            *callFlag = FALSE;
        }
        vos_mutexUnlock(mutex);
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
    static UINT32 switchConfirmOnOff = 0U;

    switch (pMsg->resultCode)
    {
        case TRDP_NO_ERR:
            if (pMsg->comId == CALLTEST_MQ_COMID)
            {
                /* no confirm for every 10000th MQ */
                if ((switchConfirmOnOff % ERROR_CYCLE) != 0)
                {
                    /* sending confirm for 99 times */
                    /* recvd. MQ from our replier */
                    /* send confirm */ 
                    tlm_confirm(appSessionCaller,
                                (const TRDP_UUID_T*)pMsg->sessionId,
                                0,
                                NULL);
                }
                switchConfirmOnOff++; /* wrap around shall be allowed */
                /* enable next call */
                if (vos_mutexLock(callMutex) == VOS_NO_ERR)
                {
                    callFlagMR_MQ = TRUE;
                    vos_mutexUnlock(callMutex);
                }
            }
            if (pMsg->comId == CALLTEST_MP_COMID)
            {
                if (vos_mutexLock(callMutexMP) == VOS_NO_ERR)
                {
                    callFlagMR_MP = TRUE;
                    vos_mutexUnlock(callMutexMP);
                }
            }
            if (pMsg->comId == CALLTEST_MP_TOPOX_COMID)
            {
                if (vos_mutexLock(callMutexTO) == VOS_NO_ERR)
                {
                    callFlagTO = TRUE;
                    vos_mutexUnlock(callMutexTO);
                }
            }
            if ( pMsg->comId == CALLTEST_MQ_INF_COMID )
            {
                if ( vos_mutexLock(callMutexIN) == VOS_NO_ERR )
                {
        //            printf("Received MQ reply from INFINITY Replier\n");
                    if ( pMsg->msgType == TRDP_MSG_MQ )
                    {
                        TRDP_ERR_T errCode;
                        
                        errCode = tlm_confirm(appSessionCaller,
                            (const TRDP_UUID_T*)pMsg->sessionId,
                            0,
                            NULL);
                        
                        if (errCode != TRDP_NO_ERR)
                        {
                            printf("unable to send confirm(% d)\n", errCode);
                       }
                    }
                    callFlagIN = TRUE;
                    vos_mutexUnlock(callMutexIN);
                }
            }
            break;
        case TRDP_REPLYTO_ERR:
        case TRDP_TIMEOUT_ERR:
            /* The application can decide here if old data shall be invalidated or kept */
            printf("Packet timed out (ComID 0x%04x, SrcIP: %s)\n", pMsg->comId, vos_ipDotted(pMsg->srcIpAddr));
            if (pMsg->comId == CALLTEST_MR_COMID)
            {
                if (vos_mutexLock(callMutex) == VOS_NO_ERR)
                {
                    callFlagMR_MQ = TRUE;
                    vos_mutexUnlock(callMutex);
                }
            }
            else if (pMsg->comId == CALLTEST_MR_MP_COMID)
            {
                if (vos_mutexLock(callMutexMP) == VOS_NO_ERR)
                {
                    callFlagMR_MP = TRUE;
                    vos_mutexUnlock(callMutexMP);
                }
            }
            else if (pMsg->comId == CALLTEST_MR_NOLISTENER_COMID)
            {
                printf("CALLTEST_MR_NOLISTENER call expired\n");
                if (vos_mutexLock(callMutexME) == VOS_NO_ERR)
                {
                    callFlagME = TRUE;
                    vos_mutexUnlock(callMutexME);
                }                
            }
            else if (pMsg->comId == CALLTEST_MR_TOPOX_COMID)
            {
                printf("CALLTEST_MR_TOPOX_COMID call expired\n");
                if (vos_mutexLock(callMutexTO) == VOS_NO_ERR)
                {
                    callFlagTO = TRUE;
                    vos_mutexUnlock(callMutexTO);
                }                
            }
            else
            {
                /* should not happen */
            }
            break;
        case TRDP_NOLIST_ERR:
            if (pMsg->comId == CALLTEST_MR_NOLISTENER_COMID)
            {
                /* this is the routine to deal with the Me */
                if (pMsg->msgType == TRDP_MSG_ME )
                {  
                    /* re-enable calling */
                    if (vos_mutexLock(callMutexME) == VOS_NO_ERR)
                    {
                        callFlagME = TRUE;
                        vos_mutexUnlock(callMutexME);
                    }                
                }
            }
            break;
        default:
            break;
    }
}  

static FILE* pLogFile;

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
    if (pLogFile != NULL)
    {
        fprintf(pLogFile, "%s%s %s@%d: %s", pTime, category == VOS_LOG_ERROR ? "ERR " : (category == VOS_LOG_WARNING ? "WAR " : (category == VOS_LOG_INFO ? "INFO" : "DBG ")), pFile, (int)line, pMsgStr);
        fflush(pLogFile);
    }
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
    TRDP_SOCK_T      noOfDesc = TRDP_INVALID_SOCKET;
    struct timeval   tv_null = { 0, 0 };
    int rv;
    char filename[TRDP_MAX_FILE_NAME_LEN];
    int ch;

    TRDP_MD_CONFIG_T mdConfiguration = {mdCallback, 
                                        NULL, 
                                        {3, 64, 2},
                                        TRDP_FLAGS_CALLBACK, 
                                        1000000, 
                                        1000000, 
                                        1000000, 
                                        1000000, 
                                        17225,
                                        0, 
                                        5};

    TRDP_PROCESS_CONFIG_T   processConfig   = {"MD_CALLER", "", "", 0, 0, TRDP_OPTION_BLOCK, 0u};

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
            callerIP = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
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
            replierIP = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
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

    if ((callerIP == 0) || (replierIP ==0))
    {
        usage(argv[0]);
        return -1;
    }

    err = tlc_init(print_log, NULL, &memcfg);

    /* pure MD session */
    if (tlc_openSession(&appSessionCaller,
                        callerIP, 
                        0,                        
                        NULL,                     
                        NULL, 
                        &mdConfiguration,
                        &processConfig) != TRDP_NO_ERR)
    {
        printf("TRDP OpenSession error\n");
        return 1;
    }

    /* Listener for reply expected from CALLTEST_MR_COMID call */
    err = tlm_addListener(appSessionCaller, 
                          &listenHandle, 
                          NULL,
                          NULL,
                          TRUE,
                          CALLTEST_MQ_COMID, 
                          0u,
                          0u,
                          VOS_INADDR_ANY,
                          VOS_INADDR_ANY, VOS_INADDR_ANY,
                          TRDP_FLAGS_CALLBACK, 
                          NULL, NULL);

    if (err != TRDP_NO_ERR)
    {
        printf("TRDP Listening to CALLTEST_MQ_COMID failed\n");
        goto CLEANUP;
    }

    /* Listener for reply expected from CALLTEST_MR_MP_COMID call */
    err = tlm_addListener(appSessionCaller, 
                          &listenHandle, 
                          NULL,
                          NULL,
                          TRUE,
                          CALLTEST_MP_COMID, 
                          0u,
                          0u,
                          VOS_INADDR_ANY,
                          VOS_INADDR_ANY, VOS_INADDR_ANY,
                          TRDP_FLAGS_CALLBACK, 
                          NULL, NULL);

    if (err != TRDP_NO_ERR)
    {
        printf("TRDP Listening to CALLTEST_MP_COMID failed\n");
        goto CLEANUP;
    }

    /* Listener for reply expected to have transient topo counter trouble */
    err = tlm_addListener(appSessionCaller, 
                          &listenHandle, 
                          NULL,
                          NULL,
                          TRUE,
                          CALLTEST_MP_TOPOX_COMID, 
                          0u,
                          0u,
                          VOS_INADDR_ANY,
                          VOS_INADDR_ANY, VOS_INADDR_ANY,
                          TRDP_FLAGS_CALLBACK,
                          NULL, NULL);

    if (err != TRDP_NO_ERR)
    {
        printf("TRDP Listening to CALLTEST_MP_COMID failed\n");
        goto CLEANUP;
    }

    /* Listener for reply expected from CALLTEST_MR_INF_COMID call */
    err = tlm_addListener(appSessionCaller, 
                          &listenHandle, 
                          NULL,
                          NULL,
                          TRUE,
                          CALLTEST_MQ_INF_COMID, 
                          0u,
                          0u,
                          VOS_INADDR_ANY,
                          VOS_INADDR_ANY, VOS_INADDR_ANY,
                          TRDP_FLAGS_CALLBACK, 
                          NULL, NULL);

    if (err != TRDP_NO_ERR)
    {
        printf("TRDP Listening to CALLTEST_MQ_INF_COMID failed\n");
        goto CLEANUP;
    }

    if (vos_mutexCreate(&callMutex) != VOS_NO_ERR)
    {
        printf("Mutex Creation for callMutex failed\n");
        goto CLEANUP;
    }
    if (vos_mutexCreate(&callMutexMP) != VOS_NO_ERR)
    {
        printf("Mutex Creation for callMutexMP failed\n");
        goto CLEANUP;
    }
    if (vos_mutexCreate(&callMutexME) != VOS_NO_ERR)
    {
        printf("Mutex Creation for callMutexME failed\n");
        goto CLEANUP;
    }
    if (vos_mutexCreate(&callMutexTO) != VOS_NO_ERR)
    {
        printf("Mutex Creation for callMutexTO failed\n");
        goto CLEANUP;
    }
    if (vos_mutexCreate(&callMutexIN) != VOS_NO_ERR)
    {
        printf("Mutex Creation for callMutexIN failed\n");
        goto CLEANUP;
    }

    while (1)
    {
        static UINT32 cycles = 0U;

        if (cycles++ % STATISTICS_CYCLE == 0)
        {
            printOwnStatistics(appSessionCaller, TRUE);
        }

        FD_ZERO(&rfds);

        tlc_getInterval(appSessionCaller, &tv, &rfds, &noOfDesc);
        rv = vos_select(noOfDesc, &rfds, NULL, NULL, &tv_null);    /* #399 */
        tlc_process(appSessionCaller, &rfds, &rv);

        /* very basic locking to keep everything no frenzy and simple */
        /* see mdCallback for unlocking conditions - be aware, that   */
        /* the replier must really be started before this program!    */

        manageMDCall(appSessionCaller,
                     CALLTEST_MR_COMID,
                     replierIP,
                     (const UINT8*)&dataMRMQ,
                     sizeof(dataMRMQ),
                     callMutex,
                     &callFlagMR_MQ,
                     0,
                     0,
                     ONESECOND);
        manageMDCall(appSessionCaller,
                     CALLTEST_MR_MP_COMID,
                     replierIP,
                     (const UINT8*)&dataMRMP,
                     sizeof(dataMRMP),
                     callMutexMP,
                     &callFlagMR_MP,
                     0,
                     0,
                     ONESECOND);
        manageMDCall(appSessionCaller,
                     CALLTEST_MR_NOLISTENER_COMID,
                     replierIP,
                     (const UINT8*)"HELLO",
                     sizeof("HELLO"),
                     callMutexME,
                     &callFlagME,
                     0,
                     0,
                     ONESECOND);
        manageMDCall(appSessionCaller,
                     CALLTEST_MR_INF_COMID,
                     replierIP,
                     (const UINT8*)"SETI CALL",
                     sizeof("SETI CALL"),
                     callMutexIN,
                     &callFlagIN,
                     0,
                     0,
                     TRDP_MD_INFINITE_TIME);

        /* existing topo config - replier shall asnwer */
        manageMDCall(appSessionCaller,
                     CALLTEST_MR_TOPOX_COMID,
                     replierIP,
                     (const UINT8*)"WORLD",
                     sizeof("WORLD"),
                     callMutexTO,
                     &callFlagTO,
                     0,
                     0,
                     ONESECOND);
    }

CLEANUP:
    tlm_delListener(appSessionCaller, listenHandle);
    tlc_closeSession(appSessionCaller);

    return 0;
}

