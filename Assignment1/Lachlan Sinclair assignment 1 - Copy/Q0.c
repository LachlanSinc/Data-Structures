
/* CS261- Assignment 1 - Q. 0*/
/* Name: Lachlan Sinclair
 * Date: 4/11/2019
 * Solution description: This program shows the basic relationship
 * of pass objects address and using pointers to work with those
 * addresses ing functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr) {

	/*Print the value and address of the integer pointed to by iptr*/
	printf("\nValue of x in fooA: %d", *iptr);
	printf("\nAddress of x in fooA: %p", (void*)iptr);

	/*Increment the value of the integer pointed to by iptr by 5*/
	*iptr += 5;
	/*Print the address of iptr itself*/
	printf("\nAddress of iptr in fooA: %p", (void*)&iptr);

   /*Dummy variable, ignore the warning*/
	int c = 5;
}


void fooB(int* jptr) {

	/*Print the value and address of the integer pointed to by jptr*/
	printf("\nValue of x in fooB: %d", *jptr);
	printf("\nAddress of x in fooB: %p", (void*)jptr);

	/*Decrement the address by 1 pointed to by jptr using jptr */
	jptr -= 1;

	/*Print the address of jptr itself*/
	printf("\nAddress of jptr in fooB: %p", (void*)&jptr);
}


int main() {
	
	/*Declare an integer x and initialize it randomly to a value in [0,10]*/
	int x;
	//generate a seed for the rand function
	srand(time(0));
	x = (rand() % 11);

	/*Print the value and address of x*/
	printf("Value of x in main: %d", x);
	printf("\nAddress of x in main: %p", (void*)&x);

	/*Call fooA() with the address of x*/
	fooA(&x);

	/*Print the value of x*/
	printf("\nValue of x in main: %d", x);
	/*Question: The value of x is different than when it was first
	 * printed. It has been increased by 5. The pointer that was 
	 * being used in fooA was  pointing to x's address on the stack
	 * so when it increment the value at the address know as x, the
	 * value of x held by x was changed.
	 */

	/*Call fooB() with the address of x*/
	fooB(&x);

	/*Print the value and address of x*/
	printf("\nValue of x in main: %d", x);
	printf("\nAddress of x in main: %p\n", (void*)&x);	
	
	/*Question: the vlaues are not changed during the call to fooB,
	 * changing the address that the pointer points to has no affect
	 *  over the variable x, or the address that holds it. THe pointer
	 * isnt used in anyway to change the value of x.
	 */

	return 0;
}
