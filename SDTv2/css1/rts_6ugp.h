/* $Header: /CSS/Code/RTS/DEVICE/VCU6U_GP/api/rts_6ugp.h 9     07-03-12 14:56 Bjarne Jensen $
*****************************************************************************
*  COPYRIGHT    : (c) 1998 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : rts_6ugp.h
*
*  ABSTRACT     : VCU6U_GP: Device specific header file
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/DEVICE/VCU6U_GP/api/rts_6ugp.h $
*  
*  9     07-03-12 14:56 Bjarne Jensen
*  New service version is 1.2.0.0
*  
*  8     02-09-18 14:22 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  7     01-04-06 17:03 Thomas Clevström
*  Removed defines of reset reasons, have been moved os_api.h (common).
*  NCR-LARS HÖGBERG10007.
*  
*  6     01-04-06 17:02 Thomas Clevström
*  Untabify.
*  
*  5     01-04-05 8:40 Lars Högberg
*  Removed hi-bootcode functions, have been moved to the common part, NCR
*  -LARS HÖGBERG10007.
*  
*  4     00-12-08 18:41 Lars Högberg
*  Changed article number and NCR -LARS HÖGBERG00009
*  
*  3     00-12-07 17:49 Thomas Clevström
*  Adapt to dluentry.c: Define ARTICLE_NO
*  
*  2     00-12-06 17:59 Thomas Clevström
*  Adapt imported VCU6U to working CSS
*  
*  1     00-11-29 17:54 Thomas Clevström
*  Re-introduced imported VCU6U 1.7.0
*  
*  4     21.01.00 10:29 Schmalfe
*  #define HI_BATT_NOT_EXISTS
*  
*  3     18.06.99 10:45 Jschmalf
*  
*  2     7.05.99 16:53 Jschmalf
*  hi_isr_attach in ind_call_table aufgenommen
*  
*  1     16.12.98 10:20 Jschmalf
*  
*  2     12.11.98 17:02 Mreisman
*  hi functions changed for VCU6U
*
*  1     98-08-12       Schmalfeldt
*  copied from vcu 1.3.b
*
*  last vcu comment
*  1     98-07-01 14:14 Anders Öhlander
*  First version.
*
******************************************************************************/

#ifndef RTS_VCU6U_GP_H
#define RTS_VCU6U_GP_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*       INCLUDES
*/
#include "css.h"

/*****************************************************************************
*   DEFINES
*/

/* Service API */

#define JMP_TABLE_BASE   0x02FFF400  /* 1 Kb on the VCU. - 0x2FFF7FF */
#define JMP_TABLE_SIZE   0x0400      /* 1 Kb */

/* led bits used with function bc_led_set */
#define LED_S_CO                ((UINT16)0x0008)

/* Define Dynamic Memory (DM-) constants.*/
#define DM_VXWORKS_START_ADRS           0x3001000
#define DM_SRAM_VECTOR_TABLE_END_ADRS   0x2FFFFFF
#define DM_SRAM_HAMSTER_AREA_START_ADRS 0x2FF6000

#include "vcu6u_gp_ee.h"


#define SERVICE_NAME_VCU
#define VCU_VERSION      1
#define VCU_RELEASE      2
#define VCU_UPDATE       0
#define VCU_EVOLUTION    0


/* GENERAL RETURN VALUES */
/* ===================== */
#define HI_RET_OK               0x0000
#define HI_FAILURE              0x0001
#define HI_OUT_OF_RANGE         0x0002
#define HI_NO_SEM               0x0003


/* HIX RETURN VALUES */
/* ================= */
#define HIX_OK                  0x00
#define HIX_NO_DATA             0x01
#define HIX_OUT_OF_RANGE        0x02


/* Temperature Status Readings */
/* =========================== */
#define HI_TEMP_OK              0
#define HI_TEMP_BAD             1
#define HI_TEMP_INVALID         2

#define HI_TEMP_COUNTDOWN_START 300
     /* Time between begin of continuously detected overheat  */
         /* case until system shutdown, starts at 300 sec / 5 min */

/* Battery Voltage Readings */
/* ======================== */
#define HI_BATT_OK              0               /* Battery unit is OK         */
#define HI_BATT_LOW             1               /* Battery low - replace soon */
#define HI_BATT_DEAD            2               /* Battery dead - replace now */
#define HI_BATT_INVALID         3               /* Please try later           */
#define HI_BATT_NOT_EXISTS      4               /* No battery on board        */
#define HI_BATT_NOT_USED        5               /* No Battery supervision     */

/* HI_BATT_INVALID occurs if the first voltage reading is requested   */
/* but the first measurement has not yet been done.  This message may */
/* most likely occur shortly after system start.                      */

/* ARTICLE NUMBER */
/* =================== */
#define ARTICLE_NO      "3EST120-48 "


/*****************************************************************************
*   TYPEDEFS
*/

/* structure for indirect call */
typedef struct STR_VCU_ICT
{
    VERSION_INFO    vcu_info;
    INT16           ( *phi_temp_status_get)     ( INT16 *, UINT16 *);
    INT16           ( *phi_batt_status_get)     ( void);
    UINT8           ( *phix_mvb_device_addr_get) ( UINT16 *);
    INT16           ( *phi_timestamp_enable)    ( void);
    INT16           ( *phi_timestamp_disable)   ( void);
    INT16           ( *phi_timestamp)           ( UINT32 *);
    void            ( *phi_error_led_on)        ( void );
    void            ( *phi_error_led_off)       ( void );
    INT16           ( *phi_isr_attach)          ( UINT16 int_nr,
                                                  VOIDFUNCPTR  int_subroutine,
                                                  INT32        int_para);
    void            ( *phi_batt_use)            ( BOOL);
    ULONG           ( *phi_flash_base_get)      ( void );
    ULONG           ( *phi_flash_size_get)      ( void );
    UINT16          ( *phi_reset_reason_get)    ( void );
    void            ( *phi_stall_set)           ( BOOL );

} VCU_ICT;


/*****************************************************************************
*   GLOBAL FUNCTIONS
*/

extern INT16    _hi_temp_status_get ( INT16 *, UINT16 * );
extern INT16    _hi_batt_status_get ( void );
extern void     _hi_batt_use(  BOOL flag );

extern UINT8    _hix_mvb_device_addr_get (UINT16 *);

extern INT16    _hi_timestamp_enable (void);
extern INT16    _hi_timestamp_disable (void);
extern INT16    _hi_timestamp (UINT32 *);

extern void     _hi_error_led_on(void);
extern void     _hi_error_led_off(void);

extern INT16    _hi_isr_attach ( UINT16, VOIDFUNCPTR, INT32);

extern UINT16   _hi_reset_reason_get( void );
extern ULONG    _hi_flash_base_get( void );
extern ULONG    _hi_flash_size_get( void );
extern void     _hi_stall_set(  BOOL activate );

extern UINT16   _hi_ser_eepr_read  (UINT16, UINT16*, UINT16, UINT16);
extern UINT16   _hi_ser_eepr_write (UINT16, UINT16*, UINT16, UINT16);

/* Define location for indirect call */
#define VCU_IND_CALL     (*(VCU_ICT * *) VCU_ADR_TABLE)

#ifdef O_DC             /* API - functions direct call */
                /* --------------------------- */

  #define hi_temp_status_get            _hi_temp_status_get
  #define hi_batt_status_get            _hi_batt_status_get
  #define hi_batt_use                   _hi_batt_use
  #define hix_mvb_device_addr_get       _hix_mvb_device_addr_get
  #define hi_timestamp_enable           _hi_timestamp_enable
  #define hi_timestamp_disable          _hi_timestamp_disable
  #define hi_timestamp                  _hi_timestamp
  #define hi_isr_attach                 _hi_isr_attach
  #define hi_error_led_on               _hi_error_led_on
  #define hi_error_led_off              _hi_error_led_off
#else                   /* API - functions indirect call */
                /* ----------------------------- */

  #define hi_temp_status_get        (* (VCU_IND_CALL->phi_temp_status_get))
  #define hi_batt_status_get        (* (VCU_IND_CALL->phi_batt_status_get))
  #define hi_batt_use               (* (VCU_IND_CALL->phi_batt_use))
  #define hix_mvb_device_addr_get   (* (VCU_IND_CALL->phix_mvb_device_addr_get))
  #define hi_timestamp_enable       (* (VCU_IND_CALL->phi_timestamp_enable))
  #define hi_timestamp_disable      (* (VCU_IND_CALL->phi_timestamp_disable))
  #define hi_timestamp              (* (VCU_IND_CALL->phi_timestamp))
  #define hi_isr_attach             (* (VCU_IND_CALL->phi_isr_attach))
  #define hi_error_led_on           (* (VCU_IND_CALL->phi_error_led_on))
  #define hi_error_led_off          (* (VCU_IND_CALL->phi_error_led_off))
#endif


#ifdef __cplusplus
}
#endif

#endif /* RTS_VCU_H */
