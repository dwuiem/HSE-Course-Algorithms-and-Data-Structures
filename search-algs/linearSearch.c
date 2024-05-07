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

    // Find indecies of target (linear search)
    int *result = (int*) calloc(size, sizeof(int));
    // Size of result
    int k = 0;
    for (int i = 0; i < size; i++) {
        // if target equals element at i index
        if (target == array[i])
        {
            // add this index to result
            result[k] = i;
            k++;
        }
    }

    // PRINT
    printf("Initial array:\n");
    printArray(array, size);
    printf("Target element: %d\n", target);
    if (k == 0)
    {
        printf("No targets");
    }
    else
    {
        printf("Target is found at: ");
        printArray(result, k);
    }

    // Free memory
    free(result);
    return 0;
}
