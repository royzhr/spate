/*
 * Rodzhang
 *
 */

#include "plane.h"
#include "plane_register.h"


plane_t *g_plane = NULL;


int  plane_singleton_add(const char *plane_name)
{
    const plane_register_t      *reg;
    int                         i;

    ASSERT(g_plane == NULL);

    for (i=0, reg=c_plane_register[i]; reg!=NULL; ++i,reg=c_plane_register[i]) {
        if (!strcmp(plane_name, reg->name)) {
            g_plane = reg->plane_create();
            LOGW("plane create: %s", plane_name);
            break;
        }
    }

    if (!g_plane) {
        LOGE("plane: ( %s ) not support!", plane_name);
        return -1;
    }

    return 0;
}

void plane_singleton_clean(void)
{
    if (g_plane) {
        g_plane->vptr->destroy(g_plane);

        g_plane = NULL;
    }
}


