
/* 
Project         : Hash Utility
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

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define HASH_INIT_CAPACITY 8	/* initial hay capacity */
#define HASH_INCR_FACTOR 0.2f	/* auto-increment hay capacity */


typedef struct _HASH_KV {
	char *key;
	void *value;
	struct _HASH_KV *next;
} HASH_KV;

typedef struct _HASH {
	unsigned long size;
	HASH_KV *data;
} HASH, *PHASH;



void cleanUp () {
	Sleep(5000);
}


bool empty (HASH *head) {
	if (head == NULL) {
		return false;
	} else {
		return true;
	}
}

void hash_set (HASH *h, char *k, void *v) {
	if (h->data == NULL) {
		h->data = malloc(sizeof(HASH_KV));
		//strcpy(h->data->key, k);
		h->data->key = k;
		h->data->value = v;
		h->data->next = NULL;
		h->size++;
	} else {
		HASH_KV *t = h->data;
		
		while (t != NULL) {
			//printf("%s: %s\n", t->key, t->value);
			if (strcmp(t->key, k) == 0) {
				t->value = v;
				return;
			}
			t = t->next;
		}
		
		if (t == NULL) {
			//t = t->next;
			t = malloc(sizeof(HASH_KV));
			t->key = k;
			t->value = v;
			t->next = h->data;
			h->data = t;
			h->size++;
		}
	}
}


void hash_remove (HASH *h, char *k) {
	bool found = false;
	HASH_KV *t;
	HASH_KV *prev = h->data;
	HASH_KV *curr = h->data->next;
	
	if (curr == NULL) {
		if (strcmp(prev->key, k) == 0) {
			//puts(k);
			free(prev);
			prev = NULL;
		}
		return;
	}
	
	while (curr != NULL && prev != NULL) {
		if (strcmp(curr->key, k) == 0) {
			t = curr;
			prev->next = curr->next;
			free(t);
			return;
		}
		curr = curr->next;
	}
	
	
}

HASH hash_new () {
	HASH h;
	h.size = 0;
	h.data = NULL;
	return h;
}

int main () {
	HASH h = hash_new();
	hash_set(&h, "ccc", "1");
	hash_set(&h, "a", "1");
	
	hash_remove(&h, "ccc");
	//hash_set(&h, "aaa", "1");
	
	HASH_KV *temp= h.data;
	while (temp != NULL) {
		//printf("%s: %s\n", temp->key, temp->value);
		temp = temp->next;
	}
	//puts(h.data->key);
	
	
	//free(h);
	
	
	
	//atexit(cleanUp);
	

	//system("pause");
	return 0;
}













