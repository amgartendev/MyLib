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
int vec_get(Vector_t *v, size_t idx, char *out);
size_t vec_size(Vector_t *v);
size_t vec_capacity(Vector_t *v);
int vec_empty(Vector_t *v);
int vec_find(Vector_t *v, char *e);
int vec_push(Vector_t *v, char *e);
int vec_insert(Vector_t *v, char *e, size_t idx);
int vec_pop(Vector_t *v);
int vec_remove(Vector_t *v, size_t idx);
int vec_first(Vector_t *v, char *out);
int vec_last(Vector_t *v, char *out);
int vec_set(Vector_t *v, char *e, size_t idx);
size_t vec_count(Vector_t *v, char *e);
int vec_contains(Vector_t *v, char *e);
int vec_swap(Vector_t *v, size_t idx1, size_t idx2);
int vec_reverse(Vector_t *v);
int vec_shrink_to_fit(Vector_t *v);
int vec_reserve(Vector_t *v, size_t new_capacity);
Vector_t *vec_copy(Vector_t *v);
int vec_clear(Vector_t *v);
int vec_free(Vector_t *v);

#endif
