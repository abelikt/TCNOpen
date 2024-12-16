/* $Header: /CSS/Code/RTS/COMMON/api/tnm_user_msg.h 4     02-09-18 9:37 Thomas Clevström $
*****************************************************************************
*  COPYRIGHT    : (c) 1999 DaimlerChrysler Rail Systems Ltd
******************************************************************************
*  PROJECT      : TNM
*
*  MODULE       : tnm_user_msg.h
*
*  ABSTRACT     : TNM service: Types and prototypes for user specific functions
*
*  REMARKS      : Compliance to IEC1375-5: 97-07-12
*
******************************************************************************
*  HISTORY      : $Revision: 4 $        $Date: 02-09-18 9:37 $
******************************************************************************/

#ifndef MM_USER_MSG_H
#define MM_USER_MSG_H

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************
* Definitions for Service Identifiers (SIF's)                               *
* 128 - 256 : user-defined objects                                          *
****************************************************************************/

#define SIF_ENTRY_POINTS_READ            128

#define SIF_MONITOR_CONTROL              129
#define SIF_MONITOR_GET_NEXT             130


/*****************************************************************************
*   SIF 128     ENTRY_POINTS_READ data types
*/

#define TNM_MAX_ENTRY_POINTS    0xff 

typedef struct STR_TNM_CALL_ENTRY_POINTS_READ
{
   UNSIGNED8               tnm_code;
   UNSIGNED8               sif_code;
} TNM_CALL_ENTRY_POINTS_READ, *P_TNM_CALL_ENTRY_POINTS_READ;

typedef struct STR_TNM_RPLY_ENTRY_POINTS_READ
{
   UNSIGNED8               tnm_code;
   UNSIGNED8               sif_code;
   UNSIGNED16              nr_entry_points;
   TNM_ENTRY_POINT_INFO    entry_points;              /* first entry point info */
} TNM_RPLY_ENTRY_POINTS_READ, *P_TNM_RPLY_ENTRY_POINTS_READ;


/*****************************************************************************
*   SIF 129     Monitor_Control data types
*/

typedef struct STR_TNM_CALL_MONITOR_CONTROL
{
   UNSIGNED8               tnm_code;
   UNSIGNED8               sif_code;
   CHARACTER               monitor_command[64];
} TNM_CALL_MONITOR_CONTROL, *P_TNM_CALL_MONITOR_CONTROL;

typedef struct STR_RPLY_CALL_MONITOR_CONTROL
{
   UNSIGNED8               tnm_code;
   UNSIGNED8               sif_code;
   UNSIGNED8               reserved0;
   UNSIGNED8               end_of_output;
   CHARACTER               monitor_output[512];
} TNM_RPLY_MONITOR_CONTROL, *P_TNM_RPLY_MONITOR_CONTROL;


/*****************************************************************************
*   SIF 130     Get_Next_Monitor data types
*/

typedef struct STR_TNM_CALL_GET_NEXT_MONITOR
{
   UNSIGNED8               tnm_code;
   UNSIGNED8               sif_code;
} TNM_CALL_GET_NEXT_MONITOR, *P_TNM_CALL_GET_NEXT_MONITOR;

typedef struct STR_TNM_RPLY_GET_NEXT_MONITOR
{
   UNSIGNED8               tnm_code;
   UNSIGNED8               sif_code;
   UNSIGNED8               reserved0;
   UNSIGNED8               end_of_output;
   CHARACTER8              monitor_output[512];
} TNM_RPLY_GET_NEXT_MONITOR, *P_TNM_RPLY_GET_NEXT_MONITOR;


#ifdef __cplusplus
}
#endif

#endif /* MM_USER_H */
