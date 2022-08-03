/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include <spate_main.h>
#include <spate_plane.h>
#include "server_worker_mgr.h"
#include "server_worker_assign.h"
#include "server_worker_ops.h"


server_worker_export_t  *g_server_worker     = NULL;
server_worker_mgr_t     *s_server_worker_mgr = NULL;


static int _server_instance_contexts_alloc(uint16_t nr)
{
    s_server_worker_mgr->contexts = mm_vmalloc(sizeof(server_instance_context_t)*nr);

    if (!s_server_worker_mgr->contexts) {
        return -1;
    }

    memset(s_server_worker_mgr->contexts, 0, sizeof(server_instance_context_t)*nr);

    return 0;
}

static void _server_instance_contexts_free(void)
{
    uint16_t                nr;

    if (!s_server_worker_mgr->contexts) {
        return;
    }

    nr = s_server_worker_mgr->worker_nr;

    mm_vfree(s_server_worker_mgr->contexts, sizeof(server_instance_context_t)*nr);
    s_server_worker_mgr->contexts = NULL;
}


int  server_worker_mgr_init(void)
{
    s_server_worker_mgr = mm_vmalloc(sizeof(*s_server_worker_mgr));
    if (!s_server_worker_mgr) {
        return -1;
    }

    memset(s_server_worker_mgr, 0, sizeof(*s_server_worker_mgr));

    if (server_worker_assign_init() < 0) {
        return -1;
    }

    g_server_worker = &s_server_worker_mgr->_export;
    g_server_worker->ops = &c_server_worker_ops;

    return 0;
}

int  server_worker_mgr_setting(void)
{
    uint16_t                cpu_nr;

    cpu_nr = __plane_get_worker_nr();

    if (_server_instance_contexts_alloc(cpu_nr) < 0) {
        return -1;
    }

    s_server_worker_mgr->worker_nr = cpu_nr;


    if (server_worker_assign_setting() < 0) {
        return -1;
    }

    return 0;
}

void server_worker_mgr_exit(void)
{
    server_worker_assign_exit();

    _server_instance_contexts_free();

    mm_vfree(s_server_worker_mgr, sizeof(*s_server_worker_mgr));
    s_server_worker_mgr = NULL;
}



