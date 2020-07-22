/* CS261- Assignment 1 - Q.2*/
/* Name: Lachlan Sinclair
 * Date: 4/15/2019
 * Solution description: Randomly assign 3 integers
 * then pass them to a function that shows how localy scoped
 * variables and pointers will affect objects who have there
 * addresses or values passed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
	int *temp = a;
	a = b;
	b = temp;

    /*Decrement the value of integer variable c*/
	c--;
    
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
	srand(time(NULL));
	int x = (rand() % 11);
	int y = (rand() % 11);
	int z = (rand() % 11);
    /*Print the values of x, y and z*/
	printf("x: %d", x);
	printf("\ny: %d", y);
	printf("\nz: %d", z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
	int result = foo(&x, &y, z);
    
    /*Print the values of x, y and z*/
	printf("\nx: %d", x);
	printf("\ny: %d", y);
	printf("\nz: %d", z);
    
    /*Print the value returned by foo*/
	printf("\nReturned Value: %d\n", result);
    	
    /*Question A: The return value is different than the value of z. During 
     * the function call, z passed its value to foo, which has its own copy
     * of the integer, it then subtracts one and returns that value. The value
     * of z is not changed but the returned value is one less than z so they
     * are different.
     *
     * Question B: No, the pointers in foo are swapped however this does not 
     * impact the values since the pointers are not performing and changes 
     * on the memory they point to, they just swap addresses so they point at
     * the others variable, but proceed to do nothing until the
     * fuction return so the variables are not affected. 
     **/	
    
    return 0;
}
    
    


