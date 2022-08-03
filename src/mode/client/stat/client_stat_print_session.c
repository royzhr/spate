/*
 *  Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_session.h>
#include "client_stat_print.h"
#include "client_stat_print_session.h"


static inline void __client_stat_print_session_title(void)
{
    stat_print( "--------------------------------------"
                "\033[1;37m  TCP Session State \033[0m"
                "--------------------------------------\n");

    stat_print("        Total |          Idle |     SYN_Send |    Establish |         FIN_Send |"
            "        Closed |\n");
    stat_print("--------------+---------------+--------------+--------------+"
            "------------------+---------------|\n");

}

static inline void __client_stat_print_session_info(client_stat_info_session_t *session)
{
    uint32_t                total;
    uint32_t                idle;
    uint32_t                syn_send;
    uint32_t                establish;
    uint32_t                fin_send;
    uint32_t                closed;

    idle      = session->idle;
    syn_send  = session->syn_send;
    establish = session->establish;
    fin_send  = session->fin_send;
    closed    = session->closed;

    total = idle + syn_send + establish + fin_send + closed;

    stat_print(" %12u |  %12u | %12u | %12u |     %12u |  %12u |\n",
            total, idle, syn_send, establish, fin_send, closed);
}

void client_stat_print_session(client_stat_info_session_t *session)
{
    if (g_session->cfg.proto != SPATE_TCP) {
        return;
    }
    
    __client_stat_print_session_title();

    __client_stat_print_session_info(session);
}


