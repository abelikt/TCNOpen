/* $Header: /CSS/Code/RTS/COMMON/api/rts_dev.h 8     06-12-21 9:29 Bjarne Jensen $
******************************************************************************
*  COPYRIGHT    : (c) 1996 Adtranz
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : rts_dev.h
*
*  ABSTRACT     : RTS-DEVICE specific header file pointer
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/rts_dev.h $
*  
*  8     06-12-21 9:29 Bjarne Jensen
*  Added a guard against multiple inclusions.
*  
*  7     02-09-18 17:12 Thomas Clevström
*  Removed unsupported targets.
*  
*  6     02-09-18 9:37 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  5     01-02-23 13:35 Niclas Ericsson
*  Updated preprocessor switches according to NCR -LARS HÖGBERG10001
*  
*  4     00-10-30 11:30 Lars Högberg
*  Added O_HW_COMMON switch NCR -LARS HÖGBERG00009
*  
*  3     00-06-27 13:50 Lars Högberg
*  Added VCUlite
*  
*  2     00-06-21 9:27 Lars Högberg
*  Added VCU_LITE
*  
*  1     98-09-24 8:00 Anders Öhlander
*  The rts_dev.h is moved from the device specific parts to COMMON/API.
*  
*  4     98-05-29 15:12 Anders Öhlander
*  Changes the file for the device spec. see MR 93.
*
*  3     97-06-27 9.11 Anders Wallin
*  Header added
*
*  2     97-06-25 22.34 Anders Wallin
*  ee added
*
*  1     96-11-25 15.05 Anders Wallin
*
******************************************************************************/
#ifndef RTS_DEV_H
#define RTS_DEV_H

/*****************************************************************************
*   INCLUDES
*/
#if   defined O_VCU
#    include "rts_vcu.h"

#elif defined O_VCU_LITE
#    include "rts_lite.h"

#elif defined O_VCU6U_GW
#    include "rts_6ugw.h"

#elif defined O_VCU6U_GP
#    include "rts_6ugp.h"

#elif defined O_COMC
#    include "rts_comc.h"

#elif defined O_DCU
#    include "rts_dcu.h"

#elif defined O_HW_COMMON
#    define JMP_TABLE_BASE   0x02FFF400  /* 1 Kb - 0x2FFF7FF, works for all devices */

#else
#    error Unsupported target
#endif

#endif
