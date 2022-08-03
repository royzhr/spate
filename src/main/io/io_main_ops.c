/*
 * Rodzhang
 *
 */

#include "io_main_ops.h"
#include "io_main_mgr.h"

static FILE *_io_get_stdout(void)
{
    return s_io_mgr->stdout;
}

static FILE *_io_get_stdin(void)
{
    return s_io_mgr->stdin;
}

static FILE *_io_get_log(void)
{
    return s_io_mgr->log;
}


const io_ops_t c_io_ops = {
    .get_stdout = _io_get_stdout,
    .get_stdin  = _io_get_stdin,
    .get_log    = _io_get_log,
};


