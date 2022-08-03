/*
 * Rodzhang
 *
 */

#include "mm_main_module.h"


static int _mm_main_module_init(__UNUSED__ int argc, __UNUSED__ char **argv)
{
    return 0;
}

static void _mm_main_module_exit(void)
{
}

const main_module_t c_mm_main_module = {
    .name    = "main_mm",
    .init    = _mm_main_module_init,
    .exit    = _mm_main_module_exit,
};


