/* $Header: /CSS/Code/RTS/COMMON/api/tcn_api.h 28    03-01-09 16:18 Thomas Clevström $
******************************************************************************
*  COPYRIGHT    : (c) 1995 ABB Daimler Benz Transportation Ltd
******************************************************************************
*  PROJECT      : CSS
*
*  MODULE       : tcn_api.h
*
*  ABSTRACT     : TCN service: Application progamming interface
*
*  REMARKS      :
*
******************************************************************************
*  HISTORY      :
*   $Log: /CSS/Code/RTS/COMMON/api/tcn_api.h $
*  
*  28    03-01-09 16:18 Thomas Clevström
*  TCN version reverted to 1.5.1.0  (1.5.2.0 cancelled)
*  
*  27    02-11-28 18:16 Thomas Clevström
*  TCN 1.5.2
*  
*  26    02-09-18 9:37 Thomas Clevström
*  Minor cleanup and complements to enable auto-generation of contents
*  file.
*  
*  25    01-09-03 16:53 Lars Högberg
*  -LARS HÖGBERG10016
*  
*  24    00-06-27 15:50 Lars Högberg
*  Extended the TCN-API according to NCR-ARMIN-HAGEN WEIß00001
*  
*  23    99-03-10 17:21 Lars Högberg
*  Added API functions; lp_open_port, lp_close_port, ap_frc_single,
*  lc_read_mvb_status, am_read_messager_status, NCR 90001 Modification
*  Request from GW project.
*  Made corrections to apd_force_variable and apd_unforce variable
*  (earlier pointed to wrong function name) 
*
*  22    98-12-17 12:15 Anders Öhlander
*  New version on the TCN software and the am_get_station_id is added. See
*  SPR 174.
*
*  21    98-11-02 16:02 Anders Öhlander
*  Update the version to 1.5.0.0 for the TCN.
*
*  20    98-07-01 13:51 Anders Öhlander
*  Change the undef statements from the apd_xxx_cluster to the
*  lp_xxx_cluster.
*
*  19    98-05-29 12:50 Anders Öhlander
*  Change apd_xxx_cluster to lpd_xxx_cluster. Added the apd_xxx_cluster to
*  the API.
*
*  18    10/16/97 2:44p Björn Elliott
*  Changes in TCN_STR_ICT made by Rene´
*
*  17    10/13/97 4:09p Björn Elliott
*  #undef lc_m_get_device_address  before #define To avoid warning
*
*  16    97-10-08 10:37 Anders Wallin
*  lc_m_get_device address added
*
*  15    97-09-10 14:49 Anders Wallin
*  papd_pass_subscr changed to papd_pass_subscription
*
*  14    97-09-10 11:12 Anders Wallin
*  O_DC functions removed
*
*  13    97-09-09 22:25 Anders Wallin
*
*  12    97-09-09 15:07 Anders Wallin
*  Mesage data added
*
*  11    97-06-27 9.24 Anders Wallin
*  Header added
*
*  10    97-02-13 11.57 Anders Wallin
*  changed name on tcn_types.h to tcn.h
*
*  9     97-02-13 11.57 Anders Wallin
*  changed name on tcn_types.h to tcn.h
*
*  8     96-12-09 14.30 Anders Wallin
*  undef of all API-functions before they are defined
*
*  7     96-12-02 7.33 Anders Wallin
*  C++ support added
*
*  6     96-11-28 12:46 Patrik Sellin
*  ap_put_variable and ap_get_variable added.
*  lp_put_cluster and lp_get_cluster substituted by lp_cluster.
*
*  5     96-11-26 11:50 Patrik Sellin
*  Removed apd_put/get_cluster functions.
*  Removed lpd_gen_pv_set and lpd_mod_pv_set functions.
*  Added lp_put/get_cluster functions.
*
*  4     96-11-21 16:58 Patrik Sellin
*  First version with a definition of a minimal process data API.
*
*  3     96-10-28 15.47 Anders Wallin
*
*  2     96-09-12 15.13 Anders Wallin
*
*  1     96-09-09 19.44 Anders Wallin
*
******************************************************************************/


#ifndef TCN_API_H
#define TCN_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
*   INCLUDES
*/
/* Is part of TCN product */
#include "tcn.h"

/*****************************************************************************
*   DEFINES
*/
#define SERVICE_NAME_TCN
#define TCN_VERSION      1
#define TCN_RELEASE      5
#define TCN_UPDATE       1
#define TCN_EVOLUTION    0


/*****************************************************************************
*   TYPEDEFS
*/
typedef struct
{
    VERSION_INFO    tcn_info;

    /* Application Process Data Functions */
	/* ---------------------------------- */

	/* >>> Start CSS 1.1.X compatiblity */
	/* Single Variable Access */
    TYPE_PD_RESULT  ( *papd_put_variable)  ( const struct STR_APD_PV_DESCRIPTOR* p );
    TYPE_PD_RESULT  ( *papd_get_variable)  ( const struct STR_APD_PV_DESCRIPTOR* p,
                                             unsigned short* p_refresh );

	/* Single Variable Access from link layer */
    TYPE_PD_RESULT  ( *pap_put_variable)   ( const struct STR_PV_NAME pv_name,
                                             void* p_variable );
    TYPE_PD_RESULT  ( *pap_get_variable)   ( const struct STR_PV_NAME pv_name,
                                             void* p_variable,
                                             unsigned short* p_refresh );
 	/* Subscription */
    TYPE_PD_RESULT  ( *papd_subscribe)     ( struct STR_APD_DS_NAME* p_ds_name,
                                             void (*proc) (unsigned short),
                                             unsigned short param );
    TYPE_PD_RESULT  ( *papd_desubscribe)   ( struct STR_APD_DS_NAME* p_ds_name );
    TYPE_PD_RESULT  ( *papd_pass_subscription) ( struct STR_APD_DS_NAME* p_dsn_old,
                                                 struct STR_APD_DS_NAME* p_dsn_new );

	/* Cluster Access from link layer */
    TYPE_PD_RESULT  ( *plp_cluster)        ( const struct STR_PV_CLUS* p,
                                             short data_flow);
	/* <<< End CSS 1.1.X compatiblity */


	/* Init functions from link layer */
    TYPE_PD_RESULT (*plp_create)       (unsigned short          ts_id,
                                        unsigned short          hw_type,
                                  const struct STR_LP_TS_CFG *  p_ts_cfg,
                                  const union  UNN_LP_HW_CFG *  p_hw_cfg);
    TYPE_PD_RESULT (*plp_redundancy)   (unsigned int            ts_id,
                                        unsigned char           action   );
    TYPE_PD_RESULT (*plp_get_p_ts_config)(unsigned int          bus_id,
                                  const struct STR_LP_TS_CFG ** p_p_ts_cfg);

	/* Single Variable Access from link layer */
    void  (*plp_get_pv_x)       (       void *                  p_port,
                                        struct STR_LP_PV_X *    p_pv_x,
                                        unsigned short          var_count);
    void  (*plp_put_pv_x)       (       void *                  p_port,
                                        struct STR_LP_PV_X *    p_pv_x,
                                        unsigned short          var_count);


	/* Set Access */
 	TYPE_PD_RESULT (*papd_put_set     )	(const struct STR_APD_PV_DESCRIPTOR * p ,
 	                                     int                           c_pv_set);

 	TYPE_PD_RESULT (*papd_put_set_fast)(const struct STR_APD_PV_SET *        p);

 	TYPE_PD_RESULT (*papd_get_set     )(const struct STR_APD_PV_DESCRIPTOR * p ,
 	                                     unsigned short *             p_refresh ,
 	                                     int                           c_pv_set);

 	TYPE_PD_RESULT (*papd_get_set_fast)(const struct STR_APD_PV_SET *        p);


 	TYPE_PD_RESULT (*plpd_gen_pv_set   )(struct STR_APD_PV_SET *       p_pv_set ,
 	                                     const struct STR_APD_PV_DESCRIPTOR * p ,
 	                                     unsigned short *             p_refresh ,
							              int                           c_pv_set);

 	void           (*plpd_mod_pv_set   )(struct STR_APD_PV_SET *       p_pv_set ,
							              char                      force_active ,
 	                                     char                   multiple_access);

	/* Set Access from link layer*/
    TYPE_PD_RESULT (*plp_gen_ds_set)   (struct STR_LP_DS_SET *  p_ds_set,
                                        struct STR_LP_PV_X   *  p_pv_x,
                                 const  struct STR_LP_PV_SET *  p_pv_set,
                                        unsigned short *        p_refresh,
                                        unsigned short          pv_set_cnt);
    TYPE_PD_RESULT (*plp_get_data_set)   (const  struct STR_LP_DS_SET *  p_ds_set);
    TYPE_PD_RESULT (*plp_put_data_set)   (const  struct STR_LP_DS_SET *  p_ds_set);


	/* Cluster Access from link layer */
    void *		   (*plp_gen_clus_ts)   (unsigned short          		ts_id,
                                         unsigned short          		ds_count);
    void *(*plp_gen_clus_ds)    		(const  struct STR_DS_NAME *    p_ds_name,
                                		 const  struct STR_LP_PV_SET *  p_pv_set,
                                		        unsigned short *        p_refresh,
                                		        unsigned short          pv_set_cnt);

 	/* Forceing */
 	TYPE_PD_RESULT (*papd_force_var   )(const struct STR_APD_PV_DESCRIPTOR * p);

 	TYPE_PD_RESULT (*papd_unforce_var )(const struct STR_APD_PV_NAME *  p_pv_n);

 	TYPE_PD_RESULT (*papd_unforce_all )(unsigned                     int ts_id);

	/* Sink Time Supervision from link layer */
    TYPE_PD_RESULT (*plp_tmo_counter)  (const struct STR_LP_TMO_CLUS *p_tmo);
    TYPE_PD_RESULT (*plp_tmo_get_state)(void);
    void           (*plp_tmo_set_state)(void);


	/* Application Massage Interface Functions */
	/* --------------------------------------- */

    void  ( *pam_nm_config)
             (unsigned char, unsigned short,
              unsigned short, AM_RESULT *);
    void  ( *pam_announce_device)
          (unsigned int, unsigned int, unsigned int, unsigned short);
    void  ( *pam_insert_dir_entries) (AM_DIR_ENTRY * , unsigned int);
    void  ( *pam_remove_dir_entries) (AM_DIR_ENTRY * , unsigned int);
    void  ( *pam_get_dir_entry)      (unsigned char, unsigned char *);
    void  ( *pam_clear_dir)          (void);
    void  ( *pam_send_requ)
          (unsigned char, const AM_ADDRESS *, void *, CARDINAL32,
          void *, CARDINAL32, unsigned int,
          AM_CALL_CONF, AM_INVOKE_CONF, void * );
    void  ( *pam_call_cancel)
          (unsigned char, const AM_ADDRESS *, AM_RESULT *);
    void  ( *pam_bind_replier)
          (unsigned char, AM_RCV_CONF, AM_REPLY_CONF, AM_RESULT *);
    void  ( *pam_unbind_replier)     (unsigned char replier_fct);
    void  ( *pam_rcv_requ)
          (unsigned char, void *, CARDINAL32, void *, AM_RESULT *);
    void  ( *pam_reply_requ)
          (unsigned char, void *, CARDINAL32, void *, AM_RESULT);
    void  ( *pam_rcv_cancel)
          (unsigned char, void *, AM_RESULT *);
    void  ( *pam_get_status)
	  (unsigned short, unsigned short, unsigned short, unsigned short *);
    AM_REPLIER_STATES ( *pam_get_replier_status) (unsigned char, void *);
    AM_RESULT ( *pam_set_current_tc) (unsigned char);

    AM_RESULT ( *pam_st_write ) (AM_ST_ENTRY entries[],
                                 unsigned int nr_of_entries);
    void ( *pam_st_read) (AM_ST_ENTRY entries[], unsigned int nr_of_entries);
    void ( *pam_disp_show_busses) (unsigned char *nr_of_busses,
                                   unsigned char bus_nr[AM_MAX_BUSSES]);
    int  ( *pam_read_messenger_status) (struct STR_AM_RD_MSNGR_STATUS *);
    int  ( *pam_write_messenger_control) (struct STR_AM_WT_MSNGR_CTRL *);
    void ( *pam_subscribe_lm) (unsigned short bus_id,
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
			      unsigned short (*lm_get_own_phya)
					     (unsigned short bus_id, int *status),
			      unsigned short (*lm_get_src_phya)
					     (unsigned short bus_id,
					      MD_PACKET *packet, int *status),
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


    /* LME Functions */
	/* ------------- */
	unsigned short  ( *plc_m_get_device_status_word) (unsigned short);

    short           ( *plc_m_get_device_address)     (unsigned short,
                                                     unsigned short *);
   /* New APD cluster functions */
   /* ------------------------- */
   TYPE_PD_RESULT (*papd_put_cluster )(const struct STR_APD_PV_CLUSTER *    p);
   TYPE_PD_RESULT (*papd_get_cluster )(const struct STR_APD_PV_CLUSTER *    p);

   /* Added AM function         */
   /* ------------------------- */
   void             ( *pam_get_station_id) (unsigned char *p_station_id);
   /* Added LME support function */
   /* -------------------------- */
   int            (*plc_read_mvb_status)          (unsigned int,
                                                    struct LC_STR_MVB_STATUS* );
   /* Added LP functions */
   /* -------------------------- */
   TYPE_PD_RESULT (*pap_frc_single)   (
                                  const struct STR_PV_NAME      pv_name,
                                        void *                  p_variable,
                                        short                   operation);
   TYPE_PD_RESULT (*plp_open_port )   (unsigned int            bus_id,
                                        const struct STR_LP_PRT_CFG *p_cfg);
   TYPE_PD_RESULT (*plp_close_port)   (unsigned int            bus_id,
                                        unsigned int            prt_addr,
                                        struct STR_LP_PRT_CFG * p_cfg);
   /* Added functions Link Layer and BA*/
   /* -------------------------------- */
   void (*pba_subscribe_diagnosis )	  (unsigned int bus_id,
										void  (*prc_notified) (struct BA_STR_DIAGNOSIS * p_diag));

   short (*pba_quick_scan )           (void);

   short (*pba_single_poll )          (unsigned char * p_poll_list,
										unsigned char poll_list_len);

   TYPE_PD_RESULT (*plp_frc_single )  (const struct STR_LP_PV_SET *  p_pv,
										short operation);
} TCN_STR_ICT;

/*****************************************************************************
*   GLOBAL FUNCTIONS
*/

/*  The following prototypes are defined in tcn.h */


/* Define location for indirect call */
#define TCN_IND_CALL     (*(TCN_STR_ICT * *) TCN_ADR_TABLE)

#ifdef O_DC

#else
	#undef apd_force_variable
	#undef apd_unforce_variable
	#undef apd_unforce_all

	/* Init functions from link layer */
	#undef  lp_init
	#undef  lp_create
	#undef  lp_redundancy
	#undef  lp_get_p_ts_config
	#define apd_ts_create			(* (TCN_IND_CALL->plp_create))
	#define lp_create				(* (TCN_IND_CALL->plp_create))
	#define apd_ts_redundancy		(* (TCN_IND_CALL->plp_redundancy))
	#define lp_redundancy			(* (TCN_IND_CALL->plp_redundancy))
	#define apd_ts_get_config		(* (TCN_IND_CALL->plp_get_p_ts_config))
	#define lp_get_p_ts_config		(* (TCN_IND_CALL->plp_get_p_ts_config))

	/* Single Variable Access */
    #undef  apd_put_variable
    #undef  apd_get_variable
    #undef  ap_put_variable
    #undef  ap_get_variable
	#undef  lp_put_pv_x
	#undef  lp_get_pv_x
    #define apd_put_variable        (* (TCN_IND_CALL->papd_put_variable))
    #define apd_get_variable        (* (TCN_IND_CALL->papd_get_variable))
    #define apd_put_var48           (* (TCN_IND_CALL->papd_put_variable))
    #define apd_get_var48           (* (TCN_IND_CALL->papd_get_variable))
    #define ap_put_variable         (* (TCN_IND_CALL->pap_put_variable))
    #define ap_get_variable         (* (TCN_IND_CALL->pap_get_variable))
    #define apd_put_var32           (* (TCN_IND_CALL->pap_put_variable))
    #define apd_get_var32           (* (TCN_IND_CALL->pap_get_variable))
    #define apd_put_pv_x           	(* (TCN_IND_CALL->plp_put_pv_x))
    #define lp_put_pv_x           	(* (TCN_IND_CALL->plp_put_pv_x))
    #define apd_get_pv_x           	(* (TCN_IND_CALL->plp_get_pv_x))
    #define lp_get_pv_x           	(* (TCN_IND_CALL->plp_get_pv_x))

	/* Set Access */
	#undef  apd_sizeof_pv_set
	#undef  apd_gen_pv_set
	#undef  apd_modify_pv_set
	#undef  apd_put_set
	#undef  apd_put_set_fast
	#undef  apd_get_set
	#undef  apd_get_set_fast
	#define apd_sizeof_pv_set		lpd_sizeof_pv_set
	#define apd_gen_pv_set			(* (TCN_IND_CALL->plpd_gen_pv_set))
	#define apd_modify_pv_set		(* (TCN_IND_CALL->plpd_mod_pv_set))
	#define apd_put_set				(* (TCN_IND_CALL->papd_put_set))
	#define apd_put_set_fast		(* (TCN_IND_CALL->papd_put_set_fast))
	#define apd_get_set				(* (TCN_IND_CALL->papd_get_set))
	#define apd_get_set_fast		(* (TCN_IND_CALL->papd_get_set_fast))

	/* Set Access from link layer */
	#undef	lp_gen_ds_set
	#undef	lp_get_data_set
	#undef	lp_put_data_set
	#define lp_gen_ds_set				(* (TCN_IND_CALL->plp_gen_ds_set))
	#define lp_get_data_set				(* (TCN_IND_CALL->plp_get_data_set))
	#define lp_put_data_set				(* (TCN_IND_CALL->plp_put_data_set))

  	/* Cluster Access from link layer */
    #undef  lp_cluster
	#undef  lpd_get_cluster
	#undef  lpd_put_cluster
	#undef  lpd_gen_clus_ts
	#undef  lpd_gen_clus_ds
    #define lp_cluster              (* (TCN_IND_CALL->plp_cluster))
	#define lpd_get_cluster(p_clus) lp_cluster (p_clus, LP_GET)
	#define lpd_put_cluster(p_clus) lp_cluster (p_clus, LP_PUT)
	#define lpd_gen_clus_ts			(* (TCN_IND_CALL->lp_gen_clus_ts))
	#define lpd_gen_clus_ds			(* (TCN_IND_CALL->lp_gen_clus_ds))

  	/* Cluster Access */
    #undef  apd_put_cluster
    #undef  apd_get_cluster
    #define apd_put_cluster             (* (TCN_IND_CALL->papd_put_cluster))
    #define apd_get_cluster             (* (TCN_IND_CALL->papd_get_cluster))

  	/* Link Layer */
    #undef  ap_frc_single
    #undef  lp_open_port
    #undef  lp_close_port
    #undef  lp_frc_single
    #define ap_frc_single           (* (TCN_IND_CALL->pap_frc_single))
    #define lp_open_port            (* (TCN_IND_CALL->plp_open_port))
    #define lp_close_port           (* (TCN_IND_CALL->plp_close_port))
    #define lp_frc_single           (* (TCN_IND_CALL->plp_frc_single))

 	/* Subscription */
    #undef  apd_subscribe
    #undef  apd_desubscribe
    #undef  apd_pass_subscription
    #define apd_subscribe           (* (TCN_IND_CALL->papd_subscribe))
    #define apd_desubscribe         (* (TCN_IND_CALL->papd_desubscribe))
    #define apd_pass_subscription   (* (TCN_IND_CALL->papd_pass_subscription))

 	/* Forceing */
    #define apd_force_variable      (* (TCN_IND_CALL->papd_force_var))
    #define apd_unforce_variable	(* (TCN_IND_CALL->papd_unforce_var))
    #define apd_unforce_all         (* (TCN_IND_CALL->papd_unforce_all))

	/* Sink Time Supervision from link layer */
	#define apd_tmo_set_state		(* (TCN_IND_CALL->plp_tmo_set_state))
	#define apd_tmo_get_state		(* (TCN_IND_CALL->plp_tmo_get_state))
	#define apd_tmo_counter			(* (TCN_IND_CALL->plp_tmo_counter))

	/* AM Initialisation */
	#undef  am_subscribe_lm
	#undef  am_disubscribe_lm
	#undef  am_announce_device
	#undef  am_read_messenger_status
   	#define am_subscribe_lm	        (* (TCN_IND_CALL->pam_subscribe_lm))
	#define am_disubscribe_lm	    (* (TCN_IND_CALL->pam_disubscribe_lm))
	#define am_announce_device      (* (TCN_IND_CALL->pam_announce_device))
	#define am_read_messenger_status      (* (TCN_IND_CALL->pam_read_messenger_status))

	/* !!! RS TO BE DONE
	#undef am_buffer_free
	#define am_buffer_free( addr )  pi_free(addr)
	*/

	/* AM Directories */
	#undef  am_insert_dir_entries
	#undef  am_remove_dir_entries
	#undef  am_get_dir_entry
	#undef  am_clear_dir
	#define am_insert_dir_entries   (* (TCN_IND_CALL->pam_insert_dir_entries))
	#define am_remove_dir_entries   (* (TCN_IND_CALL->pam_remove_dir_entries))
	#define am_get_dir_entry        (* (TCN_IND_CALL->pam_get_dir_entry))
	#define am_clear_dir            (* (TCN_IND_CALL->pam_clear_dir))

	/* AM Caller */
	#undef  am_call_requ
	#undef  am_call_cancel
	#define am_call_requ(fct, r, out_a, out_s, in_a, in_s, tmo, cc, ref) \
            (* (TCN_IND_CALL->pam_send_requ))                            \
	        (fct, r, out_a, out_s, in_a, in_s, tmo, cc, (AM_INVOKE_CONF)0, ref)
	#define am_call_cancel          (* (TCN_IND_CALL->pam_call_cancel))

	/* AM Replier */
	#undef  am_bind_replier
	#undef  am_unbind_replier
	#undef  am_rcv_requ
	#undef  am_reply_requ
	#undef  am_rcv_cancel
	#define am_bind_replier         (* (TCN_IND_CALL->pam_bind_replier))
	#define am_unbind_replier       (* (TCN_IND_CALL->pam_unbind_replier))
	#define am_rcv_requ             (* (TCN_IND_CALL->pam_rcv_requ))
	#define am_reply_requ           (* (TCN_IND_CALL->pam_reply_requ))
	#define am_rcv_cancel	        (* (TCN_IND_CALL->pam_rcv_cancel))

	/* AM Station Directory */
	#undef  am_st_write
	#undef  am_st_read
	#undef  am_set_current_tc
	#undef  am_get_station_id
	#define am_st_write             (* (TCN_IND_CALL->pam_st_write))
	#define am_st_read              (* (TCN_IND_CALL->pam_st_read))
	#define am_set_current_tc       (* (TCN_IND_CALL->pam_set_current_tc))
	#define am_get_station_id       (* (TCN_IND_CALL->pam_get_station_id))

    /* LME Functions */
    #define lme_get_DSW             (* (TCN_IND_CALL->plc_m_get_device_status_word))
	#undef  lc_m_get_device_address
    #undef  lc_read_mvb_status
    #undef  lc_get_device_status_word
    #undef  lc_m_get_device_status_word
    #define lc_m_get_device_status_word (* (TCN_IND_CALL->plc_m_get_device_status_word))
    #define lc_get_device_status_word()    lc_m_get_device_status_word(0)
    #define lc_m_get_device_address (* (TCN_IND_CALL->plc_m_get_device_address))
    #define lc_read_mvb_status (* (TCN_IND_CALL->plc_read_mvb_status))

    /* BA Functions */
    #undef   ba_subscribe_diagnosis
    #undef   ba_quick_scan         
    #undef   ba_single_poll        
    #define  ba_subscribe_diagnosis	(* (TCN_IND_CALL->pba_subscribe_diagnosis))
    #define  ba_quick_scan          (* (TCN_IND_CALL->pba_quick_scan))
    #define  ba_single_poll         (* (TCN_IND_CALL->pba_single_poll))

#endif

#ifdef __cplusplus
}
#endif

#endif /* TCN_API_H */
