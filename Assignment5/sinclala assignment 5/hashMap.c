/***********************************************************
* Author: Lachlan Sinclair
* Email: Sinclala@oregonstate.edy
* Date Created: 6/3/2019
* Filename: hashmap.c
*
* Solution description: implements a hash map based off of 
* the skeleteon files provided, it uses the hash_function
* macro to hash values.
************************************************************/


#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
	assert(map != 0);
	int capacity = map->capacity;
	struct HashLink *temp = malloc(sizeof(HashLink*));
	struct HashLink *prev = malloc(sizeof(HashLink*));

	for (int i = 0; i < capacity; i++)
	{
		temp = map->table[i];
		while (temp != 0)
		{
			prev = temp;
			temp = temp->next;

			hashLinkDelete(prev);
		}
	}
	map->size = 0;

}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
	assert(map != 0);
	int capacity = map->capacity;

	int bucket = HASH_FUNCTION(key)%capacity;
	if (bucket < 0)bucket += capacity;

	struct HashLink *temp = map->table[bucket];

	while (temp != 0)
	{
		if (strcmp(temp->key, key) == 0)
		{
			return &(temp->value);
		}
		temp = temp->next;
	}
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
	/* Create new table with twice the size */
	struct HashMap *newTable = hashMapNew(capacity);
	struct HashLink* current;
	/* Loop through old table and traverse links. Add value to new table */
	for (int i = 0; i < map->capacity; i++) {
		current = map->table[i];
		while (current != NULL) {
			hashMapPut(newTable, current->key, current->value);
			current = current->next;
		}
	}
	/* Delete old hash table. Set old table value equal to new table. */
	//free(map->table);
	//free(map);
	//hashMapCleanUp(map);

	//map = newTable;
	hashMapCleanUp(map);

	map->table = newTable->table;
	map->capacity = newTable->capacity;
	map->size = newTable->size;

	newTable = 0;
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
	assert(map != 0);
	int capacity = map->capacity;

	int bucket = HASH_FUNCTION(key) % capacity;
	if (bucket < 0)bucket += capacity;

	struct HashLink *temp = map->table[bucket];
	//see if a value can just be replaced
	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
		{
			temp->value = value;
			return;
		}
		temp = temp->next;
	}


	map->size++;
	if (hashMapTableLoad(map) >= MAX_TABLE_LOAD)
	{
		int newCap = map->capacity * 2;
		resizeTable(map, newCap);
		map->size++;
		bucket = HASH_FUNCTION(key) % map->capacity;
		if (bucket < 0) 
		{
			bucket += map->capacity;
		}
	}
	//if (map->size == 0)map->size++;

	struct HashLink *newLink = hashLinkNew(key, value, map->table[bucket]);
	map->table[bucket] = newLink;


}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
	assert(map != 0);
	int capacity = map->capacity;
	int bucket = HASH_FUNCTION(key) % capacity;

	struct HashLink *temp;
	struct HashLink *prev;

	temp = map->table[bucket];
	//prev = map->table[bucket];
	prev = NULL;

	while (temp != 0)
	{
		if (strcmp(temp->key, key) == 0)
		{
			if (prev==NULL)
			{
				map->table[bucket] = temp->next;
				free(temp->key);
				free(temp);
				map->size--;
				
			}
			else {
				prev->next = temp->next;
				free(temp->key);
				free(temp);
				map->size--;
			}
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement

	assert(map != 0);
	int capacity = map->capacity;

	int bucket = HASH_FUNCTION(key) % capacity;
	if (bucket < 0)bucket += capacity;

	struct HashLink *temp = map->table[bucket];

	while (temp != 0)
	{
		if (strcmp(temp->key, key)==0)
		{
			return 1;
		}
		temp = temp->next;
	}
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
	assert(map != 0);
	return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
	assert(map != 0);
	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
	assert(map != 0);
	int capacity = map->capacity;
	int empties = 0;

	for (int i = 0; i < capacity;i++)
	{
		if (map->table[i] == NULL)
		{
			empties++;
		}
	}
	
    return empties;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
	float links =(int)hashMapSize(map);
	float buckets=(int)hashMapCapacity(map);

	return links / buckets;

}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
  // FIXME: implement
	int capacity = map->capacity;
	struct HashLink *temp;

	for (int i = 0; i < capacity; i++)
	{
		temp = map->table[i];
		if (temp != 0)
		{
			printf("\nBucket %d -> ", i);
		}
		while (temp != 0)
		{
			printf("(%s, %d)->", temp->key, temp->value);
			temp = temp->next;
		}
	} 
}
