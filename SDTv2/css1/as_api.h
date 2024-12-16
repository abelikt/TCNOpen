/* $Header: /CSS/Code/RTS/COMMON/api/as_api.h 52    07-03-12 12:40 Bjarne Jensen $
******************************************************************************
*  COPYRIGHT    : (c) 1997 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : as_api.h
*
*  ABSTRACT     : Application Structures
*                 Defines the format of a CSS application.
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/as_api.h $
*  
*  52    07-03-12 12:40 Bjarne Jensen
*  Added two more memory attributes.
*  
*  51    07-01-19 9:33 Bjarne Jensen
*  Fixed bug in AS_APP_PTR_TAB.
*  
*  50    07-01-17 16:16 Bjarne Jensen
*  Added AS_MEM_ATTR defines for attributes in AS_MEMORY_USE.
*  
*  49    07-01-12 17:30 Bjarne Jensen
*  Added the mem service.
*  
*  48    06-06-15 11:41 Jrehnman
*  Service version 1.5.1
*  
*  47    02-10-24 14:26 Thomas Clevström
*  Service version 1.5
*  
*  46    02-10-01 5:20p Christer Olsson
*  Changed AS_DM_INIT to AS_DR_INIT in AS_DEV_PTR_TAB
*  
*  45    02-09-24 3:18p Christer Olsson
*  Changed AS_DR_INIT for compability with BE
*  
*  44    02-09-24 1:07p Christer Olsson
*  Added AS_DR_INIT for compability with BE
*  
*  43    02-09-23 3:41p Christer Olsson
*  
*  42    02-09-23 3:24p Christer Olsson
*  Changed for new Data Recorder in CSS 1.11
*  
*  41    02-09-17 17:44 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  40    02-02-14 10:23 Thomas Clevström
*  Removed the parameter AS_DEVICE_CONFIG:mon_priority
*  (Was introduced due to MR-060063ORI)
*  Replaced by the new Basic solution for CSS Task handling
*  
*  39    01-12-18 10:42 Lars Högberg
*  Added more defines for wdog_flag. Refer to concept 3EST000202-4053, CSS
*  task handling changes. Solution of CSS-project SPR 132.
*  
*  38    01-11-16 4:30p Christer Olsson
*  3EST126-261_1,changed structure OS_HW_INFO_UNIT.
*  
*  37    01-11-02 4:18p Christer Olsson
*  3EST126-261_1,changed structures for HW revision.
*  
*  36    01-10-26 15:41 Lars Högberg
*  3EST126-261_1, included functions for SW version and HW revision.
*  
*  35    01-10-26 14:57 Thomas Clevström
*  Prepared for CA-monitor: MD function configuration in AS_DEVICE_INIT:
*  mon_ca_md_fct
*  NCR -GEROLD HERES90001
*  
*  34    01-10-12 15:02 Lars Högberg
*  Added define for Bootcode Extension applications
*  
*  33    01-10-07 16:28 Thomas Clevström
*  Fixed priority problem according to MR-060063ORI:
*  RTS_Mon task priority selectable by a new field in AS_DEVICE_INIT.
*  Default is changed from 59 to 250
*  MAGIC_WORD "AS-1105". AS_VER 1.4.0
*  
*  32    01-10-04 17:48 Thomas Clevström
*  Untabify.
*  
*  31    01-04-18 17:50 Niclas Ericsson
*  Removed 2 API functions and added 1.
*  
*  30    01-04-05 8:30 Lars Högberg
*  Extended the AS_DEVICE_INIT structure with wdog_action, extended API
*  with new functions to access information in the Device- and Application
*  Configuration NCR -LARS HÖGBERG10007.
*  
*  29    01-02-21 19:12 Niclas Ericsson
*  Extended AS_DR_INIT to support NCR -LARS HÖGBERG00003
*  Added padding to AS_DM_INIT and AS_TIME_SYNC_INIT
*  
*  28    99-12-10 17:18 Lars Högberg
*  Service version updated. Magic word changed due to AS extensions. Added
*  str AS_DEV_INFO, and made other changes to handle NCR ALEXANDER
*  BAUER90001.
*  
*  27    99-06-28 11:42 Anders Öhlander
*  Change AS_TS_ to AS_TIME_SYNC_.
*  
*  26    99-06-23 16:10 Lars Högberg
*  Service version updated. Magic word changed due to AS extensions. Added
*  constants for Time Sync. and MVB bridge. Extended AS_MD_INIT, added new
*  struct AS_MVB_HW_CONFIG, changed and extended AS_DEVICE_INIT for self
*  tests, MVB bridge and memory leak detection parameters 
*  
*  25    99-06-16 19:51 Stefan Modin
*  Changed structures AS_DEVICE_INIT and AS_MEM_CHECK and added flags for
*  memory self-tests.
*  
*  24    6/15/99 8:42a Anders Öhlander
*  Added functionallity for the TimeSync services.
*  
*  23    98-06-30 13:19 Martin Gisbert
*  STR_AS_DR_INIT changed according to the new data recorder. The
*  structure contains only the max.number of instances max_n_instance
*  
*  22    98-01-07 11:05 Anders Wallin
*  as_queryinterface changed to as_library_connect
*
*  21    97-12-08 16:14 Anders Wallin
*  Version naming changed
*
*  20    97-12-08 15:55 Anders Wallin
*  AS api added
*
*  19    97-10-08 8:10 Anders Öhlander
*  Added new types for the DSP and FPGA applications.
*
*  18    97-09-12 8:38 Anders Wallin
*  ae added in as_device_init
*
*  17    97-09-12 8:34 Anders Wallin
*  ae added in as_device_init
*
*  16    97-09-12 8:17 Anders Wallin
*  const deleted
*
*  15    97-09-11 16:02 Anders Wallin
*  const added
*
*  14    97-06-27 9.23 Anders Wallin
*  Header added
*
*  13    97-05-20 12:19 Anders Öhlander
*  Deleted the DEVICE_CONFIG_ADRS for all devices.
*
*  12    97-03-12 8.16 Anders Wallin
*  const decl. aded to as_device_config
*
*  11    97-01-09 13:12 Peter Koerner
*
*  10    97-01-09 11:23 Peter Koerner
*
*  9     96-12-18 9.17 Anders Wallin
*  AS_SD_NOT_VITAL added
*
*  8     96-12-12 11.04 Anders Wallin
*  Changed som dd and dr items
*
*  7     96-12-11 14:25 Dev Pradhan
*  Data recorder and Data Dictionary added
*
*  6     96-12-09 16.36 Anders Wallin
*  including tcn_ini.h
*
*  5     96-11-29 11.03 Anders Wallin
*  Include of rts.h removed
*
*  4     96-11-26 21:18 Dev Pradhan
*  Added the application structures for the Dynamic Memory Manager
*
*  3     96-11-15 10.51 Anders Wallin
*  Added DC-address for comc
*
*  2     96-10-31 10.29 Anders Wallin
*
*  1     15.10.96 14:59 Siegenthaler
*  Replaces as_sys.h
*
******************************************************************************/


#ifndef _AS_API_H
#define _AS_API_H

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
*   INCLUDES
*/
#include "tcn_ini.h"
#include "mem_api.h"

/*******************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_AS
#define AS_VER      1
#define AS_REL      6
#define AS_UPD      0

#define AS_MAGIC_WORD       "AS-1107"


/*------------------------------------------------------------------------------
*   Type of an application. Is used during boot sequence to check
*   application dependencies. Following types are defined:
*/

#define AS_TYPE_OS          0           /* Application belongs to OS itself,
                                           e.g. the StDL has this type. */
#define AS_TYPE_AP_CFG      1           /* Application is used by the OS to
                                           configure the target system with
                                           all needed applications. */
#define AS_TYPE_AP_C        2           /* Application is written in the
                                           programming language 'C'. */
#define AS_TYPE_AP_TOOL     3           /* Application is generated by a tool.*/

#define AS_TYPE_AP_DSP      4           /* No application , DSP program code.*/

#define AS_TYPE_AP_FPGA     5           /* No application , FPGA program code.*/

#define AS_TYPE_AP_BE       6           /* No application , Bootcode Extension.*/

/*------------------------------------------------------------------------------
*   Device configuration constants used in AS_DEVICE_INIT
*/

#define AS_WDOG_OFF         0xFFFF      /* The task does not use the watchdog   */
#define AS_WDOG_ALL_OFF     0           /* No deadlines will be supervised      */
#define AS_WDOG_ALL_ON      1           /* Deadline supervision of cyclic tasks */
#define AS_WDOG_HW_ON       2           /* The HW WDOG will be trigged if all supervised cyclic tasks has executed */
#define AS_WDOG_HW_APP      3           /* The triggering of the HW WDOG is up to the application, os_hi_wdog_trigger() */
#define AS_WDOG_RESCHEDULE	4           /* Tasks that has missed the dealine will be imidiatelly rescheduled */

#define AS_CHKSUM_OFF       0           /* RTS does not calculate checksum of
                                           applications. */
#define AS_CHKSUM_ON        1           /* RTS does calculate checksum of
                                           applications during start-up. */
#define AS_CHKSUM_RT_ON     2           /* RTS does calculate checksum of
                                           applications during run-time. */

#define AS_RAM_TEST_OFF     0           /* RTS performs no RAM test during
                                           start-up or runtime. */
#define AS_RAM_TEST_ON      1           /* RTS performs RAM test during
                                           start-up and run-time. */

/* Action codes - Action to take when a self test error is detected */
#define AS_ST_CONT          0           /* RTS will continue */
#define AS_ST_RUN           1           /* RTS will reset with reason code
                                           RESET_RUN */
#define AS_ST_IDLE          2           /* RTS will reset with reason code
                                           RESET_IDLE */
#define AS_ST_DL            3           /* RTS will reset with reason code
                                           RESET_DOWNLOAD */
#define AS_ST_ERR           5           /* RTS will reset with reason code
                                           RESET_ERROR */
#define AS_ST_TEST          6           /* RTS will reset with reason code
                                           RESET_TEST */

#define AS_MVBC_IDC_A       0           /* MVBC channel A */
#define AS_MVBC_IDC_B       1           /* MVBC channel B                   */
#define AS_MVBC_IDC_AB      2           /* MVBC channel A and B             */
#define AS_MVBC_IDC_FOPBI   3           /* Fiber optical channel            */

#define AS_HW_MVB_2_NONE    0           /* No secondary MVB on target       */
#define AS_HW_MVB_2_KM02    1           /* PBI board KM02 used as secondary MVB  */
#define AS_HW_MVB_2_KF02    2           /* PBI board KF02 used as secondary MVB  */

#define AS_CPU_LOAD_STOP    0           /* Does not start the cpu-load measuring */
#define AS_CPU_LOAD_START   1           /* Start the cpu-load measuring */

#define AS_TIME_SYNC_NOT_AVAILABLE 0

#define AS_MT_NOT_AVAILABLE 0

/*------------------------------------------------------------------------------
*   Memory check configuration constants used in AS_MEM_CHECK
*/

/* Flag values, specifying the contents of a RAM area after the start-up tests */
#define AS_MEM_DONT_CARE    0           /* Don't care - the contents can be
                                           destroyed */
#define AS_MEM_RESTORE      1           /* Restore the contents */
#define AS_MEM_FILL         2           /* Fill the memory with a pattern */

/* Flag values for controlling if and when a RAM area shall be tested */
#define AS_MEM_CHECK_OFF    0           /* RTS does not check the RAM area at
                                           start-up or runtime */
#define AS_MEM_CHECK_ON     1           /* RTS checks the RAM area at start-up */
#define AS_MEM_CHECK_RT_ON  2           /* RTS checks the RAM area at runtime */

/*-----------------------------------------------------------------------------
*   Memory service attribute values.
*   This is just a rename of the "real" attribute names in the memory service.
*/
#define AS_MEM_ATTR_STD     MEM_ATTR_STD
#define AS_MEM_ATTR_NVM     MEM_ATTR_NVM
#define AS_MEM_ATTR_TRAM    MEM_ATTR_TRAM
#define AS_MEM_ATTR_PBI     MEM_ATTR_PBI
#define AS_MEM_ATTR_FAST    MEM_ATTR_FAST
#define AS_MEM_ATTR_DSP     MEM_ATTR_DSP
#define AS_MEM_ATTR_QUICK   MEM_ATTR_QUICK
#define AS_MEM_ATTR_AMS     MEM_ATTR_AMS

/*-----------------------------------------------------------------------------
*   Task configuration constants used in AS_TASK_CONFIG
*/
                                        /* Task types                       */
#define AS_TT_INIT          0           /* Initialisation tasks             */
#define AS_TT_CYCL          1           /* Cyclic task                      */
#define AS_TT_EVNT          2           /* Event driven task                */
#define AS_TT_ISR           3           /* Interrupt subroutine             */
#define AS_TT_ITASK         4           /* Interrupt task                   */
#define AS_TT_PD            5           /* Process Data task (Subscribe)    */
#define AS_TT_SD            6           /* Shutdown task                    */
#define AS_TT_SP            7           /* Special task                     */
#define AS_TT_BGND          8           /* Background task                  */
                                        /* Task priority range */
#define AS_PRI_HIGH_MAX     10          /* Highest prio for applications of the
                                           high prio range. */
#define AS_PRI_HIGH_MIN     39          /* Lowest prio for applications of the
                                           high prio range. */
#define AS_PRI_LOW_MAX      60          /* Highest prio for applications of the
                                           low prio range. */
#define AS_PRI_LOW_MIN      249         /* Lowest prio for applications of the
                                           low prio range. */

#define AS_SD_NOT_VITAL     0xff        /* Application not vital */

                                        /* Task start address type */
#define AS_AT_IND           0           /* Indirect call (address, where OS can
                                           find the task_start address) */
#define AS_AT_DIR           1           /* Direct call (task_start address) */


/*-----------------------------------------------------------------------------
*   Dynamic Memory Manager constants used in AS_DM_INIT
*/
#define AS_DM_PART          1           /* Memory partition */


/*-----------------------------------------------------------------------------
*   Time Synchronization constants used in AS_TIME_SYNC_INIT
*/
#define AS_TIME_SYNC_NONE          0           /* RTS does not use the time synchronization*/
#define AS_TIME_SYNC_MASTER        1           /* This device is the MVB time master.*/
#define AS_TIME_SYNC_SLAVE         2           /* This device is a MVB time slave.*/

#define AS_TIME_SYNC_LOCAL         0           /* local time on the time master used as global time*/
#define AS_TIME_SYNC_RTC           1           /* RTC on the time master used as global time.*/
#define AS_TIME_SYNC_API           2           /* Input from API-function used as global time.*/


/*-----------------------------------------------------------------------------
*   Data Dictionary constants used in AS_DATA_DICTIONARY
*/
#define     AS_MAX_SIGNAL_LENGTH   26

#define     AS_DD_UINT_8_TYPE      0
#define     AS_DD_UINT_16_TYPE     1
#define     AS_DD_UINT_32_TYPE     2
#define     AS_DD_INT_8_TYPE       3
#define     AS_DD_INT_16_TYPE      4
#define     AS_DD_INT_32_TYPE      5


/*******************************************************************************
*   TYPEDEFS
*/
/* -------------------------------------- */
/*   for version and revision information */
/* -------------------------------------- */
/*   unit level                           */
typedef struct STR_OS_HW_INFO_UNIT
{
    CHAR unit_name[29];
    CHAR unit[11];
    CHAR unit_article_number[16];
    CHAR unit_delivery_date[7];
    CHAR unit_delivered_revision[3];
    CHAR unit_present_revision[3];
    CHAR unit_rev_date[7];
    CHAR unit_made_latest_rev[7];
    CHAR unit_series_no[21];
} OS_HW_INFO_UNIT;

/*   board level                          */
typedef struct STR_OS_HW_INFO_BOARD
{
    CHAR board_name[9];
    CHAR board_article_number[16];
    CHAR board_delivery_date[7];
    CHAR board_delivered_revision[3];
    CHAR board_present_revision[3];
    CHAR board_rev_date[7];
    CHAR board_made_latest_rev[7];
    CHAR board_series_no[13];
    CHAR padding[3];
} OS_HW_INFO_BOARD;


/*------------------------------------------------------------------------------
*   Entry Point
*/
typedef VERSION_INFO AS_VERSION;

typedef VM_HEADER    AS_DLU_HEADER;

typedef struct STR_AS_CHECK
{
    DWORD               mvb_time_stamp;
    AS_VERSION          mvb_version;
    CHAR                hw_config[13];
    CHAR                device_name[9];
    BYTE                padding[2];
} AS_CHECK;

/* Forward declarations */
struct STR_AS_DEV_ENTRY;
struct STR_AS_APP_ENTRY;


/*------------------------------------------------------------------------------
*   Device Configuration Structures
*/

typedef struct STR_AS_APPLICATION
{
    struct STR_AS_APP_ENTRY* p_app;
    CHAR                exp_app_name[16];
    AS_VERSION          exp_app_version;
} AS_APPLICATION;


typedef struct STR_AS_TS_INIT
{
    DWORD               p_ts_cfg;
    DWORD               padding;
} AS_TS_INIT;


typedef struct STR_AS_MD_INIT
{
    DWORD               p_dir_entries;
    WORD                nr_dir_entries;
    DWORD               reserved;
    WORD                max_call_number;
    WORD                max_inst_number;
    WORD                default_reply_tmo;
    WORD                my_credit;
    WORD                reserved2;
    WORD                operation_mode;
    WORD                bridging_mode;
    DWORD               p_station_dir_entries;
    WORD                nr_station_dir_entries;
    WORD                size_station_dir_entries;
    DWORD               p_group_dir_entries;
    WORD                nr_group_dir_entries;
    WORD                size_group_dir_entries;
    DWORD               node_dir_entries;
    WORD                nr_node_dir_entries;
    WORD                size_node_dir_entries;
    DWORD               p_reserved;
    WORD                nr_reserved;
    WORD                size_reserved;
} AS_MD_INIT;


typedef struct STR_AS_BA_INIT
{
    DWORD               p_config_list;
    AS_VERSION          config_version;
    DWORD               config_date;
    CHAR                config_name[12];
} AS_BA_INIT;


typedef struct STR_AS_MVB_HW_CONFIG
{
    BYTE                mvbc_idc;
    BYTE                mvb_2_hw_type;
    BYTE                mvb_2_bus_id;
    BYTE                mvb_2_idc;
    BYTE                padding[8];
} AS_MVB_HW_CONFIG;


typedef struct STR_AS_DEVICE_INIT
{
    WORD                base_cycle_time;
    WORD                reset_counter;
    BYTE                wdog_flag;
    BYTE                checksum_flag;
    BYTE                ram_test_flag;
    BYTE                cpu_load_meas;
    CHAR*               io_device;
    CHAR*               mon_device;
    DWORD*              appl_event_address;
    DWORD               appl_event_size;
    BYTE                self_test_action_init;
    BYTE                self_test_action_rt;
    WORD                reserved;
    AS_MVB_HW_CONFIG    mvb_hw_config;
    DWORD               memory_log_size;
    BYTE                memory_log_flag;
    BYTE                memory_log_behaviour;
    BYTE                memory_log_output;
    BYTE                wdog_action;
    BYTE                mon_ca_md_fct;        /*AS-1105*/
    BYTE                padding[3];
} AS_DEVICE_INIT;


typedef struct STR_AS_MEM_CHECK
{
    BYTE*               p_check_mem;
    DWORD               size;
    BYTE                fill_flag;
    BYTE                fill_pattern;
    BYTE                mem_test_flag;
    BYTE                padding;
} AS_MEM_CHECK;


typedef struct STR_AS_DM_INIT
{
    DWORD*              p_mem_start;
    DWORD               size;
    BYTE                type;
    BYTE                identity;
    WORD                padding;
} AS_DM_INIT;


typedef struct STR_AS_DR_INIT
{
    UINT8               dummy_1;
    UINT8               dummy_2;
    UINT16              padding;
} AS_DR_INIT;


typedef struct STR_AS_DAYLIGHT
{
    UINT16              DST_mounth;
    UINT16              DST_day;
    INT16               DST_week;
    UINT16              DST_time_hh;
    UINT16              DST_time_mm;
    INT16               DST_diff;
    UINT16              ST_mounth;
    UINT16              ST_day;
    INT16               ST_week;
    UINT16              ST_time_hh;
    UINT16              ST_time_mm;
    INT16               ST_diff;
} AS_DAYLIGHT;

typedef struct STR_AS_TIME_SYNC_INIT
{
    UINT16              type;
    UINT16              traffic_store_id;
    UINT16              port;
    UINT16              cycle_time;
    UINT16              time_source;
    INT16               time_zone;
    UINT16              drift_zone;
    AS_DAYLIGHT         daylight_alg;
    UINT16              padding;
} AS_TIME_SYNC_INIT;

typedef struct STR_AS_DEV_INFO
{
    WORD                dev_address;
    WORD                index_TS;
    WORD                index_MD;
    WORD                reserved;
} AS_DEV_INFO;


typedef struct STR_AS_DEV_PTR_TAB
{
    AS_APPLICATION*     p_application;
    WORD                nr_application;
    WORD                size_application;
    AS_TS_INIT*         p_ts_init;
    WORD                nr_ts_init;
    WORD                size_ts_init;
    AS_MD_INIT*         p_md_init;
    WORD                nr_md_init;
    WORD                size_md_init;
    AS_BA_INIT*         p_ba_init;
    WORD                nr_ba_init;
    WORD                size_ba_init;
    AS_DEVICE_INIT*     p_device_init;
    WORD                nr_device_init;
    WORD                size_device_init;
    AS_MEM_CHECK*       p_mem_check;
    WORD                nr_mem_check;
    WORD                size_mem_check;
    AS_DM_INIT*         p_dm_init;
    WORD                nr_dm_init;
    WORD                size_dm_init;
    AS_DR_INIT*         p_spare_8;
    WORD                nr_spare_8;
    WORD                size_spare_8;
    AS_TIME_SYNC_INIT*  p_time_sync_init;
    WORD                nr_time_sync_init;
    WORD                size_time_sync_init;
    AS_DEV_INFO*        p_dev_info;
    WORD                nr_dev_info;
    WORD                size_dev_info;
} AS_DEV_PTR_TAB;


typedef struct STR_AS_DEV_ENTRY
{
    AS_DLU_HEADER       header;
    AS_CHECK            check;
    AS_DEV_PTR_TAB*     p_pointer_table;
    WORD                nr_pointer_table;
    WORD                size_pointer_table;
} AS_DEV_ENTRY;



/*------------------------------------------------------------------------------
*   Application Structures
*/

typedef struct STR_AS_DEPENDENCIES
{
    struct STR_AS_APP_ENTRY*    p_entry;
    CHAR                        exp_name[16];
    AS_VERSION                  exp_version;
} AS_DEPENDENCIES;

typedef void AS_TASK_FUNCTION (DWORD argc, CHAR* argv[] );

typedef struct STR_AS_TASK_CONFIG
{
    AS_TASK_FUNCTION*   p_task_init;
    AS_TASK_FUNCTION*   p_task_body;
    CHAR**              appl_argv;
    DWORD               appl_argc;
    WORD                stack_size;
    WORD                int_nr;
    CHAR                task_name[16];
    WORD                task_cycle;
    WORD                task_delay;
    WORD                wdog_delay;
    BYTE                task_type;
    BYTE                task_priority;
    BYTE                init_addr_type;
    BYTE                body_addr_type;
    WORD                expected_dev_addr;
    BYTE                padding[12];
} AS_TASK_CONFIG;


typedef struct  STR_AS_DYN_MEMORY
{
    BYTE*               p_free_mem;
    DWORD               size;
} AS_DYN_MEMORY;


typedef struct STR_AS_COPY_LIST
{
    BYTE*               p_target;
    BYTE*               p_source;
    DWORD               size;
} AS_COPY_LIST;


typedef struct STR_AS_INIT_DATA
{
    BYTE*               p_target;
    DWORD               size;
    WORD                value;
    WORD                reserved;
} AS_INIT_DATA;


typedef struct STR_AS_APPL_DATA
{
    DWORD               p_appl_data_table;
    WORD                nr_appl_data_table;
    WORD                size_appl_data_table;
} AS_APPL_DATA;


typedef struct STR_AS_DATA_DICTIONARY
{
    BYTE                signal_name[AS_MAX_SIGNAL_LENGTH];
    DWORD*              signal_addr;
    BYTE                signal_type;
} AS_DATA_DICTIONARY;


typedef struct STR_AS_MEMORY_USE
{
    UINT32              id;
    DWORD*              p_target;
    UINT32              size;
    UINT32              flags;
} AS_MEMORY_USE;



typedef struct STR_AS_APP_PTR_TAB
{
    AS_DEPENDENCIES*      p_dependencies;
    WORD                  nr_dependencies;
    WORD                  size_dependencies;
    AS_TASK_CONFIG*       p_task_config;
    WORD                  nr_task_config;
    WORD                  size_task_config;
    AS_DYN_MEMORY*        p_dyn_memory;
    WORD                  nr_dyn_memory;
    WORD                  size_dyn_memory;
    AS_COPY_LIST*         p_copy_list;
    WORD                  nr_copy_list;
    WORD                  size_copy_list;
    AS_INIT_DATA*         p_init_data;
    WORD                  nr_init_data;
    WORD                  size_init_data;
    AS_APPL_DATA*         p_appl_data;
    WORD                  nr_appl_data;
    WORD                  size_appl_data;
    AS_DATA_DICTIONARY*   p_data_dictionary;
    WORD                  nr_data_dictionary;
    WORD                  size_data_dictionary;
    AS_MEMORY_USE*        p_memory_use;           /*AS-1107*/
    WORD                  nr_memory_use;          /*AS-1107*/
    WORD                  size_memory_use;        /*AS-1107*/
} AS_APP_PTR_TAB;

typedef struct STR_AS_APP_ENTRY
{
    AS_DLU_HEADER       header;
    AS_CHECK            check;
    AS_APP_PTR_TAB*     p_pointer_table;
    WORD                nr_pointer_table;
    WORD                size_pointer_table;
} AS_APP_ENTRY;


/*****************************************************************************/
typedef struct
{
    VERSION_INFO  as_info;
    INT16         ( *pas_library_connect) ( char*,   AS_VERSION, void** );
    INT16         ( *pas_region_valid)    ( UINT32,  UINT32,     BOOL );
    INT16         ( *pas_task_period)     ( char*,   UINT16*,    UINT16* );
    INT16         ( *pas_get_device_configuration_address)
                                          ( AS_DEV_ENTRY** );
    INT16         ( *pas_get_monitor_channel)
                                          ( char** );
    INT16         ( *pas_get_application_address)
                                          ( AS_TASK_FUNCTION*, AS_APP_ENTRY** );
	INT16         ( *pas_as_sw_info_get)  ( UINT16            list_index,
	                                        AS_DLU_HEADER*    sw_info,
										    UINT16*           p_nr_sw_info);
	INT16         ( *pas_hi_info_get)     ( UINT16            list_index,
	                                        OS_HW_INFO_UNIT*  p_hw_info_unit,
										    OS_HW_INFO_BOARD* p_hw_info_board,
										    UINT16*           nr_hw_info );
} AS_STR_ICT;


/*****************************************************************************
*   GLOBALS
*/
extern const AS_DEV_ENTRY     as_device_config;


/*****************************************************************************
*   GLOBAL FUNCTIONS
*/
INT16 as_library_connect( char       app_name[],
                          AS_VERSION version,
                          void**     pp_ict );

INT16 as_region_valid   ( UINT32     start,
                          UINT32     end, 
                          BOOL       readonly);

INT16 as_task_period    ( char       task_name[],
                          UINT16*    configurated_time, 
                          UINT16*    calculated_time  );

INT16 as_get_device_configuration_address    
                        ( AS_DEV_ENTRY** pp_device_configuration_address );

INT16 as_get_monitor_channel
                        ( char*      monitor_channel[]  );

INT16 as_get_application_address    
                        ( AS_TASK_FUNCTION* p_task_body,
                          AS_APP_ENTRY** pp_application_address );

INT16 hi_info_get       ( UINT16            list_index,
	                      OS_HW_INFO_UNIT*  p_hw_info_unit,
						  OS_HW_INFO_BOARD* p_hw_info_board,
						  UINT16*           nr_hw_info );

INT16 as_sw_info_get    ( UINT16            list_index,
	                      AS_DLU_HEADER*    p_sw_info,
						  UINT16*           nr_sw_info );

/* Define location for indirect call */
#define AS_IND_CALL     (*(AS_STR_ICT * *) AS_ADR_TABLE)

#ifdef O_DC
    #define os_as_library_connect                       as_library_connect
    #define os_as_region_valid                          as_region_valid
    #define os_as_task_period                           as_task_period
    #define os_as_get_device_configuration_address      as_get_device_configuration_address
    #define os_as_get_monitor_channel                   as_get_monitor_channel
    #define os_as_get_application_address               as_get_application_address
    #define hi_info_get                                 hi_info_get
    #define os_as_sw_info_get                           as_sw_info_get
#else
    #define os_as_library_connect                      (* (AS_IND_CALL->pas_library_connect))
    #define os_as_region_valid                         (* (AS_IND_CALL->pas_region_valid))
    #define os_as_task_period                          (* (AS_IND_CALL->pas_task_period))
    #define os_as_get_device_configuration_address     (* (AS_IND_CALL->pas_get_device_configuration_address))
    #define os_as_get_monitor_channel                  (* (AS_IND_CALL->pas_get_monitor_channel))
    #define os_as_get_application_address              (* (AS_IND_CALL->pas_get_application_address))
    #define hi_info_get                                (* (AS_IND_CALL->pas_hi_info_get            ))
    #define os_as_sw_info_get                          (* (AS_IND_CALL->pas_as_sw_info_get         ))
#endif


#ifdef __cplusplus
}
#endif

#endif /* _AS_API_H */
