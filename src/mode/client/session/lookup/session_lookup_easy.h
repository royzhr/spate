/*
 *  Rodzhang
 *
 */

#ifndef __SESSION_LOOKUP_EASY_H__
#define __SESSION_LOOKUP_EASY_H__


#include "session_lookup.h"
#include "../session_mgr.h"

typedef struct {

    session_lookup_t        base;

    /*
     * Private
     */

} session_lookup_easy_t;

session_lookup_t *session_lookup_easy_create(void);


#endif /* __SESSION_LOOKUP_EASY_H__ */
