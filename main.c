#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "linked_list.h"
#include "hash_table.h"

#define HMAX 26   

int main(int argc, char**argv)
{   FILE* f;
	f = fopen(argv[1], "r");
    if(NULL == f) {
        printf("file can't be opened \n");
        return 0;
    }
    HashTable* ht = ht_create(HMAX, hash_function_string, sizeof(word_list)); 
    char* line = NULL;
    size_t buffer_size = 0;
    while (getline(&line, &buffer_size, f) != -1) {
        line[strcspn(line, "\n")] = '\0'; 
        char* token = strtok(line, " .,");
    if (!strcmp(token, "insert")) {
        token = strtok(NULL, " .,");
        while (token) {
            Word new_word;
            new_word.string = calloc(1, strlen(token) + 1);
            strcpy(new_word.string, token);
            new_word.count = 1;
            insert_word(ht, &new_word);
            token = strtok(NULL, " .,"); 
        }
    } else if (!strcmp(token, "print")) {
            ssize_t argc = 0;
            char** args = calloc(1, 2 * sizeof(*args));
            token = strtok(NULL, " .,");
            while(token) {
              args[argc] = calloc(strlen(token) + 1, 1);
              strcpy(args[argc++], token);
              token = strtok(NULL," .,");
            }  
            if(!argc) {
                print_ht(ht);
            } else if(argc == 1) {
                print3_ht(ht, atoi(args[0]));
            } else if(argc == 2) {
                print2_ht(ht, args[0], atoi(args[1]));
            }
            for(ssize_t i = 0; i < argc; i++)
                free(args[i]);
                free(args);   
        }         
    }   
    Distrugere(ht);
    free(line);
    fclose(f);
}
