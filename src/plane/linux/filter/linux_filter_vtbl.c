/*
 * Rodzhang
 *
 */

#include "linux_filter_vtbl.h"
#include "linux_filter_method.h"
#include <spate_mm.h>
#include <spate_utils.h>


static const struct sock_fprog *_linux_filter_get_filter_bpf(linux_filter_t *my)
{
    linux_filter_imp_t      *imp;

    imp = container_of(my, linux_filter_imp_t, base);

    if (imp->has_filter) {
        return &imp->bpf_code;
    } else {
        return NULL;
    }
}

static void _linux_filter_destroy(linux_filter_t *my)
{
    linux_filter_imp_t      *imp;

    imp = container_of(my, linux_filter_imp_t, base);

    linux_filter_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const linux_filter_vtbl_t c_linux_filter_vtbl = {
    .get_filter_bpf = _linux_filter_get_filter_bpf,
    .destroy        = _linux_filter_destroy,
};
