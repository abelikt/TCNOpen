/* $Header: /CSS/Code/RTS/COMMON/api/ts_api.h 5     02-09-18 9:37 Thomas Clevström $
******************************************************************************
*  COPYRIGHT      : (c) 1999 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT        : CSS
*
*  MODULE         : ts_api.h
*
*  ABSTRACT       : Time Synchronization Service
*
******************************************************************************
*  HISTORY        :
*   $Log: /CSS/Code/RTS/COMMON/api/ts_api.h $
*  
*  5     02-09-18 9:37 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  4     00-12-06 20:50 Lars Högberg
*  Updated service version
*  
*  3     00-07-21 12:47 Martin Gisbert
*  ts-bugifx: ICT modified, ts_connect added
*  
*  2     99-12-14 10:51 Lars Högberg
*  Updated service version
*  
*  1     99-06-29 16:52 Anders Öhlander
*  First version.
*  
*
******************************************************************************/


#ifndef TS_API_H
#define TS_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/

/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_TIME_SYNC
#define TIME_SYNC_VERSION      1
#define TIME_SYNC_RELEASE      0
#define TIME_SYNC_UPDATE       1
#define TIME_SYNC_EVOLUTION    0

#define TS_NONE                0

#define TS_MASTER_NOT_SYNCH 10
#define TS_MASTER_SYNCH     11

#define TS_SLAVE_NOT_SYNCH  20
#define TS_SLAVE_SYNCH      21

#define TS_MASTER_PRIORITY  38
#define TS_SLAVE_PRIORITY   38

#define TS_STORES_MAX        1
#define TS_PORT_CYCLE        1024  /* ms */  


#define TS_VERSION           1
#define TS_RELEASE           0

#define AS_TS_NONE           0
#define AS_TS_MASTER         1
#define AS_TS_SLAVE          2

#define AS_TIME_SYNC_NONE    0     /* type */
#define AS_TIME_SYNC_MASTER  1     /* type */
#define AS_TIME_SYNC_SLAVE   2     /* type */

#define AS_TIME_SYNC_LOCAL   0     /* time_source */
#define AS_TIME_SYNC_RTC     1     /* time_source */
#define AS_TIME_SYNC_API     2     /* time_source */

/*****************************************************************************
*   TYPEDEFS
*/
typedef struct
{
    VERSION_INFO  ts_info;
    INT16 ( *ptime_sync_set )   ( OS_TIMEDATE48  , INT8 , INT16 , INT16 );
    INT16 ( *ptime_sync_get )   ( OS_TIMEDATE48* , OS_TIMEDATE48* , OS_TIMEDATE48* , INT8* , INT16* , INT16* );
} TS_STR_ICT;


/*****************************************************************************
*   GLOBAL FUNCTIONS
*/
INT16 time_sync_set(  OS_TIMEDATE48     offset_time, 
                      INT8              offset_sign, 
                      INT16             time_zone, 
                      INT16             daylight);

INT16 time_sync_get(  OS_TIMEDATE48*    sync_UTC_time, 
                      OS_TIMEDATE48*    sync_zone_time, 
                      OS_TIMEDATE48*    offset_time, 
                      INT8*             offset_sign, 
                      INT16*            time_zone, 
                      INT16*            daylight);

/* Define location for indirect call */
#define TS_IND_CALL     (*(TS_STR_ICT * *) TS_ADR_TABLE)

#ifdef O_DC
    #define os_time_sync_set            time_sync_set
    #define os_time_sync_get            time_sync_get
#else
    #define os_time_sync_set            (* (TS_IND_CALL->ptime_sync_set))
    #define os_time_sync_get            (* (TS_IND_CALL->ptime_sync_get))
#endif

#ifdef __cplusplus
}
#endif


#endif /* PS_API_H */

