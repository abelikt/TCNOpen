/**********************************************************************************************************************/
/**
 * @file            trdp-pd-test-fast.c
 *
 * @brief           Test application for TRDP PD
 *
 * @details
 *
 * @note            Project: TCNOpen TRDP prototype stack
 *
 * @author          Petr Cvachoucek, UniControls
 *
 * @remarks This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 *          If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *          Copyright UniControls, 2013-2020. All rights reserved.
 *          Copyright Alstom SA or its subsidiaries and others, 2013-2023. All rights reserved.
 *
 * $Id$
 *
 *     AHW 2024-06-19: Ticket #458 Unify cmd line interfaces of tests
 *      PL 2023-07-13: Ticket #435 Cleanup VLAN and TSN for options for Linux systems
 *     CWE 2023-02-14: Ticket #419 PDTestFastBase2 failed - use even cycle factors depending on the index table base + write timestamps to log
 *      AM 2022-12-01: Ticket #399 Abstract socket type (VOS_SOCK_T, TRDP_SOCK_T) introduced, vos_select function is not anymore called with '+1'
 *      IB 2019-08-15: separate sender and receiver thread added
 *      BL 2018-06-20: Ticket #184 Building with VS 2015: WIN64 and Windows threads (SOCKET instead of INT32)
 *      BL 2018-03-06: Ticket #101 Optional callback function on PD send
 *      BL 2017-06-30: Compiler warnings, local prototypes added
 *
 */

#include <stdio.h>
#include <string.h>

#include "trdp_if_light.h"

#if defined (POSIX)
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <time.h>
#endif

#include "printOwnStatistics.h"
#include "getopt.h"

#define APP_VERSION         "1.9"
#define APP_USE             "This tool sends and receives PD messages in high performance mode."
#define RESERVED_MEMORY     240000
#define PREALLOCATE         {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}

/* --- globals ---------------------------------------------------------------*/

TRDP_MEM_CONFIG_T memcfg = { NULL, RESERVED_MEMORY, PREALLOCATE };
TRDP_APP_SESSION_T apph;
TRDP_PD_CONFIG_T pdcfg;
TRDP_PROCESS_CONFIG_T proccfg;
VOS_THREAD_T          rcvThread;
VOS_THREAD_T          sndThread;
BOOL printDetailedStatistics;

/* default addresses - overriden from command line */
TRDP_IP_ADDR_T srcip;
TRDP_IP_ADDR_T dstip;
TRDP_IP_ADDR_T mcast;

typedef enum
{
    PORT_PUSH,                      /* outgoing port ('Pd'/push)   */
    PORT_PULL,                      /* outgoing port ('Pp'/pull)   */
    PORT_REQUEST,                   /* outgoing port ('Pr'/request)*/
    PORT_SINK,                      /* incoming port               */
} Type;

static const char * types[] =
    { "Pd ->", "Pp ->", "Pr ->", "   <-" };

typedef struct
{
    Type type;                      /* port type */
    TRDP_ERR_T err;                 /* put/get status */
    TRDP_PUB_T ph;                  /* publish handle */
    TRDP_SUB_T sh;                  /* subscribe handle */
    UINT32 comid;                   /* comid            */
    UINT32 repid;                   /* reply comid (for PULL requests) */
    UINT32 size;                    /* size                            */
    TRDP_IP_ADDR_T src;             /* source ip address               */
    TRDP_IP_ADDR_T dst;             /* destination ip address          */
    TRDP_IP_ADDR_T rep;             /* reply ip address (for PULL requests) */
    UINT32 cycle;                   /* cycle                                */
    UINT32 timeout;                 /* timeout (for SINK ports)             */
    unsigned char data[TRDP_MAX_PD_DATA_SIZE];       /* data buffer                          */
    int link;                       /* index of linked port (echo or subscribe) */
} Port;

int size[3] = { 0, 256, TRDP_MAX_PD_DATA_SIZE };        /* small/medium/big dataset */

#ifdef HIGH_PERF_BASE2                                  /* High Performance: index-tables on base 2 (1, 8, 64ms)    */
int period[2]  = { 128, 256 };                          /* fast / slow cycle upon base 2 index                      */
#else                                                   /* High Performance: index-tables on base 10 (1, 10, 100ms) */
int period[2]  = { 100, 250 };                          /* fast / slow cycle upon base 10 index                     */
#endif

unsigned cycle = 0;

Port ports[64];                     /* array of ports          */
int nports = 0;                     /* number of ports         */

/***********************************************************************************************************************
 * PROTOTYPES
 */
void gen_push_ports_master(UINT32 comid, UINT32 echoid);
void gen_pull_ports_slave(UINT32 reqid, UINT32 repid);
void gen_push_ports_slave(UINT32 comid, UINT32 echoid);

/* --- generate PUSH ports ---------------------------------------------------*/

void gen_push_ports_master(UINT32 comid, UINT32 echoid)
{
    Port src, snk;
    int num = nports;
    UINT32  a, sz, per;
    
    printf("- generating PUSH ports (master side) ... ");

    memset(&src, 0, sizeof(src));
    memset(&snk, 0, sizeof(snk));

    src.type = PORT_PUSH;
    snk.type = PORT_SINK;
    snk.timeout = 4000000;         /* 4 secs timeout*/

    /* for unicast/multicast address */
    for (a = 0; a < 2; ++a)
    {   /* for all dataset sizes */
        for (sz = 1; sz < 3; ++sz)
        {   /* for all cycle periods */
            for (per = 0; per < 2; ++per)
            {   /* comid  */
                src.comid = comid + 100u *a+40*(per+1)+3*(sz+1);
                snk.comid = echoid + 100u *a+40*(per+1)+3*(sz+1);
                /* dataset size */
                src.size = snk.size = (UINT32) size[sz];
                /* period [usec] */
                src.cycle = (UINT32) 1000u * (UINT32)period[per];
                /* addresses */
                if (!a)
                {   /* unicast address */
                    src.dst = snk.src = dstip;
                    src.src = snk.dst = srcip;
                }
                else
                {   /* multicast address */
                    src.dst = snk.dst = mcast;
                    src.src = srcip;
                    snk.src = dstip;
                }
                src.link = -1;
                /* add ports to config */
                ports[nports++] = src;
                ports[nports++] = snk;
            }
        }
    }

    printf("%u ports created\n", nports - num);
}

void gen_push_ports_slave(UINT32 comid, UINT32 echoid)
{
    Port src, snk;
    int num = nports;
    UINT32 a, sz, per;

    printf("- generating PUSH ports (slave side) ... ");

    memset(&src, 0, sizeof(src));
    memset(&snk, 0, sizeof(snk));

    src.type = PORT_PUSH;
    snk.type = PORT_SINK;
    snk.timeout = 4000000;         /* 4 secs timeout */

    /* for unicast/multicast address */
    for (a = 0; a < 2; ++a)
    {   /* for all dataset sizes */
        for (sz = 1; sz < 3; ++sz)
        {   /* for all cycle periods */
            for (per = 0; per < 2; ++per)
            {   /* comid  */
                src.comid = echoid + 100*a+40*(per+1)+3*(sz+1);
                snk.comid = comid + 100*a+40*(per+1)+3*(sz+1);
                /* dataset size */
                src.size = snk.size = (UINT32) size[sz];
                /* period [usec] */
                src.cycle = (UINT32) (1000 * period[per]);
                /* addresses */
                if (!a)
                {   /* unicast address */
                    src.dst = snk.src =  dstip;
                    src.src = snk.dst =  srcip;
                }
                else
                {   /* multicast address */
                    src.dst = snk.dst = mcast;
                    src.src = srcip;
                    snk.src = dstip;
                }
                /* add ports to config */
                ports[nports++] = snk;
                src.link = nports - 1;
                ports[nports++] = src;
            }
        }
    }

    printf("%u ports created\n", nports - num);
}

/* --- generate PULL ports ---------------------------------------------------*/

static void gen_pull_ports_master(UINT32 reqid, UINT32 repid)
{
    Port req, rep;
    int num = nports;
    UINT32  a, sz;

    printf("- generating PULL ports (master side) ... ");

    memset(&req, 0, sizeof(req));
    memset(&rep, 0, sizeof(rep));

    req.type = PORT_REQUEST;
    rep.type = PORT_SINK;

    /* for unicast/multicast address */
    for (a = 0; a < 2; ++a)
    {   /* for all dataset sizes */
        for (sz = 0; sz < 2; ++sz)
        {   /* comid */
            req.comid = reqid + 100*a + 3*(sz+1);
            rep.comid = repid + 100*a + 3*(sz+1);
            /* dataset size */
            req.size = (UINT32) size[sz];
            rep.size = (UINT32) size[sz + 1];
            /* addresses */
            if (!a)
            {   /* unicast address */
                req.dst = dstip;
                req.src = srcip;
                req.rep = srcip;
                req.repid = rep.comid;
                rep.src = dstip;
                rep.dst = srcip;
            }
            else
            {   /* multicast address */
                req.dst = mcast;
                req.src = srcip;
                req.rep = mcast;
                req.repid = rep.comid;
                rep.dst = mcast;
                rep.src = dstip;
            }
            /* add ports to config */
            ports[nports++] = rep;
            req.link = nports - 1;
            ports[nports++] = req;
        }
    }

    printf("%u ports created\n", nports - num);
}

void gen_pull_ports_slave(UINT32 reqid, UINT32 repid)
{
    Port req, rep;
    int num = nports;
    UINT32 a, sz;

    printf("- generating PULL ports (slave side) ... ");

    memset(&req, 0, sizeof(req));
    memset(&rep, 0, sizeof(rep));

    req.type = PORT_SINK;
    rep.type = PORT_PULL;
    req.timeout = 4000000;      /* 4 secs timeout */

    /* for unicast/multicast address */
    for (a = 0; a < 2; ++a)
    {   /* for all dataset sizes */
        for (sz = 0; sz < 2; ++sz)
        {   /* comid */
            req.comid = reqid + 100*a + 3*(sz+1);
            rep.comid = repid + 100*a + 3*(sz+1);
            /* dataset size */
            req.size = (UINT32) size[sz];
            rep.size = (UINT32) size[sz + 1];
            /* addresses */
            if (!a)
            {   /* unicast address */
                req.dst = srcip;
                req.src = dstip;
                rep.src = srcip;
                rep.dst = 0;
            }
            else
            {   /* multicast address */
                req.dst = mcast;
                req.src = dstip;
                rep.src = srcip;
                rep.dst = 0;
            }
            /* add ports to config */
            ports[nports++] = req;
            rep.link = nports - 1;
            ports[nports++] = rep;
        }
    }

    printf("%u ports created\n", nports - num);
}

/* --- setup ports -----------------------------------------------------------*/

static void setup_ports()
{
    int i;
    printf("- setup ports:\n");
    /* setup ports one-by-one */
    for (i = 0; i < nports; ++i)
    {
        Port * p = &ports[i];

        printf("  %3d: <%d> / %s / %4d / %3d ... ",
            i, p->comid, types[p->type], p->size, p->cycle / 1000);

        /* depending on port type */
        switch (p->type)
        {
        case PORT_PUSH:
        case PORT_PULL:
            p->err = tlp_publish(
                apph,               /* session handle */
                &p->ph,             /* publish handle */
                NULL, NULL, 
                0u,                 /* serviceId        */
                p->comid,           /* comid            */
                0,                  /* topo counter     */
                0,
                p->src,             /* source address   */
                p->dst,             /* destination address */
                p->cycle,           /* cycle period   */
                0,                  /* redundancy     */
                TRDP_FLAGS_NONE,    /* flags          */
                p->data,            /* data           */
                p->size);           /* data size      */

            if (p->err != TRDP_NO_ERR)
                printf("tlp_publish() failed, err: %d\n", p->err);
            else
                printf("ok\n");
            break;

        case PORT_REQUEST:
            p->err = tlp_request(
                apph,               /* session handle */
                ports[p->link].sh,  /* related subscribe handle */
                0u,                 /* serviceId        */
                p->comid,           /* comid          */
                0,                  /* topo counter   */
                0,
                p->src,             /* source address */
                p->dst,             /* destination address */
                0,                  /* redundancy     */
                TRDP_FLAGS_NONE,    /* flags          */
                p->data,            /* data           */
                p->size,            /* data size      */
                p->repid,           /* reply comid    */
                p->rep);            /* reply ip address  */

            if (p->err != TRDP_NO_ERR)
                printf("tlp_request() failed, err: %d\n", p->err);
            else
                printf("ok\n");
            break;

        case PORT_SINK:
            p->err = tlp_subscribe(
                apph,               /* session handle   */
                &p->sh,             /* subscribe handle */
                NULL,               /* user ref         */
                NULL,               /* callback funktion */
                0u,                 /* serviceId        */
                p->comid,           /* comid            */
                0,                  /* topo counter     */
                0,
                p->src,             /* source address   */
                VOS_INADDR_ANY,
                p->dst,             /* destination address    */
                TRDP_FLAGS_NONE,    /* No flags set     */
                p->timeout,             /* timeout [usec]   */
                TRDP_TO_SET_TO_ZERO);   /* timeout behavior */

            if (p->err != TRDP_NO_ERR)
                printf("tlp_subscribe() failed, err: %d\n", p->err);
            else
                printf("ok\n");
            break;
        }
    }
}

/* --- convert trdp error code to string -------------------------------------*/

static const char * get_result_string(int ret)
{
    static char buf[128];

    switch (ret)
    {
    case TRDP_NO_ERR:
        return "TRDP_NO_ERR (no error)";
    case TRDP_PARAM_ERR:
        return "TRDP_PARAM_ERR (parameter missing or out of range)";
    case TRDP_INIT_ERR:
        return "TRDP_INIT_ERR (call without valid initialization)";
    case TRDP_NOINIT_ERR:
        return "TRDP_NOINIT_ERR (call with invalid handle)";
    case TRDP_TIMEOUT_ERR:
        return "TRDP_TIMEOUT_ERR (timeout)";
    case TRDP_NODATA_ERR:
        return "TRDP_NODATA_ERR (non blocking mode: no data received)";
    case TRDP_SOCK_ERR:
        return "TRDP_SOCK_ERR (socket error / option not supported)";
    case TRDP_IO_ERR:
        return "TRDP_IO_ERR (socket IO error, data can't be received/sent)";
    case TRDP_MEM_ERR:
        return "TRDP_MEM_ERR (no more memory available)";
    case TRDP_SEMA_ERR:
        return "TRDP_SEMA_ERR semaphore not available)";
    case TRDP_QUEUE_ERR:
        return "TRDP_QUEUE_ERR (queue empty)";
    case TRDP_QUEUE_FULL_ERR:
        return "TRDP_QUEUE_FULL_ERR (queue full)";
    case TRDP_MUTEX_ERR:
        return "TRDP_MUTEX_ERR (mutex not available)";
    case TRDP_NOSESSION_ERR:
        return "TRDP_NOSESSION_ERR (no such session)";
    case TRDP_SESSION_ABORT_ERR:
        return "TRDP_SESSION_ABORT_ERR (Session aborted)";
    case TRDP_NOSUB_ERR:
        return "TRDP_NOSUB_ERR (no subscriber)";
    case TRDP_NOPUB_ERR:
        return "TRDP_NOPUB_ERR (no publisher)";
    case TRDP_NOLIST_ERR:
        return "TRDP_NOLIST_ERR (no listener)";
    case TRDP_CRC_ERR:
        return "TRDP_CRC_ERR (wrong CRC)";
    case TRDP_WIRE_ERR:
        return "TRDP_WIRE_ERR (wire error)";
    case TRDP_TOPO_ERR:
        return "TRDP_TOPO_ERR (invalid topo count)";
    case TRDP_COMID_ERR:
        return "TRDP_COMID_ERR (unknown comid)";
    case TRDP_STATE_ERR:
        return "TRDP_STATE_ERR (call in wrong state)";
    case TRDP_APP_TIMEOUT_ERR:
        return "TRDP_APPTIMEOUT_ERR (application timeout)";
    case TRDP_UNKNOWN_ERR:
        return "TRDP_UNKNOWN_ERR (unspecified error)";
    }
    sprintf(buf, "unknown error (%d)", ret);
    return buf;
}

/* --- platform helper functions ---------------------------------------------*/

#if (defined (WIN32) || defined (WIN64))

void cursor_home()
{
    COORD c = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clear_screen()
{
    CONSOLE_SCREEN_BUFFER_INFO ci;
    COORD c = { 0, 0 };
    DWORD written;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD a = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    cursor_home();
    SetConsoleTextAttribute(h, a);
    GetConsoleScreenBufferInfo(h, &ci);
    // fill attributes
    FillConsoleOutputAttribute(h, a, ci.dwSize.X * ci.dwSize.Y, c, &written);
    // fill characters
    FillConsoleOutputCharacter(h, ' ', ci.dwSize.X * ci.dwSize.Y, c, &written);
}

int _get_term_size(int * w, int * h)
{
    CONSOLE_SCREEN_BUFFER_INFO ci;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
    if (w)
        *w = ci.dwSize.X;
    if (h)
        *h = ci.dwSize.Y;
    return 0;
}

void _set_color_red()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void _set_color_green()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void _set_color_blue()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void _set_color_default()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void _sleep_msec(int msec)
{
    Sleep(msec);
}

#if (!defined (WIN32) && !defined (WIN64))
int snprintf(char * str, size_t size, const char * format, ...)
{
    va_list args;
    int n;

    // verify buffer size
    if (size <= 0)
        // empty buffer
        return -1;

    // use vsnprintf function
    va_start(args, format);
    n = _vsnprintf(str, size, format, args);
    va_end(args);

    // check for truncated text
    if (n == -1 || n >= (int) size)
    {   // text truncated
        str[size - 1] = 0;
        return -1;
    }
    // return number of characters written to the buffer
    return n;
}
#endif
#elif defined (POSIX)

static void cursor_home()
{
    printf("\033" "[H");
}

static void clear_screen()
{
    printf("\033" "[H" "\033" "[2J");
}

static int _get_term_size(int * w, int * h)
{
    struct winsize ws;
    int ret = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    if (ret)
        return ret;
    if (ws.ws_col == 0)
        ws.ws_col = 120;
    if (ws.ws_row == 0)
        ws.ws_row = 40;
    if (w)
        *w = ws.ws_col;
    if (h)
        *h = ws.ws_row;
    return ret;
}

static void _set_color_red()
{
    printf("\033" "[0;1;31m");
}

static void _set_color_green()
{
    printf("\033" "[0;1;32m");
}

static void _set_color_blue()
{
    printf("\033" "[0;1;34m");
}

static void _set_color_default()
{
    printf("\033" "[0m");
}

static void _sleep_msec(int msec)
{
    struct timespec ts;
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000L;
    // sleep specified time
    nanosleep(&ts, NULL);
}

#elif defined (VXWORKS)
void cursor_home()
{
    printf("\033" "[H");
}

void clear_screen()
{
    printf("\033" "[H" "\033" "[2J");
}

int _get_term_size(int * w, int * h)
{
    /* assume a terminal 100 cols, 60 rows fix */
    *w = 100;
    *h = 60;
    return 0;
}

void _set_color_red()
{
    printf("\033" "[0;1;31m");
}

void _set_color_green()
{
    printf("\033" "[0;1;32m");
}

void _set_color_blue()
{
    printf("\033" "[0;1;34m");
}

void _set_color_default()
{
    printf("\033" "[0m");
}

void _sleep_msec(int msec)
{
    struct timespec ts;
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000L;
    /* sleep specified time*/
    nanosleep(&ts, NULL);
}

#else
#error "Target not defined!"
#endif


/*********************************************************************************************************************/
/** Call tlp_processSend synchronously
 */
static void *senderThread (void * pArg)
{
    TRDP_APP_SESSION_T  apphandle = (TRDP_APP_SESSION_T) pArg;

    TRDP_ERR_T result = tlp_processSend(apphandle);
    if ((result != TRDP_NO_ERR) && (result != TRDP_BLOCK_ERR))
    {
        printf("tlp_processSend failed: %d\n", result);
    }
    return NULL;
}

/* --- test data processing --------------------------------------------------*/

static void process_data()
{
    static int w = 80;
    int _w, _h;
    int i;
    unsigned n;

		
    /* get terminal size */
    if (_get_term_size(&_w, &_h) == 0)
    {   /* changed width? */
        if (_w != w || !cycle)
            clear_screen();
        else
            cursor_home();
        w = _w;
    }
    else
    {
        if (!cycle)
            clear_screen();
        else
            cursor_home();
    }

    /* go through ports one-by-one */
    for (i = 0; i < nports; ++i)
    {
        Port * p = &ports[i];
        /* write port data */
        if (p->type == PORT_PUSH || p->type == PORT_PULL)
        {
            if (p->link == -1)
            {   /* data generator */
                unsigned o = cycle % 128;
                memset(p->data, '_', p->size);
                if (o < p->size)
                {
                    snprintf((char *) p->data + o, p->size - o,
                        "<%s/%d.%d.%d.%d->%d.%d.%d.%d/%dms/%db:%d>",
                        p->type == PORT_PUSH ? "Pd" : "Pp",
                        (p->src >> 24) & 0xff, (p->src >> 16) & 0xff,
                        (p->src >> 8) & 0xff, p->src & 0xff,
                        (p->dst >> 24) & 0xff, (p->dst >> 16) & 0xff,
                        (p->dst >> 8) & 0xff, p->dst & 0xff,
                        p->cycle / 1000, p->size, cycle);
                }
            }
            else
            {   /* echo data from incoming port, replace all '_' by '~' */
                unsigned char * src = ports[p->link].data;
                unsigned char * dst = p->data;
                for (n = p->size; n; --n, ++src, ++dst)
                    *dst = (*src == '_') ? '~' : *src;
            }

            p->err = tlp_put(apph, p->ph, p->data, p->size);
        }
        else if (p->type == PORT_REQUEST)
        {
            unsigned o = cycle % 128;
            memset(p->data, '_', p->size);
            if (o < p->size)
            {
                snprintf((char *) p->data + o, p->size - o,
                    "<Pr/%d.%d.%d.%d->%d.%d.%d.%d/%dms/%db:%d>",
                    (p->src >> 24) & 0xff, (p->src >> 16) & 0xff,
                    (p->src >> 8) & 0xff, p->src & 0xff,
                    (p->dst >> 24) & 0xff, (p->dst >> 16) & 0xff,
                    (p->dst >> 8) & 0xff, p->dst & 0xff,
                    p->cycle / 1000, p->size, cycle);
            }

            p->err = tlp_request(apph, ports[p->link].sh, 0u, p->comid, 0u, 0u,
                p->src, p->dst, 0, TRDP_FLAGS_NONE, p->data, p->size,
                p->repid, p->rep);
        }

        /* print port data */
        fflush(stdout);
        if (vos_isMulticast(p->dst) || vos_isMulticast(p->src))
            _set_color_blue();
        else
            _set_color_default();
        printf("%5d ", p->comid);
        _set_color_default();
        printf("%s [", types[p->type]);

        if (p->err == TRDP_NO_ERR)
        {
            unsigned char * ptr = p->data;
            unsigned j;
            for (j = 0; j < (unsigned) w - 19; ++j, ++ptr)
            {
                if (j < p->size)
                {
                    if (*ptr < ' ' || *ptr > 127)
                        putchar('.');
                    else
                        putchar(*ptr);
                }
                else
                    putchar(' ');
            }
        }
        else
        {
            int n = printf(" -- %s", get_result_string(p->err));
            while (n++ < w - 19) putchar(' ');
        }
        putchar(']'); fflush(stdout);
        if (p->err != TRDP_NO_ERR)
            _set_color_red();
        else
            _set_color_green();
        printf(" %3d\n", p->err);
        _set_color_default();
    }

    if (printDetailedStatistics)
    {
        printOwnStatistics(apph, TRUE);
    }
    else
    {
        printOwnStatistics(apph, FALSE);
    }

    /* increment cycle counter  */
    ++cycle;
}


/*********************************************************************************************************************/
/** Call tlp_processReceive asynchronously
 */
static void *receiverThread (void * pArg)
{
    TRDP_APP_SESSION_T  apphandle = (TRDP_APP_SESSION_T) pArg;
  
    TRDP_ERR_T      result;
    TRDP_TIME_T     interval = {0,0};
    TRDP_FDS_T      fileDesc;
    INT32           noDesc = 0;

    while (vos_threadDelay(1000u) == VOS_NO_ERR)   /* this is a cancelation point! */
    {
        FD_ZERO(&fileDesc);
        result = tlp_getInterval(apphandle, &interval, &fileDesc, (TRDP_SOCK_T *) &noDesc);
        if (result != TRDP_NO_ERR)
        {
            printf("tlp_getInterval failed: %d\n", result);
        }
        noDesc = vos_select(noDesc, &fileDesc, NULL, NULL, &interval);
        result = tlp_processReceive(apphandle
            , &fileDesc, &noDesc);
        if ((result != TRDP_NO_ERR) && (result != TRDP_BLOCK_ERR))
        {
            printf("tlp_processReceive failed: %d\n", result);
        }
    }
    return NULL;
}



/* --- poll received data ----------------------------------------------------*/

static void poll_data()
{
    TRDP_PD_INFO_T pdi;
    int i;

    /* go through ports one-by-one */
    for (i = 0; i < nports; ++i)
    {
        Port * p = &ports[i];
        UINT32 size = p->size;
        if (p->type != PORT_SINK)
            /* poll only sink ports  */
            continue;

        p->err = tlp_get(apph, p->sh, &pdi, p->data, &size);
    }
}


static FILE *pLogFile;

static void printLog(
    void        *pRefCon,
    VOS_LOG_T   category,
    const CHAR8 *pTime,       // timestamp string "yyyymmdd-hh:mm:ss.µs"
    const CHAR8 *pFile,
    UINT16      line,
    const CHAR8 *pMsgStr)
{
    static const char* cat[] = { "ERR", "WAR", "INF", "DBG", "USR" };

    if (pLogFile != NULL)
    {
        fprintf(pLogFile, "%s%s %s@%d: %s", pTime, cat[category], pFile, (int)line, pMsgStr);
        fflush(pLogFile);
    }
}


/**********************************************************************************************************************/
/* Print a sensible usage message */
void usage(const char* appName)
{
    printf("%s: Version %s\t(%s - %s)\n", appName, APP_VERSION, __DATE__, __TIME__);
    printf("Usage of %s\n", appName);
    printf(APP_USE"\n"
        "Arguments are:\n"
        "-o <own IP address>       in dotted decimal\n"
        "-t <target IP address>    in dotted decimal\n"
        "-m <multicast IP address> in dotted decimal  (default 239.2.24.1)\n"
#ifdef SIM
        "-p <prefix>               instance prefix in simulation mode (ie. CCU1)\n"
#endif
        "-s <o|d>                  print statistics overview|details\n"
        "-l <logfile>              file name (e.g. test.txt)\n"
        "-v                        print version and quit\n"
    );
}


/* --- main ------------------------------------------------------------------*/
int main(int argc, char * argv[])
{
    TRDP_ERR_T err;
    unsigned tick = 0;
    char filename[TRDP_MAX_FILE_NAME_LEN];
    int ch;

    mcast = vos_dottedIP("239.2.24.1");   /* default multicast address */
    printDetailedStatistics = FALSE;

    /* get the arguments/options */
    while ((ch = getopt(argc, argv,
#ifdef SIM
        "t:o:m:p:l:h?sv"
#else
        "t:o:m:l:h?sv"
#endif
    )) != -1)
    {
        switch (ch)
        {
        case 'o':
        {    /*  read ip    */
            unsigned int ip[4];

            if (sscanf(optarg, "%u.%u.%u.%u",
                &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
            {
                usage(argv[0]);
                return 1;
            }
            srcip = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
#ifdef SIM
            if (!SimSetHostIp(optarg))
                printf("Failed to set sim host IP.");
#endif
            break;
        }
        case 't':
        {    /*  read ip    */
            unsigned int ip[4];

            if (sscanf(optarg, "%u.%u.%u.%u",
                &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
            {
                usage(argv[0]);
                return 1;
            }
            dstip = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
            break;
        }
        case 'm':
        {    /*  read ip    */
            unsigned int ip[4];

            if (sscanf(optarg, "%u.%u.%u.%u",
                &ip[3], &ip[2], &ip[1], &ip[0]) < 4)
            {
                usage(argv[0]);
                return 1;
            }
            mcast = (ip[3] << 24) | (ip[2] << 16) | (ip[1] << 8) | ip[0];
            break;
        }
#ifdef SIM
        case 'p':
        {
            vos_setTimeSyncPrefix(optarg);
        }
#endif
        case 's':
        {
            printDetailedStatistics = TRUE;
            break;
        }
        case 'v':    /*  version */
        {
            printf("%s: Version %s\t(%s - %s)\n",
                argv[0], APP_VERSION, __DATE__, __TIME__);
            return 0;
            break;
        }
        case 'l':
        {    /*  Log file   */
            strncpy(filename, optarg, sizeof(filename) - 1);
            pLogFile = fopen(optarg, "w");
            break;
        }

        case 'h':
        case '?':
        default:
            usage(argv[0]);
            return 1;
        }
    }

    printf("%s: Version %s\t(%s - %s)\n%s\n", argv[0], APP_VERSION, __DATE__, __TIME__, APP_USE);

    {
        CHAR8 sourceip[16], destip[16], mcastip[16];

        strcpy(sourceip, vos_ipDotted(srcip));
        strcpy(destip, vos_ipDotted(dstip));
        strcpy(mcastip, vos_ipDotted(mcast));
        printf("\nParameters:\n  localip    = %s\n  remoteip   = %s\n  mcast      = %s\n  logfile    = %s\n  statistics = %s\n\n",
            sourceip, destip, mcastip,
            (pLogFile == NULL ? "" : filename), 
            (printDetailedStatistics==TRUE)?"detailed" :"overview");
    }

    /* Init process config and pdcfg */
    memset(&proccfg, 0, sizeof(proccfg));
    proccfg.cycleTime = 5000u;
    proccfg.options = TRDP_OPTION_TRAFFIC_SHAPING;      // by now: there is no traffic shaping option for HIGH_PERF_INDEXED
    strcpy (proccfg.hostName, "PD_TEST_HOST");
    strcpy(proccfg.leaderName, "PD_TEST_LEADER");
    strcpy(proccfg.type, "PD_TEST_TYPE");

    pdcfg.pfCbFunction = NULL;
    pdcfg.pRefCon = NULL;
    pdcfg.sendParam.ttl = TRDP_PD_DEFAULT_TTL;
    pdcfg.flags = TRDP_FLAGS_NONE;
    pdcfg.timeout = 100*TRDP_PD_DEFAULT_TIMEOUT;
    pdcfg.toBehavior = TRDP_TO_SET_TO_ZERO;
    pdcfg.port = TRDP_PD_UDP_PORT;

#if PORT_FLAGS == TRDP_FLAGS_TSN
    proccfg.vlanId = 1;
    pdcfg.sendParam.qos = TRDP_PD_DEFAULT_TSN_PRIORITY;
#else
    pdcfg.sendParam.qos = TRDP_PD_DEFAULT_QOS;
#endif

    /* initialize TRDP protocol library */
    err = tlc_init(printLog, NULL, &memcfg);
    if (err != TRDP_NO_ERR)
    {
        printf("tlc_init() failed, err: %d\n", err);
        return 1;
    }

    /* open session */
    err = tlc_openSession(&apph, srcip, 0, NULL, &pdcfg, NULL, &proccfg);
    if (err != TRDP_NO_ERR)
    {
        printf("tlc_openSession() failed, err: %d\n", err);
        return 1;
    }

    /* generate ports configuration */
    gen_push_ports_master(10000, 20000);
    gen_push_ports_slave(10000, 20000);
    gen_pull_ports_master(30000, 40000);
    gen_pull_ports_slave(30000, 40000);
    setup_ports();
    _sleep_msec(2000);
    /* main test loop */


    /* Receiver thread runs until cancel */
    vos_threadCreate(&rcvThread,
        "Receiver Task",
        VOS_THREAD_POLICY_OTHER,
        (VOS_THREAD_PRIORITY_T)proccfg.priority,
        0u,
        0u,
        (VOS_THREAD_FUNC_T)receiverThread,
        (void*)apph);


    /* Send thread is a cyclic thread, runs until cancel */
    vos_threadCreate(&sndThread,
        "Sender Task",
        VOS_THREAD_POLICY_OTHER,
        (VOS_THREAD_PRIORITY_T)proccfg.priority,
        proccfg.cycleTime,
        0u,
        (VOS_THREAD_FUNC_T)senderThread,
        (void*)apph);

    tlc_updateSession(apph);

    while (1)
    {   /* drive TRDP communications */
//        tlc_process(apph, NULL, NULL);

        /* poll (receive) data */
        poll_data();
        /* process data every 500 msec */
        if (!(++tick % 50))
            process_data();
        /* wait 10 msec  */
        _sleep_msec(10);
    }

    return 0;
}

/* ---------------------------------------------------------------------------*/
