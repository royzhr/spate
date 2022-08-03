/*
 * Rodzhang
 *
 */

#include <pcap/pcap.h>
#include "linux_filter_bpf.h"
#include <spate_mm.h>


static void _linux_filter_print_bpf(struct bpf_program *fcode)
{
    struct bpf_insn         *insn;
    int                     i;

    insn = fcode->bf_insns;

    for (i = 0; i < fcode->bf_len; ++insn, ++i)
    {
        LOGD("{ 0x%x, %d, %d, 0x%08x },", insn->code, insn->jt, insn->jf, insn->k);
    }
}


int  linux_filter_bpf_constructor(struct sock_fprog *bpf_code, const char *filter_string)
{
    int                     ret;
    struct bpf_program      fcode;
    uint16_t                code_size;

    ret = pcap_compile_nopcap(1500, DLT_EN10MB, &fcode, filter_string, 1, PCAP_NETMASK_UNKNOWN);
    if (ret < 0) {
        return -1;
    }

    code_size = sizeof(*bpf_code->filter) * fcode.bf_len;

    bpf_code->filter = mm_vmalloc(code_size);
    if (!bpf_code->filter) {
        return -1;
    }
    bpf_code->len = fcode.bf_len;

    memcpy(bpf_code->filter, fcode.bf_insns, code_size);

    _linux_filter_print_bpf(&fcode);

    pcap_freecode(&fcode);

    return 0;
}

void linux_filter_bpf_destructor(struct sock_fprog *bpf_code)
{
    ASSERT(bpf_code->filter);

    mm_vfree(bpf_code->filter, sizeof(*bpf_code->filter)*bpf_code->len);

    bpf_code->filter = NULL;
    bpf_code->len    = 0;
}

