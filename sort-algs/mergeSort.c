#include <stdio.h>
#include <stdlib.h>
void printArray(int* array, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}
// Log shows merging of parts
void log(int* first, int* second, int* result, int firstSize, int secondSize, int resultSize)
{
    printf("\n\n");
    printf("Left part: ");
    printArray(first, firstSize);
    printf("\n");
    printf("Right part: ");
    printArray(second, secondSize);
    printf("\n");
    printf("Merged parts: ");
    printArray(result, resultSize);
}
// Merge two arrays to one array
int* merge(int* first, int* second, int firstSize, int secondSize)
{
    int commonSize = firstSize + secondSize;
    // Merged array
    int* result = (int*) calloc (commonSize, sizeof(int));
    int i = 0, j = 0, k = 0;
    // There are elements in both arrays
    while (i < firstSize && j < secondSize)
    {
        if (first[i] <= second[j])
        {
            result[k] = first[i];
            i++;
        }
        else
        {
            result[k] = second[j];
            j++;
        }
        k++;
    }
    // There are elements in only first array
    while (i < firstSize)
    {
        result[k] = first[i];
        k++;
        i++;
    }
    // There are elements in only second array
    while (j < secondSize)
    {
        result[k] = second[j];
        k++;
        j++;
    }

    // LOG
    log(first, second, result, firstSize, secondSize, commonSize);

    return result;
}

// Recoursive merge sort function
int* mergeSort(int* array, int size)
{
    // If array has <= 1 element - do not devide it
    if (size <= 1) {
        return array;
    }

    // Middle element index
    int mid = size / 2;

    // Create and fill left and right parts of arrays
    int* first = (int*) calloc(mid, sizeof(int));
    for (int i = 0; i < mid; i++) {
        first[i] = array[i];
    }
    int* second = (int*) calloc(size - mid, sizeof(int));
    for (int i = 0; i < size - mid; i++) {
        second[i] = array[i+mid];
    }

    // Keep deviding parts recoursively
    first = mergeSort(first, mid);
    second = mergeSort(second, size - mid);

    // Exiting the recursion stack by merging
    int* result = merge(first, second, mid, size - mid);

    // Free memory
    free(first);
    free(second);

    // Return result
    return result;
}
int main()
{
    // Scan Array
    int size;
    scanf("%d", &size);
    int* array = (int*) calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
    // Print Scan-Array
    printf("Initial array:\n");
    printArray(array, size);

    // Get result with log
    int* sortedArray = mergeSort(array, size);

    // Free memory
    free(array);
    free(sortedArray);
}