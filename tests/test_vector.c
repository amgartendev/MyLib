#include <stdio.h>
#include <stdlib.h>

#include "mylib/vector.h"

static int tests_passed = 0;
static int tests_failed = 0;


#define YELLOW "\033[33m"
#define GREEN  "\033[32m"
#define RED    "\033[31m"
#define RESET  "\033[0m"

#define TEST(condition, message)                                        \
    do {                                                                \
        if (condition) {                                                \
            printf(GREEN "[PASS]" RESET " %s\n", message);              \
            tests_passed++;                                             \
        } else {                                                        \
            printf(RED "[FAIL]" RESET " %s\n", message);                \
            tests_failed++;                                             \
        }                                                               \
    } while (0);                                                        \

int main(void) {
    printf("\n====== VECTOR ======");

    // -----------------------------------------
    // vec_init
    // -----------------------------------------

    printf(YELLOW "\n--- vec_init ---\n" RESET);

    Vector_t *v = vec_init(2);

    char a = 'A';
    char b = 'B';
    char c = 'C';
    char d = 'D';
    char x = 'X';
    char h = 'H';
    char out = '\0';

    size_t capacity_before_clear;
    size_t old_size;
    size_t old_capacity;
    char old_value;
    int result;

    TEST(v != NULL, "Vector was initialized");
    TEST(v->size == 0, "Initial size is 0");
    TEST(v->capacity == 2, "Initial capacity is 2");
    TEST(v->data != NULL, "Vector data was allocated");

    // -----------------------------------------
    // vec_push
    // -----------------------------------------

    printf(YELLOW "\n--- vec_push ---\n" RESET);

    vec_push(v, &a);
    TEST(v->size == 1, "Push increases size");

    vec_push(v, &b);
    TEST(v->size == 2, "Second push increases size");

    TEST(v->data[0] == 'A', "First element is A");
    TEST(v->data[1] == 'B', "Second element is B");

    // This should trigger realloc because capacity == size
    vec_push(v, &c);

    TEST(v->size == 3, "Push after capacity is reached works");
    TEST(v->capacity == 4, "Capacity doubles from 2 to 4");
    TEST(v->data[2] == 'C', "Third element is C");


    // -----------------------------------------
    // vec_insert
    // -----------------------------------------

    printf(YELLOW "\n--- vec_insert ---\n" RESET);

    // Current vector:
    // A B C
    //
    // Insert X at index 1:
    // A X B C

    result = vec_insert(v, &x, 1);

    TEST(result == STATUS_SUCCESS, "Insert returns STATUS_SUCCESS");
    TEST(v->size == 4, "Insert increases size");
    TEST(v->data[0] == 'A', "Element 0 remains A");
    TEST(v->data[1] == 'X', "Inserted X at index 1");
    TEST(v->data[2] == 'B', "B shifted to index 2");
    TEST(v->data[3] == 'C', "C shifted to index 3");

    // Insert at the end
    vec_insert(v, &d, v->size);

    TEST(v->size == 5, "Insert at end increases size");
    TEST(v->data[4] == 'D', "Insert at end works");


    // -----------------------------------------
    // vec_pop
    // -----------------------------------------

    printf(YELLOW "\n--- vec_pop ---\n" RESET);

    old_size = v->size;

    result = vec_pop(v);

    TEST(result == STATUS_SUCCESS, "Pop returns STATUS_SUCCESS");
    TEST(v->size == old_size - 1, "Pop decreases size");
    TEST(v->data[v->size - 1] == 'C', "Last element after pop is C");


    // -----------------------------------------
    // vec_remove
    // -----------------------------------------

    printf(YELLOW "\n--- vec_remove ---\n" RESET);

    // Current vector:
    // A X B C

    result = vec_remove(v, 1);

    TEST(result == STATUS_SUCCESS, "Remove returns STATUS_SUCCESS");
    TEST(v->size == 3, "Remove decreases size");
    TEST(v->data[0] == 'A', "A remains at index 0");
    TEST(v->data[1] == 'B', "B shifted to index 1");
    TEST(v->data[2] == 'C', "C shifted to index 2");

    // Remove last element
    result = vec_remove(v, 2);

    TEST(result == STATUS_SUCCESS, "Remove last element succeeds");
    TEST(v->size == 2, "Removing last element decreases size");
    TEST(v->data[0] == 'A', "A remains");
    TEST(v->data[1] == 'B', "B remains");


    // -----------------------------------------
    // vec_pop on empty vector
    // -----------------------------------------

    printf(YELLOW "\n--- vec_pop empty vector ---\n" RESET);

    vec_clear(v);

    TEST(v->size == 0, "Vector is empty before empty-pop test");

    result = vec_pop(v);

    TEST(result == STATUS_ERROR, "Pop on empty vector returns STATUS_ERROR");
    TEST(v->size == 0, "Pop on empty vector does not underflow");


    // -----------------------------------------
    // vec_remove out-of-range
    // -----------------------------------------

    printf(YELLOW "\n--- vec_remove out-of-range ---\n" RESET);

    old_size = v->size;

    result = vec_remove(v, 999);

    TEST(result == STATUS_ERROR, "Out-of-range remove returns STATUS_ERROR");
    TEST(v->size == old_size, "Out-of-range remove does not modify size");


    // -----------------------------------------
    // vec_first
    // -----------------------------------------

    printf(YELLOW "\n--- vec_first ---\n" RESET);

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    old_size = v->size;

    result = vec_first(v, &out);

    TEST(result == STATUS_SUCCESS, "First returns STATUS_SUCCESS");
    TEST(out == 'A', "First returns the first element");
    TEST(v->size == old_size, "First does not modify vector size");
    TEST(v->data[0] == 'A' && v->data[1] == 'B' && v->data[2] == 'C', "First does not modify vector contents");


    // -----------------------------------------
    // vec_last
    // -----------------------------------------

    printf(YELLOW "\n--- vec_last ---\n" RESET);

    out = '\0';

    old_size = v->size;

    result = vec_last(v, &out);

    TEST(result == STATUS_SUCCESS, "Last returns STATUS_SUCCESS");
    TEST(out == 'C', "Last returns the last element");
    TEST(v->size == old_size, "Last does not modify vector size");
    TEST(v->data[0] == 'A' && v->data[1] == 'B' && v->data[2] == 'C', "Last does not modify vector contents");


    // -----------------------------------------
    // vec_set
    // -----------------------------------------

    printf(YELLOW "\n--- vec_set ---\n" RESET);

    old_size = v->size;
    old_value = v->data[1];

    result = vec_set(v, &h, 1);

    TEST(result == STATUS_SUCCESS, "Set returns STATUS_SUCCESS");
    TEST(v->data[1] != old_value, "Set replaces the old value");
    TEST(v->data[1] == 'H', "Set successfully replaces the old value");
    TEST(v->size == old_size, "Set does not modify vector size");

    // -----------------------------------------
    // vec_clear
    // -----------------------------------------

    printf(YELLOW "\n--- vec_clear ---\n" RESET);

    capacity_before_clear = v->capacity;

    result = vec_clear(v);

    TEST(result == STATUS_SUCCESS, "Clear returns STATUS_SUCCESS");
    TEST(v->size == 0, "Clear sets size to 0");
    TEST(v->capacity == capacity_before_clear, "Clear preserves capacity");
    TEST(v->data != NULL, "Clear preserves allocated data");


    // -----------------------------------------
    // vec_insert invalid index
    // -----------------------------------------

    printf(YELLOW "\n--- vec_insert invalid index ---\n" RESET);

    result = vec_insert(v, &a, 999);

    TEST(result == STATUS_ERROR, "Insert beyond returns STATUS_ERROR");
    TEST(v->size == 0, "Invalid insert does not modify vector");


    // -----------------------------------------
    // vec_shrink_to_fit
    // -----------------------------------------

    printf(YELLOW "\n--- vec_shrink_to_fit ---\n" RESET);

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    old_capacity = v->capacity;

    result = vec_shrink_to_fit(v);

    TEST(result == STATUS_SUCCESS, "Shrink returns STATUS_SUCCESS")
    TEST(v->capacity != old_capacity, "Shrink is shrinking the vector capacity");

    // -----------------------------------------
    // vec_info / vec_output
    // -----------------------------------------

    printf(YELLOW "\n--- vec_info / vec_output ---\n" RESET);

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    printf("Expected output: A B C\n");
    printf("Actual output: ");
    vec_output(v);
    printf("\n");

    printf("\nVector info:");
    vec_info(v);
    printf("\n");


    // -----------------------------------------
    // Cleanup
    // -----------------------------------------

    free(v->data);
    free(v);


    // -----------------------------------------
    // Results
    // -----------------------------------------

    printf("\n===================\n");
    printf("Tests passed: " GREEN "%d\n" RESET, tests_passed);
    printf("Tests failed: " RED "%d" RESET, tests_failed);
    printf("\n===================\n");

    return tests_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
