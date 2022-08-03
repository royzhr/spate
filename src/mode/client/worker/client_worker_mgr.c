/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include <spate_main.h>
#include <spate_plane.h>
#include "client_worker_mgr.h"
#include "client_worker_assign.h"
#include "client_worker_ops.h"


client_worker_export_t  *g_client_worker     = NULL;
client_worker_mgr_t     *s_client_worker_mgr = NULL;


static int _client_worker_contexts_alloc(uint16_t nr)
{
    ASSERT(s_client_worker_mgr);
    
    s_client_worker_mgr->contexts = mm_vmalloc(sizeof(client_instance_context_t)*nr);
    if (!s_client_worker_mgr->contexts) {
        return -1;
    }

    memset(s_client_worker_mgr->contexts, 0, sizeof(client_instance_context_t)*nr);

    return 0;
}

static void _client_worker_contexts_free(void)
{
    uint16_t                    nr;

    ASSERT(s_client_worker_mgr);

    if (s_client_worker_mgr->contexts) {
        nr = s_client_worker_mgr->worker_nr;
        mm_vfree(s_client_worker_mgr->contexts, sizeof(client_instance_context_t)*nr);
        s_client_worker_mgr->contexts = NULL;
    }
}


int  client_worker_mgr_init(void)
{
    s_client_worker_mgr = mm_vmalloc(sizeof(*s_client_worker_mgr));
    if (!s_client_worker_mgr) {
        return -1;
    }

    memset(s_client_worker_mgr, 0, sizeof(*s_client_worker_mgr));

    if (client_worker_assign_init() < 0) {
        return -1;
    }

    g_client_worker = &s_client_worker_mgr->_export;
    g_client_worker->ops = &c_client_worker_ops;

    return 0;
}

int  client_worker_mgr_setting(void)
{
    uint16_t                cpu_nr;

    cpu_nr = __plane_get_worker_nr();

    if (_client_worker_contexts_alloc(cpu_nr) < 0) {
        return -1;
    }

    s_client_worker_mgr->worker_nr = cpu_nr;
    
    if (client_worker_assign_setting() < 0) {
        return -1;
    }

    return 0;
}

void client_worker_mgr_exit(void)
{
    client_worker_assign_exit();

    _client_worker_contexts_free();

    mm_vfree(s_client_worker_mgr, sizeof(*s_client_worker_mgr));

    s_client_worker_mgr = NULL;
    g_client_worker     = NULL;
}


