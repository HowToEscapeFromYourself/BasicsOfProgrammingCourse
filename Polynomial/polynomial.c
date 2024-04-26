#include "polynomial.h"
#include <malloc.h>
#include <stdbool.h>
#include <math.h>

polynomial createPolynomial(FILE*f) {
    polynomial p;
    fread(&p.amount, sizeof (int), 1, f);
    p.buffer = malloc(p.amount*sizeof(polynomial_part));
    fread(p.buffer, sizeof (polynomial_part), p.amount, f);
    return p;
}

void savePolynomial(polynomial p, FILE*f) {
    fwrite(&p.amount, sizeof (int), 1, f);
    fwrite(p.buffer, sizeof (polynomial_part), p.amount, f);
}

void deletePolynomial(polynomial *p) {
    free(p->buffer);
    p->buffer = NULL;
    p->amount = 0;
}

polynomial createPolynomialFromArr(int* powers, double* coeffs, int n) {
    polynomial p;
    p.amount = n;
    p.buffer = malloc(p.amount*sizeof(polynomial_part));
    for (int i = 0; i < n; ++i) {
        p.buffer[i].power = powers[i];
        p.buffer[i].coefficient = coeffs[i];
    }
    return p;
}

double calculatePolynomialValue(polynomial p, double x) {
    double res = 0;
    double res_degree = 1; //x^i
    int j = p.amount-1;
    for (int i = 0; i <= p.buffer[0].power; ++i) {
        if (p.buffer[j].power == i)
            res += p.buffer[j--].coefficient * res_degree;
        res_degree*=x;
    }
    return res;
}

bool isValuePolynomialRoot(polynomial p, double x) {
    return fabs(calculatePolynomialValue(p, x))<0.000001;
}

polynomials createPolynomials(FILE*f) {
    polynomials p;
    fread(&p.amount, sizeof (int), 1, f);
    p.buffer = malloc(p.amount*sizeof(polynomial));
    for (int  i = 0;  i < p.amount; ++ i) {
        p.buffer[i] = createPolynomial(f);
    }
    return p;
}

void savePolynomials(polynomials p, FILE*f) {
    fwrite(&p.amount, sizeof (int), 1, f);
    for (int  i = 0;  i < p.amount; ++ i)
        savePolynomial(p.buffer[i], f);
}

void deletePolynomials(polynomials *p) {
    for (int  i = 0;  i < p->amount; ++ i)
        deletePolynomial(&p->buffer[i]);
    free(p->buffer);
    p->buffer = NULL;
    p->amount = 0;
}

void deletePolynomialByIndex(polynomials* ps, int index) {
    if (ps->amount==0)
        return;
    deletePolynomial(&ps->buffer[index]);
    if (--ps->amount) {
        ps->buffer[index]=ps->buffer[ps->amount];
    }
}

