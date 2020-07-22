/* CS261- Assignment 1 - Q.1*/
/* Name: Lachlan Sinclair	
 * Date: 4/11/2019
 * Solution description: Generate 10 students, provide them
 * with unique random ids, assign them random scores, and generate
 * a basic report with the results.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student* array = malloc(10 * sizeof(struct student));
     
     /*Return the pointer*/
	return array;
}
//simple swapping function
void swap(int *n, int *m)
{
	int temp = *n;
	*n = *m;
	*m = temp;
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/

	int idArray[10] = { 1,2,3,4,5,6,7,8,9,10 };

	srand(time(NULL));
	//implement the Yates shuffle to radomize the array
	for (int i = 9; i > 0; i--) {
		
		int x = (rand() % (i));
		swap(&idArray[i], &idArray[x]);
	}
	//apply the random ids and generate/assign random scores
	for (int j=0; j < 10; j++)
	{
		students[j].id = idArray[j];
		students[j].score = (rand() % 101) + 0;
	}
		
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	for (int i = 0; i < 10; i++)
	{
		printf("Student ID:%d", students[i].id);
		printf(" Score: %d", students[i].score);
		printf("\n");
	}

}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
	int  max = students[0].score, 
		min = students[0].score, total = students[0].score;;
	double average;

	//use simple logic to find the max, min and total
	for (int i = 1; i < 10; i++)
	{
		total += students[i].score;
		if (students[i].score < min)
		{
			min = students[i].score;
		}
		if (students[i].score > max)
		{
			max = students[i].score;
		}
	}
	//display the results
	average = total / 10.00;
	printf("Maximum Score: %d", max);
	printf("\nMinimum Score: %d", min);
	printf("\nAverage Score: %f\n", average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	if (stud != 0) {
		free(stud);
	}
}

int main(int argc, const char * argv[]){
    struct student* stud = NULL;
    
    /*Call allocate*/
	stud = allocate();

    /*Call generate*/
	generate(stud);
    
    /*Call output*/
	output(stud);
    
    /*Call summary*/
	summary(stud);
    
    /*Call deallocate*/
	deallocate(stud);

    return 0;
}

