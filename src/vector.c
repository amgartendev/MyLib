#include <stdio.h>
#include <stdlib.h>

#include "mylib/vector.h"

// (PRIVATE)
// Reallocates the memory of a vector if capacity has been reached
// Args:
//     (Vector_t) *v: The vector to be used
// Returns:
//     STATUS_ERROR:  -1
//     STATUS_SUCCESS: 0
static int _vec_alloc(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, "Error: Vector seems to be NULL\n");
        return STATUS_ERROR;
    }

    if (v->size >= v->capacity) {
        size_t new_capacity = v->capacity == 0 ? 1 : v->capacity * 2;

        char *new_data = realloc(v->data, new_capacity * sizeof(*v->data));
        if (new_data == NULL) {
            perror("realloc");
            return STATUS_ERROR;
        }

        v->data = new_data;
        v->capacity = new_capacity;
    }

    return STATUS_SUCCESS;
}

// Displays some useful information of a vector
// Args:
//     (Vector_t) *v: The vector to be used
void vec_info(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, "Error: Vector seems to be NULL\n");
        return;
    }

    printf("\n--- VECTOR ---\n");
    printf("Count:\t\t%zu\n", v->size);
    printf("Capacity:\t%zu\n", v->capacity);
    printf("Size: \t\t%zu Bytes", v->size * sizeof(*v->data));
    return;
}

// Displays all the elements of a vector
// Args:
//     (Vector_t) *v: The vector to be used
void vec_output(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, "Error: Vector seems to be NULL\n");
        return;
    }

    for (size_t i = 0; i < v->size; i++) {
        printf("%c ", v->data[i]);
    }

    return;
}

// Initializes a vector with an initial capacity
// Args:
//     (size_t) initial_capacity: The initial capacity of elements this vector can hold
// Returns:
//     (Vector_t) *v: Allocated memory address of Vector_t size
Vector_t *vec_init(size_t initial_capacity) {
    Vector_t *v = malloc(sizeof(Vector_t));
    if (v == NULL) {
        perror("malloc");
        return NULL;
    }

    initial_capacity = initial_capacity == 0 ? 1 : initial_capacity;

    v->size = 0;
    v->capacity = initial_capacity;

    v->data = malloc(sizeof(*v->data) * initial_capacity);
    if (v->data == NULL) {
        perror("malloc vector->data");
        free(v);
        return NULL;
    }

    return v;
}

// Inserts an element to the end of a vector
// Args:
//     (Vector_t) *v: The vector to be used
//     (char)     *e: The element to be pushed
// Returns:
//     STATUS_ERROR:  -1
//     STATUS_SUCCESS: 0
int vec_push(Vector_t *v, char *e) {
    if (v == NULL) {
        fprintf(stderr, "Error: Vector seems to be NULL\n");
        return STATUS_ERROR;
    }

    if (_vec_alloc(v) == STATUS_ERROR) { return STATUS_ERROR; }

    v->data[v->size] = *e;
    v->size++;

    return STATUS_SUCCESS;
}

// Inserts an element into a vector
// Args:
//     (Vector_t) *v: The vector to be used
//     (char)     *e: The element to be added
//     (size_t)  idx: The index where *e will be inserted on
// Returns:
//     STATUS_ERROR:  -1
//     STATUS_SUCCESS: 0
int vec_insert(Vector_t *v, char *e, size_t idx) {
    if (v == NULL) {
        fprintf(stderr, "Error: Vector seems to be NULL\n");
        return STATUS_ERROR;
    }

    if (idx > v->size) {
        fprintf(stderr, "Error: index out of bounds\n");
        return STATUS_ERROR;
    }

    if (idx == v->size) {
        return vec_push(v, e);
    }

    if (_vec_alloc(v) == STATUS_ERROR) { return STATUS_ERROR; }

    for (size_t i = v->size; i > idx; i--) {
        v->data[i] = v->data[i - 1];
    }

    v->data[idx] = *e;
    v->size++;

    return STATUS_SUCCESS;
}

// Removes the last element from a vector
// Args:
//     (Vector_t) *v: The vector to be used
// Returns:
//     STATUS_ERROR:  -1
//     STATUS_SUCCESS: 0
int vec_pop(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, "Error: Vector seems to be NULL\n");
        return STATUS_ERROR;
    }

    if (v->size == 0) {
        fprintf(stderr, "Error: Vector is empty\n");
        return STATUS_ERROR;
    }

    v->size--;

    return STATUS_SUCCESS;
}

// Removes an element from the vector by its index
// Args:
//     (Vector_t) *v: The vector to be used
//     (size_t)  idx: The index of the element to be removed
// Returns:
//     STATUS_ERROR:  -1
//     STATUS_SUCCESS: 0
int vec_remove(Vector_t *v, size_t idx) {
    if (v == NULL) {
        fprintf(stderr, "Error: Vector seems to be NULL\n");
        return STATUS_ERROR;
    }

    if (idx >= v->size) {
        fprintf(stderr, "Error: index out of bounds\n");
        return STATUS_ERROR;
    }

    if (idx == v->size - 1) {
        return vec_pop(v);
    }

    for (size_t i = idx; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }

    v->size--;

    return STATUS_SUCCESS;
}

// Removes all of the contents of a vector
// Args:
//     (Vector_t) *v: The vector to be used
// Returns:
//     STATUS_ERROR:  -1
//     STATUS_SUCCESS: 0
int vec_clear(Vector_t *v) {
    if (v == NULL || v->data == NULL) {
        fprintf(stderr, "Error: Vector seems to be NULL\n");
        return STATUS_ERROR;
    }

    v->size = 0;

    return STATUS_SUCCESS;
}
