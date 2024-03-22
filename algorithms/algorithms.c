#include "algorithms.h"

int getMax(int *a, int n) {
    int max_elem = a[0];
    for (int index = 1; index < n; ++index) {
        if (a[index] > max_elem)
            max_elem = a[index];
    }
    return max_elem;
}

int getMin(int *a, int n) {
    int min_elem = a[0];
    for (int index = 1; index < n; ++index) {
        if (a[index] < min_elem)
            min_elem = a[index];
    }
    return min_elem;
}