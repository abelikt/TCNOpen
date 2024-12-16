/* $Header: /CSS/Code/RTS/DEVICE/VCU6U_GP/api/vcu6u_gp_ee.h 2     02-09-18 14:22 Thomas Clevström $
*****************************************************************************
*  COPYRIGHT    : (c) 1997 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : vcu6u_gp_ee.h
*
*  ABSTRACT     : VCU6U_GP: EEPROM service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/DEVICE/VCU6U_GP/api/vcu6u_gp_ee.h $
*  
*  2     02-09-18 14:22 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  1     00-11-29 17:54 Thomas Clevström
*  Re-introduced imported VCU6U 1.7.0
*  
*  2     9.11.98 13:14 Mreisman
*  defines for INT_EEPROM_BYTE_SIZE and EXT_EEPROM_BYTE_SIZE added
*  
*  
*  1     07.08.98 12:46 Detra Schm.
*  copied from VCU6U_GP - ee_api.h and renamed to vcu6u_gp_ee.h
*  
******************************************************************************/

#ifndef EE_API_H
#define EE_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_EE
#define EE_VERSION      1
#define EE_RELEASE      0
#define EE_UPDATE       0
#define EE_EVOLUTION    0



/* serial eeprom parameters */
#define INT_EE_BYTE_ADRS         0x0000		/* byte address of int. eeprom */ 
#define INT_EEPROM_BYTE_SIZE     0x0200     /* byte size of int. eeprom    */
#define EXT_EE_BYTE_ADRS         0x0200		/* byte address of ext. eeprom */ 
#define EXT_EEPROM_BYTE_SIZE     0x0200     /* byte size of ext. eeprom    */

/*****************************************************************************
*   TYPEDEFS
*/

typedef struct ee_indirect_call_table
{
    VERSION_INFO  info;

    INT16 ( *pos_ee_read                 ) ( UINT16   address,
                                             UINT16   length,
                                             UINT8*   data             );

    INT16 ( *pos_ee_write                ) ( UINT16   address,
                                             UINT16   length,
                                             UINT8*   data             );
} EE_STR_ICT;

/*****************************************************************************
*   FUNCTIONS PROTOTYPES
*
*/
/* application access via direct call */
INT16   ee_read                ( UINT16   address,
                                 UINT16   length,
                                 UINT8*   data             );

INT16   ee_write               ( UINT16   address,
                                 UINT16   length,
                                 UINT8*   data             );

#define EE_IND_CALL     (*(EE_STR_ICT * *) EE_ADR_TABLE)

/* --------------- */
/*   direct call   */
/* --------------- */

#ifdef O_DC

    #define os_ee_read          ee_read
    #define os_ee_write         ee_write

#else

    /* ----------------- */
    /*   indirect call   */
    /* ----------------- */

    #define os_ee_read                 (* (EE_IND_CALL->pos_ee_read                ))
    #define os_ee_write                (* (EE_IND_CALL->pos_ee_write               ))
#endif

#ifdef __cplusplus
}
#endif

#endif /* EE_API_H */

