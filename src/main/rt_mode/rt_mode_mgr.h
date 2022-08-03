/*
 * Rodzhang
 *
 */

#ifndef __RT_MODE_MGR_H__
#define __RT_MODE_MGR_H__



#include <spate_core.h>
#include "rt_mode_export.h"

typedef struct {

    rt_mode_export_t    _export;

    /*
     * Private:
     */

} rt_mode_mgr_t;



int  rt_mode_mgr_init(void);
void rt_mode_mgr_exit(void);


/*
 * Private:
 */
extern rt_mode_mgr_t   *s_rt_mode_mgr;




#endif /* __RT_MODE_MGR_H__ */
