/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILE_IMP_H__
#define __PCAP_FILE_IMP_H__

#include <spate_core.h>
#include "pcap_file.h"
#include "../pcap_mgr.h"


typedef struct {

    pcap_file_t     base;

    FILE            *file;

} pcap_file_imp_t;




#endif /* __PCAP_FILE_IMP_H__ */

