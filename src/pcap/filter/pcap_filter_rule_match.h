/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILTER_RULE_MATCH_H__
#define __PCAP_FILTER_RULE_MATCH_H__


#include "pcap_filter_rule.h"


int pcap_filter_rule_match(pcap_filter_rule_t *rule, char *pkt_data, uint16_t pkt_len);





#endif /* __PCAP_FILTER_RULE_MATCH_H__ */

