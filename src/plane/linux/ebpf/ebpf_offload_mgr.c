/*
 *  Rodzhang
 *
 */

#include "ebpf_offload_mgr.h"
#include <spate_mm.h>


ebpf_offload_mgr_t       *s_ebpf_offload_mgr  = NULL;


int  ebpf_offload_mgr_init(void)
{
    s_ebpf_offload_mgr = mm_vmalloc(sizeof(*s_ebpf_offload_mgr));

    if (!s_ebpf_offload_mgr) {
        return -1;
    }

    memset(s_ebpf_offload_mgr, 0, sizeof(*s_ebpf_offload_mgr));

    return 0;
}

int  ebpf_offload_mgr_setting(void)
{
    s_ebpf_offload_mgr->system = ebpf_offload_system_create(&s_ebpf_offload_mgr->cfg);
    if (!s_ebpf_offload_mgr->system) {
        return -1;
    }

    if (s_ebpf_offload_mgr->system->vptr->attach(s_ebpf_offload_mgr->system) < 0) {
        s_ebpf_offload_mgr->system->vptr->destroy(s_ebpf_offload_mgr->system);
        return -1;
    }

    s_ebpf_offload_mgr->mode = ebpf_offload_mode_create(&s_ebpf_offload_mgr->cfg);
    if (!s_ebpf_offload_mgr->mode) {
        s_ebpf_offload_mgr->system->vptr->detach(s_ebpf_offload_mgr->system);
        s_ebpf_offload_mgr->system->vptr->destroy(s_ebpf_offload_mgr->system);
        return -1;
    }

    if (s_ebpf_offload_mgr->mode->vptr->attach(s_ebpf_offload_mgr->mode) < 0) {
        s_ebpf_offload_mgr->system->vptr->detach(s_ebpf_offload_mgr->system);
        s_ebpf_offload_mgr->system->vptr->destroy(s_ebpf_offload_mgr->system);

        s_ebpf_offload_mgr->mode->vptr->destroy(s_ebpf_offload_mgr->mode);
        return -1;
    }

    return 0;
}

void ebpf_offload_mgr_exit(void)
{
    if (s_ebpf_offload_mgr->mode) {
        s_ebpf_offload_mgr->mode->vptr->detach(s_ebpf_offload_mgr->mode);
        s_ebpf_offload_mgr->mode->vptr->destroy(s_ebpf_offload_mgr->mode);
    }

    if (s_ebpf_offload_mgr->system) {
        s_ebpf_offload_mgr->system->vptr->detach(s_ebpf_offload_mgr->system);
        s_ebpf_offload_mgr->system->vptr->destroy(s_ebpf_offload_mgr->system);
    }

    mm_vfree(s_ebpf_offload_mgr, sizeof(*s_ebpf_offload_mgr));

    s_ebpf_offload_mgr = NULL;
}


