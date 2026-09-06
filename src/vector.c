#include <stdio.h>
#include <stdlib.h>

#include "mylib/vector.h"

#define ERR_VEC_NULL    "Error: vector seems to be NULL\n"
#define ERR_ELEM_NULL   "Error: element seems to be NULL\n"
#define ERR_OUTPUT_NULL "Error: output pointer seems to be NULL\n"
#define ERR_IDX_OFB     "Error: index out of bounds\n"
#define ERR_VEC_EMPTY   "Error: vector is empty\n"


// (PRIVATE)
// Ensures that the vector has enough capacity to store one more element.
//
// If the vector has reached its current capacity, its allocated memory
// is expanded by doubling the capacity.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//
// Returns:
//     STATUS_SUCCESS: The vector has enough capacity for another element
//     STATUS_ERROR:   The vector is NULL or memory reallocation failed
static int _vec_alloc(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
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

// Displays information about a vector.
//
// Prints the number of stored elements, the current capacity,
// and the amount of memory currently used by the elements.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
void vec_info(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return;
    }

    printf("\n--- VECTOR ---\n");
    printf("Count:\t\t%zu\n", v->size);
    printf("Capacity:\t%zu\n", v->capacity);
    printf("Size: \t\t%zu Bytes", v->size * sizeof(*v->data));
    return;
}

// Displays all elements stored in a vector.
//
// Elements are printed in order from the first to the last.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
void vec_output(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return;
    }

    for (size_t i = 0; i < v->size; i++) {
        printf("%c ", v->data[i]);
    }

    return;
}

// Creates and initializes a new vector.
//
// If initial_capacity is 0, the vector is initialized with a
// minimum capacity of 1.
//
// Args:
//     (size_t) initial_capacity: Initial number of elements the vector
//                                can store without reallocation
//
// Returns:
//     A pointer to the newly allocated vector on success.
//     NULL if memory allocation fails.
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

// Retrieves an element from a vector at a specified index.
//
// The retrieved element is stored at the memory location pointed
// to by out. The vector itself is not modified.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//     (size_t)   idx: Index of the element to retrive
//     (char *)   out: Pointer where the retrieved element will be stored
//
// Returns:
//    STATUS_SUCCESS: The element was successfully retrieved
//    STATUS_ERROR:   The vector or output pointer is NULL,
//                    the vector is empty, or the index is out of bounds
int vec_get(Vector_t *v, size_t idx, char *out) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (out == NULL) {
        fprintf(stderr, ERR_OUTPUT_NULL);
        return STATUS_ERROR;
    }

    if (v->size == 0) {
        fprintf(stderr, ERR_VEC_EMPTY);
        return STATUS_ERROR;
    }

    if (idx >= v->size) {
        fprintf(stderr, ERR_IDX_OFB);
        return STATUS_ERROR;
    }

    *out = v->data[idx];

    return STATUS_SUCCESS;
}

// Returns the current size of a vector.
//
// The size represents the number of elements currently stored
// in the vector.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//
// Returns:
//     The current number of elements stored in the vector.
//     0 if the vector is NULL or empty.
size_t vec_size(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return 0;
    }

    return v->size;
}

// Returns the current capacity of a vector.
//
// The capacity represents the number of elements the vector can
// store without requiring additional memory allocation.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//
// Returns:
//     The current capacity of the vector.
//     0 if the vector is NULL.
size_t vec_capacity(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return 0;
    }

    return v->capacity;
}

// Searches for the first occurrence of an element in a vector.
//
// The vector is searched from the first element to the last.
// If the element is found, the index of its first occurrence is returned.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//     (char *)     e: Pointer to the element to find
//
// Returns:
//     >= 0:             Index of the first occurrence of the element
//     STATUS_NOT_FOUND: The element was not found
//     STATUS_ERROR:     The vector or element pointer is NULL
int vec_find(Vector_t *v, char *e) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (e == NULL) {
        fprintf(stderr, ERR_ELEM_NULL);
        return STATUS_ERROR;
    }

    for (size_t i = 0; i < v->size; i++) {
        if (v->data[i] == *e) {
            return (int)i;
        }
    }

    return STATUS_NOT_FOUND;
}

// Appends an element to the end of a vector.
//
// The vector capacity is automatically increased if necessary.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//     (char *)     e: Pointer to the element to append
//
// Returns:
//     STATUS_SUCCESS: The element was successfully appended
//     STATUS_ERROR:   The vector or element pointer is NULL
//                     or memory allocation failed
int vec_push(Vector_t *v, char *e) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (e == NULL) {
        fprintf(stderr, ERR_ELEM_NULL);
        return STATUS_ERROR;
    }

    if (_vec_alloc(v) == STATUS_ERROR) { return STATUS_ERROR; }

    v->data[v->size] = *e;
    v->size++;

    return STATUS_SUCCESS;
}

// Inserts an element at a specified index.
//
// Existing elements at and after the specified index are shifted
// one position to the right. If idx is equal to the vector size,
// the element is appended to the end.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//     (char *)     e: Pointer to the element to insert
//     (size_t)   idx: Index where the element will be inserted
//
// Returns:
//     STATUS_SUCCESS: The element was successfully inserted
//     STATUS_ERROR:   An argument is invalid, the index is out of bounds,
//                     or memory allocation failed
int vec_insert(Vector_t *v, char *e, size_t idx) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (e == NULL) {
        fprintf(stderr, ERR_ELEM_NULL);
        return STATUS_ERROR;
    }

    if (idx > v->size) {
        fprintf(stderr, ERR_IDX_OFB);
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

// Removes the last element from a vector.
//
// The vector size is decreased by one, but its allocated capacity
// remains unchanged.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//
// Returns:
//     STATUS_SUCCESS: The last element was successfully removed
//     STATUS_ERROR:   The vector is NULL or empty
int vec_pop(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (v->size == 0) {
        fprintf(stderr, ERR_VEC_EMPTY);
        return STATUS_ERROR;
    }

    v->size--;

    return STATUS_SUCCESS;
}

// Removes the element at a specified index.
//
// Elements after the removed element are shifted one position
// to the left. The vector capacity remains unchanged.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//     (size_t)   idx: Index of the element to remove
//
// Returns:
//     STATUS_SUCCESS: The element was successfully removed
//     STATUS_ERROR:   The vector is NULL or the index is out of bounds
int vec_remove(Vector_t *v, size_t idx) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (idx >= v->size) {
        fprintf(stderr, ERR_IDX_OFB);
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

// Retrieves the first element of a vector.
//
// The retrieved element is stored at the memory location pointed
// to by out. The vector itself is not modified.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//     (char *)   out: Pointer where the retrieved element will be stored
//
// Returns:
//     STATUS_SUCCESS: The first element was successfully retrieved
//     STATUS_ERROR:   The vector or output pointer is NULL,
//                     or the vector is empty
int vec_first(Vector_t *v, char *out) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (out == NULL) {
        fprintf(stderr, ERR_OUTPUT_NULL);
        return STATUS_ERROR;
    }

    if (v->size == 0) {
        fprintf(stderr, ERR_VEC_EMPTY);
        return STATUS_ERROR;
    }

    *out = v->data[0];

    return STATUS_SUCCESS;
}

// Retrieves the last element of a vector.
//
// The retrieved element is stored at the memory location pointed
// to by out. The vector itself is not modified.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//     (char *)   out: Pointer where the retrieved element will be stored
//
// Returns:
//     STATUS_SUCCESS: The last element was successfully retrieved
//     STATUS_ERROR:   The vector or output pointer is NULL,
//                     or the vector is empty
int vec_last(Vector_t *v, char *out) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (out == NULL) {
        fprintf(stderr, ERR_OUTPUT_NULL);
        return STATUS_ERROR;
    }

    if (v->size == 0) {
        fprintf(stderr, ERR_VEC_EMPTY);
        return STATUS_ERROR;
    }

    *out = v->data[v->size - 1];

    return STATUS_SUCCESS;
}

// Replaces the element at a specified index.
//
// The existing element is replaced by the provided element.
// The vector size and capacity remain unchanged.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//     (char *)     e: Pointer to the new element
//     (size_t)   idx: Index of the element to replace
//
// Returns:
//    STATUS_SUCCESS: The element was successfully replaced
//    STATUS_ERROR:   The vector or element pointer is NULL,
//                    the vector is empty, or the index is out of bounds
int vec_set(Vector_t *v, char *e, size_t idx) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (e == NULL) {
        fprintf(stderr, ERR_ELEM_NULL);
        return STATUS_ERROR;
    }

    if (v->size == 0) {
        fprintf(stderr, ERR_VEC_EMPTY);
        return STATUS_ERROR;
    }

    if (idx >= v->size) {
        fprintf(stderr, ERR_IDX_OFB);
        return STATUS_ERROR;
    }

    v->data[idx] = *e;

    return STATUS_SUCCESS;
}

// Reduces the reserved memory of a vector to fit its current number of elements.
//
// The vector capacity is reduced to match its currently size.
// If the vector is empty, a minimum capacity of 1 is preserved.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//
// Returns:
//     STATUS_SUCCESS: The vector capacity was successfully reduced
//     STATUS_ERROR: The vector is NULL or memory reallocation failed
int vec_shrink_to_fit(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    if (v->size == 0) {
        char *new_data = realloc(v->data, sizeof(*v->data));
        if (new_data == NULL) {
            perror("realloc");
            return STATUS_ERROR;
        }

        v->data = new_data;
        v->capacity = 1;

        return STATUS_SUCCESS;
    }

    char *new_data = realloc(v->data, v->size * sizeof(*v->data));
    if (new_data == NULL) {
        perror("realloc");
        return STATUS_ERROR;
    }

    v->data = new_data;
    v->capacity = v->size;

    return STATUS_SUCCESS;
}

// Removes all elements from a vector.
//
// The vector size is reset to 0, but its allocated capacity is
// preserved so that the memory can be reused by future insertions.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//
// Returns:
//     STATUS_SUCCESS: The vector was successfully cleared
//     STATUS_ERROR:   The vector or its data pointer is NULL
int vec_clear(Vector_t *v) {
    if (v == NULL || v->data == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    v->size = 0;

    return STATUS_SUCCESS;
}

// Frees all memory allocated by a vector.
//
// The vector's data buffer is released first, followed by the
// vector structure itself. The vector must not be used after this call.
//
// Args:
//     (Vector_t *) v: Pointer to the vector
//
// Returns:
//     STATUS_SUCCESS: The vector was successfully freed
//     STATUS_ERROR:   The vector is NULL
int vec_free(Vector_t *v) {
    if (v == NULL) {
        fprintf(stderr, ERR_VEC_NULL);
        return STATUS_ERROR;
    }

    free(v->data);
    free(v);

    return STATUS_SUCCESS;
}
