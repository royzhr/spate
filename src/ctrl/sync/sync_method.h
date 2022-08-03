/*
 * Rodzhang
 *
 */

#ifndef __SYNC_METHOD_H__
#define __SYNC_METHOD_H__


#include "sync_imp.h"


int  sync_constructor(sync_imp_t *imp, uint16_t worker_nr, uint16_t assist_nr, uint16_t size);
void sync_destructor(sync_imp_t *imp);




#endif /* __SYNC_METHOD_H__ */
