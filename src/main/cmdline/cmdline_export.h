/*
 * Rodzhang
 *
 */

#ifndef __CMDLINE_EXPORT_H__
#define __CMDLINE_EXPORT_H__


#include <spate_core.h>


typedef struct {


    spate_mode_e    mode;


    const char      *config_file;
    const char      *plane_name;


} cmdline_export_t;


extern cmdline_export_t *g_cmdline;


#endif /* __CMDLINE_EXPORT_H__ */
