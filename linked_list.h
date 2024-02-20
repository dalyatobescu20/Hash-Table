#pragma once

// Structure for a node in the linked list
typedef struct Node Node;
struct Node {
    void* data; // Address of the data
    Node* next; // Address of the next node
};

// Structure for the linked list
typedef struct {
    Node* head; // Pointer to the first element in the list
    ssize_t data_size; // Size of the data address
    ssize_t size; // Size of the list
} List;

// Structure for a list of words with the same length
typedef struct {
    ssize_t w_len; // Length of the word
    List* list; // List of words with the same length
} word_list;

// Structure for a word
typedef struct {
    ssize_t count; // Frequency of the word
    char* string; // The word itself
} Word;

// Function prototypes
List* CreateList(ssize_t data_size);
void AddNode(List* list, ssize_t n, const void* new_data);
Node* GetNode(List* list, ssize_t n);
Node* RemoveNode(List* list, ssize_t n);
void FreeList(List** pp_list);
void SwapNodes(List* list, ssize_t n1, ssize_t n2);
void SortList(List* list, int (*compare_func)(void*, void*));
