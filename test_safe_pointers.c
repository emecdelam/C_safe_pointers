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
    return EXIT_SUCCESS;
}