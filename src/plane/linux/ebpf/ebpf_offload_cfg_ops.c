/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include "ebpf_offload_cfg_ops.h"
#include "ebpf_offload_mgr.h"

static void _ebpf_get_map_mount_path(char *mount_path)
{
    const char      *var;

    var = getenv("TC_BPF_MNT");

    if (var == NULL) {
        strcpy(mount_path, "/sys/fs/bpf/");
    } else {
        strcpy(mount_path, var);
    }

    LOGW("bpf mount path: %s", mount_path);
}


static inline void __ebpf_offload_cfg_default(ebpf_offload_cfg_t *cfg)
{
    cfg->offload_enable = 0;

    _ebpf_get_map_mount_path(cfg->mount_path);
}


static void _ebpf_offload_cfg_begin(void)
{
    ebpf_offload_cfg_t       *cfg;

    cfg = __ebpf_offload_cfg_block_get();

    __ebpf_offload_cfg_default(cfg);
}

static int _ebpf_offload_cfg_finish(void)
{

    return 0;
}

static int _ebpf_offload_cfg_parse_line(const char *key, const char *val)
{
    ebpf_offload_cfg_t       *cfg;

    cfg = __ebpf_offload_cfg_block_get();

    if (!strcmp(key, "linux.ebpf.offload_enable")) {
        cfg->offload_enable = __config_parse_bool(val);
        return 1;

    } else if (!strcmp(key, "linux.ebpf.obj_path")) {
        cfg->obj_path = strdup(val);
        return 1;

    }

    return 0;
}

const module_cfg_ops_t c_ebpf_offload_cfg_ops = {
    .begin      = _ebpf_offload_cfg_begin,
    .finish     = _ebpf_offload_cfg_finish,
    .parse_line = _ebpf_offload_cfg_parse_line,
};
