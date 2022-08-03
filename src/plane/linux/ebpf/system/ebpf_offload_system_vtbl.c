/*
 *  Rodzhang
 *
 */

#include "ebpf_offload_system_vtbl.h"
#include "ebpf_offload_system_method.h"
#include <spate_mm.h>
#include <spate_utils.h>


static int _ebpf_offload_system_attach(ebpf_offload_system_t *my)
{
    ebpf_offload_system_imp_t       *imp;
    int                             ret;

    imp = container_of(my, ebpf_offload_system_imp_t, base);

    ret = system(imp->cmd_attach);
    
    LOGW("system attach: %s ", imp->cmd_attach);

    if (ret == 512) {
        // XDP program already attached 

        system(imp->cmd_detach);

        ret = system(imp->cmd_attach);
    }

    if (ret) {
        LOGE("cmd execute error, ret=%d, errno=%d", ret, errno);
        return -1;
    }

    return 0;
}

static int _ebpf_offload_system_detach(ebpf_offload_system_t *my)
{
    ebpf_offload_system_imp_t       *imp;
    int                             ret;

    imp = container_of(my, ebpf_offload_system_imp_t, base);

    ret = system(imp->cmd_detach);
    
    LOGW("system detach: %s ret=%d", imp->cmd_detach , ret);
    return 0;
}

static void _ebpf_offload_system_destroy(ebpf_offload_system_t *my)
{
    ebpf_offload_system_imp_t       *imp;

    imp = container_of(my, ebpf_offload_system_imp_t, base);

    ebpf_offload_system_destructor(imp);

    mm_vfree(imp, sizeof(*imp));

}


const ebpf_offload_system_vtbl_t c_ebpf_offload_system_vtbl = {
    .attach  = _ebpf_offload_system_attach,
    .detach  = _ebpf_offload_system_detach,
    .destroy = _ebpf_offload_system_destroy,
};

