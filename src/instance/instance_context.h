/*
 * Rodzhang
 *
 */

#ifndef __INSTANCE_CONTEXT_H__
#define __INSTANCE_CONTEXT_H__


#include <spate_core.h>
#include <spate_pcap.h>
/*
 * Prevent circular dependency, so not used <spate_plane.h>
 */
#include "../plane/plane_context.h"

/*
 * base class of context
 */
typedef struct {

    /*
     * the ctx of plane
     */
    plane_context_t         *plane_ctx;


    uint8_t                 is_master;
    uint8_t                 reserve;

    uint16_t                worker_id;


    /*
     * pcap file 
     */
    pcap_file_t             *pcap_file;

} instance_context_t;


#define INSTANCE_RX_RET_DROP        0
#define INSTANCE_RX_RET_TX          1


extern __thread instance_context_t *g_instance_ctx;


int  instance_context_constructor(instance_context_t *ctx, uint16_t worker_id);
void instance_context_destructor(instance_context_t *ctx);


static inline pcap_file_t *__get_instance_pcap_file(void)
{
    if (!g_instance_ctx) {
        return NULL;
    }

    return g_instance_ctx->pcap_file;
}



#endif /* __INSTANCE_CONTEXT_H__ */
