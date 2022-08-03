/*
 * Rodzhang
 *
 */

#ifndef __PLANE_LINUX_H__
#define __PLANE_LINUX_H__


#include "../plane.h"
#include "../plane_utils.h"
#include "netdev/linux_netdev_export.h"
#include "filter/linux_filter_export.h"


typedef struct {

    plane_t                 base;


    linux_netdev_export_t   *netdev;
    
    linux_filter_t          *filter;


} plane_linux_t;




#endif /* __PLANE_LINUX_H__ */

