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

void test_replace(){
    char s[MAX_STRING_SIZE] = "I hate this lad";
    char out[] = "I love this lad";
    replace(s, "hate", "love");
    assertString(out,
                 s,
                 "string.h",
                 "replace",
                 122);
}

void test_arrangeWords(){
    char s1[] = "abc abc cde efj";
    char s2[] = "abc cde efj abc";
    assert(arrangeWords(s1));
    assert(!arrangeWords(s2));
}

void test_getBagOfWords() {
    char s1[] = "I love this lad";
    getBagOfWords(&_bag, s1);
}

void test_countPalindromes() {
    char s1[] = "cffc,tee,wefsfew,req,abccba";
    assert(countPalindromes(s1)==3);
}

void test_mergeStr(){
    char s1[] = "I to";
    char s2[] = "want go the sea";
    char s3[MAX_STRING_SIZE];
    mergeStr(s1, s2, s3);
    char out[] = "I want to go the sea";
    replace(s3, "hate", "love");
    assertString(out,
                 s3,
                 "string.h",
                 "mergeStr",
                 122);
}

void test_getReverseSort() {
    char s[] = "I want to go the sea";
    char out[] = "sea the go to want I";
    getReverseSort(s);
    assertString(out,
                 s,
                 "string.h",
                 "getReverseSort",
                 122);
}

void all_test(){
    test_removeAdjacentEqualLetters();
    test_getWordReverse();
    test_getWordsInStringReverse();
    test_changNumberToSpacese();
    test_replace();
    test_arrangeWords();
    test_getBagOfWords();
    test_countPalindromes();
    test_mergeStr();
    test_getReverseSort();
}


int main() {
    all_test();
    return 0;
}