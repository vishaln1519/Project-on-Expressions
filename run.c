#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
#include "header.h"
int main()
{

	char exp[MAX];
	int option;int res;
	
	do{
		
	printf(" enter the option\n");
	printf("1: evaluation of exp\n2: innfix to postfix \n3: infix to prefix\n0: exit \n");
	scanf("%d",&option);      
		
	switch(option)// switch case to select the opration we want to perform
	{
		case 1: printf("Enter the expression\n");
			scanf("%s",exp);			
			res=evaluation(exp);// calling the function which performs evaluation of postfix expression
			if(res!=0)
				printf("THE EXP WAS EVALUATED AND OUTPUT IS :%d \n",res );
			else
				printf("THE EVALUATION COULD NOT BE PERFORMED\n");
			break;
	
		case 2: printf("Enter the expression\n");
				scanf("%s",exp);  
			
			infixToPostfix(exp);// calling the function which performs conversion of in-fix expressions to post-fix expression

			break;
			
		case 3: printf("Enter the exp\n");
				scanf("%s",exp);
				infixToPretfix(exp);// calling the function which performs evaluation of infix to pre-fix expressions
				break;
		case 0: exit(0);
			break;	
		default : printf("enter a valid option\n");
			break;	
	}

	
    	}while(option<4);

}

