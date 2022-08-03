/*
 * Rodzhang
 *
 */

#include <spate_debug.h>
#include "session_table_build.h"
#include "session_table_shuffle.h"


static inline uint32_t __session_ip_acquire(spate_cfg_ipv4_t *cfg_ip, uint16_t offset)
{
    uint32_t                ip;

    ip = cfg_ip->addr + offset;

    return ip;
}

static inline uint16_t __session_port_acquire(spate_cfg_port_t *cfg_port, uint16_t offset)
{
    uint16_t                port;

    port = cfg_port->port + offset;

    return port;
}


static void _session_engress_build(session_engress_t *engress, session_cfg_t *cfg, 
        uint16_t si, uint16_t di, uint16_t sp, uint16_t dp)
{
    engress->sip   = __session_ip_acquire(&cfg->sip, si);
    engress->dip   = __session_ip_acquire(&cfg->dip, di);
    engress->sport = __session_port_acquire(&cfg->sport, sp);
    engress->dport = __session_port_acquire(&cfg->dport, dp);
    engress->proto = cfg->proto;

    engress->state   = 0;
    engress->retrans = 0;
    engress->tick_id = 0;
}

static void _session_table_show(session_table_t *tbl)
{
    uint32_t                i;
    session_engress_t       *engress;
    char                    ip1[128];
    char                    ip2[128];

    for (i=0; i<tbl->sess_nr; ++i) {
        engress = &tbl->ses[i];

        strcpy(ip1, __ipv4_h_to_string(engress->sip));
        strcpy(ip2, __ipv4_h_to_string(engress->dip));

        LOGD("be: %s:%u -> %s:%u", ip1, engress->sport, ip2, engress->dport);
    }
}

static void _session_table_build(session_table_t *tbl, session_cfg_t *cfg)
{
    uint16_t                si, di, sp, dp;
    uint32_t                idx;
    session_engress_t       *engress;  

    idx = 0;

    /*
     * Is this ugly???
     */
    for (sp=0; sp<cfg->sport.cnt; ++sp) {
        for (dp=0; dp<cfg->dport.cnt; ++dp) {
            for (di=0; di<cfg->dip.cnt; ++di) {
                for(si=0; si<cfg->sip.cnt; ++si) {
                
                    engress = &tbl->ses[idx];

                    _session_engress_build(engress, cfg, si, di, sp, dp);

                    ++idx;
                }
            }
        }
    }

    ASSERT(idx == tbl->sess_nr);
}



int session_table_build(session_table_t *tbl, session_cfg_t *cfg)
{
    _session_table_build(tbl, cfg);
    
    if (cfg->table_shuffle) {
        session_table_shuffle(tbl);
    }

    if (cfg->table_show) {
        _session_table_show(tbl);
    }

    return 0;
}



