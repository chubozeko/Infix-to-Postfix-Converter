#include <cstdlib>
#include <iostream>
#define STACKSIZE 10

struct stack{
    int items[STACKSIZE];
    int top;
};

void initStack(struct stack *s);
int is_empty(struct stack *s);
int is_full(struct stack *s);
void push(struct stack *s, char);
char pop(struct stack *s);
char stackTop(struct stack * s);
bool prcd(char,char);

using namespace std;

int main(int argc, char *argv[])
{
	int i=0,p=0;
	char symb[20],post[20],topsymb,top;
	struct stack s;
    initStack(&s);
	cout<<"Enter operational equation: "<<endl;
	cin>>symb;
	cout<<endl<<"The INFIX form is "<<symb<<endl;
	while(symb[i]!=NULL)
	{
		if(symb[i]!='+' && symb[i]!='-' && symb[i]!='*' && symb[i]!='/' && 
		symb[i]!='$' && symb[i]!='(' && symb[i]!=')' && symb[i] != '[' && 
		symb[i]!='{' && symb[i]!=']' && symb[i]!='}') // to check if it's an operand
			post[p++] = symb[i];	// add operand to Postfix string
		else
		{
			if(symb[i] == ')' || symb[i] == ']' || symb[i] == '}' )
			{	// while topsymb != preceding opening delimiter
				while(!is_empty(&s) && prcd(stackTop(&s),symb[i]))
				{	// if op <= stackTop
					topsymb = pop(&s);		// popping stackTop
					if(topsymb != '(' && topsymb != '[' && topsymb != '{')
						post[p++] = topsymb;	// adding to Postfix string
				}	
			}
			else if(symb[i] == '(' || symb[i] == '[' || symb[i] == '{')
				push(&s,symb[i]);
			else
			{
				while(!is_empty(&s) && prcd(stackTop(&s),symb[i]))
				{	// if op <= stackTop
					topsymb = pop(&s);		// popping stackTop	
					post[p++] = topsymb;	// adding to Postfix string
				}
				push(&s,symb[i]);
			}
		}
		i++;
	}
	while(!is_empty(&s))
	{
		topsymb = pop(&s);
		post[p++] = topsymb;
	}
	cout<<"The POSTFIX form is "<<post<<endl;
    system ("PAUSE");
    return 0;
}

void initStack(struct stack *s)
{
        s->top = - 1;
}

int is_empty(struct stack *s)
{
        if(s->top == -1)
            return 1;
        else
            return 0;
}

int is_full(struct stack *s)
{
        if(s->top == STACKSIZE-1)
            return 1;
        else
            return 0;
}

void push(struct stack *s, char x)
{
    if(is_full(s))        
    {
        printf("Overflow: Stack is full");
        exit(1);
    }
    s->top++;
    s->items[s->top]=x;
}
char pop(struct stack *s)
{
    if(is_empty(s)==1)    
    {
        printf("Underflow: Stack is empty");
        exit(1);
    }
    return s->items[(s->top)--];
}

char stackTop(struct stack * s)
{
    return s->items[(s->top)];
}

bool prcd(char sTop,char symb)
{
	if( (sTop == '+' && symb == '*') || (sTop == '+' && symb == '/') || 
    (sTop == '-' && symb == '*') || (sTop == '-' && symb == '/') || 
	(sTop == '(' && symb == '+') || (sTop == '(' && symb == '-') || 
	(sTop == '(' && symb == '*') || (sTop == '(' && symb == '/') || 
	(sTop == '[' && symb == '+') || (sTop == '[' && symb == '-') || 
	(sTop == '[' && symb == '*') || (sTop == '[' && symb == '/') || 
	(sTop == '{' && symb == '+') || (sTop == '{' && symb == '-') || 
	(sTop == '{' && symb == '*') || (sTop == '{' && symb == '/') )
        return false;
    else
        return true;	
}

