/*Tobescu Dalya-Alexandra-Grupa 311CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "linked_list.h"

List* CreateList(ssize_t data_size)
{
    List* ll;
    ll = malloc(sizeof(*ll));
    if(ll == NULL) {
        printf("ALocarea nu a reusit");
        return NULL;
    }
    ll->head = NULL;
    ll->data_size = data_size;
    ll->size = 0;
    return ll;
}

void AddNode(List* list, ssize_t n, const void* new_data)
{
    Node *prev = NULL, *curr = NULL;
    Node* new_node = NULL;
    if (!list) {
        return;
    }
    if (n > list->size) {
        n = list->size;
    }
    curr = list->head;
    prev = NULL;
    while (n > 0) {
        prev = curr;
        curr = curr->next;
        --n;
    }
    new_node = malloc(sizeof(*new_node));//aloc memorie pentru nodul pe care il introduc
    if(new_node == NULL) 
        printf("Alocarea nu a reusit");
        new_node->data = malloc(list->data_size);
    if(new_node->data == NULL) 
        printf("Alocarea nu a reusit");
        memcpy(new_node->data, new_data, list->data_size); //copiem datele primite ca parametru in nodul nostru
        new_node->next = curr;
    if (prev == NULL) {
        list->head = new_node;  
    } else {
        prev->next = new_node;
    }
    list->size++; //crestem marimea listei deoarece am mai adaugat un nod
}

Node* RemoveNode(List* list, ssize_t n)
{
    Node *prev, *curr;
    if (!list || !list->head) {
        return NULL;
    }
    curr = list->head; //pointam catre primul element din lista
    prev = NULL;
    while (n > 0) {//parcurgem toata lista si eliminam fiecare element
        prev = curr;
        curr = curr->next; 
        --n;
    }
    if (prev == NULL) {
        /* Adica n == 0. */
        list->head = curr->next;  
    } else {
        prev->next = curr->next;
    }
    list->size--; 
    return curr;
}

void FreeList(List** list)
{
    Node* currNode;
    if (!list || !*list) {
        return;
    }
    while ((*list)->size > 0) {
        currNode = RemoveNode(*list, 0); //eliminam fiecare nod din lista pana cand se termina lista
        free(currNode->data);
        currNode->data = NULL;
        free(currNode);
        currNode = NULL;
    }
    free(*list);
    *list = NULL;
}

Node* GetNode(List* list, ssize_t n)
{
    if (!list || n >= list->size) //daca lista este nula
        return NULL;
    Node* curr = list->head;
    while (n--) {//cautam nodul
        curr = curr->next; 
    }
    return curr;
}
//functii pentru sortarea sublistelor 
void SwapNodes(List* list, ssize_t n1, ssize_t n2)
{
    Node* node1 = GetNode(list, n1);
    Node* node2 = GetNode(list, n2);
    void* aux = node1->data;
    node1->data = node2->data;
    node2->data = aux;
}

void SortList(List* list, int (*compare_func)(void*, void*))
{
    for (ssize_t i = 0; i < list->size - 1; i++) {
        for (ssize_t j = i + 1; j < list->size; j++) {
            if (compare_func(GetNode(list, i)->data, 
                             GetNode(list, j)->data) > 0) {
                SwapNodes(list, i, j);
            }
        }
    }
}
