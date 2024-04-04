#include <stdlib.h>
#include <ctype.h>
#include <memory.h>
#include "string.h"
#include <stdbool.h>

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char* findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin))
        begin++;
    return begin;
}

char* findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin))
        begin++;
    return begin;
}

char* findNonSpaceReverse(char *rbegin, const char *rend) {
    while (*rbegin != *rend && isspace(*rbegin))
        rbegin--;
    return rbegin;
}

char* findSpaceReverse(char *rbegin, const char *rend) {
    while (*rbegin != *rend && !isspace(*rbegin))
        rbegin--;
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs != '\0' && *lhs == *rhs)
        lhs++, rhs++;
    return *lhs-*rhs;
}

char* copy_(const char *beginSource, const char *endSource,
           char *beginDestination) {
    long long w = endSource-beginSource;
    return memcpy(beginDestination, beginSource, w)+w;
}


char* copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int)) {
    while (beginSource!=endSource ) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
}

char* copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int)) {
    while (rendSource!=rbeginSource ) {
        if (f(*rbeginSource)) {
            *beginDestination = *rbeginSource;
            beginDestination++;
        }
        rbeginSource--;
    }
}

//18 лаба

char* getEndOfString(char *s) {
    char *endOfString = s + strlen_(s);
    return endOfString;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void removeAdjacentEqualLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *reader = s;
    char *writer = s;
    while (reader != endSource) {
        char *next = reader+1;
        if (*next != *reader) {
            *writer = *reader;
            writer++;
        }
        reader++;
    }
    *writer = '\0';
}


int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

char _stringBuffer[MAX_STRING_SIZE + 1];

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy_(word.begin, word.end,
                                 _stringBuffer);

    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend);
    if (word->end == rend)
        return 0;
    word->begin = findSpaceReverse(word->end, rend)+1;
    word->end++;
    return 1;
}

void getWordsInStringReverse(char *s) {
    WordDescriptor word;
    char* real_end = s;
    while (getWord(real_end, &word)) {
        real_end = word.end;
        word.end--;
        while (word.begin < word.end) {
            char sim = *word.begin;
            *word.begin = *word.end;
            *word.end = sim;
            word.begin++;
            word.end--;
        }
    }
}
