/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include <spate_utils.h>
#include "pcap_filter_imp.h"
#include "pcap_filter_vtbl.h"
#include "pcap_filter_method.h"
#include "pcap_filter_rule_match.h"


static int _pcap_filter_is_match(pcap_filter_t *my, char *pkt_data, uint16_t pkt_len)
{
    pcap_filter_imp_t       *imp;
    pcap_filter_rule_t      *rule;

    imp = container_of(my, pcap_filter_imp_t, base);

    rule = &imp->rule;

    return pcap_filter_rule_match(rule, pkt_data, pkt_len);
}

static void _pcap_filter_destroy(pcap_filter_t *my)
{
    pcap_filter_imp_t       *imp;

    imp = container_of(my, pcap_filter_imp_t, base);

    pcap_filter_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const pcap_filter_vtbl_t c_pcap_filter_vtbl = {
    .is_match   = _pcap_filter_is_match,
    .destroy    = _pcap_filter_destroy,
};



