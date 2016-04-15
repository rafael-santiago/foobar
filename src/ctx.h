/*
 *                                Copyright (C) 2016 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#ifndef FOOBAR_CTX_H
#define FOOBAR_CTX_H 1

#include "types.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

brainf_ck_instructions_ctx *asm_brainf_ck_program(const char *program);

brainf_ck_machine_ctx *new_brainf_ck_machine(size_t max_stack_size);

void del_brainf_ck_machine(brainf_ck_machine_ctx *machine);

void del_brainf_ck_instructions_ctx(brainf_ck_instructions_ctx *instructions);

#ifdef __cplusplus
}
#endif

#endif
