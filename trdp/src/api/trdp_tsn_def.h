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
 *     AHW 2023-06-08: Ticket #435 Cleanup VLAN and TSN options at different places
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


/**  Default PD communication parameters   */
#define TRDP_PD_DEFAULT_TSN_PRIORITY        3u                          /**< matching new proposed priority classes */

#ifdef __cplusplus
}
#endif


#endif
