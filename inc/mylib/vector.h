#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

#include "mylib/common.h"

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} Vector_t;

Vector_t *vec_init(size_t initial_capacity);
void vec_info(Vector_t *v);
void vec_output(Vector_t *v);
int vec_push(Vector_t *v, char *e);
int vec_insert(Vector_t *v, char *e, size_t idx);
int vec_pop(Vector_t *v);
int vec_remove(Vector_t *v, size_t idx);
int vec_first(Vector_t *v, char *out);
int vec_clear(Vector_t *v);

#endif
