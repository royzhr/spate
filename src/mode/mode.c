/*
 * Rodzhang
 *
 */

#include <unistd.h>
#include "mode.h"
#include "client/client.h"
#include "server/server.h"


const mode_ops_t *spate_mode_get_ops(spate_mode_e mode)
{
    switch (mode) {
        case SPATE_MODE_CLIENT:
            return &c_client_mode_ops;

        case SPATE_MODE_SERVER:
            return &c_server_mode_ops;

        default:
            break;
    }
    return NULL;

}

void spate_mode_put_ops(__UNUSED__ const mode_ops_t *mode_ops)
{
}

