/* $Header: /CSS/Code/RTS/COMMON/api/ae_api.h 10    02-11-04 17:41 Thomas Clevström $
*****************************************************************************
*  COPYRIGHT    : (c) 1995 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : AE_API.H
*
*  ABSTRACT     : Application Event log service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/ae_api.h $
*  
*  10    02-11-04 17:41 Thomas Clevström
*  General purpose return values moved from PRV to API because they are
*  refered to in the API manual
*  
*  9     02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  8     98-05-29 12:25 Anders Öhlander
*  The AE log is now readable from the applications. See MR 117.
*
*  7     97-08-08 9.56 Anders Wallin
*  Version changed to 1.0
*
*  6     97-06-27 9.23 Anders Wallin
*  Header added
*
*  5     97-06-25 15:07 Anders Öhlander
*  Change the api for the function ae_log_text( char * file, INT16 line,
*  char * text) to  ae_log_text( const char * file, UINT16 line, const
*  char * text).See SPR 66.
*
*  4     97-05-22 12.07 Anders Wallin
*  Log history added
*
*
******************************************************************************/


#ifndef  AE_API_H
#define  AE_API_H

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
#define AE_POSITION         __FILE__,__LINE__

/* strategies */
#define AE_CONTINUE         0
#define AE_RESET            1
#define AE_STOP             2
#define AE_STALL            3
#define AE_SHUTDOWN         4


/* version verification mechanism */
#define SERVICE_NAME_AE
#define AE_VERSION          1
#define AE_RELEASE          0
#define AE_UPDATE           0
#define AE_EVOLUTION        0

/* general purpose return values */
#define AE_RET_OK               0x00
#define AE_FAILURE              0x01


/**************************************************************************
*                   EXTERNALS
*/

extern void  ae_log_info        ( INT16* p_entry_count,
                                  INT16* p_current_index );

extern INT16 ae_log_last_get    ( char* log_entry , INT16* index);

extern INT16 ae_log_prev_get    ( char* log_entry , INT16* index);

extern void  ae_log_text        ( const char* p_file_id,
                                  UINT16 line_nr,
                                  const char* fmt,
                                  ... );

/*****************************************************************************
*   TYPEDEFS
*/

/* structure for indirect call */

  typedef struct
  {
     VERSION_INFO ae_info;
     void  ( *pos_ae_info)           ( INT16* p_entry_count,
                                       INT16* p_current_index );
     INT16 ( *pos_ae_last_get)       ( char* log_entry, INT16* index);
     INT16 ( *pos_ae_prev_get)       ( char* log_entry, INT16* index);
     void  ( *pos_ae_write)          ( const char* p_file_id,
                                       UINT16 line_nr,
                                       const char* fmt,
                                       ... );
  } AE_IND_CALL_T;

/*****************************************************************************
 *              DECLARATIONS FOR INDIRECT/DIRECT CALLING MECHANISM
 */

extern const AE_IND_CALL_T  ae_ind_call_table;

#define PAE_IND_CALL        (*(AE_IND_CALL_T * *) AE_ADR_TABLE)

#ifdef O_DC
    /* API - functions direct call */
    /* --------------------------- */

    #define os_ae_write        ae_log_text

    #define os_ae_info         ae_log_info
    #define os_ae_last_get     ae_log_last_get
    #define os_ae_prev_get     ae_log_prev_get

#else
    /* API - functions indirect call */
    /* ----------------------------- */

    #define os_ae_write        (* (PAE_IND_CALL->pos_ae_write))
    #define os_ae_info         (* (PAE_IND_CALL->pos_ae_info))
    #define os_ae_last_get     (* (PAE_IND_CALL->pos_ae_last_get))
    #define os_ae_prev_get     (* (PAE_IND_CALL->pos_ae_prev_get))
#endif

#ifdef __cplusplus
}
#endif


#endif /* AE_API_H */
