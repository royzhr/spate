/*
 * Rodzhang
 *
 */

#ifndef __PLANE_CONTEXT_H__
#define __PLANE_CONTEXT_H__


#include <spate_core.h>

struct _plane_context_s;

typedef struct {

    void (*destroy)(struct _plane_context_s *my);

} plane_context_vtbl_t;



typedef struct _plane_context_s {

    const plane_context_vtbl_t  *vptr;

} plane_context_t;




#endif /* __PLANE_CONTEXT_H__ */

