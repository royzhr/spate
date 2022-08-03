/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_OFFLOAD_MGR_H__
#define __EBPF_OFFLOAD_MGR_H__


#include "ebpf_offload_cfg.h"
#include "system/ebpf_offload_system.h"
#include "mode/ebpf_offload_mode.h"


typedef struct {

    ebpf_offload_cfg_t          cfg;

    ebpf_offload_system_t       *system;

    ebpf_offload_mode_t         *mode;

} ebpf_offload_mgr_t;

int  ebpf_offload_mgr_init(void);
int  ebpf_offload_mgr_setting(void);
void ebpf_offload_mgr_exit(void);

extern ebpf_offload_mgr_t  *s_ebpf_offload_mgr;

static inline ebpf_offload_cfg_t *__ebpf_offload_cfg_block_get(void)
{
    return &s_ebpf_offload_mgr->cfg;
}

#endif /* __EBPF_OFFLOAD_MGR_H__ */
