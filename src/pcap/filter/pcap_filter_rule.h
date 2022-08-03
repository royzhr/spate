/*
 * Rodzhang
 *
 */

#ifndef __PCAP_FILTER_RULE_H__
#define __PCAP_FILTER_RULE_H__


#include <spate_core.h>
#include <spate_config.h>


typedef struct {

    uint32_t            enable      : 1,
                        sip_enable  : 1,
                        dip_enable  : 1;

    spate_cfg_ipv4_t    sip;
    spate_cfg_ipv4_t    dip;

} pcap_filter_rule_ip_t;


typedef struct {

    uint32_t            enable      : 1,
                        sport_enable: 1,
                        dport_enable: 1;

    spate_cfg_port_t    sport;
    spate_cfg_port_t    dport;

} pcap_filter_rule_udp_t;


typedef struct {

    uint32_t            enable      : 1,
                        sport_enable: 1,
                        dport_enable: 1;

    spate_cfg_port_t    sport;
    spate_cfg_port_t    dport;

} pcap_filter_rule_tcp_t;



typedef struct {

    pcap_filter_rule_ip_t    ip_rule;
    pcap_filter_rule_tcp_t   tcp_rule;
    pcap_filter_rule_udp_t   udp_rule;

} pcap_filter_rule_t;





#endif /* __PCAP_FILTER_RULE_H__ */
