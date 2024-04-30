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
}










void all_test(){
    test1();
}



int main() {
    all_test();
    return 0;
}