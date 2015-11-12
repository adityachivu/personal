#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, r, x, y;
    scanf("%d", &n);
    scanf("%d", &r);
    
    int adj[26][26] = {0};
    int set[26][26] = {0};
    int dis[26][26] = {0};
    int ecc[26] = {0};
    
    //printf("%d\n", n);
    for ( int i = 0; i < r; i++ )
    {
            scanf("%d", &x);
            scanf("%d", &y);
            adj[x][y] = 1;
            adj[y][x] = 1;
    }
    
    int temp[26][26] = {0};
    int mul[26][26] = {0};
    int sum = 0;
    int iter = 1;
    int rad = n, diam = 0;
    
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n; j++ )
        {
            temp[i][j] = adj[i][j];
            dis[i][j] = adj[i][i];
            set[i][j] = adj[i][j];
        }
    }
        
    for ( int iter = 2; iter < n; iter++ )
    {
        for ( int i = 0; i < n; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                sum = 0;
                for ( int k = 0; k < n; k++ )
                {
                    sum += temp[i][k] * adj[k][j];
                }
                mul[i][j] = sum;
                if ( sum != 0 && set[i][j] != 1 )
                {
                    dis[i][j] = iter;
                    set[i][j] = 1;
                }
            }
        }
        for ( int i = 0; i <= n; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                temp[i][j] = mul[i][j];
            }
        }
        /*for ( int i = 0; i < n; i++ )
        {
            for ( int j = 0; j < n; j++ )
            {
                printf("%d ", temp[i][j]);
                //temp[i][j] = mul[i][j];
            }
            printf("\t");
            for ( int j = 0; j < n; j++ )
            {
                printf("%d ", set[i][j]);
                //temp[i][j] = mul[i][j];
            }
            printf("\t");
            for ( int j = 0; j < n; j++ )
            {
                printf("%d ", dis[i][j]);
                //temp[i][j] = mul[i][j];
            }
            printf("\n");
        }
        printf("\n");*/
        
    }
    
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n; j++ )
        {
            if ( dis[i][j] > ecc[i] )
            {
                ecc[i] = dis[i][j];
            }
        }
    }
    
    for ( int i = 0; i < n; i++ )
    {
        if ( rad > ecc[i] )
            rad = ecc[i];
        if ( diam < ecc[i] )
            diam = ecc[i];
    }
    
    printf("%d %d", rad, diam);
    return 0;
}
