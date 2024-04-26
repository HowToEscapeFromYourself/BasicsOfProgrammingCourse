#ifndef DATA_STRUCTURES1_POLYNOMIAL_H
#define DATA_STRUCTURES1_POLYNOMIAL_H
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int power; // n
    double coefficient; // a(n)
} polynomial_part;

typedef struct {
    polynomial_part* buffer; // массив
    int amount; // размер массива
} polynomial;

typedef struct {
    polynomial* buffer;
    int amount;
} polynomials;

//создает многочлен из файла
polynomial createPolynomial(FILE*f);

//сохраняет многочлен в файл
void savePolynomial(polynomial p, FILE*f);

//удаляет многочлен из динамической памяти
void deletePolynomial(polynomial *p);

//создает структуру polynomial из массивов степеней и коэфициентов
polynomial createPolynomialFromArr(int* powers, double* coeffs, int n);

// возвращает значение многочлена при х
double calculatePolynomialValue(polynomial p, double x);

//является ли х корнем
bool isValuePolynomialRoot(polynomial p, double x);

//создает многочлены
polynomials createPolynomials(FILE*f);

//сохраняет многочлены в файл
void savePolynomials(polynomials p, FILE*f);

//удаляет многочлены из динамической памяти
void deletePolynomials(polynomials *p);

//удаляет текущий элемент по индексу и на его местро ставит последний
void deletePolynomialByIndex(polynomials* ps, int index);

#endif //DATA_STRUCTURES1_POLYNOMIAL_H
