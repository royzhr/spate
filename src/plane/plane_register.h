/*
 * Rodzhang
 *
 */

#ifndef __PLANE_REGISTER_H__
#define __PLANE_REGISTER_H__


#include "plane.h"


typedef struct {

    const char      *name;

    plane_t *(*plane_create)(void);

} plane_register_t;


#define __spate_plane_register__    __attribute__((unused, section("spate_plane_register")))




#endif /* __PLANE_REGISTER_H__ */
