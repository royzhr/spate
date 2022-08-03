/*
 * Rodzhang
 *
 * Runtime Mode of spate
 */

#ifndef __MODE_H__
#define __MODE_H__


#include <spate_core.h>
#include "mode_class.h"



/*
 * spate get special mode's ops
 */
const mode_ops_t *spate_mode_get_ops(spate_mode_e mode);

void spate_mode_put_ops(const mode_ops_t *mode_ops);

#endif /* __MODE_H__ */

