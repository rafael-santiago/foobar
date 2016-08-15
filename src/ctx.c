/*
 *                                Copyright (C) 2016 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include "ctx.h"
#include "memory.h"
#include <string.h>

typedef struct _brainf_ck_instructions_ctx_ends {
    brainf_ck_instructions_ctx *head, *tail;
}brainf_ck_instructions_ctx_ends;

static brainf_ck_instructions_ctx* new_brainf_ck_instructions_ctx() {
    brainf_ck_instructions_ctx *ctx = (brainf_ck_instructions_ctx *) new_f_ck_segment(sizeof(brainf_ck_instructions_ctx));

    ctx->instr = kFckNop;
    ctx->sub = ctx->next = NULL;

    return ctx;
}

static void add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(brainf_ck_instructions_ctx_ends *list,
                                                                    char instruction) {
    brainf_ck_instructions_ctx *p = new_brainf_ck_instructions_ctx();
    if (list->head == NULL) {
        list->head = p;
    } else {
        list->tail->next = p;
    }
    list->tail = p;
    switch (instruction) {
        case '+':
            p->instr = kFckDataAdd;
            break;

        case '-':
            p->instr = kFckDataDec;
            break;

        case '>':
            p->instr = kFckPtrAdd;
            break;

        case '<':
            p->instr = kFckPtrDec;
            break;

        case ',':
            p->instr = kFckReadData;
            break;

        case '.':
            p->instr = kFckWriteData;
            break;

        case '[':
            p->instr = kFckLoop;
            break;
    }
}

static const char *asm_brainf_ck_subprogram(const char *subprogram, brainf_ck_instructions_ctx **mainsub) {
    const char *p = subprogram;
    brainf_ck_instructions_ctx_ends your_f_ck_substuff = {0};
    if (p == NULL) {
        return NULL;
    }
    while (*p != ']' && *p != 0) {
        switch (*p) {
            case '+':
            case '-':
            case '>':
            case '<':
            case ',':
            case '.':
                add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(&your_f_ck_substuff, *p);
                break;

            case '[':
                add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(&your_f_ck_substuff, *p);
                p = asm_brainf_ck_subprogram(p + 1, &your_f_ck_substuff.tail->sub);
                break;

        }
        p++;
    }
    *mainsub = your_f_ck_substuff.head;
    return p;
}

brainf_ck_instructions_ctx *asm_brainf_ck_program(const char *program) {
    const char *p = program;
    brainf_ck_instructions_ctx_ends your_f_ck_stuff = {0};
    if (p == NULL) {
        return NULL;
    }
    while (*p != 0) {
        switch (*p) {
            case '+':
            case '-':
            case '>':
            case '<':
            case ',':
            case '.':
                add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(&your_f_ck_stuff, *p);
                break;

            case '[':
                add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(&your_f_ck_stuff, *p);
                p = asm_brainf_ck_subprogram(p + 1, &your_f_ck_stuff.tail->sub);
                break;
        }
        p++;
    }
    return your_f_ck_stuff.head;
}

brainf_ck_machine_ctx *new_brainf_ck_machine(size_t max_stack_size) {
    brainf_ck_machine_ctx *f_ck_machine_p = (brainf_ck_machine_ctx *) new_f_ck_segment(sizeof(brainf_ck_machine_ctx));
    f_ck_machine_p->stack = (unsigned char *) new_f_ck_segment(max_stack_size);
    memset(f_ck_machine_p->stack, 0, max_stack_size);
    f_ck_machine_p->stack_end = f_ck_machine_p->stack + max_stack_size;
    f_ck_machine_p->sp = NULL;
    return f_ck_machine_p;
}

void del_brainf_ck_machine(brainf_ck_machine_ctx *machine) {
    free(machine->stack);
    free(machine);
}

void del_brainf_ck_instructions_ctx(brainf_ck_instructions_ctx *instructions) {
    brainf_ck_instructions_ctx *t, *p;
    for (t = p = instructions; t != NULL; t = p->next, p = p->next) {
        if (p->sub != NULL) {
            del_brainf_ck_instructions_ctx(p->sub);
        }
        free(p);
    }
}
