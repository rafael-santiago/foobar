/*
 *                                Copyright (C) 2016 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#ifndef FOOBAR_TYPES_H
#define FOOBAR_TYPES_H 1

typedef enum _brainf_ck_instructions_t {
    kFckDataAdd,
    kFckDataDec,
    kFckPtrAdd,
    kFckPtrDec,
    kFckReadData,
    kFckWriteData,
    kFckLoop,
    kFckNop
}brainf_ck_instructions_t;

typedef struct _brainf_ck_instructions_ctx {
    int instr;
    struct _brainf_ck_instructions_ctx *sub, *next;
}brainf_ck_instructions_ctx;

typedef struct _brainf_ck_machine_ctx {
    unsigned char *stack, *stack_end;
    unsigned char *sp;
    brainf_ck_instructions_ctx *program;
}brainf_ck_machine_ctx;

#endif
