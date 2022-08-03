/*
 * Rodzhang
 *
 */


#include <spate_core.h>
#include "main_module.h"



int main(int argc, char **argv)
{
	int             ret;

	ret = main_module_init(argc, argv);
	if (ret < 0) {
        return -1;
    }

    main_module_run();

    main_module_exit();

	return 0;

}
