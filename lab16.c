#include "matrix/matrix.h"
#include <assert.h>

void swapRowsMaxAndMinElem (matrix *m) {
    position pos_max = getMaxValuePos(*m);
    position pos_min = getMinValuePos(*m);
    swapRows(*m, pos_min.rowIndex, pos_max.rowIndex);
}

void test_swapRowsMaxAndMinElem(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            4, 5, 6,
                            1, 3, 6
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            1, 3, 6,
                            4, 5, 6,
                            2, 3, 9,
                    },
            3, 3
    );

    swapRowsMaxAndMinElem(&m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}

void all_test(){
    test_swapRowsMaxAndMinElem();
}









int main() {
    all_test();
    return 0;
}