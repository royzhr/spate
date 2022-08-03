/*
 * Rodzhang
 *
 */

#ifndef __MAIN_EXPORT_H__
#define __MAIN_EXPORT_H__


#include <spate_core.h>


typedef struct {

    spate_mode_e (*get_mode)(void);

} main_ops_t;


/*
 * Common global setting for both client-mode and server-mode
 *
 */
typedef struct {

    const main_ops_t    *ops;

    uint8_t             quit_sig;
    uint8_t             force_quit;

    uint8_t             pcap_enable;

} main_export_t;


extern main_export_t   *g_main;





#endif /* __MAIN_EXPORT_H__ */
