/* $Header: /CSS/Code/RTS/COMMON/api/ps_api.h 21    02-10-24 14:19 Thomas Clevström $
******************************************************************************
*  COPYRIGHT      : (c) 1995 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT        : CSS
*
*  MODULE         : ps_api.h
*
*  ABSTRACT       : Periodic Scheduler service
*
******************************************************************************
*  HISTORY        :
*   $Log: /CSS/Code/RTS/COMMON/api/ps_api.h $
*  
*  21    02-10-24 14:19 Thomas Clevström
*  Service version 1.2
*  
*  20    02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  19    00-12-06 20:47 Lars Högberg
*  Updated service version
*  
*  18    00-10-30 11:33 Lars Högberg
*  Added a new API-function (time since last execution), NCR -LARS
*  HÖGBERG00009
*  
*  17    97-06-27 9.23 Anders Wallin
*  Header added
*
*  16    96-12-02 12.26 Anders Wallin
*
*  15    96-12-02 7.32 Anders Wallin
*  C++ support added
*
*  14    96-11-22 16.21 Anders Wallin
*  ps_cycles_get and ps_cycle_time_get added
*
*  13    96-10-28 15.39 Anders Wallin
*  task_id removed from ps_add
*  ps_delete changed
*
*  12    96-09-09 11.12 Anders Wallin
*
*  11    96-09-02 18.32 Anders Wallin
*  Su component added
*
*  10    96-08-30 16.24 Anders Wallin
*
*  9     96-08-27 23.10 Anders Wallin
*
*  8     96-08-22 11.24 Anders Wallin
*
*  7     96-08-22 8:07 Björn Elliott
*  Removed ps_status_get()
*
*  6     96-08-16 16.08 Anders Wallin
*
*  5     96-08-08 8:37 Björn Elliott
*
*  4     96-08-08 8:30 Björn Elliott
*
*  3     96-08-07 17:03 Björn Elliott
*
*  2     96-08-01 16:53 Björn Elliott
*  Changes due to lint
*
*  1     96-07-17 9:15 Björn Elliott
*  Periodic Scheduling  API header file
*
******************************************************************************/


#ifndef PS_API_H
#define PS_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/

/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_PS
#define PS_VERSION      1
#define PS_RELEASE      2
#define PS_UPDATE       0
#define PS_EVOLUTION    0

/*****************************************************************************
*   TYPEDEFS
*/
typedef struct
{
    VERSION_INFO  ps_info;
    INT16         ( *pps_add)            			( UINT32, UINT32, UINT16, UINT16* );
    INT16         ( *pps_wait)           			( UINT16 );
    INT16         ( *pps_delete)         			( UINT16 );
    void          ( *pps_cycles_get)    			( UINT32* );
    void          ( *pps_cycle_time_get) 			( UINT16* );
	INT16		  ( *pps_time_since_last_execution)	( UINT32* );
} PS_STR_ICT;


/*****************************************************************************
*   GLOBAL FUNCTIONS
*/
INT16 ps_add(               		UINT32  cycle_time,
                            		UINT32  delay_time,
                            		UINT16  wdog_delay,
                            		UINT16* p_timer_index );

INT16 ps_wait(              		UINT16  timer_index );

INT16 ps_delete(            		UINT16  timer_index );
void  ps_cycles_get(        		UINT32* activation_count );
void  ps_cycle_time_get(    		UINT16* cycle_time );
INT16 ps_time_since_last_execution(	UINT32* cycle_time );

/* Define location for indirect call */
#define PS_IND_CALL     (*(PS_STR_ICT * *) PS_ADR_TABLE)

#ifdef O_DC
    #define os_ps_add            			ps_add
    #define os_ps_wait           			ps_wait
    #define os_ps_delete         			ps_delete
    #define os_ps_cycles_get     			ps_cycles_get
    #define os_ps_cycle_time_get 			ps_cycle_time_get
	#define os_ps_time_since_last_execution	ps_time_since_last_execution
#else
    #define os_ps_add            			(* (PS_IND_CALL->pps_add))
    #define os_ps_wait           			(* (PS_IND_CALL->pps_wait))
    #define os_ps_delete         			(* (PS_IND_CALL->pps_delete))
    #define os_ps_cycles_get     			(* (PS_IND_CALL->pps_cycles_get))
    #define os_ps_cycle_time_get 			(* (PS_IND_CALL->pps_cycle_time_get))
	#define os_ps_time_since_last_execution	(* (PS_IND_CALL->pps_time_since_last_execution))
#endif

#ifdef __cplusplus
}
#endif


#endif /* PS_API_H */

