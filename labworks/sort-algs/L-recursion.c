#include <stdio.h>

int lRecursion(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0) return 1;
    if (a > 20 || b > 20 || c > 20) return lRecursion(20, 20, 20);
    if (a < b && b < c) return (lRecursion(a, b, c - 1) + lRecursion(a, b - 1, c - 1) - lRecursion(a, b - 1, c));
    else return (lRecursion(a - 1, b, c) + lRecursion(a - 1, b - 1, c) + lRecursion(a - 1, b, c - 1) - lRecursion(a - 1, b - 1, c - 1));
}
int main()
{
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    printf("%d", lRecursion(a, b, c));
}