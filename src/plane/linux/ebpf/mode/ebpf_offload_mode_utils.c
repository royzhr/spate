/*
 *  Rodzhang
 *
 */

#include "ebpf_offload_mode_utils.h"
#include "../ebpf_offload_mgr.h"

void ebpf_offload_mode_on_map_error()
{
    LOGE("ebpf map open error, maybe you need execute cmd:" 
            "mount bpffs %s -t bpf", s_ebpf_offload_mgr->cfg.mount_path);
}


