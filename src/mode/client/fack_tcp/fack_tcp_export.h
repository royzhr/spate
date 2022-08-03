/*
 * Rodzhang
 *
 */

#ifndef __FACK_TCP_EXPORT_H__
#define __FACK_TCP_EXPORT_H__


#include "fack_tcp_cfg.h"

/*
 * the export of fack_tcp Module
 */
typedef struct {
    
    fack_tcp_cfg_t          cfg;

} fack_tcp_export_t;


extern fack_tcp_export_t     *g_fack_tcp;



#endif /* __FACK_TCP_EXPORT_H__ */
