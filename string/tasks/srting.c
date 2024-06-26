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

void printWord(WordDescriptor word) {
    char* ptr = word.begin;
    while (ptr !=word.end) {
        putchar(*ptr);
        ptr++;
    }
}

BagOfWords _bag;
BagOfWords _bag2;

void getBagOfWords(BagOfWords *bag, char *s) {
    WordDescriptor word1 = {s,s};
    bag->size = 0;
    while (getWord(word1.end, &word1)) {
        bag->words [bag->size++] = word1;
    }
//    for (int i = bag->size-1; i >= 0 ; --i) {
//        printWord(bag->words[i]);
//        putchar('\n');
//    }
}

int countPalindromes(char *s) {
    int counter = 0;
    WordDescriptor word = {s,s};
    while (*word.end!='\0') {
        while (*word.end!=',' && *word.end!='\0') {
            word.end++;
        }
        s = word.end--;
        while (word.begin < word.end && *word.begin == *word.end) {
            word.begin++;
            word.end--;
        }
        if (word.begin >= word.end)
            counter++;
        if (*s != '\0')
            word.begin=word.end=++s;
        else
            word.end = s;
    }
    return counter;
}

void mergeStr(char* s1, char* s2, char* out) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        if (isW1Found) {
            beginSearch1 = word1.end;
            out = wordCpy( out, word1);
            *out = ' ';
            out++;
        }
        if (isW2Found) {
            beginSearch2 = word2.end;
            out = wordCpy( out, word2);
            *out = ' ';
            out++;
        }
    }
    out--;
    *out = '\0';
}

void  strcpy_(char *dst, char *src){
    while (*src){
        *dst = *src;
        dst++, src++;
    }
    *dst = '\0';
}

void getReverseSort(char *s) {
    strcpy_(_stringBuffer, s);
    WordDescriptor word = {getEndOfString(_stringBuffer), NULL};
    while (getWordReverse(word.begin-1, _stringBuffer-1, &word)) {
        s = wordCpy(s, word);
        *s = ' ';
        s++;
    }
    s--;
    *s = '\0';
}

bool isAlphaInWord(WordDescriptor *word, char c) {
    char* ptr = word->begin;
    while (ptr != word->end) {
        if (*ptr == c)
            return true;
        ptr++;
    }
    return false;

}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(
        char *s, WordDescriptor *w) {
    WordDescriptor word;
    if (!getWord(s, w))
        return EMPTY_STRING;
    if (isAlphaInWord(w, 'A'))
        return FIRST_WORD_WITH_A;
    while (getWord(w->end, &word)) {
        if (isAlphaInWord(&word, 'A'))
            return WORD_FOUND;
        else
            *w = word;
    }
    return NOT_FOUND_A_WORD_WITH_A;
}

void wordDescriptorToString(WordDescriptor word, char *destination) {
    destination = wordCpy(destination, word);
    *destination = 0;
}


WordDescriptor lastWordInFirstStringInSecondString(char* s1, char* s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    for (int bag1_index =_bag.size-1; bag1_index >= 0; --bag1_index) {
        for (int bag2_index = 0; bag2_index < _bag2.size; ++bag2_index) {
            if (!wordCmp(_bag.words[bag1_index], _bag2.words[bag2_index]))
                return _bag.words[bag1_index];
        }
    }
    return (WordDescriptor) {NULL, NULL};
}


bool haveEqualWordsInBag(BagOfWords bag) {
    for (int word1_index = 0; word1_index < _bag.size; ++word1_index) {
        for (int word2_index = word1_index+1; word2_index < _bag.size;
             ++word2_index) {
            if (!wordCmp(_bag.words[word1_index], _bag.words[word2_index]))
                return true;
        }
    }
    return false;
}

bool haveEqualWords(char* s) {
    getBagOfWords(&_bag, s);
    return haveEqualWordsInBag(_bag);
}

// Сравнвает два числа
int compare(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

// Функция для сортировки массива символов
void sortCharArray(char arr[], int n) {
    qsort(arr, n, sizeof(char), compare);
}

bool haveWordWithEqualSymbolSet(char* s) {
    strcpy_(_stringBuffer, s);
    getBagOfWords(&_bag, _stringBuffer);
    for (int word_index = 0; word_index < _bag.size; ++word_index) {
        sortCharArray(_bag.words[word_index].begin,
                      wordLen(_bag.words[word_index]));
    }
    return haveEqualWordsInBag(_bag);
}

void deleteEqualLastWord(char* s) {
    WordDescriptor last_word;
    getWordReverse(getEndOfString(s)-1, s-1, &last_word);
    char* read_ptr = s;
    char* write_ptr = s;

    WordDescriptor word;
    while (getWord(read_ptr, &word)) {
        if (wordCmp(word, last_word)) {
            write_ptr = wordCpy(write_ptr, word);
            *write_ptr = ' ';
            write_ptr++;
        }
        read_ptr = word.end;
    }
    if (write_ptr!= s)
        write_ptr--;
    *write_ptr = '\0';
}

WordDescriptor getFirstWordS1InS2(char* s1, char* s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    for (int bag1_index = 0; bag1_index < _bag.size; ++bag1_index) {
        for (int bag2_index = 0; bag2_index < _bag2.size; ++bag2_index) {
            if (!wordCmp(_bag.words[bag1_index], _bag2.words[bag2_index])) {
                if (bag1_index)
                    return _bag.words[bag1_index-1];
                else
                    return (WordDescriptor) {NULL, NULL};
            }
        }
    }
    return (WordDescriptor) {NULL, NULL};
}

bool isPalindrome(WordDescriptor word) {
    word.end--;
    while (word.begin < word.end && *word.begin == *word.end) {
        word.begin++;
        word.end--;
    }
    return word.begin >= word.end;

}

void deletePalindromes(char* s) {
    char *ptr = s;
    WordDescriptor word = {ptr, ptr};
    while (getWord(word.end, &word))
        if (!isPalindrome(word)) {
            ptr = wordCpy(ptr, word);
            if (*ptr)
                *ptr = ' ';
            ptr++;
        }
    if(ptr != s)
        ptr--;

    *ptr = '\0';
}

void fillStrWords(char* s, BagOfWords bag, size_t start_copy_index) {
    char *ptr = getEndOfString(s);
    if (*s){
        *ptr = ' ';
        ptr++;
    }
    for (size_t i = start_copy_index; i < bag.size; ++i) {
        ptr = wordCpy(ptr, bag.words[i]);
        *ptr = ' ';
        ptr++;
    }
    ptr--;
    *ptr = '\0';
}

void fillShorterStr(char* s1, char* s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    if (_bag.size > _bag2.size){
        fillStrWords(s2, _bag, _bag2.size);
    }
    if (_bag.size < _bag2.size){
        fillStrWords(s1, _bag2, _bag.size);
    }
}

bool isAllWordLettersInStr(char* s, WordDescriptor word) {
    const int alphabet_size = 26;
    char buffer[alphabet_size];
    memset(buffer, 0, alphabet_size);
    int size = 0;
    char* ptr = word.begin;
    while (ptr != word.end) {
        if (buffer[*ptr-'a'] == 0) {
            buffer[*ptr - 'a'] = 1;
            size++;
        }
        ptr++;
    }
    ptr = s;
    while (*ptr && size) {
        if (buffer[*ptr -'a']) {
            buffer[*ptr-'a'] = 0;
            size--;
        }
        ptr++;
    }
    return size==0;
}

//считывает одну строку из бинарного файла
char* loadStr(FILE*f) {
    int n;
    fread(&n, sizeof(int), 1, f);
    char* s = malloc(n+1);
    fread(s, sizeof (char), n, f);
    *(s+n) = '\0';
    return s;
}

//записывает строку в бинарный файл f
void saveStrInBin(char* s, FILE*f) {
    int n = (int) strlen_(s);
    fwrite(&n, sizeof (int), 1, f);
    fwrite(s, sizeof (char), n, f);
}