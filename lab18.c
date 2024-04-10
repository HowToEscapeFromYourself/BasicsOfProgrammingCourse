#include "string/tasks/string.h"
#include <assert.h>
#include <stdio.h>
#include <memory.h>
#include <ctype.h>
#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)


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

void testAll_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    assert(
            getWordBeforeFirstWordWithA(s1, &word)
            == EMPTY_STRING
    );
    char s2[] = "ABC";
    assert(
            getWordBeforeFirstWordWithA(s2, &word)
            == FIRST_WORD_WITH_A
    );
    char s3[] = "BC A";
    assert(
            getWordBeforeFirstWordWithA(s3, &word)
            == WORD_FOUND
    );
    char got[MAX_WORD_SIZE];
    wordCpy(got, word);
    got[word.end - word.begin] = '\0';
    ASSERT_STRING("BC", got);

    char s4[] = "B Q WE YR OW IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) ==
           NOT_FOUND_A_WORD_WITH_A);
}

void testAll_lastWordInFirstStringInSecondString() {
    WordDescriptor word;
    char s1[] = "";
    char s12[] = "ds sdf";
    assert(
            lastWordInFirstStringInSecondString(s1, s12).begin == NULL
    );
    char s2[] = "ab gd ae";
    char s22[] = "re ab wq";
    word = lastWordInFirstStringInSecondString(s2, s22);
    char got[MAX_WORD_SIZE];
    wordDescriptorToString(word, got);
    ASSERT_STRING("ab", got);

    char s3[] = "";
    assert(
            lastWordInFirstStringInSecondString(s3, s3).begin == NULL
    );
}

void test_haveEqualWords(){
    char s1[] = "I want to go the sea want";
    char s2[] = "I love this lad";
    assert(haveEqualWords(s1));
    assert(!haveEqualWords(s2));
}

void test_haveWordWithEqualSymbolSet(){
    char s1[] = "I want to go the sea ntaw";
    char s2[] = "I love this lad";
    assert(haveWordWithEqualSymbolSet(s1));
    assert(!haveWordWithEqualSymbolSet(s2));
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
    testAll_getWordBeforeFirstWordWithA();
    testAll_lastWordInFirstStringInSecondString();
    test_haveEqualWords();
    test_haveWordWithEqualSymbolSet();
}


int main() {
    all_test();
    return 0;
}