#include <stdio.h>
#include <stdlib.h>

#include "test_common.h"
#include "test_vector.h"

int tests_passed = 0;
int tests_failed = 0;


int main(void) {
    run_vector_tests();

    printf("\n==========================\n");
    printf("Tests passed: " GREEN "%d" RESET "\n", tests_passed);
    printf("Tests failed: " RED "%d" RESET "\n", tests_failed);
    printf("==========================\n");

    return tests_failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
