#include "safe_pointers.c"

typedef struct test_struct{
    int num;
    char* array;
} test;
int main(int argc, char** argv)
{
    p* pointer = safe_malloc(sizeof(test), "test");
    

    return EXIT_SUCCESS;
}