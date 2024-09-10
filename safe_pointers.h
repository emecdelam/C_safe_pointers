#ifndef SAFE_POINTER_H
#define SAFE_POINTER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define POINTER_MALLOC_FAIL (void *) -1
#define POINTER_NOT_FOUND 2
#define POINTER_ERROR 1
#define POINTER_SUCCESS 0
#define POINTER_INVALID_INPUT -1



//==================
// Set to 0 to have no warning messages on malloc fails
#define LOG_ERRORS 1

void log_error(char* str){
    if (LOG_ERRORS){
        fprintf(stderr, "[ERROR] POINTERS : %s\n", str);
    }
}
// Set this variable to whatever std you want to use
#define POINTER_INFO_STD stdout


typedef struct node{
    void* p;
    char* name;
    struct node* next;
} p;

typedef struct pointer_list{
    p* head;
    int size;
} p_list;

p_list* POINTER_LIST = NULL;
p* create_node(void* pointer, char* name);
void append_node(p* new_node);
int pop_node(p* node);
int initialize_safer_pointers();
void exit_safer_pointers();
p* safe_malloc(size_t size, char* name);
int safe_free(p* pointer);
#endif




