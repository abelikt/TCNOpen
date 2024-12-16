/* $Header: /CSS/Code/RTS/COMMON/api/dm_api.h 17    02-09-17 17:44 Thomas Clevström $
******************************************************************************
*  COPYRIGHT    : (c) 1996 Adtranz
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : dm_api.h
*
*  ABSTRACT     : Dynamic Memory service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/dm_api.h $
*  
*  17    02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  16    98-05-29 12:33 Anders Öhlander
*  Defines are moved to the rts_device.h files, see MR 93.
*
*  15    98-03-04 13:44 Davor Ivicevic
*  Added O_ORION
*
*  14    28.11.97 18:03 Detra
*  dm defines for VCU6U_GW  and VCU6U_GP changed
*
*  13    24.10.97 12:35 Detra
*  divide VCU_6U into VCU6U_GW and VCU6U_GP
*
*  12    97-08-14 15:22 Davor Ivicevic
*  Changed ICON
*
*  11    97-08-08 15:07 Björn Elliott
*  Changed DM_VXWORKS_START_ADRS for VCU_L
*
*  10    97-07-17 10:30 Davor Ivicevic
*  Added O_ICON
*
*  9     97-07-17 9:20 Björn Elliott
*
*  8     97-06-27 9.23 Anders Wallin
*  Header added
*
*  7     97-01-09 13:50 Peter Koerner
*  O_VCU_6U same as O_VCU
*
*  6     96-12-04 21:17 Dev Pradhan
*  Added defines for Memory Map Addresses
*
*  5     96-12-02 12.57 Anders Wallin
*  Duoble-pointer to p_block in dm_alloc added
*
*  4     96-12-02 7.35 Anders Wallin
*  C++ support added
*
*  3     96-11-29 11.03 Anders Wallin
*
******************************************************************************/

#ifndef DM_API_H
#define DM_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/

/*****************************************************************************
*   DEFINES
*/

#define SERVICE_NAME_DM
#define DM_VERSION          1
#define DM_RELEASE          0
#define DM_UPDATE           0
#define DM_EVOLUTION        1

/*****************************************************************************
*   TYPEDEFS
*/
typedef struct
{
    VERSION_INFO dm_info;
    INT16 ( *pdm_malloc) ( UINT8, UINT32, void** );
    INT16 ( *pdm_free)   ( UINT8, void*);
} DM_STR_ICT;


/*****************************************************************************
*   GLOBALS
*/



/*****************************************************************************
*   GLOBAL FUNCTIONS
*/
INT16 dm_malloc( UINT8   identity,
                 UINT32  n_bytes,
                 void**  p_block);

INT16 dm_free(   UINT8   identity,
                 void*   p_block);

/* Define location for indirect call */
#define DM_IND_CALL     (*(DM_STR_ICT * *) DM_ADR_TABLE)

#ifdef O_DC
    #define os_dm_malloc   dm_malloc
    #define os_dm_free     dm_free
#else
    #define os_dm_malloc   (* (DM_IND_CALL->pdm_malloc))
    #define os_dm_free     (* (DM_IND_CALL->pdm_free))
#endif

#ifdef __cplusplus
}
#endif


#endif /* DM_API_H */
