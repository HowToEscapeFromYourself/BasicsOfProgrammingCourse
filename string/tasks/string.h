
#ifndef DATA_STRUCTURES1_STRING_H
#define DATA_STRUCTURES1_STRING_H
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
#include <stdlib.h>
#include <stdbool.h>



//возвращает длину строки
size_t strlen_(const char *begin);

//возвращает указатель на первый элемент с кодом ch
char* find(char *begin, char *end, int ch);

//возвращает указатель на первый символ, отличный от пробельных
char* findNonSpace(char *begin);

//возвращает указатель на первый пробельный символ
char* findSpace(char *begin);

//возвращает указатель на первый справа символ, отличный от пробельных
char* findNonSpaceReverse(char *rbegin, const char *rend);

//возвращает указатель на первый пробельный символ справа
char* findSpaceReverse(char *rbegin, const char *rend);

//сравнивает две строки и возвращает их разницу
int strcmp(const char *lhs, const char *rhs);

//записывает по адресу beginDestination фрагмент памяти, начиная с адреса
//beginSource до endSource
char* copy_(const char *beginSource, const char *endSource,
           char *beginDestination) ;

//записывает по адресу beginDestination элементы из фрагмента памяти начиная с
// beginSource заканчивая endSource, удовлетворяющие функции-предикату f
char* copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int));

//записывает по адресу beginDestination элементы из фрагмента памяти начиная с
// rbeginSource заканчивая rendSource, удовлетворяющие функции-предикату f
char* copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int));



//удаляет из строки все пробельные символы
void removeNonLetters(char *s);

//возвращает указатель на конец строки
char* getEndOfString(char *s);

//преобразовает строку, оставляя только один символ в каждой последовательности
//подряд идущих одинаковых символов
void removeAdjacentEqualLetters(char *s);

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

//возвращает 0, если не было считано слово, и 1 если было
int getWord(char *beginSearch, WordDescriptor *word);

//преобразовает строку таким образом, чтобы цифры каждого слова были перенесены
// в начало слова и изменен порядок следования цифр в слове на обратный
void digitToStart(WordDescriptor word);

//считывает слово с конца строки
int getWordReverse(char *rbegin, char *rend, WordDescriptor *word);

//преобразовывет строку, обратив каждое слово этой строки
void getWordsInStringReverse(char *s);

//преобразовывет строку, заменяя каждую цифру соответствующим ей числом пробелов
void changNumberToSpaces(char *s);

//возвращает длину строки
int wordLen(WordDescriptor wd);

//сравнивает два слова, возвращает 0, если слова равны
int wordCmp(WordDescriptor w1, WordDescriptor w2);

//копирует слово в строку dst и возвращает указатель на след. фрагмент памяти
char* wordCpy(char *dst, WordDescriptor src);

//заменяет все вхождения слова w1 на слово w2
void replace(char *source, char *w1, char *w2);

//проверяет упорядочены ли лексикографически слова данного предложения
bool arrangeWords(char *s);

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

extern BagOfWords _bag;
extern BagOfWords _bag2;

//выводит слово
void printWord(WordDescriptor word);

//выводит слова данной строки в обратном порядке по одному в строке экрана
void getBagOfWords(BagOfWords *bag, char *s);

//возвращает количество слов-палиндромов
int countPalindromes(char *s);

//возвращает строку out, в которой чередуются слова первой и второй строки
void mergeStr(char* s1, char* s2, char* out);

//копирует строку
void  strcpy_(char *dst, char *src);

//преобразовает строку, изменив порядок следования слов в строке на обратный
void getReverseSort(char *s);

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

//проверяет есть ли буква с в слове
bool isAlphaInWord(WordDescriptor *word, char c);

//возвращает слово данной строки, предшествующее первому из слов, содержащих
// букву "а"
WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(
        char *s, WordDescriptor *w);

//копирует слово в строку и ставит нолик
void wordDescriptorToString(WordDescriptor word, char *destination);

//oпределяет последнее из слов первой строки, которое есть во второй строке
WordDescriptor lastWordInFirstStringInSecondString(char* s1, char* s2);

//oпределяет, есть ли в данной строке одинаковые слова
bool haveEqualWords(char* s);

//определяет, есть ли в данной строке пара слов, составленных из одинакового
// набора букв
bool haveWordWithEqualSymbolSet(char* s);

//получает строку из слов данной строки, которые отличны от последнего слова
void deleteEqualLastWord(char* s);

//возвращает первое слово строки s1 котрое есть в строке s2
WordDescriptor getFirstWordS1InS2(char* s1, char* s2);

//является ли слово палиндромом
bool isPalindrome(WordDescriptor word);

//удаляет из данной строки слова-палиндромы
void deletePalindromes(char* s);

//копирует из сумки bag слова начиная с bag2_size
void fillStrWords(char* s, BagOfWords bag, size_t start_copy_index);

//дополняет строку, содержащую меньшее количество слов, последними словами строки,
// в которой содержится большее количество слов
void fillShorterStr(char* s1, char* s2);

//определяет, входит ли в данную строку каждая буква данного слова
bool isAllWordLettersInStr(char* s, WordDescriptor word);

#endif //DATA_STRUCTURES1_STRING_H
