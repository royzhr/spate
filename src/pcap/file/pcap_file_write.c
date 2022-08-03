/*
 * Rodzhang
 *
 */

#include "pcap_file_write.h"
#include "pcap_file_format.h"

static const pcap_file_header_t c_pcap_file_header = {
    .magic = 0xA1B2C3D4,
    .version_major = 2,
    .version_minor = 4,
    .thiszone = 0,
    .sigfigs = 0,
    .snaplen = 0x40000,
    .linktype = 1,
};

int pcap_file_write_header(FILE *fp)
{
    fwrite(&c_pcap_file_header, sizeof(c_pcap_file_header), 1, fp);

    return 0;
}

int pcap_file_write_packet(FILE *fp, char *pkt_data, uint16_t pkt_len, uint32_t sec, uint32_t us)
{
    pcap_pkthdr_t           hdr;

    hdr.sec    = sec;
    hdr.us     = us;
    hdr.caplen = pkt_len;
    hdr.len    = pkt_len;

    fwrite(&hdr, sizeof(hdr), 1, fp);
    fwrite(pkt_data, pkt_len, 1, fp);

    return 0;
}
