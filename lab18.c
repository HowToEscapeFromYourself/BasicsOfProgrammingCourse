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

void test_getWordReverse(){
    char s[] = "asdf qwery                         zxcv";
    WordDescriptor wd;
    assert(getWordReverse(s + 15, s - 1, &wd));
    assert(wd.begin == s + 5);
    assert(wd.end == s + 10);
}

void test_getWordsInStringReverse(){
    char s[] = "Sword of fortune";
    getWordsInStringReverse(s);
    assertString("drowS fo enutrof",
                 s,
                 "string.h",
                 "getWordsInStringReverse",
                 144);
}

void test_changNumberToSpacese() {
    char s[100] = "2s 3d1r";
    changNumberToSpaces(s);
    assertString("  s    d r",
                 s,
                 "string.h",
                 "changNumberToSpacese",
                 143);
}





void all_test(){
    test_removeAdjacentEqualLetters();
    test_getWordReverse();
    test_getWordsInStringReverse();
    test_changNumberToSpacese();

}


int main() {
    all_test();
    return 0;
}