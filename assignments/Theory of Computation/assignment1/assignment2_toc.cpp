#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

void print(char *argv[], int n)
{
    int i = n;
    while( argv[1][i] != '\0' )
    {
        printf("%c", argv[1][i]);
        i++;
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    if ( argc != 2 )
    {
        printf("enter command line input\n");
        return 0;
    }
        
    int state0[] = {1, 4, 3, 1, 6, 1, 6};
    int state1[] = {6, 2, 6, 2, 5, 6, 6};
    
    int final_states[] = {2, 3, 5};
    int start_state = 0;
    
    int i = 0;
    int curr_state = start_state;
    int prev_state = start_state;
    
    printf("\nPrevious State\tCurrent State\tRemaining String\n");
    while(argv[1][i] != '\0')
    {
        printf("%d\t\t%d\t\t", prev_state, curr_state);
        prev_state = curr_state;
        print(argv, i);
        if ( argv[1][i] == '0' )
        {
            curr_state = state0[curr_state];
            
        }
        else if ( argv[1][i] == '1' )
        {
            curr_state = state1[curr_state];
            
        }
        //prev_state = curr_state;
        i++;
    }
    printf("%d\t\t%d\t\tNULL", prev_state, curr_state);
    print(argv, i);
    
    printf("\n\nFinal State: %d.\nTherefore - ", curr_state);
    for ( i = 0; i < 3; i++ )
    {
        if (curr_state == final_states[i])
        {
            printf("Accepted\n");
            return 0;
        }
    }    
    
    printf("Rejected\n");
    
    return 0;
}
