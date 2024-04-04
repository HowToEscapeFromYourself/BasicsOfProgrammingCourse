
#ifndef DATA_STRUCTURES1_STRING_H
#define DATA_STRUCTURES1_STRING_H
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
#include <stdlib.h>


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

#endif //DATA_STRUCTURES1_STRING_H
