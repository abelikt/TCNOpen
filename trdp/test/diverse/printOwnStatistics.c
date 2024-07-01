/**********************************************************************************************************************/
/**
 * @file            printOwnStatistics
 *
 * @brief           Test application to print own statistics
 *
 * @details         Prints out own statistic information
 *
 * @note            Project: TCNOpen TRDP prototype stack
 *
 * @author          Armin-Hagen Weiss, Alstom Transportation Germany GmbH GmbH
 *
 * @remarks This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 *          If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *          Copyright Alstom SA or its subsidiaries and others, 2013-2023. All rights reserved.
 *
 * $Id: printOwnStatistics.c 2445 2024-05-31 09:12:34Z ahweiss $
 *
 *     AHW 2024-05-31: First version
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
#elif (defined (WIN32) || defined (WIN64))
#include "getopt.h"
#endif

#include "trdp_if_light.h"
#include "trdp_types.h"
#include "vos_thread.h"
#include "vos_sock.h"
#include "vos_utils.h"
#include "vos_mem.h"
#include "tlc_if.h"

/***********************************************************************************************************************
 * Prototypes
 */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/*
 *  Print out the own TRDP statistics
 * 
 *  @param[in]      appHandle       Handle returned from tlc_openSession
 *
 *  @retval         VOS_NO_ERR      no error
 *  @retval         VOS_PARAM_ERR   appHadle == NULL
 *  @retval         VOS_NO_INIT_ERR no valid appHandle
 */
TRDP_ERR_T printOwnStatistics(TRDP_APP_SESSION_T  appHandle, BOOL details)
{
    TRDP_STATISTICS_T statistics;
    UINT32 i;
    TRDP_VERSION_T  trdp;
 
    if (appHandle == NULL)
    {
        return TRDP_PARAM_ERR;
    }

    if (!trdp_isValidSession(appHandle))
    {
        return TRDP_NOINIT_ERR;
    }

    printf("\n------------------------------------------- OWN STATISTICS -----------------------------------------\n");

    tlc_getStatistics(appHandle, &statistics);

    trdp.evo = (UINT8)statistics.version;
    trdp.upd = (UINT8)(statistics.version >> 8);
    trdp.rel = (UINT8)(statistics.version >> 16);
    trdp.ver = (UINT8)(statistics.version >> 24);

    printf("version:                 %d.%d.%d.%d\n",
        (UINT32)trdp.ver,
        (UINT32)trdp.rel,
        (UINT32)trdp.upd,
        (UINT32)trdp.evo);
    printf("timestamp:               %llu\n", (statistics.timeStamp));
    printf("upTime:                  %u\n", (statistics.upTime));
    printf("lastStatReset:           %u\n", (statistics.statisticTime));
    printf("hostName:                %s\n", statistics.hostName);
    printf("leaderName:              %s\n", statistics.leaderName);
    printf("type:                    %s\n", statistics.type);   /* #451 */
    printf("ownIpAddr:               %s\n", vos_ipDotted((statistics.ownIpAddr)));
    printf("leaderIpAddr:            %s\n", vos_ipDotted((statistics.leaderIpAddr)));
    printf("vlanId:                  %u\n", (statistics.vlanId)); /* #451 */
    printf("processPrio:             %u\n", (statistics.processPrio));
    printf("processCycle:            %u\n", (statistics.processCycle));
    printf("numJoin:                 %u\n", (statistics.numJoin));
    printf("numRed:                  %u\n", (statistics.numRed));
    printf("----------------------------------------------------------------------------------------------------\n");

    /* Memory */
    printf("mem.total:               %u\n", (statistics.mem.total));
    printf("mem.free:                %u\n", (statistics.mem.free));
    printf("mem.minFree:             %u\n", (statistics.mem.minFree));
    printf("mem.numAllocBlocks:      %u\n", (statistics.mem.numAllocBlocks));
    printf("mem.numAllocErr:         %u\n", (statistics.mem.numAllocErr));
    printf("mem.numFreeErr:          %u\n", (statistics.mem.numFreeErr));
    printf("mem.usedBlockSizes:      ");

    for (i = 0; i < VOS_MEM_NBLOCKSIZES; i++)
    {
        printf("%d x %u, ", statistics.mem.usedBlockSize[i], statistics.mem.blockSize[i]);
        if ((i+1) % 8 == 0)
        {
            printf("\n                         ");
        }
    }

    printf("\n----------------------------------------------------------------------------------------------------\n");

     /* PD &  TCP & UDP */
    printf("pd.defQos:       %u\t tcpMd.defQoS:            %u\t\t udp.efQoS:             %u\n", statistics.pd.defQos, statistics.tcpMd.defQos, statistics.udpMd.defQos);
    printf("pd.defTtl:       %u\t tcpMd.defTtl:            %u\t\t udp.defTtl:            %u\n", statistics.pd.defTtl, statistics.tcpMd.defTtl, statistics.udpMd.defTtl);
    printf("pd.defTimeout:   %u\t tcpMd.defReplyTimeout:   %u\t udp.defReplyTimeout:     %u\n", statistics.pd.defTimeout, statistics.tcpMd.defReplyTimeout, statistics.udpMd.defReplyTimeout);
    printf("pd.numPub:       %u\t tcpMd.defConfirmTimeout: %u\t udp.defConfirmTimeout:   %u\n", statistics.pd.numPub, statistics.tcpMd.defConfirmTimeout, statistics.udpMd.defConfirmTimeout);
    printf("pd.numSubs:      %u\t tcpMd.numList:           %u\t\t udp.numList:           %u\n", statistics.pd.numSubs, statistics.tcpMd.numList, statistics.udpMd.numList);
    printf("pd.numMissed:    %u\t tcpMd.numConfirmTimeout: %u\t\t udp.numConfirmTimeout: %u\n", statistics.pd.numMissed, statistics.tcpMd.numConfirmTimeout, statistics.udpMd.numConfirmTimeout);
    printf("pd.numNoSubs:    %u\t tcpMd.numNoListener:     %u\t\t udp.numNoListener:     %u\n", statistics.pd.numNoSubs, statistics.tcpMd.numNoListener, statistics.udpMd.numNoListener);
    printf("pd.numSend:      %u\t tcpMd.numSend:           %u\t\t udp.numSend:           %u\n", statistics.pd.numSend, statistics.tcpMd.numSend, statistics.udpMd.numSend);
    printf("pd.numRcv:       %u\t tcpMd.numRcv:            %u\t\t udp.numRcv:            %u\n", statistics.pd.numRcv, statistics.tcpMd.numRcv, statistics.udpMd.numRcv);
    printf("pd.numTimeout:   %u\t tcpMd.numReplyTimeout:   %u\t\t udp.numReplyTimeout:   %u\n", statistics.pd.numTimeout, statistics.tcpMd.numReplyTimeout, statistics.udpMd.numReplyTimeout);
    printf("pd.numTopoErr:   %u\t tcpMd.numTopoErr:        %u\t\t udp.numTopoErr:        %u\n", statistics.pd.numTopoErr, statistics.tcpMd.numTopoErr, statistics.udpMd.numTopoErr);
    printf("pd.numProtErr:   %u\t tcpMd.numProtErr:        %u\t\t udp.numProtErr:        %u\n", statistics.pd.numProtErr, statistics.tcpMd.numProtErr, statistics.udpMd.numProtErr);
    printf("pd.numCrcErr:    %u\t tcpMd.numCrcErr:         %u\t\t udp.numCrcErr:         %u\n", statistics.pd.numCrcErr, statistics.tcpMd.numCrcErr, statistics.udpMd.numCrcErr);
    printf("pd.numNoPub:     %u\n", (statistics.pd.numNoPub));
    printf("----------------------------------------------------------------------------------------------------\n");

    if (details)
    {
        if (statistics.pd.numSubs != 0)
        {
            TRDP_SUBS_STATISTICS_T* pSubsStatistics = (TRDP_SUBS_STATISTICS_T*)vos_memAlloc(statistics.pd.numSubs * sizeof(TRDP_SUBS_STATISTICS_T));
            UINT16 numSubs = (UINT16)statistics.pd.numSubs;

            printf("PD Subscriber\n");

            if (tlc_getSubsStatistics(appHandle, &numSubs, pSubsStatistics) == TRDP_NO_ERR)
            {
                for (i = 0; i < numSubs; i++)
                {
                    printf("Comid: 0x%04x ", pSubsStatistics[i].comId);                           /* Subscribed ComId            */
                    printf("JoinedAddr: %s ", vos_ipDotted(pSubsStatistics[i].joinedAddr));     /* Joined IP address           */
                    printf("SrcIpAddr: %s ", vos_ipDotted(pSubsStatistics[i].filterAddr));      /* Filter IP address           */
                    printf("CallBack: %s ", (pSubsStatistics[i].callBack) ? "USED" : "UNUSED");
                    printf("UserRef: %s ", (pSubsStatistics[i].userRef) ? "USED" : "UNUSED");
                    printf("TimeOut: %dms ", (pSubsStatistics[i].timeout / 1000));
                    printf("TimeOutBehav: %s ", !(pSubsStatistics[i].toBehav) ? "DEFAULT" : (pSubsStatistics[i].toBehav) == 1 ? "ZERO" : "LAST");
                    printf("Received: %d ", pSubsStatistics[i].numRecv);        /* Number of packets received for this subscription.  */
                    printf("Missed: %d ", pSubsStatistics[i].numMissed);        /* Number of packets missed for this subscription.  */
                    printf("Status: %d \n", pSubsStatistics[i].status);         /* Last received status information  */
                }
            }

            vos_memFree(pSubsStatistics);
            printf("----------------------------------------------------------------------------------------------------\n");
        }

        if (statistics.pd.numPub)
        {
            TRDP_PUB_STATISTICS_T* pPubStatistics = (TRDP_PUB_STATISTICS_T*)vos_memAlloc(statistics.pd.numPub * sizeof(TRDP_PUB_STATISTICS_T));
            UINT16 numPub = (UINT16)statistics.pd.numPub;

            printf("PD Publisher\n");

            if (tlc_getPubStatistics(appHandle, &numPub, pPubStatistics) == TRDP_NO_ERR)
            {
                for (i = 0; i < numPub; i++)
                {
                    printf("Comid: 0x%04x ", pPubStatistics[i].comId);
                    printf("DestAddr: %s ", vos_ipDotted(pPubStatistics[i].destAddr));
                    printf("RedId: %d ", pPubStatistics[i].redId);
                    printf("RedState: %s ", pPubStatistics[i].redState ? "LEADER" : "FOLLOWER");
                    printf("Cycle: %dms ", pPubStatistics[i].cycle / 1000);
                    printf("NumSent: %d ", pPubStatistics[i].numSend);
                    printf("NumPut: %d \n", pPubStatistics[i].numPut);
                }
            }

            vos_memFree(pPubStatistics);
            printf("----------------------------------------------------------------------------------------------------\n");
        }

        if (statistics.udpMd.numList)
        {
            TRDP_LIST_STATISTICS_T* pListStatistics = (TRDP_LIST_STATISTICS_T*)vos_memAlloc(statistics.udpMd.numList * sizeof(TRDP_LIST_STATISTICS_T));
            UINT16 numList = (UINT16)statistics.udpMd.numList;

            printf("UDP MD Listener\n");

            if (tlc_getUdpListStatistics(appHandle, &numList, pListStatistics) == TRDP_NO_ERR)
            {

                for (i = 0; i < numList; i++)
                {
                    printf("DestUri: %s ", pListStatistics[i].uri);
                    printf("ComId: 0x%04x ", pListStatistics[i].comId);
                    printf("JoinedAddr: %s ", vos_ipDotted(pListStatistics[i].joinedAddr));
                    printf("CallBack: %s ", pListStatistics[i].callBack ? "USED" : "UNUSED");
                    printf("UserRef: %s ", pListStatistics[i].userRef ? "USED" : "UNUSED");
                    printf("Queue: %d ", pListStatistics[i].queue);
                    printf("NumReceived: %d \n", pListStatistics[i].numRecv);
                }
            }

            vos_memFree(pListStatistics);
            printf("----------------------------------------------------------------------------------------------------\n");
        }

        if (statistics.tcpMd.numList)
        {
            TRDP_LIST_STATISTICS_T* pListStatistics = (TRDP_LIST_STATISTICS_T*)vos_memAlloc(statistics.tcpMd.numList * sizeof(TRDP_LIST_STATISTICS_T));
            UINT16 numList = (UINT16)statistics.tcpMd.numList;

            printf("TCP MD Listener\n");

            if (tlc_getTcpListStatistics(appHandle, &numList, pListStatistics) == TRDP_NO_ERR)
            {
                for (i = 0; i < numList; i++)
                {
                    printf("DestUri: %s ", pListStatistics[i].uri);
                    printf("ComId: 0x%04x ", pListStatistics[i].comId);
                    printf("JoinedAddr: %s ", vos_ipDotted(pListStatistics[i].joinedAddr));
                    printf("CallBack: %s ", pListStatistics[i].callBack ? "USED" : "UNUSED");
                    printf("UserRef: %s ", pListStatistics[i].userRef ? "USED" : "UNUSED");
                    printf("Queue: %d ", pListStatistics[i].queue);
                    printf("NumReceived: %d \n", pListStatistics[i].numRecv);
                }
            }

            vos_memFree(pListStatistics);
            printf("----------------------------------------------------------------------------------------------------\n");
        }

        if (statistics.numRed)
        {
            TRDP_RED_STATISTICS_T* pRedStatistics = (TRDP_RED_STATISTICS_T*)vos_memAlloc(statistics.numRed * sizeof(TRDP_RED_STATISTICS_T));
            UINT16 numRed = statistics.numRed;

            printf("Redundancy groups\n");

            if (tlc_getRedStatistics(appHandle, &numRed, pRedStatistics) == TRDP_NO_ERR)
            {
                for (i = 0; i < numRed; i++)
                {
                    printf("Id: %d State: %s ", pRedStatistics[i].id, pRedStatistics[i].state ? "LEADER" : "FOLLOWER");

                    if ((i + 1) % 8 == 0)
                    {
                        printf("\n");
                    }
                }
                printf("\n");
            }

            vos_memFree(pRedStatistics);
            printf("----------------------------------------------------------------------------------------------------\n");
        }

        if (statistics.numJoin)
        {
            UINT32* pJoinStatistics = (UINT32*)vos_memAlloc(statistics.numJoin * sizeof(UINT32));
            UINT16 numJoin = statistics.numJoin;

            printf("Joined addresses\n");

            if (tlc_getJoinStatistics(appHandle, &numJoin, pJoinStatistics) == TRDP_NO_ERR)
            {
                for (i = 0; i < numJoin; i++)
                {
                    printf("%s ", vos_ipDotted(pJoinStatistics[i]));

                    if ((i + 1) % 8 == 0)
                    {
                        printf("\n");
                    }
                }
                printf("\n");
            }

            vos_memFree(pJoinStatistics);
            printf("----------------------------------------------------------------------------------------------------\n");
        }
    }
    return TRDP_NO_ERR;
}

