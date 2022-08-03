/*
 * Rodzhang
 *
 */

#ifndef __SESSION_TABLE_H__
#define __SESSION_TABLE_H__



#include "session_struct.h"


typedef struct {

    session_engress_t   *ses;
    session_ingress_t   *sis;

    /*
     * the count of session
     */
    uint32_t            sess_nr;

} session_table_t;


int  session_table_init(void);
int  session_table_setting(void);
void session_table_exit(void);




#endif /* __SESSION_TABLE_H__ */
