/*
 * Rodzhang
 *
 */

#ifndef __FACK_TCP_MGR_H__
#define __FACK_TCP_MGR_H__


#include "fack_tcp_export.h"


typedef struct {

    fack_tcp_export_t        _export;

    /*
     * Private:
     */

} fack_tcp_mgr_t;


int  fack_tcp_mgr_init(void);
int  fack_tcp_mgr_setting(void);
void fack_tcp_mgr_exit(void);


/*
 * Private (Only used in this module)
 */
extern fack_tcp_mgr_t *s_fack_tcp_mgr;



static inline fack_tcp_cfg_t *__fack_tcp_cfg_block_get(void)
{
    return &g_fack_tcp->cfg;
}



#endif /* __FACK_TCP_MGR_H__ */
