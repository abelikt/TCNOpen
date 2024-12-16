/* $Header: /CSS/Code/RTS/COMMON/api/led_api.h 7     02-09-17 17:44 Thomas Clevström $
******************************************************************************
*  COPYRIGHT      : (c) 1995 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT        : CSS
*
*  MODULE         : led_api
*
*  ABSTRACT       : LED service
*
******************************************************************************
*  HISTORY        :
*   $Log: /CSS/Code/RTS/COMMON/api/led_api.h $
*  
*  7     02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  6     97-11-24 15:19 Anders Wallin
*  MR 125
*
*  5     97-10-08 8:09 Anders Wallin
*
*  4     10/07/97 2:23p Björn Elliott
*
*  3     10/06/97 1:04p Björn Elliott
*
*  2     8/22/97 11:03a Björn Elliott
*
*  1     8/20/97 4:36p Björn Elliott
*
*
******************************************************************************/


#ifndef LED_API_H
#define LED_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/


/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_LED
#define LED_VERSION      1
#define LED_RELEASE      1
#define LED_UPDATE       0
#define LED_EVOLUTION    0


/*****************************************************************************
*   TYPEDEFS
*/
typedef struct
{
    VERSION_INFO  led_info;
    void          ( *pled_css)     		 ( void );
    void          ( *pled_appl) 		 ( void );
    INT16         ( *pled_appl_set)      ( UINT16, UINT16 );
} LED_STR_ICT;



/*****************************************************************************
*   GLOBAL FUNCTIONS
*/
void  led_css( void );
void  led_appl( void );
INT16 led_appl_set( UINT16 pattern, UINT16 mask );


/* Define location for indirect call */
#define LED_IND_CALL     (*(LED_STR_ICT * *) LED_ADR_TABLE)

#ifdef O_DC
    #define os_led_css           led_css
    #define os_led_appl          led_appl
    #define os_led_set      	 led_appl_set
#else
    #define os_led_css           (* (LED_IND_CALL->pled_css))
    #define os_led_appl          (* (LED_IND_CALL->pled_appl))
    #define os_led_set      	 (* (LED_IND_CALL->pled_appl_set))
#endif

#ifdef __cplusplus
}
#endif

#endif /* LED_API_H */
