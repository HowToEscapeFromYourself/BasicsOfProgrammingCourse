#include <assert.h>
#include <stdio.h>
#include "matrix/matrix.h"

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





void all_test(){
    test_task1();
    test_task2();
    test_task3();
}



int main() {
    all_test();
    return 0;
}