/* $Header: /CSS/Code/RTS/COMMON/api/mon_api.h 36    07-03-15 17:38 Bjarne Jensen $
******************************************************************************
*  COPYRIGHT    : (c) 1996 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : mon_api.h
*
*  ABSTRACT     : RTS Monitor service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/mon_api.h $
*  
*  36    07-03-15 17:38 Bjarne Jensen
*  Bumped the release number to 11 (was 10)
*  
*  35    06-06-15 11:39 Jrehnman
*  Service version 1.10.3
*  
*  34    06-06-14 12:38 Jrehnman
*  Service Version 1.10.2. due to fix in Central Monitor
*  
*  33    04-05-07 13:42 Christer Olsson
*  Service version 1.10.1. due to fix in Central Monitor
*  
*  32    03-08-14 10:20 Thomas Clevström
*  Service version 1.10.0. due to new DR command
*  
*  31    02-10-24 14:17 Thomas Clevström
*  Service version 1.9 due to new DR commands
*  
*  30    02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  29    02-02-12 13:59 Thomas Clevström
*  CA-Monitor
*  
*  28    01-04-06 11:06 Thomas Clevström
*  Eliminated type conflics MON_FILE=OS_IO_FILE
*  
*  27    01-02-26 16:45 Thomas Clevström
*  Update RTS_MON version to 1.7:
*  SPR 00-384 Command line editor in RTS-mon
*  
*  26    99-12-10 17:15 Lars Högberg
*  Update RTS_MON version to 1.6.
*  
*  25    99-06-28 15:40 Anders Öhlander
*  Update RTS_MON version to 1.5.
*  
*  24    98-10-08 18:10 Anders Öhlander
*  The monitor version is updated to 1.4.0, see MR 161.
*
*  23    98-09-23 14:48 Anders Öhlander
*  Update the version to 1.3 of the RTS-monitor , see MR 156.
*
*  22    98-05-29 12:30 Anders Öhlander
*  Update the version to 1.2.0 because of the new "md -w x:y -c" command,
*  see MR 129.
*
*  21    97-08-14 15.43 Anders Wallin
*  Version changed from 1.0 to 1.1
*
*  20    97-06-27 9.23 Anders Wallin
*  Header added
*
*  19    97-05-20 14.57 Anders Wallin
*  mon_cmd_add interface changed
*
*  18    97-04-28 15:43 Anders Öhlander
*  Change version to 1.0.0.
*
*  17    97-01-09 15.39 Anders Wallin
*
*  16    97-01-06 20:34 Alexander Lalosevic
*  - Minor changes
*
*  15    96-12-09 19.44 Anders Wallin
*
*  14    96-12-09 17:30 Alexander Lalosevic
*  - HELP command implemented
*  - RESET command implemented
*
*  13    96-12-05 22:09 Alexander Lalosevic
*  - const added to typedefs for help syntaxes
*
*  12    96-12-04 15:40 Alexander Lalosevic
*  - Channel changed to /TyCo/1
*  - FILE* changed to MON_FILE*
*
*  11    96-12-03 19.16 Anders Wallin
*  FILE changed to MON_FILE
*
*  10    96-12-03 14:05 Alexander Lalosevic
*  - short_name and long_name in mon_cmd_add() changed to const.
*  - pointer names changed according to coding conventions (p_...).
*  - optional switch for debugg info (o_mon) uncommented.
*  - a rough login and logout command implemented.
*
*  9     96-12-02 15:50 Alexander Lalosevic
*  - mon_init routine changed to using mon_cmd_add routine.
*  - se_log functionality inserted.
*  - mon_cmd_add updated (bugg fix).
*
*  8     96-12-02 7.29 Anders Wallin
*  C++ support added
*
*  7     96-11-29 16:12 Alexander Lalosevic
*  Version 0.6 Beta
*
*  6     96-11-29 14.11 Anders Wallin
*  dm_init takes void-argument
*
*  5     96-11-29 13:35 Alexander Lalosevic
*  Updated
*
*  3     96-11-21 18:18 Alexander Lalosevic
*  Updated. Typedefs and defines added.
*
*  2     96-11-21 16:23 Alexander Lalosevic
*  First draft
*
******************************************************************************/

#ifndef  MON_API_H
#define  MON_API_H

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
*   INCLUDES
*/

#include "ansi_api.h"

/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_MON
#define MON_VERSION      1
#define MON_RELEASE      11
#define MON_UPDATE       0
#define MON_EVOLUTION    0

/* Command store defines for the Monitor */

#define MON_MIN_NAME             1  /* Minimum nr of chars in short_ and long_name */
#define MON_MAX_LONG_NAME       15  /* Maximum nr of chars in long_name            */
#define MON_MAX_SHORT_NAME      10  /* Maximum nr of chars in short_name           */

#define MON_MAX_NR_OF_ARGC      10  /* Maximum nr of arguments to a command  */


/*****************************************************************************
*   TYPEDEFS
*/

typedef OS_IO_FILE MON_FILE;

typedef void (*MONFUNCPTR)( MON_FILE*  fp_channel,
                            INT16      argc,
                            char*      argv_p[MON_MAX_NR_OF_ARGC] );

typedef struct
{
    VERSION_INFO  mon_info;
    INT16         ( *pmon_cmd_add)       ( const char*, const char*, MONFUNCPTR,
                                           const char*, const char*, BOOL);
    INT16         ( *pmon_cmd_del)       ( const char* );
} MON_STR_ICT;


/*****************************************************************************
*   GLOBAL FUNCTIONS
*/
INT16 mon_cmd_add( const char   long_name[MON_MAX_LONG_NAME],
                   const char   short_name[MON_MAX_SHORT_NAME],
                   MONFUNCPTR   p_mon_func,
                   const char   long_help[],
                   const char   short_help[],
                   BOOL         password_protected);

INT16 mon_cmd_del( const char short_name[MON_MAX_SHORT_NAME] );


/* Define location for indirect call */
#define MON_IND_CALL     (*(MON_STR_ICT * *) MON_ADR_TABLE)


#ifdef O_DC
    #define os_mon_cmd_add       mon_cmd_add
    #define os_mon_cmd_del       mon_cmd_del
#else
    #define os_mon_cmd_add       (* (MON_IND_CALL->pmon_cmd_add))
    #define os_mon_cmd_del       (* (MON_IND_CALL->pmon_cmd_del))
#endif


#ifdef __cplusplus
}
#endif


#endif /* MON_API_H */
