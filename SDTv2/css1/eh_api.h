/* $Header: /CSS/Code/RTS/COMMON/api/eh_api.h 6     02-09-17 17:44 Thomas Clevström $
******************************************************************************
*  COPYRIGHT    : (c) 1996 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : eh_api.h
*
*  ABSTRACT     : Event Handler service
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/eh_api.h $
*  
*  6     02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  5     97-09-11 16:03 Anders Wallin
*  const added
*
*  4     97-06-27 9.23 Anders Wallin
*  Header added
*
*  3     97-02-10 20.45 Anders Wallin
*  Changed version
*
*  2     96-12-18 12.30 Anders Wallin
*  Changed release no
*
*  1     96-12-18 11.44 Anders Wallin
*
******************************************************************************/


#ifndef EH_API_H
#define EH_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/

/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_EH
#define EH_VERSION      1
#define EH_RELEASE      0

/*****************************************************************************
*   TYPEDEFS
*/
typedef struct
{
    VERSION_INFO  eh_info;
    INT16         ( *peh_connect) ( const char*, FUNCPTR, UINT8 );
} EH_STR_ICT;


/*****************************************************************************
*   GLOBAL FUNCTIONS
*/
INT16 eh_connect( const char appl_name[],
                  FUNCPTR    function,
                  UINT8      priority );


/* Define location for indirect call */
#define EH_IND_CALL     (*(EH_STR_ICT * *) EH_ADR_TABLE)

#ifdef O_DC
    #define os_eh_connect        eh_connect
#else
    #define os_eh_connect        (* (EH_IND_CALL->peh_connect))
#endif

#ifdef __cplusplus
}
#endif


#endif /* EH_API_H */

