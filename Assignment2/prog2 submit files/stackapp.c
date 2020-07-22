/*********************************
* Author: Lachlan Sinclair
* Date: 4/22/2019
* Description: The program uses the stack structure
* from the dynamicArray file to check if a string is
* has balanced parentheses
**********************************/



/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"



/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	
	post:	returns 0 or 1 to be used as a bool
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */	
	//create the stack
	DynArr *stack;
	//ceate it using the size of the string passed
	stack = newDynArr(sizeof(s));

	char temp;
	temp = nextChar(s);

	//loop until the end of the string
	while (temp != '\0')
	{
		//check if the char is one of the opening brackets
		if (temp == 40 || temp == 91 || temp == 123) {
			//push opening brace
			pushDynArr(stack, temp);

		}
		//check for closing bracket
		else if (temp == 41 || temp == 93 || temp == 125) {
			//pop opening brace
			//check to make sure stack has atleast one opening brace
			if (isEmptyDynArr(stack))
			{
				return 0;
			}
			//check to make sure the closing bracket matches the right kind of 
			//opening bracket on the stack
			else{
				if (temp == topDynArr(stack)+1 || temp == topDynArr(stack) + 2)
				{
					popDynArr(stack);
				}
				//the types dont match return false
				else 
				{
					return 0;
				}
			}
		}
		temp = nextChar(s);
	}
	//check the size to determine if the string is balanced
	if (isEmptyDynArr(stack))
	{
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

