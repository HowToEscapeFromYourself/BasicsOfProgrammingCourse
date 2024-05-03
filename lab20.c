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

//функция сравнения
int intCmp(const void* p1,const void* p2) {
    const int* s1 = (int*) p1;
    const int* s2 = (int*) p2;
    return *s1-*s2;
}

int filterWindow(matrix m, int row_index, int col_index, int filter,
                 int *buffer) {
    int start = filter/2;
    int k = 0;
    for (int row_i = row_index-start; row_i <= row_index+start; ++row_i) {
        for (int col_i = col_index-start; col_i <= col_index+start; ++col_i) {
            buffer[k++] = m.values[row_i][col_i];
        }
    }
    qsort(buffer, filter*filter, sizeof(int), intCmp);
    return buffer[filter*filter/2];
}

matrix task3(matrix m, int filter) {
    int start = filter/2;
    int buffer[filter*filter];
    matrix next = copyMatrix(m);
    for (int row_index = start; row_index < m.nRows-start; ++row_index) {
        for (int col_index = start; col_index < m.nCols-start; ++col_index) {
            next.values[row_index][col_index] = filterWindow(
                    m, row_index,col_index,filter, buffer);
        }
    }
    return next;
}

void test3() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            10, 20, 30,
                            25, 35, 45,
                            15, 25, 35
                    },
            3, 3
    );
    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            10, 20, 30,
                            25, 25, 45,
                            15, 25, 35
                    },
            3, 3
    );
    matrix res = task3(m1, 3);
    assert(areTwoMatricesEqual(&res, &m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&res);
}

//считывает строку справа до точки
bool getReverse(char* r_begin, char* r_end, WordDescriptor* word) {
    if (r_end >= r_begin)
        return false;
    word->end = r_begin;
    while (*r_begin != '.' && r_begin != r_end )
        r_begin--;
    word->begin = r_begin+1;
    return true;
}

//ищет индекс строки в массиве arr
int findStrIndex(char** arr, char* str, int n) {
    for (int i = 0; i < n; ++i) {
        if (!strcmp(arr[i], str))
            return i;
    }
    return -1;
}

void task4(char* a[],  int digits[], int n, char*** out_arr, int** out_values,
             int* out_n) {
    char** arr = malloc(n*3*sizeof (char*));
    int* values = malloc(n*3*sizeof (int));
    int arr_size = 0;
    for (int i = 0; i < n; ++i) {
        WordDescriptor word = {getEndOfString(a[i])+1, NULL};
        while (getReverse(word.begin-2, a[i]-1, &word)) {
            int index_arr = findStrIndex(arr, word.begin, arr_size);
            if (index_arr != -1)
                values[index_arr] += digits[i];
            else {
                values[arr_size] = digits[i];
                arr[arr_size] = malloc(strlen(word.begin)+1);
                strcpy_(arr[arr_size++], word.begin);
            }
        }
    }
    *out_n = arr_size;
    *out_arr = arr;
    *out_values = values;
}

void test4() {
    int n = 4;
    char* str[] = {"google.mail.com", "yahoo.com", "intel.mail.com", "wiki.org"};
    int digits[] = {900, 50, 1, 5};
    int res_n;
    char** res_str;
    int* res_digits;
    task4(str, digits, n, &res_str, &res_digits, &res_n);
    for (int i = 0; i < res_n; ++i) {
        printf("%d %s\n", res_digits[i], res_str[i]);
    }

}

void all_test(){
    test1();
    test2();
    test3();
    test4();
}



int main() {
    all_test();
    return 0;
}