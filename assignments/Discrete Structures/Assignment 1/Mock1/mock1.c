#include<stdlib.h>
#include<stdio.h>

int main()
{
    int arr1[100], arr2[100];
    int i = 0;
    for ( i = 0; i < 100; i++)
    {
        arr1[i] = 0;
        arr2[i] = 0;
    }
    int m, n;
    scanf("%d %d", &m, &n);
    
    for ( i = 0; i < m; i++)
    {
        int temp = 0;
        scanf("%d", &temp);
        if ( arr1[temp] != 1)
            arr1[temp] = 1;
    }
    
    for ( i = 0; i < n; i++)
    {
        int temp = 0;
        scanf("%d", &temp);
        if ( arr2[temp] != 1)
            arr2[temp] = 1;
    }
    
    int flag = 0;  
    for ( i = 0; i < 100; i++)
    {
        if( arr1[i] && arr2[i])
            flag = printf("%d ", i);
    }
    
    if ( flag == 0 )
     printf("NULL");
    return 0;
}
    
