/* CS261- Assignment 1 - Q.3*/
/* Name: Lachlan Sincalir
 * Date: 4/15/2019
 * Solution description: Recieves input from the user
 * then if the input was valid will output the result as a 
 * camel cased version. If the input is invalid it will out put
 * that to the console and end the program.
 */

#include <stdio.h>
#include <stdlib.h>


//function to set a portion of a array of chars to a specific char
void setMem(char* ptr, char v, int length) {
	for (int i = 0; i < length; i++) {
		ptr[i] = v;
	}
}


char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
	//+32
	ch -= 32;
	return ch;
}

char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                          
	ch += 32;
	return ch;
}

int stringLength(char s[]) {
   /*Return the length of the string*/
	int length = 0;
	//for (int i = 0; s[i-1] != 0 && i < 100; i++)
	for (int i = 0; s[i] != 0 && i < 100; i++)
		length = i;
	return length+1;
}
/***********************************
* Decription: Removes all non under score and alphabetical
* characters. Retruns true of false depending on if it is a 
* valid string.
***********************************/
int cleanString(char * temp)
{
	int length = stringLength(temp);
	int underScoreFound = 0;
	int lowerFound = 0;
	int upperFound = 0;
	int oldIndex = 0;
	int newIndex = 0;

	//temporary char array to store good characters in
	char *newWord;
	newWord = (char*)malloc(sizeof(char)*length);

	//set all characters to '\0'
	setMem(newWord, '\0', length);

	//make all letters lowercase, and turn spaces into
	//underscores
	for (int i = 0; i < 100; i++)
	{
		if (temp[i] < 91 && temp[i]>64) {
			temp[i] = toLowerCase(temp[i]);
		}
		else if(temp[i]<97 || temp[i]>123){
			temp[i] = 95;
		}
	}
	//loop that uses three bools to insure 3 seperate
	//requirements are met
	while (oldIndex < length)
	{
		//this will find letters after an underscore
		if (temp[oldIndex] > 96 && temp[oldIndex] < 123 && underScoreFound
			&& lowerFound)
		{
			upperFound = 1;
		}
		//finds lower case letters
		else if (temp[oldIndex] > 96 && temp[oldIndex] < 123) {
			lowerFound = 1;
		}
		//finds underscores
		else if (temp[oldIndex] == 95) {
			underScoreFound = 1;
		}
		oldIndex++;
	}
	//check to see if all requirements were met.
	if (!upperFound || !lowerFound || !underScoreFound) {
		//wipe the array
		setMem(temp, '\0', length);
		
		//free the dynamic array
		free(newWord);
		newWord = 0;
		//return with the now empty string
		return 0;
	}
	//reset the bool  values so they can be used in formating
	//the array one last time
	underScoreFound = 0;
	lowerFound = 0;
	for (int i = 0; i < length; i++)
	{
		if (temp[i] == 95 && lowerFound) {
			underScoreFound = 1;
		}
		//valid lower case char
		else if (temp[i] > 96 && temp[i] < 123)
		{
			lowerFound = 1;
			//adds the trailing underscore infront of the new character
			//to be used by the camel case function
			if (underScoreFound) {
				newWord[newIndex] = '_';
				newIndex++;
				newWord[newIndex] = temp[i];
				newIndex++;
				underScoreFound = 0;
			}
			else {
				newWord[newIndex] = temp[i];
				newIndex++;
			}
		}
	}
	//put the correct characters back into the passed array
	setMem(temp, '\0', length);
	for (int i = 0; i < newIndex; i++) {
		temp[i] = newWord[i];
	}
	//clear memory
	free(newWord);
	newWord = 0;
	return 1;
}

void camelCase(char* word){
	/*Convert to camelCase*/
	int length = stringLength(word);
	//boolean section
	int underScoreFound = 0;
	int finalIndex= 0;
	
	//int lowerFound = 0;
	char *newWord;
	newWord = (char*)malloc(sizeof(char)*length);
	setMem(newWord, '\0', length);

	//clear the orginal array to prep it to be refilled	
	for (int j = 0; j < length; j++) {
		if (word[j] == 95) {
			underScoreFound = 1;
		}
		//else for letter chars
		else
		{
			if (underScoreFound) {
				newWord[finalIndex] = toUpperCase(word[j]);
				finalIndex++;
				underScoreFound = 0;
			}
			else {
				newWord[finalIndex] = word[j];
				finalIndex++;
			}
		}
	}
	//puts the new string into word for use in main
	setMem(word, '\0', length);
	for (int i = 0; i < length; i++) {
		word[i] = newWord[i];
	}
	//clear memory
	free(newWord);
	newWord = 0;
}

int main(){

	/*Read the string from the keyboard*/
	char input[100];
	setMem(input, '\0', 100);


	if (fgets(input, 100,stdin)) {

		//converts to the string to lowercase
		//checks to makesure the user inputted a string
		//and that the string is a valid entry
		if (cleanString(input)) {
			/*Call camelCase*/
			camelCase(input);

			/*Print the new string*/
			printf("%s\n", input);
			
		}
		else {
			printf("invalid input string\n");
			//skip the camelCase function if invalid			
		}
				
	}
	//issue entering the string correctly
	else {
		printf("invalid input string\n");
	}
	
	//jumping point to skip some code.
	return 0;
}

