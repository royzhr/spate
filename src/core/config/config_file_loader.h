/*
 * Rodzhang
 *
 * Config-File Loader
 */

#ifndef __CONFIG_FILE_LOADER_H__
#define __CONFIG_FILE_LOADER_H__


typedef struct {

    void (*cfg_begin)   (void *user_data);

    int  (*cfg_finish)  (void *user_data);

    /*
     * Return Value:
     *  0   : continue
     *  1   : get this config-line(valid cfg)
     *  <0  : error, process it as 0
     *
     */
    int  (*cfg_parse_line)(const char *key, const char *val, void *user_data);

} config_file_loader_ops_t;



int  config_file_load(const char *cfg_file, const config_file_loader_ops_t *loader, void *user_data);


#endif /* __CONFIG_FILE_LOADER_H__ */

