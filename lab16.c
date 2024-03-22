#include "matrix/matrix.h"
#include <assert.h>
#include "algorithms/algorithms.h"

//меняет строки с максимальным и минимальным элементом матрицы m
void swapRowsMaxAndMinElem (matrix *m) {
    position pos_max = getMaxValuePos(*m);
    position pos_min = getMinValuePos(*m);
    swapRows(*m, pos_min.rowIndex, pos_max.rowIndex);
}

//сортирует по неубыванию минимальные элементы матрицы m
void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMin);
}

//сортирует по неубыванию максимальные элементы матрицы m
void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}







//Тесты
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

void test_sortRowsByMinElement(){
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
                            2, 3, 9,
                            4, 5, 6,
                    },
            3, 3
    );

    sortRowsByMinElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}
void test_sortRowsByMaxElement(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            4, 5, 6,
                            1, 3, 10
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            4, 5, 6,
                            2, 3, 9,
                            1, 3, 10,

                    },
            3, 3
    );

    sortRowsByMaxElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}





void all_test(){
    test_swapRowsMaxAndMinElem();
    test_sortRowsByMinElement();
    test_sortRowsByMaxElement();
}









int main() {
    all_test();
    return 0;
}