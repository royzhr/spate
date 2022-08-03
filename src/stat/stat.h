/*
 * Rodzhang
 *
 */

#ifndef __STAT_H__
#define __STAT_H__


#include <spate_core.h>
#include <spate_module.h>
#include "stat_cfg.h"


struct _stat_s;


typedef struct {

    void (*begin)   (struct _stat_s *my);

    int  (*finish)  (struct _stat_s *my);

    int  (*parse_line)(struct _stat_s *my, const char *key, const char *val);

} stat_cfg_ops_t;


typedef struct {

    const char      *uri;

    char            *buf;
    int             buf_len;
    int             buf_size;

} stat_cmd_t;

typedef struct {

    int  (*setting)  (struct _stat_s *my);
    void (*on_tick)  (struct _stat_s *my);
    int  (*on_flush) (struct _stat_s *my);
    /*
     * 此返回值需要服从 http module handler 的约束
     */
    int  (*on_cmd)   (struct _stat_s *my, stat_cmd_t *cmd);
    void (*destroy)  (struct _stat_s *my);

    const stat_cfg_ops_t    *stat_cfg_ops;

} stat_vtbl_t;


/*
 * Base Class of stat
 */
typedef struct _stat_s {


    const stat_vtbl_t   *vptr;

    stat_cfg_t          cfg;

} stat_t;






#endif /* __STAT_H__ */

