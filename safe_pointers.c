#include "safe_pointers.h"



p* create_node(void* pointer, char* name){
    p* node = (p*) malloc(sizeof(p));
    if (node == NULL){
        log_error("malloc failed when creating a node");
        return POINTER_MALLOC_FAIL;
    }
    node->p = pointer;
    node->name = name;
    node->next = NULL;
    return node;
}

int initialize_safer_pointers(){
    p_list* list = (p_list*) malloc(sizeof(p_list));
    if (list == NULL){
        log_error("malloc failed when initialising the node lists");
        return POINTER_ERROR;
    }
    list->head = NULL;
    list->size = 0;
    POINTER_LIST = list;
    return POINTER_SUCCESS;
}
void exit_safer_pointers(){
    if (POINTER_LIST->size == 0 && POINTER_LIST->head == NULL){
        fprintf(POINTER_INFO_STD, "[SUCCESS] POINTERS : %s\n", "All pointers where freed");
        free(POINTER_LIST);
        return;
    }
    while (POINTER_LIST->size > 0){
        fprintf(POINTER_INFO_STD, "[FAILURE] POINTERS : Unfreed pointer : %s\n", POINTER_LIST->head->name);
        safe_free(POINTER_LIST->head);
    }
    free(POINTER_LIST);
    POINTER_LIST = NULL;

}
p* safe_malloc(size_t size, char* name){

    void* pointer = malloc(size);
    if (pointer == NULL){
        log_error("malloc failed for a safe malloc");
        return POINTER_MALLOC_FAIL;
    }
    p* node = create_node(pointer, name);
    if (node == POINTER_MALLOC_FAIL){
        return node;
    }
    append_node(node);
    return node;
}

int safe_free(p* pointer){
    if (pointer == NULL || pointer == POINTER_MALLOC_FAIL){
        return POINTER_INVALID_INPUT;
    }
    free(pointer->p);
    int res = pop_node(pointer);
    if (res == POINTER_SUCCESS){
        free(pointer);
    }
    return res;
}
void append_node(p* new_node){
    if (POINTER_LIST->head == NULL){
        POINTER_LIST->head = new_node;
        POINTER_LIST->size++;
        return;
    }

    p* current = POINTER_LIST->head;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = new_node;
    POINTER_LIST->size++;
}
int pop_node(p* node) {
    if (POINTER_LIST->size == 0 || POINTER_LIST->head == NULL) {
        log_error("Trying to remove a node from an empty list");
        return POINTER_INVALID_INPUT;
    }
    if (node == POINTER_LIST->head) {
        POINTER_LIST->head = POINTER_LIST->head->next;
        POINTER_LIST->size--;
        return POINTER_SUCCESS;
    }
    p* current = POINTER_LIST->head;
    p* prev = NULL;
    while (current != NULL && current != node) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return POINTER_NOT_FOUND;
    }
    prev->next = current->next;
    POINTER_LIST->size--;
    
    return POINTER_SUCCESS;
}
void display_safe_pointers() {
    p* temp = POINTER_LIST->head;
    fprintf(POINTER_INFO_STD,"[");
    while (temp->next != NULL) {
        fprintf(POINTER_INFO_STD,"\"%s\", ", temp->name);
        temp = temp->next;
    }
    fprintf(POINTER_INFO_STD,"\"%s\"]\n", temp->name);
}