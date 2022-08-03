/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_config.h>
#include "pcap_filter_rule_parse.h"


static void _pcap_filter_parse_item(pcap_filter_rule_t *rule, const char *key, const char *val)
{
    pcap_filter_rule_ip_t       *rule_ip;
    pcap_filter_rule_tcp_t      *rule_tcp;
    pcap_filter_rule_udp_t      *rule_udp;

    rule_ip  = &rule->ip_rule;
    rule_tcp = &rule->tcp_rule;
    rule_udp = &rule->udp_rule;

    LOGD("filter > %s : %s", key, val);

    if (!strcmp(key, "ip_saddr")) {

        rule_ip->enable     = 1;
        rule_ip->sip_enable = 1;

        __config_parse_spate_ip(&rule_ip->sip, val);

    } else if (!strcmp(key, "ip_daddr")) {

        rule_ip->enable     = 1;
        rule_ip->dip_enable = 1;

        __config_parse_spate_ip(&rule_ip->dip, val);

    } else if (!strcmp(key, "tcp_sport")) {

        rule_tcp->enable       = 1;
        rule_tcp->sport_enable = 1;
        
        __config_parse_spate_port(&rule_tcp->sport, val);

    } else if (!strcmp(key, "tcp_dport")) {

        rule_tcp->enable       = 1;
        rule_tcp->dport_enable = 1;
        
        __config_parse_spate_port(&rule_tcp->dport, val);

    } else if (!strcmp(key, "udp_sport")) {

        rule_udp->enable       = 1;
        rule_udp->sport_enable = 1;
        
        __config_parse_spate_port(&rule_udp->sport, val);

    } else if (!strcmp(key, "udp_dport")) {

        rule_udp->enable       = 1;
        rule_udp->dport_enable = 1;
        
        __config_parse_spate_port(&rule_udp->dport, val);
    }
}


static void _pcap_filter_parse_item_string(pcap_filter_rule_t *rule, char *str)
{
    char                *p;
    char                *key, *val;

    p = strchr(str, ':');
    if (p == NULL)
        return;

    *p = 0;

    key = str;
    val = p + 1;

    key = __config_string_strip_space(key);
    val = __config_string_strip_space(val);

    _pcap_filter_parse_item(rule, key, val);
}


int pcap_filter_rule_parse(pcap_filter_rule_t *rule, const char *filter_str)
{
    char                str[CFG_MAX_PER_LINE+1];
    char                *p, *q;

    strcpy(str, filter_str);

    p = str;

    for ( ; ; ) {
        q = strchr(p, ',');
        if (!q) {
            break;
        }

        *q = '\0';

        _pcap_filter_parse_item_string(rule, p);

        p = q + 1;
    }

    return 0;
}
