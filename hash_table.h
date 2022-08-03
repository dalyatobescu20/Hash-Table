/*Tobescu Dalya-Alexandra -grupa 311CB*/
#pragma once

#include "linked_list.h"

typedef struct {
	List **v;
	ssize_t size;
	ssize_t (*hash_function)(void*);
} HashTable;

int compare_function_strings(void *a, void *b);

int Distrugere(HashTable *ht);

ssize_t hash_function_string(void* string);

HashTable* ht_create(ssize_t size, ssize_t (*hash_function)(void*),
						ssize_t data_size);

int compare_words(void* w1, void* w2);

void insert_word(HashTable* ht, Word* w);

void print_ht(HashTable* ht);

void print2_ht(HashTable* ht, char* c, ssize_t n);

void print3_ht(HashTable* ht, ssize_t max_count);
