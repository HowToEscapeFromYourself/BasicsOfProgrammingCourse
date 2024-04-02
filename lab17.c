#include "string/tasks/string.h"
#include <assert.h>
#include <stdio.h>
#include <memory.h>
#include <ctype.h>

void test_findNonSpace() {
    char* s1 = "Hello";
    char* s2 = "";
    char* s3 = " ";
    char* s4 = "  He ll o";
    char* s5 = "Hello ";
    assert(*findNonSpace(s1) == 'H');
    assert(*findNonSpace(s2) == 0);
    assert(*findNonSpace(s3) == 0);
    assert(*findNonSpace(s4) == 'H');
    assert(*findNonSpace(s5) == 'H');
}

void test_findSpace() {
    char* s1 = "Hello";
    char* s2 = "\nRet";
    char* s3 = " ";
    char* s4 = "He ll o";
    char* s5 = "Hello ";
    assert(*findSpace(s1) == 0);
    assert(*findSpace(s2) == '\n');
    assert(*findSpace(s3) == ' ');
    assert(*findSpace(s4) == ' ');
    assert(*findSpace(s5) == ' ');
}

void test_findNonSpaceReverse() {
    char s1[] = "Hello";
    char s2[] = "";
    char s3[] = " ";
    char s4[] = "   He ll o";
    char s5[] = "Hello ";
    assert(findNonSpaceReverse(s1+4, s1-1) == s1+4);
    assert(findNonSpaceReverse(s2-1, s2-1) == s2-1);
    assert(findNonSpaceReverse(s3, s3-1) == s3-1);
    assert(findNonSpaceReverse(s4+9, s4-1) == s4+9);
    assert(findNonSpaceReverse(s5+5, s5-1) == s5+4);
}

void  test_findSpaceReverse() {
    char s1[] = "Hello";
    char s2[] = "";
    char s3[] = " ";
    char s4[] = "   He ll o";
    char s5[] = " Hello";
    assert(findSpaceReverse(s1+4, s1-1) == s1-1);
    assert(findSpaceReverse(s2-1, s2-1) == s2-1);
    assert(findSpaceReverse(s3, s3-1) == s3);
    assert(findSpaceReverse(s4+9, s4-1) == s4+8);
    assert(findSpaceReverse(s5+5, s5-1) == s5);
}

void  test_strcmp() {
    char s1[] = "Hello";
    char s2[] = "Hello";
    char s3[] = "Helo";
    char s4[] = "Hello";
    char s5[] = " ";
    char s6[] = " ";
    char s7[] = " ";
    char s8[] = " t";
    char s9[] = "";
    char s10[] = "w";
    assert(strcmp(s1, s2) == 0);
    assert(strcmp(s3, s4) == 3);
    assert(strcmp(s5, s6) == 0);
    assert(strcmp(s7, s8) == -116);
    assert(strcmp(s9, s10) == -119);
}

void  test_copy() {
    char src[] = "Helloo";
    char dest[20];
    copy_(src, src + 3, dest);
    assert(!memcmp(src, dest, 3));
    copy_(src + 4, src + 6, dest);
    assert(!memcmp(src + 4, dest, 2));
}

int isNotSpace(int c){
    return !isspace(c);
}

void test_copyIf(){
    char src[] = "When will it and";
    char dest[20];

    char s1[] = "Whenwill";
    copyIf(src, src + 9, dest, isNotSpace);
    assert(!memcmp(dest, s1, 8));

    char s2[] = "   ";
    copyIf(src, src + 16, dest, isspace);
    assert(!memcmp(dest, s2, 3));
}

void test_copyIfReverse() {
    char src[] = "I think it is already over";
    char dest[30];

    char s1[] = "revoydaerlasi";
    copyIfReverse(src + 25, src + 10, dest, isNotSpace);
    assert(!memcmp(dest, s1, 13));

    char s2[] = " ";
    copyIfReverse(src + 25, src + 11, dest, isspace);
    assert(!memcmp(dest, s2, 1));
}

void all_test(){
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp();
    test_copy();
    test_copyIfReverse();
}





int main() {
    all_test();
    return 0;
}
