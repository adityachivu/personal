#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m = 0, n = 0;
    scanf("%d", &m);
    scanf("%d", &n); 
    
       
    if ( m > n )
    {
        printf("INVALID\n");
        return 0;
    }
    
    int i = 0, count[n+1];
    
    for ( i = 0; i <= n; i++)
    {
        count[i] = 0;
    }
    
    for ( i = 0; i < m; i++)
    {
        int temp;
        scanf("%d", &temp);
        if (temp > n)
        {
            printf("INVALID\n");
            return 0;
        }
        
        else
        {
            count[temp]++;
        }
    }
    
    for ( i = 0; i < (n+1); i++)
    {
        if ( count[i] > 1 )
        {
            printf("INVALID\n");
            return 0;
        }
    }
    
    printf("VALID\n");
    
    return 0;
}
    
        