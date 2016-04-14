/*
 *                                Copyright (C) 2007 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 * "main.c" ( Thu 03 May 2007 11:22:18 AM UTC )
 * by Rafael Santiago
 *
 */
#include "foobar.h"
#include <stdlib.h>
#include <signal.h>

void f_ck_SIGINT_f_ck_callback(int s) {
    f_ck_ctrl_c = 1;
    printf("\n-- f_ck INT sig received! --"); //  INFO(Santiago): baaaad.
}

int main(int argc, char **argv) {
    FILE *f_ck_file;
    int i;
    F_CK_CELL_SIZE *f_ck_pointer;
    extern int f_ck_ctrl_c;
    if (argc > 1) {
        if (*argv[1] == '-' && *(argv[1]+1) == '-') {
            handleTheF_ckCommandLine(getTheF_ckAsk(argv[1]));
        } else {
            if(!(f_ck_pointer = (F_CK_CELL_SIZE *) malloc(POINTER_SIZE))) {
                informthef_ckerror(F_CK_ERROR_NO_MEMORY);
                return 1;
            }
            signal(SIGINT, f_ck_SIGINT_f_ck_callback);
            f_ck_ctrl_c = 0;
            memset(f_ck_pointer,0,sizeof(F_CK_CELL_SIZE)*POINTER_SIZE);
            f_ck_file = fopen(argv[1], "r");
            f_ckTheBrain(f_ck_pointer, f_ck_file);
            if (f_ck_file != NULL) {
                fclose(f_ck_file);
            }
            free(f_ck_pointer);
        }
    } else {
        informthef_ckerror(F_CK_ERROR_DUMB_USER);
    }
    return 0;
}
