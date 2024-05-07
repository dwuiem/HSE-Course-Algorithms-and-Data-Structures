#include <stdio.h>
#include <stdlib.h>

void mRecursion(int number, int isReverse, int previous)
{
    if (number == 0) return;

    // REVERSE == TRUE
    if (isReverse == 1)
    {
        if (previous != number % 2)
        {
            printf("%d", number % 2);
            previous = number % 2;
        }
        else
        {
            previous = -1;
        }
        mRecursion(number / 2, isReverse, previous);
    }

    // REVERSE == FALSE
    if (isReverse == 0)
    {
        if (previous != number % 2)
        {
            previous = number % 2;
            mRecursion(number / 2, isReverse, previous);
            printf("%d", number % 2);
        }
        else
        {
            previous = -1;
            mRecursion(number / 2, isReverse, previous);
        }
    }
}

int main()
{
    int number;
    scanf("%d", &number);
    mRecursion(number, 0, -1);
    printf("\n");
    mRecursion(number, 1, -1);
}