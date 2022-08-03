/*
 * Rodzhang
 *
 */

#ifndef __LINUX_NETDEV_MGR_H__
#define __LINUX_NETDEV_MGR_H__


#include "linux_netdev_export.h"
#include "../plane_linux_utils.h"
#include <spate_utils.h>

typedef struct {
    
    linux_netdev_export_t        _export;

    /*
     * Private:
     */


} linux_netdev_mgr_t;


int  linux_netdev_mgr_init(void);
int  linux_netdev_mgr_setting(void);
void linux_netdev_mgr_exit(void);


/*
 * Private: Only available at this Module
 */

static inline linux_netdev_mgr_t *__get_linux_netdev_mgr(void)
{
    plane_linux_t            *lix;

    lix = __get_plane_linux();

    return container_of(lix->netdev, linux_netdev_mgr_t, _export);
}

static inline void __set_linux_netdev_mgr(linux_netdev_mgr_t *mgr)
{
    plane_linux_t            *lix;

    lix = __get_plane_linux();

    lix->netdev = &mgr->_export;
}

#endif /* __LINUX_NETDEV_MGR_H__ */

