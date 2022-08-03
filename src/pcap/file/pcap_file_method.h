/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILE_METHOD_H__
#define __PCAP_FILE_METHOD_H__


#include "pcap_file_imp.h"


int  pcap_file_constructor(pcap_file_imp_t *imp, uint16_t worker_id);
void pcap_file_destructor(pcap_file_imp_t *imp);



#endif /* __PCAP_FILE_METHOD_H__ */
