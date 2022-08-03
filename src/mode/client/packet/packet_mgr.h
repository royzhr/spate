/*
 * Rodzhang
 *
 */

#ifndef __PACKET_MGR_H__
#define __PACKET_MGR_H__


#include "packet_export.h"

typedef struct {

    packet_export_t        _export;

    /*
     * Private:
     */

} packet_mgr_t;


int  packet_mgr_init(void);
int  packet_mgr_setting(void);
void packet_mgr_exit(void);


static inline packet_cfg_t *__packet_cfg_block_get(void)
{
    return &g_packet->cfg;
}



#endif /* __PACKET_MGR_H__ */
