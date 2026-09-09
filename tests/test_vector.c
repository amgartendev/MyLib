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
    } while (0)


// ------------------------------------------------------------
// Helpers
// ------------------------------------------------------------

static int vec_value_equals(Vector_t *v, size_t idx, char expected) {
    char out;

    if (vec_get(v, idx, &out) == STATUS_ERROR) { return 0; }

    return out == expected;
}


// ------------------------------------------------------------
// vec_init
// ------------------------------------------------------------

static void test_vec_init(void) {
    printf(YELLOW "\n--- vec_init ---\n" RESET);

    Vector_t *v = vec_init(2);

    TEST(v != NULL, "Vector was initialized");
    TEST(vec_size(v) == 0, "Initial size is 0");
    TEST(vec_capacity(v) == 2, "Initial capacity is 2");

    vec_free(v);


    v = vec_init(0);

    TEST(v != NULL, "Vector with capacity 0 was initialized");
    TEST(vec_size(v) == 0, "Initial size remains 0");
    TEST(vec_capacity(v) == 1, "Capacity 0 is normalized to 1");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_push
// ------------------------------------------------------------

static void test_vec_push(void) {
    printf(YELLOW "\n--- vec_push ---\n" RESET);

    Vector_t *v = vec_init(3);

    char a = 'A';
    char b = 'B';
    char c = 'C';
    char d = 'D';

    TEST(vec_push(v, &a) == STATUS_SUCCESS,
         "Push A returns STATUS_SUCCESS");

    TEST(vec_push(v, &b) == STATUS_SUCCESS,
         "Push B returns STATUS_SUCCESS");

    TEST(vec_push(v, &c) == STATUS_SUCCESS,
         "Push C returns STATUS_SUCCESS");

    TEST(vec_size(v) == 3, "Size is 3");
    TEST(vec_capacity(v) == 3, "Capacity is 3");

    TEST(vec_value_equals(v, 0, 'A'), "First element is A");
    TEST(vec_value_equals(v, 1, 'B'), "Second element is B");
    TEST(vec_value_equals(v, 2, 'C'), "Third element is C");

    TEST(vec_push(v, &d) == STATUS_SUCCESS,
         "Push D returns STATUS_SUCCESS");

    TEST(vec_size(v) == 4, "Size is 4 after fourth push");
    TEST(vec_capacity(v) == 6, "Capacity doubles from 3 to 6");

    TEST(vec_value_equals(v, 3, 'D'), "Fourth element is D");

    TEST(vec_push(NULL, &a) == STATUS_ERROR,
         "Push on NULL vector returns STATUS_ERROR");

    TEST(vec_push(v, NULL) == STATUS_ERROR,
         "Push with NULL element returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_insert
// ------------------------------------------------------------

static void test_vec_insert(void) {
    printf(YELLOW "\n--- vec_insert ---\n" RESET);

    Vector_t *v = vec_init(3);

    char a = 'A';
    char b = 'B';
    char c = 'C';
    char x = 'X';
    char y = 'Y';
    char d = 'D';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    TEST(vec_insert(v, &x, 1) == STATUS_SUCCESS,
         "Insert in middle returns STATUS_SUCCESS");

    TEST(vec_size(v) == 4, "Insert in middle increases size");

    TEST(vec_value_equals(v, 0, 'A'), "A remains at index 0");
    TEST(vec_value_equals(v, 1, 'X'), "X inserted at index 1");
    TEST(vec_value_equals(v, 2, 'B'), "B shifted to index 2");
    TEST(vec_value_equals(v, 3, 'C'), "C shifted to index 3");

    TEST(vec_insert(v, &y, 0) == STATUS_SUCCESS,
         "Insert at beginning returns STATUS_SUCCESS");

    TEST(vec_size(v) == 5, "Insert at beginning increases size");

    TEST(vec_value_equals(v, 0, 'Y'), "Y inserted at index 0");
    TEST(vec_value_equals(v, 1, 'A'), "A shifted to index 1");

    TEST(vec_insert(v, &d, vec_size(v)) == STATUS_SUCCESS,
         "Insert at end returns STATUS_SUCCESS");

    TEST(vec_size(v) == 6, "Insert at end increases size");
    TEST(vec_value_equals(v, 5, 'D'), "D inserted at end");

    size_t old_size = vec_size(v);

    TEST(vec_insert(v, &a, 999) == STATUS_ERROR,
         "Insert out of bounds returns STATUS_ERROR");

    TEST(vec_size(v) == old_size,
         "Invalid insert does not modify size");

    TEST(vec_insert(NULL, &a, 0) == STATUS_ERROR,
         "Insert on NULL vector returns STATUS_ERROR");

    TEST(vec_insert(v, NULL, 0) == STATUS_ERROR,
         "Insert with NULL element returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_pop
// ------------------------------------------------------------

static void test_vec_pop(void) {
    printf(YELLOW "\n--- vec_pop ---\n" RESET);

    Vector_t *v = vec_init(2);

    char a = 'A';
    char b = 'B';

    vec_push(v, &a);
    vec_push(v, &b);

    size_t old_capacity = vec_capacity(v);

    TEST(vec_pop(v) == STATUS_SUCCESS,
         "Pop returns STATUS_SUCCESS");

    TEST(vec_size(v) == 1, "Pop decreases size");
    TEST(vec_capacity(v) == old_capacity,
         "Pop preserves capacity");

    TEST(vec_value_equals(v, 0, 'A'),
         "A remains after popping B");

    TEST(vec_pop(v) == STATUS_SUCCESS,
         "Pop last remaining element succeeds");

    TEST(vec_size(v) == 0, "Vector is empty after second pop");

    TEST(vec_pop(v) == STATUS_ERROR,
         "Pop on empty vector returns STATUS_ERROR");

    TEST(vec_size(v) == 0,
         "Pop on empty vector does not underflow");

    TEST(vec_pop(NULL) == STATUS_ERROR,
         "Pop on NULL vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_remove
// ------------------------------------------------------------

static void test_vec_remove(void) {
    printf(YELLOW "\n--- vec_remove ---\n" RESET);

    Vector_t *v = vec_init(4);

    char a = 'A';
    char b = 'B';
    char c = 'C';
    char d = 'D';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);
    vec_push(v, &d);

    TEST(vec_remove(v, 1) == STATUS_SUCCESS,
         "Remove middle element returns STATUS_SUCCESS");

    TEST(vec_size(v) == 3, "Remove decreases size");

    TEST(vec_value_equals(v, 0, 'A'), "A remains at index 0");
    TEST(vec_value_equals(v, 1, 'C'), "C shifted to index 1");
    TEST(vec_value_equals(v, 2, 'D'), "D shifted to index 2");

    TEST(vec_remove(v, 2) == STATUS_SUCCESS,
         "Remove last element returns STATUS_SUCCESS");

    TEST(vec_size(v) == 2,
         "Removing last element decreases size");

    size_t old_size = vec_size(v);

    TEST(vec_remove(v, 999) == STATUS_ERROR,
         "Out-of-range remove returns STATUS_ERROR");

    TEST(vec_size(v) == old_size,
         "Out-of-range remove preserves size");

    TEST(vec_remove(NULL, 0) == STATUS_ERROR,
         "Remove on NULL vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_get
// ------------------------------------------------------------

static void test_vec_get(void) {
    printf(YELLOW "\n--- vec_get ---\n" RESET);

    Vector_t *v = vec_init(2);

    char a = 'A';
    char out = '\0';

    vec_push(v, &a);

    TEST(vec_get(v, 0, &out) == STATUS_SUCCESS,
         "Get valid index returns STATUS_SUCCESS");

    TEST(out == 'A', "Get retrieves correct element");

    TEST(vec_get(v, 1, &out) == STATUS_ERROR,
         "Get out of bounds returns STATUS_ERROR");

    TEST(vec_get(v, 0, NULL) == STATUS_ERROR,
         "Get with NULL output returns STATUS_ERROR");

    TEST(vec_get(NULL, 0, &out) == STATUS_ERROR,
         "Get on NULL vector returns STATUS_ERROR");

    vec_clear(v);

    TEST(vec_get(v, 0, &out) == STATUS_ERROR,
         "Get on empty vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_size
// ------------------------------------------------------------

static void test_vec_size(void) {
    printf(YELLOW "\n--- vec_size ---\n" RESET);

    Vector_t *v = vec_init(2);

    char a = 'A';
    char b = 'B';

    TEST(vec_size(v) == 0, "Empty vector size is 0");

    vec_push(v, &a);

    TEST(vec_size(v) == 1, "Size is 1 after one push");

    vec_push(v, &b);

    TEST(vec_size(v) == 2, "Size is 2 after two pushes");

    vec_pop(v);

    TEST(vec_size(v) == 1, "Size decreases after pop");

    TEST(vec_size(NULL) == 0,
         "Size of NULL vector returns 0");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_capacity
// ------------------------------------------------------------

static void test_vec_capacity(void) {
    printf(YELLOW "\n--- vec_capacity ---\n" RESET);

    Vector_t *v = vec_init(2);

    char a = 'A';
    char b = 'B';
    char c = 'C';

    TEST(vec_capacity(v) == 2, "Initial capacity is 2");

    vec_push(v, &a);
    vec_push(v, &b);

    TEST(vec_capacity(v) == 2,
         "Capacity remains 2 while space is available");

    vec_push(v, &c);

    TEST(vec_capacity(v) == 4,
         "Capacity doubles when vector becomes full");

    TEST(vec_capacity(NULL) == 0,
         "Capacity of NULL vector returns 0");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_empty
// ------------------------------------------------------------

static void test_vec_empty(void) {
    printf(YELLOW "\n--- vec_empty ---\n" RESET);

    Vector_t *v = vec_init(1);

    char a = 'A';

    TEST(vec_empty(v) == 1, "New vector is empty");

    vec_push(v, &a);

    TEST(vec_empty(v) == 0,
         "Vector with an element is not empty");

    vec_clear(v);

    TEST(vec_empty(v) == 1,
         "Cleared vector is empty");

    TEST(vec_empty(NULL) == STATUS_ERROR,
         "Empty on NULL vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_find
// ------------------------------------------------------------

static void test_vec_find(void) {
    printf(YELLOW "\n--- vec_find ---\n" RESET);

    Vector_t *v = vec_init(4);

    char a = 'A';
    char b = 'B';
    char c = 'C';
    char x = 'X';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);
    vec_push(v, &b);

    TEST(vec_find(v, &a) == 0, "Find A returns index 0");
    TEST(vec_find(v, &b) == 1, "Find returns first occurrence of B");
    TEST(vec_find(v, &c) == 2, "Find C returns index 2");

    TEST(vec_find(v, &x) == STATUS_NOT_FOUND,
         "Missing element returns STATUS_NOT_FOUND");

    TEST(vec_find(NULL, &a) == STATUS_ERROR,
         "Find on NULL vector returns STATUS_ERROR");

    TEST(vec_find(v, NULL) == STATUS_ERROR,
         "Find with NULL element returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_first
// ------------------------------------------------------------

static void test_vec_first(void) {
    printf(YELLOW "\n--- vec_first ---\n" RESET);

    Vector_t *v = vec_init(3);

    char a = 'A';
    char b = 'B';
    char out = '\0';

    vec_push(v, &a);
    vec_push(v, &b);

    TEST(vec_first(v, &out) == STATUS_SUCCESS,
         "First returns STATUS_SUCCESS");

    TEST(out == 'A', "First returns A");

    TEST(vec_first(v, NULL) == STATUS_ERROR,
         "First with NULL output returns STATUS_ERROR");

    TEST(vec_first(NULL, &out) == STATUS_ERROR,
         "First on NULL vector returns STATUS_ERROR");

    vec_clear(v);

    TEST(vec_first(v, &out) == STATUS_ERROR,
         "First on empty vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_last
// ------------------------------------------------------------

static void test_vec_last(void) {
    printf(YELLOW "\n--- vec_last ---\n" RESET);

    Vector_t *v = vec_init(3);

    char a = 'A';
    char b = 'B';
    char out = '\0';

    vec_push(v, &a);
    vec_push(v, &b);

    TEST(vec_last(v, &out) == STATUS_SUCCESS,
         "Last returns STATUS_SUCCESS");

    TEST(out == 'B', "Last returns B");

    TEST(vec_last(v, NULL) == STATUS_ERROR,
         "Last with NULL output returns STATUS_ERROR");

    TEST(vec_last(NULL, &out) == STATUS_ERROR,
         "Last on NULL vector returns STATUS_ERROR");

    vec_clear(v);

    TEST(vec_last(v, &out) == STATUS_ERROR,
         "Last on empty vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_set
// ------------------------------------------------------------

static void test_vec_set(void) {
    printf(YELLOW "\n--- vec_set ---\n" RESET);

    Vector_t *v = vec_init(3);

    char a = 'A';
    char b = 'B';
    char x = 'X';

    vec_push(v, &a);
    vec_push(v, &b);

    size_t old_size = vec_size(v);
    size_t old_capacity = vec_capacity(v);

    TEST(vec_set(v, &x, 1) == STATUS_SUCCESS,
         "Set returns STATUS_SUCCESS");

    TEST(vec_value_equals(v, 1, 'X'),
         "Set replaces element");

    TEST(vec_size(v) == old_size,
         "Set preserves size");

    TEST(vec_capacity(v) == old_capacity,
         "Set preserves capacity");

    TEST(vec_set(v, &x, 999) == STATUS_ERROR,
         "Set out of bounds returns STATUS_ERROR");

    TEST(vec_set(NULL, &x, 0) == STATUS_ERROR,
         "Set on NULL vector returns STATUS_ERROR");

    TEST(vec_set(v, NULL, 0) == STATUS_ERROR,
         "Set with NULL element returns STATUS_ERROR");

    vec_clear(v);

    TEST(vec_set(v, &x, 0) == STATUS_ERROR,
         "Set on empty vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_count
// ------------------------------------------------------------

static void test_vec_count(void) {
    printf(YELLOW "\n--- vec_count ---\n" RESET);

    Vector_t *v = vec_init(5);

    char a = 'A';
    char b = 'B';
    char x = 'X';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &a);
    vec_push(v, &a);
    vec_push(v, &b);

    TEST(vec_count(v, &a) == 3,
         "Count finds three occurrences of A");

    TEST(vec_count(v, &b) == 2,
         "Count finds two occurrences of B");

    TEST(vec_count(v, &x) == 0,
         "Count returns 0 when element is absent");

    TEST(vec_count(NULL, &a) == 0,
         "Count on NULL vector returns 0");

    TEST(vec_count(v, NULL) == 0,
         "Count with NULL element returns 0");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_contains
// ------------------------------------------------------------

static void test_vec_contains(void) {
    printf(YELLOW "\n--- vec_contains ---\n" RESET);

    Vector_t *v = vec_init(3);

    char a = 'A';
    char b = 'B';
    char x = 'X';

    vec_push(v, &a);
    vec_push(v, &b);

    TEST(vec_contains(v, &a) == 1,
         "Contains returns 1 for A");

    TEST(vec_contains(v, &b) == 1,
         "Contains returns 1 for B");

    TEST(vec_contains(v, &x) == 0,
         "Contains returns 0 for missing element");

    TEST(vec_contains(NULL, &a) == STATUS_ERROR,
         "Contains on NULL vector returns STATUS_ERROR");

    TEST(vec_contains(v, NULL) == STATUS_ERROR,
         "Contains with NULL element returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_swap
// ------------------------------------------------------------

static void test_vec_swap(void) {
    printf(YELLOW "\n--- vec_swap ---\n" RESET);

    Vector_t *v = vec_init(3);

    char a = 'A';
    char b = 'B';
    char c = 'C';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    TEST(vec_swap(v, 0, 2) == STATUS_SUCCESS,
         "Swap returns STATUS_SUCCESS");

    TEST(vec_value_equals(v, 0, 'C'),
         "C moved to index 0");

    TEST(vec_value_equals(v, 2, 'A'),
         "A moved to index 2");

    TEST(vec_swap(v, 1, 1) == STATUS_SUCCESS,
         "Swap same index returns STATUS_SUCCESS");

    TEST(vec_value_equals(v, 1, 'B'),
         "Swap same index preserves element");

    TEST(vec_swap(v, 0, 999) == STATUS_ERROR,
         "Swap out of bounds returns STATUS_ERROR");

    TEST(vec_swap(NULL, 0, 0) == STATUS_ERROR,
         "Swap on NULL vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_reverse
// ------------------------------------------------------------

static void test_vec_reverse(void) {
    printf(YELLOW "\n--- vec_reverse ---\n" RESET);

    Vector_t *v = vec_init(4);

    char a = 'A';
    char b = 'B';
    char c = 'C';
    char d = 'D';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);
    vec_push(v, &d);

    TEST(vec_reverse(v) == STATUS_SUCCESS,
         "Reverse even vector returns STATUS_SUCCESS");

    TEST(vec_value_equals(v, 0, 'D'), "Index 0 is D");
    TEST(vec_value_equals(v, 1, 'C'), "Index 1 is C");
    TEST(vec_value_equals(v, 2, 'B'), "Index 2 is B");
    TEST(vec_value_equals(v, 3, 'A'), "Index 3 is A");

    vec_free(v);


    v = vec_init(3);

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    TEST(vec_reverse(v) == STATUS_SUCCESS,
         "Reverse odd vector returns STATUS_SUCCESS");

    TEST(vec_value_equals(v, 0, 'C'), "Odd reverse index 0 is C");
    TEST(vec_value_equals(v, 1, 'B'), "Odd reverse middle remains B");
    TEST(vec_value_equals(v, 2, 'A'), "Odd reverse index 2 is A");

    vec_clear(v);

    TEST(vec_reverse(v) == STATUS_SUCCESS,
         "Reverse empty vector returns STATUS_SUCCESS");

    TEST(vec_reverse(NULL) == STATUS_ERROR,
         "Reverse NULL vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_copy
// ------------------------------------------------------------

static void test_vec_copy(void) {
    printf(YELLOW "\n--- vec_copy ---\n" RESET);

    Vector_t *v = vec_init(4);

    char a = 'A';
    char b = 'B';
    char c = 'C';
    char x = 'X';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    Vector_t *copy = vec_copy(v);

    TEST(copy != NULL, "Copy was created");

    TEST(vec_size(copy) == vec_size(v),
         "Copy preserves size");

    TEST(vec_capacity(copy) == vec_capacity(v),
         "Copy preserves capacity");

    TEST(vec_value_equals(copy, 0, 'A'), "Copy contains A");
    TEST(vec_value_equals(copy, 1, 'B'), "Copy contains B");
    TEST(vec_value_equals(copy, 2, 'C'), "Copy contains C");

    vec_set(copy, &x, 1);

    TEST(vec_value_equals(copy, 1, 'X'),
         "Copy can be modified independently");

    TEST(vec_value_equals(v, 1, 'B'),
         "Modifying copy does not modify original");

    TEST(vec_copy(NULL) == NULL,
         "Copy NULL vector returns NULL");

    vec_free(copy);
    vec_free(v);
}


// ------------------------------------------------------------
// vec_shrink_to_fit
// ------------------------------------------------------------

static void test_vec_shrink_to_fit(void) {
    printf(YELLOW "\n--- vec_shrink_to_fit ---\n" RESET);

    Vector_t *v = vec_init(10);

    char a = 'A';
    char b = 'B';
    char c = 'C';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    TEST(vec_capacity(v) == 10,
         "Capacity starts at 10");

    TEST(vec_shrink_to_fit(v) == STATUS_SUCCESS,
         "Shrink returns STATUS_SUCCESS");

    TEST(vec_capacity(v) == 3,
         "Shrink reduces capacity to size");

    TEST(vec_size(v) == 3,
         "Shrink preserves size");

    TEST(vec_value_equals(v, 0, 'A'), "Shrink preserves A");
    TEST(vec_value_equals(v, 1, 'B'), "Shrink preserves B");
    TEST(vec_value_equals(v, 2, 'C'), "Shrink preserves C");

    vec_clear(v);

    TEST(vec_shrink_to_fit(v) == STATUS_SUCCESS,
         "Shrink empty vector returns STATUS_SUCCESS");

    TEST(vec_capacity(v) == 1,
         "Shrink empty vector preserves minimum capacity of 1");

    TEST(vec_shrink_to_fit(NULL) == STATUS_ERROR,
         "Shrink NULL vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_reserve
// ------------------------------------------------------------

static void test_vec_reserve(void) {
    printf(YELLOW "\n--- vec_reserve ---\n" RESET);

    Vector_t *v = vec_init(2);

    char a = 'A';
    char b = 'B';

    vec_push(v, &a);
    vec_push(v, &b);

    TEST(vec_reserve(v, 10) == STATUS_SUCCESS,
         "Reserve returns STATUS_SUCCESS");

    TEST(vec_capacity(v) == 10,
         "Reserve increases capacity to 10");

    TEST(vec_size(v) == 2,
         "Reserve preserves size");

    TEST(vec_value_equals(v, 0, 'A'),
         "Reserve preserves A");

    TEST(vec_value_equals(v, 1, 'B'),
         "Reserve preserves B");

    TEST(vec_reserve(v, 5) == STATUS_SUCCESS,
         "Reserve smaller capacity returns STATUS_SUCCESS");

    TEST(vec_capacity(v) == 10,
         "Reserve does not shrink capacity");

    TEST(vec_reserve(v, 10) == STATUS_SUCCESS,
         "Reserve equal capacity returns STATUS_SUCCESS");

    TEST(vec_capacity(v) == 10,
         "Reserve equal capacity preserves capacity");

    TEST(vec_reserve(NULL, 10) == STATUS_ERROR,
         "Reserve NULL vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_clear
// ------------------------------------------------------------

static void test_vec_clear(void) {
    printf(YELLOW "\n--- vec_clear ---\n" RESET);

    Vector_t *v = vec_init(5);

    char a = 'A';
    char b = 'B';

    vec_push(v, &a);
    vec_push(v, &b);

    size_t old_capacity = vec_capacity(v);

    TEST(vec_clear(v) == STATUS_SUCCESS,
         "Clear returns STATUS_SUCCESS");

    TEST(vec_size(v) == 0,
         "Clear resets size to 0");

    TEST(vec_capacity(v) == old_capacity,
         "Clear preserves capacity");

    TEST(vec_empty(v) == 1,
         "Vector is empty after clear");

    TEST(vec_clear(v) == STATUS_SUCCESS,
         "Clearing empty vector succeeds");

    TEST(vec_clear(NULL) == STATUS_ERROR,
         "Clear NULL vector returns STATUS_ERROR");

    vec_free(v);
}


// ------------------------------------------------------------
// vec_free
// ------------------------------------------------------------

static void test_vec_free(void) {
    printf(YELLOW "\n--- vec_free ---\n" RESET);

    Vector_t *v = vec_init(2);

    char a = 'A';

    vec_push(v, &a);

    TEST(vec_free(v) == STATUS_SUCCESS,
         "Free valid vector returns STATUS_SUCCESS");

    TEST(vec_free(NULL) == STATUS_ERROR,
         "Free NULL vector returns STATUS_ERROR");
}


// ------------------------------------------------------------
// vec_info / vec_output
// ------------------------------------------------------------

static void test_vec_info_output(void) {
    printf(YELLOW "\n--- vec_info / vec_output ---\n" RESET);

    Vector_t *v = vec_init(3);

    char a = 'A';
    char b = 'B';
    char c = 'C';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    printf("Expected vec_output: A B C\n");
    printf("Actual vec_output:   ");
    vec_output(v);
    printf("\n");

    printf("\nExpected vec_info:");
    printf("\nCount:    3");
    printf("\nCapacity: 3");
    printf("\nSize:     3 Bytes\n");

    printf("\nActual vec_info:");
    vec_info(v);
    printf("\n");

    /*
     * These two functions only print output and do not return a status,
     * so this is currently a smoke/manual-output test rather than a
     * strict automated assertion.
     */

    TEST(1, "vec_output executed without crashing");
    TEST(1, "vec_info executed without crashing");

    vec_free(v);
}


// ------------------------------------------------------------
// main
// ------------------------------------------------------------

int main(void) {
    printf("\n====== VECTOR TESTS ======\n");

    test_vec_init();

    test_vec_push();
    test_vec_insert();
    test_vec_pop();
    test_vec_remove();

    test_vec_get();
    test_vec_size();
    test_vec_capacity();
    test_vec_empty();

    test_vec_find();
    test_vec_first();
    test_vec_last();
    test_vec_set();

    test_vec_count();
    test_vec_contains();

    test_vec_swap();
    test_vec_reverse();
    test_vec_copy();

    test_vec_shrink_to_fit();
    test_vec_reserve();

    test_vec_clear();
    test_vec_free();

    test_vec_info_output();


    printf("\n==========================\n");
    printf("Tests passed: " GREEN "%d" RESET "\n", tests_passed);
    printf("Tests failed: " RED "%d" RESET "\n", tests_failed);
    printf("==========================\n");


    return tests_failed == 0
         ? EXIT_SUCCESS
         : EXIT_FAILURE;
}
