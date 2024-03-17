#include <stdint.h>
#include <assert.h>
#include "../vector/vector.h"


void test_createVector() {
    Vector v1 = createVector(0);
    Vector v2 = createVector(100000);

    deleteVector(&v1);
    deleteVector(&v2);
}


void test_reserve() {
    Vector v1 = createVector(43534);
    pushBack(&v1, 101);
    pushBack(&v1, 42);
    reserve(&v1, 1);
    assert(v1.size == v1.capacity);
    reserve(&v1, 0);
    assert(v1.data == NULL);

    deleteVector(&v1);
}


void test_shrinkToFit() {
    Vector v1 = createVector(3);
    pushBack(&v1, 101);
    pushBack(&v1, 42);
    pushBack(&v1, 310);
    pushBack(&v1, 777);

    assert(v1.size == 4);
    assert(v1.capacity == 6);
    shrinkToFit(&v1);
    assert(v1.capacity == 4);

    deleteVector(&v1);
}


void test_getVectorValue() {
    Vector v1 = createVector(3);
    pushBack(&v1, 123);
    pushBack(&v1, 123);
    pushBack(&v1, 308);
    pushBack(&v1, 712);

    assert(getVectorValue(&v1, 0) == 123);
    assert(getVectorValue(&v1, 3) == 345);

    deleteVector(&v1);
}


void test_isEmpty_isFull() {
    Vector v1 = createVector(2);
    pushBack(&v1, 354);
    pushBack(&v1, 42);
    assert(isFull(&v1));
    assert(!isEmpty(&v1));
    clear(&v1);
    assert(!isFull(&v1));
    assert(isEmpty(&v1));
    reserve(&v1, 0);
    assert(isFull(&v1));
    assert(isEmpty(&v1));

    deleteVector(&v1);
}


void test_pushBack_emptyVector() {
    Vector v1 = createVector(0);
    pushBack(&v1, 101);
    pushBack(&v1, 42);
    pushBack(&v1, 310);
    assert(v1.size == 3);
    assert(v1.capacity == 4);

    deleteVector(&v1);
}


void test_pushBack_fullVector() {
    Vector v1 = createVector(3);
    pushBack(&v1, 101);
    pushBack(&v1, 42);
    pushBack(&v1, 310);

    pushBack(&v1, 777);
    assert(v1.size == 4);
    assert(v1.capacity == 6);

    deleteVector(&v1);
}


void test_popBack_notEmptyVector() {
    Vector v1 = createVector(0);
    pushBack(&v1, 10);
    assert(v1.size == 1);
    popBack(&v1);
    assert(v1.size == 0);
    assert(v1.capacity == 1);

    deleteVector(&v1);
}


void test_atVector_notEmptyVector() {
    Vector v1 = createVector(4);
    pushBack(&v1, 101);
    pushBack(&v1, 42);
    pushBack(&v1, 310);
    pushBack(&v1, 777);
    assert(&v1.data[2] == atVector(&v1, 2));

    deleteVector(&v1);
}


void test_atVector_requestToLastElement() {
    Vector v1 = createVector(4);
    pushBack(&v1, 101);
    pushBack(&v1, 42);
    pushBack(&v1, 310);
    pushBack(&v1, 777);
    assert(&v1.data[3] == atVector(&v1, 3));

    deleteVector(&v1);
}


void test_back_oneElementInVector() {
    Vector v1 = createVector(4);
    pushBack(&v1, 101);
    assert(&v1.data[0] == back(&v1));

    deleteVector(&v1);
}


void test_front_oneElementInVector() {
    Vector v1 = createVector(4);
    pushBack(&v1, 101);
    assert(&v1.data[0] == front(&v1));

    deleteVector(&v1);
}


void test() {

}


int main() {
    test();
    return 0;
}
