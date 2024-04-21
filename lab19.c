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







void all_test(){
    test_task1();
    test_task2();
}



int main() {
    all_test();
    return 0;
}