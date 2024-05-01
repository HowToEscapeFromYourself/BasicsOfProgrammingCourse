#include <assert.h>
#include <stdio.h>
#include "matrix/matrix.h"
#include <string.h>
#include "string/tasks/string.h"
#include "Polynomial/polynomial.h"

typedef struct {
    int row1;
    int col1;
    int row2;
    int col2;
} coordinate;

matrix task1 (int n, coordinate* cs, int w) {
    matrix m = getMemMatrix(n, n);
    for (int i = 0; i < w; ++i) {
        for (int row_index = cs[i].row1; row_index <= cs[i].row2; ++row_index) {
            for (int col_index = cs[i].col1; col_index <= cs[i].col2; ++col_index) {
                m.values[row_index][col_index]++;
            }
        }
    }
    return m;
}

void test1() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            1, 1, 0,
                            1, 2, 1,
                            0, 1, 1
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            1, 1, 0,
                            1, 2, 1,
                            1, 2, 1
                    },
            3, 3
    );
    coordinate c1 = {1, 1, 2, 2};
    coordinate c2 = {0, 0, 1, 1};
    coordinate cs1[] = {c1, c2};

    coordinate c3 = {0, 0, 2, 1};
    coordinate c4 = {1, 1, 2, 2};
    coordinate cs2[] = {c3, c4};
    matrix m3 = task1 (3, cs1, 2);
    matrix m4 = task1 (3, cs2, 2);
    assert(areTwoMatricesEqual(&m1, &m3));
    assert(areTwoMatricesEqual(&m2, &m4));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
    freeMemMatrix(&m4);
}

int max_(int x, int y) {
    return x>y ? x: y;
}

int min_(int x, int y) {
    return x<y ? x: y;
}

int countNeighbours(matrix m, int row_index, int col_index) {
    int n = 0;
    for (int row_n = max_(0, row_index-1); row_n <=
        min_(m.nRows-1 ,row_index+1); ++row_n) {
        for (int col_n = max_(0, col_index-1); col_n <=
            min_ (m.nCols-1,col_index+1); ++col_n) {
            if (m.values[row_n][col_n] == 1)
                n++;
        }
    }
    return n-m.values[row_index][col_index];
}

matrix task2 (matrix m) {
    matrix next = getMemMatrix(m.nRows, m.nCols);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        for (int col_index = 0; col_index < m.nCols; ++col_index) {
            int count = countNeighbours(m, row_index, col_index);
            if (m.values[row_index][col_index] == 1) {
                if (count < 2 || count > 3) {
                    next.values[row_index][col_index] = 0;
                } else
                    next.values[row_index][col_index] = 1;
            } else {
                if (count == 3) {
                    next.values[row_index][col_index] = 1;
                } else
                    next.values[row_index][col_index] = 0;
            }
        }
    }
    return next;
}

void test2() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            0, 1, 0,
                            0, 0, 1,
                            1, 1, 1,
                            0, 0, 0
                    },
            4, 3
    );
    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            1, 0, 1,
                            0, 1, 1,
                            0, 1, 0
                    },
            4, 3
    );
    matrix res = task2(m1);
    assert(areTwoMatricesEqual(&res, &m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&res);
}





void all_test(){
    test1();
    test2();

}



int main() {
    all_test();
    return 0;
}