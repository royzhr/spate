/*
 *  Rodzhang
 *
 */

#ifndef __EBPF_SPATE_CLIENT_STAT_H__
#define __EBPF_SPATE_CLIENT_STAT_H__


#include "ebpf_spate_client_dep.h"

static __inline void __ebpf_spate_client_stat_update(spate_ebpf_client_stat_t *stat,
        uint16_t idx, uint32_t us)
{
    if (idx >= CLIENT_STAT_LATENCY_NR) {
        return;
    }

    /*
     * Too Ugly For ebpf-check
     */
    switch (idx) {
        case 0:
            stat->latency.cnt_tbl[0] ++;
            break;
        case 1:
            stat->latency.cnt_tbl[1] ++;
            break;
        case 2:
            stat->latency.cnt_tbl[2] ++;
            break;
        case 3:
            stat->latency.cnt_tbl[3] ++;
            break;
        case 4:
            stat->latency.cnt_tbl[4] ++;
            break;
        case 5:
            stat->latency.cnt_tbl[5] ++;
            break;
        case 6:
            stat->latency.cnt_tbl[6] ++;
            break;
        case 7:
            stat->latency.cnt_tbl[7] ++;
            break;
        case 8:
            stat->latency.cnt_tbl[8] ++;
            break;
        case 9:
            stat->latency.cnt_tbl[9] ++;
            break;

        case 10:
            stat->latency.cnt_tbl[10] ++;
            break;
        case 11:
            stat->latency.cnt_tbl[11] ++;
            break;
        case 12:
            stat->latency.cnt_tbl[12] ++;
            break;
        case 13:
            stat->latency.cnt_tbl[13] ++;
            break;
        case 14:
            stat->latency.cnt_tbl[14] ++;
            break;
        case 15:
            stat->latency.cnt_tbl[15] ++;
            break;
        case 16:
            stat->latency.cnt_tbl[16] ++;
            break;
        case 17:
            stat->latency.cnt_tbl[17] ++;
            break;
        case 18:
            stat->latency.cnt_tbl[18] ++;
            break;
        case 19:
            stat->latency.cnt_tbl[19] ++;
            break;


        case 20:
            stat->latency.cnt_tbl[20] ++;
            break;
        case 21:
            stat->latency.cnt_tbl[21] ++;
            break;
        case 22:
            stat->latency.cnt_tbl[22] ++;
            break;
        case 23:
            stat->latency.cnt_tbl[23] ++;
            break;
        case 24:
            stat->latency.cnt_tbl[24] ++;
            break;
        case 25:
            stat->latency.cnt_tbl[25] ++;
            break;
        case 26:
            stat->latency.cnt_tbl[26] ++;
            break;
        case 27:
            stat->latency.cnt_tbl[27] ++;
            break;
        case 28:
            stat->latency.cnt_tbl[28] ++;
            break;
        case 29:
            stat->latency.cnt_tbl[29] ++;
            break;

        case 30:
            stat->latency.cnt_tbl[30] ++;
            break;
        case 31:
            stat->latency.cnt_tbl[31] ++;
            break;
        case 32:
            stat->latency.cnt_tbl[32] ++;
            break;
        case 33:
            stat->latency.cnt_tbl[33] ++;
            break;
        case 34:
            stat->latency.cnt_tbl[34] ++;
            break;
        case 35:
            stat->latency.cnt_tbl[35] ++;
            break;
        case 36:
            stat->latency.cnt_tbl[36] ++;
            break;
        case 37:
            stat->latency.cnt_tbl[37] ++;
            break;
        case 38:
            stat->latency.cnt_tbl[38] ++;
            break;
        case 39:
            stat->latency.cnt_tbl[39] ++;
            break;

        case 40:
            stat->latency.cnt_tbl[40] ++;
            break;
        case 41:
            stat->latency.cnt_tbl[41] ++;
            break;
        case 42:
            stat->latency.cnt_tbl[42] ++;
            break;
        case 43:
            stat->latency.cnt_tbl[43] ++;
            break;
        case 44:
            stat->latency.cnt_tbl[44] ++;
            break;
        case 45:
            stat->latency.cnt_tbl[45] ++;
            break;
        case 46:
            stat->latency.cnt_tbl[46] ++;
            break;
        case 47:
            stat->latency.cnt_tbl[47] ++;
            break;
        case 48:
            stat->latency.cnt_tbl[48] ++;
            break;
        case 49:
            stat->latency.cnt_tbl[49] ++;
            break;


        case 50:
            stat->latency.cnt_tbl[50] ++;
            break;
        case 51:
            stat->latency.cnt_tbl[51] ++;
            break;
        case 52:
            stat->latency.cnt_tbl[52] ++;
            break;
        case 53:
            stat->latency.cnt_tbl[53] ++;
            break;
        case 54:
            stat->latency.cnt_tbl[54] ++;
            break;
        case 55:
            stat->latency.cnt_tbl[55] ++;
            break;
        case 56:
            stat->latency.cnt_tbl[56] ++;
            break;
        case 57:
            stat->latency.cnt_tbl[57] ++;
            break;
        case 58:
            stat->latency.cnt_tbl[58] ++;
            break;
        case 59:
            stat->latency.cnt_tbl[59] ++;
            break;
    }

    stat->latency.total_us += us;

    stat->traffic.rx_pkts += 1;

#ifdef SPATE_EBPF_DEBUG
    char            fmt4[] = "spate client stat x idx: %d us:%d";
    bpf_trace_printk(fmt4, sizeof(fmt4), idx, us);
#endif

}

static __inline void __ebpf_spate_client_stat(spate_ebpf_client_stat_t *stat, uint64_t delta)
{
    uint64_t                    us64;
    uint32_t                    us;
    uint16_t                    idx;

    us64 = delta/1000;
    us = (uint32_t)us64;

    idx = __spate_latency_slot_by_us(us);

    if (idx >= CLIENT_STAT_LATENCY_NR) {
        return;
    }
    
    __ebpf_spate_client_stat_update(stat, idx, us);
}


#endif /* __EBPF_SPATE_CLIENT_STAT_H__ */
