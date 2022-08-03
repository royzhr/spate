/*
 * Rodzhang
 *
 */

#include <spate_core.h>
#include <spate_utils.h>
#include "utils_main_module.h"


#include <time.h>


static int _utils_main_module_init(__UNUSED__ int argc, __UNUSED__ char **argv)
{
    random32_init((uint32_t)time(NULL));
    
    return 0;
}

static void _utils_main_module_exit(void)
{

}

const main_module_t c_utils_main_module = {
    .name = "main_utils",
    .init = _utils_main_module_init,
    .exit = _utils_main_module_exit, 
};

