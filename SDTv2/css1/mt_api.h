/* $Header: /CSS/Code/RTS/COMMON/api/mt_api.h 2     02-09-17 17:44 Thomas Clevström $
*****************************************************************************
*  COPYRIGHT    : (c) 1999 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : mt_api.h
*
*  ABSTRACT     : Memory Test service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/mt_api.h $
*  
*  2     02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  1     99-06-29 17:16 Anders Öhlander
*  First version.
*  
*  1     97-04-08 16.34 Anders Wallin
*  Service template 
*
******************************************************************************/

#ifndef MT_API_H
#define MT_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   DEFINES
*/                                          
#define SERVICE_NAME_MT
#define MT_VERSION      1
#define MT_RELEASE      0
#define MT_UPDATE       0
#define MT_EVOLUTION    0

/* Memory test result codes */
#define MT_NOT_TESTED           0x00000000
#define MT_TEST_PASSED          0x00000001
#define MT_RAM_STACK_NZ_ERR     0xFF000000
#define MT_RAM_STACK_MEM_ERR    0xFF000001
#define MT_RAM_DATA_BUS_ERR     0xFF000002
#define MT_RAM_ADDRESS_BUS_ERR  0xFF000003
#define MT_RAM_MEM_CELL_ERR     0xFF000004
#define MT_RAM_SKIP_TEST_ERR    0xFF000005
#define MT_ROM_CHKSUM_ERR       0xFF000006

#ifndef _ASMLANGUAGE

/*****************************************************************************
*   TYPEDEFS
*/

typedef struct mt_indirect_call_table
{
    VERSION_INFO  info;
} MT_STR_ICT;

/*****************************************************************************
*   FUNCTIONS PROTOTYPES
*
*/
/* application access via direct call */

#define MT_IND_CALL     (*(MT_STR_ICT * *) MT_ADR_TABLE)

#ifdef O_DC
    /* --------------- */
    /*   direct call   */
    /* --------------- */

#else
    /* ----------------- */
    /*   indirect call   */
    /* ----------------- */

#endif

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* MT_API_H */

