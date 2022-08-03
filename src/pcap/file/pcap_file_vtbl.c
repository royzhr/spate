/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_mm.h>
#include <spate_main.h>
#include <spate_plane.h>
#include "pcap_file_imp.h"
#include "pcap_file_vtbl.h"
#include "pcap_file_write.h"
#include "pcap_file_method.h"
#include <spate_utils.h>


static void _pcap_cycles_to_timestamp(uint64_t cycles, uint32_t *psec, uint32_t *pus)
{
    uint32_t                us;
    uint64_t                delta;

    delta = cycles - s_pcap_mgr->start_cycles;

    us = __spate_cycles_to_usec(delta);

    *psec = us / 1000000;
    *pus  = us % 1000000;
}

static int _pcap_file_fsave(pcap_file_t *my, uint64_t cycles, char *pkt_data, uint16_t pkt_len)
{
    pcap_file_imp_t         *imp;
    uint32_t                sec, us;

    imp = container_of(my, pcap_file_imp_t, base);

    _pcap_cycles_to_timestamp(cycles, &sec, &us);

    return pcap_file_write_packet(imp->file, pkt_data, pkt_len, sec, us);
}

static void _pcap_file_fflush(pcap_file_t *my)
{
    pcap_file_imp_t         *imp;

    imp = container_of(my, pcap_file_imp_t, base);

    fflush(imp->file);
}

static void _pcap_file_destroy(pcap_file_t *my)
{
    pcap_file_imp_t         *imp;

    imp = container_of(my, pcap_file_imp_t, base);

    pcap_file_destructor(imp);

    mm_vfree(imp, sizeof(*imp));
}

const pcap_file_vtbl_t c_pcap_file_vtbl = {
    .fsave   = _pcap_file_fsave,
    .fflush  = _pcap_file_fflush,
    .destroy = _pcap_file_destroy,
};

