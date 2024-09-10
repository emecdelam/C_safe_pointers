#include <assert.h>
#include <stdio.h>
#define TUNIT_IMPLEMENTATION
#include "tunit.h"
#include "safe_pointers.c"

typedef struct{
    int a;
    bool b;
} test_struct;

void test_create_node()
{
    safe_pointer* pointer = create_node(malloc(sizeof(test_struct)), "pointer to test_struct");
    t_assert_str_eq(pointer->name, "pointer to test_struct");
    t_assert_void((void*)pointer->p, !=, NULL);
    t_assert_void((void*)pointer->next, == , NULL);
    free(pointer->p);
    free(pointer);
}

void test_initialize_safer_pointers()
{
    t_assert_int(POINTER_SUCCESS, == , initialize_safer_pointers());
    t_assert_void((void*) POINTER_LIST, != , NULL);
    t_assert_int(POINTER_LIST->size, == , 0);
    free(POINTER_LIST);
}
void test_append_node()
{
    //t_assert_int(POINTER_SUCCESS, == , initialize_safer_pointers());
    //t_assert_void((void*) POINTER_LIST, != , NULL);
    /*safe_pointer* pointer1 = create_node(malloc(sizeof(test_struct)), "pointer1 to test_struct");
    safe_pointer* pointer2 = create_node(malloc(sizeof(test_struct)), "pointer2 to test_struct");
    safe_pointer* pointer3 = create_node(malloc(sizeof(test_struct)), "pointer3 to test_struct");

    append_node(pointer1);
    t_assert_int(POINTER_LIST->size, == , 1);
    append_node(pointer2);
    t_assert_int(POINTER_LIST->size, == , 2);
    append_node(pointer3);
    t_assert_int(POINTER_LIST->size, == , 3);
    t_assert_void(POINTER_LIST->head, == ,(void*) pointer1);

    t_assert_int(POINTER_SUCCESS, == ,safe_free(pointer1));
    t_assert_int(POINTER_SUCCESS, == ,safe_free(pointer2));
    t_assert_int(POINTER_SUCCESS, == ,safe_free(pointer3));*/
    //free(POINTER_LIST);

}
void test_pop_node()
{
    t_assert_int(POINTER_SUCCESS, == , initialize_safer_pointers());
    t_assert_void((void*) POINTER_LIST, != , NULL);
    safe_pointer* pointer1 = create_node(malloc(sizeof(test_struct)), "pointer1 to test_struct");
    safe_pointer* pointer2 = create_node(malloc(sizeof(test_struct)), "pointer2 to test_struct");
    safe_pointer* pointer3 = create_node(malloc(sizeof(test_struct)), "pointer3 to test_struct");

    append_node(pointer1);
    append_node(pointer2);
    append_node(pointer3);
    display();
    t_assert_void(POINTER_LIST->head, == ,(void*) pointer1);
    t_assert_int(POINTER_LIST->size, == , 3);
    t_assert_int(POINTER_SUCCESS, == ,pop_node(pointer1));
    display();
    t_assert_int(POINTER_LIST->size, == , 2);
    t_assert_int(POINTER_SUCCESS, == ,pop_node(pointer3));
    display();
    t_assert_int(POINTER_LIST->size, == , 1);
    t_assert_int(POINTER_SUCCESS, == ,pop_node(pointer2));
    display();
    t_assert_int(POINTER_LIST->size, == ,0);
    free(pointer1->p);
    free(pointer1);
    free(pointer2->p);
    free(pointer2);
    free(pointer3->p);
    free(pointer3);
}

int main(int argc, char** argv)
{
    //testsuite_t* create_node = t_registerTestSuite("node creation");
    //t_addTestToSuite(create_node, "Create node", test_create_node);

    //testsuite_t* initialize = t_registerTestSuite("iniatialize the pointers list");
    //t_addTestToSuite(initialize, "init safer pointers", test_initialize_safer_pointers);

    testsuite_t* append_pop = t_registerTestSuite("append and pop");
    t_addTestToSuite(append_pop, "append a node to the list", test_append_node);
    //t_addTestToSuite(append_pop, "pop a node from the list", test_pop_node);

    return t_runSuites(argc, argv);
}