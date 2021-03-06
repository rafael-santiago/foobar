/*
 *                          Copyright (C) 2007, 2016 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 * "foobar.h" ( Thu 03 May 2007 10:24:27 AM UTC )
 * by Rafael Santiago
 *
 */
#ifndef FOOBAR_FOOBAR_H
#define FOOBAR_FOOBAR_H 1

#include "types.h"
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int f_ck_ctrl_c;

#define F_CK_ERROR_NULL_FILE 0
#define F_CK_ERROR_NO_MEMORY 1
#define F_CK_ERROR_DUMB_USER 2
#define F_CK_ERROR_NO_OUT    3

#define F_CK_STACK_SIZE 300000
#define informthef_ckerror(e) (\
 e == F_CK_ERROR_NULL_FILE ? printf("run forest run: unable to access the file!\n") :\
 e == F_CK_ERROR_NO_MEMORY ? printf("run forest run: no usable memory!\n") :\
 e == F_CK_ERROR_DUMB_USER ? printf("run forest run: use: foobar <brainf_ck file>\n") :\
 e == F_CK_ERROR_NO_OUT    ? printf("run forest run: use: no output file specified.\n") :\
 printf("run forest run: SUPERunKNOWN error!\n") )

int loadThisF_ckinCode(brainf_ck_machine_ctx **machine, const char *filepath);

void unloadThisF_ckinCode(brainf_ck_machine_ctx **machine);

void runThisF_ckinCode(brainf_ck_machine_ctx **machine);

#ifdef __linux__

void asmThisF_ckinCode(FILE *out, brainf_ck_machine_ctx *machine);

#endif

void handleTheF_ckCommandLine(int);

int getTheF_ckAsk(char *);

#ifdef __cplusplus
}
#endif


#endif
