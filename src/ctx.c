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

#define new_brainf_ck_instructions_ctx(m) ( (m) = (brainf_ck_instructions_ctx *) new_f_ck_segment(sizeof(brainf_ck_instructions_ctx)), (m)->instr = kFckNop,\
                                            (m)->sub = (m)->next = NULL )

static brainf_ck_instructions_ctx *get_brainf_ck_instructions_ctx_tail(brainf_ck_instructions_ctx *instructions) {
    brainf_ck_instructions_ctx *ip;
    for (ip = instructions; ip->next != NULL; ip = ip->next);
    return ip;
}

static brainf_ck_instructions_ctx *add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(brainf_ck_instructions_ctx *ip,
                                                                                           char instruction) {
    brainf_ck_instructions_ctx *head = ip, *p = NULL;
    if (head == NULL) {
        new_brainf_ck_instructions_ctx(head);
        p = head;
    } else {
        p = get_brainf_ck_instructions_ctx_tail(head);
        new_brainf_ck_instructions_ctx(p->next);
        p = p->next;
    }
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
    return head;
}

static const char *asm_brainf_ck_subprogram(const char *subprogram, brainf_ck_instructions_ctx **mainsub) {
    const char *p = subprogram;
    brainf_ck_instructions_ctx *your_f_ck_substuff = NULL, *f_ck_current = NULL;
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
                your_f_ck_substuff = add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(your_f_ck_substuff, *p);
                break;

            case '[':
                your_f_ck_substuff = add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(your_f_ck_substuff, *p);
                f_ck_current = get_brainf_ck_instructions_ctx_tail(your_f_ck_substuff);
                p = asm_brainf_ck_subprogram(p + 1, &f_ck_current->sub);
                break;

        }
        p++;
    }
    *mainsub = your_f_ck_substuff;
    return p;
}

brainf_ck_instructions_ctx *asm_brainf_ck_program(const char *program) {
    const char *p = program;
    brainf_ck_instructions_ctx *your_f_ck_stuff = NULL, *f_ck_current = NULL;
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
                your_f_ck_stuff = add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(your_f_ck_stuff, *p);
                break;

            case '[':
                your_f_ck_stuff = add_brainf_ck_instruction_to_brainf_ck_instructions_ctx(your_f_ck_stuff, *p);
                f_ck_current = get_brainf_ck_instructions_ctx_tail(your_f_ck_stuff);
                p = asm_brainf_ck_subprogram(p + 1, &f_ck_current->sub);
                break;
        }
        p++;
    }
    return your_f_ck_stuff;
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
