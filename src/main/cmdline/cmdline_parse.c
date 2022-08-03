/*
 * Rodzhang
 *
 */

#include "cmdline_parse.h"
#include <unistd.h>




int cmdline_parse_arg(int argc, char **argv, cmdline_args_t *ca)
{
    int             ret;

    memset(ca, 0, sizeof(*ca));

    while ((ret = getopt(argc, argv, "c:m:p:vhsL")) != EOF) {
        switch(ret) {

            /* running mode */
            case 'm':
                ca->mode = optarg;
                break;

            case 'c':
                ca->config_file = optarg;
                break;

            case 'p':
                ca->plane = optarg;
                break;

            case 'h':
                ca->help = 1;
                break;

            case 'v':
                ca->version = 1;
                break;

            case 'L':
                ca->log = 1;
                break;

            case 's':
                ca->show = 1;
                break;

            case '-':
                break;

            default:
                break;
        }
    }

    if (optind >= 0) {
        argv[optind - 1] = argv[0];
    }

    return optind - 1;
}
