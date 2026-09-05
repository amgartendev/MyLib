#include <stdio.h>
#include <stdlib.h>

#include "mylib/vector.h"

int main() {
    Vector_t *vector = vec_init(1);

    vec_push(vector, "Aa");
    vec_push(vector, "Bb");
    vec_push(vector, "Cc");
    vec_push(vector, "Dd");
    vec_push(vector, "Ee");
    vec_push(vector, "Ff");
    vec_push(vector, "Gg");
    vec_insert(vector, "Oo", 1);

    vec_info(vector);
    printf("\n\n");
    vec_output(vector);

    vec_remove(vector, 1);

    vec_info(vector);
    printf("\n\n");
    vec_output(vector);

    vec_clear(vector);

    vec_info(vector);
    printf("\n\n");
    vec_output(vector);

    free(vector);
    return STATUS_SUCCESS;
}
