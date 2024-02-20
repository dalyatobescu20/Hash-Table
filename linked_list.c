#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "linked_list.h"

// Function to create a new linked list
List* CreateList(ssize_t data_size)
{
    List* ll;
    ll = malloc(sizeof(*ll));
    if(ll == NULL) {
        printf("Allocation failed");
        return NULL;
    }
    ll->head = NULL;
    ll->data_size = data_size;
    ll->size = 0;
    return ll;
}

// Function to add a new node to the linked list
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
    new_node = malloc(sizeof(*new_node)); // Allocate memory for the new node
    if(new_node == NULL) {
        printf("Allocation failed");
        return;
    }
    new_node->data = malloc(list->data_size); // Allocate memory for the data in the new node
    if(new_node->data == NULL) {
        printf("Allocation failed");
        free(new_node);
        return;
    }
    memcpy(new_node->data, new_data, list->data_size); // Copy the data to the new node
    new_node->next = curr;
    if (prev == NULL) {
        list->head = new_node;  
    } else {
        prev->next = new_node;
    }
    list->size++; // Increment the size of the list
}

// Function to remove a node from the linked list
Node* RemoveNode(List* list, ssize_t n)
{
    Node *prev, *curr;
    if (!list || !list->head) {
        return NULL;
    }
    curr = list->head; // Point to the first node
    prev = NULL;
    while (n > 0) {
        prev = curr;
        curr = curr->next; 
        --n;
    }
    if (prev == NULL) {
        list->head = curr->next;  
    } else {
        prev->next = curr->next;
    }
    list->size--; // Decrement the size of the list
    return curr;
}

// Function to free the memory allocated for the linked list
void FreeList(List** list)
{
    Node* currNode;
    if (!list || !*list) {
        return;
    }
    while ((*list)->size > 0) {
        currNode = RemoveNode(*list, 0); // Remove each node from the list
        free(currNode->data); // Free the memory allocated for the data
        currNode->data = NULL;
        free(currNode);
        currNode = NULL;
    }
    free(*list);
    *list = NULL;
}

// Function to get a node at a specific index in the linked list
Node* GetNode(List* list, ssize_t n)
{
    if (!list || n >= list->size)
        return NULL;
    Node* curr = list->head;
    while (n--) {
        curr = curr->next; // Traverse the list to find the node
    }
    return curr;
}

// Function to swap two nodes in the linked list
void SwapNodes(List* list, ssize_t n1, ssize_t n2)
{
    Node* node1 = GetNode(list, n1);
    Node* node2 = GetNode(list, n2);
    void* aux = node1->data;
    node1->data = node2->data;
    node2->data = aux;
}

// Function to sort the linked list
void SortList(List* list, int (*compare_func)(void*, void*))
{
    for (ssize_t i = 0; i < list->size - 1; i++) {
        for (ssize_t j = i + 1; j < list->size; j++) {
            if (compare_func(GetNode(list, i)->data, GetNode(list, j)->data) > 0) {
                SwapNodes(list, i, j);
            }
        }
    }
}
