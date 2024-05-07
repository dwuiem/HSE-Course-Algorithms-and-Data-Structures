#include <stdio.h>
#include <stdlib.h>

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
void worst(int* pivots, int* arrayResult, int size)
{
    for (int i = size - 1; i >= 0; i--) {
        int place;
        switch (pivots[size - 1 - i]) {
            case 0:
                place = (0 + i) / 2;
                break;
            case 1:
                place = 0;
                break;
            case -1:
                place = i;
                break;
        }
        // Заполняем массив индексов пустых ячеек (нулевых)
        int* indexArray = (int*) calloc(i + 1, sizeof(int));
        int k = 0;
        for (int j = 0; j < size; j++) {
            if (arrayResult[j] == 0)
            {
                indexArray[k] = j;
                k++;
            }
        }
        // Подмассив пустых чисел, в которое внедрим число
        int* subArray = (int*) calloc(i+1, sizeof(int));
        for (int j = 0; j < i + 1; j++) {
            subArray[j] = 0;
        }
        subArray[place] = i + 1;
        //  Внедряем подмассив в основной массив по индексам
        for (int j = 0; j < i + 1; j++) {
            arrayResult[indexArray[j]] = subArray[j];
        }
        free(subArray);
        free(indexArray);
    }
}

int main() {
    // Scan Array
    int size;
    scanf("%d", &size);
    int* pivots = (int*)calloc(size, sizeof(int));
    int* array = (int*)calloc(size, sizeof(int));
    int* arrayResult = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        scanf("%d", &pivots[i]);
    }
    for (int i = 0; i < size; i++) {
        array[i] = i + 1;
        arrayResult[i] = 0;
    }
    worst(pivots, arrayResult, size);
    printArray(arrayResult, size);

    free(pivots);
    free(array);
    free(arrayResult);

    return 0;
}
