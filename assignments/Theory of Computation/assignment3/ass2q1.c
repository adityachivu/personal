#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack
{
	char c;
	struct stack *next;
}dpda;

char state = 'p';
int ind = 0;
int r=0;
int length;

typedef struct stack st;
st *head= NULL;

void push(char v)
{
	st *temp;
	temp= (st *)malloc(sizeof(st));
	temp->c = v;
	temp->next = head;
	if(head==NULL)
	{
		head= temp;
		return;
	}
	head= temp;
	return;
}

char top()
{
	if(head==NULL)
		return 'z';
	return head->c;
}

char pop()
{
	char t;
	if(head==NULL)
	{
		printf("Stack is empty");
		return 'z';
	}
	t = head->c;
	head= head->next;
	return t;
}

void printConfig(char *inputString)
{
    int i;
    for(i=ind;i<length;i++)
    {
        printf("%c",inputString[i]);
    }
    if(ind>length-1)
        printf("e");
    printf("\t\t");
}

void printStack()
{
    st *temp=head;
    if(head==NULL)
        printf("e");
    while(temp!=NULL)
    {
        printf("%c",temp->c);
        temp=temp->next;
    }
    //printf("\n");
    return;
}
void updateState(char *inputString)
{
    r=0;
	switch(state)
	{
		case 'p':
		{
			state = 'q';
			push('S');
			break;
		}
		case 'q':
		{
			if(inputString[ind]== 'a')
			{
				state='r';
				ind++;
			}
			else if(inputString[ind]== 'b')
			{
				state='t';
				ind++;
			}
			else if(inputString[ind]=='$')
			{
				state='u';
				ind++;
			}
			else
            {
                printf("State q: error");
                r = 1;
                break;
            }
			break;

		}
		case 'r':
		{
			if(top()=='S')
			{
				pop();
				push('B');
				push('A');
				push('a');
			}
			else if(top()=='A')
			{
				pop();
				push('a');
			}
			else if(top()=='B')
			{
				pop();
				push('S');
				push('a');
			}
			else if(top()=='a')
			{
				pop();
				state='q';
			}
			else
            {
               printf("State r: error");
               r = 1;
               break;
            }

			break;
		}
		case 't':
		{
			if(top()=='S')
			{
				pop();
				push('A');
				push('B');
				push('b');
			}
			else if(top()=='A')
			{
				pop();
				push('S');
				push('b');
			}
			else if(top()=='B')
			{
				pop();
				push('b');
			}
			else if(top()=='b')
			{
				pop();
				state='q';
			}
			else
            {
                printf("State r: error");
                r=1;
                break;
            }
			break;
		}
		case 'u':
		{
			if(top()== 'z')
			{
				state='f';

			}
			else
            {
				printf("State u: error");
				r=1;
				break;
            }
			break;
		}
	}
	return;
}


int main(int argc, char **argv)
{
	char *inputS = argv[1];
	printf("Input String is:");
	printf("%s\n\n", inputS);
	char inputString[strlen(inputS)+1];
    strcpy(inputString,inputS);
	strcat(inputString,"$");
	length = strlen(inputString);
	printf("State\tUnread Input\tStack\n");
	printf("%c\t%s\t\t-\n",state,inputString);
	while((state!='f')&&(r==0))
	{
		updateState(inputString);
		printf("%c\t",state);
		printConfig(inputString);
		printStack();
		printf("\n");
	}
	printf("\n");
	if((state=='f')&&(r==0))
		printf("The string is accepted\n");
	else
		printf("The string is rejected\n");
	return 0;
}

