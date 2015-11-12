#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    int deg[100] = {0}, temp[i] = {0};
    int valid = 0;
    int sum = 0, seq = 0;
    for ( int i = 0; i < n; i++ )
    {
        scanf("%d", &deg[i]);
        temp[i] = deg[i]
    }
    
    for ( int i = 0; i < n; i++ )
    {
        printf("%d ", deg[i]);
    }
    for ( int iter = 0; iter < n; iter++ )
    {
        
        for ( int i = iter+1; i < deg[iter]; i++ )
        {
            deg[i] -= 1;
        }
        deg[iter] = 0;
        
        
        for ( int i = 0; i < n; i++ )
        {
            printf("%d ", deg[i]);
        }
        printf("\n");
        
        for ( int i = iter; i < n; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                if ( deg[j] > deg[i] )
                {
                    int temp = deg[j];
                    deg[j] = deg[i];
                    deg[i] = temp;
                }
            }
        }
        
        
    }    
    
    for ( int i = 0; i < n; i++ )
    {
        if ( deg[i] >= 0 )
            sum += deg[i];
        seq += temp[i];
    }
               
    if ( !valid )
    {
        printf("INVALID\n");
        return 0;
    }
    
    switch ( seq )
    {
        case (n*(n-1)) :{
                            printf("complete%d", n-1);
                        }break;
        case 
    return 0;
}
