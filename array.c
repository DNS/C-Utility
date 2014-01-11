
/* 
Project         : Array Utility
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
//#include <apr_tables.h>

#define ARRAY_INIT_CAPACITY 8	/* initial array capacity */
#define ARRAY_INCR_FACTOR 0.2f	/* auto-increment array capacity */

typedef struct _ARRAY {
	void **values;
	unsigned long size;
	unsigned long capacity;
} ARRAY, *PARRAY;

void array_push_internal (ARRAY *arr, void *p) {
	unsigned long previous_size = arr->size;
	
	if (arr->size >= arr->capacity) {
		//puts("bigger");
		/*void **tmp = malloc(arr->capacity * sizeof(void *));
		memmove(tmp, arr->values, previous_size * sizeof(void *));
		//printf("tmp: %d\n", tmp[0]);
		free(arr->values);
		arr->values = malloc((previous_size + (unsigned long) previous_size * ARRAY_INCR_FACTOR) * sizeof(void *));
		
		memmove(arr->values, tmp, previous_size * sizeof(void *));
		free(tmp);
		
		arr->capacity = previous_size + (unsigned long) previous_size * ARRAY_INCR_FACTOR;
		*/
		arr->values = realloc(arr->values, (previous_size + (unsigned long) previous_size * ARRAY_INCR_FACTOR)  * sizeof(void *));
		arr->capacity = (previous_size + (unsigned long) previous_size * ARRAY_INCR_FACTOR);
	}
	arr->values[arr->size] = p;
	arr->size += 1;
	
	
}

void array_optimize (ARRAY *arr) {
	// TODO
	// called every array_pop()
}

void array_pop (ARRAY *arr) {
	arr->size -= 1;
}

ARRAY *array_new () {
	ARRAY *arr;
	arr = malloc(sizeof(ARRAY));
	arr->values = malloc(ARRAY_INIT_CAPACITY * sizeof(void *));	  // automatically gets bigger when array_push()
	arr->capacity = ARRAY_INIT_CAPACITY;
	arr->size = 0;
	return arr;
}

void array_destroy (ARRAY *arr) {
	free(arr->values);
	free(arr);
}

void *array_get (ARRAY *arr, unsigned long index) {
	return arr->values[index];
}


unsigned long array_count (ARRAY *arr ) {
	return arr->size;
}

#define array_push(arr, value) array_push_internal(arr, (void *) value)

void cleanUp () {
	Sleep(5000);
}

int main () {
	ARRAY *arr;
	int x, i;
	x = 123;
	arr = array_new();
	for (i=0; i<3.0e+8; i++) { // 3.0e+8
		array_push(arr, (void *) i);
		//printf("%d\n", array_get(arr, i));
	}
	
	//asm ("");

	puts("MID");
	fflush(NULL);
	
	for (i=0; i<array_count(arr); i++) {
		//printf("%d\n", array_get(arr, i));
		//fflush(NULL);
		//test();
	}

	
	puts("END");
	fflush(NULL);
	
	atexit(cleanUp);
	

	//printf("int size: %d\n", sizeof(int));
	//printf("pointer size: %d\n", sizeof(void *));
	//printf("values size: %d\n", sizeof(arr->values));
	
	array_destroy(arr);
	//system("pause");
	return 0;
}













