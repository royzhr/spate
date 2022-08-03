/*
 * Rodzhang
 *
 */

#ifndef __MAIN_MGR_H__
#define __MAIN_MGR_H__



#include "main_export.h"


typedef struct {
    
    main_export_t       _export;

    /*
     * Private: 
     */

} main_mgr_t;


int  main_mgr_init(void);
void main_mgr_exit(void);


/*
 * Private
 */
extern main_mgr_t   *s_main_mgr;


#endif /* __MAIN_MGR_H__ */
