#ifndef TEST_COMMON_H
#define TEST_COMMON_H


extern int tests_passed;
extern int tests_failed;


#define YELLOW "\033[33m"
#define GREEN  "\033[32m"
#define RED    "\033[31m"
#define RESET  "\033[0m"


#include <stdio.h>


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

#endif
