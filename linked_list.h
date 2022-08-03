/*Tobescu Dalya-Alexandra- grupa 311CB*/
#pragma once

typedef struct Node Node;
struct Node {
    void* data; //adresa informatie
    Node* next;  //adresa urmatoarei celule
};

typedef struct {
    Node* head;  //pointer catre primul elem din lista
    ssize_t data_size; //dimensiunea adresei de informatie
    ssize_t size; //dimensiunea listei
} List;

typedef struct {
    ssize_t w_len;//dimensiunea unui cuvant
    List* list;//lista de cuvinte de aceeasi lungime
}word_list;

typedef struct {
    ssize_t count;//frecventa cuvantului
    char* string;//cuvantul
} Word;

List* CreateList(ssize_t data_size);

void AddNode(List* list, ssize_t n, const void* new_data);

Node* GetNode(List* list, ssize_t n);

Node* RemoveNode(List* list, ssize_t n);

void FreeList(List** pp_list);

void SwapNodes(List* list, ssize_t n1, ssize_t n2);

void SortList(List* list, int (*compare_func)(void*, void*));
