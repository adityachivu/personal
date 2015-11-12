#include<stdlib.h>
#include<stdio.h>

int main()
{
    int function[101], inverse[101];
    int t = 0;
    int i = 0;
    int x = 0, y = 0;
    for( i = 0; i < 100; i++)
    {
         scanf("%d", &x);
         scanf("%d", &y);
         function[x] = y;
         inverse[y] = x;
    }
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &y);
        printf("%d\n", inverse[y]);        
    }
    return 0;
}
