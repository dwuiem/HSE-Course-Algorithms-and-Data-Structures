#include <stdio.h>
#include <stdlib.h>

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void log(int pivotIndex, int pivot, int* resultArray, int size) {
    printf("\n");
    printf("Pivot index: %d , pivot element: %d\n", pivotIndex, pivot);
    printf("Array after partition: ");
    printArray(resultArray, size);
}

void swap(int* first, int* second) {
    int t = *first;
    *first = *second;
    *second = t;
}

void quickSort(int* array, int size, int left, int right) {
    if (left >= right) return;

    int pivotIndex = (left + right) / 2;
    int pivot = array[pivotIndex];

    // Temp arrays
    int* lessPivot = (int*)malloc((right - left + 1) * sizeof(int));
    int* morePivot = (int*)malloc((right - left + 1) * sizeof(int));

    int l = 0, m = 0;

    for (int i = left; i <= right; i++) {
        if (i != pivotIndex) {
            if (array[i] <= pivot) {
                lessPivot[l++] = array[i];
            } else {
                morePivot[m++] = array[i];
            }
        }
    }

    // Copy elements to array consistently
    for (int i = 0; i < l; i++) {
        array[left + i] = lessPivot[i];
    }
    array[left + l] = pivot;
    for (int i = 0; i < m; i++) {
        array[left + l + 1 + i] = morePivot[i];
    }

    // Free memory
    free(lessPivot);
    free(morePivot);

    // LOG
    log(pivotIndex, pivot, array, size);

    // Change pivotIndex
    pivotIndex = left + l;

    // Recursively sort arrays before and after pivot element with other borders
    quickSort(array, size, left, pivotIndex - 1);
    quickSort(array, size, pivotIndex + 1, right);
}

int main() {
    // Scan Array
    int size;
    scanf("%d", &size);
    int* array = (int*)calloc(size, sizeof(int));

    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    // Print Scan-Array
    printf("Initial array:\n");
    printArray(array, size);

    quickSort(array, size, 0, size - 1);

    free(array);
    return 0;
}
