/*
 * Rodzhang
 *
 */

#include "client_instance_ftbl.h"
#include "client_instance_rx.h"
#include "client_instance_stat.h"


const client_instance_ftbl_t c_client_instance_ftbl = {
    .on_recv_packet = client_instance_on_recv_packet,
    .on_stat_tx     = client_instance_stat_tx,
};

