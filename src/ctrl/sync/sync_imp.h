/*
 * Rodzhang
 *
 */

#ifndef __SYNC_IMP_H__
#define __SYNC_IMP_H__


#include "sync.h"


typedef struct {
    sync_t          base;

    uint16_t        size;
    uint16_t        worker_nr;
    uint16_t        assist_nr;

    volatile int    run;

    volatile int    *workers;
    volatile int    report_boards[];


} sync_imp_t;




#endif /* __SYNC_IMP_H__ */
