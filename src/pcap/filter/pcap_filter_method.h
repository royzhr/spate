/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILTER_METHOD_H__
#define __PCAP_FILTER_METHOD_H__


#include "pcap_filter_imp.h"

int  pcap_filter_constructor(pcap_filter_imp_t *imp, const char *filter_str);
void pcap_filter_destructor(pcap_filter_imp_t *imp);



#endif /* __PCAP_FILTER_METHOD_H__ */
