/*
 *  Rodzhang
 *
 */

#include "lib/ebpf_spate_client.h"



static __inline spate_ebpf_client_config_t *__get_client_config(void)
{
    uint32_t        cfg_key;

    cfg_key = 0;

    return bpf_map_lookup_elem(&spate_client_config, &cfg_key);
}

static __inline spate_ebpf_client_stat_t *__get_client_stat(void)
{
    uint32_t        cfg_key;

    cfg_key = 0;

    return bpf_map_lookup_elem(&spate_client_stat, &cfg_key);
}

static __inline int __ebpf_spate_client_on_rx_ip(char *ip, uint16_t len, struct xdp_md *ctx, 
        spate_ebpf_client_config_t *cfg, spate_ebpf_client_stat_t *stat)
{
    if (cfg->vxlan.vxlan_enable) {
        return __ebpf_spate_client_rx_vxlan(ip, len, ctx, cfg, stat);

    } else {
        return __ebpf_spate_client_rx_ip((ipv4_hdr_t *)ip, len, ctx, cfg, stat);
    }
}

SEC("xdp_spate_client")
int spate_client_ingress_on_xdp(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    uint16_t                    ether_type;
    uint16_t                    eth_len;
    uint16_t                    pkt_len;
    int                         ret;
    eth_hdr_t                   *ethhdr;
    spate_ebpf_client_config_t  *cfg;
    spate_ebpf_client_stat_t    *stat;

    if (!ctx->ingress_ifindex) {
        return XDP_PASS;
    }

    cfg = __get_client_config();
    if (!cfg) {
        return XDP_PASS;
    }

    if (!cfg->enable) {
        return XDP_PASS;
    }

    if (ctx->ingress_ifindex != cfg->device.ifindex) {
        return XDP_PASS;
    }

    stat = __get_client_stat();
    if (!stat) {
        return XDP_PASS;
    }

#ifdef SPATE_EBPF_DEBUG
    char            fmt4[] = "x4 client enable=%d, payload_size:%d";
    bpf_trace_printk(fmt4, sizeof(fmt4), cfg->enable, cfg->packet.payload_size);
#endif


    if (data_end < data + sizeof(eth_hdr_t) + sizeof(vlan_hdr_t)) {
        return XDP_PASS;
    }

    pkt_len = data_end - data;

    ethhdr = (eth_hdr_t *)data;

    if (__spate_ethhdr_parse(ethhdr, pkt_len, &ether_type, &eth_len) < 0) {
        return XDP_PASS;
    }

    if (!__spate_is_ethhdr_dmac_myself(ethhdr, cfg->device.mac_addr)) {
        return XDP_PASS;
    }

    if (ether_type == NP_ETHER_TYPE_IPV4) {

        if (data_end < data + eth_len + sizeof(ipv4_hdr_t)) {
            return XDP_PASS;
        }
        ret = __ebpf_spate_client_on_rx_ip(data+eth_len, pkt_len-eth_len, ctx, cfg, stat);

    } else if (ether_type == NP_ETHER_TYPE_ARP) {

        if (data_end < data + eth_len + sizeof(arp_hdr_t)) {
            return XDP_PASS;
        }
        ret = __ebpf_spate_client_rx_arp((arp_hdr_t*)(data+eth_len), pkt_len-eth_len, cfg);

    } else {
        return XDP_PASS;
    }

    if (ret == XDP_TX) {
        __spate_ethhdr_reverse_mac(ethhdr, cfg->device.mac_addr);
    }

    return ret;
}






char _license[] SEC("license") = "GPL";

