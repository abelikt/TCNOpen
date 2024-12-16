/* $Header: /CSS/Code/RTS/COMMON/api/se_api.h 19    02-11-04 17:41 Thomas Clevström $
******************************************************************************
*  COPYRIGHT    : (c) 1995 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : SE_API.H
*
*  ABSTRACT     : System Event log service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/se_api.h $
*  
*  19    02-11-04 17:41 Thomas Clevström
*  General purpose return values moved from PRV to API because they are
*  refered to in the API manual
*  
*  18    02-09-18 9:37 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  17    00-08-01 7:24 Martin Gisbert
*  #define du_hamster_prev_get corrected
*  
*  16    98-12-17 12:12 Anders Öhlander
*  Some asserts are added for the TDS team.
*
*  15    98-10-06 7:51 Anders Öhlander
*  Corrected the api for the DU_HAMSTER functions.
*
*  14    98-09-18 11:28 Anders Öhlander
*  Add du_hamster_text, see MR 157. Some more minor changes has been done
*  on the hamster api.
*
*  13    98-05-29 12:28 Anders Öhlander
*  The SE log is now readable from the applications. See MR 117. The
*  hamster_put_text functions is now added to the API, see MR 146.
*
*  12    97-06-27 9.24 Anders Wallin
*  Header added
*
*  11    96-12-17 12.58 Anders Wallin
*  changed the se ICT names
*
*  10    96-11-28 18:00 Johan Frank
*  Modified se_log_text()
*
*  9     96-09-04 12.24 Anders Wallin
*
*  8     96-08-16 16.08 Anders Wallin
*
*  7     96-08-09 15.05 Johan Frank
*
*
*  6     96-08-06 15.24 Anders Wallin
*  SUBPROJECT_SE changed SERVICE_SE
*
*  5     96-08-06 10.39 Johan Frank
*  Changed type of parameter preceeding ellipses
*
*  4     96-08-02 16.28 Johan Frank
*  Added du_-functions for compatibility reasons with TCN SW
*
*  3     96-07-01 17.45 Johan Frank
*
*  2     96-06-27 15.51 Johan Frank
*  Conversion complete
*
*  1     96-06-26 15.41 Johan Frank
*  First version
*
******************************************************************************/


#ifndef  SE_API_H
#define  SE_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/

/*****************************************************************************
*   DEFINES
*/

/* file position for hamster call */
#define SE_POSITION         __FILE__,__LINE__
#define DU_POSITION         __FILE__,__LINE__

/* strategies */
#define SE_CONTINUE         0
#define SE_RESET            1
#define SE_HALT             1
#define SE_STOP             2
#define SE_STALL            3
#define SE_SHUTDOWN         4

/* strategies for the old DU-functions.*/
#define DU_CONTINUE         0
#define DU_RESET            1
#define DU_HALT             1
#define DU_STOP             2
#define DU_STALL            3
#define DU_SHUTDOWN         4


/* version verification mechanism */
#define SERVICE_NAME_SE
#define SE_VERSION          1
#define SE_RELEASE          0

/* general purpose return values */
#define SE_RET_OK               0x00
#define SE_FAILURE              0x01

/* compatibility to the old system event log (hamster) */
#define du_info_hamster         os_se_info
#define du_hamster_last_get     os_se_last_get
#define du_hamster_prev_get     os_se_prev_get

#define du_hamster              du_hamster_put


/* Macros which substitute corresponding MicOS-functions .        */
#define du_hamster_continue( cond ) if(( cond )) du_hamster_put( SE_POSITION, SE_CONTINUE, 0 );
#define du_hamster_halt( cond )     if(( cond )) du_hamster_put( SE_POSITION, SE_RESET, 0 );
#define du_hamster_reset( cond )    if(( cond )) du_hamster_put( SE_POSITION, SE_RESET, 0 );
#define du_hamster_shutdown( cond ) if(( cond )) du_hamster_put( SE_POSITION, SE_SHUTDOWN, 0 );
#define du_hamster_stall( cond )    if(( cond )) du_hamster_put( SE_POSITION, SE_STALL, 0 );

/**************************************************************************
*                   EXTERNALS
*/

extern void  se_log_info        ( INT16* p_entry_count,
                                  INT16* p_current_index );

extern INT16 se_log_last_get    ( CHAR* log_entry , INT16* index);

extern INT16 se_log_prev_get    ( CHAR* log_entry , INT16* index);

extern void se_log_text         ( const CHAR* p_file_id,
                                  UINT16 line_nr,
                                  const CHAR* fmt,
                                  ... );

/* compatibility to the old system event log (hamster) */
extern void  _du_hamster_put    ( const CHAR* p_file_id,
                                  UINT16 line_nr,
                                  INT16 strategy,
                                  INT32 count,
                                  ... );
extern void _du_hamster_text    ( const CHAR* p_file_id,
                                  UINT16 line_nr,
                                  INT16 strategy,
                                  const CHAR* fmt,
                                  ... );

/*****************************************************************************
*   TYPEDEFS
*/

/* structure for indirect call */

  typedef struct
  {
     VERSION_INFO se_info;
     void  ( *pos_se_info)           ( INT16* p_entry_count,
                                       INT16* p_current_index );
     INT16 ( *pos_se_last_get)       ( CHAR* log_entry , INT16* index);
     INT16 ( *pos_se_prev_get)       ( CHAR* log_entry , INT16* index);

     void  ( *pos_se_write)          ( const CHAR* p_file_id,
                                       UINT16 line_nr,
                                       const CHAR* fmt,
                                       ... );

     void  ( *pdu_hamster_put)       ( const CHAR* p_file_id,
                                       UINT16 line_nr,
                                       INT16 strategy,
                                       INT32 count,
                                       ... );

     void  ( *pdu_hamster_text)      ( const CHAR* p_file_id,
                                       UINT16 line_nr,
                                       INT16 strategy,
                                       const CHAR* fmt,
                                       ... );

  } SE_IND_CALL_T;

/*****************************************************************************
 *              DECLARATIONS FOR INDIRECT/DIRECT CALLING MECHANISM
 */

extern const SE_IND_CALL_T  se_ind_call_table;

#define PSE_IND_CALL        (*(SE_IND_CALL_T * *) SE_ADR_TABLE)

#ifdef O_DC
    /* API - functions direct call */
    /* --------------------------- */

    #define os_se_write        se_log_text
    #define os_se_info         se_log_info
    #define os_se_last_get     se_log_last_get
    #define os_se_prev_get     se_log_prev_get
	#define du_hamster_put 	   _du_hamster_put
	#define du_hamster_text	   _du_hamster_text
#else
    /* API - functions indirect call */
    /* ----------------------------- */

    #define os_se_write        (* (PSE_IND_CALL->pos_se_write))
    #define os_se_info         (* (PSE_IND_CALL->pos_se_info))
    #define os_se_last_get     (* (PSE_IND_CALL->pos_se_last_get))
    #define os_se_prev_get     (* (PSE_IND_CALL->pos_se_prev_get))
	#define du_hamster_put 	   (* (PSE_IND_CALL->pdu_hamster_put))
	#define du_hamster_text	   (* (PSE_IND_CALL->pdu_hamster_text))
#endif


/* Assert macros, only available if switch O_ASSERT is defined. */
#if defined ( O_ASSERT )
  #define du_assert(cond)                      \
    if( cond )                                 \
    {                                          \
    }                                          \
    else                                       \
    {                                          \
      du_hamster(DU_POSITION,DU_HALT, 0);      \
    }
  #define du_assertx(cond,f)                   \
    if( cond )                                 \
    {                                          \
    }                                          \
    else                                       \
    {                                          \
      f;                                       \
    }
#else
  #define du_assert(cond) {}
  #define du_assertx(cond,f) {}
#endif


#ifdef __cplusplus
}
#endif


#endif /* SE_API_H */
