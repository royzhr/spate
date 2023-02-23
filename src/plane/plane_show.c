/*
 *  Rodzhang
 *
 */

#include "plane_show.h"
#include <spate_print.h>


static int _is_plane_support_dpdk(void) 
{
#ifdef DPDK_ENABLE
    return 1;
#else
    return 0;
#endif
}


static int _is_plane_support_ebpf_offload(void)
{

#ifdef EBPF_ENABLE
    return 1;
#else
    return 0;
#endif
}

#define MAX_SHOW_LEN    128

static const char *_plane_support_string(int is_support, char *buf, uint16_t buf_len)
{
    if (is_support) {
        return __spate_color_string(buf, buf_len, SPATE_COLOR_B_GREEN, "[Can Use]");
    } else {
        return __spate_color_string(buf, buf_len, SPATE_COLOR_B_RED, "[Not Compile]");
    }

}


void plane_show_support(void)
{
    char                dpdk[MAX_SHOW_LEN];
    char                ebpf[MAX_SHOW_LEN];
    char                raw[MAX_SHOW_LEN];
    char                af_xdp[MAX_SHOW_LEN];
    int                 support_dpdk;
    int                 support_ebpf;

    support_dpdk = _is_plane_support_dpdk();
    support_ebpf = _is_plane_support_ebpf_offload();

    _plane_support_string(support_dpdk, dpdk, MAX_SHOW_LEN), 
    _plane_support_string(support_ebpf, ebpf, MAX_SHOW_LEN), 
    _plane_support_string(1, raw, MAX_SHOW_LEN), 
    __spate_color_string(af_xdp, MAX_SHOW_LEN, SPATE_COLOR_B_RED, "[Need Develop...]");

    __spate_print("support plane list:\n");
    __spate_print("|\n");
    __spate_print("|-- DPDK  : %s \n", dpdk);
    __spate_print("|\n");
    __spate_print("|-- Linux  \n");
    __spate_print("    |--- eBPF offload : %s \n", ebpf);
    __spate_print("    |--- Socket\n");
    __spate_print("         |--- RAW     : %s \n", raw);
    __spate_print("         |--- AF_XDP  : %s \n", af_xdp);

    __spate_print("\n\n");
}

