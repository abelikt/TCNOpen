/**********************************************************************************************************************/
/**
 * @file            trdp_tsn_def.h
 *
 * @brief           Additional definitions for TSN
 *
 * @details         This header file defines proposed extensions and additions to IEC61375-2-3:2017
 *                  The definitions herein are preliminary and may change with the next major release
 *                  of the IEC 61375-2-3 standard.
 *
 * @note            Project: TCNOpen TRDP prototype stack & FDF/DbD
 *
 * @author          Bernd Loehr, NewTec GmbH, 2019-02-19
 *
 * @remarks         Copyright 2019, NewTec GmbH
 *
 *
 * $Id$
 * 
 *      PL 2023-05-19: Ticket #434 Code adaption due to TSN header version 2 removal.
 *
 */

#ifndef TRDP_TSN_DEF_H
#define TRDP_TSN_DEF_H

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************************************************************
 * DEFINITIONS
 */


#undef TRDP_MD_DEFAULT_QOS
#define TRDP_MD_DEFAULT_QOS                 2u                          /**< matching new proposed priority classes */
#undef TRDP_MD_DEFAULT_SEND_PARAM
#define TRDP_MD_DEFAULT_SEND_PARAM          {TRDP_MD_DEFAULT_QOS, TRDP_MD_DEFAULT_TTL,\
                                                TRDP_MD_DEFAULT_RETRIES, FALSE, 0u}

/**  Default PD communication parameters   */
#undef TRDP_PD_DEFAULT_QOS
#define TRDP_PD_DEFAULT_QOS                 2u                          /**< matching new proposed priority classes */
#define TRDP_PD_DEFAULT_TSN_PRIORITY        3u                          /**< matching new proposed priority classes */
#define TRDP_PD_DEFAULT_TSN                 FALSE                       /**< matching new proposed priority classes */
#undef TRDP_PD_DEFAULT_SEND_PARAM
#define TRDP_PD_DEFAULT_SEND_PARAM          {TRDP_PD_DEFAULT_QOS, TRDP_PD_DEFAULT_TTL,\
                                                0u, TRDP_PD_DEFAULT_TSN, 0u}

/** New Message Types for TRDP TSN-PDU (preliminary)    */
#define TRDP_MSG_PT                     0x5074u                   /**< TSN PD Data "Pt"                      */

#ifdef __cplusplus
}
#endif


#endif
