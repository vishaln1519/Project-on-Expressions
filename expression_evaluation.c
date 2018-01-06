#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
#include "header.h"


/****************************TO CREATE A STACK OF SIZE CAPACITY**************************************************************************/
STACK *CreateStack(unsigned capacity)
{
        //printf("entered stack creation\n");
        STACK *stack=(STACK*)malloc(sizeof(STACK));//creating an dynamic memory of struct STACK
        if(stack == NULL)
        {	
        		
        	return NULL;
        }

        stack->capacity=capacity;//enterring the details to the stack created
        stack->top=-1;
        stack->array=(char *)malloc(stack->capacity * sizeof(int));

        if(stack->array == NULL)
        	return NULL;

         return stack;



}



/*************************TO PUSH THE CONETENTS INTO THE STACK****************************************************************************/

void push(STACK *stack,int ele)//push function takes address of stack and element to be pushed in the stack
{

        if(isFull(stack)==1)
        {
                printf("cannot push since stack is full\n");
                return ;
        }
        else
        {
                stack->top=stack->top+1;//updating the stack top 
                stack->array[stack->top]=ele;
                

        }       



}



/*************************TO POP THE CONETENTS INTO THE STACK************************************************************************/


char pop(STACK *stack)//used to pop the element at top of stack and return the popped value
{
        if(isEmpty(stack)==1)
        {
                printf("no elements to pop\n");
                return 0;
        }

        return stack->array[stack->top--];// returning and updating the stack top 
}



/***********************FINDS THE TOP ELEMENT ON STACK AND RETURNS IT*******************************************************************/


char peek(STACK* stack)
{
	return stack->array[stack->top];
}




/**********************USED TO CHECK IF THE STACK IS FULL OR NOT******************************************************************************/

int isFull(STACK *stack)//this function takes the address of the stack and finds if the stack is full or not
{
        if(stack->top == stack->capacity -1)
                return 1;
        else
                return 0;
}







/******************************USED TO CHECK IF THE STACK IS EMPTY OR NOT*******************************************************************/


int isEmpty(STACK *stack)////this function takes the address of the stack and finds if the stack is empty or not
{

        if(stack->top == -1)
                return 1;
        else
                return 0;

}


/****************************************FUNCTION TO  EVALUATE THE POST-FIX EXPRESSION********************************************************/

int evaluation(char exp[])
{

	int len=strlen(exp);// finding the lenght of the expression
	STACK *stack = CreateStack(len);//creating a stack of size 'lenl'
	int i;
	

	for(i=0; exp[i];++i)
	{
		if(isdigit(exp[i]))     //checks if the character in string is difit or not i.e '0' ----- '9'
			push(stack,exp[i]-'0');
		else
		{
			int val2 = pop(stack);
			int val1 = pop(stack);
			switch (exp[i])//switch case to match the character with the operator below
			{
			  case '+': push(stack, val2 + val1); 
                        break;
			  case '-': push(stack, val2 - val1); 
                        break;
			  case '*': push(stack, val2 * val1); 
                        break;
			  case '/': push(stack, val2/val1); 
                        break;
			}
		}
	}
	if(stack->top >0)
		return 0;
	else
		return pop(stack);

}


/************************************TO CHECK IF THE CHARACTER IN STRING IS OPERAND i.e 'a' to 'z' and 'A' to 'Z"***************************/

int isOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}



/***************************** TO CHECK THE PRESEDENCE OF THE OPERANDS IN THE EXPRESSION*******************************************************/


int Prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}


/****************************** FUNCTION TO CONVERT IN-FIX EXPRESSION TO POST-FIX *************************************************************/

int infixToPostfix(char* exp)
{
	int i, k;
	
		
	// Create a stack of capacity equal to expression size 
	STACK* stack = CreateStack(strlen(exp));
    if(!stack) // See if stack was created successfully 
        return -1 ;
 
    for (i = 0, k = -1; exp[i]; ++i)
    {
         // If the scanned character is an operand, add it to output.
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
         
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (exp[i] == '(')
            push(stack, exp[i]);
        
        //  If the scanned character is an ‘)’, pop and output from the stack 
        // until an ‘(‘ is encountered.
        else if (exp[i] == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1; // invalid expression                
            else
                pop(stack);
        }
        else // an operator is encountered
        {
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))//checks the precedence of the operand with the peek of stack
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
 
    }
 

	// pop all the operators from the stack
	while (!isEmpty(stack))
		exp[++k] = pop(stack );

	exp[++k] = '\0';
	
	
	printf("THE POST-FIX ECPRESSION IS \n");	
	printf( "%s\n", exp );
}

/****************************** FUNCTION TO CONVERT IN-FIX EXPRESSION TO PRE-FIX ***************************************************************/

int infixToPretfix(char* exp)
{	
	int i, k;

	reverse(exp);// reversing the expression then apllying to the algorithm below

	printf("the 1st reverse is %s\n",exp );

	// Create a stack of capacity equal to expression size 
	STACK* stack = CreateStack(strlen(exp));
	if(!stack) // See if stack was created successfully 
		return -1 ;

	for (i = 0, k = -1; exp[i]; ++i)
	{
		
		if (isOperand(exp[i]))
			exp[++k] = exp[i];
		
		//if scanned character is ') ' ,push it to stack
		else if (exp[i] == ')')
			push(stack, exp[i]);
		
		
		else if (exp[i] == '(')		//if scanned character is '(' ,pop it to stack all elemnts in stack till it finds ')'

		{
			while (!isEmpty(stack) && peek(stack) != ')')
				exp[++k] = pop(stack);
			if (!isEmpty(stack) && peek(stack) != ')')
				return -1; // invalid expression			 
			else
				pop(stack);
		}
		else // an operator is encountered
		{
			while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))//checks the precedence of the operand with the peek of stack
				exp[++k] = pop(stack);
			push(stack, exp[i]);
		}

	}

	while (!isEmpty(stack))
		exp[++k] = pop(stack );

	exp[++k] = '\0';


	reverse(exp);// reversing the string again

	

	printf("THE PRE-fix exp is:  \n");
	printf("%s\n",exp );
}

/*********************************** REVERSING THE STRING ***********************************************************************************/

void reverse(char str[])// function to reverse the srring str 
{
    int i,n;
    int tmp=0;
 
    for(n=0; str[n]!=0; n++);
 
    for(i=0; i<n/2; i++)
    {
        tmp=str[i];
        str[i]=str[n-1-i];
        str[n-1-i]=tmp;
    }
 
    
}






















