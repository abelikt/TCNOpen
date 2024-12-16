/* $Header: /CSS/Code/RTS/COMMON/api/tnm_api.h 11    06-06-15 11:34 Jrehnman $
*****************************************************************************
*  COPYRIGHT    : (c) 1997 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : tnm_api.h
*
*  ABSTRACT     : TNM service: Application Programming Interface
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      : $Revision: 11 $      $Date: 06-06-15 11:34 $
******************************************************************************/


#ifndef TNM_API_H
#define TNM_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/
/* Is part of TNM product */
#include "tnm.h"

/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_TNM
#define TNM_VERSION        1
#define TNM_RELEASE        3
#define TNM_UPDATE         2
#define TNM_EVOLUTION      0


/*****************************************************************************
*   TYPEDEFS
*/
typedef struct
{
   VERSION_INFO      tnm_info;
   void              (*pma_subscribe) (ENUM16, ENUM8, MA_SERVICE_CALL, MA_SERVICE_CLOSE, char *);
} TNM_STR_ICT;

/*****************************************************************************
*   GLOBAL FUNCTIONS
*/

/*  The following prototypes are defined in tnm.h */

/* Define location for indirect call */
#define TNM_IND_CALL     (*(TNM_STR_ICT **) TNM_ADR_TABLE)

#ifdef O_DC
   #define ma_subscribe        _ma_subscribe
#else
   #define ma_subscribe        (*(TNM_IND_CALL->pma_subscribe))
#endif

#ifdef __cplusplus
}
#endif

#endif /* TNM_API_H */
