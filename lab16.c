#include "matrix/matrix.h"
#include <assert.h>
#include "algorithms/algorithms.h"
#include <limits.h>
#include <stdio.h>
#include <math.h>

//меняет строки с максимальным и минимальным элементом матрицы m
void swapRowsMaxAndMinElem (matrix *m) {
    position pos_max = getMaxValuePos(*m);
    position pos_min = getMinValuePos(*m);
    swapRows(*m, pos_min.rowIndex, pos_max.rowIndex);
}

//сортирует строки по неубыванию минимальных элементов матрицы m
void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMin);
}

//сортирует строки по неубыванию максимальных элементов матрицы m
void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

//сортирует столбцы по неубыванию минимальных элементов матрицы m
void sortColsByMinElement(matrix m) {
    selectionSortColsMatrixByColCriteria(m, getMin);
}

//сортирует столбцы по неубыванию максимальных элементов матрицы m
void sortColsByMaxElement(matrix m) {
    selectionSortColsMatrixByColCriteria(m, getMax);
}

// умножении матрицы m1 на матрицу m2
matrix mulMatrices(matrix m1, matrix m2) {
    assert (m1.nCols == m2.nRows);
    matrix m3 = getMemMatrix(m1.nRows, m2.nCols);
    for (int col_index = 0; col_index < m3.nCols; ++col_index) {
        for (int row_index = 0; row_index < m3.nRows; ++row_index) {
            int sum = 0;
            for (int i = 0; i < m1.nCols; ++i) {
                sum += m1.values[row_index][i] * m2.values[i][col_index];
                m3.values[row_index][col_index] = sum;
            }

        }
    }
    return m3;
}

//возведение симметричной матрицы в квадрат
void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(m)) {
        matrix m1 = mulMatrices(*m, *m);
        freeMemMatrix(m);
        *m = m1;
    }
}

//возращает сумму элементов массива
long long getSum(int *a, int n) {
    long long  sum = 0;
    for (int i = 0; i < n; ++i) {
        sum+=a[i];
    }
    return sum;
}

//возвращает истина если массив уникален, иначе ложь
bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (a[i] == a[j])
                return false;

        }

    }
    return true;
}

//транспонирует матрицу, если среди сумм элементов строк матрицы нет равных
void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    long long arr[m->nRows];
    for (int row_index = 0; row_index < m->nRows; ++row_index) {
        arr[row_index] = getSum(m->values[row_index], m->nCols);

    }
    if (isUnique(arr, m->nRows)) {
        transposeMatrix(m);
    }
}

//возвращает истина, если m1=m2^-1 или m1*m2=единичная матрица
bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix m3 = mulMatrices(m1, m2);
    bool e = isEMatrix(&m3);
    freeMemMatrix(&m3);
    return e;
}

//возвращает максимальное из двух чисел
int max(int a, int b) {
    return a>b?a:b;
}

//возвращает минимальное из двух чисел
int min(int a, int b) {
    return a<b?a:b;
}

//возвращает сумму максимальных элементов всех псевдодиагоналей матрицы
long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int n = m.nRows+m.nCols-1;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = INT_MIN;
    }
    int q = m.nCols-1;
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        for (int col_index = 0; col_index < m.nCols; ++col_index) {
            int index = row_index-col_index+q;
            arr[index] = max(arr[index], m.values[row_index][col_index]);
        }
    }
    return getSum(arr, n) - arr[q];
}

//возвращает минимальный элемент матрицы в выделенной области
int getMinInArea(matrix m) {
    position pos_max = getMaxValuePos(m);
    int min_el = m.values[pos_max.rowIndex][pos_max.colIndex];
    for (int row_index = 0; row_index < pos_max.rowIndex; ++row_index) {
        int post = min(pos_max.colIndex-row_index+pos_max.rowIndex+1, m.nCols);
        for (int col_index = max(pos_max.colIndex+row_index-pos_max.rowIndex, 0);
             col_index < post;
             ++col_index)
            min_el = min(min_el, m.values[row_index][col_index]);

    }
    return min_el;
}

//возвращает дистанцию от нач. координат до точки
float getDistance(int *a, int n) {
    float d;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i]*a[i];
    }
    d = sqrtf(sum);
    return d;
}

//сортировка вставками строк матрицы m по неубыванию значения функции criteria
//применяемой для строк
void insertionSortRowsMatrixByRowCriteriaF(matrix m,
                                           float (*criteria)(int *, int)) {
    float criteria_array [m.nRows];
    for (int row_index = 0; row_index < m.nRows; ++row_index)
        criteria_array[row_index] = criteria(m.values[row_index], m.nCols);

    float newElement;
    int location;

    for (int i = 1; i < m.nRows; i++) {
        newElement = criteria_array[i];
        int *prow = m.values[i];
        location = i - 1;

        while(location >= 0 && criteria_array[location] > newElement) {
            criteria_array[location+1] = criteria_array[location];
            m.values[location+1] = m.values[location];
            location = location - 1;

        }
        criteria_array[location+1] = newElement;
        m.values[location+1] = prow;
    }
}

//возвращает упорядоченную матрицу по неубыванию строк как точек в
// m-мерном пространстве
void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
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
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
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
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
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
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_sortColsByMinElement() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            3, 4, 9,
                            5, 2, 6,
                            3, 1, 10
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            4, 3, 9,
                            2, 5, 6,
                            1, 3, 10,

                    },
            3, 3
    );

    sortColsByMinElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_sortColsByMaxElement(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            9, 3, 2,
                            6, 5, 4,
                            10, 3, 1
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            4, 5, 6,
                            1, 3, 10
                    },
            3, 3
    );

    sortColsByMaxElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_getSquareOfMatrixIfSymmetric() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            1, 3, 2,
                            3, 5, 4,
                            2, 4, 6
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            14, 26, 26,
                            26, 50, 50,
                            26, 50, 56
                    },
            3, 3
    );

    getSquareOfMatrixIfSymmetric(&m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_transposeIfMatrixHasNotEqualSumOfRows(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9, 5,
                            3, 5, 6, 3,
                            9, 6, 6, 5
                    },
            3, 4
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            3, 5, 6,
                            9, 6, 6,
                            5, 3, 5
                    },
            4, 3
    );

    transposeIfMatrixHasNotEqualSumOfRows(&m1);
    assert(areTwoMatricesEqual(&m1, &m2));

    matrix m3 = createMatrixFromArray(
            (int[])
                    {
                            8, 3, 1,
                            3, 5, 4,
                            2, 4, 6
                    },
            3, 3
    );

    matrix m4 = createMatrixFromArray(
            (int[])
                    {
                            8, 3, 1,
                            3, 5, 4,
                            2, 4, 6
                    },
            3, 3
    );

    transposeIfMatrixHasNotEqualSumOfRows(&m3);
    assert(areTwoMatricesEqual(&m3, &m4));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
    freeMemMatrix(&m4);
}

void test_isMutuallyInverseMatrices() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 5, 7,
                            6, 3, 4,
                            5, -2, -3
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            1, -1, 1,
                            -38, 41, -34,
                            27, -29, 24
                    },
            3, 3
    );
    assert(isMutuallyInverseMatrices(m1, m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_findSumOfMaxesOfPseudoDiagonal() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 5, 7,
                            6, 3, 4,
                            5, -2, -3,
                            -2, -2, -3,
                            0, -1, -3,
                    },
            5, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            3, 2, 5, 4,
                            1, 3, 6, 3,
                            3, 2, 1, 2
                    },
            3, 4
    );

    assert(findSumOfMaxesOfPseudoDiagonal(m1) == 22);
    assert(findSumOfMaxesOfPseudoDiagonal(m2) == 20);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_getMinInArea() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 5, 7,
                            6, 3, 4,
                            5, 1, 2,
                            -2, 9, -3,
                            0, -1, -3,
                    },
            5, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            2, 5, 7, 5, 8,
                            6, 3, 4, 6, 10,
                            5, 1, 2, 3, 2
                    },
            3, 5
    );
    assert(getMinInArea(m1) == 1);
    assert(getMinInArea(m2) == 5);
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_sortByDistances() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            -2, -2, -4,
                            2, -2, 1,
                            0, 3, -4,
                            100, 9, -3,
                    },
            4, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            2, -2, 1,
                            -2, -2, -4,
                            0, 3, -4,
                            100, 9, -3,
                    },
            4, 3
    );

    sortByDistances(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}


//void test_sortByDistances1() {
//    matrix m1 = createMatrixFromArray(
//            (int[])
//                    {
//                            2, 5, 7,
//                            6, 3, 4,
//                            5, 1, 2,
//                            2, 9, 3,
//                            0, 1, 3,
//                    },
//            5, 3
//    );
//
//    matrix m2 = createMatrixFromArray(
//            (int[])
//                    {
//                            0, 1, 3,
//                            5, 1, 2,
//                            6, 3, 4,
//                            2, 5, 7,
//                            2, 9, 3,
//
//                    },
//            5, 3
//    );
//    sortByDistances(m1);
//    outputMatrix(m1);
//    outputMatrix(m2);
//    assert(areTwoMatricesEqual(&m1, &m2));
//    freeMemMatrix(&m1);
//    freeMemMatrix(&m2);
//}



void all_test(){
 //   test_sortByDistances1();
    test_swapRowsMaxAndMinElem();

    test_sortRowsByMinElement();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_sortByDistances();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();

}









int main() {
    all_test();
    return 0;
}