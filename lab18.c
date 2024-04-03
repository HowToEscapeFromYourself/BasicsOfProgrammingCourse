#include "string/tasks/string.h"
#include <assert.h>
#include <stdio.h>
#include <memory.h>
#include <ctype.h>



void assertString(const char* expected, char* got,
                  char* const fileName, char* const funcName,
                  int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void test_removeAdjacentEqualLetters(){
    char s[] = "Hello";
    removeAdjacentEqualLetters(s);
    assertString("Helo",
                 s,
                 "string.h",
                 "removeAdjacentEqualLetters",
                 144);
}










void all_test(){
    test_removeAdjacentEqualLetters();
}


int main() {
    all_test();
    return 0;
}