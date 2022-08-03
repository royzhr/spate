/*
 * Rodzhang
 *
 */

#include "pcap_file_method.h"
#include "pcap_file_vtbl.h"
#include "pcap_file_write.h"


static inline void __pcap_file_path_fill(char *path, uint16_t worker_id)
{
    sprintf(path, "%s_%d.pcap", s_pcap_mgr->cfg.file_prefix, worker_id);
}

int  pcap_file_constructor(pcap_file_imp_t *imp, uint16_t worker_id)
{
    FILE                    *fp;
    char                    path[SPATE_MAX_PATH];

    __pcap_file_path_fill(path, worker_id);

    fp = fopen(path, "wb");

    if (!fp) {
        LOGE("pcap file open failed: %s", path);
        return -1;
    }

    if (pcap_file_write_header(fp) < 0) {
        LOGE("pcap file write header failed!");
        fclose(fp);
        return -1;
    }

    imp->file = fp;
    imp->base.vptr = &c_pcap_file_vtbl;

    return 0;
}


void pcap_file_destructor(pcap_file_imp_t *imp)
{
    fclose(imp->file);

    imp->file = NULL;

    LOGI("fclose pcap file");
}


