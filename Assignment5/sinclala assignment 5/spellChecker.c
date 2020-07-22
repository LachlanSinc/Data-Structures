/***********************************************************
* Author: Lachlan Sinclair
* Email: Sinclala@oregonstate.edy
* Date Created: 6/3/2019
* Filename: spellChecker.c
*
* Solution description: Uses the hash map and levenshtein distance
* to spell check user input and recomend possible words if the 
* provided word is misspelled.
************************************************************/


#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/**
 * Returns the lowest of three integers
 * @param 3 ints to be compared
 * @return the minnium of three values
 */

int minimum(int a, int b, int c)
{
	int min = a;
	if (b < min) min = b;
	if (c < min) min = c;
	return min;
}

/**
 * Calculates and returns the levenshtein distance between two strings using the 
 * iterative method with two matrix rows.
 * refrenced: https://en.wikipedia.org/wiki/Levenshtein_distance 
 * @param 2 strings
 * @return int that is the levenshtein distance
 */


int levenshtein(char *key, char *tempKey) {


	unsigned int keylen, tempKeylen, x, y, prevVal, lastVal;
	keylen = strlen(key);
	tempKeylen = strlen(tempKey);
	//dynamically allocate the array
	unsigned int *column = malloc((keylen + 1) * sizeof(int));

	for (y = 1; y <= keylen; y++)
	{
		column[y] = y;
	}

	for (x = 1; x <= tempKeylen; x++) {
		column[0] = x;
		for (y = 1, prevVal = x - 1; y <= keylen; y++) {
			lastVal = column[y];
			column[y] = minimum(column[y] + 1, column[y - 1] + 1, prevVal + (key[y - 1] == tempKey[x - 1] ? 0 : 1));
			prevVal = lastVal;
		}
	}

	int temp = (column[keylen]);
	free(column);

	return temp;
}


/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement

	char *current = nextWord(file);
	while (current != NULL)
	{

		hashMapPut(map, current, 254);
	
		current = nextWord(file);
	}
}

void levenBucket(struct HashMap *map, char * key)
{
	struct HashLink *temp; 

	int keyLen = strlen(key);
	//int a = hashMapEmptyBuckets(map);
	//printf("%d\n", a);

	int count = 0;
	char nearStrings[5][256];
	int nearValues[5];
	nearValues[0] = nearValues[1] = nearValues[2] = nearValues[3] = nearValues[4] = keyLen;

	//if (keyLen < 5) factor = 3;

	for (int i = 0; i < map->capacity; i++)
	{
		temp = map->table[i];
		while (temp != NULL)
		{
			//tempLen = strlen(temp->key);
			//temp->value = LevenshteinDistance(key, keyLen, temp->key, tempLen);
			temp->value =  levenshtein(key, temp->key);

			for (int j = 0; j < 5; j++)
			{
				if (temp->value < nearValues[j])
				{
					if (temp->value < 2)
					{
						count++;
					}
					nearValues[j] = temp->value;
					strcpy(nearStrings[j], temp->key);
					break;
				}
			}
			temp = temp->next;		
		}
		if (count > 3)
		{
			i = map->capacity;
		}
	}
	//if code reaches here 5 values were not found with only one difference
	printf("%s, %s, %s, %s, %s", nearStrings[0], nearStrings[1], nearStrings[2], nearStrings[3], nearStrings[4]);
}


/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
	char inputLower[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
		strcpy(inputLower, inputBuffer);

		for (int i = 0; inputBuffer[i]; i++) {
			inputLower[i] = tolower(inputBuffer[i]);
		}
        
		if (strcmp(inputLower, "quit") == 0)
		{
			quit = 1;
			continue;
		}

        // Implement the spell checker code here..
		if (hashMapContainsKey(map, inputLower))
		{
			printf("The inputted word %s is spelled correctly\n", inputBuffer);
		}
		else 
		{
			printf("The inputted word %s is spelled incorrectly\n", inputBuffer);
			printf("Did you mean ");
			levenBucket(map, inputLower);
			printf("?\n");
		}     
    }
    
    hashMapDelete(map);
    return 0;
}