/*
 *                                Copyright (C) 2007 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 * "foobar.h" ( Thu 03 May 2007 10:24:27 AM UTC )
 * by Rafael Santiago
 *
 */
#ifndef _FOOBAR_H
#define _FOOBAR_H 1

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int f_ck_ctrl_c;

#define F_CK_ERROR_NULL_FILE 0
#define F_CK_ERROR_NO_MEMORY 1
#define F_CK_ERROR_DUMB_USER 2

#define POINTER_SIZE 30000
#define informthef_ckerror(e) (\
 e == F_CK_ERROR_NULL_FILE ? printf("run forest run: arquivo nao esta acessivel!\n") :\
 e == F_CK_ERROR_NO_MEMORY ? printf("run forest run: sem memoria suficiente!\n") :\
 e == F_CK_ERROR_DUMB_USER ? printf("run forest run: use: foobar <brainf_ck file>\n") :\
 printf("run forest run: erro desconhecido!\n") )

#define F_CK_LINUX 0
#define F_CK_WIN32 1

#define F_CK_OSYSTEM F_CK_LINUX

#if F_CK_OSYSTEM == F_CK_LINUX
 #include <termios.h>
 #include <unistd.h>
#else
 #include <conio.h>
#endif

#define F_CK_CODE_RELEASE "## brainf_ckin @ foobar f_ck code release 0.0f_ck1\n"

#define F_CK_CELL_SIZE unsigned char

static char *f_ck_line_options_state[] = {
 "--help",
 "--ascii2dec",
 "--dec2ascii",
 "--asciitable",
 ""
};

#define DO_F_CK_HELP       0
#define DO_F_CK_ASCII2DEC  1
#define DO_F_CK_DEC2ASCII  2
#define DO_F_CK_ASCIITABLE 3
#define WHAT_A_F_CK_IS_IT  4

#define F_CK_HELP_STR "# foobar help\n#\n# rodar codigo brainfuck: foobar <brainf_ck file>\n# para ver o que voce esta vendo: foobar --help\n# conversor ascii para decimal: foobar --ascii2dec\n# conversor decimal para ascii: foobar --dec2ascii\n# exibir toda a tabela ascii: foobar --asciitable\n#\n"

int f_ckTheBrain(F_CK_CELL_SIZE *, FILE *);

void handleTheF_ckCommandLine(int);

int getTheF_ckAsk(char *);

#ifdef __cplusplus
}
#endif


#endif
