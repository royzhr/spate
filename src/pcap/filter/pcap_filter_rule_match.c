/*
 * Rodzhang
 *
 */

#include "pcap_filter_rule_match.h"
#include <spate_net.h>



static int _pcap_filter_rule_match_udp(pcap_filter_rule_udp_t *rule_udp, 
        udp_hdr_t *udp, uint16_t udp_len)
{
    if (unlikely(!__spate_is_udphdr_check_ok(udp, udp_len))) {
        return 0;
    }

    if (rule_udp->enable) {
        if (rule_udp->sport_enable) {
            if (!__spate_cfg_port_is_contain(&rule_udp->sport, udp->src_port)) {
                return 0;
            }
        }

        if (rule_udp->dport_enable) {
            if (!__spate_cfg_port_is_contain(&rule_udp->dport, udp->dst_port)) {
                return 0;
            }
        }
    }

    return 1;
}

static int _pcap_filter_rule_match_tcp(pcap_filter_rule_tcp_t *rule_tcp,
        tcp_hdr_t *tcp, uint16_t tcp_len)
{
    if (unlikely(!__spate_is_tcphdr_check_ok(tcp, tcp_len))) {
        return 0;
    }

    if (rule_tcp->enable) {
    
        if (rule_tcp->sport_enable) {
            if (!__spate_cfg_port_is_contain(&rule_tcp->sport, tcp->src_port)) {
                return 0;
            }
        }

        if (rule_tcp->dport_enable) {
            if (!__spate_cfg_port_is_contain(&rule_tcp->dport, tcp->dst_port)) {
                return 0;
            }
        }
    }

    return 1;
}


static int _pcap_filter_rule_match_ip(pcap_filter_rule_t *rule, 
        ipv4_hdr_t *iphdr, uint16_t ip_len)
{
    pcap_filter_rule_ip_t   *rule_ip;
    uint16_t                l4_len, iphdr_len;
    void                    *l4_hdr;

    rule_ip = &rule->ip_rule;

    if (unlikely(!__spate_is_iphdr_check_ok(iphdr, ip_len))) {
        return 0;
    }

    iphdr_len = __spate_iphdr_len(iphdr);
    l4_len = ip_len - iphdr_len;
    l4_hdr = (char *)(iphdr) + iphdr_len;

    if (rule_ip->enable) {
        
        if (rule_ip->sip_enable) {
            if (!__spate_cfg_ip_is_contain(&rule_ip->sip, iphdr->src_addr)) {
                return 0;
            }
        }

        if (rule_ip->dip_enable) {
            if (!__spate_cfg_ip_is_contain(&rule_ip->dip, iphdr->dst_addr)) {
                return 0;
            }
        }
    }

    if (iphdr->next_proto_id == IPPROTO_UDP) {

        return _pcap_filter_rule_match_udp(&rule->udp_rule, (udp_hdr_t *)l4_hdr, l4_len);

    } else if (iphdr->next_proto_id == IPPROTO_TCP) {
        
        return _pcap_filter_rule_match_tcp(&rule->tcp_rule, (tcp_hdr_t *)l4_hdr, l4_len);
    }

    return 0;
}


int pcap_filter_rule_match(pcap_filter_rule_t *rule, char *pkt_data, uint16_t pkt_len)
{
    uint16_t                eth_len;
    uint16_t                ether_type;
    eth_hdr_t               *ethhdr;

    ethhdr = (eth_hdr_t *)pkt_data;
    
    if (__spate_ethhdr_parse(ethhdr, pkt_len, &ether_type, &eth_len) < 0) {
        return 0;
    }

    if (ether_type == NP_ETHER_TYPE_IPV4) {
        
        return _pcap_filter_rule_match_ip(rule, 
                (ipv4_hdr_t *)(pkt_data+eth_len), 
                pkt_len - eth_len);

    } else {
        return 0;
    }
}


