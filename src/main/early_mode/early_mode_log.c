/*
 *  Rodzhang
 *
 */

#include "early_mode_log.h"
#include <spate_print.h>

static const char *c_spate_log  = "\n"
"                                                                                                                                             \n"
"                          iiiiiiiiiiiiiiiiiiiiiiiftt                                                                                         \n"
"                   iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii1ttttttt                                                                                  \n"
"               iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii1iittttttttttft                                                                             \n"
"            iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii1i1itttttttttttttttttf                                                                          \n"
"         iiiiiiiiiiiiiiiiiiiiiiiiiii1ii11iitttttttttttttttttttttttttf                                                                        \n"
"       iiiiiiiiiiiiiii1i11iii11tttttttttttttttttttttttttttttttttttttttf                                                                      \n"
":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::       11111111111111111111111111                             \n"
":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::      11111111111111111111111111111                           \n"
";;;;;;::::::::;:;;::::::::;:;;:::::::;:;;;::::::;;;;;;::::::;;;;:::::::;;;;;;;;      1111GGGGGGGGGGft[Rod]fffGLt111.                         \n"
"::                                                                           ::      1111GGGGGGGGGttttttttttGGtt1111                         \n"
"::                                                                           ::      1111GGG                Gtttf111;                        \n"
"::                                                                           ::      1111GGG                Gtfff1111                        \n"
"::                                                                           ::      1111GGG                GttfGf1111                       \n"
"::  SSSSSSSSSSS     PPPPPPPPPPP        A    TTTTTTTTTTTTTTT   EEEEEEEEEEEEE  ::      1111GGG                GttGGGt111                       \n"
"::  SS       SS     PP       PP       A A          TT         EE             ::;;;;;;1111GGGtt              G GGGGf1111                      \n"
"::   SS             PP      PP       A   A         TT         EE             ::;;;;;;1111GGtttttt           GGGGGGGt111                      \n"
"::    SSSSSSSS      PP    PPP       AA   AA        TT         EEEEEEEEEEE    ::;;;;;;1111GttttttttfLGG      GGGGGGGL1111                     \n"
"::           SS     PPPPPPP        AAAAAAAAA       TT         EE             ::;;;;;;111111111111111ftttftGGGGGGGGGLt111                     \n"
"::  SS        SS    PP            AA       AA      TT         EE             ::;;;;;;11111iii111t111ttfffGGGGGGGGGGGL111111                  \n"
"::   SS      SSS    PP           AA         AA     TT         EE             ::;;;;;;111111111111111111111111111111111111111111              \n"
"::     SSSSSS       PP          AA           AA    TT         EEEEEEEEEEEEE  ::;;;;;;111111111111111111111111111[Yuhui]11111111111           \n"
"::                                                                           ::;;;;;;1111111111111111111111111111111111111111111111111       \n"
":: _________________________________________________________________________ ::;;;;;;11111111111+----------+11111111111111111111111111111    \n"
"::                                                                           ::;;;;;;11111111111|   Spate  |11111111111111:::::11111111111   \n"
":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;;;;;:11111111111+----------+11111111111111:::::11111111111 ; \n"
"       CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC11111111111111111111111111111111111111111111111111111 ; \n"
"       CCCCCCCCCGGGCGt;;;;;;;;;;;;;;;;;;;;;;;;1fCCCCCCCCCCCCCCCCCCCCCCCCCCCCGGCCCCCCC11111111111111111111111111111111i;:;i1111111111111111 ; \n"
"       CCCCCCC8,,,:,,:,,,,,,,,,,,,,,,,,,,,,,,,,:,,,,:;CCCCCCCCCCCCCCCCCCCCCCCC8888888888888888888888CCLLftf111i;,,,,,,,,,,,,,,,11111111111 ; \n"
"       CCCCG,,.,,fCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCGi:,,,fCCCCCCCCCCCCCCCCCCCCC8888888888888888888888888888888:,,:,8888888888C,,,,,11111111 ; \n"
"       CCC,,,:CCCCGGCGCGCGGCCCCCCCCCCCCCCCCGCCGCGCCGCC;:,,GCCCCCCCCCCCCCCCCCCC88888888888888888888888888888:,:.8888GGCGCGGCC8888:,::11111i : \n"
"       88,,:C88GCGGGGGGGGGGGCG88888888CCGGGGGGGGGGGGC888,,:,888888888888888888888888888888888888888888888L,:,888CCGGGGGGGGGGGCG888:,,8888;,,,\n"
"       0,,,888GGGGGGf1111GGGGGGC88888GCGCGGL1111GGGGGGG80t,,:C888888888888888888888888888888888888888888C,,,88GGGGGGC1111fGGGGCG888,:,888;,,,\n"
"       888888CGGGC11;;;:;11tGGGCG888CGGGG11;;;;:111CGGGC88888888888888888888888888888888888888888888888888888CGGGGt11;:;;;11GGGGC88888888;,,,\n"
"       88888CCGGC1i:1i;:1;:i1GGGC08CCGGG11:11;;11:11GGGC88888888888888888888888888888888888888888888888888888CGGGt1;i1;;i1;;1GGGCC8888888;,,,\n"
"       88888CCGGf1;11:::;1;1iGGG8C8CCGLGi:11;:;:1;1iGGGCC8888888888888888888888888888888888888888888888888888CGGG11;1;:;:i1;1fGGGC8888888;,,:\n"
"            CGGGG11;1;1;ii;iGGGGG   GGGGi1;111;11;1tGGGC                                                     GGGGL1ii1:1;1;11GGGGC           \n"
"             GGGGG111;;;111GGGCL    GCGGGt11;;;i1iGGGGG                                                       GGGGC111;;;111GGGGC            \n"
"              GCGGGGGGLGGGGGGGG      GCCGGGGGLGGGGGGLC                                                         CGGGGGGGLGGGGGGCC             \n"
"                GCCGGGGGGGCCG          CGCGGGGGGCGCGL                                                           tGCGGGGGGGGGCC               \n"
"                   GGGCGCG                1GCCCCG                                                                   GCGGGGt                  \n"
"                                                                                                                                             \n"
"                                                                                                                                             \n"
"\n";


void early_mode_log(void)
{
    __spate_print(c_spate_log);
}
