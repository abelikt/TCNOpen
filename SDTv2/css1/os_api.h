/* $Header: /CSS/Code/RTS/COMMON/api/os_api.h 39    02-10-24 14:20 Thomas Clevström $
******************************************************************************
*  COPYRIGHT    : (c) 1996 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : os_api.h
*
*  ABSTRACT     : Real Time service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/os_api.h $
*  
*  39    02-10-24 14:20 Thomas Clevström
*  Service version 1.2
*  
*  38    02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  37    01-10-17 9:52 Niclas Ericsson
*  Added os_mvbc_xxx functions, ER-000866ORI:3.
*  
*  36    01-04-06 16:34 Thomas Clevström
*  Added Reset reasons, from DEVICE/XXX/api/rts_xxx.h
*  NCR -LARS HÖGBERG10007.
*  Incremented VERSION to 1.1.0
*  
*  35    01-04-05 8:28 Lars Högberg
*  Added hi_xx functions, NCR -LARS HÖGBERG10007.
*  
*  34    99-06-28 15:47 Anders Öhlander
*  Update OS_ version to 1.0.1.
*  
*  33    98-11-02 16:06 Anders Öhlander
*  Change the struct TIMEDATE48 to OS_STR_TIMEDATE. SESIG has problem to
*  buikd the system with the old name.
*
*  32    98-06-16 10:04 Anders Öhlander
*  Change the timedate48 prototype.
*
*  31    98-05-29 12:41 Anders Öhlander
*  OS_IO functions are moved to the ANSI-api files, see MR 126. The
*  structures TIMEDATE-48 and converions functions are added , see MR 147.
*
*  30    98-01-07 11:05 Anders Wallin
*  os_t_name interface changed
*
*  29    98-01-07 10:31 Anders Wallin
*  os_t_name interface changed
*
*  28    97-12-09 15:09 Anders Wallin
*  os_t_name changed
*
*  27    97-12-09 11:43 Anders Wallin
*  os_t_name added
*
*  26    97-12-02 13:28 Anders Wallin
*  os_ack_queues removed (MR 55)
*
*  25    97-12-01 9:04 Anders Wallin
*  OS_IO_NULL added (MR130)
*
*  24    97-08-09 22.24 Anders Wallin
*   MR 91: os_hi_halt and os_hi_shutdown pointers corrected
*
*  22    97-06-27 9.23 Anders Wallin
*  Header added
*
*  21    97-05-22 13.15 Anders Wallin
*  return arg for scanf,printf,fscanf,fprintf changed to int32
*
*  20    97-05-20 14.54 Anders Wallin
*  os_io_fp_to_fd and os_errno added
*
*  19    97-05-15 14:29 Anders Öhlander
*  Removed prototypes for os_io_kbhit and added prototypes for
*  os_io_fp_to_fd.
*
*  18    97-04-25 7:28 Anders Öhlander
*  Added os_io_kbhit() prototyp and OS_IO_DEVICE_DELETE definition.
*
*  17    97-04-08 15.00 Anders Wallin
*  ee moved to the new service ee
*
*  16    97-01-07 11.55 Anders Wallin
*  OS_IO_HW_OPTION_GET removed
*
*  15    96-12-19 10:24 Peter Koerner
*  os_t_lock() and os_t_unlock() removed
*
*  14    96-12-18 21.07 Anders Wallin
*  OS_IO_COMx added and OS_IO_STD... removed
*
*  13    96-12-18 20.59 Anders Wallin
*  OS_IO_HW_OPTION_SET/GET added
*
*  12    96-12-17 12.57 Anders Wallin
*  ee-functions changed
*
*  11    96-12-14 23.06 Anders Wallin
*  Formatted io changed
*
*  10    96-12-12 14.17 Anders Wallin
*  Change the size of task_id from 16 to 32 bit
*
*  9     96-12-10 22:23 Dev Pradhan
*  stdio.h removed
*
*  8     96-12-08 17:45 Dev Pradhan
*  Added the following functions to the ICT
*  - os_io_printf
*  - os_io_scanf
*  - os_io_fopen
*  - os_io_fclose
*  - os_io_fprintf
*  - os_io_fscanf
*
*  7     96-12-03 18.31 Anders Wallin
*  IO-defines added
*
*  6     96-12-03 0.12 Anders Wallin
*  os_t_id_get removed
*
*  5     96-12-02 23.31 Anders Wallin
*  added io and halt and shutdown
*
*  4     96-12-02 7.31 Anders Wallin
*  C++ support added
*
*  3     96-11-28 23:00 Peter Koerner
*
*  2     96-11-25 15:14 Peter Koerner
*
*  1     96-11-07 15:41 Peter Koerner
*
******************************************************************************/

#ifndef OS_API_H
#define OS_API_H

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
*   DEFINES
*/


#define SERVICE_NAME_OS
#define OS_VERSION      1
#define OS_RELEASE      2
#define OS_UPDATE       0
#define OS_EVOLUTION    0


/* semaphores */
#define OS_SEM_Q_FIFO   		0x0	    /* first in first out queue     */
#define OS_SEM_Q_PRIORITY		0x1	    /* priority sorted queue        */
#define OS_SEM_DELETE_SAFE      0x4
#define OS_SEM_INVERSION_SAFE   0x8
#define OS_SEM_EMPTY            0x0
#define OS_SEM_FULL             0x1

/* message queues */
#define OS_MSG_Q_FIFO       	0x0	    /* tasks wait in FIFO order     */
#define OS_MSG_Q_PRIORITY    	0x1	    /* tasks wait in PRIORITY order */
#define OS_MSG_PRI_NORMAL       0x0	    /* normal priority message      */
#define OS_MSG_PRI_URGENT       0x1     /* urgent priority message      */

/* general */
#define OS_NO_WAIT	             0
#define OS_WAIT_FOREVER	       (-1)


/* RESET REASONS */
/* ============= */
#define  HI_POWER_UP                RESET_POWER_UP
#define  HI_PROG_START              RESET_RUN
#define  HI_PROG_STOP               RESET_IDLE
#define  HI_DOWNLOAD                RESET_DOWNLOAD
#define  HI_DOWNLOAD_HAMSTER        RESET_ERROR_STDL
#define  HI_SIMON                   RESET_TEST
#define  HI_HAMSTER_RESET           RESET_ERROR


/*****************************************************************************
*   TYPEDEFS
*/

/* ------------------ */
/*   for semaphores   */
/* ------------------ */

typedef enum	     	/* SEM_STATE */
{
    EMPTY,              /* 0: semaphore not available */
    FULL                /* 1: semaphore     available */
} OS_SEM_B_STATE;

/* ---------------------- */
/*   for time functions   */
/* ---------------------- */

typedef struct posix_time
{
    					/* interval = sec*10**9 + nanosec */
  UINT32 sec;			/* seconds     */
  UINT32 nanosec;		/* nanoseconds */

} OS_STR_TIME_POSIX;


typedef struct ansi_time
{
	INT32 tm_sec;	    /* seconds after the minute	- [0, 61] */
	INT32 tm_min;	    /* minutes after the hour	- [0, 59] */
	INT32 tm_hour;	    /* hours after midnight		- [0, 23] */
   	INT32 tm_mday;  	/* day of the month		    - [1, 31] */
	INT32 tm_mon;	    /* months since January		- [0, 11] */
	INT32 tm_year;	    /* years since 1900	                  */
	INT32 tm_wday;  	/* days since Sunday		- [0, 6]  */
	INT32 tm_yday;	    /* days since January 1		- [0, 365]*/
	INT32 tm_isdst;	    /* Daylight Saving Time flag */

} OS_STR_TIME_ANSI;

typedef struct OS_STR_TIMEDATE48
{
    UINT32 seconds;
    UINT16 ticks;
} OS_TIMEDATE48;

/* ----------------------- */
/*   indirect call table   */
/* ----------------------- */

typedef struct os_indirect_call_table
{
    VERSION_INFO  os_info;

    INT16 ( *pos_t_spawn                 ) ( char     appl_name[],
                                             INT32    appl_type,
                                             char     task_name[],
                                             UINT8    priority,
                                             INT32    stack_size,
                                             FUNCPTR  entry_pt,
                                             INT32    argc,
                                             INT32    argv[],
                                             UINT32*  task_id          );
    INT16 ( *pos_t_delay                 ) ( UINT32   delay_time_ms    );
    INT16 ( *pos_t_event_raise           ) ( char     task_name[]      );
    INT16 ( *pos_t_event_wait            ) ( VOID                      );
    INT16 ( *pos_t_delete                ) ( void                      );
    void  ( *pos_t_name                  ) ( char*    task_name[]      );

    INT16 ( *pos_c_res_get               ) ( INT32*   p_res_ms,
                                             INT32*   p_ticks_per_sec  );

    INT16 ( *pos_c_get                   ) ( OS_STR_TIME_POSIX* p_time );
    INT16 ( *pos_c_set                   ) ( OS_STR_TIME_POSIX* p_time );
    INT16 ( *pos_c_localtime             ) ( UINT32             input_sec,
                                             OS_STR_TIME_ANSI*  p_output_ANSI_time );
    INT16 ( *pos_c_mktime                ) ( OS_STR_TIME_ANSI*  p_input_ANSI_time,
                                             UINT32*  output_sec       );
    INT16 ( *pos_i_disable               ) ( INT32*   p_lock_key       );
    INT16 ( *pos_i_enable                ) ( INT32    lock_key         );
    INT16 ( *pos_sb_create               ) ( INT32    options,
                                             OS_SEM_B_STATE     ini_state,
                                             INT32*   p_id               );
    INT16 ( *pos_sm_create               ) ( INT32    options,
                                             INT32*   p_id               );
    INT16 ( *pos_s_take                  ) ( INT32    sem_id,
                                             INT32    time_out         );
    INT16 ( *pos_s_give                  ) ( INT32    sem_id           );
    INT16 ( *pos_s_delete                ) ( INT32    sem_id           );
    INT16 ( *pos_q_create                ) ( INT32    max_msgs,
                                             INT32    max_msg_length,
                                             INT32    options,
                                             INT32*   p_msg_q_id       );
    INT16 ( *pos_q_send                  ) ( INT32    msg_q_id,
                                             INT8*    p_buffer,
                                             UINT32   n_bytes,
                                             INT32    time_out,
                                             INT32    priority         );
    INT16 ( *pos_q_receive               ) ( INT32    msg_q_id,
                                             INT8*    p_buffer,
                                             UINT     max_n_bytes,
                                             INT32    time_out,
                                             INT32*   p_rcv_size       );
    INT16 ( *pos_q_delete                ) ( INT32    msg_q_id         );

    void  ( *pos_hi_reset                ) ( void                      );
    void  ( *pos_hi_halt                 ) ( void                      );
    void  ( *pos_hi_shutdown             ) ( UINT16   restart_mode     );

	INT16 ( *pos_timedate_48_clock_get   ) ( OS_TIMEDATE48* p_timedate48);
	INT16 ( *pos_timedate_48_clock_set   ) ( OS_TIMEDATE48 timedate48);

    ULONG ( *pos_hi_flash_base_get       ) ( void );
    ULONG ( *pos_hi_flash_size_get       ) ( void );
    UINT16( *pos_hi_reset_reason_get     ) ( void );
    void  ( *pos_hi_stall_set            ) ( BOOL );

    INT16 ( *pos_mvbc_state              ) ( UINT8 mvb_bus_id );
    INT16 ( *pos_mvbc_reset              ) ( UINT8 mvb_bus_id, UINT32* no_of_resets );

} OS_STR_ICT;

/*****************************************************************************
*   FUNCTIONS PROTOTYPES
*
*/
extern UINT16   os_hi_reset_reason_get( void );
extern ULONG    os_hi_flash_base_get( void );
extern ULONG    os_hi_flash_size_get( void );
extern void     os_hi_stall_set(  BOOL activate );

extern INT16    os_mvbc_state( UINT8 mvb_bus_id );
extern INT16    os_mvbc_reset( UINT8 mvb_bus_id, UINT32* no_of_resets );

/* Define location for indirect call */
#define OS_IND_CALL     (*(OS_STR_ICT * *) OS_ADR_TABLE)

/* --------------- */
/*   direct call   */
/* --------------- */

#ifdef O_DC

    /* application access via direct call */

    INT16   os_t_spawn                ( char     appl_name[],
                                        INT32    appl_type,
                                        char     task_name[],
                                        UINT8    priority,
                                        INT32    stack_size,
                                        FUNCPTR  entry_pt,
                                        INT32    argc,
                                        INT32    argv[],
                                        UINT32*  task_id          );
    INT16   os_t_delay                ( UINT32   delay_time_ms    );
    INT16   os_t_event_raise          ( char     task_name[]      );
    INT16   os_t_event_wait           ( VOID                      );
    INT16   os_t_delete               ( void                      );
    void    os_t_name                 ( char*    task_name[]      );

    INT16   os_c_res_get              ( INT32*   p_res_ms,
                                        INT32*   p_ticks_per_sec  );
    INT16   os_c_get                  ( OS_STR_TIME_POSIX* p_time );
    INT16   os_c_set                  ( OS_STR_TIME_POSIX* p_time );
    INT16   os_c_localtime            ( UINT32             input_sec,
                                        OS_STR_TIME_ANSI*  p_output_ANSI_time );
    INT16   os_c_mktime               ( OS_STR_TIME_ANSI*  p_input_ANSI_time,
                                        UINT32*            p_output_sec       );

    INT16   os_i_disable              ( INT32*   p_lock_key       );
    INT16   os_i_enable               ( INT32    lock_key         );

    INT16   os_sb_create              ( INT32              options,
                                        OS_SEM_B_STATE     init_state,
                                        INT32*             p_sem_id           );
    INT16   os_sm_create              ( INT32              options,
                                        INT32*             p_sem_id           );
    INT16   os_s_take                 ( INT32    sem_id,
                                        INT32    time_out         );
    INT16   os_s_give                 ( INT32    sem_id           );
    INT16   os_s_delete               ( INT32    sem_id           );

    INT16   os_q_create               ( INT32    max_msgs,
                                        INT32    max_msg_length,
                                        INT32    options,
                                        INT32*   p_msg_q_id       );
    INT16   os_q_send                 ( INT32    msg_q_id,
                                        INT8*    p_buffer,
                                        UINT32   n_bytes,
                                        INT32    time_out,
                                        INT32    priority         );
    INT16   os_q_receive              ( INT32    msg_q_id,
                                        INT8*    p_buffer,
                                        UINT     max_n_bytes,
                                        INT32    time_out,
                                        INT32*   p_rcv_size       );
    INT16   os_q_delete               ( INT32    msg_q_id         );

    void    os_hi_reset               ( void                      );
    void    os_hi_halt                ( void                      );
    void    os_hi_shutdown            ( UINT16   restart_mode     );

	INT16 	os_timedate_48_clock_get  ( OS_TIMEDATE48* p_timedate48);
	INT16 	os_timedate_48_clock_set  ( OS_TIMEDATE48 timedate48);

#ifndef BC_API_H
  #define hi_flash_base_get           os_hi_flash_base_get
  #define hi_flash_size_get           os_hi_flash_size_get
  #define hi_reset_reason_get         os_hi_reset_reason_get
  #define hi_stall_set                os_hi_stall_set
#endif /* BC_API_H */

    INT16   os_mvbc_state             ( UINT8 mvb_bus_id );
    INT16   os_mvbc_reset             ( UINT8 mvb_bus_id, UINT32* no_of_resets );


#else

    /* ----------------- */
    /*   indirect call   */
    /* ----------------- */

    #define os_t_spawn                 (* (OS_IND_CALL->pos_t_spawn                ))
    #define os_t_delay                 (* (OS_IND_CALL->pos_t_delay                ))
    #define os_t_event_raise           (* (OS_IND_CALL->pos_t_event_raise          ))
    #define os_t_event_wait            (* (OS_IND_CALL->pos_t_event_wait           ))
    #define os_t_delete                (* (OS_IND_CALL->pos_t_delete               ))
    #define os_t_name                  (* (OS_IND_CALL->pos_t_name                 ))
    #define os_c_res_get               (* (OS_IND_CALL->pos_c_res_get              ))
    #define os_c_get                   (* (OS_IND_CALL->pos_c_get                  ))
    #define os_c_set                   (* (OS_IND_CALL->pos_c_set                  ))
    #define os_c_localtime             (* (OS_IND_CALL->pos_c_localtime            ))
    #define os_c_mktime                (* (OS_IND_CALL->pos_c_mktime               ))
    #define os_i_disable               (* (OS_IND_CALL->pos_i_disable              ))
    #define os_i_enable                (* (OS_IND_CALL->pos_i_enable               ))
    #define os_sb_create               (* (OS_IND_CALL->pos_sb_create              ))
    #define os_sm_create               (* (OS_IND_CALL->pos_sm_create              ))
    #define os_s_take                  (* (OS_IND_CALL->pos_s_take                 ))
    #define os_s_give                  (* (OS_IND_CALL->pos_s_give                 ))
    #define os_s_delete                (* (OS_IND_CALL->pos_s_delete               ))
    #define os_q_create                (* (OS_IND_CALL->pos_q_create               ))
    #define os_q_send                  (* (OS_IND_CALL->pos_q_send                 ))
    #define os_q_receive               (* (OS_IND_CALL->pos_q_receive              ))
    #define os_q_delete                (* (OS_IND_CALL->pos_q_delete               ))
    #define os_hi_reset                (* (OS_IND_CALL->pos_hi_reset               ))
    #define os_hi_halt                 (* (OS_IND_CALL->pos_hi_halt                ))
    #define os_hi_shutdown             (* (OS_IND_CALL->pos_hi_shutdown            ))
    #define os_timedate_48_clock_get   (* (OS_IND_CALL->pos_timedate_48_clock_get  ))
    #define os_timedate_48_clock_set   (* (OS_IND_CALL->pos_timedate_48_clock_set  ))
#ifndef BC_API_H
    #define hi_flash_base_get          (* (OS_IND_CALL->pos_hi_flash_base_get      ))
    #define hi_flash_size_get          (* (OS_IND_CALL->pos_hi_flash_size_get      ))
    #define hi_reset_reason_get        (* (OS_IND_CALL->pos_hi_reset_reason_get    )) 
    #define hi_stall_set               (* (OS_IND_CALL->pos_hi_stall_set           ))
#endif /* BC_API_H */
    #define os_mvbc_state              (* (OS_IND_CALL->pos_mvbc_state             ))
    #define os_mvbc_reset              (* (OS_IND_CALL->pos_mvbc_reset             ))

#endif

#ifdef __cplusplus
}
#endif

#endif /* OS_API_H */

