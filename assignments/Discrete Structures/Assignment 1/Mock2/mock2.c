#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    int A[n][n], B[n][n], C[n][n];
    
    int i = 0, j = 0, k = 0;
    
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }
    
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
