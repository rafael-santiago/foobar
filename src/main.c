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
#include <stdlib.h>
#include <signal.h>

void f_ck_SIGINT_f_ck_callback(int s) {
    f_ck_ctrl_c = 1;
    printf("\n-- f_ck INT sig received! --"); //  INFO(Santiago): baaaad.
}

int main(int argc, char **argv) {
    FILE *f_ck_file;
    int i;
    extern int f_ck_ctrl_c;
    brainf_ck_machine_ctx *f_ck_machine = NULL;
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
            runThisF_ckinCode(&f_ck_machine);
            unloadThisF_ckinCode(&f_ck_machine);
            del_brainf_ck_machine(f_ck_machine);
            return 0;
        }
    } else {
        informthef_ckerror(F_CK_ERROR_DUMB_USER);
    }
    return 0;
}
