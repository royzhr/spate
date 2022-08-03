/*
 * Rodzhang
 *
 */

#include <spate_mm.h>
#include "linux_worker_frame_module.h"
#include "linux_worker_frame_factory.h"
#include "linux_worker_frame_cfg_ops.h"
#include "linux_worker_frame_utils.h"
#include "../../plane_utils.h"


static int  _linux_worker_frame_module_init(void)
{
    __plane_worker_frame_clean();

    g_plane->worker_frame = plane_linux_worker_frame_factory();
    if (!g_plane->worker_frame) {
        return -1;
    }
    
    return 0;
}

static int  _linux_worker_frame_module_setting(void)
{
    plane_linux_worker_frame_t      *wf;

    wf = __get_linux_worker_frame();

    wf->worker_threads = mm_vmalloc(sizeof(linux_worker_thread_t)*wf->cfg.worker_nr);
    if (!wf->worker_threads) {
        return -1;
    }

    memset(wf->worker_threads, 0, sizeof(linux_worker_thread_t)*wf->cfg.worker_nr);

    return 0;
}

static void _linux_worker_frame_module_exit(void)
{
    __plane_worker_frame_clean();
}


const module_class_t c_linux_worker_frame_module = {
    .module_name    = "linux_worker_frame",
    .cfg_ops        = &c_linux_worker_frame_cfg_ops,
    .module_init    = _linux_worker_frame_module_init,
    .module_setting = _linux_worker_frame_module_setting,
    .module_exit    = _linux_worker_frame_module_exit,
};

