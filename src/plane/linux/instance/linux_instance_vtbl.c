/*
 * Rodzhang
 *
 */


#include <spate_core.h>
#include <spate_mm.h>
#include "linux_instance_vtbl.h"
#include "../../plane_instance_method.h"

#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)

#include "client/linux_client_instance_run.h"
#include "server/linux_server_instance_run.h"


static void _plane_linux_instance_run(__UNUSED__ plane_instance_t *my, 
        spate_mode_e mode, instance_context_t *ctx)
{
    LOGI("plane instance enter mode:%d, pid:%lu, tid:%lu, worker_id:%u", 
            mode, getpid(), gettid(), ctx->worker_id);

    switch (mode) {
        case SPATE_MODE_CLIENT:
            linux_client_instance_run(ctx);
            break;

        case SPATE_MODE_SERVER:
            linux_server_instance_run(ctx);
            break;

        default:
            ASSERT(0);
            break;
    }

}

static void _plane_linux_instance_destroy(plane_instance_t *my)
{
    plane_instance_destructor(my);

    mm_vfree(my, sizeof(*my));
}

const plane_instance_vtbl_t c_plane_linux_instance_vtbl = {
    .instance_run = _plane_linux_instance_run,
    .destroy      = _plane_linux_instance_destroy,
};


