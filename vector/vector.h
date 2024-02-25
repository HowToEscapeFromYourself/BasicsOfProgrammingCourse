#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


#ifndef VECTOR_LIBRARY_H
#define VECTOR_LIBRARY_H


typedef struct Vector {
    int *data;
    size_t size;
    size_t capacity;
} Vector;


Vector createVector(size_t n);

void reserve(Vector *v, size_t newCapacity);

void clear(Vector *v);

void shrinkToFit(Vector *v);

void deleteVector(Vector *v);

bool isEmpty(Vector *v);

bool isFull(Vector *v);

int getVectorValue(Vector *v, size_t i);

void pushBack(Vector *v, int x);

void popBack(Vector *v);

int* atVector(Vector *v, size_t index);

int* back(Vector *v);

int* front(Vector *v);

#endif //VECTOR_LIBRARY_H
