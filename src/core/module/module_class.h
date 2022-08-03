/*
 * Rodzhang
 *
 */
 
#ifndef __MODULE_CLASS_H__
#define __MODULE_CLASS_H__


#include <spate_core.h>


typedef struct {
    
    void (*begin)   (void);

    int  (*finish)  (void);

    /*
     * Return Value:
     *  0   : continue
     *  1   : get this config-line(valid cfg)
     *  <0  : error, process it as 0
     *
     */
    int  (*parse_line)(const char *key, const char *val);

} module_cfg_ops_t;


typedef struct {
    
    const char                  *module_name;
    const module_cfg_ops_t      *cfg_ops;

    /*
     * Before Load config init
     */
    int  (*module_init)(void);

    /*
     * After Load config's setting
     */
    int  (*module_setting)(void);

    /*
     * Module exit
     */
    void (*module_exit)(void);
   

} module_class_t;






#endif /* __MODULE_CLASS_H__ */

