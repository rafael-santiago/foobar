/*
 *                          Copyright (C) 2007, 2016 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 * "main.c" ( Thu 03 May 2007 11:22:18 AM UTC )
 * by Rafael Santiago
 *
 */
#include "foobar.h"
#include "ctx.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define TEMP_ASM ".bftemp_S"
#define TEMP_ASM_O ".bftemp_S.o"

void f_ck_SIGINT_f_ck_callback(int s) {
    f_ck_ctrl_c = 1;
    printf("\n-- f_ck INT sig received! --"); //  INFO(Santiago): baaaad.
}

#ifdef __linux__

static char *ldpath(void) {
    static char *path = NULL;
    /*
     * WARN(Rafael): Feel free to improve it, I will not. ;)
     */
#ifdef __linux__
    path = "/lib/ld-linux.so.2";
#endif
    return path;
}

int mka(const char *outpath, brainf_ck_machine_ctx *f_ck_machine) {
    FILE *f_ck_file;
    char cmdline[255];
    int exit_code = 0;

    f_ck_file = fopen(TEMP_ASM, "wb");

    if (f_ck_file != NULL) {
        asmThisF_ckinCode(f_ck_file, f_ck_machine);
        fclose(f_ck_file);

        sprintf(cmdline, "as %s -o%s", TEMP_ASM, TEMP_ASM_O);

        if (system(cmdline) != 0) {
            printf("ERROR: Link error.\n");
            exit_code = 1;
            goto mka_epilogue;
        }

        sprintf(cmdline, "ld -dynamic-link %s -o%s %s -lc", ldpath(), outpath, TEMP_ASM_O);
        if (system(cmdline) != 0) {
            printf("ERROR: Link error.\n");
            exit_code = 1;
            goto mka_epilogue;
        }
    }

mka_epilogue:
    remove(TEMP_ASM);
    remove(TEMP_ASM_O);

    return exit_code;
}

#endif

int main(int argc, char **argv) {
    int i;
    extern int f_ck_ctrl_c;
    brainf_ck_machine_ctx *f_ck_machine = NULL;
    char *out = NULL;
    if (argc > 1) {
        if (*argv[1] == '-' && *(argv[1]+1) == '-') {
            handleTheF_ckCommandLine(getTheF_ckAsk(argv[1]));
        } else {
            signal(SIGINT, f_ck_SIGINT_f_ck_callback);
            f_ck_ctrl_c = 0;
            f_ck_machine = new_brainf_ck_machine(F_CK_STACK_SIZE);
            if (f_ck_machine == NULL) {
                return 1;
            }
            if (!loadThisF_ckinCode(&f_ck_machine, argv[1])) {
                del_brainf_ck_machine(f_ck_machine);
                return 1;
            }
#ifdef __linux__
            if (argc > 2 && *argv[2] == '-' && *(argv[2]+1) == 'o') {
                if (*(argv[2]+2) != 0) {
                    out = argv[2] + 2;
                } else if (argc > 3) {
                    out = argv[3];
                }
                if (out == NULL) {
                    informthef_ckerror(F_CK_ERROR_NO_OUT);
                    del_brainf_ck_machine(f_ck_machine);
                    return 1;
                }
                i = mka(out, f_ck_machine);
                del_brainf_ck_machine(f_ck_machine);
                return i;
            } else {
#endif
                runThisF_ckinCode(&f_ck_machine);
#ifdef __linux__
            }
#endif

            unloadThisF_ckinCode(&f_ck_machine);
            del_brainf_ck_machine(f_ck_machine);
            return 0;
        }
    } else {
        informthef_ckerror(F_CK_ERROR_DUMB_USER);
    }
    return 0;
}
