/* $Header: /CSS/Code/RTS/COMMON/api/pi_api.h 4     02-09-17 17:44 Thomas Clevström $
******************************************************************************
*  COPYRIGHT      : (c) 1997 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT        : CSS
*
*  MODULE         : pi_api.h
*
*  ABSTRACT       : PIL service
*
******************************************************************************
*  HISTORY        :
*   $Log: /CSS/Code/RTS/COMMON/api/pi_api.h $
*  
*  4     02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  3     98-12-17 11:28 Anders Öhlander
*  pi_alloc and pi_free is added see SPR 154.
*
*  2     97-09-10 16:01 Anders Wallin
*  PIL update
*
*  1     97-09-10 9:09 Anders Wallin
*  added
*
******************************************************************************/


#ifndef PI_API_H
#define PI_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/

/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_PI
#define PI_VERSION  1
#define PI_RELEASE  0

/* BASE data types */
#ifndef INT16
    #define INT16           short
#endif
#ifndef UINT16
    #define UINT16          unsigned short
#endif
#ifndef INT32
    #define INT32           int
#endif
#ifndef UINT32
    #define UINT32          unsigned int
#endif

/* error definitions */
#define PI_RET_OK   0x0000   /* success */
#define PI_ERR_MM   0x0001   /* no memory available */
#define PI_ERR_NM   0x0002   /* no message available */
#define PI_ERR_ID   0x0003   /* wrong resource ID */
#define PI_ERR_TO   0x0004   /* timeout error */
#define PI_ERR_FB   0x0005   /* message queue buffer full */
#define PI_ERR_NC   0x0006   /* no control block available */
#define PI_ERR_OV   0x0007   /* semaphore overflow */
#define PI_ERR_CT   0x0008   /* function is called twice */
#define PI_ERR_PD   0x0009   /* no more pending to semaphore */

/* value of PI_FOREVER has been formerly WAIT_FOREVER */
#define PI_FOREVER  (-1)

/* PIL definitions */
#define PI_ORD_PRIO 0
#define PI_ORD_FCFS 1

#define PI_TICK     16UL


/*****************************************************************************
*   TYPEDEFS
*/
typedef struct
{
    VERSION_INFO   pi_info;
    void           (*ppi_copy8)             ( void*, void*, UINT16 );
    void           (*ppi_copy16)            ( void*, void*, UINT16 );
    void           (*ppi_disable)           ( void );
    void           (*ppi_enable)            ( void );
    void           (*ppi_call_hw_int)       ( INT16 );
    void*          (*ppi_alloc)             ( UINT16, INT16, char*);
    void           (*ppi_free)              ( void*, INT16, char*);
    INT16          (*ppi_create_queue)      ( INT16, INT16, INT16* );
    char*          (*ppi_accept_queue)      ( INT16, INT16* );
    char*          (*ppi_receive_queue)     ( INT16, INT32,  INT16* );
    void           (*ppi_send_queue)        ( INT16, char*,  INT16* );
    void           (*ppi_queue_jam)         ( INT16, char*,  INT16* );
    void           (*ppi_queue_inquiry)     ( INT16, INT16*, INT16* );
    INT16          (*ppi_create_semaphore)  ( UINT16, INT16, INT16* );
    UINT16         (*ppi_inquiry_semaphore) ( INT16, INT16* );
    void           (*ppi_pend_semaphore)    ( INT16, INT32, INT16* );
    void           (*ppi_post_semaphore)    ( INT16, INT16* );
    void           (*ppi_lock_task)         ( void );
    void           (*ppi_unlock_task)       ( void );
    INT16          (*ppi_create_timeout)    ( INT16*, void*, void*, INT16 );
    INT16          (*ppi_enable_timeout)    ( INT16, UINT32 );
    INT16          (*ppi_disable_timeout)   ( INT16 );
    INT16          (*ppi_delete_timeout)    ( INT16 );
    void           (*ppi_semaphore_accept)  ( INT16, INT16* );
    void           (*ppi_task_delay)        ( UINT32 );
    void           (*ppi_memset16)          ( void* , INT16,  UINT16 );
    void           (*ppi_memset8)           ( void* , char,   UINT16 );
}
PI_STR_ICT;


/*****************************************************************************
*   GLOBAL FUNCTIONS
*/
void     _pi_copy8(             void* pTarget, void* pSource, UINT16  Size );
void     _pi_copy16(            void* pTarget, void* pSource, UINT16  Size );
void     _pi_disable(           void );
void     _pi_enable(            void );
void     _pi_call_hw_int(       INT16 sNumber );
void*    _pi_alloc(             UINT16 size, INT16 line, char* file);
void     _pi_free (             void *ptr, INT16 line, char* file );
INT16    _pi_create_queue(      INT16 sSize, INT16  sOption,  INT16* psErr);
char*    _pi_accept_queue(      INT16 sId,   INT16* psErr);
char*    _pi_receive_queue(     INT16 sId,   INT32   lTimeout, INT16* psErr);
void     _pi_send_queue(        INT16 sId,   char*  pchMsg,   INT16* psErr);
void     _pi_queue_inquiry(     INT16, INT16* , INT16* );
void     _pi_queue_jam(         INT16, char*, INT16* );
INT16    _pi_create_semaphore(  UINT16 sInit, INT16 sOption, INT16* psErr);
UINT16   _pi_inquiry_semaphore( INT16 sId, INT16* psErr);
void     _pi_semaphore_accept(  INT16 sID, INT16* errp);
void     _pi_pend_semaphore(    INT16 sId, INT32 lTimeout, INT16 *psErr);
void     _pi_post_semaphore(    INT16 sId, INT16* psErr );
void     _pi_lock_task(         void );
void     _pi_unlock_task(       void );
INT16    _pi_create_timeout(    INT16* psId, void* pFunc, void* pPara, INT16 sCount);
INT16    _pi_enable_timeout(    INT16  sId, UINT32 ulTicks );
INT16    _pi_disable_timeout(   INT16 sId );
INT16    _pi_delete_timeout(    INT16 sId );
void     _pi_task_delay(        UINT32 time );
void     _pi_memset16(          void* targetp, INT16 value, UINT16 size );
void     _pi_memset8(           void* targetp, char value,  UINT16 size );


/* Define location for indirect call */
#define PI_IND_CALL     (*(PI_STR_ICT * *) PIL_ADR_TABLE)

#ifdef O_DC
    #define pi_copy8                    _pi_copy8
    #define pi_copy16                   _pi_copy16
    #define pi_disable                  _pi_disable
    #define pi_enable                   _pi_enable
    #define pi_call_hw_int              _pi_call_hw_int
    #define pi_alloc(size)              _pi_alloc( (size), __LINE__, __FILE__)
    #define pi_free(ptr)                _pi_free( (ptr) , __LINE__, __FILE__)
    #define pi_create_queue             _pi_create_queue
    #define pi_accept_queue             _pi_accept_queue
    #define pi_receive_queue            _pi_receive_queue
    #define pi_send_queue               _pi_send_queue
    #define pi_create_semaphore         _pi_create_semaphore
    #define pi_inquiry_semaphore        _pi_inquiry_semaphore
    #define pi_accept_semaphore         _pi_semaphore_accept
    #define pi_pend_semaphore           _pi_pend_semaphore
    #define pi_post_semaphore           _pi_post_semaphore
    #define pi_lock_task                _pi_lock_task
    #define pi_unlock_task              _pi_unlock_task
    #define pi_create_timeout           _pi_create_timeout
    #define pi_enable_timeout           _pi_enable_timeout
    #define pi_disable_timeout          _pi_disable_timeout
    #define pi_delete_timeout           _pi_delete_timeout
    #define pi_memset8                  _pi_memset8
    #define pi_memset16                 _pi_memset16
    #define pi_delay_task               _pi_task_delay
    #define pi_jam_queue                _pi_queue_jam
    #define pi_inquiry_queue            _pi_queue_inquiry
#else
    #define pi_copy8                    (* (PI_IND_CALL->ppi_copy8))
    #define pi_copy16                   (* (PI_IND_CALL->ppi_copy16))
    #define pi_disable                  (* (PI_IND_CALL->ppi_disable))
    #define pi_enable                   (* (PI_IND_CALL->ppi_enable))
    #define pi_call_hw_int              (* (PI_IND_CALL->ppi_call_hw_int))
    #define pi_alloc(size)              (* (PI_IND_CALL->ppi_alloc)) ((size),__LINE__,__FILE__)
    #define pi_free(ptr)                (* (PI_IND_CALL->ppi_free))  ((ptr),__LINE__,__FILE__)
    #define pi_create_queue             (* (PI_IND_CALL->ppi_create_queue))
    #define pi_accept_queue             (* (PI_IND_CALL->ppi_accept_queue))
    #define pi_receive_queue            (* (PI_IND_CALL->ppi_receive_queue))
    #define pi_send_queue               (* (PI_IND_CALL->ppi_send_queue))
    #define pi_create_semaphore         (* (PI_IND_CALL->ppi_create_semaphore))
    #define pi_inquiry_semaphore        (* (PI_IND_CALL->ppi_inquiry_semaphore))
    #define pi_pend_semaphore           (* (PI_IND_CALL->ppi_pend_semaphore))
    #define pi_post_semaphore           (* (PI_IND_CALL->ppi_post_semaphore))
    #define pi_lock_task                (* (PI_IND_CALL->ppi_lock_task))
    #define pi_unlock_task              (* (PI_IND_CALL->ppi_unlock_task))
    #define pi_create_timeout           (* (PI_IND_CALL->ppi_create_timeout))
    #define pi_enable_timeout           (* (PI_IND_CALL->ppi_enable_timeout))
    #define pi_disable_timeout          (* (PI_IND_CALL->ppi_disable_timeout))
    #define pi_delete_timeout           (* (PI_IND_CALL->ppi_delete_timeout))
    #define pi_memset8                  (* (PI_IND_CALL->ppi_memset8))
    #define pi_memset16                 (* (PI_IND_CALL->ppi_memset16))
    #define pi_delay_task               (* (PI_IND_CALL->ppi_task_delay))
    #define pi_jam_queue                (* (PI_IND_CALL->ppi_queue_jam))
    #define pi_accept_semaphore         (* (PI_IND_CALL->ppi_semaphore_accept))
    #define pi_inquiry_queue            (* (PI_IND_CALL->ppi_queue_inquiry))
#endif

#ifdef __cplusplus
}
#endif


#endif /* PI_API_H */

