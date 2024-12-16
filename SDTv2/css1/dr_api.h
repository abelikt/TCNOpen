/* $Header: /CSS/Code/RTS/COMMON/api/dr_api.h 21    03-08-14 10:14 Thomas Clevström $
******************************************************************************
*  COPYRIGHT    : (c) 1996 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : dr_api.h
*
*  ABSTRACT     : Data Recorder service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/dr_api.h $
*  
*  21    03-08-14 10:14 Thomas Clevström
*  Service version 2.1.0
*  
*  20    03-06-05 15:40 Christer Olsson
*  Added function dr_status_get
*  
*  19    02-11-15 4:44p Christer Olsson
*  Added API function dr_versions_get
*  
*  18    02-10-21 1:17p Christer Olsson
*  Moved the internal DR structures to dr_local.h
*  Changed dr_ext_trig_connect to dr_callback_connect
*  
*  17    02-09-23 3:24p Christer Olsson
*  Changed for new Data Recorder in CSS 1.11
*  
*  16    02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  15    99-03-30 8:03 Anders Öhlander
*  Change the version on DR to 1.0.
*  
*  14    99-03-10 10:47 Anders Öhlander
*  The file is updated from the MR 188 and others. See added doc in MR
*  188. There has been an request of added more commands to the DR , see
*  178.
*
*  13    98-08-10 14:37 Martin Gisbert
*  parameter dr_queue in callback function removed
*
*  12    98-07-01 15:48 Martin Gisbert
*
*  11    98-07-01 15:12 Martin Gisbert
*  dr_clear added
*
*  10    98-06-30 11:26 Martin Gisbert
*  minor change
*
*  9     98-06-30 7:50 Martin Gisbert
*  complete new DR design
*
*  8     97-06-27 9.23 Anders Wallin
*  Header added
*
*  7     96-12-18 12.16 Anders Wallin
*  minor changes
*
*  6     96-12-14 23.12 Anders Wallin
*
*  5     96-12-11 14:24 Dev Pradhan
*
*  4     96-12-02 7.28 Anders Wallin
*
*  3     96-11-26 21:35 Dev Pradhan
*  Updated after debugging and testing
*
*  2     96-10-10 7:34 Dev Pradhan
*  Updated as per Design Review comments
*
*  - changed all function, global variables, structures, etc to be in
*  lower case only and to start with dr_
*  - added the priority and over_write_flag to the Data Log Configuration
*  structure
*
*  1     96-09-30 8:43 Dev Pradhan
*  Version 1.0 of the Data Recorder
*
******************************************************************************/

#ifndef DR_API_H
#define DR_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/
#include "os_api.h"

/*****************************************************************************
*   DEFINES
*/
/* Define location for indirect call */
#define SERVICE_NAME_DR
#define     DR_VERSION          2
#define     DR_RELEASE          1
#define     DR_UPDATE           0
#define     DR_EVOLUTION        0

#ifndef     REAL32
#define     REAL32              float
#endif

/* values for signal status: */
#define     SIGNAL_DEFINED      1
#define     SIGNAL_NOT_DEFINED  0

/* values for signal type: */
/* If these values or some signals type are added the programmer must 
   change the test of the parameter in the function dr_signal_add.*/
#define     DR_UINT8            0
#define     DR_UINT16           1
#define     DR_UINT32           2
#define     DR_INT8             3
#define     DR_INT16            4
#define     DR_INT32            5
#define     DR_REAL32           6

/* values for trigger condition: */
/* If these values or some trigger condition are added the programmer must 
   change the test of the parameter in the function dr_signal_add.*/
#define     DR_NO_TRIGG         0
#define     DR_GREATER_THAN     1
#define     DR_LESS_THAN        2
#define     DR_EQUAL            3

/* values for trigger operator: */
/* If these values or some trigger operator are added the programmer must 
   change the test of the parameter in the function dr_signal_add.*/
#define     DR_OR               1
#define     DR_AND              2

/* values for read mode:        */
#define     DR_QUEUE_CONTINUE   0
#define     DR_QUEUE_HEAD       1
#define     DR_QUEUE_TAIL       2
#define     DR_QUEUE_TRIP_POINT 3

/* values for dr mode:          */
#define     DR_CONFIG_MODE      0
#define     DR_RECORDING_MODE   1
#define     DR_STOPPED_MODE     2
#define     DR_STOPPING_MODE    3

/* value for DR_INSTANCE_ENTRY.dr_id*/
#define     DR_INSTANCE_NOT_CREATED     0xFFFFFFFF

#define     DR_MEM_ERROR        0xFF

/* values for queue mode: */
#define     DR_EMPTY            0
#define     DR_RECORDING        1
#define     DR_TRIGGERED        2
#define     DR_TRIPPED          3

#define     TRIGGERED           0
#define     NOT_TRIGGERED       1

#define     DR_NO_RECOVER       0 
#define     DR_RECOVER          1 
#define     DR_RECOVER_RUN      2 

#define     DR_NO_CALLBACK         0 
#define     DR_CALL_IGNORE_TRIGG   1 
#define     DR_CALL_UNTIL_TRIGG    2 
#define     DR_CALL_ALWAYS         3 

/*****************************************************************************
*   TYPEDEFS
*/


typedef struct STR_INSTANCELIST_ITEM
{
    UINT32              dr_id;
    char                dr_name[16];
}INSTANCELIST_ITEM;


typedef struct dr_indirect_call_table
{
    VERSION_INFO dr_info;
    INT16         (*pdr_instance_create)(char*,        
                                         UINT8,        
                                         UINT16,        
                                         UINT8,        
                                         UINT8,        
                                         UINT32*);        

    INT16               (*pdr_configure)(UINT32,        
                                         UINT32,        
                                         UINT8,        
                                         UINT16,        
                                         UINT16,        
                                         UINT8);        


    INT16              (*pdr_signal_add)(UINT32,        
                                         char*,        
                                         void*,        
                                         UINT8,        
                                         UINT8,        
                                         UINT32,        
                                         UINT8,        
                                         UINT8,        
                                         UINT32,        
                                         UINT16*);        

    INT16           (*pdr_signal_delete)(UINT32,        
                                         UINT16);        


    INT16                   (*pdr_start)(UINT32);        

    INT16            (*pdr_sample_write)(UINT32);        

    INT16                    (*pdr_stop)(UINT32);        

    INT16             (*pdr_sample_read)(UINT32,          
                                         UINT16,          
                                         UINT8,          
                                         INT16,          
                                         UINT32*,          
                                         UINT32,
                                         UINT16*,          
                                         UINT8*);          

	INT16	      (*pdr_instance_delete)(UINT32);

    INT16                 (*pdr_trigger)(UINT32,          
                                         UINT16*);          

    INT16        (*pdr_callback_connect)(UINT32,          
								         INT32,
                                         UINT8 (* function) (void));          

    INT16                  (*pdr_id_get)(char*,
                                         UINT8*,          
                                         UINT32*);          

    INT16         (*pdr_instance_status)(UINT32,          
                                         char*,          
                                         UINT16*,          
                                         UINT8*,          
                                         UINT8*,          
                                         UINT16*,          
                                         UINT8*,          
                                         UINT8*,          
                                         UINT32*,          
                                         UINT8*,          
                                         UINT16*);          

    INT16            (*pdr_queue_status)(UINT32,          
                                         UINT16,          
                                         UINT16*,          
                                         UINT16*,          
                                         OS_STR_TIME_POSIX*);          

    INT16           (*pdr_signal_status)(UINT32,          
                                         UINT16,          
                                         char*,          
                                         void**,          
                                         UINT8*,          
                                         UINT8*,          
                                         UINT32*,          
                                         UINT8*,          
                                         UINT8*,          
                                         UINT32*);          

    INT16                   (*pdr_clear)(UINT32);          

    INT16  (*pdr_get_active_instance_nr)(UINT16*);

    INT16         (*pdr_getinstancelist)(INSTANCELIST_ITEM*);    

    INT16        (*pdr_memory_surrender)(UINT8);    

    INT16             (*pdr_memory_init)(UINT8*,    
                                         INT32,     
                                         INT32,     
                                         INT32,     
                                         UINT8*);    

    INT16            (*pdr_versions_get)(UINT8*,    
                                         AS_VERSION*,     
                                         AS_VERSION*);
       
    INT16              (*pdr_status_get)(SERVICE_STATUS*);

}  DR_STR_ICT;



/*****************************************************************************
*   GLOBALS
*/
/*****************************************************************************
*   GLOBAL FUNCTIONS
*/

extern INT16  dr_instance_create(char               dr_name[ ],
                                 UINT8              n_queues,
                                 UINT16             n_samples,
                                 UINT8              max_n_signals,
                                 UINT8              mem_id,
                                 UINT32*            dr_id);

extern INT16        dr_configure(UINT32             dr_id,
                                 UINT32             sample_rate,
                                 UINT8              priority,
								 UINT16             wdog_delay,
                                 UINT16             post_trig_samples,
                                 UINT8              circular_trig);

extern INT16       dr_signal_add(UINT32             dr_id,
                                 char               signal_name[ ],
                                 void*              p_signal_value,
                                 UINT8              signal_type,
                                 UINT8              trigger_condition_1,
                                 UINT32             trigger_value_1,
                                 UINT8              trigger_operator,
                                 UINT8              trigger_condition_2,
                                 UINT32             trigger_value_2,
                                 UINT16*            signal_index);

extern INT16    dr_signal_delete(UINT32             dr_id,
                                 UINT16             signal_index);

extern INT16            dr_start(UINT32             dr_id);

extern INT16     dr_sample_write(UINT32             dr_id);

extern INT16             dr_stop(UINT32             dr_id);

extern INT16      dr_sample_read(UINT32             dr_id,
                                 UINT16             dr_queue,
                                 UINT8              read_mode,
                                 INT16              n_samples_requested,
                                 UINT32*            buffer,
                                 UINT32             buffer_size,
                                 UINT16*            n_samples_returned,
                                 UINT8*             continue_overwritten);

extern INT16  dr_instance_delete(UINT32           dr_id);

extern INT16          dr_trigger(UINT32             dr_id,
                                 UINT16*            dr_queue);

extern INT16 dr_callback_connect(UINT32             dr_id,
								 INT32              callback_mode,
                                 UINT8              (*function)(void));

extern INT16           dr_id_get(char               dr_name[ ],
                                 UINT8*             mem_id,
                                 UINT32*            dr_id);

extern INT16  dr_instance_status(UINT32             dr_id,
                                 char*              dr_name,
                                 UINT16*            dr_mode,
                                 UINT8*             n_queues,
                                 UINT8*             n_tripped_queues,
                                 UINT16*            n_samples,
                                 UINT8*             max_n_signals,
                                 UINT8*             n_signals,
                                 UINT32*            sample_rate,
                                 UINT8*             priority,
                                 UINT16*            post_trig_samples );

extern INT16     dr_queue_status(UINT32             dr_id,
                                 UINT16             dr_queue,
                                 UINT16*            dr_queue_mode,
                                 UINT16*            n_samples,
                                 OS_STR_TIME_POSIX* trig_time);

extern INT16    dr_signal_status(UINT32             dr_id,
                                 UINT16             signal_index,
                                 char*              signal_name,
                                 void**             p_signal_value,
                                 UINT8*             signal_type,
                                 UINT8*             trigger_condition_1,
                                 UINT32*            trigger_value_1,
                                 UINT8*             trigger_operator,
                                 UINT8*             trigger_condition_2,
                                 UINT32*            trigger_value_2);

extern INT16            dr_clear(UINT32             dr_id);

extern INT16 dr_get_active_instance_nr(UINT16*      n_instances);

extern INT16  dr_getinstancelist(INSTANCELIST_ITEM* p_instance_list);

extern INT16 dr_memory_surrender(UINT8              mem_id);

extern INT16      dr_memory_init(UINT8*             p_mem_start,
                                 INT32              mem_size,
                                 INT32              max_n_instance,
                                 INT32              recover,
                                 UINT8*             mem_id);

extern INT16     dr_versions_get(UINT8*             p_mem_start,
                                 AS_VERSION*        dr_version,
                                 AS_VERSION*        mem_version);

extern INT16       dr_status_get(SERVICE_STATUS* status);

/* Define location for indirect call */
#define DR_IND_CALL     (*(DR_STR_ICT * *) DR_ADR_TABLE)

#ifdef O_DC
    #define os_dr_instance_create           dr_instance_create
    #define os_dr_configure                 dr_configure
    #define os_dr_signal_add                dr_signal_add
    #define os_dr_signal_delete             dr_signal_delete
    #define os_dr_start                     dr_start
    #define os_dr_sample_write              dr_sample_write
    #define os_dr_stop                      dr_stop
    #define os_dr_sample_read               dr_sample_read
	#define os_dr_instance_delete		    dr_instance_delete
    #define os_dr_trigger                   dr_trigger
    #define os_dr_callback_connect          dr_callback_connect
    #define os_dr_id_get                    dr_id_get
    #define os_dr_instance_status           dr_instance_status
    #define os_dr_queue_status              dr_queue_status
    #define os_dr_signal_status             dr_signal_status
    #define os_dr_clear                     dr_clear
    #define os_dr_get_active_instance_nr    dr_get_active_instance_nr
    #define os_dr_getinstancelist           dr_getinstancelist
    #define os_dr_memory_surrender          dr_memory_surrender
    #define os_dr_memory_init               dr_memory_init
    #define os_dr_versions_get              dr_versions_get
    #define os_dr_status_get                dr_status_get
#else
    #define os_dr_instance_create           (* (DR_IND_CALL->pdr_instance_create))
    #define os_dr_configure                 (* (DR_IND_CALL->pdr_configure))
    #define os_dr_signal_add                (* (DR_IND_CALL->pdr_signal_add))
    #define os_dr_signal_delete             (* (DR_IND_CALL->pdr_signal_delete))
    #define os_dr_start                     (* (DR_IND_CALL->pdr_start))
    #define os_dr_sample_write              (* (DR_IND_CALL->pdr_sample_write))
    #define os_dr_stop                      (* (DR_IND_CALL->pdr_stop))
    #define os_dr_sample_read               (* (DR_IND_CALL->pdr_sample_read))
    #define os_dr_instance_delete		    (* (DR_IND_CALL->pdr_instance_delete))
    #define os_dr_trigger                   (* (DR_IND_CALL->pdr_trigger))
    #define os_dr_callback_connect          (* (DR_IND_CALL->pdr_callback_connect))
    #define os_dr_id_get                    (* (DR_IND_CALL->pdr_id_get))
    #define os_dr_instance_status           (* (DR_IND_CALL->pdr_instance_status))
    #define os_dr_queue_status              (* (DR_IND_CALL->pdr_queue_status))
    #define os_dr_signal_status             (* (DR_IND_CALL->pdr_signal_status))
    #define os_dr_clear                     (* (DR_IND_CALL->pdr_clear))
    #define os_dr_get_active_instance_nr    (* (DR_IND_CALL->pdr_get_active_instance_nr))
    #define os_dr_getinstancelist           (* (DR_IND_CALL->pdr_getinstancelist))
    #define os_dr_memory_surrender          (* (DR_IND_CALL->pdr_memory_surrender))
    #define os_dr_memory_init               (* (DR_IND_CALL->pdr_memory_init))
    #define os_dr_versions_get              (* (DR_IND_CALL->pdr_versions_get))
    #define os_dr_status_get                (* (DR_IND_CALL->pdr_status_get))
#endif

#ifdef __cplusplus
}
#endif

#endif /* DR_API_H */
