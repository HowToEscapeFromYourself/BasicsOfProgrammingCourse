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




void all_test(){
    test_task1();
    test_task2();
    test_task3();
    test_task4();
    test_task5();
    test_task6();
}



int main() {
    all_test();
    return 0;
}