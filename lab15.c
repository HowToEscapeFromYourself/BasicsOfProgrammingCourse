#include "matrix/matrix.h"
#include <assert.h>


void test_countZeroRows() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    0, 0, 0,
                    0, 0, 1,
                    0, 0, 0,
                    0, 1, 1,
            },
            5, 3
    );
    assert(countZeroRows(m) == 2);
    freeMemMatrix(&m);
}
int getSum (int *arr, int n){
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum+=arr[i];
    }
    return sum;
}

void test_insertionSortRowsMatrixByRowCriteria() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 7,
                    3, 0, 5,
                    6, 7, 0,
                    8, 22, 13,
                    0, 1, 1,
            },
            5, 3
    );
    matrix res = createMatrixFromArray(
            (int[]) {
                    0, 1, 1,
                    3, 0, 5,
                    1, 2, 7,
                    6, 7, 0,
                    8, 22, 13,

            },
            5, 3
    );
    insertionSortRowsMatrixByRowCriteria(m, getSum);
    assert(areTwoMatricesEqual(&m, &res));
    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test_selectionSortColsMatrixByColCriteria() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 7,
                    3, 0, 5,
                    6, 7, 0,
                    8, 22, 13,
                    0, 1, 1,
            },
            5, 3
    );
    matrix res = createMatrixFromArray(
            (int[]) {
                    1, 7, 2,
                    3, 5, 0,
                    6, 0, 7,
                    8,13, 22,
                    0, 1, 1,
            },
            5, 3
    );
    selectionSortColsMatrixByColCriteria(m, getSum);
    assert(areTwoMatricesEqual(&m, &res));
    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test_isEMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 7,
                    3, 0, 5,
                    6, 7, 0,

            },
            3, 3
    );
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,

            },
            3, 3
    );
    assert(!isEMatrix(&m));
    assert(isEMatrix(&m2));
    freeMemMatrix(&m);
    freeMemMatrix(&m2);
}

void test_isSymmetricMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 7,
                    3, 0, 5,
                    6, 7, 0,

            },
            3, 3
    );
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    2, 1, 4,
                    3, 4, 1,

            },
            3, 3
    );
    assert(!isSymmetricMatrix(&m));
    assert(isSymmetricMatrix(&m2));
    freeMemMatrix(&m);
    freeMemMatrix(&m2);
}

void test_transposeMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 7,
                    3, 0, 5,
                    6, 7, 0,
                    8, 22, 13,
                    0, 1, 1,
            },
            5, 3
    );
    matrix res = createMatrixFromArray(
            (int[]) {
                    1, 3, 6, 8, 0,
                    2, 0, 7, 22, 1,
                    7, 5, 0, 13, 1,
            },
            3, 5
    );
    transposeMatrix(&m);
    assert(areTwoMatricesEqual(&m, &res));
    freeMemMatrix(&m);
    freeMemMatrix(&res);
}


void test_matrix_all() {
    test_countZeroRows();
    test_insertionSortRowsMatrixByRowCriteria();
    test_selectionSortColsMatrixByColCriteria();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeMatrix();
}

int main() {
    test_matrix_all();
    return 0;
}