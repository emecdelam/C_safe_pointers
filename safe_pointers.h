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
// Set to 0 to directly call to free without using the list
#define DEBUG_MODE 0
//==================
// Set to 0 to have no warning messages on malloc fails
#define LOG_ERRORS 1
//==================
// Set this variable to whatever std you want to use
#define POINTER_INFO_STD stdout
//==================

#if DEBUG_MODE == 1
    #define SAFE_CAST(pointer, type) ((type*)((p*)(pointer))->p)
#elif DEBUG_MODE == 0
    #define SAFE_CAST(pointer, type) ((type*)(pointer))
#endif


void log_error(char* str){
    if (LOG_ERRORS){
        fprintf(stderr, "[ERROR] POINTERS : %s\n", str);
    }
}





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


int initialize_safer_pointers();
void exit_safer_pointers();
p* safe_malloc(size_t size, char* name);
int safe_free(p* pointer);



void* _malloc(size_t size, char* name);
void _free(void* pointer);

#endif




