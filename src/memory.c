/*
 *                                Copyright (C) 2016 by Rafael Santiago
 *
 * This is a free software. You can redistribute it and/or modify under
 * the terms of the GNU General Public License version 2.
 *
 */
#include "memory.h"
#include <stdio.h>

void *new_f_ck_segment(size_t s) {
    void *p = malloc(s);
    if (p == NULL) {
        printf("no memory!\n");
        exit(1);
    }
    return p;
}
