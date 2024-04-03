
#ifndef DATA_STRUCTURES1_STRING_H
#define DATA_STRUCTURES1_STRING_H
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


#endif //DATA_STRUCTURES1_STRING_H
