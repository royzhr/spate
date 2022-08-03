/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_event.h>
#include "client_worker_event.h"
#include "client_worker_event_pps.h"



int  client_worker_event_init(void)
{
    return 0;
}

int  client_worker_event_setting(void)
{

    g_event->ops->register_handler(EVENT_PPS_CHANGE, client_worker_event_on_pps_change, NULL);

    return 0;
}

void client_worker_event_exit(void)
{
    g_event->ops->unregister_handler(EVENT_PPS_CHANGE, client_worker_event_on_pps_change, NULL);
}


