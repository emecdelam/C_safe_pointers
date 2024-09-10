#include "safe_pointers.c"
#include <stdbool.h>

typedef struct test_struct{
    int num;
    char* array;
} test;
typedef struct test_struct2{
    bool num;
    char* array;
} test_struct;




int main(int argc, char** argv)
{
    // The following tests without considering debug mode, hence the use of safe_malloc instead of _malloc
    initialize_safer_pointers();

    p* _test_pointer1 = safe_malloc(sizeof(test), "_test_pointer1");
    p* _test_pointer2 = safe_malloc(sizeof(test), "_test_pointer2");
    p* _test_struct_pointer3 = safe_malloc(sizeof(test_struct), "_test_struct_pointer3");
    p* _test_struct_pointer4 = safe_malloc(sizeof(test_struct), "_test_struct_pointer4");

    SAFE_CAST(_test_pointer1, test)->array = "test";
    SAFE_CAST(_test_struct_pointer3, test_struct)->array = "test_struct";
    display_safe_pointers();
    safe_free(_test_struct_pointer4);
    safe_free(_test_pointer2);
    safe_free(_test_pointer1);
    safe_free(_test_struct_pointer3);
    exit_safer_pointers();
    initialize_safer_pointers();
    p* _test_struct_pointer = safe_malloc(sizeof(test_struct), "pointer never freed");
    p* _test_struct_pointer2 = safe_malloc(sizeof(test_struct), "pointer2 never freed");
    exit_safer_pointers();

    // here debug mode has a real impact so we use _malloc wich works with or without debug
    initialize_safer_pointers();
    void* str_ = _malloc(sizeof(char)*8, "string example 2");

    _free(str_);
    exit_safer_pointers(); // nothing got added to the list

    initialize_safer_pointers(); // /!\ needed, else the program will segfault due to head being null   

    void* str = _malloc(sizeof(char) * 8, "string example"); // simple allocation for a string

    char* str_casted = SAFE_CAST(str, char);  // /!\ using SAFE_CAST is necessary when using debug mode as it takes care of the cast to the node struct necessary or not
    str_casted[0] = 'T';
    str_casted[1] = 'E';
    str_casted[2] = 'S';
    str_casted[3] = 'T';
    str_casted[4] = '\0';

    _free(str); // don't forget to free, if you don't and debug mode is on, the program will tell you that you forgot to free it


    exit_safer_pointers(); // free the whole list, this is necessary to avoid any memory leaks

    return EXIT_SUCCESS;
}
