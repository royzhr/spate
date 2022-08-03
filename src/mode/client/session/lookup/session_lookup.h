/*
 *  Rodzhang
 *
 */

#ifndef __SESSION_LOOKUP_H__
#define __SESSION_LOOKUP_H__


#include <spate_core.h>

struct session_lookup_s;

typedef struct {

    /*
     *  IP and Port must Host order.
     *
     *  Retrun value: 0 for success, -1 for failed.
     */
    int (*lookup)(struct session_lookup_s *my, uint32_t *sess_idx, 
            uint32_t sip, uint32_t dip, uint16_t sport, uint16_t dport);

    void (*destroy)(struct session_lookup_s *my);

} session_lookup_vtbl_t;

typedef struct session_lookup_s {
    
    const session_lookup_vtbl_t     *vptr;

} session_lookup_t;


session_lookup_t *session_lookup_create(void);


#endif /* __SESSION_LOOKUP_H__ */
