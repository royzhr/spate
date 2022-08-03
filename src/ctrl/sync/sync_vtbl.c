/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include "sync_vtbl.h"
#include "sync_method.h"
#include <spate_mm.h>
#include <spate_utils.h>

static inline int __sync_is_all_report(sync_imp_t *imp)
{
    uint16_t                i;
    uint16_t                nr;

    nr = imp->worker_nr + imp->assist_nr;

    for (i=0; i<nr; ++i) {
        if (!imp->report_boards[i]) {
            return 0;
        }
    }

    return 1;
}

static void _sync_wait_all_report(sync_imp_t *imp)
{
    while (1) {

        if (__sync_is_all_report(imp)) {
            break;
        }

        __spate_msleep(1);
    }
}

static void _sync_wait_run(sync_imp_t *imp)
{
    if (imp->run) {
        LOGW("sync wait run already run!!!!");
    }

    while (1) {
        if (imp->run) {
            break;
        }
    }
}

static void _sync_report_on_sync_wait(sync_t *my, int report_id)
{
    sync_imp_t          *imp;

    imp = container_of(my, sync_imp_t, base);

    if (report_id >= 0) {
        ASSERT(report_id < imp->worker_nr);
    } else {
        ASSERT(-report_id <= imp->assist_nr);
    }

    imp->workers[report_id] = 1;

    SMP_MB();

    _sync_wait_all_report(imp);

    //LOGD("sync wait report_id %d wait finish", report_id);

    _sync_wait_run(imp);

    //LOGD("sync run , report_id: %d", report_id);
}

static int _sync_is_all_report(sync_t *my)
{
    sync_imp_t          *imp;

    imp = container_of(my, sync_imp_t, base);

    return __sync_is_all_report(imp);
}

static void _sync_wake_all_waiter(sync_t *my)
{
    sync_imp_t          *imp;

    imp = container_of(my, sync_imp_t, base);

    imp->run = 1;

    SMP_MB();

    //LOGD("sync wake all");
}

static void _sync_destroy(sync_t *my)
{
    sync_imp_t          *imp;

    imp = container_of(my, sync_imp_t, base);

    sync_destructor(imp);

    mm_vfree(imp, imp->size);
}

const sync_vtbl_t c_sync_vtbl = {
    .report_on_sync_wait = _sync_report_on_sync_wait,
    .is_all_report       = _sync_is_all_report,
    .wake_all_waiter     = _sync_wake_all_waiter,
    .destroy             = _sync_destroy,
};

