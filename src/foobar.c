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

static F_CK_CELL_SIZE *handleTheF_ckLoop(F_CK_CELL_SIZE *, FILE *, F_CK_CELL_SIZE *,long *);

static void f_ckAscii2F_ckDec(void);

static void f_ckDec2F_ckAscii(void);

static void showTheF_ckAsciiTable(void);

static int checkF_ckBrackets(FILE *);

int f_ckTheBrain(F_CK_CELL_SIZE *f_ck_pointer, FILE *f_ck_file){
    char c;
    long f_ck_offset, f_ck_instructions_counter = 0L;
#if F_CK_OSYSTEM == F_CK_LINUX 
    struct termios f_ck_attr, f_ck_old_attr;
#endif
    F_CK_CELL_SIZE *f_ck_pt_start = f_ck_pointer;
    if (!f_ck_file) {
        informthef_ckerror(F_CK_ERROR_NULL_FILE);
        return 0;
    }
    if (!checkF_ckBrackets(f_ck_file)) {
        return 0;
    }
    printf("*** bof#!@\n");
    c = getc(f_ck_file);
    while (!feof(f_ck_file) && !f_ck_ctrl_c) {

        switch (c) {

            case '+':
                if (*f_ck_pointer < 255) {
                    (*f_ck_pointer)++;
                    f_ck_instructions_counter++;
                }
                break;

            case '-':
                if (*f_ck_pointer > 0) {
                    (*f_ck_pointer)--;
                    f_ck_instructions_counter++;
                }
                break;

            case '>':
                if (f_ck_pointer < f_ck_pt_start + POINTER_SIZE) {
                    f_ck_pointer++;
                }
                f_ck_instructions_counter++;
                break;

            case '<':
                if (f_ck_pointer > f_ck_pt_start) {
                    f_ck_pointer--;
                }
                f_ck_instructions_counter++;
                break;

            case '.':
                printf("%c",*f_ck_pointer);
                f_ck_instructions_counter++;
                break;

            case ',':
#if F_CK_OSYSTEM == F_CK_LINUX
                fflush(stdout);
                tcgetattr(STDIN_FILENO,&f_ck_attr);
                f_ck_old_attr = f_ck_attr;
                f_ck_attr.c_lflag = ~(ICANON);
                tcsetattr(STDIN_FILENO,TCSANOW,&f_ck_attr);
                read(STDIN_FILENO,f_ck_pointer,1);
                tcsetattr(STDIN_FILENO,TCSANOW,&f_ck_old_attr);
#else
                *f_ck_pointer = getch();
                printf("%c",*f_ck_pointer);
#endif
                f_ck_instructions_counter++;
                break;

            case '[':
                f_ck_offset = ftell(f_ck_file);
                f_ck_pointer = handleTheF_ckLoop(f_ck_pointer, f_ck_file, f_ck_pt_start, &f_ck_instructions_counter);
__f_ck_check_pointer:
                if(*f_ck_pointer){
                    fseek(f_ck_file, f_ck_offset, SEEK_SET);
                    f_ck_pointer = handleTheF_ckLoop(f_ck_pointer, f_ck_file, f_ck_pt_start, &f_ck_instructions_counter);
                    if (!f_ck_ctrl_c)
                        goto __f_ck_check_pointer;
                }
;
                f_ck_instructions_counter++;
                break;
        }
        c = getc(f_ck_file);
    }
    printf("\n*** eof#!@\n-- %d f_ckin instructions executed --\n%s", f_ck_instructions_counter, F_CK_CODE_RELEASE);
    fseek(f_ck_file, 0L, SEEK_SET);
    return 1;
}

static F_CK_CELL_SIZE *handleTheF_ckLoop(F_CK_CELL_SIZE *f_ck_pointer, FILE *f_ck_file, F_CK_CELL_SIZE *f_ck_pt_start, long *f_ck_instructions_counter){
    char c;
    long f_ck_offset;
#if F_CK_OSYSTEM == F_CK_LINUX
    struct termios f_ck_attr, f_ck_old_attr;
#endif
    if (!f_ck_file) {
        informthef_ckerror(F_CK_ERROR_NULL_FILE);
        return NULL;
    }
    c = getc(f_ck_file);
    while (!feof(f_ck_file) && !f_ck_ctrl_c) {
        switch (c) {

            case '+':
                if (*f_ck_pointer < 255) {
                    (*f_ck_pointer)++;
                    (*f_ck_instructions_counter)++;
                }
                break;

            case '-':
                if (*f_ck_pointer > 0) {
                    (*f_ck_pointer)--;
                    (*f_ck_instructions_counter)++;
                }
                break;

            case '>':
                if (f_ck_pointer < f_ck_pt_start + POINTER_SIZE) {
                    f_ck_pointer++;
                }
                (*f_ck_instructions_counter)++;
                break;

            case '<':
                if (f_ck_pointer > f_ck_pt_start) {
                    f_ck_pointer--;
                }
                (*f_ck_instructions_counter)++;
                break;

            case '.':
                printf("%c", *f_ck_pointer);
                (*f_ck_instructions_counter)++;
                break;

            case ',':
#if F_CK_OSYSTEM == F_CK_LINUX
                fflush(stdout);
                tcgetattr(STDIN_FILENO, &f_ck_attr);
                f_ck_old_attr = f_ck_attr;
                f_ck_attr.c_lflag = ~(ICANON);
                tcsetattr(STDIN_FILENO, TCSANOW, &f_ck_attr);
                read(STDIN_FILENO, f_ck_pointer, 1);
                tcsetattr(STDIN_FILENO, TCSANOW, &f_ck_old_attr);
#else
                *f_ck_pointer = getch();
                printf("%c", *f_ck_pointer);
#endif
                (*f_ck_instructions_counter)++;
                break;

            case '[':
                f_ck_offset = ftell(f_ck_file);
                f_ck_pointer = handleTheF_ckLoop(f_ck_pointer, f_ck_file, f_ck_pt_start, f_ck_instructions_counter);
__f_ck_while_check_pointer:
                if (f_ck_pointer != NULL && *f_ck_pointer) {
                    fseek(f_ck_file, f_ck_offset, SEEK_SET);
                    f_ck_pointer = handleTheF_ckLoop(f_ck_pointer,f_ck_file,f_ck_pt_start,f_ck_instructions_counter);
                    if (!f_ck_ctrl_c) {
                        goto __f_ck_while_check_pointer;
                    }
                }
;
                (*f_ck_instructions_counter)++;
                break;

            case ']':
                (*f_ck_instructions_counter)++;
                return f_ck_pointer;
                break;

        }
        c = getc(f_ck_file);
    }
    return f_ck_pointer;
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
