/*
 * Rodzhang
 *
 */

#include "host_ops.h"
#include "garp/host_garp.h"


static int _host_on_worker_init(uint16_t worker_id)
{
    if (worker_id == 0) {
        host_garp_announce(worker_id);
    }

    return 0;
}

const host_ops_t c_host_ops = {
    .on_worker_init = _host_on_worker_init,
};


