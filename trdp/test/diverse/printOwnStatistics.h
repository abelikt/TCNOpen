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
TRDP_ERR_T printOwnStatistics(TRDP_APP_SESSION_T  appHandle, BOOL8 details);
