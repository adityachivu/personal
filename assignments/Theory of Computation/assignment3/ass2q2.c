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
int ind1, ind2, ind3, ind4;
int b;

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
    if(ind<=length-1)
    {
    for(i=0;i<ind;i++)
    {
    printf(" ");
    }
    }
    if(ind>length-1)
        printf("e");
    printf("\t\t");
}

void printStack()
{
    st *temp=head;
    if(head==NULL)
    {
       if(state=='u'|| state=='f')
            printf("\t\t");
       printf("e");
    }
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
			push('T');
			break;
		}
		case 'q':
		{
			if(inputString[ind]== 'n')
			{
				state='r';
				ind++;
			}
			else if(inputString[ind]== '=')
			{
				state='t';
				ind++;
			}
			else if(inputString[ind]=='$')
			{
				state='u';
				ind++;
			}
			else if(inputString[ind]=='<')
			{
				state='v';
				ind++;
			}
			else if(inputString[ind]=='>')
			{
				state='w';
				ind++;
			}
			else if(top()=='T')
			{
				pop();
				push('A');
				push('E');
				push('F');
			}
			else if(top()=='F')
			{
				pop();
				push('i');
				push('(');
				push('r');
				push('o');
				push('f');
			}
			else if(inputString[ind]=='$')
			{
				state='u';
				ind++;
			}
			else if((inputString[ind]=='f')&&(top()=='f'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='o')&&(top()=='o'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='r')&&(top()=='r'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='(')&&(top()=='('))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]==')')&&(top()==')'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='i')&&(top()=='i'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='n')&&(top()=='n'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='t')&&(top()=='t'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='=')&&(top()=='='))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='0')&&(top()=='0'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]==';')&&(top()==';'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='+')&&(top()=='+'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='<')&&(top()=='<'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='>')&&(top()=='>'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='1')&&(top()=='1'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='2')&&(top()=='2'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='3')&&(top()=='3'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='4')&&(top()=='4'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='5')&&(top()=='5'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='6')&&(top()=='6'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='7')&&(top()=='7'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='8')&&(top()=='8'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='9')&&(top()=='9'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]=='-')&&(top()=='-'))
			{
				pop();
				ind++;
			}
			else if((inputString[ind]==' ')&&(top()==' '))
			{
				pop();
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
			if(top()=='E')
			{
				pop();
				push('i');
				push(';');
				//push('0');
				//push('-');
				for(b=ind2-1;b>ind1;b--)
                {
                    push(inputString[b]);
                }
				push('=');
				push('i');
				push('t');
				push('n');
			}
			else if(top()=='n')
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
			if(top()=='E')
			{
				pop();
				push('i');
				push(';');
				//push('0');
				//push('-');
				for(b=ind2-1;b>ind1;b--)
                {
                    push(inputString[b]);
                }
				push('=');
			}
			else if(top()=='=')
			{
				pop();
				state='q';
			}
			else
            {
                printf("State t: error");
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
		case 'v':
		{
			if(top()=='A')
			{
				pop();
				push(')');
				push('+');
				push('+');
				push('i');
				push(';');
				//push('0');
				//push('2');
				for(b=ind4-1;b>ind3;b--)
                {
                    push(inputString[b]);
                }
				push('<');
			}
			else if(top()=='<')
			{
				pop();
				state='q';
			}
			else
            {
                printf("State v: error");
                r=1;
                break;
            }
			break;
		}
		case 'w':
		{
			if(top()=='A')
			{
				pop();
				push(')');
				push('-');
				push('-');
				push('i');
				push(';');
				//push('0');
				//push('2');
				for(b=ind4-1;b>ind3;b--)
                {
                    push(inputString[b]);
                }
				push('>');
			}
			else if(top()=='>')
			{
				pop();
				state='q';
			}
			else
            {
                printf("State w: error");
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

	char *e;

    e = strchr(inputString, '=');
    ind1 = (int)(e - inputString);
    e = strchr(inputString, ';');
    ind2 = (int)(e - inputString);
    if(strchr(inputString, '>'))
        {e = strchr(inputString, '>');
        ind3 = (int)(e - inputString);}
    else
        {e = strchr(inputString, '<');
        ind3 = (int)(e - inputString);}
    e = strrchr(inputString, ';');
    ind4 = (int)(e - inputString);

	printf("State\tUnread Input\t\t\tStack\n");
	printf("%c\t%s\t\te\n",state,inputString);
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


