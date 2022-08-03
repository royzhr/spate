/*
 * Rodzhang
 *
 */

#include "main_module.h"
#include "mm/mm_main_module.h"
#include "mgr/mgr_main_module.h"
#include "os/os_main_module.h"
#include "io/io_main_module.h"

#include "cmdline/cmdline_main_module.h"
#include "plane/plane_main_module.h"
#include "early_mode/early_mode_main_module.h"
#include "rt_mode/rt_mode_main_module.h"
#include "utils/utils_main_module.h"


/*
 * Main Modules Table
 *
 * NOTE:
 * The order of the table is very important.
 */
static const main_module_t *c_main_modules[] = {
    &c_mm_main_module,
    &c_cmdline_main_module,
    &c_early_mode_main_module,
    &c_io_main_module,
    &c_mgr_main_module,
    &c_os_main_module,
    &c_plane_main_module,
    &c_utils_main_module,
    &c_rt_mode_main_module,
    NULL,
};

static inline int __main_modules_count(void)
{
    int                     i;
    const main_module_t     *m_module;

    for (i=0; ; ++i) {
        m_module = c_main_modules[i];

        if (!m_module) {
            break;
        }
    }

    return i;
    
}

int  main_module_init(int argc, char **argv)
{
    int                     eat;
    int                     ret, i;
    const main_module_t     *m_module;

    eat = 0;

    for (i=0; ; ++i) {
        m_module = c_main_modules[i];
        if (!m_module) {
            break;
        }

        ret = m_module->init(argc-eat, argv+eat);
        if (ret < 0) {
            return -1;
        }

        eat += ret;
    }

    return eat;
}

void main_module_exit(void)
{
    int                     i;
    const main_module_t     *m_module;

    for (i=__main_modules_count()-1; i>=0; --i) {
        m_module = c_main_modules[i];

        m_module->exit();
    }
}

void main_module_run(void)
{
    int                     i;
    const main_module_t     *m_module;

    for (i=0; ; ++i) {
        m_module = c_main_modules[i];

        if (!m_module) {
            break;
        }

        if (m_module->run) {
            m_module->run();
        }
    }
}

