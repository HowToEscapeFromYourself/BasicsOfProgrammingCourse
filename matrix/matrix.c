#include "matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <memory.h>

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++) {
        values[i] = (int *) malloc(sizeof(int) * nCols);
        memset(values[i], 0, nCols*sizeof (int));
    }
    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int row_index = 0; row_index < m->nRows; row_index++)  {
        free(m->values[row_index]);
    }
    free(m->values);
    m->nRows = m->nCols = 0;
    m->values = NULL;
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(&ms[i]);
}

void inputMatrix(matrix *m) {
    for (int row_index = 0; row_index < m->nRows; row_index++)
        for (int col_index = 0; col_index < m->nCols; ++col_index)
            scanf("%d", &m->values[row_index][col_index]);

}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(&ms[i]);
}

void outputMatrix(matrix m) {
    for (int row_index = 0; row_index < m.nRows; row_index++) {
        for (int col_index = 0; col_index < m.nCols; ++col_index)
            printf("%d ", m.values[row_index][col_index]);
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        outputMatrix(ms[i]);
}

void swapRows(matrix m, int i1, int i2) {
    assert (i1 < m.nRows && i1 >= 0);
    assert (i2 < m.nRows && i2 >= 0);

    int *t = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = t;
}

void swapColumns(matrix m, int j1, int j2) {
    assert (j1 < m.nCols && j1 >= 0);
    assert (j2 < m.nCols && j2 >= 0);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        int t = m.values[row_index][j1];
        m.values[row_index][j1] = m.values[row_index][j2];
        m.values[row_index][j2] = t;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)){
    int criteria_array [m.nRows];
    for (int row_index = 0; row_index < m.nRows; ++row_index)
        criteria_array[row_index] = criteria(m.values[row_index], m.nCols);

    int newElement, location;

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

//меняем столбец на строку
void columnToArray(matrix m, int column_index, int *array) {
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        array[row_index] = m.values[row_index][column_index];
    }
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)){
    int criteria_array [m.nCols];
    int column_array [m.nRows];
    for (int column_index = 0; column_index < m.nCols; ++column_index) {
        columnToArray(m, column_index, column_array);
        criteria_array[column_index] = criteria(column_array, m.nRows);

    }
    int minPosition, tmp;

    for (int i = 0; i < m.nCols; i++) {
        minPosition = i;
        for (int j = i + 1; j < m.nCols; j++)
            if (criteria_array[minPosition] > criteria_array[j])
                minPosition = j;
        tmp = criteria_array[minPosition];
        criteria_array[minPosition] = criteria_array[i];
        criteria_array[i] = tmp;
        swapColumns(m, i, minPosition);
    }
}

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols)
        return false;
    for (int row_index = 0; row_index < m1->nRows; ++row_index) {
        if (memcmp(m1->values[row_index],
                   m2->values[row_index],
                   m1->nCols*sizeof (int)))
            return false;
    }
    return true;
}

bool isEMatrix(matrix *m) {
    if (!isSquareMatrix(m))
        return false;
    for (int row_index = 0; row_index < m->nRows; ++row_index) {
        for (int col_index = 0; col_index < m->nCols; ++col_index) {
            if (!(row_index == col_index && m->values[row_index][col_index] == 1||
                    row_index != col_index &&
                    m->values[row_index][col_index] == 0))
                return false;
        }
    }
    return true;
}

bool isSymmetricMatrix(matrix *m) {
    if (!isSquareMatrix(m))
        return false;
    for (int row_index = 0; row_index < m->nRows; ++row_index) {
        for (int col_index = m->nCols-1; col_index > row_index; --col_index) {
            if (m->values[row_index][col_index] !=
            m->values[col_index][row_index])
                return false;
        }
    }
    return true;
}

//функция обмена
void swapInt(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}


void transposeSquareMatrix(matrix *m) {
    if (!isSquareMatrix(m))
        return;
    for (int row_index = 0; row_index < m->nRows; ++row_index)
        for (int col_index = m->nCols-1; col_index > row_index; --col_index)
            swapInt(&m->values[row_index][col_index],
                    &m->values[col_index][row_index]);

}

void transposeMatrix(matrix *m) {
    if (isSquareMatrix(m)) {
        transposeSquareMatrix(m);
        return;
    }
    matrix tm = getMemMatrix(m->nCols, m->nRows);
    for (int row_index = 0; row_index < m->nRows; ++row_index)
        for (int col_index = 0; col_index < m->nCols; ++col_index)
            tm.values[col_index][row_index] = m->values[row_index][col_index];
    freeMemMatrix(m);
    *m = tm;
}

position getMinValuePos(matrix m) {
    int min_elem = m.values[0][0];
    position pos_min = {0, 0};
    for (int row_index = 0; row_index < m.nRows; ++row_index)
        for (int col_index = 0; col_index < m.nCols; ++col_index)
            if (m.values[row_index][col_index] < min_elem) {
                min_elem = m.values[row_index][col_index];
                pos_min  = (position){row_index, col_index};
            }
    return pos_min;
}

position getMaxValuePos(matrix m) {
    int max_elem = m.values[0][0];
    position pos_max = {0, 0};
    for (int row_index = 0; row_index < m.nRows; ++row_index)
        for (int col_index = 0; col_index < m.nCols; ++col_index)
            if (m.values[row_index][col_index] > max_elem) {
                max_elem = m.values[row_index][col_index];
                pos_max  = (position){row_index, col_index};
            }
    return pos_max;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];
    return m;
}

int countZeroRows(matrix m) {
    int counter = 0;
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        int col_index;
        for (col_index = 0; col_index < m.nCols; ++col_index) {
            if (m.values[row_index][col_index] != 0)
                break;

        }
        if (col_index == m.nCols)
            counter++;
    }
    return counter;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices,
                                     size_t nRows,size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}

//19lab

matrix loadSquareMatrix(FILE*file) {
    int n;
    fscanf(file, "%d", &n);
    matrix m = getMemMatrix(n, n);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        for (int col_index = 0; col_index < m.nCols; ++col_index) {
             fscanf(file, "%d", &m.values[row_index][col_index]);
        }
    }
    return m;
}

void saveSquareMatrix(matrix m, FILE*file) {
    fprintf(file, "%d\n", m.nRows);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        for (int col_index = 0; col_index < m.nCols; ++col_index) {
            fprintf(file, "%d ", m.values[row_index][col_index]);
        }
        fputc('\n', file);
    }
}

matrix* loadSquareMatrices(FILE*file, int*n) {
    fscanf(file, "%d", n);
    matrix* arr = malloc(*n*sizeof(matrix));
    for (int i = 0; i < *n; ++i) {
        arr[i] = loadSquareMatrix(file);
    }
    return arr;
}

void saveSquareMatrices(FILE*file, matrix* ms, int n) {
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; ++i) {
        saveSquareMatrix(ms[i], file);
    }
}

//


matrix loadSquareMatrixBin(FILE*f) {
    int n;
    fread(&n, sizeof (int), 1, f);
    matrix m = getMemMatrix(n, n);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        fread(m.values[row_index], sizeof (int), m.nCols, f);
    }
    return m;
}

void saveSquareMatrixBin(matrix m, FILE*f) {
    fwrite(&m.nRows, sizeof (int), 1, f);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        fwrite(m.values[row_index], sizeof (int), m.nCols, f);
    }
}

matrix* loadSquareMatricesBin(FILE*f, int*n) {
    fread(n, sizeof (int), 1, f);
    matrix* arr = malloc(*n*sizeof(matrix));
    for (int i = 0; i < *n; ++i) {
        arr[i] = loadSquareMatrixBin(f);
    }
    return arr;
}

void saveSquareMatricesBin(FILE*f, matrix* ms, int n) {
    fwrite(&n, sizeof (int), 1, f);
    for (int i = 0; i < n; ++i) {
        saveSquareMatrixBin(ms[i], f);
    }
}



