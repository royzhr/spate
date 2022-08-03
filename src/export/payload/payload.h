/*
 *  Rodzhang
 *
 */

#ifndef __PAYLOAD_H__
#define __PAYLOAD_H__



#include <stdint.h>



#define SPATE_PAYLOAD_MAGIC0    's'
#define SPATE_PAYLOAD_MAGIC1    'p'
#define SPATE_PAYLOAD_MAGIC2    't'



typedef struct {

    uint8_t             magic[3];
    uint8_t             flags;

    uint32_t            sess_index;
    uint64_t            tx_cycles;

} spate_payload_t;


static __inline void __spate_payload_set_magic(spate_payload_t *ps)
{
    ps->magic[0] = SPATE_PAYLOAD_MAGIC0;
    ps->magic[1] = SPATE_PAYLOAD_MAGIC1;
    ps->magic[2] = SPATE_PAYLOAD_MAGIC2;
}

static __inline int __spate_payload_is_magic_right(spate_payload_t *ps)
{
    if (ps->magic[0] == SPATE_PAYLOAD_MAGIC0 && 
            ps->magic[1] == SPATE_PAYLOAD_MAGIC1 &&
            ps->magic[2] == SPATE_PAYLOAD_MAGIC2) {

        return 1;
    }

    return 0;
}


#endif /* __PAYLOAD_H__ */
