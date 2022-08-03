/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILTER_IMP_H__
#define __PCAP_FILTER_IMP_H__


#include "pcap_filter.h"
#include "pcap_filter_rule.h"


typedef struct {

    pcap_filter_t       base;

    pcap_filter_rule_t  rule;

} pcap_filter_imp_t;




#endif /* __PCAP_FILTER_IMP_H__ */
