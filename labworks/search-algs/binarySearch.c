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
int binarySearch(int *array, int size, int target)
{
    printf("Search history: ");
    int low = 0;
    int high = size - 1;
    while (low <= high)
    {
        int pivot = (high + low) / 2;
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
int main()
{
    int size, target;

    scanf("%d", &size);
    scanf("%d", &target);

    int array[size];

    // Scan elements of array
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    // PRINT
    printf("Initial array:\n");
    printArray(array, size);
    printf("Target element: %d\n", target);
    int index = binarySearch(array, size, target);
    printf("\n");
    if (index == -1)
    {
        printf("No targets\n");
    }
    else
    {
        printf("Target is found at: %d\n", index);
    }
    return 0;
}
