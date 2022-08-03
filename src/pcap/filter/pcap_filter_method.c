/*
 * Rodzhang
 *
 */

#include "pcap_filter_method.h"
#include "pcap_filter_vtbl.h"
#include "pcap_filter_rule_parse.h"


int  pcap_filter_constructor(pcap_filter_imp_t *imp, const char *filter_str)
{
    memset(imp, 0, sizeof(*imp));

    if (pcap_filter_rule_parse(&imp->rule, filter_str) < 0) {
        LOGE("parse filter rule error: %s", filter_str);
        return -1;
    }

    imp->base.vptr = &c_pcap_filter_vtbl;

    return 0;
}

void pcap_filter_destructor(pcap_filter_imp_t *imp)
{
    imp->base.vptr = NULL;
}

