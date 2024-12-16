/* $Header: /CSS/Code/RTS/COMMON/api/tcn.h 7     06-06-15 11:46 Jrehnman $
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : tcn_api.h
*
*  ABSTRACT     : TCN service: Types, constants and prototypes
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/tcn.h $
*  
*  7     06-06-15 11:46 Jrehnman
*  New tcn.h for TCN 1.6.0.0
******************************************************************************/

/****************************************************************************
*                                                                           *
* Property of   : Bombardier Transportation GmbH                            *
*                                                                           *
* Copyright     : (c) 2005 Bombardier Transportation GmbH                   *
*****************************************************************************
*                                                                           *
* Project       : TCN - Train Communication Network                         *
*                                                                           *
* Subproject    : RTP - Real-Time Protocols                                 *
*                                                                           *
*****************************************************************************
*                                                                           *
* Module        : tcn.h                                                     *
*                                                                           *
* Document      : -                                                         *
*                                                                           *
* Abstract      : Definitions of types, constants and prototypes            *
*                                                                           *
* Remarks       : Common include file for TCN                               *
*                                                                           *
* Dependencies  : -                                                         *
*                                                                           *
* Accepted      : -                                                         *
*                                                                           *
*****************************************************************************
*                                                                           *
*       Version Identification:                                             *
*       =======================                                             *
*                                                                           *
*       Version                        Product                              *
*       -------                        -------                              *
*       1.6.x.x                      TCN (total product)                    *
*                                                                           *
****************************************************************************/

   
   
/****************************************************************************
*****************************************************************************
*                                                                           *
*               TCN APPLICATION MESSAGE INTERFACE                           *
*                                                                           *
*****************************************************************************
****************************************************************************/
   

#ifndef     AM_SYS_H
#define     AM_SYS_H

#ifdef __cplusplus
extern "C" {
#endif

#if (defined (__TURBOC__) || defined (__BORLANDC__))
#define HUGE huge
#else
#define HUGE
#endif

/*
*****************************************
* basic constants, types and functions  *
*****************************************
*/

typedef unsigned long  CARDINAL32;

/*
*****************************************
* global constants                      *
*****************************************
*/


/* maximal number of simultaneous send connections              */
/* required if max_call_number specified in am_announce_device  */
/* is to high                                                   */
#define AM_MAX_SEND_CONN               30   /* limited because of memory and */
#define AM_MIN_SEND_CONN               2    /* FL , minimal configuration  */
                                            /* for service                 */

#define am_buffer_free( addr, size)     pi_free(addr)

#define AM_MAX_CREDIT     7      /* maximal credit for message transmission */

#define AM_ROUTER_FCT  (unsigned char)251
        /* 251 decimal, this function is always
           located on the gateway */

#define AM_SERVICE_FCT (unsigned char)253
        /* 253 decimal, service replier function,
           this is the only replier function which
        may use physical addressing */

#define AM_MANAGER_FCT (unsigned char)254
        /* 254 decimal, service caller function,
           this is the only caller function which
           may use physical addressing */

#define AM_UNKNOWN_DEVICE (unsigned char) 255

#define AM_SAME_DEVICE    (unsigned char) 0
        /* my generic device address, myself for every device */

#define AM_PHYS_ADDR      (unsigned char) 0x80
        /* physical addressing bit in vehicles */

#define AM_SAME_VEHICLE   (unsigned char) 0
        /* my generic vehicle, myself for every vehicle */

#define AM_GROUP_BIT      (unsigned char) 0x40
        /* vehicles with bit 6 set are groups, multicast */

#define AM_ALL_VEH        (unsigned char) 0xFF
        /* this vehicle group contains all vehicles, broadcast */

#define AM_ANY_TC         (unsigned char) 0
        /* pass-all value for topo count, is always valid */

#define AM_MAX_TC         (unsigned char) 0x3F
        /* maximal value for 6-bit topo counter */

#define AM_VALID_TC_BIT   (unsigned char) 0x40
        /* valid topo counter bit */

#define AM_PACK_CODE_27BYTE   0 /* Code for 27 Byte packets */

#define AM_PACK_CODE_128BYTE 15 /* Code for 128 Byte packets */

#define AM_MAX_NODES 62

/* error code definitions: -------------------------------------------- */
#define AM_MAX_ERR   31

/* The following error codes are defined for the type 'AM_RESULT'.
   Application specific error codes must be higher than 'AM_MAX_ERR'. */
#define AM_OK                    0
#define AM_FAILURE               1
#define AM_BUS_ERR               2
#define AM_REM_CONN_OVF          3
#define AM_CONN_TMO_ERR          4
#define AM_SEND_TMO_ERR          5
#define AM_REPLY_TMO_ERR         6
#define AM_ALIVE_TMO_ERR         7
#define AM_NO_LOC_MEM_ERR        8
#define AM_NO_REM_MEM_ERR        9
#define AM_REM_CANC_ERR         10
#define AM_ALREADY_USED         11
#define AM_ADDR_FMT_ERR         12
#define AM_NO_REPLY_EXP_ERR     13
#define AM_NR_OF_CALLS_OVF      14
#define AM_REPLY_LEN_OVF        15
#define AM_DUPL_LINK_ERR        16
#define AM_MY_DEV_UNKNOWN_ERR   17
#define AM_NO_READY_INST_ERR    18
#define AM_NR_OF_INST_OVF       19
#define AM_CALL_LEN_OVF         20
#define AM_UNKNOWN_DEST_ERR     21
#define AM_INAUG_ERR            22
#define AM_TRY_LATER_ERR        23
#define AM_DEST_NOT_REG_ERR     24
#define AM_GW_DEST_NOT_REG_ERR  25
#define AM_GW_SRC_NOT_REG_ERR   26
#define AM_REPEAT_TMO_ERR       27


  /* constants for am_get_status */

#define AM_NO_RESET             0x0000
#define AM_RECV_ACTIVE          0x0001
#define AM_SEND_ACTIVE          0x0002
#define AM_RECV_OVF             0x0004
#define AM_IRQ_WITHOUT_MESSAGE  0x0008
#define AM_INDICATE_MESSAGE     0x0010

  /* some special bus numbers for the stadi directory */

#define     AM_UNKNOWN_BUS_NR   255
#define     AM_MY_VB_NR         254   /* my own VB if there is just 1 VB  */
#define     AM_TB_NR              1   /* this is always the bus_nr for TB */
#define     AM_VB1_NR             0   /* bus_nr for the first VB    (VCU) */
#define     AM_VB2_NR             2   /* bus_nr for the second VB   (MIB) */
#define     AM_MAX_BUSSES         3   /* maximal number of busses/station */

 /* constants for Message Data Mode */

 #define    AM_VB_END_OR_GW       0
 #define    AM_ROUTER_BRIDGE      1
 #define    AM_TB_END             2
 #define    AM_VB_END             3


/*
*************************************
* types                             *
*************************************
*/

typedef unsigned char    AM_RESULT;


typedef struct {
   unsigned char        function;
   unsigned char        device;
} AM_DIR_ENTRY;


 /* Network address format.
    'vehicle' includes the 'AM_PHYS_ADDR' bit if physical addressing mode
    is used, the value 'AM_SAME_VEHICLE' always means the own vehicle.
    'fct_or_sta' is either a logical function or a station depending on the
    addressing mode indicated in 'vehicle'.
    'next_sta' is the station address of the next hop towards the entity
    represented by the other fields.
    'tc' is the topo count which specifies the time interval during which
    'vehicle' is valid (this is only a 6-bit value, without topo valid bit).
*/
typedef struct {
   unsigned char     vehicle;        /* physical or logical addressing */
   unsigned char     fct_or_sta;     /* station if phys., function if log. */
   unsigned char     next_sta;       /* next station used on the way */
   unsigned char     tc;             /* topo count for which vehicle is valid */
} AM_ADDRESS;

/* some special types for the stadi directory */

typedef unsigned short LINK_ADDRESS;
/* 16 bit link address consists of a concatenation of the bus_id and
   station_address */

typedef struct {
  LINK_ADDRESS   link_address;
  unsigned char  final_station;
  unsigned char  next_station;
  unsigned short bus_id;
} AM_ST_ENTRY;

/****************************************************
*  special types for LME (Layer Management Entity)  *
****************************************************/

/* Structure contains information about the status of the messenger */

struct STR_AM_RD_MSNGR_STATUS
{
  unsigned long messages_sent;
  unsigned long messages_received;
  unsigned long packets_sent;
  unsigned long packet_retries;
  unsigned long multicast_retries;
  unsigned char messenger_id[32];
  unsigned char send_time_out;
  unsigned char ack_time_out;
  unsigned char alive_time_out;
  unsigned char credit;
  unsigned char packet_size;
  unsigned char instances;
  unsigned char multicast_window;
};

struct STR_AM_WT_MSNGR_CTRL
{
  unsigned char messenger_id[32];
  unsigned char send_time_out;
  unsigned char ack_time_out;
  unsigned char alive_time_out;
  unsigned char credit;
  unsigned char packet_size;
  unsigned char clear;
  unsigned char multicast_window;
};

/****************************
*  callback function types  *
*****************************/

 /* A function of type AM_CALL_CONF is called at the caller site after recep-
    tion of an expected reply message or an error and signals call completion.
    If any error occurred then 'status' is set !== 'AM_OK', otherwise
    'status' returns the value which has been specified for the reply
    by the replier function.
    'in_msg_addr' returns the address which was passed with 'am_call_requ'
    or the address of a buffer which was allocated by the messenger if any.
    ( may be NULL, i.e. the messenger has not allocated a buffer! )
    and 'in_msg_size' is set to 0 in case of an error or if just a status
    ( and no user data ) has been specified for the reply. */
typedef void ( * AM_CALL_CONF )( unsigned char caller_fct,
                                 void *ext_ref,
                                 const AM_ADDRESS *replier,
                                 void *in_msg_addr,
                                 CARDINAL32 in_msg_size,
                                 AM_RESULT status );

 /* A function of type AM_INVOKE_CONF is called at the caller site
    after transmission of a call message or an error and signals
    completion of an invoke request (call without reply message).
    If any error occurred then 'status' is set !== 'AM_OK'. */
typedef void ( * AM_INVOKE_CONF )( /* caller_fct */ unsigned char,
                                   /* ext_ref */ void *,
                                   /* replier */ const AM_ADDRESS *,
                                   /* status */ AM_RESULT );

typedef enum
{
  AM_RS_BOUND=0, AM_RS_UNBOUND, AM_RS_UNBINDING,
  AM_RS_READY, AM_RS_RECEIVING, AM_RS_RPI_INEXEC, AM_RS_RPC_INEXEC,
  AM_RS_SENDING, AM_RS_CLOSING
} AM_REPLIER_STATES;

 /* A function of this type is called at the replier site after reception
    of an incoming call message for which there is a ready instance.
    It signals receive completion. */
typedef void ( * AM_RCV_CONF )(  unsigned char replier_fct,
                                 const AM_ADDRESS *caller,
                                 void *in_msg_addr,
                                 CARDINAL32 in_msg_size,
                                 void *ext_ref);

 /* A function of this type is called at the replier site after trans-
    mission of a reply message and signals reply completion. */
typedef void ( * AM_REPLY_CONF )( unsigned char replier_fct,
                                  void *ext_ref );


/****************************************************
*  special types for the subscribe mechanism        *
****************************************************/

/* Attention: The Structure MD_PACKET was defined in earlier version in
   the file md_layer.h */

#ifdef WAG
  #define MD_DATA_SIZE      123
#else
  #define MD_DATA_SIZE      22
#endif


typedef struct str_mvb_link_packet {
    unsigned char   mode_hdest;  /* mode (1) and upper 4 dest bits */
    unsigned char   dest;        /* destination address            */
    unsigned char   prot_hsrc;   /* prot and upper 4 source bits   */
    unsigned char   src;         /* source address                 */
} MD_MVB_LINK_PACKET ;

typedef struct str_wtb_link_packet {
        unsigned char   reserved;
        unsigned char   dest;
        unsigned char   llc;
        unsigned char   src;
} MD_WTB_LINK_PACKET;

typedef struct str_link_packet {
        union unn_version {
                MD_MVB_LINK_PACKET      mvb;
                MD_WTB_LINK_PACKET      wtb;
        } version;
        unsigned char   size;
        unsigned char   final_vehicle;
        unsigned char   final_fct_or_dev;
        unsigned char   origin_vehicle;
        unsigned char   origin_fct_or_dev;
        unsigned char   mtc;
        unsigned char   data[ MD_DATA_SIZE ] ;
} MD_LINK_PACKET;


typedef struct str_port_packet {
        MD_LINK_PACKET  lk ;
        } MD_PORT_PACKET ;

typedef struct {
    void           *next ;
    void           *identifier ;
    unsigned char   control ;
    unsigned char   status ;
    MD_PORT_PACKET      port ;
        } MD_PACKET;

typedef struct
{
  unsigned char node_type;
  unsigned char node_version;
} Type_NodeKey;

typedef Type_NodeKey Type_NodeIx2NodeKeyArray[AM_MAX_NODES] ;

typedef struct
{
  unsigned char node_address ;
  unsigned char node_orient ;
  unsigned char topo_counter ;
  unsigned char individual_period ;
  unsigned char is_strong ;
  unsigned char number_of_nodes ;
  unsigned char bottom_address ;
  unsigned char top_address ;
  Type_NodeIx2NodeKeyArray NK ;
} Type_Topography;




/*****************************************************************************

                                 Prototypes

*****************************************************************************/

void  _am_version_read       (short *, short *, short *, short *);
void  _am_init               (void);
void  _am_nm_config (unsigned char bus_id,
                     unsigned short rcv_pool_size,
                     unsigned short transit_pool_size,
                     AM_RESULT *status);
void _am_announce_device (unsigned int   max_call_number,
			              unsigned int   max_inst_number,
			              unsigned int   default_reply_tmo,
			              unsigned short my_credit);
void  _am_insert_dir_entries( AM_DIR_ENTRY * list, unsigned nr_of_entries );
void  _am_remove_dir_entries( AM_DIR_ENTRY * list, unsigned nr_of_entries );
void  _am_get_dir_entry( unsigned char function, unsigned char * device );
void  _am_clear_dir          (void);
void  _am_send_requ( unsigned char caller_fct,
                     const AM_ADDRESS * replier,
                     void * out_msg_addr,         /* call message */
                     CARDINAL32 out_msg_size,
                     void * in_msg_addr,          /* reply message */
                     CARDINAL32 in_msg_size,
                     unsigned int reply_tmo,      /* 0 if default */
                     AM_CALL_CONF confirm,
                     AM_INVOKE_CONF invoke_conf,  /* @JDP */
                     void * ext_ref);
/*   @JDP
void  _am_call_requ
    (unsigned char, const AM_ADDRESS *, void *, CARDINAL32,
    void *, CARDINAL32, unsigned int, AM_CALL_CONF, void * );
@JDP*/
void  _am_call_cancel (unsigned char caller_fct,
                       const AM_ADDRESS * replier,
                       AM_RESULT * status);
void  _am_get_status (unsigned short bus_id, unsigned short selector,
		      unsigned short reset, unsigned short *status);
void  _am_bind_replier (unsigned char replier_fct,
                       AM_RCV_CONF rcv_conf,
                       AM_REPLY_CONF reply_conf,
                       AM_RESULT * status);
void  _am_unbind_replier     (unsigned char replier_fct);
void  _am_rcv_requ (unsigned char replier_fct,
                    void * in_msg_addr,  /* buffer for call message */
                    CARDINAL32 in_msg_size,
                    void * ext_ref,
                    AM_RESULT * status);
AM_REPLIER_STATES _am_get_replier_status (unsigned char, void *);
void _am_reply_requ (unsigned char replier_fct,
                     void * out_msg_addr,       /* reply message */
                     CARDINAL32 out_msg_size,
                     void * ext_ref,
                     AM_RESULT status); 
void _am_rcv_cancel (unsigned char replier_fct,
                     void * ext_ref, AM_RESULT * status);
AM_RESULT _am_set_current_tc (unsigned char tc);   /* EH 14-Jul-1994 */

AM_RESULT _am_set_operation_mode( unsigned short md_operation_mode);

AM_RESULT _am_enable_bridging( unsigned short bus_id);

AM_RESULT _am_disable_bridging (unsigned short bus_id);

void _am_get_station_id(unsigned char *p_station_id);

/*********************************************************
* Fl Link Layer subscribtion and initializing procedures *
*********************************************************/

void _am_subscribe_lm (unsigned short bus_id,
                 void (*lm_init)(unsigned short bus_id,
                                 void (* receive_confirm)(void),
                                 void (* get_pack)(void **, MD_PACKET **),
                                 void ** ident,
                                 void (* put_pack)( MD_PACKET * ),
                                 void (* status_indicate)(int )),
                 void (*lm_get_status)(unsigned short bus_id,
                                       unsigned short selector,
                                       unsigned short reset,
                                       unsigned short * status),
                 void (*lm_send_request)(unsigned short bus_id,
                                         unsigned char src_dev,
                                         unsigned char dst_dev,
                                         MD_PACKET * packet,
                                         int * status),
                 void (*lm_send_queue_flush)(unsigned short bus_id),
                 void (*lm_receive_poll)(unsigned short bus_id,
                                         unsigned char *src_dev,
                                         unsigned char *dst_dev,
                                         MD_PACKET **packet,
                                         int *status),
                 unsigned short (*lm_get_own_phya)(unsigned short bus_id,
                                                   int *status),
                 unsigned short (*lm_get_src_phya)(unsigned short bus_id,
                                                   MD_PACKET *packet,
                                                   int *status),
                 void (* lm_system_init)(unsigned short bus_id),
                 short(* lm_config)(unsigned short bus_id,
                                    void * p_xq0_space,  /* inst. of queue struct. for MVBC TS */
                                    void * p_xq1_space,
                                    void * p_rq_space),
        /* Memory Fragment Descr. for xmit q 0 (input parameter lm_config)   */
                 void * p_xq0_space,
        /* Memory Fragment Descr. for xmit q 1 (input parameter lm_config    */
                 void * p_xq1_space,
        /* Memory Fragment Descr. for rcve queue (input parameter lm_config) */
                 void * p_rq_space,
                 void (* lm_free_recources)(unsigned short bus_id,
                                            unsigned char * status),
                 unsigned short (* ls_t_GetTopography)(Type_Topography * p_topo),
                 AM_RESULT *status);

void _am_subscribe_lm_x (unsigned short bus_id,
                 void (*lm_init)(unsigned short bus_id,
                                 void (* receive_confirm)(void),
                                 void (* get_pack)(void **, MD_PACKET **),
                                 void ** ident,
                                 void (* put_pack)( MD_PACKET * ),
                                 void (* status_indicate)(int )),
                 void (*lm_get_status)(unsigned short bus_id,
                                       unsigned short selector,
                                       unsigned short reset,
                                       unsigned short * status),
                 void (*lm_send_request)(unsigned short bus_id,
                                         unsigned char src_dev,
                                         unsigned char dst_dev,
                                         MD_PACKET * packet,
                                         int * status),
                 void (*lm_send_queue_flush)(unsigned short bus_id),
                 void (*lm_receive_poll)(unsigned short bus_id,
                                         unsigned char *src_dev,
                                         unsigned char *dst_dev,
                                         MD_PACKET **packet,
                                         int *status),
                 unsigned short (*lm_get_own_phya)(unsigned short bus_id,
                                                   int *status),
                 unsigned short (*lm_get_src_phya)(unsigned short bus_id,
                                                   MD_PACKET *packet,
                                                   int *status),
                 void (* lm_system_init)(unsigned short bus_id),
                 short(* lm_config)(unsigned short bus_id,
                                    void * p_xq0_space,  /* inst. of queue struct. for MVBC TS */
                                    void * p_xq1_space,
                                    void * p_rq_space),
        /* Memory Fragment Descr. for xmit q 0 (input parameter lm_config)   */
                 void * p_xq0_space,
        /* Memory Fragment Descr. for xmit q 1 (input parameter lm_config    */
                 void * p_xq1_space,
        /* Memory Fragment Descr. for rcve queue (input parameter lm_config) */
                 void * p_rq_space,
                 void (* lm_free_recources)(unsigned short bus_id,
                                            unsigned char * status),
                 unsigned short (* ls_t_GetTopography)(Type_Topography * p_topo),
                 unsigned short (* lm_enable_bridging)(unsigned short bus_id),
                 unsigned short (* lm_disable_bridging)(unsigned short bus_id),
                 AM_RESULT *status);

void _am_disubscribe_lm(unsigned short bus_id, AM_RESULT *status);


/* the messenger is normally called over the indirect jump table, but it
   is also possible to start it direct from the OS or if necessary from the
   applications */

/* the messenger must be started as a cyclic task which has lower priority
   than the timeout process. */

void tm_messenger (void);

/*    special functions for stadi management.                           */
/*    The station directory is necessary if there is more than 1 VB     */
/*    in a vehicle, or if the physical address is not identical with    */
/*    the station address. A station address is unique within a         */
/*    vehicle.                                                          */

AM_RESULT _am_st_write (AM_ST_ENTRY entries[], unsigned int nr_of_entries);
   /* Writes (inserts) a number of entries into the STADI.
   Returns AM_OK on success, or AM_FAILURE if some entries of the list
   cannot be written because they do not pass the checks.
   */

void _am_st_read (AM_ST_ENTRY entries[], unsigned int nr_of_entries);
   /* Reads a number of entries from the STADI. */


void _am_disp_show_busses (unsigned char *nr_of_busses,
                           unsigned char bus_nr[AM_MAX_BUSSES]);
   /* Returns a list of connected bus numbers. nr_of_busses specifies the
   number of valid entries in bus_nr list and is limited to AM_MAX_BUSSES.
   The TB is always the last entry in the list if it is connected.
   This information is provided by the bus dispatcher module.
   */

/****************************************************************************
*                 special functions for network management                  *
*                                                                           *
*  !! These function are reserved for the Network Management and            *
*     it is not allowed to use the functions for Message Data Applications  *
*****************************************************************************/

int _am_read_messenger_status(struct STR_AM_RD_MSNGR_STATUS *p_stat);
  /* Retrieve the status of the messenger and its statistic counters */

int _am_write_messenger_control(struct STR_AM_WT_MSNGR_CTRL *p_stat);
   /* Set parameters in the messenger */


typedef struct
{
   unsigned char amd_version[4];
   void  (*pam_init)        (void);
   void  (*pam_nm_config)(unsigned char, unsigned short,
                          unsigned short, AM_RESULT *);
   void  (*pam_announce_device)(unsigned int, unsigned int,
                                unsigned int, unsigned short);
   void  (*pam_insert_dir_entries) (AM_DIR_ENTRY * , unsigned int);
   void  (*pam_remove_dir_entries) (AM_DIR_ENTRY * , unsigned int);
   void  (*pam_get_dir_entry)      (unsigned char, unsigned char *);
   void  (*pam_clear_dir)          (void);
   void  (*pam_send_requ)(unsigned char, const AM_ADDRESS *, void *, CARDINAL32, /* @JDP */
                          void *, CARDINAL32, unsigned int,                      /* @JDP */
                          AM_CALL_CONF, AM_INVOKE_CONF, void * );                /* @JDP */
/* @JDP
   void  (*pam_call_requ)(unsigned char, const AM_ADDRESS *, void *, CARDINAL32,
                          void *, CARDINAL32, unsigned int, AM_CALL_CONF, void * );
@JDP */
   void  (*pam_call_cancel)(unsigned char, const AM_ADDRESS *, AM_RESULT *);
   void  (*pam_bind_replier)(unsigned char, AM_RCV_CONF, AM_REPLY_CONF, AM_RESULT *);
   void  (*pam_unbind_replier)(unsigned char replier_fct);
   void  (*pam_rcv_requ)(unsigned char, void *, CARDINAL32, void *, AM_RESULT *);
   void  (*pam_reply_requ)(unsigned char, void *, CARDINAL32, void *, AM_RESULT);
   void  (*pam_rcv_cancel)(unsigned char, void *, AM_RESULT *);
   void  (*pam_get_status)(unsigned short, unsigned short,
                           unsigned short, unsigned short *);
   void  (*pam_tm_messenger)(void);
   AM_REPLIER_STATES (*pam_get_replier_status)(unsigned char, void *);
   AM_RESULT (*pam_set_current_tc)(unsigned char);

   AM_RESULT (*pam_st_write ) (AM_ST_ENTRY entries[],
                               unsigned int nr_of_entries);
   void (*pam_st_read) (AM_ST_ENTRY entries[], unsigned int nr_of_entries);
   void (*pam_disp_show_busses) (unsigned char *nr_of_busses,
                                 unsigned char bus_nr[AM_MAX_BUSSES]);
   int  (*pam_read_messenger_status) (struct STR_AM_RD_MSNGR_STATUS *);
   int  (*pam_write_messenger_control) (struct STR_AM_WT_MSNGR_CTRL *);
   void (*pam_subscribe_lm) (unsigned short bus_id,
                     void (*lm_init)(unsigned short bus_id,
                                     void (* receive_confirm)(void),
                                     void (* get_pack)(void **, MD_PACKET **),
                                     void ** ident,
                                     void (* put_pack)( MD_PACKET * ),
                                     void (* status_indicate)(int )),
                     void (*lm_get_status)(unsigned short bus_id,
                                           unsigned short selector,
                                           unsigned short reset,
                                           unsigned short * status),
                     void (*lm_send_request)(unsigned short bus_id,
                                             unsigned char src_dev,
                                             unsigned char dst_dev,
                                             MD_PACKET * packet,
                                             int * status),
                     void (*lm_send_queue_flush)(unsigned short bus_id),
                     void (*lm_receive_poll)(unsigned short bus_id,
                                             unsigned char *src_dev,
                                             unsigned char *dst_dev,
                                             MD_PACKET **packet,
                                             int *status),
                     unsigned short (*lm_get_own_phya)(unsigned short bus_id,
                                                       int *status),
                     unsigned short (*lm_get_src_phya)(unsigned short bus_id,
                                                       MD_PACKET *packet,
                                                       int *status),
                     void (* lm_system_init)(unsigned short bus_id),
                     short(* lm_config)(unsigned short bus_id,
                                        void * p_xq0_space,  /* inst. of queue structures for MVBC TS */
                                        void * p_xq1_space,
                                        void * p_rq_space),
                     void * p_xq0_space, /* Memory Fragment Descr. for xmit q 0 (input parameter lm_config)   */
                     void * p_xq1_space, /* Memory Fragment Descr. for xmit q 1 (input parameter lm_config    */
                     void * p_rq_space,  /* Memory Fragment Descr. for rcve queue (input parameter lm_config) */
                     void (* lm_free_recources)(unsigned short bus_id, unsigned char * status),
                     unsigned short (* ls_t_GetTopography)(Type_Topography * p_topo),
                     AM_RESULT *status);
   void (*pam_disubscribe_lm)(unsigned short bus_id, AM_RESULT *status);
   void (*pam_subscribe_lm_x) (unsigned short bus_id,
                     void (*lm_init)(unsigned short bus_id,
                                     void (* receive_confirm)(void),
                                     void (* get_pack)(void **, MD_PACKET **),
                                     void ** ident,
                                     void (* put_pack)( MD_PACKET * ),
                                     void (* status_indicate)(int )),
                     void (*lm_get_status)(unsigned short bus_id,
                                           unsigned short selector,
                                           unsigned short reset,
                                           unsigned short * status),
                     void (*lm_send_request)(unsigned short bus_id,
                                             unsigned char src_dev,
                                             unsigned char dst_dev,
                                             MD_PACKET * packet,
                                             int * status),
                     void (*lm_send_queue_flush)(unsigned short bus_id),
                     void (*lm_receive_poll)(unsigned short bus_id,
                                             unsigned char *src_dev,
                                             unsigned char *dst_dev,
                                             MD_PACKET **packet,
                                             int *status),
                     unsigned short (*lm_get_own_phya)(unsigned short bus_id,
                                                       int *status),
                     unsigned short (*lm_get_src_phya)(unsigned short bus_id,
                                                       MD_PACKET *packet,
                                                       int *status),
                     void (* lm_system_init)(unsigned short bus_id),
                     short(* lm_config)(unsigned short bus_id,
                                        void * p_xq0_space,  /* inst. of queue structures for MVBC TS */
                                        void * p_xq1_space,
                                        void * p_rq_space),
                     void * p_xq0_space, /* Memory Fragment Descr. for xmit q 0 (input parameter lm_config)   */
                     void * p_xq1_space, /* Memory Fragment Descr. for xmit q 1 (input parameter lm_config    */
                     void * p_rq_space,  /* Memory Fragment Descr. for rcve queue (input parameter lm_config) */
                     void (* lm_free_recources)(unsigned short bus_id, unsigned char * status),
                     unsigned short (* ls_t_GetTopography)(Type_Topography * p_topo),
                     unsigned short (* lm_enable_bridging)(unsigned short bus_id),
                     unsigned short (* lm_disable_bridging)(unsigned short bus_id),
                     AM_RESULT *status);
   AM_RESULT (*pam_set_operation_mode)( unsigned short);
   AM_RESULT (*pam_enable_bridging)( unsigned short);
   AM_RESULT (*pam_disable_bridging)(unsigned short);
   void		 (*pam_get_station_id)(unsigned char*);
} TYPE_AM_IND_CALL;

/* !!! indirect jump table not yet supported for multicast protocol! */

void am_multicast_requ (unsigned char caller_fct,
                        const AM_ADDRESS *replier,
                        void *out_msg_addr,
                        unsigned int out_msg_size,
                        AM_INVOKE_CONF confirm,
                        void *ext_ref);
void am_multicast_init (void);

#define am_version_read             _am_version_read
#define am_init                     _am_init
#define am_announce_device          _am_announce_device
#define am_nm_config                _am_nm_config
#define am_insert_dir_entries       _am_insert_dir_entries
#define am_remove_dir_entries       _am_remove_dir_entries
#define am_get_dir_entry            _am_get_dir_entry
#define am_clear_dir                _am_clear_dir
#define am_send_requ                _am_send_requ
#define am_call_requ(fct, r, out_a, out_s, in_a, in_s, tmo, cc, ref) /*@JDP*/\
       _am_send_requ(fct, r, out_a, out_s, in_a, in_s, tmo, cc, (AM_INVOKE_CONF)0, ref) /* @JDP */
/* @JDP
#define am_call_requ               _am_call_requ
@JDP */
#define am_invoke_requ(fct, r, out_a, out_s, ic, ref)  \
       _am_send_requ(fct, r, out_a, out_s, NULL, 0, 0, NULL, ic, ref)
#define am_call_cancel              _am_call_cancel
#define am_get_status               _am_get_status
#define am_bind_replier             _am_bind_replier
#define am_unbind_replier           _am_unbind_replier
#define am_rcv_requ                 _am_rcv_requ
#define am_reply_requ               _am_reply_requ
#define am_rcv_cancel               _am_rcv_cancel
#define am_get_replier_status       _am_get_replier_status
#define am_set_current_tc           _am_set_current_tc
#define am_st_write                 _am_st_write
#define am_st_read                  _am_st_read
#define am_disp_show_busses         _am_disp_show_busses
#define am_read_messenger_status    _am_read_messenger_status
#define am_write_messenger_control  _am_write_messenger_control
#define am_subscribe_lm             _am_subscribe_lm
#define am_disubscribe_lm           _am_disubscribe_lm
#define am_tm_messenger             tm_messenger
#define am_subscribe_lm_x           _am_subscribe_lm_x
#define am_set_operation_mode       _am_set_operation_mode
#define am_enable_bridging          _am_enable_bridging
#define am_disable_bridging         _am_disable_bridging
#define am_get_station_id           _am_get_station_id

/*
*************************************
* Version Verification Mechanism    *
*************************************
*/


#define AM_VERSION         4     /* if you update, update also MESSENGER_ID */
#define AM_RELEASE         5     /* if you update, update also MESSENGER_ID */
#define AM_UPDATE          1     /* if you update, update also MESSENGER_ID */
#define AM_EVOLUTION       0


#define MESSENGER_ID       "RTP_MD-V4.5.1 98-09-21\0"
#define MESSENGER_ID_SIZE  sizeof(MESSENGER_ID)



#define am_version()    0

#ifdef __cplusplus
}
#endif


#endif                                 /* AM_SYS_H */
   
   
/****************************************************************************
*****************************************************************************
*                                                                           *
*               TCN LINK LAYER COMMON INTERFACE                             *
*                                                                           *
*****************************************************************************
****************************************************************************/
   
    

#ifndef         LC_SYS_H
    #define     LC_SYS_H

#ifdef __cplusplus 
extern "C" {
#endif 


#define LC_TRUE  (0==0)
#define LC_FALSE (0!=0)


/*
        ***********************************************************
        *                                                         *
        * Version Verification Mechanism                          *
        *                                                         *
        ***********************************************************
*/

#define LC_VERSION       4
#define LC_RELEASE       6


/*
        ***********************************************************
        *                                                         *
        * Basic Constants, Types and Functions                    *
        *                                                         *
        ***********************************************************
*/

/* Interrupt Codes */

#define LC_INT_DTI1      0x00
#define LC_INT_DTI2      0x01
#define LC_INT_DTI3      0x02
#define LC_INT_DTI4      0x03
#define LC_INT_DTI5      0x04
#define LC_INT_DTI6      0x05
#define LC_INT_DTI7      0x06
#define LC_INT_BTI       0x07
#define LC_INT_RTI       0x08
#define LC_INT_SFC       0x09
#define LC_INT_MFC       0x0A
#define LC_INT_AMFX      0x0B
#define LC_INT_DSF       0x0C
#define LC_INT_DMF       0x0D
#define LC_INT_ESF       0x0E
#define LC_INT_EMF       0x0F

#define LC_INT_EXT_0     0x10
#define LC_INT_EXT_1     0x11
#define LC_INT_TIMER_1   0x12
#define LC_INT_FEV       0x17
#define LC_INT_RQC       0x18
#define LC_INT_XQ0C      0x19
#define LC_INT_XQ1C      0x1A
#define LC_INT_RQE       0x1B
#define LC_INT_XQE       0x1C
#define LC_INT_EXT_2     0x1D
#define LC_INT_EXT_3     0x1E
#define LC_INT_TIMER_2   0x1F

/* Expressions for compatibility reasons */

#define LC_INT_LP_SEND       LC_INT_DTI1
#define LC_INT_LP_RECV       LC_INT_DTI2  /* Corrected fr. LM_SEND */
#define LC_INT_EXT_5         LC_INT_EXT_0
#define LC_INT_EXT_6         LC_INT_EXT_1
#define LC_INT_TIMER         LC_INT_TIMER_1

#define LC_KERNEL                     0   /* !!! keep consistent with     */
#define LC_NO_KERNEL                  1   /*     constants in LCINTR.S    */

#define LC_OK                         0   /* Return Values */
#define LC_REJECT                     1
#define LC_K_CALLS                    2

#define LC_DSW_SER_MSK              0x0001   /* Device Status Report */
#define LC_DSW_SER_SET              0x0001
#define LC_DSW_SER_CLR              0x0000

#define LC_DSW_DNR_MSK              0x0002
#define LC_DSW_DNR_SET              0x0002
#define LC_DSW_DNR_CLR              0x0000

#define LC_DSW_FRC_MSK              0x0004
#define LC_DSW_FRC_SET              0x0004
#define LC_DSW_FRC_CLR              0x0000

#define LC_DSW_ERD_MSK              0x0008
#define LC_DSW_ERD_SET              0x0008
#define LC_DSW_ERD_CLR              0x0000

#define LC_DSW_SDD_MSK              0x0010
#define LC_DSW_SDD_SET              0x0010
#define LC_DSW_SDD_CLR              0x0000

#define LC_DSW_SSD_MSK              0x0020
#define LC_DSW_SSD_SET              0x0020
#define LC_DSW_SSD_CLR              0x0000

#define LC_DSW_RLD_MSK              0x0040
#define LC_DSW_RLD_SET              0x0040
#define LC_DSW_RLD_CLR              0x0000

#define LC_DSW_LAA_MSK              0x0080
#define LC_DSW_LAA_SET              0x0080
#define LC_DSW_LAA_CLR              0x0000

#define LC_DSW_MAS_MSK              0x0100
#define LC_DSW_MAS_SET              0x0100
#define LC_DSW_MAS_CLR              0x0000

#define LC_DSW_ACT_MSK              0x0200
#define LC_DSW_ACT_SET              0x0200
#define LC_DSW_ACT_CLR              0x0000

#define LC_DSW_AX_MSK               0x0C00
#define LC_DSW_AX_0                 0x0000
#define LC_DSW_AX_1                 0x0400
#define LC_DSW_AX_2                 0x0800
#define LC_DSW_AX_3                 0x0C00
#define LC_DSW_AX_UNIT              LC_DSW_AX_1

#define LC_DSW_TYPE_MSK             0xF000

#define LC_DSW_TYPE_SPECIAL_MSK     0x8000
#define LC_DSW_TYPE_SPECIAL_SET     0x8000
#define LC_DSW_TYPE_SPECIAL_CLR     0x0000

#define LC_DSW_TYPE_BUS_ADMIN_MSK   0x4000
#define LC_DSW_TYPE_BUS_ADMIN_SET   0x4000
#define LC_DSW_TYPE_BUS_ADMIN_CLR   0x0000

#define LC_DSW_TYPE_BRIDGE_MSK      0x2000
#define LC_DSW_TYPE_BRIDGE_SET      0x2000
#define LC_DSW_TYPE_BRIDGE_CLR      0x0000

#define LC_DSW_TYPE_CLASS_2_3_MSK   0x1000
#define LC_DSW_TYPE_CLASS_2_3_SET   0x1000
#define LC_DSW_TYPE_CLASS_2_3_CLR   0x0000

#define LC_DSW_TYPE_SPEC_MSK        0x7000
#define LC_DSW_TYPE_SPEC_CLR        0x0000
#define LC_DSW_TYPE_SPEC_CLASS1_SET 0x7000

/* Other allowed LC_DSW_TYPE_SPEC_..._SET values for future use: */
/* 0x6000, 0x5000, 0x4000, 0x3000, 0x2000, 0x1000, 0x0000        */

#define LC_DSW_ALL_MSK              0xFFFF
#define LC_DSW_ALL_CLR              0x0000

#define LC_MCM_16K               0        /* Memory Config. Modes */
#define LC_MCM_32K               1
#define LC_MCM_64K               2
#define LC_MCM_256K              3
#define LC_MCM_1M                4

#define LC_0_TO_256K             0        /* MF-Table/Queue Offset Values */
#define LC_256_TO_512K           1
#define LC_512_TO_768K           2
#define LC_768K_TO_1M            3

#define LC_CTRL_BLK_SIZE         8        /* Description Control Blocks */


/* MVBC Hardware Configuration Parameters */

#define LC_CH_A                  1        /* Channel A */
#define LC_CH_B                  0        /* Channel B */
#define LC_CH_BOTH               2        /* Both Channels */

#define LC_TREPLY_21US           0        /* Reply Timeout Coefficients */
#define LC_TREPLY_43US           1
#define LC_TREPLY_64US           2
#define LC_TREPLY_85US           3

#define LC_TREPLY_UNCHANGED     10        /* Don't change TREPLY at all */


/*
 ---------------------------------------------------------------------------
 Volatile attribute: Assures that register accesses are not optimized by "C"
 ---------------------------------------------------------------------------
*/

#ifndef VOL
   #define VOL volatile
#endif

/*
 ---------------------------------------------------------------------------
    Traffic Store Size Constants
 ---------------------------------------------------------------------------
*/


#define LC_TS_MAX_PORT_ADDR          4095

#if !defined (O_LC_MCM)
    #define O_LC_MCM                 LC_MCM_256K
#endif

#if   (O_LC_MCM == LC_MCM_16K)

    #define LC_TS_MAX_DA_PORT_INDX   0
    #define LC_TS_MAX_LA_PORT_INDX   255

#elif (O_LC_MCM == LC_MCM_32K)

    #define LC_TS_MAX_DA_PORT_INDX   255
    #define LC_TS_MAX_LA_PORT_INDX   255

#elif (O_LC_MCM == LC_MCM_64K)

    #define LC_TS_MAX_DA_PORT_INDX   255
    #define LC_TS_MAX_LA_PORT_INDX   1023

#elif (O_LC_MCM == LC_MCM_256K)

    #define LC_TS_MAX_DA_PORT_INDX   1023
    #define LC_TS_MAX_LA_PORT_INDX   4095

#elif (O_LC_MCM == LC_MCM_1024K)

    #define LC_TS_MAX_DA_PORT_INDX   4095
    #define LC_TS_MAX_LA_PORT_INDX   4095

#endif

/*
 ---------------------------------------------------------------------------
    Traffic Store Type Definitions for PIT, PCS and Port
 ---------------------------------------------------------------------------
*/

#if (O_LC_MCM <= LC_MCM_32K)
typedef unsigned short     LC_TYPE_TS_PIT [(LC_TS_MAX_PORT_ADDR + 1) / 2];
#else
typedef unsigned short     LC_TYPE_TS_PIT [LC_TS_MAX_PORT_ADDR + 1];
#endif

typedef VOL unsigned short LC_TYPE_TS_PCS [4];

typedef LC_TYPE_TS_PCS     LC_TYPE_TS_LA_PCS [LC_TS_MAX_LA_PORT_INDX + 1];

typedef unsigned short     LC_TYPE_TS_DCK [4];
typedef LC_TYPE_TS_DCK     LC_TYPE_TS_PGE [4];
typedef LC_TYPE_TS_PGE     LC_TYPE_TS_PRT [2];

typedef unsigned short     LC_TYPE_TS_PGE_WTB [64];
typedef LC_TYPE_TS_PGE_WTB LC_TYPE_TS_PRT_WTB [2];

#if (O_LC_MCM >= LC_MCM_32K)
typedef LC_TYPE_TS_PCS     LC_TYPE_TS_DA_PCS [LC_TS_MAX_DA_PORT_INDX + 1];
typedef LC_TYPE_TS_PRT     LC_TYPE_TS_DA_PRT [(LC_TS_MAX_DA_PORT_INDX + 1) / 4];
#endif


/*
 ---------------------------------------------------------------------------
    Traffic Store Access Routines for PIT
 ---------------------------------------------------------------------------
*/

#if defined (O_LE)
#define LC_PIT_MSK_ODD    0x00FF
#define LC_PIT_MSK_EVN    0xFF00
#define LC_PIT_OFF_ODD    8
#define LC_PIT_OFF_EVN    0
#else
#define LC_PIT_MSK_ODD    0xFF00
#define LC_PIT_MSK_EVN    0x00FF
#define LC_PIT_OFF_ODD    0
#define LC_PIT_OFF_EVN    8
#endif

#if (O_LC_MCM <= LC_MCM_32K)

#define lc_put_pit(p_pit, prt_addr, prt_indx)             \
{ unsigned short tmp_prt_ad = (prt_addr) >> 1;            \
  unsigned short tmp_prt_ix;                              \
  if (((prt_addr) & 1) == 1)                              \
  { tmp_prt_ix  = p_pit[0][tmp_prt_ad] & LC_PIT_MSK_ODD;  \
    tmp_prt_ix |= ((prt_indx) << LC_PIT_OFF_ODD);         \
    p_pit[0][tmp_prt_ad] = tmp_prt_ix;                    \
  } else                                                  \
  { tmp_prt_ix  = p_pit[0][tmp_prt_ad] & LC_PIT_MSK_EVN;  \
    tmp_prt_ix |= ((prt_indx) << LC_PIT_OFF_EVN);         \
    p_pit[0][tmp_prt_ad] = tmp_prt_ix;                    \
  } }


#define lc_get_pit(p_ix, p_pit, prt_addr)                                   \
{ if (((prt_addr) & 1) == 1)                                                \
  { *p_ix = (p_pit[0][(prt_addr) >> 1] & LC_PIT_MSK_EVN) >> LC_PIT_OFF_ODD; } \
  else                                                                      \
  { *p_ix = (p_pit[0][(prt_addr) >> 1] & LC_PIT_MSK_ODD) >> LC_PIT_OFF_EVN; } \
}


#else
#define lc_put_pit(p_pit, prt_addr, prt_indx)        \
        { p_pit[0][(prt_addr)] = (prt_indx); }

#define lc_get_pit(p_ix, p_pit, prt_addr)            \
        { *(p_ix) = p_pit[0][(prt_addr)]; }
#endif

/*
 ---------------------------------------------------------------------------
    Traffic Store Access Routines for PCS
 ---------------------------------------------------------------------------
*/

#define lc_put_pcs(p_pcs, mask, offset, value)       \
        {register VOL unsigned short * p_pcs_vol = (VOL unsigned short *) (p_pcs); \
         *(p_pcs_vol + ((offset) / 16))  =       \
        ((mask) & ((value) << ((offset) % 16))) |       \
        ( *(p_pcs_vol + ((offset) / 16)) & ~(mask));}

#define lc_get_pcs(p_val, p_pcs, mask, offset)                    \
        {register VOL unsigned short * p_pcs_vol = (VOL unsigned short *) (p_pcs); \
         *p_val = (*(p_pcs_vol + ((offset) / 16)) & (mask)) \
                >> ((offset) % 16);}

extern unsigned short lc_wait_word; /* dummy variable to fix page pointer failure */
/* new macro implementation to fix page pointer failure */
#define lc_tgl_pcs(p_pcs, mask, offset) \
        { register VOL unsigned short* p_pcs_vol = ((VOL unsigned short*)p_pcs) + ((offset) / 16); \
          register unsigned short new_pcs_val = (*p_pcs_vol) ^ (mask); \
          (*p_pcs_vol) = new_pcs_val; \
          lc_wait_word = new_pcs_val; \
          (*p_pcs_vol) = new_pcs_val; }

#define lc_inc_pcs(p_pcs, mask, offset) \
        {register VOL unsigned short * p_pcs_vol = (VOL unsigned short *) (p_pcs); \
          (*(p_pcs_vol + ((offset) / 16))) += 1; }


#define lc_put_pcs_bap(a,b,c,d)         /* empty function for mvbc */
#define lc_put_pcs_mvbc         lc_put_pcs



/*
 ---------------------------------------------------------------------------
    Constants as Parameter for Traffic Store PCS Access Routines
 ---------------------------------------------------------------------------
*/


#define LC_PCS_MSK_FCODE        0xF000
#define LC_PCS_OFF_FCODE        12
#define LC_PCS_VAL_FCODE_08     8
#define LC_PCS_VAL_FCODE_09     9
#define LC_PCS_VAL_FCODE_15     15

#define LC_PCS_MSK_TYPE         0x0C00
#define LC_PCS_OFF_TYPE         10
#define LC_PCS_VAL_TYPE_CLR     0
#define LC_PCS_VAL_TYPE_SNK     1
#define LC_PCS_VAL_TYPE_SRC     2

#define LC_PCS_MSK_TWCS         0x0200
#define LC_PCS_OFF_TWCS         9
#define LC_PCS_VAL_TWCS_ACT     1

#define LC_PCS_MSK_DTI          0x00E0
#define LC_PCS_OFF_DTI          5
#define LC_PCS_VAL_DTI_CLR      0
#define LC_PCS_VAL_DTI_1        1
#define LC_PCS_VAL_DTI_2        2
#define LC_PCS_VAL_DTI_3        3
#define LC_PCS_VAL_DTI_4        4
#define LC_PCS_VAL_DTI_5        5
#define LC_PCS_VAL_DTI_6        6

#define LC_PCS_MSK_FE           0x0001
#define LC_PCS_OFF_FE           0
#define LC_PCS_VAL_FE_CLR       0
#define LC_PCS_VAL_FE_SET       1

#define LC_PCS_MSK_NUM          0x0002
#define LC_PCS_OFF_NUM          1
#define LC_PCS_VAL_NUM_CLR      0
#define LC_PCS_VAL_NUM_SET      1

#define LC_PCS_MSK_VP           0x0040
#define LC_PCS_OFF_VP           (16 + 6)

#define LC_PCS_MSK_DIAG         0x0007
#define LC_PCS_OFF_DIAG         (16 + 0)
#define LC_PCS_VAL_DIAG_CLR     0
#define LC_PCS_VAL_DIAG_STO     1
#define LC_PCS_VAL_DIAG_TERR    2
#define LC_PCS_VAL_DIAG_RDY     3
#define LC_PCS_VAL_DIAG_BNI     4

#define LC_PCS_MSK_TACK         0xFFFF
#define LC_PCS_OFF_TACK         (32 + 0)


/*
 ---------------------------------------------------------------------------
    LME Support
 ---------------------------------------------------------------------------
*/

#define LC_HW_ID_SIZE   32 /* Bytes */
#define LC_SW_ID_SIZE   32 /* Bytes */

struct LC_STR_MVB_STATUS
       {
           unsigned char  hardware_id[LC_HW_ID_SIZE];
                                              /* Identifies MVBC type     */
           unsigned char  software_id[LC_SW_ID_SIZE];
                                              /* Identifies LC version    */
           unsigned long  lineA_errors;       /* Error ctr for line A     */
           unsigned long  lineB_errors;       /* Error ctr for line B     */
           unsigned short link_address;       /* ts_id (high 4 bits), and */
                                              /* dev_addr (lower 12 bits) */
           unsigned short device_status_word; /* Device status word       */
           unsigned char  t_reply;            /* Reply timeout, in us     */

           /* lineA_errors is used if line A (single line mode) or       */
           /*              redundant line communication (A+B) is used.   */
           /* lineB_errors is used if line B (single line mode) is used  */
       };

/* Bit masks to select bit-wise command for 2nd param of lc_m_mvb_line() */

#define LC_MVB_LINE_CMD_CLB  0x80
#define LC_MVB_LINE_CMD_CLA  0x40
#define LC_MVB_LINE_CMD_SLB  0x20
#define LC_MVB_LINE_CMD_SLA  0x10



/*
        ***********************************************************
        *                                                         *
        * Direct Function Prototypes                              *
        *                                                         *
        ***********************************************************
*/

extern short          _lc_init                     (void);
extern short          _lc_m_config                 (unsigned short,
                                                    void *,short,short,short);
extern short          _lc_m_int_connect            (unsigned short,
                                                    void (*)(unsigned short),
                                                    short,
                                                    unsigned short, 
                                                    unsigned short);
extern short          _lc_m_int_disconnect         (unsigned short,short);
extern short          _lc_m_get_device_address     (unsigned short,
                                                    unsigned short *);
extern short          _lc_m_set_device_address     (unsigned short,
                                                    unsigned short);
extern unsigned short _lc_m_get_device_status_word (unsigned short);
extern void           _lc_m_set_device_status_word (unsigned short,
                                                    unsigned short,
                                                    unsigned short);
extern void *         _lc_m_get_service_area_addr  (unsigned short);
extern void           _lc_set_laa_rld              (void);
extern void           _lc_exit                     (void);
extern short          _lc_m_go                     (unsigned short);
extern short          _lc_m_hardw_config           (unsigned short,
                                                    unsigned short,
                                                    unsigned short);
extern void           _lc_intr_hdlr_0_k            (unsigned short);
extern void           _lc_intr_hdlr_1_k            (unsigned short);
extern void           _lc_intr_hdlr_b_k            (unsigned short);
extern short          _lc_intr_hdlr_0_nk           (unsigned short);
extern short          _lc_intr_hdlr_1_nk           (unsigned short);
extern short          _lc_intr_hdlr_b_nk           (unsigned short);
extern void           _lc_wait                     (unsigned short);
extern void           _lc_memset16                 (unsigned short * ptr,
                                                    unsigned short   val,
                                                    unsigned short   sze);
extern unsigned short _lc_m_set_mbc                (unsigned short);
extern unsigned short _lc_m_clr_mbc                (unsigned short);

/* Starting here: LME support functions */

extern int            _lc_read_mvb_status          ( unsigned int,
                                                     struct LC_STR_MVB_STATUS* );
extern int            _lc_mvb_line                 ( unsigned int,
                                                     unsigned char );


typedef struct
{

    unsigned char lc_version_info[4];   	/* !!! No const: 4 = Four entries:          */
						/* version / release / update / evolution   */

    short          (*plc_init)                     (void);
    short          (*plc_m_config)                 (unsigned short,
                                                    void *,
                                                    short,
                                                    short,
                                                    short);
    short          (*plc_m_int_connect)            (unsigned short,
                                                    void (*)(unsigned short),
                                                    short,
                                                    unsigned short, 
                                                    unsigned short);
    short          (*plc_m_int_disconnect)         (unsigned short,short);
    short          (*plc_m_get_device_address)     (unsigned short,
                                                    unsigned short *);
    short          (*plc_m_set_device_address)     (unsigned short,
                                                    unsigned short);
    unsigned short (*plc_m_get_device_status_word) (unsigned short);
    void           (*plc_m_set_device_status_word) (unsigned short,
                                                    unsigned short,
                                                    unsigned short);
    void *         (*plc_m_get_service_area_addr)  (unsigned short);
    void           (*plc_set_laa_rld)              (void);
    void           (*plc_exit)                     (void);
    short          (*plc_m_go)                     (unsigned short);
    short          (*plc_m_hardw_config)           (unsigned short,
                                                    unsigned short,
                                                    unsigned short);
    void           (*plc_intr_hdlr_0_k)            (unsigned short);
    void           (*plc_intr_hdlr_1_k)            (unsigned short);
    void           (*plc_intr_hdlr_b_k)            (unsigned short);
    short          (*plc_intr_hdlr_0_nk)           (unsigned short);
    short          (*plc_intr_hdlr_1_nk)           (unsigned short);
    short          (*plc_intr_hdlr_b_nk)           (unsigned short);
    void           (*plc_wait)                     (unsigned short);
    void           (*plc_memset16)                 (unsigned short * ptr,
                                                    unsigned short   val,
                                                    unsigned short   sze);
    unsigned short (*plc_m_set_mbc)                (unsigned short);
    unsigned short (*plc_m_clr_mbc)                (unsigned short);

    /* Starting here: LME support functions */

    int            (*plc_read_mvb_status)          (unsigned int,
                                                    struct LC_STR_MVB_STATUS* );
    int            (*plc_mvb_line)                 (unsigned int,
                                                    unsigned char);
}
    TYPE_LC_IND_CALL;



/*
        ***********************************************************
        *                                                         *
        * Direct Calling Mechanism (no ICM)                       *
        *                                                         *
        ***********************************************************
*/



    /* Connection to user by direct call */
    /* --------------------------------- */

    #define lc_init                     _lc_init
    #define lc_m_config                 _lc_m_config
    #define lc_m_int_connect            _lc_m_int_connect
    #define lc_m_int_disconnect         _lc_m_int_disconnect
    #define lc_m_get_device_address     _lc_m_get_device_address
    #define lc_m_set_device_address     _lc_m_set_device_address
    #define lc_m_get_device_status_word _lc_m_get_device_status_word
    #define lc_m_set_device_status_word _lc_m_set_device_status_word
    #define lc_m_get_service_area_addr  _lc_m_get_service_area_addr
    #define lc_set_laa_rld              _lc_set_laa_rld
    #define lc_exit                     _lc_exit
    #define lc_m_go                     _lc_m_go
    #define lc_m_hardw_config           _lc_m_hardw_config
    #define lc_intr_hdlr_0_k            _lc_intr_hdlr_0_k
    #define lc_intr_hdlr_1_k            _lc_intr_hdlr_1_k
    #define lc_intr_hdlr_b_k            _lc_intr_hdlr_b_k
    #define lc_intr_hdlr_0_nk           _lc_intr_hdlr_0_nk
    #define lc_intr_hdlr_1_nk           _lc_intr_hdlr_1_nk
    #define lc_intr_hdlr_b_nk           _lc_intr_hdlr_b_nk
    #define lc_wait                     _lc_wait
    #define lc_m_set_mbc                _lc_m_set_mbc
    #define lc_m_clr_mbc                _lc_m_clr_mbc

    /* LME Support */
    #define lc_read_mvb_status          _lc_read_mvb_status
    #define lc_mvb_line                 _lc_mvb_line

/*
    #define lc_memset16                 _lc_memset16
*/


    /* Version Verification Call:  Not supported here */
    /* ---------------------------------------------- */

    #define lc_version() {;}



/*
        ***********************************************************
        *                                                         *
        * LC-spec. function name remapping for default systems    *
        * containing one Traffic Memory (usual case)              *
        *                                                         *
        ***********************************************************
*/

#define lc_config(a,b,c,d)             lc_m_config(0,a,b,c,d)
#define lc_int_connect(a,b,c,d)        lc_m_int_connect(0,a,b,c,d)
#define lc_int_disconnect(a)           lc_m_int_disconnect(0,a)
#define lc_get_device_address(a)       lc_m_get_device_address((unsigned short)0,a)
#define lc_set_device_address(a)       lc_m_set_device_address(0,a)
#define lc_get_device_status_word()    lc_m_get_device_status_word(0)
#define lc_set_device_status_word(a,b) lc_m_set_device_status_word(0,a,b)
#define lc_get_service_area_addr()     lc_m_get_service_area_addr(0)
#define lc_go()                        lc_m_go(0)
#define lc_hardw_config(a,b)           lc_m_hardw_config(0,a,b)


/*
 ---------------------------------------------------------------------------

    Functions implemented as macros

 ---------------------------------------------------------------------------
*/

#define lc_memset16(ptr, val, size)      \
        {                                \
        unsigned short ii  = (size);     \
        unsigned short *pp = (unsigned short *) (ptr); \
            while (ii-- != 0)            \
            {                            \
                *pp++ = val;             \
            }                            \
        }

#ifdef __cplusplus 
}
#endif 

#endif                                 /* LC_SYS_H */
   

/****************************************************************************
*****************************************************************************
*                                                                           *
*               TCN APPLICATION PROCESS INTERFACE                           *
*                                                                           *
*****************************************************************************
****************************************************************************/

   

#if defined (__cplusplus)
 extern "C"
 {
#endif


#ifndef APD_INCL_H
#define APD_INCL_H

typedef         unsigned int TYPE_PD_BITFIELD;

/*
 ----------------------------------------------------------------------------

    DS_NAME                            Ref: IEC Part 2, Chapter 2.3.1.2

 ----------------------------------------------------------------------------

*/

typedef struct          STR_APD_DS_NAME
{
#if defined (O_LE)
    TYPE_PD_BITFIELD    prt_addr: 12;
    TYPE_PD_BITFIELD    ts_id   : 4;
#else
    TYPE_PD_BITFIELD    ts_id   : 4;
    TYPE_PD_BITFIELD    prt_addr: 12;
#endif
}                       TYPE_APD_DS_NAME;



/*
 ----------------------------------------------------------------------------

    PV_NAME                            Ref: IEC Part 2, Chapter 2.3.1.2

 ----------------------------------------------------------------------------

*/

#if  defined (O_LE)
#define apd_init_dsn(ts_id, prt_addr) prt_addr, ts_id
#define apd_init_pvn(ts_id, prt_addr, size, bit_o, type, ctl_o) \
        ctl_o, type, bit_o, size, prt_addr, ts_id
#else
#define apd_init_dsn(ts_id, prt_addr) ts_id, prt_addr
#define apd_init_pvn(ts_id, prt_addr, size, bit_o, type, ctl_o) \
        ts_id, prt_addr, size, bit_o, type, ctl_o
#endif

typedef struct          STR_APD_PV_NAME
{
#if defined (O_LE)
    TYPE_PD_BITFIELD    ctl_offset  :10;
    TYPE_PD_BITFIELD    type        : 6;
    TYPE_PD_BITFIELD    bit_offset  :10;
    TYPE_PD_BITFIELD    size        : 6;
    TYPE_PD_BITFIELD    prt_addr    : 12;
    TYPE_PD_BITFIELD    ts_id       : 4;
#else
    TYPE_PD_BITFIELD    ts_id       : 4;
    TYPE_PD_BITFIELD    prt_addr    : 12;
    TYPE_PD_BITFIELD    size        : 6;
    TYPE_PD_BITFIELD    bit_offset  :10;
    TYPE_PD_BITFIELD    type        : 6;
    TYPE_PD_BITFIELD    ctl_offset  :10;
#endif
}                       TYPE_APD_PV_NAME;



/* new page
 ---------------------------------------------------------------------------
|
| type          TYPE_LP_RD_PRT_CFG
|
 ------------   A B S T R A C T   ------------------------------------------



*/

typedef struct  STR_LP_RD_PRT_CFG
{
    unsigned short port_address;
    unsigned char  port_config;
    unsigned char  port_size;
}   TYPE_LP_RD_PRT_CFG;




/*
 ----------------------------------------------------------------------------

    Constants                          Ref: IEC Part 2, Chapter 2.3.2

 ----------------------------------------------------------------------------
*/

typedef int                 TYPE_APD_RESULT;
                                       #if !defined PD_T_RESULT
#define PD_T_RESULT
typedef TYPE_APD_RESULT     TYPE_PD_RESULT;
                                       #endif

#define APD_OK              0
#define APD_PRT_PASSIVE     1
#define APD_ERROR           2
#define APD_CONFIG          3
#define APD_MEMORY          4
#define APD_UNKNOWN_TS      5
#define APD_RANGE           6
#define APD_DATA_TYPE       7

#define APD_TS_ID_MAX       15
#define APD_C_SUBSCRIBERS   5

#define APD_LL_TCN          0
#define APD_LL_FIP          1

#define APD_PASSIVE         0
#define APD_ACTIVE          1

#define APD_CHK_IS_ERROR    0
#define APD_CHK_IS_OK       1
#define APD_CHK_IS_FRCD     2
#define APD_CHK_IS_UDFND    3

/*
 ----------------------------------------------------------------------------

    Cluster Structures                  Ref: IEC Part 2, Chapter 2.3.4

 ----------------------------------------------------------------------------
*/



struct  STR_APD_PV_LIST
{
    void *                  p_appl;
    unsigned char           type;
    unsigned char           size;
    unsigned char           byte_offset;
    unsigned char           bit_offset;
};


struct  STR_APD_PV_SET
{
    struct STR_APD_PV_LIST *p_pv_list;
    unsigned short *        p_refresh;
    void *                  p_pcs;
    void *                  p_prt;
    void *                  p_frc;
    unsigned char           prt_sze;
    unsigned char           c_pv_list;
    unsigned short          ts_id;
    unsigned char           force_active;
    unsigned char           multiple_access;
    struct STR_APD_PV_LIST  pv_list[1];
};

struct  STR_APD_PV_CLUSTER
{
    unsigned short          ts_id;
    unsigned short          c_pv_set;
    struct STR_APD_PV_SET * p_pv_set[1];
};

struct STR_APD_PV_DESCRIPTOR
{
    struct STR_APD_PV_NAME  pv_name;
    void *                  p_value;
    void *                  p_check;
};


/*
 ----------------------------------------------------------------------------

    Cluster Boolean Pack Structures

 ----------------------------------------------------------------------------

    A FUPLA feature

    PAC_2:     Each member of the PAC_2 array has a pointer to the boolean
               and a mask marking the bit position with a "1" in the bitset.

    PAC_1:
*/


struct STR_APD_PAC_2
{
    char *                 p_bool;
    unsigned int           b_mask;
};

struct STR_APD_PAC_1
{
    struct STR_APD_PAC_2 * p_array_of_pac_2;
    unsigned short *       p_bitset;
    unsigned int           c_bools_in_bitset;
};

struct STR_APD_PAC_0
{
    struct STR_APD_PAC_1 * p_array_of_pac_1;
    unsigned int           c_pac_1;
};




/*
 ----------------------------------------------------------------------------

    Static Structure

 ----------------------------------------------------------------------------

    For each traffic store id, a link layer type can be connected.
    At the moment, only the TCN link layer is known. The FIP link layer
    is planned.

*/

struct APD_STR_DTA
{
    struct
    {
        unsigned short in_use ;
        unsigned short ds_name;
        unsigned short param  ;
        void (*p_func) (unsigned short);
    }   subscribed[APD_C_SUBSCRIBERS];
    char ll_type[16];
};


/*
 ----------------------------------------------------------------------------

    Prototypes              Ref: IEC Part 2, Chapter 2.3.3

 ----------------------------------------------------------------------------
*/

/*  Initialisation   */

TYPE_PD_RESULT _apd_init            (void                                  );

TYPE_PD_RESULT  apd_connect_mll     (unsigned int     ts_id,
                                      int              ll_type                       );
/*  put and get variable   */

TYPE_PD_RESULT _apd_put_variable    (const struct STR_APD_PV_DESCRIPTOR * p);

TYPE_PD_RESULT _apd_get_variable    (const struct STR_APD_PV_DESCRIPTOR * p ,
                                      unsigned short *             p_refresh);

/*  put and get data set   */

TYPE_PD_RESULT _apd_put_set         (const struct STR_APD_PV_DESCRIPTOR * p ,
                                      int                           c_pv_set);

TYPE_PD_RESULT _apd_put_set_fast    (const struct STR_APD_PV_SET *        p);

TYPE_PD_RESULT _apd_get_set         (const struct STR_APD_PV_DESCRIPTOR * p ,
                                      unsigned short *             p_refresh ,
                                      int                           c_pv_set);

TYPE_PD_RESULT _apd_get_set_fast    (const struct STR_APD_PV_SET *        p);


/*  put and get clusters   */

TYPE_PD_RESULT _apd_put_cluster     (const struct STR_APD_PV_CLUSTER *    p);

TYPE_PD_RESULT _apd_get_cluster     (const struct STR_APD_PV_CLUSTER *    p);


/*  Force Mechanism        */

TYPE_PD_RESULT _apd_force_variable  (const struct STR_APD_PV_DESCRIPTOR * p);

TYPE_PD_RESULT _apd_unforce_variable(const struct STR_APD_PV_NAME *  p_pv_n);

TYPE_PD_RESULT _apd_unforce_all     (unsigned                     int ts_id);


/*  Subscription           */

TYPE_PD_RESULT _apd_subscribe       (struct STR_APD_DS_NAME *     p_ds_name ,
                                      void (*proc)          (unsigned short) ,
                                      unsigned short               param   );

TYPE_PD_RESULT  _ds_subscribe       (struct STR_APD_DS_NAME *  p_ds_name,
                                     void (*proc) (unsigned short)      ,
                                     unsigned short            param    );
TYPE_PD_RESULT _apd_desubscribe     (struct STR_APD_DS_NAME *     p_ds_name);
TYPE_PD_RESULT _ds_desubscribe      (struct STR_APD_DS_NAME *  p_ds_name);

TYPE_PD_RESULT _apd_pass_subscription(struct STR_APD_DS_NAME*     p_dsn_old ,
                                      struct STR_APD_DS_NAME *     p_dsn_new);

/*  Boolean to Bitset Conversion  */

void            _apd_pack            (const struct STR_APD_PAC_0 *   p_pac_0);

void            _apd_unpack          (const struct STR_APD_PAC_0 *   p_pac_0);

TYPE_PD_RESULT _apd_endian_conversion  (struct STR_APD_PV_NAME * p_pv_name,
                                        void *                   p_var_out,
                                        void *                   p_var_in );

/*  Externally Available Link Layer Extensions   */

TYPE_PD_RESULT _lpd_gen_pv_set      (struct STR_APD_PV_SET *       p_pv_set ,
                                      const struct STR_APD_PV_DESCRIPTOR * p ,
                                      unsigned short *             p_refresh ,
						              int                           c_pv_set);

void            _lpd_mod_pv_set      (struct STR_APD_PV_SET *       p_pv_set ,
                                      char                      force_active ,
						              char                   multiple_access);


TYPE_PD_RESULT  _lpd_rd_prt_cfg       (unsigned int               bus_id,
                                       struct STR_LP_RD_PRT_CFG * p_rd_prt_cfg,
                                       unsigned int *             p_c_prts,
                                       unsigned int               c_prts_max);



/*  Internally Used Link Layer Extensions   */

TYPE_PD_RESULT lpd_gen_pv_list      (struct STR_APD_PV_LIST *     p_pv_list ,
							          const struct STR_APD_PV_DESCRIPTOR * p ,
								      int                           c_pv_set);

TYPE_PD_RESULT lpd_force_variable   (const struct STR_APD_PV_DESCRIPTOR * p);

TYPE_PD_RESULT lpm_mpb_init	        (unsigned short	            offs_bcr);

void		   lpm_mpb_close	    (void                                  );

TYPE_PD_RESULT lpm_read_mpb_setup   (void **                           p_ts ,
                                      unsigned int   *            bap_ioaddr ,
                                      unsigned int   *           mpb_intr_nr);


TYPE_PD_RESULT lpd_unforce_variable (const struct STR_APD_PV_NAME * p_pv_nm);

TYPE_PD_RESULT lpd_subscribe        (struct STR_APD_DS_NAME *    p_ds_name ,
                                      void (*proc)           (unsigned short),
                                      unsigned short                   param ,
                                      int    ix                             );

TYPE_PD_RESULT lpd_desubscribe      (struct STR_APD_DS_NAME *    p_ds_name ,
                                      int    ix                             );

TYPE_PD_RESULT lpd_pass_subscription(struct STR_APD_DS_NAME * p_ds_name_old ,
                                      struct STR_APD_DS_NAME * p_ds_name_new);

#define lpd_sizeof_pv_set(c_pv_set) \
   (unsigned short) ( (sizeof (struct STR_APD_PV_SET) +    \
                      (sizeof (struct STR_APD_PV_LIST) * (2*c_pv_set))) )


typedef struct STR_APD_IND_CALL
{
 unsigned char                       apd_version_info[4];

 TYPE_PD_RESULT (*papd_init)        (       void);

 TYPE_PD_RESULT (*papd_put_variable)(const struct STR_APD_PV_DESCRIPTOR * p);

 TYPE_PD_RESULT (*papd_get_variable)(const struct STR_APD_PV_DESCRIPTOR * p ,
                                      unsigned short *             p_refresh);

 TYPE_PD_RESULT (*papd_put_set     )(const struct STR_APD_PV_DESCRIPTOR * p ,
                                      int                           c_pv_set);

 TYPE_PD_RESULT (*papd_put_set_fast)(const struct STR_APD_PV_SET *        p);

 TYPE_PD_RESULT (*papd_get_set     )(const struct STR_APD_PV_DESCRIPTOR * p ,
                                      unsigned short *             p_refresh ,
                                      int                           c_pv_set);

 TYPE_PD_RESULT (*papd_get_set_fast)(const struct STR_APD_PV_SET *        p);

 TYPE_PD_RESULT (*papd_put_cluster )(const struct STR_APD_PV_CLUSTER *    p);

 TYPE_PD_RESULT (*papd_get_cluster )(const struct STR_APD_PV_CLUSTER *    p);

 TYPE_PD_RESULT (*papd_force_var   )(const struct STR_APD_PV_DESCRIPTOR * p);

 TYPE_PD_RESULT (*papd_unforce_var )(const struct STR_APD_PV_NAME *  p_pv_n);

 TYPE_PD_RESULT (*papd_unforce_all )(unsigned                     int ts_id);

 TYPE_PD_RESULT (*papd_subscribe   )(struct STR_APD_DS_NAME *     p_ds_name ,
                                      void (*proc)  (unsigned short param  ) ,
                                      unsigned short              the_param );

 TYPE_PD_RESULT (*papd_desubscribe )(struct STR_APD_DS_NAME *     p_ds_name);

 TYPE_PD_RESULT (*papd_pass_subscr )(struct STR_APD_DS_NAME * p_ds_name_old ,
                                      struct STR_APD_DS_NAME * p_ds_name_new);

 void            (*papd_pack        )(const struct STR_APD_PAC_0 *   p_pac_0);

 void            (*papd_unpack      )(const struct STR_APD_PAC_0 *   p_pac_0);

 TYPE_PD_RESULT (*plpd_gen_pv_set   )(struct STR_APD_PV_SET *       p_pv_set ,
                                      const struct STR_APD_PV_DESCRIPTOR * p ,
                                      unsigned short *             p_refresh ,
						              int                           c_pv_set);

 void           (*plpd_mod_pv_set   )(struct STR_APD_PV_SET *       p_pv_set ,
						              char                      force_active ,
                                      char                   multiple_access);

 TYPE_PD_RESULT (*plpd_rd_prt_cfg    )(unsigned int                     ts_id,
                                       struct STR_LP_RD_PRT_CFG *p_rd_prt_cfg,
                                       unsigned int *                p_c_prts,
                                       unsigned int               c_prts_max);
 TYPE_PD_RESULT (*pds_subscribe      )(struct STR_APD_DS_NAME *     p_ds_name ,
                                       void (*proc)  (unsigned short param  ) ,
                                       unsigned short              the_param );

 TYPE_PD_RESULT (*pds_desubscribe    )(struct STR_APD_DS_NAME *     p_ds_name);

 TYPE_PD_RESULT (*papd_endian_conv   )(struct STR_APD_PV_NAME * p_pv_name,
                                       void *                   p_var_out,
                                       void *                   p_var_in );

} TYPE_PD_IND_CALL;


/*
 ----------------------------------------------------------------------------
|
|       Function Definitions
|
 ----------------------------------------------------------------------------
*/

extern const TYPE_PD_IND_CALL      pd_ind_call_table;


#define	apd_init                    _apd_init
#define apd_put_variable            _apd_put_variable
#define apd_get_variable            _apd_get_variable
#define apd_put_set                 _apd_put_set
#define apd_put_set_fast            _apd_put_set_fast
#define apd_get_set                 _apd_get_set
#define apd_get_set_fast            _apd_get_set_fast
#define apd_put_cluster             _apd_put_cluster
#define apd_get_cluster             _apd_get_cluster
#define apd_force_variable          _apd_force_variable
#define apd_unforce_variable        _apd_unforce_variable
#define apd_unforce_all             _apd_unforce_all
#define apd_subscribe               _apd_subscribe
#define apd_desubscribe             _apd_desubscribe
#define apd_pass_subscription       _apd_pass_subscription
#define apd_pack                    _apd_pack
#define apd_unpack                  _apd_unpack
#define apd_endian_conversion       _apd_endian_conversion

#define lpd_gen_pv_set              _lpd_gen_pv_set
#define lpd_mod_pv_set              _lpd_mod_pv_set
#define lp_read_port_configuration  _lpd_rd_prt_cfg

#define ds_subscribe                _ds_subscribe
#define ds_desubscribe              _ds_desubscribe





/*
 ----------------------------------------------------------------------------

    Version

 ----------------------------------------------------------------------------

*/

#define PD_VERSION      1
#define PD_RELEASE      3

#define PD_UPDATE       5
#define PD_EVOLUTION    0


#define apd_get_version() \
"Name=RTP-APD MVBC V:1.3.5-D:97-10-27-C: redundancy for several TS     "


#endif


#if defined (__cplusplus)
 }
#endif




  
  
/****************************************************************************
*****************************************************************************
*                                                                           *
*               TCN MVBC SPECIFIC PARAMETERS                                *
*                                                                           *
*****************************************************************************
****************************************************************************/


#ifndef O_LE

    #define O_BIGENDIAN

#endif

/*
******************************************************************************
*                                                                            *
*  A T T E N T I O N :                                                       *
*  -------------------                                                       *
*                                                                            *
*  All MVBC-related constants and data structures must be defined in this    *
*  file.  Do not add your own definitions in your application code.  Code,   *
*  which makes sense to be added in this header file, should be returned     *
*  to me for evaluation and insertion.  Thanks for your cooperation.         *
*                                                                            *
*                                              Georg A. zur Bonsen/BATC      *
*                                                                            *
******************************************************************************
*/

/*
******************************************************************************
* Compile Check                                                              *
******************************************************************************
*/

#ifndef MVBC_H

    #define MVBC_H

#ifdef __cplusplus 
extern "C" {
#endif 


/*  #endif  at bottom of file */

/*
******************************************************************************
* Volatile attribute: Assures that register accesses are not optimized by "C"*
******************************************************************************
*/

#ifndef VOL
   #define VOL volatile
#endif

/*
******************************************************************************
* Data Structure: Bytes and Words                                            *
******************************************************************************
*/

typedef unsigned char  TM_TYPE_BYTE ;
typedef unsigned short TM_TYPE_WORD ;

typedef VOL unsigned short TM_TYPE_RWORD; /* Always accessed directly */

/*
******************************************************************************
* Data Structure: Data Areas and Force Tables                                *
******************************************************************************
*/

typedef union
    {
	TM_TYPE_BYTE   b[ 8];
	TM_TYPE_WORD   w[ 4];
    }
        TM_TYPE_DOCK;

typedef union
    {
	TM_TYPE_BYTE   b[32];
	TM_TYPE_WORD   w[16];
        TM_TYPE_DOCK   dock[4];
    }
	TM_TYPE_PAGE;  /* for 4 docks */

typedef union
    {
	TM_TYPE_PAGE   page[2];
        TM_TYPE_DOCK   pgdc[2][4];
        TM_TYPE_WORD   pgwd[2][16];
    }
	TM_TYPE_DATA;  /* for 4 docks */


#define TM_PAGE_0    0      /* Data Area: Page 0     */
#define TM_PAGE_1    1      /* Data Area: Page 1     */
#define TM_FRC_DATA  0      /* Force Table Data Page */
#define TM_FRC_MASK  1      /* Force Table Mask Page */

/*
*****************************************************************************
* name          tm_data_ptr                 Macro Expression                *
*                                                                           *
* param. in     void           * tm_da      Start address to TM Data Area   *
*               unsigned short   pidx       Port Index (0,1,2,...4095)      *
*                                                                           *
* return value  TM_TYPE_DATA   * p_data     Pointer to selected port        *
*****************************************************************************
* description   Returns pointer to selected port.  When accessing the port, *
*               you can access both pages, even if the port index is not    *
*               divisible by 4. However, for odd port indexes, only the 1st *
*               4 words may be accessed.  For port indexes 2,6,10,...,      *
*               only the 1st 8 words may be accessed.                       *
*****************************************************************************
* history       1   93-08-20   BG Created                                   *
*****************************************************************************
*/

#define tm_data_ptr(tm_da,pidx) \
    ( (TM_TYPE_DATA *) &(( (TM_TYPE_DATA *)(tm_da) )[(pidx)>>2].pgdc[TM_PAGE_0][(pidx)&0x3]) )

/*
*****************************************************************************
* name          tm_1_data_wd                Macro Expression                *
*                                                                           *
* param. in     void           * tm_da      Start address to TM Data Area   *
*               unsigned short   pidx       Port Index (0,1,2,...4095)      *
*               unsigned short   pg         Page = { TM_PAGE_0, TM_PAGE_1 } *
*               unsigned short   wd         Word index, allowed values:     *
*                                           0..15: If pidx = {0,4,8,...4092}*
*                                           0.. 7: If pidx = {2,6,10,..4094}*
*                                           0.. 3: If pidx = {1,3,5,...4095}*
*                                                                           *
* return value  TM_TYPE_WORD     data       Reference to data               *
*****************************************************************************
* description   The macro references a selected port in the Data Area. This *
*               expression can be used on both left and right side of the   *
*               assignment statements.                                      *
*****************************************************************************
* history       1   93-08-20   BG Created                                   *
*****************************************************************************
*/

#define tm_1_data_wd(tm_da,pidx,pg,wd) \
   ((tm_da)[(pidx)>>2].page[pg].dock[(pidx)&0x3].w[wd])


/*
******************************************************************************
* Data Structure: Port Control and Status Register                           *
******************************************************************************
*/

typedef union
    {
        TM_TYPE_WORD   w;
    }
        TM_TYPE_PCS_WORD0;

typedef VOL union
    {
        TM_TYPE_WORD   w;
    }
        TM_TYPE_PCS_WORD1;

typedef VOL union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            TM_TYPE_BYTE    crc1;
            TM_TYPE_BYTE    crc0;
          #else
            TM_TYPE_BYTE    crc0;
            TM_TYPE_BYTE    crc1;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_PCS_CRCS;

typedef VOL struct
    {
        TM_TYPE_PCS_WORD0 word0;
        TM_TYPE_PCS_WORD1 word1;
	TM_TYPE_RWORD     tack;
	TM_TYPE_PCS_CRCS  crcs;
    }
	TM_TYPE_PCS;


/*  !!! & mask */
#define tm_get_pcs(p_pcs, member, mask, offset)          \
            (((((TM_TYPE_PCS *) p_pcs)->member) & (mask)) >> (offset))

#define tm_put_pcs(p_pcs, member, mask, offset, value)  \
        { ((TM_TYPE_PCS *) p_pcs)->member =             \
          (((TM_TYPE_PCS *) p_pcs)->member & ~(mask)) |  \
           (((value) << (offset)) & (mask)) ;}

#define tm_tgl_pcs(p_pcs, member, mask)                 \
        { ((TM_TYPE_PCS *) p_pcs)->member ^= (mask); }

#define tm_put_sa(p_reg, member, mask, offset, value)       \
        {  (p_reg)->member =            \
           ((p_reg)->member & ~(mask)) | (((value) << (offset)) & (mask)) ;}

/*  !!! & mask */
#define tm_get_sa(p_reg, member, mask, offset)          \
            ((((p_reg)->member) & (mask)) >> (offset))

#define tm_tgl_sa(p_reg, member, mask)                 \
            {(p_reg)->member ^= (mask); }

#define tm_act_sa(p_reg, member, mask, offset, value)       \
        {  (p_reg)->member = (((value) << (offset)) & (mask)) ;}


    /* !!! Begin of "New constants in update 1.1" */

                                        /* WORD 0 */
    #define TM_PCS_FCODE_MSK    0xF000
    #define TM_PCS_FCODE_OFF    12

    #define TM_PCS_TYPE_MSK     0x0C00
    #define TM_PCS_TYPE_OFF     10
    #define TM_PCS_TYPE_CLR     0       /* !!! NEW */
    #define TM_PCS_TYPE_SNK     1       /* !!! NEW */
    #define TM_PCS_TYPE_SRC     2       /* !!! NEW */

    #define TM_PCS_DTI_MSK      0x00E0
    #define TM_PCS_DTI_OFF      5
    #define TM_PCS_DTI_6        6       /* !!! NEW  BA SRCE */

    #define TM_PCS_FE_MSK       0x0001
    #define TM_PCS_FE_OFF       0
    #define TM_PCS_FE_CLR       0
    #define TM_PCS_FE_SET       1

    #define TM_PCS_NUM_MSK      0x0002
    #define TM_PCS_NUM_OFF      1
    #define TM_PCS_NUM_CLR      0
    #define TM_PCS_NUM_SET      1

                                        /* WORD 1 */
    #define TM_PCS_VP_MSK       0x0040
    #define TM_PCS_VP_OFF       6
    #define TM_PCS_DIAG_MSK     0x0007  /* !!! new !!! */
    #define TM_PCS_DIAG_OFF     0       /* !!! new !!! */
    #define TM_PCS_DIAG_CLR     0       /* !!! new !!! */
    #define TM_PCS_DIAG_STO     1       /* !!! new !!! */
    #define TM_PCS_DIAG_TERR    2       /* !!! new !!! */
    #define TM_PCS_DIAG_RDY     3       /* !!! new !!! */
    #define TM_PCS_DIAG_BNI     4       /* !!! new !!! */
                                        /* MR VOL */
    #define TM_MR_BUSY_MSK      0x0200
    #define TM_MR_BUSY_OFF      9
    #define TM_MR_BUSY_CLR      0
    #define TM_MR_BUSY_SET      1

                                        /* MFS VOL */
    #define TM_MFS_PRT_ADDR_MSK     0x0FFF
    #define TM_MFS_PRT_ADDR_OFF     0

                                        /* New constants in update 1.3 */
    #define TM_SCR_IL_MSK       TM_SCR_IL_MASK
    #define TM_SCR_IL_OFF       0
    #define TM_SCR_IL_VAL_RST   TM_SCR_IL_RESET
    #define TM_SCR_IL_VAL_CFG   TM_SCR_IL_CONFIG
    #define TM_SCR_IL_VAL_TST   TM_SCR_IL_TEST
    #define TM_SCR_IL_VAL_RUN   TM_SCR_IL_RUNNING

    /* Alternative bit specification for PCS */

    /* F-Codes: use W_FC0, W_FC1, etc */

    #define TM_PCS0_SRC     0x0800
    #define TM_PCS0_SINK    0x0400
    #define TM_PCS0_TWCS    0x0200
    #define TM_PCS0_WA      0x0100
    #define TM_PCS0_DTI7    0x00E0
    #define TM_PCS0_DTI6    0x00C0
    #define TM_PCS0_DTI5    0x00A0
    #define TM_PCS0_DTI4    0x0080
    #define TM_PCS0_DTI3    0x0060
    #define TM_PCS0_DTI2    0x0040
    #define TM_PCS0_DTI1    0x0020
    #define TM_PCS0_CPE1    0x0010
    #define TM_PCS0_CPE0    0x0008
    #define TM_PCS0_QA      0x0004
    #define TM_PCS0_NUM     0x0002
    #define TM_PCS0_FE      0x0001

    #define TM_PCS1_DEC     0xFF00
    #define TM_PCS1_PTD     0x0080
    #define TM_PCS1_VP1     0x0040
    #define TM_PCS1_VP0     0x0000
    #define TM_PCS1_CRC     0x0020
    #define TM_PCS1_SQE     0x0010
    #define TM_PCS1_ALO     0x0008
    #define TM_PCS1_BNI     0x0004
    #define TM_PCS1_TERR    0x0002
    #define TM_PCS1_STO     0x0001

    #define TM_PCS1_DEC_OFF 8


/*
******************************************************************************
* MVBC Message Queue Structure                                               *
******************************************************************************
*/

typedef VOL struct
    {
        TM_TYPE_WORD   p16_data;
        TM_TYPE_WORD   p16_next;
    }
        TM_TYPE_LLR;


/*
*****************************************************************************
* name          tm_p16_to_linear            Macro Expression                *
*                                                                           *
* param. in     unsigned short   p16        16-bit MVBC pointer             *
*               unsigned long    o          Linear address to begin of 256K *
*                                           block where p16 addresses data  *
*                                                                           *
* return value  unsigned long    addr       Linear address to pointed data  *
*****************************************************************************
* description   This macro computes the address from the 16-bit MVBC type   *
*               pointer (used for queues and MF-tables).  Since p16 contains*
*               partial address only (bits 17..0), the upper bits must be   *
*               supplied by parameter 'o'.                                  *
*                                                                           *
* attention     ADDRESS IS LINEAR !!!                                       *
*****************************************************************************
* history       1.0 93-08-20   BG Created                                   *
* history       1.1 94-05-20   BG Corrected                                 *
*****************************************************************************
*/

#define tm_p16_to_linear(p16,o) ( (((unsigned long) (p16))<<2) | ((unsigned long) (o)) )



/*
*****************************************************************************
* name          tm_linear_to_p16            Macro Expression                *
*                                                                           *
* param. in     unsigned long    linear     Linear address                  *
*                                                                           *
* return value  unsigned short   p16        16-bit MVBC type pointer        *
*****************************************************************************
* description   The address is converted to a 16-bit MVBC type pointer by   *
*               extracting bits 17..2 and shifting them 2 bits to the right.*
*                                                                           *
* attention     ADDRESS IS LINEAR !!!                                       *
*****************************************************************************
* history       1   93-08-20   BG Created                                   *
* history       2   94-05-11   Mr: Modification (see top of file) (V. 1.4)  *
*****************************************************************************
*/

#if defined (TM_SIZE_16K)
  #define tm_linear_to_p16(lin)     ( (unsigned short) ((((unsigned long) (lin))>>2) & 0x0FFFL) )

#elif defined (TM_SIZE_32K)
  #define tm_linear_to_p16(lin)     ( (unsigned short) ((((unsigned long) (lin))>>2) & 0x1FFFL) )

#elif defined (TM_SIZE_64K)
  #define tm_linear_to_p16(lin)     ( (unsigned short) ((((unsigned long) (lin))>>2) & 0x3FFFL) )

#else
  #define tm_linear_to_p16(lin)     ( (unsigned short) ((((unsigned long) (lin))>>2) & 0xFFFFL) )

#endif


/*
******************************************************************************
* Data Structure: Queue Descriptor Table                                     *
******************************************************************************
*/

typedef VOL struct
    {
	TM_TYPE_WORD   xmit_q[2];
	TM_TYPE_WORD   rcve_q;
    }
	TM_TYPE_QDT;


/*
******************************************************************************
* Data Structure: Bitmaps of Internal Registers (MVBC)                       *
******************************************************************************
*/

/* Status Control Register: SCR */
/* **************************** */

typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL unsigned int   im    : 1;
            VOL unsigned int   quiet : 1;
            VOL unsigned int   mbc   : 1;
            VOL unsigned int   dmy__ : 1;  /* !!! Unsupported bit */
            VOL unsigned int   tmo   : 2;
            VOL unsigned int   ws    : 2;
            VOL unsigned int   arb   : 2;
            VOL unsigned int   uts   : 1;
            VOL unsigned int   utq   : 1;
            VOL unsigned int   mas   : 1;
            VOL unsigned int   rcev  : 1;
            VOL unsigned int   il    : 2;
            VOL unsigned int   dummy :16;
          #else
            VOL unsigned int   il    : 2;
            VOL unsigned int   rcev  : 1;
            VOL unsigned int   mas   : 1;
            VOL unsigned int   utq   : 1;
            VOL unsigned int   uts   : 1;
            VOL unsigned int   arb   : 2;
            VOL unsigned int   ws    : 2;
            VOL unsigned int   tmo   : 2;
            VOL unsigned int   dmy__ : 1;  /* !!! Unsupported bit */
            VOL unsigned int   mbc   : 1;
            VOL unsigned int   quiet : 1;
            VOL unsigned int   im    : 1;
            VOL unsigned int   dummy :16;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_SCR;

    #define TM_SCRX_WS_0     0
    #define TM_SCRX_WS_1     1
    #define TM_SCRX_WS_2     2
    #define TM_SCRX_WS_3     3

    #define TM_SCRX_ARB_0    0
    #define TM_SCRX_ARB_1    1
    #define TM_SCRX_ARB_2    2
    #define TM_SCRX_ARB_3    3

    #define TM_SCRX_TMO_21US 0
    #define TM_SCRX_TMO_43US 1
    #define TM_SCRX_TMO_64US 2
    #define TM_SCRX_TMO_83US 3

    /* Following two lines identifies TMO in microsecond value */

    #define TM_SCRV_TMO_SIZE 4     /* Vector size */
    #define TM_SCRV_TMO_US         { 21, 43, 64, 85 }

    /* Alternative: 16-bit Mask Values */

    #define TM_SCR_IM       0x8000
    #define TM_SCR_QUIET    0x4000
    #define TM_SCR_MBC      0x2000

    #define TM_SCR_TMO_MASK 0x0C00
    #define TM_SCR_TMO_83US 0x0C00
    #define TM_SCR_TMO_64US 0x0800
    #define TM_SCR_TMO_43US 0x0400
    #define TM_SCR_TMO_21US 0x0000

    #define TM_SCR_WS_MASK  0x0300
    #define TM_SCR_WS_3     0x0300
    #define TM_SCR_WS_2     0x0200
    #define TM_SCR_WS_1     0x0100
    #define TM_SCR_WS_0     0x0000

    #define TM_SCR_ARB_MASK 0x00C0
    #define TM_SCR_ARB_3    0x00C0
    #define TM_SCR_ARB_2    0x0080
    #define TM_SCR_ARB_1    0x0040
    #define TM_SCR_ARB_0    0x0000

    #define TM_SCR_UTS      0x0020
    #define TM_SCR_UTQ      0x0010
    #define TM_SCR_MAS      0x0008
    #define TM_SCR_RCEV     0x0004

    #define TM_SCR_IL_MASK    0x0003
    #define TM_SCR_IL_RUNNING 0x0003
    #define TM_SCR_IL_TEST    0x0002
    #define TM_SCR_IL_CONFIG  0x0001
    #define TM_SCR_IL_RESET   0x0000

    #define TM_SCR_MAS_SET  0x0001    /*  !!! new   */
    #define TM_SCR_MAS_CLR  0x0000    /*  !!! new   */
    #define TM_SCR_MAS_MSK  0x0008    /*  !!! new   */
    #define TM_SCR_MAS_OFF  3         /*  !!! new   */

/* Memory Configuration Register: MCR */
/* ********************************** */


typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL unsigned int   rev_idx: 5;  /* New: Revision Index  */
			VOL unsigned int   dmad   : 1;  /* DMA Direct     - MVBC 02 only */
			VOL unsigned int   po     : 2;  /* Port Offset    - MVBC 02 only */
			VOL unsigned int   icd    : 1;  /* Intercyc Delay - MVBC 02 only */
            VOL unsigned int   mo     : 2;  /* MF Table Offset      */
            VOL unsigned int   qo     : 2;  /* Queue Addr Offset    */
            VOL unsigned int   mcm    : 3;  /* Memory Configuration */
            VOL unsigned int   dummy  :16;
          #else
            VOL unsigned int   mcm    : 3;  /* Memory Configuration */
            VOL unsigned int   qo     : 2;  /* Queue Addr Offset    */
            VOL unsigned int   mo     : 2;  /* MF Table Addr Offset */
			VOL unsigned int   icd    : 1;  /* Intercyc Delay - MVBC 02 only */
			VOL unsigned int   po     : 2;  /* Port Offset    - MVBC 02 only */
			VOL unsigned int   dmad   : 1;  /* DMA Direct     - MVBC 02 only */
            VOL unsigned int   rev_idx: 5;  /* New: Revision Index  */
            VOL unsigned int   dummy  :16;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_MCR;

    #define TM_MCM_16K        0
    #define TM_MCM_32K        1
    #define TM_MCM_64K        2
    #define TM_MCM_256K       3
    #define TM_MCM_1M         4

    #define TM_MCR_MO_3       0x0060
    #define TM_MCR_MO_2       0x0040
    #define TM_MCR_MO_1       0x0020
    #define TM_MCR_MO_0       0x0000

    #define TM_MCR_QO_3       0x0018
    #define TM_MCR_QO_2       0x0010
    #define TM_MCR_QO_1       0x0008
    #define TM_MCR_QO_0       0x0000

    #define TM_MCR_PO_3       0x0300
    #define TM_MCR_PO_2       0x0200
    #define TM_MCR_PO_1       0x0100
    #define TM_MCR_PO_0       0x0000

    #define tm_mcr_get_rev_idx(mcr)  ((mcr).b.rev_idx + 1)


/* Decoder Register: DR */
/* ******************** */


typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL unsigned int   dmy__ :  3;  /* !!! Unsupported bits */
			VOL unsigned int   lsm   :  1;  /* Line Sw. Mode  - MVBC 02 only */
			VOL unsigned int   blvl  :  1;  /* Line B level   - MVBC 02 only */
			VOL unsigned int   bchg  :  1;  /* Line B changed - MVBC 02 only */
			VOL unsigned int   alvl  :  1;  /* Line A level   - MVBC 02 only */
			VOL unsigned int   achg  :  1;  /* Line A changed - MVBC 02 only */
			VOL unsigned int   turbo :  1;  /* Turbo 3.0 Mode - MVBC 02 only */
			VOL unsigned int   opto  :  1;  /* Fiber Opto     - MVBC 02 only */
			VOL unsigned int   trafo :  1;  /* Trafo EMDB     - MVBC 02 only */
			VOL unsigned int   wtr   :  1;  /* Wait Timeout   - MVBC 02 only */
            VOL unsigned int   laa   :  1;  /* Line A active        */
            VOL unsigned int   rld   :  1;  /* Red. Line disturbed  */
            VOL unsigned int   ls    :  1;  /* Line Switch          */
            VOL unsigned int   slm   :  1;  /* Single Line Mode     */
            VOL unsigned int   dummy : 16;
          #else
            VOL unsigned int   slm   :  1;  /* Single Line Mode     */
            VOL unsigned int   ls    :  1;  /* Line Switch          */
            VOL unsigned int   rld   :  1;  /* Red. Line disturbed  */
            VOL unsigned int   laa   :  1;  /* Line A active        */
			VOL unsigned int   wtr   :  1;  /* Wait Timeout   - MVBC 02 only */
			VOL unsigned int   trafo :  1;  /* Trafo EMDB     - MVBC 02 only */
			VOL unsigned int   opto  :  1;  /* Fiber Opto     - MVBC 02 only */
			VOL unsigned int   turbo :  1;  /* Turbo 3.0 Mode - MVBC 02 only */
			VOL unsigned int   achg  :  1;  /* Line A changed - MVBC 02 only */
			VOL unsigned int   alvl  :  1;  /* Line A level   - MVBC 02 only */
			VOL unsigned int   bchg  :  1;  /* Line B changed - MVBC 02 only */
			VOL unsigned int   blvl  :  1;  /* Line B level   - MVBC 02 only */
			VOL unsigned int   lsm   :  1;  /* Line Sw. Mode  - MVBC 02 only */
            VOL unsigned int   dmy__ :  3;  /* !!! Unsupported bits */
            VOL unsigned int   dummy : 16;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_DR;

    /* Alternative definition: integer masks */

    #define TM_DR_LSM    0x1000  /* MVBC 02 only */
    #define TM_DR_BLVL   0x0800  /* MVBC 02 only */
    #define TM_DR_BCHG   0x0400  /* MVBC 02 only */
    #define TM_DR_ALVL   0x0200  /* MVBC 02 only */
    #define TM_DR_ACHG   0x0100  /* MVBC 02 only */
    #define TM_DR_TURBO  0x0080  /* MVBC 02 only */
    #define TM_DR_OPTO   0x0040  /* MVBC 02 only */
    #define TM_DR_TRAFO  0x0020  /* MVBC 02 only */
    #define TM_DR_WTR    0x0010  /* MVBC 02 only */
    #define TM_DR_LAA    0x0008
    #define TM_DR_RLD    0x0004
    #define TM_DR_LS     0x0002
    #define TM_DR_SLM    0x0001


/* Sink-Time Supervision Register: STSR */
/* ************************************ */


typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL unsigned int   interv:  4;
            VOL unsigned int   range : 12;
            VOL unsigned int   dummy : 16;
          #else
            VOL unsigned int   range : 12;
            VOL unsigned int   interv:  4;
            VOL unsigned int   dummy : 16;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_STSR;

    #define TM_STSR_INTERV_OFF      0
    #define TM_STSR_INTERV_1MS      1
    #define TM_STSR_INTERV_2MS      2
    #define TM_STSR_INTERV_4MS      3
    #define TM_STSR_INTERV_8MS      4
    #define TM_STSR_INTERV_16MS     5
    #define TM_STSR_INTERV_32MS     6
    #define TM_STSR_INTERV_64MS     7
    #define TM_STSR_INTERV_128MS    8
    #define TM_STSR_INTERV_256MS    9



/* Master Register: MR */
/* ******************* */

typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL unsigned int   par1  : 1;
            VOL unsigned int   par0  : 1;
            VOL unsigned int   ea1   : 1;
            VOL unsigned int   ea0   : 1;
            VOL unsigned int   ec1   : 1;
            VOL unsigned int   ec0   : 1;
            VOL unsigned int   busy  : 1;
            VOL unsigned int   csmf  : 1;
            VOL unsigned int   smf   : 2;
            VOL unsigned int   smfm  : 1;
            VOL unsigned int   size  : 5;
            VOL unsigned int   dummy : 16;
          #else
            VOL unsigned int   size  : 5;
            VOL unsigned int   smfm  : 1;
            VOL unsigned int   smf   : 2;
            VOL unsigned int   csmf  : 1;
            VOL unsigned int   busy  : 1;
            VOL unsigned int   ec0   : 1;
            VOL unsigned int   ec1   : 1;
            VOL unsigned int   ea0   : 1;
            VOL unsigned int   ea1   : 1;
            VOL unsigned int   par0  : 1;
            VOL unsigned int   par1  : 1;
            VOL unsigned int   dummy :16;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_MR;

    /* Alternative definition: integer masks */

    #define TM_MR_SMFM   0x0020
    #define TM_MR_SMFA   0x0040
    #define TM_MR_SMFT   0x0080
    #define TM_MR_SMFE   0x00C0
    #define TM_MR_CSMF   0x0100
    #define TM_MR_BUSY   0x0200
    #define TM_MR_EC0    0x0400
    #define TM_MR_EC1    0x0800
    #define TM_MR_EA0    0x1000
    #define TM_MR_EA1    0x2000
    #define TM_MR_PAR0   0x4000
    #define TM_MR_PAR1   0x8000

    #define TM_MR_CSMF_SET   0x0001     /* !!! new */
    #define TM_MR_CSMF_MSK   0x0100     /* !!! new */
    #define TM_MR_CSMF_OFF   8          /* !!! new */

    #define TM_MR_SMFM_SET   0x0001     /* !!! new */
    #define TM_MR_SMFM_MSK   0x0020     /* !!! new */
    #define TM_MR_SMFM_OFF   5          /* !!! new */

    #define TM_MR_SMFX_MSK   0x00DF     /* !!! new */
    #define TM_MR_SMFX_OFF   0          /* !!! new */

    #define TM_MR_SMFE_SET   0x00C0     /* !!! new */

    /* Bit field 'smf' only: Valid values, for both MR and MR2 */

    #define TM_MRX_MONE    0;
    #define TM_MRX_SMFA    1;
    #define TM_MRX_SMFT    2;
    #define TM_MRX_SMFE    3;


/* Secondary Master Register: MR2 */
/* ****************************** */


/* !!! Use TM_TYPE_MR, but following bits are ignored: */
/*     par1, par0, ea1, ea0, ec1, ec0, busy, csmf      */

/* Interrupt 0 Registers: IMR0, ISR0, IVR0 */
/* *************************************** */

typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL unsigned int   emf   : 1;
            VOL unsigned int   esf   : 1;
            VOL unsigned int   dmf   : 1;
            VOL unsigned int   dsf   : 1;
            VOL unsigned int   amfx  : 1;
            VOL unsigned int   mfc   : 1;
            VOL unsigned int   sfc   : 1;
            VOL unsigned int   rti   : 1;
            VOL unsigned int   bti   : 1;
            VOL unsigned int   dti7  : 1;
            VOL unsigned int   dti6  : 1;
            VOL unsigned int   dti5  : 1;
            VOL unsigned int   dti4  : 1;
            VOL unsigned int   dti3  : 1;
            VOL unsigned int   dti2  : 1;
            VOL unsigned int   dti1  : 1;
            VOL unsigned int   dummy :16;
          #else
            VOL unsigned int   dti1  : 1;
            VOL unsigned int   dti2  : 1;
            VOL unsigned int   dti3  : 1;
            VOL unsigned int   dti4  : 1;
            VOL unsigned int   dti5  : 1;
            VOL unsigned int   dti6  : 1;
            VOL unsigned int   dti7  : 1;
            VOL unsigned int   bti   : 1;
            VOL unsigned int   rti   : 1;
            VOL unsigned int   sfc   : 1;
            VOL unsigned int   mfc   : 1;
            VOL unsigned int   amfx  : 1;
            VOL unsigned int   dsf   : 1;
            VOL unsigned int   dmf   : 1;
            VOL unsigned int   esf   : 1;
            VOL unsigned int   emf   : 1;
            VOL unsigned int   dummy :16;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_I0;

    /* Alternative definition: integer masks */

    #define TM_I0_EMF    0x8000
    #define TM_I0_ESF    0x4000
    #define TM_I0_DMF    0x2000
    #define TM_I0_DSF    0x1000
    #define TM_I0_AMFX   0x0800
    #define TM_I0_MFC    0x0400
    #define TM_I0_SFC    0x0200
    #define TM_I0_RTI    0x0100
    #define TM_I0_BTI    0x0080

    #define TM_I0_DTI    0x007F

    #define TM_I0_DTI7   0x0040
    #define TM_I0_DTI6   0x0020
    #define TM_I0_DTI5   0x0010
    #define TM_I0_DTI4   0x0008
    #define TM_I0_DTI3   0x0004
    #define TM_I0_DTI2   0x0002
    #define TM_I0_DTI1   0x0001


/* Dispatch Pointer Register: DPR */
/* ****************************** */

    #define TM_DPR_MASK  0xFFFC   /* Lower 2 bits are zero */



/* Interrupt 1 Registers: IMR1, ISR1, IVR1 */
/* *************************************** */

typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL unsigned int   ti2   : 1;
            VOL unsigned int   xi3   : 1;
            VOL unsigned int   xi2   : 1;
            VOL unsigned int   xqe   : 1;
            VOL unsigned int   rqe   : 1;
            VOL unsigned int   xq1c  : 1;
            VOL unsigned int   xq0c  : 1;
            VOL unsigned int   rqc   : 1;
            VOL unsigned int   fev   : 1;
            VOL unsigned int   dmy__ : 4;
            VOL unsigned int   ti1   : 1;
            VOL unsigned int   xi1   : 1;
            VOL unsigned int   xi0   : 1;
            VOL unsigned int   dummy :16;
          #else
            VOL unsigned int   xi0   : 1;
            VOL unsigned int   xi1   : 1;
            VOL unsigned int   ti1   : 1;
            VOL unsigned int   dmy__ : 4;
            VOL unsigned int   fev   : 1;
            VOL unsigned int   rqc   : 1;
            VOL unsigned int   xq0c  : 1;
            VOL unsigned int   xq1c  : 1;
            VOL unsigned int   rqe   : 1;
            VOL unsigned int   xqe   : 1;
            VOL unsigned int   xi2   : 1;
            VOL unsigned int   xi3   : 1;
            VOL unsigned int   ti2   : 1;
            VOL unsigned int   dummy :16;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_I1;


    /* Alternative definition: integer masks */

    #define TM_I1_TI2    0x8000
    #define TM_I1_XI3    0x4000
    #define TM_I1_XI2    0x2000
    #define TM_I1_XQE    0x1000
    #define TM_I1_RQE    0x0800
    #define TM_I1_XQ1C   0x0400
    #define TM_I1_XQ0C   0x0200
    #define TM_I1_RQC    0x0100
    #define TM_I1_FEV    0x0080
    #define TM_I1_TI1    0x0004
    #define TM_I1_XI1    0x0002
    #define TM_I1_XI0    0x0001


/* Interrupt Vector Register IVR0/1 */
/* ******************************** */

typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL TM_TYPE_BYTE    iav;
            VOL TM_TYPE_BYTE    vec;
            VOL TM_TYPE_WORD  dummy;
          #else
            VOL TM_TYPE_BYTE    vec;
            VOL TM_TYPE_BYTE    iav;
            VOL TM_TYPE_WORD  dummy;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_IVR;

    /* Alternative definition: integer masks */

    #define TM_IVR_IAV   0x0100
    #define TM_IVR_MASK  0x00FF



/* Device Address Override Key DAOK */
/* ******************************** */

    #define	TM_DAOK_ENABLE	 0x94	/* Enable override  (Wr)             */
    #define	TM_DAOK_DISABLE	 0x49	/* Disable override (Wr)             */
    #define	TM_DAOK_ENABLED	 0xFF	/* Enabled Status   (Rd)             */
    #define	TM_DAOK_DISALBED 0x00	/* Disabled Status  (Rd)             */


/* Timer Control Register: TCR */
/* *************************** */

typedef union
    {
        struct
        {
          #ifdef O_BIGENDIAN
            VOL unsigned int   dmy__ : 10;
            VOL unsigned int   rs2   : 1;
            VOL unsigned int   ta2   : 1;
            VOL unsigned int   dmy_0 : 1;
            VOL unsigned int   xsyn  : 1;
            VOL unsigned int   rs1   : 1;
            VOL unsigned int   ta1   : 1;
            VOL unsigned int   dummy :16;
          #else
            VOL unsigned int   ta1   : 1;
            VOL unsigned int   rs1   : 1;
            VOL unsigned int   xsyn  : 1;
            VOL unsigned int   dmy_0 : 1;
            VOL unsigned int   ta2   : 1;
            VOL unsigned int   rs2   : 1;
            VOL unsigned int   dmy__ : 10;
            VOL unsigned int   dummy : 16;
          #endif
        }
            b;
        TM_TYPE_WORD   w;
    }
        TM_TYPE_TCR;

    /* Alternative definition: integer masks */

    #define TM_TCR_RS2   0x0020
    #define TM_TCR_TA2   0x0010
    #define TM_TCR_XSYN  0x0004
    #define TM_TCR_RS1   0x0002
    #define TM_TCR_TA1   0x0001


/*
******************************************************************************
* Data Structure: Internal Registers (MVBC)                                  *
******************************************************************************
*/

typedef VOL struct
    {
	VOL TM_TYPE_SCR     scr;   /* + 0x00 */
	VOL TM_TYPE_MCR     mcr;   /* + 0x04 */
	VOL TM_TYPE_DR      dr;    /* + 0x08 */
	VOL TM_TYPE_STSR    stsr;  /* + 0x0C */

	VOL TM_TYPE_WORD    fc;    /* + 0x10 */
            TM_TYPE_WORD    dmy__12;
	VOL TM_TYPE_WORD    ec;    /* + 0x14 */
            TM_TYPE_WORD    dmy__16;
	VOL TM_TYPE_WORD    mfr;   /* + 0x18 */
            TM_TYPE_WORD    dmy__1A;
	VOL TM_TYPE_WORD    mfre;  /* + 0x1C */
            TM_TYPE_WORD    dmy__1E;

	VOL TM_TYPE_MR      mr;    /* + 0x20 */
	VOL TM_TYPE_MR      mr2;   /* + 0x24 */
	VOL TM_TYPE_WORD    dpr;   /* + 0x28 */
            TM_TYPE_WORD    dmy__2A;
	VOL TM_TYPE_WORD    dpr2;  /* + 0x2C */
            TM_TYPE_WORD    dmy__2E;

	VOL TM_TYPE_I0      ipr0;  /* + 0x30 */
	VOL TM_TYPE_I1      ipr1;  /* + 0x34 */
	VOL TM_TYPE_I0      imr0;  /* + 0x38 */
	VOL TM_TYPE_I1      imr1;  /* + 0x3C */

	VOL TM_TYPE_I0      isr0;  /* + 0x40 */
	VOL TM_TYPE_I1      isr1;  /* + 0x44 */
	VOL TM_TYPE_IVR     ivr0;  /* + 0x48 */
	VOL TM_TYPE_IVR     ivr1;  /* + 0x4C */

	VOL TM_TYPE_WORD    dmy__50[4];
	VOL TM_TYPE_WORD    daor;  /* + 0x58 */
            TM_TYPE_WORD    dmy__5A;
	VOL TM_TYPE_WORD    daok;  /* + 0x5C */
            TM_TYPE_WORD    dmy__5E;

	VOL TM_TYPE_TCR     tcr;   /* + 0x60 */
	VOL TM_TYPE_WORD    dmy__62[6];

	VOL TM_TYPE_WORD    tr1;   /* + 0x70 */
	VOL TM_TYPE_WORD    dmy__72;
	VOL TM_TYPE_WORD    tr2;   /* + 0x74 */
	VOL TM_TYPE_WORD    dmy__76;
	VOL TM_TYPE_WORD    tc1;   /* + 0x78 */
	VOL TM_TYPE_WORD    dmy__7A;
	VOL TM_TYPE_WORD    tc2;   /* + 0x7C */
	VOL TM_TYPE_WORD    dmy__7E;
    }
	TM_TYPE_INT_REGS;


/*
******************************************************************************
* Data Structure: Entire Service Area                                        *
******************************************************************************
*/


typedef struct
    {
        TM_TYPE_DATA     pp_data[ 8];  /* !!! Only 1st  4 of them are used */
        TM_TYPE_PCS      pp_pcs [32];  /* !!! Only 1st 16 of them are used */
        TM_TYPE_WORD     mfs;          /* Master Frame Slot                */
        TM_TYPE_WORD     dmy__1[7];    /* Vacancy between MFS and QDT      */
        TM_TYPE_QDT      qdt;          /* Queue Descriptor Table           */
        TM_TYPE_WORD     dmy__2[53];   /* Vacancy between QDT and 1st reg. */
        TM_TYPE_INT_REGS int_regs;     /* !!! Located inside MVBC          */
    }
        TM_TYPE_SERVICE_AREA;


/* Location of physical ports, needed for pp_pcs and pp_data */

#define TM_PP_FC8     0x0   /* Mastership Offer Source Port             */
#define TM_PP_EFS     0x1   /* Event Frame Sink Port                    */
#define TM_PP_EF0     0x4   /* Event Frame Source Port for Ev. Type = 0 */
#define TM_PP_EF1     0x5   /* Event Frame Source Port for Ev. Type = 1 */

#define TM_PP_MOS     0x6   /* Mastership Offser Sink  Port             */
#define TM_PP_FC15    0x7   /* Device Status Report Source Port         */

#define TM_PP_MSRC    0x8   /* Message Source Port                      */
#define TM_PP_TSRC    0x8   /* Test    Source Port                      */
#define TM_PP_MSNK    0xC   /* Message Sink   Port                      */
#define TM_PP_TSNK    0xC   /* Test    Sink   Port                      */

/* Location of physical ports, needed for pp_pcs and pp_data */


#define TM_SRV_AREA_SIZE         1024
#define TM_SRV_AREA_SIZE_NO_REGS (1024-128)




/*
******************************************************************************
* Locations and sizes of the different TM areas w.r.t MCM                    *
******************************************************************************
*/

#define TM_PORT_COUNT      4096  /* Applies to all ports */

#define TM_OFFSET_COUNT    5

/*      Parameters for MCM = 0 (16K)  1 (32K)  2 (64K)  3 (256K)  4 (1M)  */

#define TM_LA_PCS_OFFSETS  { 0x3000L, 0x3000L, 0xC000L, 0x30000L, 0x30000L }
#define TM_DA_PCS_OFFSETS  { 0x0L,    0x7000L, 0xF000L, 0x4000L , 0x38000L }

#define TM_LA_DATA_OFFSETS { 0x1000L, 0x1000L, 0x4000L, 0x10000L, 0x10000L }
#define TM_DA_DATA_OFFSETS { 0x0L,    0x5000L, 0xE000L, 0x38000L, 0x40000L }
#define TM_LA_FRCE_OFFSETS { 0x2000L, 0x2000L, 0x8000L, 0x20000L, 0x20000L }

#define TM_LA_PIT_OFFSETS  { 0x0000L, 0x0000L, 0x0000L, 0x0000L , 0x0000L  }
#define TM_DA_PIT_OFFSETS  { 0x0L,    0x4000L, 0x2000L, 0x2000L , 0x2000L  }

#define TM_SERVICE_OFFSETS { 0x3C00L, 0x7C00L, 0xFC00L, 0xFC00L , 0xFC00L  }

#define TM_PIT_BYTE_SIZES  { 4096,    4096,    8192,    8192,     8192     }
#define TM_LA_PORT_COUNTS  { 256,     256,     1024,    4096,     4096     }
#define TM_DA_PORT_COUNTS  { 0,       256,     256,     2048,     4096     }

#define TM_MEMORY_SIZES    {16*1024l,32*1024l,64*1024l,256*1024l,1024*1024l}

/* Usage example:     unsigned long la_pcs_offsets[] = TM_LA_PCS_OFFSETS; */


/*
******************************************************************************
*                                                                            *
* Data Structure Usage                                                       *
*                                                                            *
******************************************************************************
*                                                                            *
* Internal Registers:                                                        *
*                                                                            *
* srv_area->int_regs.scr.b.il = 0;    -- Bit type access to Init. Level      *
* srv_area->int_regs.mcr.w    = 0;    -- Word type access                    *
*                                                                            *
* Physical Ports (PCS):                                                      *
*                                                                            *
* srv_area->pp_pcs[TM_PP_EF0].word0.b.f_code = 0;  -- Bit type access        *
* srv_area->pp_pcs[TM_PP_MOS].tack = 0;            -- Word type access       *
*                                                                            *
* Physical Ports (Data):                                                     *
*                                                                            *
* srv_area->pp_data[TM_PP_EF0].word0.b.f_code = 0; -- Bit type access        *
* srv_area->pp_data[TM_PP_MOS].w[i+4*vp] = 0;      -- Word type access       *
* srv_area->pp_data[TM_PP_MOS].b[i+8*vp] = 0;      -- Byte type access       *
*                                                                            *
* Queue Descriptor Table (QDT):                                              *
*                                                                            *
* srv_area->qdt.xmit_q[0] = 0;                     -- Transmit Queues        *
* srv_area->qdt.rcve_q    = 0;                     -- Receive Queues         *
*                                                                            *
* Master Frame Slot (MFS):                                                   *
*                                                                            *
* srv_area->mfs = 0;                               -- 1 Master Frame         *
*                                                                            *
******************************************************************************
*/

/*
******************************************************************************
* Data Structure: Frame Contents                                             *
******************************************************************************
*/


/* Device Statis Word: DSW */
/* *********************** */

typedef union
    {
        TM_TYPE_WORD   w;
    }
        TM_TYPE_DSW;

    /* Alternative definition: integer masks */

    #define TM_DSW_DEVTYPE      0xF000
	#define TM_DSW_DEVTYPE_OFF	12

    #define    TM_DSW_CLASS_1   0xF000
    #define    TM_DSW_CLASS_23  0x0000
    #define    TM_DSW_BRIDGE    0x8000
    #define    TM_DSW_BUS_ADM   0x4000

    #define TM_DSW_RESERVED     0x0F00
    #define TM_DSW_RESERVED_OFF 8

    #define TM_DSW_LAA       0x0080
    #define TM_DSW_RLD       0x0040
    #define TM_DSW_SSD       0x0020
    #define TM_DSW_SDD       0x0010
    #define TM_DSW_SPD       0x0008
    #define TM_DSW_FRC       0x0004
    #define TM_DSW_DNR       0x0002
    #define TM_DSW_SER       0x0001

/*
******************************************************************************
* Universal Constants                                                        *
******************************************************************************
*/

/* Function Code, applies to both PCS Word 0 and Master Frames */

#define	W_FC0		0x0000	/* F-Code 0			     */
#define	W_FC1		0x1000	/* F-Code 1                          */
#define	W_FC2		0x2000	/* F-Code 2                          */
#define	W_FC3		0x3000	/* F-Code 3                          */
#define	W_FC4		0x4000	/* F-Code 4                          */
#define	W_FC5		0x5000	/* F-Code 5                          */
#define	W_FC6		0x6000	/* F-Code 6                          */
#define	W_FC7		0x7000	/* F-Code 7                          */
#define	W_FC8		0x8000	/* F-Code 8                          */
#define	W_FC9		0x9000	/* F-Code 9                          */
#define	W_FC10		0xa000	/* F-Code 10                         */
#define	W_FC11		0xb000	/* F-Code 11                         */
#define	W_FC12		0xc000	/* F-Code 12                         */
#define	W_FC13		0xd000	/* F-Code 13                         */
#define	W_FC14		0xe000	/* F-Code 14                         */
#define	W_FC15		0xf000	/* F-Code 15                         */


/* Communication Mode (CM), found in Master Frame with F-Code = 9 */

#define	CM_PT_TO_PT	0x1000	/* Single-Cast                       */
#define	CM_BROADCAST	0xF000	/* Broadcast                         */
#define	CM_MASK		0xF000	/* Communication Mode Mask           */

/* Event Modes (EM), found in Master Frame with F-Code = 9 */

#define	EM_0		0x0000
#define	EM_1		0x0100
#define	EM_2		0x0200
#define	EM_3		0x0300
#define EM_MASK		0x0F00  /* Event Mode Mask                   */

/* Event Types (ET), found in Master Frame with F-Code = 9 */

#define	ET_0		0x0000
#define	ET_1		0x0010
#define ET_MASK         0x00F0  /* Event Type Mask                   */

/* Device Group Addresses (DGA), found in Master Frame with F-Code = 13 */

#define	DGA_ALL_DEV	0xFFE	/* All  Devices selected             */
#define	DGA_EVEN_DEV	0xFFC	/* Even Devices selected             */
#define	DGA_ODD_DEV	0xFFD	/* Odd  Devices selected             */
#define DGA_MASK        0xFFF   /* Device Group Address Mask         */

#ifdef __cplusplus 
}
#endif 


#endif /* MVBC_H */
  
  
/****************************************************************************
*****************************************************************************
*                                                                           *
*               TCN LINK LAYER PROCESS INTERFACE                            *
*                                                                           *
*****************************************************************************
****************************************************************************/


#if defined (__cplusplus)
 extern "C"
 {
#endif


#ifndef         LP_SYS_H
#define         LP_SYS_H


                                       #if !defined PD_T_RESULT
#define PD_T_RESULT
typedef int                 TYPE_PD_RESULT;
                                       #endif
typedef unsigned int        TYPE_LP_BITFIELD;

/*
 -----------------------------------------------------------------------------
|
|  Macro        pv_name
|
 ------------   A B S T R A C T   --------------------------------------------


   Macros to initialise and access the different types of LP pv name
   (little endian / big endian, 16 and 32 bit aligned bitfields )

*/

#define lp_put_pvn_pvf(pv_name,member,val) {(pv_name)->member = val;}
#define lp_put_pvn_dsn(pv_name,member,val) {(pv_name)->member = val;}
#define lp_get_pvn_pvf(pv_name,member    ) ((pv_name)->member)
#define lp_get_pvn_dsn(pv_name,member    ) ((pv_name)->member)


/*  These macros generate the old "prototype" pv_name structure */
#if defined (O_LE)
    #define lp_init_pvn(dsn, pvf)           {pvf, dsn}
    #define lp_init_dsn(ts_id, prt_addr  )  prt_addr, ts_id
    #define lp_init_pvf(bit_o, size, type)  type, size, bit_o
#else
    #define lp_init_pvn(dsn, pvf)           {dsn, pvf}
    #define lp_init_dsn(ts_id, prt_addr  )  ts_id, prt_addr
    #define lp_init_pvf(bit_o, size, type)  bit_o, size, type
#endif


/*
 -----------------------------------------------------------------------------
| 
| Chapter       union of basic "c" types
|
 ------------   A B S T R A C T   --------------------------------------------


  This union allows an 8-bit, 16-bit or 32 bit access to a variable.

*/

union           UNN_LP_BASIC
{
                unsigned char   uc[1];
                         char   sc[1];
                unsigned short  us[1];
                         short  ss[1];
                unsigned long   ul[1];
                         long   sl[1];
};


/*
 -----------------------------------------------------------------------------
|
| constant     LP_PUT, GET
|
 ----------------------------------------------------------------------------- 


  These constants are used to define the data flow direction. The constants are
  compatible to LP_SRCE (put) and LP_SINK (get). They are used to define the
  operation in macro functions

*/


#define         LP_GET                  1
#define         LP_PUT                  2


/*
 ----------------------------------------------------------------------------- 
| 
| constants     LP_..._MAX
|
 ------------   A B S T R A C T   -------------------------------------------- 
  

  These constants define range boundaries

*/

#define LP_TS_ID_MAX                    15

#define         LP_HW_TYPE_MAX          63
#define         LP_PIT_TYPE_MAX          1

#define         LP_TS_ARRAY_INDEX       (LP_TS_ID_MAX + 1)


/*
 ----------------------------------------------------------------------------- 
| 
| constant      LP_FUP_....
|
 ------------   A B S T R A C T   -------------------------------------------- 
 
 
  Constants are employed to define the "TRUE" and "FALSE" bus values,
  which are compiler independant.


  LP_FUP_TRUE   is defined as bit0 == 1

*/
  
#define         LP_FUP_FALSE            0
#define         LP_FUP_TRUE             1




/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 3.1   TYPE_PV_FORMAT
|
 ------------   A B S T R A C T   -------------------------------------------

  Parameters required to identify a bus data variable.

*/
typedef         struct                  STR_PV_FORMAT
{
#if defined (O_LE)
                TYPE_LP_BITFIELD        type        : 4;
                TYPE_LP_BITFIELD        size        : 4;
                TYPE_LP_BITFIELD        bit_offset  : 8;
#else
                TYPE_LP_BITFIELD        bit_offset  : 8;
                TYPE_LP_BITFIELD        size        : 4;
                TYPE_LP_BITFIELD        type        : 4;
#endif
}                                       TYPE_PV_FORMAT;


/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 3.1   TYPE_DS_NAME
|
 ------------   A B S T R A C T   -------------------------------------------- 
  
  Parameters required to identify a bus data set. 

*/

typedef struct                  STR_DS_NAME
{
#if defined (O_LE)
                TYPE_LP_BITFIELD        prt_addr    : 12;
                TYPE_LP_BITFIELD        ts_id       : 4;
#else
                TYPE_LP_BITFIELD        ts_id       : 4;
                TYPE_LP_BITFIELD        prt_addr    : 12;
#endif
}                                       TYPE_DS_NAME;

typedef struct  STR_DS_NAME_TB
{
                TYPE_LP_BITFIELD        reserved    : 2 ;
                TYPE_LP_BITFIELD        prt_addr    : 10;
                TYPE_LP_BITFIELD        ts_id       : 4;
}               TYPE_DS_NAME_TB;


/*
 -----------------------------------------------------------------------------
|
| Chapter 3.1   TYPE_PV_NAME
|
 ------------   A B S T R A C T   --------------------------------------------

  Parameters required to identify a bus data variable within a device.

*/

#if defined (O_LE)
typedef struct  STR_PV_NAME
{
                TYPE_LP_BITFIELD        type        : 4;
                TYPE_LP_BITFIELD        size        : 4;
                TYPE_LP_BITFIELD        bit_offset  : 8;
                TYPE_LP_BITFIELD        prt_addr    : 12;
                TYPE_LP_BITFIELD        ts_id       : 4;
}               TYPE_PV_NAME;

typedef struct  STR_PV_NAME_TB
{
                TYPE_LP_BITFIELD        type        : 4;
                TYPE_LP_BITFIELD        size        : 4;
                TYPE_LP_BITFIELD        bit_offset  : 10;
                TYPE_LP_BITFIELD        prt_addr    : 10;
                TYPE_LP_BITFIELD        ts_id       : 4;

}               TYPE_PV_NAME_TB;

#else

typedef struct  STR_PV_NAME
{               TYPE_LP_BITFIELD        ts_id       : 4;
                TYPE_LP_BITFIELD        prt_addr    : 12;
                TYPE_LP_BITFIELD        bit_offset  : 8;
                TYPE_LP_BITFIELD        size        : 4;
                TYPE_LP_BITFIELD        type        : 4;
}               TYPE_PV_NAME;

typedef struct  STR_PV_NAME_TB
{
                TYPE_LP_BITFIELD        ts_id       : 4;
                TYPE_LP_BITFIELD        prt_addr    : 10;
                TYPE_LP_BITFIELD        bit_offset  : 10;
                TYPE_LP_BITFIELD        size        : 4;
                TYPE_LP_BITFIELD        type        : 4;

}               TYPE_PV_NAME_TB;

#endif

typedef union   UNN_PV_NAME_TB_VB
{
                TYPE_PV_NAME            vb;
                TYPE_PV_NAME_TB         tb;
}               TYPE_PV_NAME_TB_VB;


/*
 -----------------------------------------------------------------------------
|
| Chapter 3.1   TYPE_LP_TS_...
|
 ------------   A B S T R A C T   --------------------------------------------

  Traffic Store components, memory size definitions for applications.

*/

typedef         struct          STR_LP_PIT_A
{
				unsigned char   prt_addr;

}                               TYPE_LP_PIT_A;


typedef         struct          STR_LP_PIT_B
{
				unsigned short  prt_addr;

}                               TYPE_LP_PIT_B;


#define                         STR_LP_PIT_C            STR_LP_PIT_A
#define                         STR_LP_PIT_D            STR_LP_PIT_B

typedef         struct          STR_LP_PCS_A
{
				unsigned char   pcs_byte[4];

}                               TYPE_LP_PCS_A;


typedef         struct          STR_LP_PCS_B
{
				unsigned char   pcs_byte[8];

}                               TYPE_LP_PCS_B;


typedef         struct          STR_LP_PCS_C
{
				unsigned char   pcs_byte[2];

}                               TYPE_LP_PCS_C;

typedef         struct          STR_LP_PCS_D
{
				unsigned char   pcs_byte[16];

}                               TYPE_LP_PCS_D;

typedef         struct          STR_LP_PGE_A
{
				unsigned char   prt_byte[8];

}                               TYPE_LP_PGE_A;

typedef         struct          STR_LP_PGE_D
{
				unsigned char   prt_byte[128];

}                               TYPE_LP_PGE_D;

typedef         struct          STR_LP_PRT_A
{
				unsigned char   prt_byte[16];

}                               TYPE_LP_PRT_A;

#define         STR_LP_PRT_B    STR_LP_PRT_A
#define         STR_LP_PRT_C    STR_LP_PRT_A

typedef         struct          STR_LP_PRT_D
{
				unsigned char   prt_byte[256];

}                               TYPE_LP_PRT_D;

#define         STR_LP_FRC_A    STR_LP_PRT_A
#define         STR_LP_FRC_B    STR_LP_PRT_A
#define         STR_LP_FRC_C    STR_LP_PRT_A
#define         STR_LP_FRC_D    STR_LP_PRT_D

#define         STR_LP_DEF_A    STR_LP_PGE_A
#define         STR_LP_DEF_B    STR_LP_PGE_A
#define         STR_LP_DEF_C    STR_LP_PGE_A
#define			STR_LP_DEF_D	STR_LP_PGE_D

typedef         struct          STR_LP_MWD
{
				unsigned short  m_accs;
				unsigned short  m_word;

}                               TYPE_LP_MWD;


#define         STR_LP_MWD_A    STR_LP_MWD
#define         STR_LP_MWD_B    STR_LP_MWD
#define         STR_LP_MWD_C    STR_LP_MWD


/* new page
 ----------------------------------------------------------------------------- 
|
| Chapter 3.2   LPS_......
|
 ----------------------------------------------------------------------------- 


  Link Level Status Messages (function values).

        LPS_OK                          Command successfully executed
        LPS_PRT_PASSIVE                 ... Warning: no copying for this var
        LPS_ERROR                       ... Error  : general error (-1)
        LPS_CONFIG                      ... Error  : configuration error
        LPS_MEMORY                      ... Error  : Allocation error
        LPS_UNKNOWN_TS_ID               ... Error  : ts out of range
                                                     ts not created
        LPS_RANGE                       ... port address > port address max
                                        ... port index > port index max
                                        ... indication nr > indication nr max
                                        ... hw_type > hw_type_max
        LPS_UNKNOWN_DATA_TYPE           ... undefined data type used


*/

#define         LPS_OK                  0
#define         LPS_PRT_PASSIVE         1
#define         LPS_ERROR               2
#define         LPS_CONFIG              3
#define         LPS_MEMORY              4
#define         LPS_UNKNOWN_TS_ID       5
#define         LPS_RANGE               6
#define         LPS_UNKNOWN_DATA_TYPE   7
#define         LPS_PRT_ADDR_0          LPS_ERROR

#define         LP_OK                   LPS_OK
#define         LP_PRT_PASSIVE          LPS_PRT_PASSIVE
#define         LP_ERROR                LPS_ERROR
#define         LP_CONFIG               LPS_CONFIG
#define         LP_MEMORY               LPS_MEMORY
#define         LP_UNKNOWN_TS_ID        LPS_UNKNOWN_TS_ID
#define         LP_RANGE                LPS_RANGE
#define         LP_DATA_TYPE            LPS_UNKNOWN_DATA_TYPE

/*
 -----------------------------------------------------------------------------
|
| Chapter 3.2   LP_SIZE_...
|
 ----------------------------------------------------------------------------- 

  These constants are used to configure PV_NAME.

*/

                                                #ifndef         TC_IGNORE
#define         LP_SIZE_BITS                    0x0
#define         LP_SIZE_8                       0x0
#define         LP_SIZE_16                      0x1
#define         LP_SIZE_32                      0x2
#define         LP_SIZE_48                      0x3
#define         LP_SIZE_64                      0x4

#define         lp_size_for_arrays(size_in_bytes) \
                ((((size_in_bytes) + 1) / 2) - 1)

/* These constants have been replaced by macro lp_size_for_arrays (),
   but remain here for compatibility reasons                              */

#define         LP_SIZE_A8_1                    0x0
#define         LP_SIZE_A8_2                    0x0
#define         LP_SIZE_A8_3                    0x1
#define         LP_SIZE_A8_4                    0x1
#define         LP_SIZE_A8_5                    0x2
#define         LP_SIZE_A8_6                    0x2
#define         LP_SIZE_A8_7                    0x3
#define         LP_SIZE_A8_8                    0x3
#define         LP_SIZE_A8_9                    0x4
#define         LP_SIZE_A8_10                   0x4
#define         LP_SIZE_A8_11                   0x5
#define         LP_SIZE_A8_12                   0x5
#define         LP_SIZE_A8_13                   0x6
#define         LP_SIZE_A8_14                   0x6
#define         LP_SIZE_A8_15                   0x7
#define         LP_SIZE_A8_16                   0x7
#define         LP_SIZE_A8_17                   0x8
#define         LP_SIZE_A8_18                   0x8
#define         LP_SIZE_A8_19                   0x9
#define         LP_SIZE_A8_20                   0x9
#define         LP_SIZE_A8_21                   0xA
#define         LP_SIZE_A8_22                   0xA
#define         LP_SIZE_A8_23                   0xB
#define         LP_SIZE_A8_24                   0xB
#define         LP_SIZE_A8_25                   0xC
#define         LP_SIZE_A8_26                   0xC
#define         LP_SIZE_A8_27                   0xD 
#define         LP_SIZE_A8_28                   0xD
#define         LP_SIZE_A8_29                   0xE
#define         LP_SIZE_A8_30                   0xE
#define         LP_SIZE_A8_31                   0xF
#define         LP_SIZE_A8_32                   0xF
/* new page */
#define         LP_SIZE_A16_1                   0x0
#define         LP_SIZE_A16_2                   0x1
#define         LP_SIZE_A16_3                   0x2
#define         LP_SIZE_A16_4                   0x3
#define         LP_SIZE_A16_5                   0x4
#define         LP_SIZE_A16_6                   0x5
#define         LP_SIZE_A16_7                   0x6
#define         LP_SIZE_A16_8                   0x7
#define         LP_SIZE_A16_9                   0x8
#define         LP_SIZE_A16_10                  0x9
#define         LP_SIZE_A16_11                  0xA
#define         LP_SIZE_A16_12                  0xB
#define         LP_SIZE_A16_13                  0xC
#define         LP_SIZE_A16_14                  0xD
#define         LP_SIZE_A16_15                  0xE
#define         LP_SIZE_A16_16                  0xF 

#define         LP_SIZE_A32_1                   0x1
#define         LP_SIZE_A32_2                   0x3
#define         LP_SIZE_A32_3                   0x5
#define         LP_SIZE_A32_4                   0x7
#define         LP_SIZE_A32_5                   0x9
#define         LP_SIZE_A32_6                   0xB
#define         LP_SIZE_A32_7                   0xD
#define         LP_SIZE_A32_8                   0xF
                                                #endif
/* new page
 ----------------------------------------------------------------------------- 
| 
| Chapter 3.2  LP_TYPE_...
|
 ----------------------------------------------------------------------------- 


  These constants are used to configure PV_NAME.

*/

                                                #ifndef         TC_IGNORE

#define         LP_TYPE_BOOL_1                  0x0
#define         LP_TYPE_BOOL_2                  0x1
#define         LP_TYPE_BCD_4                   0x2
#define         LP_TYPE_CHAR                    0x7
#define         LP_TYPE_TIMEDATE                0x2
#define         LP_TYPE_REAL                    0x3
#define         LP_TYPE_BITSET                  0x4
#define         LP_TYPE_CARD                    0x5
#define         LP_TYPE_SIGN                    0x6

#define         LP_TYPE_FRAC_200                0x8
#define         LP_TYPE_FRAC_400                0x9
#define         LP_TYPE_FRAC_800                0xA

#define         LP_TYPE_A8_EVEN                 0xF
#define         LP_TYPE_A8_ODD                  0x7

#define         LP_TYPE_A16_CARD                0xD
#define         LP_TYPE_A16_SIGN                0xE

#define         LP_TYPE_A32_CARD                0xB
#define         LP_TYPE_A32_SIGN                0xC

                                                #endif

/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 3.2   LP_TS_TYPE_...
|
 ----------------------------------------------------------------------------- 

  These constants are used to identify the TS structure types

*/

#define         LP_TS_TYPE_B            0x0001          /* MVB, MVBC        */
#define         LP_TS_TYPE_D            0x0003          /* WTB              */

#define         LP_PIT_TYPE_A           0x0000          /*  8 Bit Port Indx */
#define         LP_PIT_TYPE_B           0x0001          /* 16 Bit Port Indx */
#define         LP_PIT_TYPE_C           LP_PIT_TYPE_A   /*  8 Bit Port Indx */
#define			LP_PIT_TYPE_D			LP_PIT_TYPE_B

#define         LP_PCS_TYPE_A           0x0000          /*  4 Byte PCS      */
#define         LP_PCS_TYPE_B           0x0001          /*  8 Byte PCS      */
#define         LP_PCS_TYPE_C           0x0002          /*  2 Byte PCS      */
#define			LP_PCS_TYPE_D			0x0003			/* 16 Byte PCS      */

#define         LP_PRT_TYPE_A           0x0000          /*  4 x 8 Byte Port */
#define         LP_PRT_TYPE_B           LP_PRT_TYPE_A   /*  4 x 8 Byte Port */
#define         LP_PRT_TYPE_C           LP_PRT_TYPE_A   /*  4 x 8 Byte Port */
#define			LP_PRT_TYPE_D			0x0003

#define         LP_MAGIC_WORD           0xA55A
#define         LP_MBOX_DELAY           500             /*  500 ms          */


/* new page
 ----------------------------------------------------------------------------- 
|
| Chapter 3.2   LP_HW_TYPE_.....
|
 ------------   A B S T R A C T   -------------------------------------------- 
  
  These constants are used to identify the bus (controller)

                                        IEC normed busses (1 ..... 31)
        LP_HW_TYPE_BAP                  MVB old Bus Controller
        LP_HW_TYPE_MVBC                 MVB new Bus Controller
        LP_HW_TYPE_HDLC                 DVB / WTB

                                        Additional busses (32 ..... 63)
        LP_HW_TYPE_MIC_0                No Bus (i.e. intertask commu)
        LP_HW_TYPE_MIC_1                AMS_BUS
        LP_HW_TYPE_MIC_2                P_BUS
        LP_HW_TYPE_MIC_3                Serial EEPROM

*/

#define         LP_HW_TYPE_BAP          0x0000
#define         LP_HW_TYPE_MVBC         0x0001

#define         LP_HW_TYPE_HDLC         9

#define         LP_HW_TYPE_MIC_0        0x0020
#define         LP_HW_TYPE_MIC_1        0x0021
#define         LP_HW_TYPE_MIC_2        0x0022
#define         LP_HW_TYPE_MIC_3        0x0023
#define         LP_HW_TYPE_PCM_0        0x0024







/* new page
 -----------------------------------------------------------------------------
|
| Chapter 4.1   LP_CFG_....
|
 -----------------------------------------------------------------------------

  The port index table can take 8 bit and 16 bit port indexes. The type of
  port index is defined with these constants.

  Configuration constants for PCS size and PCS type (data flow direction)

*/

                                                #ifndef         TC_IGNORE

#define         LP_CFG_TS_ALIEN                  0
#define         LP_CFG_TS_OWNED                  1

#define         LP_CFG_XX_BYTES_MSK              0x7F
#define         LP_CFG_02_BYTES_DSW              (128 + LP_CFG_02_BYTES)
#define         LP_CFG_02_BYTES                  2
#define         LP_CFG_04_BYTES                  4
#define         LP_CFG_08_BYTES                  8
#define         LP_CFG_16_BYTES                 16
#define         LP_CFG_32_BYTES                 32

#define         LP_CFG_000_BYTES                 0   /* WTB SPECIFIC 0...128 */
#define         LP_CFG_128_BYTES               128


                                                #endif

#define         LP_CFG_PASSIVE                   0
#define         LP_CFG_SINK                      1
#define         LP_CFG_SRCE                      2

                                                #ifndef         TC_IGNORE

#define         LP_CFG_BIDIRECTIONAL             3
#define         LP_CFG_BDIR                     LP_CFG_BIDIRECTIONAL

#define         LP_AMS_WINDOW_00000H               0
#define         LP_AMS_WINDOW_40000H            0x10
#define         LP_AMS_WINDOW_80000H            0x20
#define         LP_AMS_WINDOW_C0000H            0x30

#define         LP_AMS_MBOX_00000H              0x00
#define         LP_AMS_MBOX_10000H              0x01
#define         LP_AMS_MBOX_20000H              0x02
#define         LP_AMS_MBOX_30000H              0x03
#define         LP_AMS_MBOX_40000H              0x04
#define         LP_AMS_MBOX_50000H              0x05
#define         LP_AMS_MBOX_60000H              0x06
#define         LP_AMS_MBOX_70000H              0x07
#define         LP_AMS_MBOX_80000H              0x08
#define         LP_AMS_MBOX_90000H              0x09
#define         LP_AMS_MBOX_A0000H              0x0A
#define         LP_AMS_MBOX_B0000H              0x0B
#define         LP_AMS_MBOX_C0000H              0x0C
#define         LP_AMS_MBOX_D0000H              0x0D
#define         LP_AMS_MBOX_E0000H              0x0E
#define         LP_AMS_MBOX_F0000H              0x0F

#define         LP_AMS_DVC_MBOX_OFF             0x00
#define         LP_AMS_DVC_MBOX_ON              0x10

#define         LP_AMS_BUS_MBOX_OFF             0x00
#define         LP_AMS_BUS_MBOX_ON              0x20

#define         LP_AMS_NOT_ANY_RQST             0x00
#define         LP_AMS_ANY_RQST                 0x40

#define         LP_AMS_SLAVE                    0x00
#define         LP_AMS_MASTER                   0x80

#define         LP_AMS_BUS_RESET_ON             0x01
#define         LP_AMS_BUS_RESET_OFF            0x00

#define         LP_AMS_DVC_RESET_ON             0x00
#define         LP_AMS_DVC_RESET_OFF            0x01

                                                #endif


/* new page
 ----------------------------------------------------------------------------- 
| 
| Chapter 4.2   TYPE_LP_PRT_CFG
|
 ------------   A B S T R A C T   -------------------------------------------- 
  

  The parameters required to open a traffic store port are configured in the 
  port configuration list. 

  prt_addr      The port index table is an array of port_nr. This is the
                virtual connection between the port_address and the port_number

  prt_indx      The port_nr defines the port to use for the telegram

  size          Defines the port size in bytes

  type          Defines the port direction (0/1/2: passive / sink / source)

*/

typedef         struct                  STR_LP_PRT_CFG
{
                unsigned short          prt_addr;
                unsigned short          prt_indx;
                unsigned short          size;
                unsigned short          type;

}                                       TYPE_LP_PRT_CFG;

/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 4.2   TYPE_LP_TS_CFG
|
 ------------   A B S T R A C T   ------------------------------------------- 
  

  The parameters required to open a traffic store port are configured in this
  type of list.

  Traffic Stores consist generally of

        - a port index table (pit) used to connect the full range port address
          a reduced range physical data port 

        - port control and status registers (pcs) which are used to store per
          port the port dependant control and status information

        - data ports which store the data alternatively in pages (range 2)

        - a force sub traffic store which consists of force ports which store
          a predefined value to be used instead of the process variable and
          force status registers which are used to decode whether the force
          or the process variable is to be used

  Each element can be either provided (static) or will be created (dynamic) by
  the link process software. A NULL pointer indicates the need to create the
  buffer. At all times, the sizes are supplied.

  It is possible to recreate traffic stores online, e.g. for a train reconfigu-
  ration. 

  pb_pit        A pointer to the base address of the port index table.
                NULL: dynamic allocation from memory utility

  pb_pcs        A pointer to the port communication & status field base address.
                NULL: dynamic allocation from memory utility

  pb_prt        A pointer to the port base address.
                NULL: dynamic allocation from memory utility

  pb_frc        A pointer to the force table base address.
                NULL: dynamic allocation from memory utility

  pb_def        Pointer to buffer with port default values
                NULL: Initialise all ports to zero

  ts_type       LP_TS_TYPE_A ...

  prt_addr_max  Port index table range is 0 .... prt_addr_max

  prt_indx_max  Port range is 0 .... prt_indx_max
                This value determines the range of the port_data, port_pcs and
                force table

  ownership     LP_CFG_TS_ALIEN / LP_CFG_TS_OWNED
                The traffic store can be owned by the caller or by a third
                party located (perhaps) on a different computer behind a
                dual ported RAM

  prt_count     Independant of LP_MAX_PRT_COUNT, the structure is
                terminated after prt_count elements of config_list

  p_prt_cfg     Pointer to the port configuration, see TYPE_LP_PRT_CFG

new page */

typedef         struct                  STR_LP_TS_CFG
{
                void *                  pb_pit;
                void *                  pb_pcs;
                void *                  pb_prt;
                void *                  pb_frc;
                void *                  pb_def;
                void *                  pb_mwd;
                unsigned char           ownership;
                unsigned char           ts_type;
                unsigned short          prt_addr_max;
                unsigned short          prt_indx_max;
                unsigned short          prt_count;
                struct STR_LP_PRT_CFG * p_prt_cfg;

}                                       TYPE_LP_TS_CFG;


/* new page
 ----------------------------------------------------------------------------- 
| 
| Chapter 4.2   TYPE_LP_HW_BAP_CFG
|
 ------------   A B S T R A C T   -------------------------------------------- 
  

  The parameters required to initialise the type BAP bus controller hardware
  are listed here.

*/

typedef         struct          STR_LP_HW_BAP_CFG
{
                void *          p;

}                               TYPE_LP_HW_BAP_CFG;


/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 4.2   TYPE_LP_HW_MIC_1_CFG
|
 ------------   A B S T R A C T   -------------------------------------------- 
  

  The parameters required to initialise the type MICOS_1 bus controller
  hardware are listed here.

        mbox_base       Mail box base address: 00000H, 10000H, ...., F0000H
        bus_base        AMS bus window, 00000H, 40000H, 80000H, F0000H
        master          (0/1) The master (1) provides the AMS bus clock
        any_rqst        low priority master waits for end of bus transfer
                        high priority master gets bus after transfer end
        dvc_resets_bus  device reset does not reset AMS bus
                        device reset causes AMS reset
        bus_resets_dvc  AMS reset does not reset device
                        AMS reset causes device reset
        dvc_mbox        no mailbox access by device
                        mailbox access by device        
        bus_mbox        no mailbox access by AMS bus
                        mailbox access by AMS bus       

*/

typedef         struct          STR_LP_HW_MIC_1_CFG
{
                char            mbox_base;
                char            bus_base;
                char            master;
                char            dvc_resets_bus;
                char            bus_resets_dvc;
                char            dvc_mbox;
                char            bus_mbox;
                char            any_rqst;

}                               TYPE_LP_HW_MIC_1_CFG;

/* new page
 ----------------------------------------------------------------------------- 
| 
| Chapter 4.2   TYPE_LP_HW_MIC_2_CFG
|
 ------------   A B S T R A C T   -------------------------------------------- 
  

  The parameters required to initialise the type MICOS_2 bus controller
  hardware are listed here.

*/

typedef         struct          STR_LP_HW_MIC_2_CFG
{
                void *          p;

}                               TYPE_LP_HW_MIC_2_CFG;


/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 4.2   TYPE_LP_HW_MIC_3_CFG
|
 ------------   A B S T R A C T   -------------------------------------------- 
  

  The parameters required to initialise the type MICOS_2 bus controller
  hardware are listed here.

*/

typedef         struct          STR_LP_HW_MIC_3_CFG
{
                void *          p;

}                               TYPE_LP_HW_MIC_3_CFG;


/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 4.2   Initialisation - Type definitions  TYPE_LP_HW_CFG
|
 ------------   A B S T R A C T   -------------------------------------------- 
  

  The parameters required to initialise the a bus controller hardware are
  listed here as union of all bus controller types.

*/

typedef         union                   UNN_LP_HW_CFG
{
                struct STR_LP_HW_BAP_CFG        bap_1;
                struct STR_LP_HW_MIC_1_CFG      mic_1;
                struct STR_LP_HW_MIC_2_CFG      mic_2;
                struct STR_LP_HW_MIC_3_CFG      mic_3;

}                                       TYPE_LP_HW_CFG;

/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 4.3   Prototypes (connection to user)
|
 ----------------------------------------------------------------------------
*/

                                                #ifndef         TC_IGNORE


/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 4.4   Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_prt_addr_max
|
| param. in     prt_addr                Proposed port address max
|               pit_type                LP_PIT_TYPE_A / LP_CFG_PIT_16
|
| return value  prt_addr_max            next defined prt_addr_max
|
 ------------   A B S T R A C T   ------------------------------------------- 

  Convert proposed port address max to next defined port address max.
  Used to build correct configuration list
*/

#define         lp_prt_addr_max(prt_addr, pit_type) \
                (((((prt_addr) & 1) == 0) & ((pit_type) == LP_PIT_TYPE_A)) ? \
                    (unsigned short) ((prt_addr) + 1) : \
                    (unsigned short)  (prt_addr))

/*
 ----------------------------------------------------------------------------
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  91-11-09  created                   Marsden      --
 ----------------------------------------------------------------------------
End of function lp_prt_addr_max                                            */

/* new page
 ----------------------------------------------------------------------------
|
| Chapter 4.4   Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_prt_blck_addr
|
| param. in     prt_addr                Proposed port address max
|               pit_type                LP_PIT_TYPE_A
|                                       LP_PIT_TYPE_B
|
| return value  prt_addr_max            next defined prt_addr_max
|
 ------------   A B S T R A C T   -------------------------------------------

  Convert proposed port address max to next defined port address max.
  Add "1" as array is from 0 .... prt_addr_max.
  Used to define the traffic store port index table memory.
*/

#define         lp_prt_blck_addr(prt_addr, pit_type) \
                        (lp_prt_addr_max(prt_addr, pit_type) + 1)

/*
 ----------------------------------------------------------------------------
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  91-11-09  created                   Marsden      --
 ----------------------------------------------------------------------------
End of function lp_prt_blck_addr                                           */

/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 4.4   Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_prt_indx_max
|
| param. in     prt_indx                Proposed port index max
|
| return value  prt_indx_max            next defined prt_indx_max
|
 ------------   A B S T R A C T   ------------------------------------------- 

  Convert proposed port index max to next defined port index max.
  Used to build correct configuration list

  !!! Does not yet support the types "B" and "C"

*/

#define         lp_prt_indx_max(prt_indx, prt_type) \
                  ((unsigned short) (prt_indx) | LP_PRT_INDX_MAX_MASK)
/*
 ----------------------------------------------------------------------------
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  91-11-09  created                   Marsden      --
 ----------------------------------------------------------------------------
End of function lp_prt_indx_max                                            */

/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 4.4   Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_prt_blck_indx
|
| param. in     prt_indx                Proposed port index max
|
| return value  prt_indx_max            next defined prt_indx_max
|
 ------------   A B S T R A C T   ------------------------------------------- 

  Convert proposed port index max to next defined port index max.
  Used to define the traffic store port data buffer, pcs, force, def memory.

*/

#define         lp_prt_blck_indx(prt_indx, prt_type) \
                    (lp_prt_indx_max(prt_indx, prt_type) + 1)
/*
 ----------------------------------------------------------------------------
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  91-11-09  created                   Marsden      --
|  0.2  BAEI-2  92-07-02  modified                  Marsden      --
|                         functionality changed
 ----------------------------------------------------------------------------
End of function lp_prt_blck_indx                                           */


/* new page
 ----------------------------------------------------------------------------
|
| Chapter 4.4.5 Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_pit_size
|
| param. in     prt_addr                Proposed port address max
|               pit_type                A, B or C
|
| return value  size                    size in bytes
|
 ------------   A B S T R A C T   ------------------------------------------- 

  Convert proposed port address max to minimum port index table size.

*/

#define         lp_pit_size(prt_addr, pit_type) \
                (pit_type == LP_PIT_TYPE_A ?                    \
                  (lp_prt_blck_addr(prt_addr, pit_type)) :     \
                  (lp_prt_blck_addr(prt_addr, pit_type) << 1) )

/*
 ----------------------------------------------------------------------------- 
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  92-03-20  created                   Marsden      --
 ----------------------------------------------------------------------------- 
End of function lp_pit_size*/


/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 4.4.5 Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_pcs_size
|
| param. in     prt_indx                Proposed prt index max
|               pcs_type                A, B or C
|
| return value  size                    size in bytes
|
 ------------   A B S T R A C T   ------------------------------------------- 

  Convert port index max to minimum required pcs array size in bytes

  LP_PCS_TYPE_A:        4 * (lp_prt_indx_max(prt_indx) + 1)
  LP_PCS_TYPE_B:        8 * (lp_prt_indx_max(prt_indx) + 1)
  LP_PCS_TYPE_C:        2 * (lp_prt_indx_max(prt_indx) + 1)

  !!! Does not yet support the types "B" and "C"

*/

#define         lp_pcs_size(prt_indx, pcs_type) \
                (sizeof(struct STR_LP_PCS_A) * (lp_prt_blck_indx(prt_indx, pcs_type)))

/*
 ----------------------------------------------------------------------------- 
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  92-03-20  created                   Marsden      --
 ----------------------------------------------------------------------------- 
End of function lp_pcs_size*/

/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 4.4.5 Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_prt_size
|
| param. in     prt_indx                Proposed prt index max
|               prt_type                A, B or C
|
| return value  size                    size in bytes
|
 ------------   A B S T R A C T   ------------------------------------------- 

  Convert port index max to minimum required port data array size in bytes

*/

#define         lp_prt_size(prt_indx, prt_type) \
                (sizeof(struct STR_LP_PRT_A) * \
                (lp_prt_blck_indx(prt_indx, prt_type)))

/*
 ----------------------------------------------------------------------------- 
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  92-03-20  created                   Marsden      --
 ----------------------------------------------------------------------------- 
End of function lp_prt_size*/

/* new page
 ---------------------------------------------------------------------------- 
|
| Chapter 4.4.5 Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_frc_size
|
| param. in     prt_indx                Proposed prt index max
|               prt_type                A, B or C
|
| return value  size                    size in bytes
|
 ------------   A B S T R A C T   ------------------------------------------- 

  Convert port index max to minimum required force table size in bytes

*/

#define         lp_frc_size(prt_indx, prt_type) \
                lp_prt_size(prt_indx, prt_type)

/*
 -----------------------------------------------------------------------------
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  92-03-20  created                   Marsden      --
 -----------------------------------------------------------------------------
End of function lp_frc_size */

/* new page
 ----------------------------------------------------------------------------
|
| Chapter 4.4.5 Initialisation - Traffic Store Macro Definitions
|
| macro funct.  lp_def_size
|
| param. in     prt_indx                Proposed prt index max
|               prt_type                A, B or C
|
| return value  size                    size in bytes
|
 ------------   A B S T R A C T   ------------------------------------------- 

  Convert port index max to minimum required default value array size in bytes

*/

#define         lp_def_size(prt_indx, prt_type) \
                (lp_prt_size(prt_indx, prt_type) >> 1)

/*
 ----------------------------------------------------------------------------- 
| Vers  Dept.   YY-MM-DD  Status   Debug Rep.  Ctr  Name     Reference
| ----  ------  --------  -------  ----------  ---  -------  ---------
|  0.1  BAEI-2  92-03-20  created                   Marsden      --
 ----------------------------------------------------------------------------- 
End of function lp_def_size */


#endif

/* new page
 ----------------------------------------------------------------------------- 
| 
| Chapter 5.1   TYPE_LP_CLUS_VAR
|
 ------------   A B S T R A C T   -------------------------------------------- 
  

  The parameters required to update one bus variable within the cluster copy
  list

  pv_name       see TYPE_PV_NAME

  p_var         pointer to the application copy of the bus variable

*/

typedef         struct                  STR_LP_CLUS_VAR
{
                struct STR_PV_NAME      pv_name;
                void *                  p_var;

}                                       TYPE_LP_CLUS_VAR;



/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 5.1   TYPE_LP_CLUS_PRT
|
 ------------   A B S T R A C T   -------------------------------------------- 


  The parameters required to update "var_count" bus variables in one port
  within the cluster copy list.

  p_refresh     pointer to a variable to write the refresh information for a
                data set

  var_count     var_count gives the real count of the var_list array

  p_clus_var    see TYPE_LP_CLUS_VAR

  p_clus_prt    Pointer to parameter set for next port in cluster copy list

*/

typedef         struct                  STR_LP_CLUS_PRT
{
                struct STR_LP_CLUS_PRT* p_clus_prt;
                TYPE_DS_NAME            ds_name;
                unsigned short          prt_indx;
                unsigned short    *     p_refresh;
                TYPE_LP_CLUS_VAR  *     p_clus_var;
                unsigned short          var_count;

}                                       TYPE_LP_CLUS_PRT;

/* new page
 ----------------------------------------------------------------------------- 
| 
| type          TYPE_LP_CLUS_TS
|
 ------------   A B S T R A C T   -------------------------------------------- 


  The parameters required to address "prt_count" ports within the traffic
  store "ts_id".

  ts_id         Identifier to define target traffic store

  ds_count      ds_count gives the real count of elements STR_LP_CLUS_DS

  p_clus_ds     Pointer, see structure STR_LP_CLUS_DS
  
*/

typedef         struct                  STR_LP_CLUS_TS
{
                unsigned short          ts_id;
                unsigned short          ds_count;
                struct STR_LP_CLUS_DS * p_clus_ds;

}                                       TYPE_LP_CLUS_TS;



/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 5.1   TYPE_PV_CLUS
|
 ------------   A B S T R A C T   -------------------------------------------- 


  The parameters required to update the bus variables specified by the
  cluster copy list for "ts_count" different traffic stores.

  ts_count      ts_count gives the real count of pointers to p_clus_ts

  p_clus_ts     see TYPE_LP_CLUS_TS

*/

typedef         struct                  STR_PV_CLUS
{
                unsigned short          ts_count;
                unsigned short          reserved;
                struct STR_LP_CLUS_TS * p_clus_ts[LP_TS_ARRAY_INDEX];

}                                       TYPE_PV_CLUS;



struct          STR_LP_DS_X
{
                unsigned short *        p_refresh;
                void *                  p_pcs;
                void *                  p_prt;
                void *                  p_frc;
                unsigned char           prt_sze;
                unsigned char           pv_x_cnt;
};


struct          STR_LP_PV_X
{
                void *                  p_appl;
                unsigned char           type;
                unsigned char           size;
                unsigned char           byte_offset;
                unsigned char           bit_offset;
};

struct          STR_LP_DS_SET
{
                struct  STR_LP_PV_X *   p_pv_x;
                unsigned short *        p_refresh;
                void *                  p_pcs;
                void *                  p_prt;
                void *                  p_frc;
                unsigned char           prt_sze;
                unsigned char           pv_x_cnt;
                unsigned short          ts_id;
                unsigned char           with_frce;
                unsigned char           with_else;
};

typedef struct  STR_LP_PV_SET
{
                struct STR_PV_NAME      pv_name;
                void *                  p_var;

} TYPE_LP_PV_SET;

typedef struct          STR_LP_CLUS_DS
{
                struct STR_LP_CLUS_DS * p_nxt_lst;
                struct STR_LP_PV_X *    p_dta_lst;
                struct STR_LP_DS_X      ds_x;
} TYPE_LP_CLUS_DS;

                                                #ifndef         TC_IGNORE

#define         LP_VAR_WITHOUT          0

#define         LP_VAR_WITH_FRCE        1
#define         LP_VAR_WITH_ELSE        1


/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 5.3   struct STR_LP_PAC_X
|
 ------------   A B S T R A C T   -------------------------------------------- 


  The pack list structures are a FUPLA feature.

*/

                                                #endif

struct          STR_LP_PAC_2
{
                unsigned short          i_bool;
                unsigned char           zero;
                unsigned char           boff;
};

struct          STR_LP_PAC_1
{
                unsigned short          i_pac_2;
                unsigned short          i_bitset;
                unsigned short          bit_count;
};

struct          STR_LP_PAC_0
{
                unsigned short          i_pac_1;
                unsigned short          pac_1_count;
};


/* new page
 ----------------------------------------------------------------------------- 
| 
| Chapter 7.1   LP_FORCE  constants
|
 ----------------------------------------------------------------------------- 


  Force Constants for force state and force operation parameter

*/

#define         LP_FORCE                1
#define         LP_UNFORCE              0
#define         LP_UNFORCED             LP_UNFORCE
#define         LP_FORCED               LP_FORCE
#define         LP_NO_FORCE             !LP_FORCE


#define         LP_RED_PASSIVE          0
#define         LP_RED_ACTIVE           1

/* new page
 -----------------------------------------------------------------------------
| 
| Chapter 8.1   TYPE_LP_TMO_CLUS_TS
|
 ------------   A B S T R A C T   -------------------------------------------- 


  The parameters required to access the update timeout counters of "prt_count"
  ports within the traffic store "ts_id".

  ts_id         Identifier to define target traffic store

  prt_count     prt_count gives the real count of pointers to prt_list

  p_clus_prt    Pointer to sublist, see TYPE_LP_TMO_CLUS_PRT
  
*/

typedef         struct                  STR_LP_TMO_CLUS_TS
{
                unsigned short          ts_id;
                unsigned short          prt_count;
                struct STR_DS_NAME *    p_ds_name;

}                                       TYPE_LP_TMO_CLUS_TS;



/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 8.1   LP_TMO_...
|
 ----------------------------------------------------------------------------- 


  Timeout Constants for timeout status

*/

#define         LP_TMO_PASSIVE          0
#define         LP_TMO_ACTIVE           1

#define			LP_PASSIVE				0
#define			LP_ACTIVE				1

#define         LP_TMO_MAX_TIME         4096

/*
 ----------------------------------------------------------------------------- 
| 
| Chapter 8.2   TYPE_LP_TMO_CLUS
|
 ------------   A B S T R A C T   -------------------------------------------- 


  The parameters required to update the update counters of "ts_count"
  traffic strores

  ts_count      ts_count gives the real count of pointers to p_clus_ts

  p_clus_ts     see TYPE_LP_CLUS_TO

*/

typedef         struct                          STR_LP_TMO_CLUS
{
                unsigned short                  ts_count;
                unsigned short                  reserved;
                struct STR_LP_TMO_CLUS_TS *     p_clus_ts[LP_TS_ID_MAX + 1];

}                                               TYPE_LP_TMO_CLUS;


                                                #ifndef         TC_IGNORE


#define         LP_PRT_INDX_PASSIVE     0
#define         LP_PRT_ADDR_MAX_MASK    1
#define         LP_PRT_INDX_MAX_MASK    3

#define         LP_PRT_ADDR_MAX_MVB     4095
                                                #endif

/* new page
 --------------------------------------------------------------------------- 
|
| type          TYPE_LP_CB
| 
 ------------   A B S T R A C T   ------------------------------------------ 
  
  
  Structure of the Link Layer Process Control Block. This structure exists
  separately for each created traffic store. The structure is accessed via
  the traffic store id (the control block index).

        pb_pit                  base pointer to port index table
        pb_pcs                  base pointer to port status and comm registers
        pb_prt                  base pointer to port data buffer
        pb_frc                  base pointer to force table
        pit_type                type of pit     (LP_PIT_8 / LP_PIT_16)
        prt_addr_max            port address must not exceed this value
        prt_indx_max            port index must not exceed this value
        pit_mem_type            pit memory type (LPC_STATIC / LPC_DYNAMIC)
        pcs_mem_type            pcs memory type (LPC_STATIC / LPC_DYNAMIC)
        prt_mem_type            prt memory type (LPC_STATIC / LPC_DYNAMIC)
        frc_mem_type            frc memory type (LPC_STATIC / LPC_DYNAMIC)
        irpt_sink               the handler for receive indication is sub-
                                scribed         (LP_IRPT_FREE / LP_IRPT_IN_USE)
        irpt_srce               the handler for sent indication is subscribed
        state                   init state      (LPC_FREE
                                                 LPC_IN_USE
                                                 LPC_ERROR)
        frc_flag                forced data     (LP_UNFORCED / LP_FORCED)
        hw_type                 hardware type   (LP_WTB, LP_BAP_1, LP_MICOS_1)

*/

typedef struct             STR_LP_CB
{
    void *                 pb_pit;
    void *                 pb_pcs;
    void *                 pb_prt;
    void *                 pb_frc;
    void *                 pb_mwd;
    void *                 p_root;              /* root of recyclable mem */
    const struct STR_LP_TS_CFG * p_ts_cfg;
    unsigned int           ts_id;
    unsigned short         prt_addr_max;
    unsigned short         prt_indx_max;
    unsigned char          ts_type;
    unsigned char          hw_type;
    unsigned char          ts_owner;
    unsigned char          pcs_power_of_2;      /* size in powers of 2 */
    unsigned char          irpt_sink;
    unsigned char          irpt_srce;
    unsigned char          frc_flag;
    unsigned char          state;
    unsigned char          f_redundancy;
    unsigned char          reserved;
}   TYPE_LP_CB;



/* new page
 -----------------------------------------------------------------------------
| 
| constant     LP_TYPE
|
 ----------------------------------------------------------------------------- 
*/

typedef         unsigned char           TYPE_LP_8;
typedef         unsigned short          TYPE_LP_16;

typedef         char                    TYPE_LP_BOOL_1;
typedef         char                    TYPE_LP_BOOL_2;
typedef         char                    TYPE_LP_BCD_4;
typedef         char                    TYPE_LP_FLD_8;

typedef         unsigned char           TYPE_LP_BITSET_8;
typedef         unsigned short          TYPE_LP_BITSET_16;
typedef         unsigned long           TYPE_LP_BITSET_32;

typedef         char                    TYPE_LP_CHAR_8;
typedef         unsigned char           TYPE_LP_CARD_8;
typedef         unsigned short          TYPE_LP_CARD_16;
typedef         unsigned long           TYPE_LP_CARD_32;

typedef         unsigned short          TYPE_LP_FRAC_200;
typedef         unsigned short          TYPE_LP_FRAC_400;
typedef         unsigned short          TYPE_LP_FRAC_800;

typedef         char                    TYPE_LP_SIGN_8;
typedef         short                   TYPE_LP_SIGN_16;
typedef         long                    TYPE_LP_SIGN_32;

typedef         char                    TYPE_LP_A8_SIGN;
typedef         short                   TYPE_LP_A16_SIGN;
typedef         long                    TYPE_LP_A32_SIGN;

typedef         unsigned char           TYPE_LP_A8_CARD;
typedef         unsigned short          TYPE_LP_A16_CARD;
typedef         unsigned long           TYPE_LP_A32_CARD;


typedef         struct                  STR_LP_TIMEDATE_48
{
                TYPE_LP_CARD_32 seconds;
                TYPE_LP_CARD_16 ticks;
}                                       TYPE_LP_TIMEDATE_48;




/*
 ----------------------------------------------------------------------------
|
|       Function Prototypes
|
 ----------------------------------------------------------------------------
*/

TYPE_PD_RESULT   _lp_init                (       void);
TYPE_PD_RESULT   _lpm_mbox_req_create    (const  struct STR_LP_TS_CFG *  p_ts_cfg);
TYPE_PD_RESULT   _lp_create              (       unsigned short          ts_id,
                                                 unsigned short          hw_type,
                                          const  struct STR_LP_TS_CFG *  p_ts_cfg,
                                          const  union  UNN_LP_HW_CFG *  p_hw_cfg);
TYPE_PD_RESULT   _lp_redundancy        (       unsigned int            ts_id,
                                        unsigned char           action  );
TYPE_PD_RESULT   _lp_get_p_ts_config   (unsigned int  bus_id,
                                        const struct STR_LP_TS_CFG ** p_p_ts_cfg);
TYPE_PD_RESULT   _lp_cluster             (const  struct STR_PV_CLUS   *  p,
                                          short                   data_flow);
TYPE_PD_RESULT   _lp_get_data_set        (const  struct STR_LP_DS_SET *  p_ds_set);
TYPE_PD_RESULT   _lp_put_data_set        (const  struct STR_LP_DS_SET *  p_ds_set);
TYPE_PD_RESULT   _lp_get_variable        (const  struct STR_LP_PV_SET *  p_pv_set,
                                          unsigned short *        p_refresh);
TYPE_PD_RESULT   _lp_put_variable        (const  struct STR_LP_PV_SET *  p_pv_set);
void             _lpa_pack               (const  struct STR_LP_PAC_0 *   p_pac_0);
void             _lpa_unpack             (const  struct STR_LP_PAC_0 *   p_pac_0);
TYPE_PD_RESULT   _ap_get_variable        (const  struct STR_PV_NAME      pv_name,
                                        void *                  p_variable,
                                        unsigned short *        p_refresh);
TYPE_PD_RESULT   _ap_put_variable        (const  struct STR_PV_NAME      pv_name,
                                        void *                  p_variable);
TYPE_PD_RESULT   _lp_frc_single          (const  struct STR_LP_PV_SET *  p_pv_set,
                                        short                   operation);
TYPE_PD_RESULT   _ap_frc_single          (const  struct STR_PV_NAME      pv_name,
                                        void *                  p_variable,
                                        short                   operation);
TYPE_PD_RESULT   _lpc_frc_flag_sum       (       void);
TYPE_PD_RESULT   _lp_unfrc_all           (       unsigned short          ts_id);

void             _lp_tmo_clr_state       (       void);
TYPE_PD_RESULT   _lp_tmo_get_state       (       void);
void             _lp_tmo_set_state       (       void);
TYPE_PD_RESULT   _lp_tmo_counter         (const  struct STR_LP_TMO_CLUS *p_tmo);
TYPE_PD_RESULT   _lp_subscribe           (       unsigned short          ds_type,
                                          struct STR_DS_NAME      ds_name,
                                          void (*proc) (struct STR_DS_NAME));
TYPE_PD_RESULT   _lp_desubscribe         (       unsigned short          ds_type,
                                          struct STR_DS_NAME      ds_name);
TYPE_PD_RESULT   _lp_pv_size             (const  struct STR_PV_NAME  *   pv_name);

TYPE_PD_RESULT   _lp_endian_conversion   (struct STR_PV_NAME *  p_pv_name,
                                          void *                p_var_out,
                                          void *                p_var_in );

void *  _lpx_gen_clus_ts        (       unsigned short          ts_id,
                                        unsigned short          ds_count);
void *  _lpx_gen_clus_ds        (const  struct STR_DS_NAME *    p_ds_name,
                                 const  struct STR_LP_PV_SET *  p_pv_set,
                                        unsigned short *        p_refresh,
                                        unsigned short          pv_set_cnt);
TYPE_PD_RESULT   _lpx_gen_ds_set(       struct STR_LP_DS_SET *  p_ds_set,
                                        struct STR_LP_PV_X   *  p_pv_x,
                                 const  struct STR_LP_PV_SET *  p_pv_set,
                                        unsigned short *        p_refresh,
                                        unsigned short          pv_set_cnt);
TYPE_PD_RESULT   _lpc_enquiry            (       unsigned short          ts_id,
                                        void *                  p_cb_struct);


void    _lpl_put_pv_x           (       void *                 	p_port,
										struct STR_LP_PV_X *   	p_pv_x,
										unsigned short         	var_count);

void    _lpl_get_pv_x           (       void *                 	p_port,
										struct STR_LP_PV_X *   	p_pv_x,
										unsigned short         	var_count);

TYPE_PD_RESULT   _lp_open_port  (       unsigned int            ts_id,
                                        const struct STR_LP_PRT_CFG *p_cfg);

TYPE_PD_RESULT   _lp_close_port (       unsigned int            ts_id,
                                        unsigned int            prt_addr,
                                        struct STR_LP_PRT_CFG * p_cfg);

TYPE_PD_RESULT   _lp_close_ts    (      unsigned int bus_id);




/* !!! dummy interface !!!*/
TYPE_PD_RESULT  _lp_put_cluster (const  struct STR_PV_CLUS   *  p);
TYPE_PD_RESULT  _lp_get_cluster (const  struct STR_PV_CLUS   *  p);

/*
 -----------------------------
    internal prototypes
 -----------------------------
*/


TYPE_PD_RESULT  lpx_gen_ds_x    (       struct STR_LP_DS_SET *  p_x,
                                 const  struct STR_DS_NAME *    p_ds_name);
TYPE_PD_RESULT  lpx_gen_pv_x    (       struct STR_LP_PV_X *    p_x,
                                 const  struct STR_LP_PV_SET *  p_pv_set,
                                        unsigned short          count);
void            lpx_recycle     (void **                        p_root);

TYPE_PD_RESULT  lpx_remember    (void **                        p_root,
                                 void *                         the_pointer);




typedef         struct                  STR_LP_IND_CALL
{
    unsigned char                       lp_version_info[4];
    TYPE_PD_RESULT (*plp_init)         (void);
    TYPE_PD_RESULT (*plp_create)       (unsigned short          ts_id,
                                        unsigned short          hw_type,
                                  const struct STR_LP_TS_CFG *  p_ts_cfg,
                                  const union  UNN_LP_HW_CFG *  p_hw_cfg);
    TYPE_PD_RESULT (*plp_cluster)      (
                                  const struct STR_PV_CLUS *    p,
                                        short                   data_flow);
    TYPE_PD_RESULT (*plp_get_data_set) (
                                  const struct STR_LP_DS_SET *  p_ds_set);
    TYPE_PD_RESULT (*plp_put_data_set) (
                                  const struct STR_LP_DS_SET *  p_ds_set);
    TYPE_PD_RESULT (*plp_get_variable) (
                                  const struct STR_LP_PV_SET *  p_pv_set,
                                        unsigned short        * p_refresh);
    TYPE_PD_RESULT (*plp_put_variable) (
                                  const struct STR_LP_PV_SET *  p_pv_set);
    void  (*plp_pack)            (const struct STR_LP_PAC_0 *   p_pac_0);
    void  (*plp_unpack)          (const struct STR_LP_PAC_0 *   p_pac_0);
    TYPE_PD_RESULT (*plp_frc_single)   (
                                  const struct STR_LP_PV_SET *  p_pv,
                                        short                   operation);
    TYPE_PD_RESULT (*plp_unfrc_all)    (unsigned short          ts_id);
    TYPE_PD_RESULT (*plp_frc_get_state)(void);
    TYPE_PD_RESULT (*plp_pv_size)      (
                                  const struct STR_PV_NAME *    pv_name);
    TYPE_PD_RESULT (*pap_get_variable) (
                                  const struct STR_PV_NAME      pv_name,
                                        void *                  p_variable,
                                        unsigned short *        p_refresh);
    TYPE_PD_RESULT (*pap_put_variable) (
                                  const struct STR_PV_NAME      pv_name,
                                        void *                  p_variable);
    TYPE_PD_RESULT (*pap_frc_single)   (
                                  const struct STR_PV_NAME      pv_name,
                                        void *                  p_variable,
                                        short                   operation);
    void *(*plp_gen_clus_ts)           (unsigned short          ts_id,
                                        unsigned short          ds_count);
    void *(*plp_gen_clus_ds)    (const  struct STR_DS_NAME *    p_ds_name,
                                 const  struct STR_LP_PV_SET *  p_pv_set,
                                        unsigned short *        p_refresh,
                                        unsigned short          pv_set_cnt);
    TYPE_PD_RESULT (*plp_gen_ds_set)   (struct STR_LP_DS_SET *  p_ds_set,
                                        struct STR_LP_PV_X   *  p_pv_x,
                                 const  struct STR_LP_PV_SET *  p_pv_set,
                                        unsigned short *        p_refresh,
                                        unsigned short          pv_set_cnt);
    TYPE_PD_RESULT (*plp_enquiry)      (unsigned short          ts_id,
                                        void *                  p_cb_struct);
    void  (*plp_get_pv_x)              (void *                  p_port,
                                        struct STR_LP_PV_X *    p_pv_x,
                                        unsigned short          var_count);
    void  (*plp_put_pv_x)              (void *                  p_port,
                                        struct STR_LP_PV_X *    p_pv_x,
                                        unsigned short          var_count);
    TYPE_PD_RESULT (*plp_redundancy)   (unsigned int            ts_id,
                                        unsigned char           action   );
    TYPE_PD_RESULT (*plp_get_p_ts_config)(unsigned int          bus_id,
                                  const struct STR_LP_TS_CFG ** p_p_ts_cfg);
    TYPE_PD_RESULT (*plp_endian_conv)  (struct STR_PV_NAME *    p_pv_name,
                                        void *                  p_var_out,
                                        void *                  p_var_in );
    TYPE_PD_RESULT (*plp_tmo_counter)  (const struct STR_LP_TMO_CLUS *p_tmo);
    void           (*plp_tmo_clr_state)(void);
    TYPE_PD_RESULT (*plp_tmo_get_state)(void);
    void           (*plp_tmo_set_state)(void);
    TYPE_PD_RESULT (*plp_open_port )   (unsigned int            bus_id,
                                        const struct STR_LP_PRT_CFG *p_cfg);
    TYPE_PD_RESULT (*plp_close_port)   (unsigned int            bus_id,
                                        unsigned int            prt_addr,
                                        struct STR_LP_PRT_CFG * p_cfg);
    TYPE_PD_RESULT (*plp_close_ts  )   (unsigned int            bus_id);

}                                       TYPE_LP_IND_CALL;


/*
 ----------------------------------------------------------------------------
|
|       Function Definitions
|
 ----------------------------------------------------------------------------
*/

#define lp_req_create(x,y)     	0	/*   not part of TCN functionality  */

#define	lp_init			     _lp_init
#define lp_create	     	 _lp_create
#define lp_redundancy        _lp_redundancy
#define lp_get_p_ts_config   _lp_get_p_ts_config
#define lp_endian_conversion _lp_endian_conversion
#define	lp_cluster           _lp_cluster
#define	lp_get_data_set		_lp_get_data_set
#define	lp_put_data_set		_lp_put_data_set
#define	lp_get_variable		_lp_get_variable
#define	lp_put_variable		_lp_put_variable
#define	lp_pack		        _lpa_pack
#define	lp_unpack		    _lpa_unpack
#define	lp_frc_single		_lp_frc_single
#define	lp_unfrc_all		_lp_unfrc_all
#define	lp_frc_get_state	_lpc_frc_flag_sum
#define	lp_tmo_clr_state	_lp_tmo_clr_state
#define	lp_tmo_get_state	_lp_tmo_get_state
#define	lp_tmo_set_state	_lp_tmo_set_state
#define	lp_tmo_counter		_lp_tmo_counter
#define	lp_subscribe		_lp_subscribe
#define	lp_pv_size	        _lp_pv_size
#define	lp_gen_clus_ts		_lpx_gen_clus_ts
#define	lp_gen_clus_ds		_lpx_gen_clus_ds
#define	lp_gen_ds_set		_lpx_gen_ds_set
#define	lp_enquiry   		_lpc_enquiry
#define	lp_desubscribe		_lp_desubscribe
#define	lp_put_pv_x	        _lpl_put_pv_x
#define	lp_get_pv_x	        _lpl_get_pv_x

#define	lp_open_port        _lp_open_port
#define	lp_close_port       _lp_close_port
#define	lp_close_ts         _lp_close_ts

#define	ap_get_variable		_ap_get_variable
#define	ap_put_variable		_ap_put_variable
#define	ap_frc_single		_ap_frc_single



#define lp_frc_variable(p_pv_set)       lp_frc_single (p_pv_set, LP_FORCE)
#define lp_unfrc_variable(p_pv_set)     lp_frc_single (p_pv_set, LP_UNFORCE)
#define ap_frc_variable(pv_name, p_var) ap_frc_single (pv_name, p_var, LP_FORCE)
#define ap_unfrc_variable(pv_name)      ap_frc_single (pv_name, NULL, LP_UNFORCE)

#define lp_subscribe_sent(ds_name, proc)       lp_subscribe (LP_CFG_SRCE, ds_name, proc)
#define lp_subscribe_received(ds_name, proc)   lp_subscribe (LP_CFG_SINK, ds_name, proc)

#define lp_desubscribe_sent(ds_name)           lp_desubscribe (LP_CFG_SRCE, ds_name)
#define lp_desubscribe_received(ds_name)       lp_desubscribe (LP_CFG_SINK, ds_name)

#define lp_get_cluster(p_cluster_list)         lp_cluster (p_cluster_list, LP_GET)
#define lp_put_cluster(p_cluster_list)         lp_cluster (p_cluster_list, LP_PUT)

#define ap_force_variable                      ap_frc_variable
#define ap_unforce_variable                    ap_unfrc_variable
#define ap_unforce_all                         lp_unfrc_all

#define ap_get_cluster                         lp_get_cluster
#define ap_put_cluster                         lp_put_cluster

#define ap_get_data_set                        lp_get_data_set
#define ap_put_data_set                        lp_put_data_set

#define ap_ds_subscribe_sent                   lp_subscribe_sent
#define ap_ds_subscribe_received               lp_subscribe_received

#define ap_ds_desubscribe_sent                 lp_desubscribe_sent
#define ap_ds_desubscribe_received             lp_desubscribe_received


/*
 -----------------------------------
  Version Verification Mechanism
 -----------------------------------
*/

#define LP_VERSION       2                      /* Interface check    */
#define LP_RELEASE       9

#define LP_UPDATE        2
#define LP_EVOLUTION     0



#define lp_get_version() \
"Name=RTP-LP MVBC TCN:1.6.0.0:06-01-18-D: dyn. address calc for PPC  "
#endif



#if defined (__cplusplus)
 }
#endif


  

/****************************************************************************
*****************************************************************************
*                                                                           *
*               TCN BUS ADMINISTRATOR INTERFACE                             *
*                                                                           *
*****************************************************************************
****************************************************************************/

#ifndef     BA_INCL_H
#define     BA_INCL_H

#ifdef __cplusplus 
extern "C" {
#endif 


/*  new page
 ----------------------------------------------------------------------------
|
|   Version Information
|
 ----------------------------------------------------------------------------
*/

typedef struct { unsigned short item16[100];} TYPE_USHRT_A100;
typedef struct { unsigned char  bite[50][2]; } TYPE_CHAR_A50X2;


/*  new page
 ----------------------------------------------------------------------------
|
|   contents
|
 ----------------------------------------------------------------------------

    structures

    constants

    functions

*/


/*  new page
 ----------------------------------------------------------------------------
|
|   constants
|
 ----------------------------------------------------------------------------
*/

#ifndef     RET_OK
#define     RET_OK              0
#endif

#ifndef     NULL
#define     NULL                ((void *) 0L)
#endif


#define     BA_ERROR           -1
#define     BA_E               BA_ERROR


#define     BA_CA_CNT           5

#define	    BA_PL_ETH_N_ETL_Y 	0x8000
#define	    BA_PL_ETH_Y_ETL_N 	0x4000
#define	    BA_PL_ETH_Y_ETL_Y 	0xC000

#define     BA_SCAN_KWN_DVC     0
#define     BA_SCAN_ALL_DVC     1
#define     BA_SCAN_QUICK       2


/*  new page
 ----------------------------------------------------------------------------
|
|   structures
|
 ----------------------------------------------------------------------------
*/

struct       BA_STR_CFG_SL
{
	unsigned char  c_low;
    unsigned char  c_hgh;
};

struct       BA_STR_CFG_SCN
{
    unsigned char  c_slot[1024];
};

struct       BA_STR_CFG_KC3
{
    unsigned short kc3_mf[256];
};

struct       BA_STR_CFG_KC4
{
    unsigned short kc4_mf[16];
};

struct       BA_STR_CFG_CTL
{
    unsigned short mf[256];
};

/*  new page
 ----------------------------------------------------------------------------
|
|   structure   Configuration Interface
|
 ----------------------------------------------------------------------------


*/

struct      BA_STR_CONFIGURATION
{
	unsigned short  nu0;                /* not used                     */
    unsigned short  mtvc;               /* master transfer version ctrl */
    unsigned short  t_reply_max;        /* 42 or 64 us                  */
    unsigned short  c_periods_in_macro; /* periods per macro (1024/512) */
    unsigned short  eps;                /* event poll strategy          */
    unsigned short  basic_period;       /* in us!                       */
    unsigned short  c_macros_in_turn;   /* macro cycles per turn        */
    unsigned short  scan_strategy;      /* 0/1: known/all devices       */
    unsigned char   nu1[8];             /* not used                     */
    unsigned short  i_kdl;              /* index p device addr list     */
    unsigned short  i_nu1;              /* not used - was i_rql         */
    unsigned short  i_ctl;              /* index p cyclic transm list   */
    unsigned short  i_bal;              /* index p bus admin list       */
    unsigned short  i_snl;              /* index scan list              */
    unsigned short  i_eol;              /* index p end of list mark     */
};

#define     BA_STR_BA_CFG    BA_STR_CONFIGURATION
#define     BA_STR_BA_CFG_1  BA_STR_CONFIGURATION

/*  new page
 ----------------------------------------------------------------------------
|
|   structure   Cyclic Index Pointer Table
|
 ----------------------------------------------------------------------------

    i_cl        index cycle list, 11 pointers to 11 cycle lists
    i_sl        index split list,  5 pointers to  5 split lists

*/

struct       BA_STR_CYC_IX_PTR_TAB
{
    unsigned short      i_cl[11];
    unsigned short      i_sl[5];
};

struct       BA_STR_SCAN_RESULT
{
    struct   BA_STR_SCAN_RSLT_MBR
    {
        unsigned short      rsp;
        unsigned short      dsw;
    }        sn_rslt[256];
};

struct       BA_STR_POLL_STAT
{
	unsigned long       c_event[256];
};

#define BA_RSP_OK           0
#define BA_RSP_MISSING      1
#define BA_RSP_ERROR        2
#define BA_RSP_NOT_POLLED   3

struct       BA_STR_DIAGNOSIS
{
	unsigned long             c_scan_update;
	unsigned long             c_error_frame;
	unsigned long             c_ref_frame;
	unsigned long             c_poll_event_error;
	unsigned long             c_poll_rsp_total;
	struct BA_STR_POLL_STAT * p_poll_rsp;
	unsigned long             c_poll_rsp;
	unsigned long             s_poll_rsp;
	struct BA_STR_SCAN_RESULT * p_scan_rslt_cl_1;
	unsigned long             c_scan_rslt_cl_1;
	unsigned long             s_scan_rslt_cl_1;
	struct BA_STR_SCAN_RESULT * p_scan_rslt_cl_2p;
	unsigned long             c_scan_rslt_cl_2p;
	unsigned long             s_scan_rslt_cl_2p;
};

struct       BA_STR_ERROR_COUNTERS
{
    unsigned short            c_mcu_deadlock;
    unsigned short            c_csmf_workaround;
    unsigned short            c_amfx_panic;
    unsigned short            c_int_bti_master;
    unsigned short            c_int_bti_slave;
    unsigned short            c_int_tmr2_master;
    unsigned short            c_int_emf_master;
    unsigned short            c_int_emf_slave;
};

/*  new page
 ----------------------------------------------------------------------------
|
|   prototypes
|
 ----------------------------------------------------------------------------

	Two interfaces are available during configuration:
	either :  bam_init () - bam_create () - bam_task ()
	or     :  bam_main ()

	One interface is available to network management:

	bam_diag ()

*/

void    bam_init   (void);

int     bam_create (unsigned int bus_id,
					struct BA_STR_CONFIGURATION *  p_ba_cfg);

void    bam_task   (unsigned int bus_id                    );

void    bam_main   (unsigned int bus_id,
					struct BA_STR_CONFIGURATION *  p_ba_cfg);

void    bam_diag   (unsigned int bus_id,
					void  (*prc_notified) (struct BA_STR_DIAGNOSIS * p_diag));

short   bad_quick_scan (void);

short   bap_single_poll (unsigned char *p_poll_list,
                         unsigned char poll_list_len);

void    bal_error_counters (struct BA_STR_ERROR_COUNTERS * p_err);


typedef struct STR_BA_IND_CALL
{
 unsigned char                       ba_version_info[4];

 void        (*pba_init  )           (       void);

 int         (*pba_create)           (unsigned int bus_id,
									  struct BA_STR_CONFIGURATION * p_cfg);

 void        (*pba_task  )           (unsigned int bus_id                );

 void        (*pba_main  )           (unsigned int	bus_id,
									  struct BA_STR_CONFIGURATION * p_cfg);

 void        (*pba_diag  )           (unsigned int bus_id,
									  void  (*prc_notified)
									 (struct BA_STR_DIAGNOSIS * p_diag)  );

 short       (*pba_quick_scan)       (void);

 short       (*pba_single_poll)      (unsigned char * p_poll_list,
                                      unsigned char poll_list_len);

 void        (*pba_error_counters)   (struct BA_STR_ERROR_COUNTERS * p_err);

} TYPE_BA_IND_CALL;

/*
 ----------------------------------------------------------------------------
|
|       Function Definitions
|
 ----------------------------------------------------------------------------
*/


#define	ba_init                     bam_init
#define	ba_create                   bam_create
#define ba_subscribe_diagnosis      bam_diag
#define ba_main                     bam_main
#define ba_task                     bam_task
#define ba_quick_scan               bad_quick_scan
#define ba_single_poll              bap_single_poll
#define ba_error_counters           bal_error_counters


/*
 ----------------------------------------------------------------------------

    Version

 ----------------------------------------------------------------------------

*/

#define BA_VERSION      1
#define BA_RELEASE      3

#define BA_UPDATE       1
#define BA_EVOLUTION    0


#define ba_get_version() \
"Name=BA MVBC TCN:1.6.0.0:29.08.05-C: MD-arb error fixed "

#ifdef __cplusplus
}
#endif

#endif

  
  
/****************************************************************************
*****************************************************************************
*                                                                           *
*               TCN LAYER MANAGEMENT ENTITY INTERFACE                       *
*                                                                           *
*****************************************************************************
****************************************************************************/


#ifndef LME_SYS_H
  #define LME_SYS_H

#ifdef __cplusplus 
extern "C" {
#endif 


/****************************************************************************
*                                                                           *
*                               defines                                     *
*                                                                           *
****************************************************************************/

#define VERSION  1
#define RELEASE  0
     
/****************************************************************************
*                                                                           *
*  LME return values issue from Process Data Application Layer LME's        *
*                                                                           *
****************************************************************************/

#define LME_APD_OK          0   /* correct function call termination */
#define LME_APD_PRT_PASSIVE 1   /* target data set not active        */
#define LME_APD_ERROR       2   /* unspecified failure               */
#define LME_APD_CONFIG      3   /* configuration error occured       */
#define LME_APD_MEMORY      4   /* not enough memory available       */
#define LME_APD_UNKNOWN_TS  5   /* unknown traffic store             */
#define LME_APD_RANGE       6   /* unspecified out of range error    */
#define LME_APD_DATA_TYPE   7   /* unsuported data type              */


/****************************************************************************
*                                                                           *
*  LME return values issue from Process Data Link Layer LME's               *
*                                                                           *
****************************************************************************/


#define LME_LP_ERROR            -1  /* general error                       */
#define LME_LP_OK                0  /* command successfully executed       */
#define LME_LP_PRT_PASSIVE       1  /* no copying of this variable         */
#define LME_LP_PRT_ADDR_O        2  /* port address overflow               */
#define LME_LP_CONFIG            3  /* configuration error                 */
#define LME_LP_MEMORY            4  /* Allocation error                    */
#define LME_LP_RANGE             5  /* port address > port address max     */
                                    /* port index > port index max         */
                                    /* indication nr > indication nr max   */
                                    /* hw_type > hw_type_max               */
#define LME_LP_UNKNOWN_TS_ID     6  /* traffic store ident. out of range   */
#define LME_LP_UNKNOWN_DATA_TYPE 7  /* undefined data type used            */


/****************************************************************************
*                                                                           *
*  LME return values issue from Link Layer Common LME's (MVB)               *
*                                                                           *
****************************************************************************/


#define LME_LC_OK             0   /* operation terminated successfully */
#define LME_LC_REJECT        !0   /* operation failed                  */


/****************************************************************************
*                                                                           *
*  LME return values issue from Message Data LME's                          *
*                                                                           *
****************************************************************************/


#define LME_AM_OK                   0  /* normal success                   */
#define LME_AM_FAILURE              1  /* unspecified failure              */
#define LME_AM_BUS_ERR              2  /* no bus transmission possible     */
#define LME_AM_REM_CONN_OVF         3  /* too many incoming connections    */
#define LME_AM_CONN_TMO_ERR         4  /* connect request not answered     */
#define LME_AM_SEND_TMO_ERR         5  /* send timeout (connect was ok)    */
#define LME_AM_REPLY_TMO_ERR        6  /* no reply received                */
#define LME_AM_ALIVE_TMO_ERR        7  /* no complete message received     */
#define LME_AM_NO_LOC_MEM_ERR       8  /* not enough memory                */
#define LME_AM_NO_REM_MEM_ERR       9  /* not enough memory at partner     */
#define LME_AM_REM_CANC_ERR         10 /* cancelled by partner             */
#define LME_AM_ALREADY_USED         11 /* same operation already done      */
#define LME_AM_ADDR_FMT_ERR         12 /* address format error             */
#define LME_AM_NO_REPLY_EXP_ERR	    13 /* no such reply expected           */
#define LME_AM_NR_OF_CALLS_OVF      14 /* too many calls requested         */
#define LME_AM_REPLY_LEN_OVF        15 /* reply message too long           */
#define LME_AM_DUPL_LINK_ERR        16 /* duplicated link error            */
#define LME_AM_MY_DEV_UNKNOWN_ERR   17 /* my device unknown or not valid   */
#define LME_AM_NO_READY_INST_ERR    18 /* no ready replier  instance       */
#define LME_AM_NR_OF_INST_OVF       19 /* too many replier instances       */
#define LME_AM_CALL_LEN_OVF         20 /* call message too long            */
#define LME_AM_UNKNOWN_DEST_ERR     21 /* partner unknown (not existing)   */
#define LME_AM_INAUG_ERR            22 /* train inauguration occurred      */
#define LME_AM_TRY_LATER_ERR        23 /* (internally used only)           */
#define LME_AM_DEST_NOT_REG_ERR	    24 /* not registered at caller's site  */
#define LME_AM_GW_DEST_NOT_REG_ERR  25 /* dest. not registered on gateway  */
#define LME_AM_GW_SRC_NOT_REG_ERR   26 /* source not registered on gateway */


/****************************************************************************
*                                                                           *
*                           Connection to the user                          *
*                                                                           *
****************************************************************************/


#define lme_lc_read_mvb_status          lc_read_mvb_status
#define lme_ba_task                     bam_main
#define lme_lc_mvb_line                 lc_mvb_line
#define lme_ba_subscribe_diagnosis      ba_subscribe_diagnosis
#define lme_lp_read_port_configuration  lp_read_port_configuration
#define lme_apd_get_variable            apd_get_variable
#define lme_apd_force_variable          apd_force_variable
#define lme_apd_unforce_variable        apd_unforce_variable
#define lme_apd_unforce_all             apd_unforce_all
#define lme_am_read_messenger_status    am_read_messenger_status
#define lme_am_write_messenger_control  am_write_messenger_control
#define lme_am_get_fdir_entry           am_get_dir_entry
#define lme_am_insert_fdir_entries      am_insert_dir_entries
#define lme_am_sdir_read                am_st_read
#define lme_am_sdir_write               am_st_write
#define lme_am_is_member_of_gdir        am_is_member_of
#define lme_am_write_gdir               am_join_groups
#define lme_am_leave_gdir               am_leave_groups


/****************************************************************************
*                                                                           *
*                            types                                          *
*                                                                           *
****************************************************************************/

typedef int             LME_TYPE_APD_RESULT;
typedef int             LME_TYPE_LP_RESULT;
typedef int             LME_TYPE_LC_RESULT;
typedef int             LME_TYPE_AM_RESULT;

#ifdef __cplusplus 
}
#endif 


#endif
