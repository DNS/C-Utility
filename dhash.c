
/* 
Project         : Dynamic Hash - Hashed Array Tree
Status          : Complete
Author          : Daniel Sirait <dns@cpan.org>
Copyright       : Copyright (c) 2013 Daniel Sirait
License         : Must be distributed only under the terms of "THE BEER-WARE LICENSE"  (Revision 42):
                 As long as you retain this notice you
                 can do whatever you want with this stuff. If we meet some day, and you think
                 this stuff is worth it, you can buy me a beer in return
Disclaimer      : I CAN UNDER NO CIRCUMSTANCES BE HELD RESPONSIBLE FOR
                  ANY CONSEQUENCES OF YOUR USE/MISUSE OF THIS DOCUMENT,
                  WHATEVER THAT MAY BE (GET BUSTED, WORLD WAR, ETC..).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <tchar.h>
#include <windows.h>

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef DWORD
typedef unsigned long DWORD;
#endif

#ifndef QWORD
typedef unsigned long long QWORD;
#endif


#define ARRAY_BLOCK_CAPACITY 4	/* default size 8 */

typedef struct _ARRAY_BLOCK {
	void **elements;
} ARRAY_BLOCK;

typedef struct _ARRAY {
	ARRAY_BLOCK *blocks;
	DWORD element_size;
	DWORD block_size;
	DWORD capacity;		/* maximum capacity (ARRAY_BLOCK_CAPACITY * block_size) */
} ARRAY, *PARRAY;


ARRAY *array_new () {
	ARRAY *arr;
	arr = malloc(sizeof(ARRAY));
	if (arr == NULL) return NULL;
	arr->blocks = malloc(sizeof(ARRAY_BLOCK));
	arr->blocks[0].elements = malloc(sizeof(void *) * ARRAY_BLOCK_CAPACITY);
	arr->element_size = 0;
	arr->block_size = 1;
	arr->capacity = ARRAY_BLOCK_CAPACITY;
	return arr;
}



void array_add (ARRAY *arr, void *val) {
	DWORD curr_index;
	if (arr->element_size < arr->capacity) {
		curr_index = ARRAY_BLOCK_CAPACITY - (arr->capacity - arr->element_size);
		
		arr->blocks[arr->block_size-1].elements[curr_index] = val;
		arr->element_size++;
	} else {
		arr->blocks = realloc(arr->blocks, (arr->block_size+1) * sizeof(ARRAY_BLOCK));
		arr->blocks[arr->block_size].elements = malloc(sizeof(void *) * ARRAY_BLOCK_CAPACITY);
		
		arr->blocks[arr->block_size].elements[0] = val;
		
		arr->block_size++;
		arr->element_size++;
		arr->capacity += ARRAY_BLOCK_CAPACITY;
	}
}

DWORD array_size (ARRAY *arr) {
	return arr->element_size;
}

void *array_get (ARRAY *arr, DWORD index) {
	DWORD block_index = index / ARRAY_BLOCK_CAPACITY;
	DWORD el_index = index % ARRAY_BLOCK_CAPACITY;
	return arr->blocks[block_index].elements[el_index];
}


bool array_set (ARRAY *arr, DWORD index, void *val) {
	DWORD block_index;
	DWORD el_index;
	
	if (array_size(arr)-1 < index)
		return false;
	
	block_index = index / ARRAY_BLOCK_CAPACITY;
	el_index = index % ARRAY_BLOCK_CAPACITY;
	arr->blocks[block_index].elements[el_index] = val;
	
	return true;
}



void array_remove (ARRAY *arr, DWORD index) {
	DWORD el_index, size, i;
	
	size = array_size(arr);
	
	for (i=index+1; i<size; i++) 
		array_set(arr, i-1, array_get(arr, i));
	
	el_index = index % ARRAY_BLOCK_CAPACITY;
	
	if (el_index == 0) {
		if (arr->block_size > 1) {
			free(arr->blocks[arr->block_size].elements);
			
			arr->block_size--;
			arr->blocks = realloc(arr->blocks, arr->block_size * sizeof(ARRAY_BLOCK));
		}
	}
	
	if (arr->element_size != 0)
		arr->element_size--;
	
}

void array_clear (ARRAY *arr) {
	DWORD i, block_size;
	
	block_size = array_size(arr);
	
	for (i=1; i<arr->block_size; i++)
		free(arr->blocks[i].elements);
	
	arr->blocks = realloc(arr->blocks, 1 * sizeof(ARRAY_BLOCK));
	arr->element_size = 0;
	arr->block_size = 1;
	arr->capacity = ARRAY_BLOCK_CAPACITY;
}


void array_destroy (ARRAY *arr) {
	array_clear(arr);
	free(arr->blocks[0].elements);
	free(arr->blocks);
	free(arr);
}


void array_iterate (ARRAY *arr, void (*callback)(void *val)) {
	DWORD i;
	for (i=0; i<array_size(arr); i++)
		callback(array_get(arr, i));
}

void cetak (void *val) {
	printf("%d\n", val);
}

int main () {
	ARRAY *arr = array_new();
	array_add(arr, (void *) 1);
	array_add(arr, (void *) 2);
	array_add(arr, (void *) 3);
	array_add(arr, (void *) 4);
	array_add(arr, (void *) 5);
	array_add(arr, (void *) 6);
	array_add(arr, (void *) 7);
	array_add(arr, (void *) 8);
	
	//array_set(arr, 1, array_get(arr, 7));
	//printf("%d\n", array_get(arr, 7));
	//array_clear(arr);
	//array_add(arr, (void *) 5);
	
	array_iterate(arr, cetak);
	
	
	
	array_destroy(arr);
	
	
	return 0;
}

