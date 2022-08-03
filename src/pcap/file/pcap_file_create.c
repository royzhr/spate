/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "pcap_file_create.h"
#include "pcap_file_imp.h"
#include "pcap_file_method.h"




pcap_file_t *pcap_file_create(uint16_t worker_id)
{
    pcap_file_imp_t         *imp;

    imp = mm_vmalloc(sizeof(*imp));

    if (pcap_file_constructor(imp, worker_id) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }

    return &imp->base;
}


