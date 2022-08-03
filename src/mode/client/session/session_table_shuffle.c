/*
 * Rodzhang
 *
 */

#include <spate_utils.h>
#include "session_table_shuffle.h"


/*
 * get random value between in [0, upper_bound)
 */
static inline uint32_t __random_below(uint32_t upper_bound)
{
    uint32_t                r;

    r = random32() % upper_bound;

    return r;
}

static inline void __session_table_swap(session_table_t *tbl, uint32_t a, uint32_t b)
{
    session_engress_t       *engress;
    session_engress_t       tmp;

    engress = tbl->ses;

    memcpy(&tmp, engress+a, sizeof(session_engress_t));

    memcpy(engress+a, engress+b, sizeof(session_engress_t));

    memcpy(engress+b, &tmp, sizeof(session_engress_t));
}

/*
 * Fisher-Yates Shuffle algorithm
 *
 */
void session_table_shuffle(session_table_t *tbl)
{
    uint32_t                nr;
    uint32_t                r;

    nr = tbl->sess_nr - 1;

    for (; nr>0; --nr) {
        r = __random_below(nr);

        __session_table_swap(tbl, r, nr);
    } 

}
