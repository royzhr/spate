/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include <spate_utils.h>
#include "http_accept_vtbl.h"
#include "http_accept_method.h"




static void _http_accept_destroy(http_accept_t *my)
{
    http_accept_imp_t       *imp;

    imp = container_of(my, http_accept_imp_t, base);

    http_accept_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const http_accept_vtbl_t c_http_accept_vtbl = {
    .destroy = _http_accept_destroy,
};

