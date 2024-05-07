#include <stdio.h>
#include <stdlib.h>

// Array output
void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int binarySearch(int *array, int low, int high, int target)
{
    printf("Search history: ");
    while (low <= high)
    {
        int pivot = low + (high - low) / 2;;
        if (array[pivot] == target)
        {
            printf("%d(%d) ", array[pivot], pivot);
            return pivot;
        }
        else if (array[pivot] > target)
        {
            printf("%d(%d) ", array[pivot], pivot);
            high = pivot - 1;
        }
        else
        {
            printf("%d(%d) ", array[pivot], pivot);
            low = pivot + 1;
        }
    }
    return -1;
}
int doublingSearch(int *array, int size, int target)
{
    printf("Bounds history: ");
    printf("%d(%d) ", array[0], 0);
    if (array[0] == target) return 0;
    if (array[0] > target) return -1;
    int step = 1;
    int previousStep = 0;
    while (step < size && array[step] < target)
    {
        printf("%d(%d) ", array[step], step);
        previousStep = step;
        step *= 2;
    }

    if (step >= size)
    {
        step = size - 1;
        if (previousStep >= step)
        {
            return -1;
        }
        printf("\n");
        binarySearch(array, previousStep+1, step, target);
    }
    else
    {
        printf("%d(%d) ", array[step], step);
        if (array[step] == target)
        {
            return step;
        }
        else
        {
            if (previousStep+1 > step-1)
            {
                return -1;
            }
            printf("\n");
            return binarySearch(array, previousStep+1, step-1, target);
        }
    }
}
int main()
{
    int size, target;

    scanf("%d", &size);
    scanf("%d", &target);

    int *array = (int *)malloc(size * sizeof(int));

    // Scan elements of array
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    // PRINT
    printf("Initial array:\n");
    printArray(array, size);
    printf("Target element: %d\n", target);
    int index = doublingSearch(array, size, target);
    printf("\n");
    if (index == -1)
    {
        printf("No targets\n");
    }
    else
    {
        printf("Target is found at: %d\n", index);
    }
    free(array);
    return 0;
}