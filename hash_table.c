#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include "hash_table.h"

#define MAX_STRING_SIZE	256
#define MIN_STRING_SIZE 3

// Function to compare strings
int compare_function_strings(void *a, void *b) 
{
	char *str1 = (char *)a;
	char *str2 = (char *)b;
	return strcmp(str1, str2);
}

// Hash function for strings
ssize_t hash_function_string(void *string)
{
	if(((char*)string)[0] >= 'A' && ((char*)string)[0] <= 'Z')  
		return ((char*)string)[0] + 32 - 'a';
	return ((char*)string)[0] - 'a';
}

// Function to create a hash table
HashTable* ht_create(ssize_t size, ssize_t (*hash_function)(void*), ssize_t data_size)
{
	HashTable* new = calloc(1, sizeof(HashTable));
	if(!new) {
	     printf("Allocation failed");
		 return NULL;
	}
    new->v = calloc(1, size * sizeof(List*));
	if(!new->v) {
	    printf("Allocation failed");
		return NULL;
	}
	for (ssize_t i = 0; i < size; i++) {
		new->v[i] = CreateList(sizeof(data_size));
		if(!new->v[i]) {
		printf("Allocation failed");
		return NULL;
		}
	}
	new->size = size;
	new->hash_function = hash_function;
	return new;
}

// Function to compare words within sublist
int compare_words(void* w1, void* w2)
{
	if (((Word*)w1)->count > ((Word*)w2)->count)
		return -1;
	if (((Word*)w1)->count < ((Word*)w2)->count)
		return 1;
	return strcmp(((Word*)w1)->string, ((Word*)w2)->string);
}

// Function to insert a word into the hash table
void insert_word(HashTable* ht, Word* w)
{
	if (!ht || !w)
		return;
	if (strlen(w->string) < MIN_STRING_SIZE) {
        free(w->string);
		return;
	}
	if (w->string[0] < 57 && w->string[0] > 48) {
		free(w->string);
		return;
	}	
	List* tmp = ht->v[ht->hash_function(w->string)];
	Node* curr = tmp->head;   
	ssize_t pos = 0;
	while (curr) {
		if ((*(word_list**)curr->data)->w_len == strlen(w->string))
			break;
		else if ((*(word_list**)curr->data)->w_len < strlen(w->string))
			pos++;
		curr = curr->next;
	}
	if (!curr) {
		word_list *new_word_list;
		new_word_list = calloc(1, sizeof(word_list));
		new_word_list->list = CreateList(sizeof(Word));
		new_word_list->w_len = strlen(w->string);
		AddNode(new_word_list->list, 0, w);
		AddNode(tmp, pos, &new_word_list);
	} else {
		List* curr_word_list = (*(word_list**)curr->data)->list;
		Node* curr_word = curr_word_list->head;
		while (curr_word) {
			if (!strcmp(((Word*)curr_word->data)->string, w->string)) {
				((Word*)curr_word->data)->count++;
				free(w->string);
				break;
			}
		curr_word = curr_word->next;
		}
		if (!curr_word) {
			AddNode(curr_word_list, 0, w);
		}
		SortList(curr_word_list, compare_words);
	}
}

// Function to destroy the hash table
int Distrugere(HashTable *ht)
{
    List** bucket;
    if(!ht)
		return -1; 
	for(ssize_t i = 0; i < ht->size; i++) {
		List* curr_list = ht->v[i];
		for (ssize_t j = 0; j < curr_list->size; j++) {
			Node* curr_node = GetNode(curr_list, j);
			word_list* curr_word_list =*(word_list**)curr_node->data; 
			List* curr_sublist = curr_word_list->list;
			for(ssize_t k = 0; k < curr_sublist->size; k++) {
				Node* tmp = GetNode(curr_sublist, k);
				free(((Word*)tmp->data)->string);
			}
			FreeList(&curr_sublist);
			free(curr_word_list);
		}
        FreeList(&curr_list);
	}
	free(ht->v);
	free(ht);
    return 0;
}

// Function to print the hash table
void print_ht(HashTable* ht)
{
	for(ssize_t i = 0; i < ht->size; i++) {
		List* tmp = ht->v[i];
		if (tmp->size) {  
		   printf("pos %zu: ", i);
		for(ssize_t j = 0; j < tmp->size; j++) {
			word_list* curr_word_list = *(word_list**)GetNode(tmp, j)->data; 
			printf("(%zu:", curr_word_list->w_len);
            for (ssize_t k = 0; k < curr_word_list->list->size; k++) {
				if (k)
				printf(", ");
                Node* curr_word = GetNode(curr_word_list->list, k);
				printf("%s/%zu", ((Word*)curr_word->data)->string,
									 ((Word*)curr_word->data)->count);
			}
			printf(")");
		}
        	printf("\n");
		}
	}
}

// Function to print specific elements of the hash table
void print2_ht(HashTable* ht, char* c, ssize_t n)
{   
    bool print_newline = 0;
	List* list = ht->v[ht->hash_function(c)];
	for(ssize_t i = 0; i < list->size; i++) {
		word_list* curr_word_list = *(word_list**)GetNode(list, i)->data; 
		if(curr_word_list->w_len == n) {
			printf("(%zu:", n); 
			List* tmp = curr_word_list->list;
			for (ssize_t j = 0; j < tmp->size; j++) {
				if (j)
					printf(", ");
	     Word* curr_word = GetNode(tmp, j)->data;
				printf("%s/%zu", curr_word->string, curr_word->count);
				print_newline = 1;
			}
			printf(")");
			break;
		}
	}
	if(print_newline)
	printf("\n");
}

// Function to print specific elements of the hash table based on maximum count
void print3_ht(HashTable* ht, ssize_t max_count)
{
	for(ssize_t i = 0; i < ht->size; i++) {
		bool print_pos = 1;
		bool print_len = 1;
		bool print_newline = 0;
		List* tmp = ht->v[i];
		if (tmp->size) {
		for(ssize_t j = 0; j < tmp->size; j++) {
			word_list* curr_word_list = *(word_list**)GetNode(tmp, j)->data;
	        ssize_t printed_words = 0;
		    for(ssize_t k = 0; k < curr_word_list->list->size; k++) {
				if (printed_words)
					printf(", ");
					Word* curr_word = GetNode(curr_word_list->list, k)->data;
					if(curr_word->count <= max_count) {
						if (print_pos) {
							printf("pos%zu: ", i);
							print_pos = 0;
						}
						if (print_len) {
							printf("(%zu: ", curr_word_list->w_len);
							print_len = 0;
						}
						printf("%s/%zu", curr_word->string, curr_word->count);
						printed_words++;
						print_newline = 1;
					}
				}
	            print_len = 1;
				if (printed_words)
					printf(")");
			}
			if (print_newline)
				printf("\n");
		}
	}
}
