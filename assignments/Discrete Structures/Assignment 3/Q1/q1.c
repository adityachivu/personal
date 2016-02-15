#include <stdlib.h>
#include <stdio.h>

int rec(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    if (n == 3)
        return 2;
    if (n >= 4)
        return rec(n-1) + rec(n-3);
}
void main()
{
    int n;
    scanf("%d", &n);
    printf("%d", rec(n));
}
