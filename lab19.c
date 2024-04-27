#include <assert.h>
#include <stdio.h>
#include "matrix/matrix.h"
#include <string.h>
#define MAX_STR_SIZE 100
#include "string/tasks/string.h"
#include "Polynomial/polynomial.h"



//возвращает размер файла
long getFileSize(const char* filename) {
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return size;
}

//копирует файл
void fileCopy(const char *dst, const char* source) {
    long n = getFileSize(source);
    FILE*file = fopen(source, "rb");
    char buffer[n];
    fread(buffer, 1, n, file);
    fclose(file);
    file = fopen(dst, "wb");
    fwrite(buffer, 1, n, file);
    fclose(file);
}

//сравнивает файлы
bool isFilesEqual(const char* filename1, const char* filename2) {
    FILE* f1 = fopen(filename1, "r");
    FILE* f2 = fopen(filename2, "r");
    int c1, c2;
    do {
        c1= fgetc(f1);
        c2 = fgetc(f2);
    } while (c1==c2 && c1!=EOF);
    fclose(f1);
    fclose(f2);
    return c1==c2;
}


void task1(const char *filename) {
    FILE*file = fopen(filename, "r");
    int n;
    matrix* ms = loadSquareMatrices(file, &n);
    for (int i = 0; i < n ; ++i) {
        transposeSquareMatrix(&ms[i]);
    }
    fclose(file);
    file = fopen(filename, "w");
    saveSquareMatrices(file, ms, n);
    fclose(file);
}

void test_task1() {
    char filename[] = "task1.txt";
    fileCopy(filename, "task1original.txt");
    task1(filename);
    assert(isFilesEqual("task1finish.txt", filename));
}

void task2(const char *filename) {
    FILE*file = fopen(filename, "r");
    int n;
    fscanf(file, "%d", &n);
    float arr[n];
    for (int i = 0; i < n; ++i) {
        fscanf(file, "%f", &arr[i]);
    }
    fclose(file);
    file = fopen(filename, "w");
    fprintf(file, "%d \n", n);
    for (int i = 0; i < n; ++i) {
        fprintf(file, "%.2f \n", arr[i]);
    }
    fclose(file);
}

void test_task2() {
    char filename[] = "task2.txt";
    fileCopy(filename, "task2original.txt");
    task2(filename);
    assert(isFilesEqual("task2finish.txt", filename));
}

float calc(int o, float d1, float d2) {
    switch (o) {
        case '+': return d1+d2;
        case '-': return d1-d2;
        case '*': return d1*d2;
        case '/': return d1/d2;
    }
}

void task3(const char *filename) {
    float res;
    FILE*file = fopen(filename, "r");
    int d1 = fgetc(file)-'0';
    int o1 = fgetc(file);
    int d2 = fgetc(file)-'0';
    int o2 = fgetc(file);
    if (o2 == EOF)
        res = calc(o1, d1, d2);
    else {
        int d3 = fgetc(file) - '0';
        if ((o1=='+' || o1=='-') && (o2=='*' || o2=='/'))
            res = calc(o1, d1, calc(o2, d2, d3));
        else
            res = calc(o2, calc(o1, d1, d2), d3);
    }
    fclose(file);
    file = fopen(filename, "a");
    fprintf(file, "=%.2f", res);
    fclose(file);
}

void test_task3() {
    char filename[] = "task3.txt";
    fileCopy(filename, "task3original.txt");
    task3(filename);
    assert(isFilesEqual("task3finish.txt", filename));
}

void task4(const char *filename, char* sub_str) {
    FILE*file = fopen(filename, "r");
    long n = getFileSize(filename);
    char s[n+1];
    char* write_ptr = s;
    while (fscanf(file, "%s", write_ptr) == 1) {
        if (strstr(write_ptr, sub_str)) {
            write_ptr+= strlen(write_ptr);
            *write_ptr=' ';
            write_ptr++;
        }
    }
    *write_ptr = '\0';
    fclose(file);
    file = fopen(filename, "w");
    fprintf(file, "%s", s);
    fclose(file);
}

void test_task4() {
    char filename[] = "task4.txt";
    fileCopy(filename, "task4original.txt");
    task4(filename, "abc");
    assert(isFilesEqual("task4finish.txt", filename));
}

void task5(const char *filename) {
    long n = getFileSize(filename);
    FILE *file = fopen(filename, "r");
    char s[n];
    char* write_ptr = s;
    char buffer[n];
    while (fgets(buffer, n, file)!=NULL) {  //строку
        WordDescriptor word = {0, buffer};
        WordDescriptor longest_word = {0, 0};
        int max_len = 0;
        while (getWord(word.end, &word)) {
            if (max_len < wordLen(word)) {
                longest_word = word;
                max_len = wordLen(word);
            }
        }
        if (max_len!= 0) {
            write_ptr = wordCpy(write_ptr, longest_word);
            *write_ptr = '\n';
            write_ptr++;
        }
    }
    *write_ptr = '\0';
    fclose(file);
    file = fopen(filename, "w");
    fprintf(file, "%s", s);
    fclose(file);
}

void test_task5() {
    char filename[] = "task5.txt";
    fileCopy(filename, "task5original.txt");
    task5(filename);
    assert(isFilesEqual("task5finish.txt", filename));
}

void task6(const char *filename, double x) {
    FILE*f = fopen(filename, "rb");
    polynomials ps = createPolynomials(f);
    for (int i = 0; i < ps.amount; ++i) {
        if (isValuePolynomialRoot(ps.buffer[i], x))
            deletePolynomialByIndex(&ps, i--);
    }
    fclose(f);
    f = fopen(filename, "wb");
    savePolynomials(ps,f);
    fclose(f);
}

void task6_gen() {
    polynomials ps = {
            (polynomial[]){
                    createPolynomialFromArr(
                            (int[]){5, 3, 2, 0},
                            (double[]){-2, 4, 2, 8}, //x=1.7
                            4
                    ),
                    createPolynomialFromArr(
                            (int[]){3, 0},
                            (double[]){1, -27}, // x=3
                            2
                    )
            }, 2
    };
    FILE*f = fopen("task6.txt", "wb");
    savePolynomials(ps,f);
    fclose(f);
    for (int i = 0; i < ps.amount; ++i) {
        deletePolynomial(&ps.buffer[i]);
    };
}

void test_task6() {
    task6_gen();
    task6("task6.txt", 3);
    FILE*f = fopen("task6.txt", "rb");
    polynomials ps = createPolynomials(f);
    assert(ps.amount == 1);
    assert(ps.buffer[0].buffer[0].power == 5);
}

void task7(const char *filename) {
    FILE*f = fopen(filename, "rb");
    int n;
    fread(&n, sizeof (int), 1, f);
    int negative[n/2];
    int positive[n/2];
    int index_p = 0;
    int index_n = 0;
    for (int i = 0; i < n; ++i) {
        int num;
        fread(&num, sizeof (int), 1, f);
        if (num > 0)
            positive[index_p++] = num;
        else
            negative[index_n++] = num;
    }
    fclose(f);
    f = fopen(filename, "wb");
    fwrite(&n, sizeof (int), 1, f);
    fwrite(positive, sizeof (int), n/2, f);
    fwrite(negative, sizeof (int), n/2, f);
    fclose(f);
}

void task7_gen() {
    FILE*f = fopen("task7.txt", "wb");
    int n = 8;
    fwrite(&n, sizeof (int), 1, f);
    int arr[8] = {9,-4,-2,20,7,-35,1,-564};
    fwrite(arr, sizeof (int), n, f);
    fclose(f);
}

void test_task7() {
    task7_gen();
    task7("task7.txt");
    FILE*f = fopen("task7.txt", "rb");
    int exp[8] = {9,20,7,1,-4,-2,-35,-564};
    int n;
    fread(&n, sizeof (int), 1, f);
    int res[n];
    fread(res, sizeof (int), n, f);

    assert(!memcmp(res, exp, sizeof (int)*8));
}

void task8(const char *filename) {
    FILE*f = fopen(filename, "rb");
    int n;
    matrix* ms = loadSquareMatricesBin(f, &n);
    for (int i = 0; i < n; ++i) {
        if (!isSymmetricMatrix(&ms[i]))
            transposeSquareMatrix(&ms[i]);
    }
    fclose(f);
    f = fopen(filename, "wb");
    saveSquareMatricesBin(f, ms, n);
    fclose(f);
}

void task8_gen() {
    matrix m01 = createMatrixFromArray(
            (int[])
                    {
                            1, 78,
                            58, 5
                    },
            2,2
    );

    matrix m02 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            2, 4, 7,
                            3, 7, 10
                    },
            3, 3
    );

    matrix m03 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            2, 0, 0,
                            3, 0, 10
                    },
            3, 3
    );

    matrix m04 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            3, 4, 3,
                            1, 2, 10
                    },
            3, 3
    );
    FILE*f = fopen("task8.txt", "wb");
    int n = 4;
    fwrite(&n, sizeof (int), 1, f);
    saveSquareMatrixBin(m01, f);
    saveSquareMatrixBin(m02, f);
    saveSquareMatrixBin(m03, f);
    saveSquareMatrixBin(m04, f);
    fclose(f);
    freeMemMatrix(&m01);
    freeMemMatrix(&m02);
    freeMemMatrix(&m03);
    freeMemMatrix(&m04);
}

void test_task8() {
    task8_gen();
    task8("task8.txt");
    FILE*f = fopen("task8.txt", "rb");
    matrix m01 = createMatrixFromArray( //
            (int[])
                    {
                            1, 58,
                            78, 5
                    },
            2,2
    );

    matrix m02 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            2, 4, 7,
                            3, 7, 10
                    },
            3, 3
    );

    matrix m03 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            2, 0, 0,
                            3, 0, 10
                    },
            3, 3
    );

    matrix m04 = createMatrixFromArray( //
            (int[])
                    {
                            1, 3, 1,
                            2, 4, 2,
                            3, 3, 10
                    },
            3, 3
    );
    int n;
    matrix *ms = loadSquareMatricesBin(f, &n);
    assert(areTwoMatricesEqual(&m01, &ms[0]));
    assert(areTwoMatricesEqual(&m02, &ms[1]));
    assert(areTwoMatricesEqual(&m03, &ms[2]));
    assert(areTwoMatricesEqual(&m04, &ms[3]));
    fclose(f);
    freeMemMatrix(&m01);
    freeMemMatrix(&m02);
    freeMemMatrix(&m03);
    freeMemMatrix(&m04);
}

//считывает одну строку из бинарного файла
char* loadStr(FILE*f) {
    int n;
    fread(&n, sizeof(int), 1, f);
    char* s = malloc(n+1);
    fread(s, sizeof (char), n, f);
    *(s+n) = '\0';
    return s;
}

//записывает строку в бинарный файл f
void saveStrInBin(char* s, FILE*f) {
    int n = (int) strlen_(s);
    fwrite(&n, sizeof (int), 1, f);
    fwrite(s, sizeof (char), n, f);
}

typedef struct {
    char* s;
    int n;
} sportsman;

//загружает из файла 1-го спортстмена
sportsman loadSportsman(FILE*f) {
    sportsman one;
    one.s = loadStr(f);
    fread(&one.n, sizeof (int), 1, f);
    return one;
}

//сохранение в бинарный файл 1-го спортсмена
void saveSportsman(sportsman* one, FILE*f) {
    saveStrInBin(one->s, f);
    fwrite(&one->n, sizeof (int), 1, f);
}

//освобождение памяти, выделенной для 1-го спортсмена
void freeSportsman(sportsman* one) {
    free(one->s);
    one->s = NULL;
    one->n = 0;
}

typedef struct {
    sportsman* buffer;
    int n;
} sportsmen;

//загружает из файла всех спортстменов
sportsmen loadSportsmen(FILE*f) {
    sportsmen many;
    fread(&many.n, sizeof (int), 1, f);
    many.buffer = malloc(sizeof (sportsman)*many.n);
    for (int i = 0; i < many.n; ++i) {
        many.buffer[i] = loadSportsman(f);
    }
    return many;
}

//сохранение в бинарный файл всех спортсменов
void saveSportsmen(sportsmen* many, FILE*f) {
    fwrite(&many->n, sizeof (int), 1, f);
    for (int i = 0; i < many->n; ++i) {
        saveSportsman(&many->buffer[i], f);
    }
}

//освобождение памяти, выделенной для всех спортсменов
void freeSportsmen(sportsmen* many) {
    for (int i = 0; i < many->n; ++i) {
        freeSportsman(&many->buffer[i]);
    }
    many->buffer = NULL;
    many->n = 0;
}

//функция сравнения
int sportsmanCmp(const void* p1,const void* p2) {
    const sportsman* s1 = (sportsman*) p1;
    const sportsman* s2 = (sportsman*) p2;
    return s2->n-s1->n;
}

//оставить n лучших спортсменов в стуктуре many
void theBest(sportsmen* many, int n) {
    qsort(many->buffer, many->n, sizeof (sportsman), sportsmanCmp);
    for (int i = n; i < many->n; ++i) {
        freeSportsman(&many->buffer[i]);
    }
    many->n = n;
}

void task9(char* filename, int n) {
    FILE*f = fopen(filename, "rb");
    sportsmen many = loadSportsmen(f);
    theBest(&many, n);
    fclose(f);
    f = fopen(filename, "wb");
    saveSportsmen(&many,f);
    fclose(f);
    freeSportsmen(&many);
}

void task9_gen() {
    sportsman s1 = {"Фамилия1", 34};
    sportsman s2 = {"Фамилия2", 10};
    sportsman s3 = {"Фамилия3", 100};
    sportsman s4 = {"Фамилия4", 90};
    sportsman s5 = {"Фамилия5", 75};
    sportsman s6 = {"Фамилия6", 60};
    sportsmen ss = {(sportsman[]){s1,s2,s3,s4,s5,s6}, 6};
    FILE*f = fopen("task9.txt", "wb");
    saveSportsmen(&ss, f);
    fclose(f);
}

void test_task9() {
    task9_gen();
    task9("task9.txt", 3);
    FILE*f = fopen("task9.txt", "rb");
    sportsmen many = loadSportsmen(f);
    assert(many.n == 3);
    assert(many.buffer[0].n == 100);
    assert(many.buffer[1].n == 90);
    assert(many.buffer[2].n == 75);
    fclose(f);
    freeSportsmen(&many);
}


void all_test(){
    test_task1();
    test_task2();
    test_task3();
    test_task4();
    test_task5();
    test_task6();
    test_task7();
    test_task8();
    test_task9();
}




int main() {
    all_test();
    return 0;
}