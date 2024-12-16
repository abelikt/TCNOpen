/* $Header: /CSS/Code/RTS/COMMON/api/rts.h 114   07-03-27 17:13 Bjarne Jensen $
******************************************************************************
*  COPYRIGHT      : (c) 1995 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT        : CSS
*
*  MODULE         : rts.h
*
*  ABSTRACT       : RTS general header file
*
******************************************************************************
*  HISTORY        :
*   $Log: /CSS/Code/RTS/COMMON/api/rts.h $
*  
*  114   07-03-27 17:13 Bjarne Jensen
*  New release 1.14.1
*  
*  113   07-03-08 12:01 Bjarne Jensen
*  RTS_UPDATE now set to 0.
*  
*  112   07-01-19 12:59 Bjarne Jensen
*  Update 99 is better than 255 because MTPE can only have 2 digits.
*  
*  111   07-01-16 12:36 Bjarne Jensen
*  Bumped RELEASE to 14 and UPDATE to 255. This is BETA.
*  
*  109   06-10-11 15:42 Bjarne Jensen
*  Changed to version 1.13.1
*  
*  107   06-08-24 11:18 Mattias Rehnman
*  Version upgraded.
*  
*  103   06-05-30 9:38 Kristoffer Johansson
*  RTS version 1.10.8
*  
*  102   06-05-29 12:46 Christer Olsson
*  Updated to version 1.12.4
*  
*  101   06-04-19 14:13 Christer Olsson
*  Updated to version to 1.12.3
*  
*  100   05-01-14 14:01 Anders Persson
*  Update for Release 1.12.2
*  
*  99    05-01-14 13:56 Anders Persson
*  RTS version 1.12.2
*  
*  98    04-11-10 13:26 Bjarne Jensen
*  RTS version 1.10.7
*  
*  95    04-03-15 15:17 Thomas Clevström
*  RTS version 1.10.6
*  
*  93    03-12-12 13:59 Thomas Clevström
*  RTS version 1.10.5
*  
*  92    03-11-07 14:10 Thomas Clevström
*  RTS version 1.12.0
*  
*  91    03-08-14 9:31 Thomas Clevström
*  RTS version 1.11.1
*  
*  89    03-04-09 17:53 Thomas Clevström
*  RTS version 1.10.4
*  
*  88    03-01-09 12:52 Thomas Clevström
*  RTS version 1.11.0
*  
*  86    02-12-02 12:31 Thomas Clevström
*  RTS version 1.10.3
*  
*  85    02-11-28 18:22 Thomas Clevström
*  Version 1.11.-1 (beta B)
*  
*  83    02-11-25 9:13 Thomas Clevström
*  Version 1.10.2
*  
*  82    02-10-24 14:21 Thomas Clevström
*  Version 1.11.-1 (beta)
*  
*  81    02-09-18 9:37 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  79    02-06-27 17:54 Thomas Clevström
*  Version 1.10.1
*  
*  78    02-02-13 2:01p Christer Olsson
*  Changed RTS version to 1.10.0
*  
*  77    01-11-19 5:00p Christer Olsson
*  Changed RTS version to 1.10.A
*  
*  76    01-10-30 13:13 Kristoffer Johansson
*  version 1.9.3
*  
*  75    01-10-17 17:35 Kristoffer Johansson
*  Version 1.9.2
*  
*  74    01-04-19 16:22 Thomas Clevström
*  Version 1.9.1
*  
*  73    01-04-06 17:05 Thomas Clevström
*  Version 1.9.0
*  
*  72    01-02-16 13:19 Thomas Clevström
*  Untabify.
*  Version 1.8.1
*  
*  70    00-12-05 8:28 Lars Högberg
*  Version 1.8.0
*  
*  69    00-04-18 11:05 Martin Gisbert
*  version 1.7.3
*  
*  68    00-04-04 15:52 Lars Högberg
*  version 1.7.2
*  
*  67    00-03-31 16:53 Lars Högberg
*  version 1.8.0
*  
*  66    00-02-22 10:29 Martin Gisbert
*  version 1.7.1
*  
*  65    00-01-20 15:38 Martin Gisbert
*  version 1.7.0
*  
*  64    99-12-20 17:51 Martin Gisbert
*  version 17A
*  
*  63    99-12-10 17:32 Lars Högberg
*  Update to 1.7.0
*  
*  62    99-10-22 13:24 Martin Gisbert
*  update to 1.6.1
*  
*  61    99-06-30 8:48 Anders Öhlander
*  Update to 1.6.0.
*  
*  60    99-06-29 16:41 Anders Öhlander
*  Update version to 1.6.A.
*  
*  59    5/10/99 12:09p Anders Öhlander
*  Update to version 1.5.2.
*  
*  58    99-03-29 9:35 Anders Öhlander
*  Update to 1.5.1.
*  
*  57    99-03-16 19:24 Anders Öhlander
*  Update version to 1.5.0.
*  
*  56    99-03-11 18:08 Anders Öhlander
*  Change the version to 1.4.1.
*  
*  55    98-12-17 12:15 Anders Öhlander
*  New version on the RTS 1.4.0.
*
*  54    98-10-28 10:29 Anders Öhlander
*  Update to 1.3.2.
*
*  53    98-10-08 19:21 Anders Öhlander
*  Update the RTS version to 1.3.1.
*
*  52    98-05-29 12:43 Anders Öhlander
*  Add include of RTS_DEV.H file, see MR 93.
*
*  51    98-04-16 6:24 Anders Wallin
*  Update the version to 1.3.B.
*
*  50    98-04-02 15:37 Anders Wallin
*  AO : Change the RTS-version to 1.3.A.
*
*  49    97-09-11 8:05 Anders Wallin
*  RTS 1.2.0
*
*  48    97-08-04 7.55 Anders Wallin
*  RTS 1.1.1
*
*  47    97-06-27 9.23 Anders Wallin
*  Header added
*
*  46    97-06-26 1.24 Anders Wallin
*  RTS 1.1.0
*
*  45    97-06-26 1.06 Anders Wallin
*  RTS 1.1.0
*
*  44    97-05-26 16.09 Anders Wallin
*  Version 1.01
*
*  43    97-04-28 15:43 Anders Öhlander
*  Change version to 1.0.0.
*
*  42    97-03-05 9.03 Anders Wallin
*  Version changed to 0.95
*
*  41    97-02-18 10.50 Anders Wallin
*  rts.h diveded to rts. and css.h
*
*  40    97-02-14 12:14 Anders Öhlander
*  Added MAGIC-WORD for the bootcode , MAGIC_WORD_BOOTCODE = AS-1200.
*
*  39    97-02-10 20.45 Anders Wallin
*  Changed version
*
*  38    97-01-28 17:58 Björn Elliott
*  Changed the name of mode switch setting according to spec.
*
*  37    97-01-28 17:37 Björn Elliott
*  Changed defines from BC_CHKSUM to DLU_CHKSUM according to documentation
*
*  36    97-01-21 19.15 Anders Wallin
*  New version 0910
*
*  35    97-01-14 15:43 Peter Koerner
*
*  34    97-01-09 10:01 Björn Elliott
*  Nothing done!!
*
*  33    97-01-08 17:18 Björn Elliott
*  Typed all LED_ defines to UINT16
*
*  32    96-12-18 12.31 Anders Wallin
*  Changed release no
*
*  31    96-12-16 21.24 Anders Wallin
*  Structure changed, ee-prom moved to bc_api.h
*
*  30    96-11-28 23.25 Anders Wallin
*  Changed version
*
*  29    96-11-26 20:47 Dev Pradhan
*  Added a service to the RTS jump table and added an address table for
*  the Dynamic Memory Manager
*
*  28    96-11-12 12.17 Anders Wallin
*  JUMP TABLE changed
*
*  27    96-11-08 11:09 Björn Elliott
*  added LED_MVB, LED_S_CO
*
*  26    96-11-07 15:43 Peter Koerner
*
*  25    15.10.96 14:53 Siegenthaler
*  16 Bit support added for basic types (INT8, INT16,...)
*  Used switch: O_16BIT
*  This is needed for PC based SW witch includes CSS API files.
*  E.g. Testprogram for TNM
*
*  24    96-10-09 13:37 Peter Koerner
*
*  23    96-10-09 13:29 Peter Koerner
*  extended for OS-functions
*
*  22    96-10-09 13.10 Anders Wallin
*
*  21    96-09-09 10:36 Peter Koerner
*  su modul added
*
*  20    96-09-02 18.32 Anders Wallin
*  Su component added
*
*  19    96-08-27 23.10 Anders Wallin
*
*  18    96-08-20 11.40 Anders Wallin
*  RESET_WATCHDOG added
*
*  17    96-08-18 22.40 Anders Wallin
*  JMP_TBL_BASE added
*
*  16    96-08-18 22.04 Anders Wallin
*  renamed os_sys.h to  rts.h
*
*  15    96-08-18 21.51 Anders Wallin
*  renamed ti rts.h
*
*  14    96-08-16 16.08 Anders Wallin
*
*  13    96-08-16 15.18 Anders Wallin
*
*  12    96-08-06 0.01 Anders Wallin
*  Mode switch changed to hardware mode switch and adresses to SE_LOG
*  added
*
*  11    96-08-02 9:53 Peter Koerner
*  SUBPROJECT_BC added
*
*  10    96-08-01 8.38 Anders Wallin
*  Subprojects changed to services
*
*  9     96-06-27 13.35 Anders Wallin
*  Hardware definitions added
*
*  8     96-06-19 13.45 Anders Wallin
*  IDLE MODE changed to LOCAL MODE
*
*  7     96-06-14 10.29 Anders Wallin
*  BOOT_MODE.. changed to RUN_MODE....
*
*  6     96-06-14 8.52 Anders Wallin
*  Reset reasons changed and api moved to os_api.h
*
*  5     96-06-10 16.13 Anders Wallin
*  os_def.h added
*
*  4     96-06-05 22.48 Anders Wallin
*  DWORD changed to unsigned int and OK and ERROR added
*
*  3     96-06-04 9.15 Anders Wallin
*  VCOS-dependencies removed
*
*  2     96-05-30 12.05 Anders Wallin
*  Header changed and VCOS changed to OS
*
*  1     96-05-10 16.01 Anders Wallin
*  Renamed from vcos_sys.h
*
******************************************************************************/

#ifndef  RTS_H
#define  RTS_H

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
*   INCLUDES
*/
#include "css.h"
#include "rts_dev.h"

/*****************************************************************************
*   DEFINES
*/

/* Version information */

#define SERVICE_NAME_RTS
#define RTS_VERSION     1
#define RTS_RELEASE     14
#define RTS_UPDATE      1


/*****************************************************************************
*   TYPEDEFS
*/

typedef enum
{
  SERVICE_STOPPED, SERVICE_STARTED, SERVICE_ERROR
} SERVICE_STATUS;

#ifdef __cplusplus
}
#endif

#endif /* RTS_H */
