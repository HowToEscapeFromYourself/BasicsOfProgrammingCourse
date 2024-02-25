#include "vector.h"


Vector createVector(size_t n) {
    int *data = (int *) (malloc(sizeof(int) * n));

    if (n == 0)
        data = NULL;
    else if (data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return (Vector) {data, 0, n};
}


void reserve(Vector *v, size_t newCapacity) {
    v->data = (int *) (realloc(v->data, sizeof(int) * newCapacity));
    v->capacity = newCapacity;

    if (newCapacity < v->size)
        v->size = newCapacity;

    if (newCapacity == 0)
        v->data = NULL;
    else if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}


void clear(Vector *v) {
    v->size = 0;
}


void shrinkToFit(Vector *v) {
    v->data = (int *) (realloc(v->data, sizeof(int) * v->size));
    v->capacity = v->size;
}


void deleteVector(Vector *v) {
    free(v->data);
}


bool isEmpty(Vector *v) {
    return v->size == 0 ? true : false;
}


bool isFull(Vector *v) {
    return v->size == v->capacity ? true : false;
}


int getVectorValue(Vector *v, size_t i) {
    return v->data[i];
}


void pushBack(Vector *v, int x) {
    while (v->size >= v->capacity)
        reserve(v, v->capacity > 0 ? v->capacity * 2 : 1);

    v->data[v->size++] = x;
}


void popBack(Vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "bad popBack");
        exit(1);
    } else
        v->size--;
}


int *atVector(Vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "IndexError: a[%zu] is not exists", index);
        exit(1);
    }

    return &v->data[index];
}


int *back(Vector *v) {
    return atVector(v, v->size - 1);
}


int *front(Vector *v) {
    return atVector(v, 0);
}
