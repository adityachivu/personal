#include <stdio.h>
#include <stdlib.h>

int main()
{
    char person1, person2;
    int m = 0, n = 0;
    
    scanf("%d", &m);
    scanf("%d", &n);
    
    int i = 0, friend[m];
    for ( i = 0; i < m; i++)
    {
        friend[i] = i+1;        
    }
    
    while ( n-- )
    {
        scanf("\n%c %c", &person1, &person2);
        int k = 0;
        int p1 = person1 - 'A';
        int p2 = person2 - 'A';       
        
        int a = friend[p1];
        int b = friend[p2];
        
        for ( k = 0; k < m; k++)
        {            
            if (friend[k] == a || friend[k] == b)
            {
                friend[k] = a;
            }
        }
        
        
    }
    
    int count[m+1];
    for ( i = 0; i <= m; i++)
    {
        count[i] = 0;
    }
    
    for ( i = 0; i < m; i++)
    {
        count[friend[i]] = 1;
    }
    
    int temp = 0;
    for ( i = 0; i <= m; i++)
    {
        temp += count[i];
    }
    
    printf("%d", temp);
            
    return 0;    
}
