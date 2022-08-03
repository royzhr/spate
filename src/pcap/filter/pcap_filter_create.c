/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include "pcap_filter_imp.h"
#include "pcap_filter_create.h"
#include "pcap_filter_method.h"



pcap_filter_t *pcap_filter_create(const char *filter_str)
{
    pcap_filter_imp_t       *imp;

    if (filter_str == NULL) {
        return NULL;
    }

    imp = mm_vmalloc(sizeof(*imp));
    if (!imp) {
        return NULL;
    }

    if (pcap_filter_constructor(imp, filter_str) < 0) {
        mm_vfree(imp, sizeof(*imp));
        return NULL;
    }
    
    return &imp->base;
}


