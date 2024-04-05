#include <stdlib.h>
#include <ctype.h>
#include <memory.h>
#include "string.h"
#include <stdbool.h>
#include <stdio.h>

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

void changNumberToSpaces(char *s) {
    char* writer = s;
    copy_(s, getEndOfString(s)+1, _stringBuffer);
    char* reader = _stringBuffer;
    while (*reader) {
        if (isdigit(*reader)) {
            int digit = *reader-'0';
            for (int i = 0; i < digit; ++i) {
                *writer = ' ';
                writer++;
            }

        } else {
            *writer = *reader;
            writer++;
        }

        reader++;
    }
}


int wordLen(WordDescriptor wd){
    return wd.end - wd.begin;
}

int wordCmp(WordDescriptor w1, WordDescriptor w2){
    int w1len = wordLen(w1);
    int w2len = wordLen(w2);

    if(w1len == w2len){
        return memcmp(w1.begin, w2.begin, w1len); //0
    } else{
        if(w1len > w2len) {
            int res = memcmp(w1.begin, w2.begin, w2len);
            return res != 0 ? res : 1;
        } else{
            int res = memcmp(w1.begin, w2.begin, w1len);
            return res != 0 ? res : -1;
        }
    }
}

char* wordCpy(char *dst, WordDescriptor src){
    return copy_(src.begin, src.end, dst);
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char *readPtr, *recPtr;
    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy_(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }
    WordDescriptor word;
    while (getWord(readPtr, &word)) {
        if (!wordCmp(word, word1))
            recPtr = wordCpy(recPtr, word2);
        else
            recPtr = wordCpy(recPtr, word);
        *recPtr = ' ';
        recPtr++;
        readPtr = word.end;
    }
    recPtr--;
    *recPtr = '\0';
}

bool arrangeWords(char *s) {
    WordDescriptor word1;
    getWord(s, &word1);
    WordDescriptor word2;
    int order = 0;
    while (getWord(word1.end, &word2)) {
        if (order == 0)
            order = wordCmp(word1, word2);
        else {
            int new_order = wordCmp(word1, word2);
            if ((order != new_order) && (new_order != 0))
                return false;
        }
            word1 = word2;
    }
    return true;
}







