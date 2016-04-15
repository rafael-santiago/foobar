/*
 *                                Copyright (C) 2007 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 * "foobar.c" ( Thu 03 May 2007 10:29:07 AM UTC )
 * by Rafael Santiago
 */
#include "foobar.h"
#include "ctx.h"
#include <string.h>
#include <stdlib.h>

#define F_CK_LINUX 1
#define F_CK_WIN32 2

#if F_CK_OSYSTEM == F_CK_LINUX
 #include <termios.h>
 #include <unistd.h>
#else
 #include <conio.h>
#endif

#define F_CK_CODE_RELEASE "## brainf_ckin @ foobar f_ck code release 0.0f_ck1\n"

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

#define F_CK_HELP_STR "# foobar help\n#\n# run brainfuck code: foobar <brainf_ck file>\n# see what you are seeing: foobar --help\n# ascii to decimal conversor: foobar --ascii2dec\n# decimal to ascii conversor: foobar --dec2ascii\n# show the entire ASCII table: foobar --asciitable\n#\n"

static void f_ckAscii2F_ckDec(void);

static void f_ckDec2F_ckAscii(void);

static void showTheF_ckAsciiTable(void);

static int checkF_ckBrackets(FILE *);

int loadThisF_ckinCode(brainf_ck_machine_ctx **machine, const char *filepath) {
    FILE *input = NULL;
    char *code = NULL;
    long code_size = 0;
    input = fopen(filepath, "rb");
    if (input != NULL) {
        if (! checkF_ckBrackets(input)) {
            fclose(input);
            return 0;
        }
    }
    fseek(input, 0L, SEEK_END);
    code_size = ftell(input);
    fseek(input, 0L, SEEK_SET);
    code = (char *) malloc(code_size + 1);
    memset(code, 0, code_size + 1);
    fread(code, 1, code_size, input);
    fclose(input);
    (*machine)->program = asm_brainf_ck_program(code);
    return ((*machine)->program != NULL);
}

void unloadThisF_ckinCode(brainf_ck_machine_ctx **machine) {
    del_brainf_ck_instructions_ctx((*machine)->program);
    (*machine)->program = NULL;
    (*machine)->sp = NULL;
}

void print_stack(brainf_ck_machine_ctx **machine) {
    unsigned char *sp = NULL;
    for (sp = (*machine)->stack; sp != (*machine)->stack_end; sp++) {
        printf("%d ", *sp);
    }
    printf("\n");
}

void runThisF_ckinCode(brainf_ck_machine_ctx **machine) {
    brainf_ck_instructions_ctx *p = NULL, *old_f_ck_tape = NULL;
#if F_CK_OSYSTEM == F_CK_LINUX
    struct termios f_ck_attr, f_ck_old_attr;
#endif
    if (machine == NULL || (*machine)->program == NULL) {
        return;
    }
    if ((*machine)->sp == NULL) {
        (*machine)->sp = (*machine)->stack;
    }
    for (p = (*machine)->program; p != NULL && !f_ck_ctrl_c; p = p->next) {
        switch (p->instr) {

            case kFckDataAdd:
                (*(*machine)->sp)++;
                break;

            case kFckDataDec:
                (*(*machine)->sp)--;
                break;

            case kFckPtrAdd:
                if ((*machine)->sp < (*machine)->stack_end) {
                    (*machine)->sp++;
                }
                break;

            case kFckPtrDec:
                if ((*machine)->sp > (*machine)->stack) {
                    (*machine)->sp--;
                }
                break;

            case kFckWriteData:
                printf("%c", *(*machine)->sp);
                break;

            case kFckReadData:
#if F_CK_OSYSTEM == F_CK_LINUX
                fflush(stdout);
                tcgetattr(STDIN_FILENO, &f_ck_attr);
                f_ck_old_attr = f_ck_attr;
                f_ck_attr.c_lflag = ~(ICANON);
                tcsetattr(STDIN_FILENO,TCSANOW, &f_ck_attr);
                read(STDIN_FILENO, (*machine)->sp, 1);
                tcsetattr(STDIN_FILENO, TCSANOW, &f_ck_old_attr);
#else
                *f_ck_pointer = getch();
                printf("%c",*(*machine)->sp);
#endif
                break;

            case kFckLoop:
                old_f_ck_tape = (*machine)->program;
                (*machine)->program = p->sub;
                while (*(*machine)->sp > 0 && !f_ck_ctrl_c) {
                    runThisF_ckinCode(machine);
                }
                (*machine)->program = old_f_ck_tape;
                break;

        }
    }
}

void handleTheF_ckCommandLine(int cmdno){
    switch (cmdno) {

        case DO_F_CK_HELP:
            printf("%s",F_CK_HELP_STR);
            break;

        case DO_F_CK_ASCII2DEC:
            f_ckAscii2F_ckDec();
            break;

        case DO_F_CK_DEC2ASCII:
            f_ckDec2F_ckAscii();
            break;

        case DO_F_CK_ASCIITABLE:
            showTheF_ckAsciiTable();
            break;

        case WHAT_A_F_CK_IS_IT:
            printf("run forest run: use: foobar --help\n");
            break;

    }
}

int getTheF_ckAsk(char *ask) {
    int w;
    for (w = 0; f_ck_line_options_state[w][0]; w++) {
        if(strcmp(ask, f_ck_line_options_state[w]) == 0) {
            return w;
        }
    }
    return w;
}

static void f_ckAscii2F_ckDec() {
    unsigned char c;
    printf("ascii: ");
#if F_CK_OSYSTEM == F_CK_LINUX
    struct termios f_ck_attr, f_ck_old_attr;

    fflush(stdout);
    tcgetattr(STDIN_FILENO, &f_ck_attr);
    f_ck_old_attr = f_ck_attr;
    f_ck_attr.c_lflag = ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &f_ck_attr);
    read(STDIN_FILENO, &c, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &f_ck_old_attr);
    printf("\n");
#else
    c = getch();
    printf("%c\n", c);
#endif
    printf("ascii2dec = %d\n", c);
}

static void f_ckDec2F_ckAscii() {
    unsigned char c[100];
    printf("dec: ");
#if F_CK_OSYSTEM == F_CK_LINUX
    fflush(stdout);
    read(STDIN_FILENO,c,100);
#else
    gets(c);
#endif
    printf("dec2ascii = '%c'\n", atoi(c));
}

static void showTheF_ckAsciiTable() {
    unsigned char w;
    for(w = 0; w < 255; w++) {
        printf("%2d \t=\t %c\n", w, w);
    }
}

static int checkF_ckBrackets(FILE *f_ck_file) {
    char c;
    int hooks = 0;

    c = getc(f_ck_file);
    while (!feof(f_ck_file)) {
        switch (c) {
            case '[': hooks++; break;
            case ']': hooks--; break;
        }
        c = getc(f_ck_file);
    }

    fseek(f_ck_file, 0L, SEEK_SET);

    if (hooks > 0) {
        printf("run forest run: parse: the file has %d unterminated ['s.\n", hooks);
        return 0;
    } else if (hooks < 0) {
        printf("run forest run: parse: the file has %d unterminated ]'s\n", abs(hooks));
        return 0;
    }

    return 1;
}
