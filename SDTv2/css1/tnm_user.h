/* $Header: /CSS/Code/RTS/COMMON/api/tnm_user.h 5     02-09-18 9:37 Thomas Clevström $
*****************************************************************************
*  COPYRIGHT    : (c) 1999 DaimlerChrysler Rail Systems Ltd
******************************************************************************
*  PROJECT      : TNM
*
*  MODULE       : tnm_user.h
*
*  ABSTRACT     : TNM service: Types and prototypes for user specific functions
*
*  REMARKS      : Compliance to IEC1375-5: 97-07-12
*
******************************************************************************
*  HISTORY      : $Revision: 5 $        $Date: 02-09-18 9:37 $
******************************************************************************/

#ifndef MM_USER_H
#define MM_USER_H

#ifdef __cplusplus
extern "C"
{
#endif


/*****************************************************************************
*   SIF 128     ENTRY_POINTS_READ data types
*/

#define TNM_MAX_ENTRY_POINTS    0xff 

typedef struct STR_TNM_ENTRY_POINT_INFO
{
   UNSIGNED8         version;                   /* version info of the entry point     */
   UNSIGNED8         release;                   /* release info of the entry point     */
   UNSIGNED8         update;                    /* update info of the entry point      */
   UNSIGNED8         evolution;                 /* evolution info of the entry point   */
   STRING16          name;                      /* name of the entry point (null term.) */
   UNSIGNED32        date;                      /* generation date of the entry point  */
   UNSIGNED32        type;                      /* type of the entry point             */
   UNSIGNED32        entry_point_addr;          /* address of the entry point structure */
} TNM_ENTRY_POINT_INFO, *P_TNM_ENTRY_POINT_INFO, MM_ENTRY_POINT_INFO;


/*****************************************************************************
*   SIF 129     Monitor_Control data types
*/



/*****************************************************************************
*   SIF 130     Get_Next_Monitor data types
*/


/*****************************************************************************
*   Manager Interface (MGI) of User Functions
*****************************************************************************/


/*-----------------------------------------------------------------------------
*  FUNCTION : mm_read_entry_points                                      SIF 128
*------------------------------------------------------------------------------
*  INPUTS   : agent_address
*
*  OUTPUTS  : nr_entry_points,         number of entry points 
*             entry_point_list[]      returned entry points 
*
*  RETURNS  : MM_RESULT
*------------------------------------------------------------------------------
*  ABSTRACT : Reads information from the device entry point and from all 
*           application entry points on the target. An array of entry points 
*           is returned. The caller is responsible for the deletion of the 
*           returned array. 
*----------------------------------------------------------------------------*/

MM_RESULT mm_read_entry_points (AM_ADDRESS                agent,             
                                UNSIGNED16*               nr_entry_points,   
                                TNM_ENTRY_POINT_INFO     *entry_point_list[]);

/*----------------------------------------------------------------------------  
*   MGI MONITOR_CONTROL
*-----------------------------------------------------------------------------  
*   Reads the output of the monitor for specific command.
*   A boolean ist returned, wether the output is terminated or not.
*   An array of the output is returned.
*/

MM_RESULT mm_monitor_control (AM_ADDRESS     agent,                          /* agent address                      */
                              char           monitor_command[64],            /* monitor command                    */
                              UNSIGNED8     *end_of_output,                  /* 0 unless output is terminated      */
                              char           monitor_output[512]);           /* output of the monitor              */

/*----------------------------------------------------------------------------  
*   MGI MONITOR_GET_NEXT
*-----------------------------------------------------------------------------  
*   Reads the rest of the output of the monitor for a specific command   
*   A boolean ist returned, wether the output is terminated or not.    
*   An array of the output is returned.                                
*/

MM_RESULT mm_monitor_get_next (AM_ADDRESS       agent,                       /* agent address                          */
                               UNSIGNED8       *end_of_output,               /* 0 unless output is terminated          */
                               char             monitor_output[512]);        /* output of the monitor                  */


#ifdef __cplusplus
}
#endif

#endif /* MM_USER_H */
