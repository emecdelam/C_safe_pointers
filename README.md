# safe_pointers

> [!WARNING]
> This repository does not make every pointer operation safe, it only allows you to debug and make safer use of pointers

How does it make it safer?

The main goal is not avoid having forgotten non freed pointers that were allocated, it helps that by storing every pointer in a list and at the end of a program freeing every pointer in that list.



A complete exmaple of usage

```c
// The following works with DEBUG_MODE = 0 or 1, when 0, the program is faster and doesn't use a list to check for forgotten allocations

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

initialize_safer_pointers(); //this is necessary here but in practice, you should only use this function once
void* forgotten = _malloc(sizeof(int), "forgotten allocation oops");
exit_safer_pointers();  // this is necessary to get the error message, it should also be used only once
```
has the following output with DEBUG_MODE = 1
```
[SUCCESS] POINTERS : All pointers where freed       // this is due to the two call to initialize_safer_pointers() wich you should only use once
[FAILURE] POINTERS : Unfreed pointer : forgotten allocation oops
```
and no memory leaks because we used `exit_safer_pointers()` wich will free every unfreed pointer
```
==568414== HEAP SUMMARY:
==568414==     in use at exit: 0 bytes in 0 blocks
==568414==   total heap usage: 7 allocs, 7 frees, 1,116 bytes allocated
==568414==
==568414== All heap blocks were freed -- no leaks are possible
```
with debug mode = 0, there are no output but the program leaks, (intentionnaly since we have a forgotten allocation)
```
==568747== LEAK SUMMARY:
==568747==    definitely lost: 4 bytes in 1 blocks
==568747==    indirectly lost: 0 bytes in 0 blocks
==568747==      possibly lost: 0 bytes in 0 blocks
==568747==    still reachable: 0 bytes in 0 blocks
==568747==         suppressed: 0 bytes in 0 blocks
```
this sort of error could have been preventend using the warnings of DEBUG_MODE
## Inclusion

to add it into your project, the main c files are `safe_pointers.c` and `safe_pointers.h`


## Usage
If you plan on using the debug mode and having a fast application without allocations in a list in the background, you can use `_malloc()` and `_free()` with `SAFE_CAST`

When starting a program, you need to call `initialize_safer_pointers()` wich initializes the list correctly in the global variable `p_list* POINTER_LIST`

On exiting a program safely, you need to call `exit_safer_pointers()` wich will print all unfreed pointers and free them for you


For a working example, check the [test](test_safe_pointers.c)



## Utils

For using these helper functions, there are some parameters and utilies

### logging

You can choose to log errors such as malloc fails with the `LOG_ERRORS` definition in the `safe_pointers.h` file, you can also choose a std for the output of infos such as success on exiting in the `POINTER_INFO_STD` definition

### casting

when allocating a struct, you will have to use typecast to allow for autocompletion, the macro `SAFE_CAST` is there to help, it takes care of the issue of uses of debug mode returning either a node with the allocation or directly the allocation

### debug

you can ignore the complete linkedlist part by using `_malloc` and `_free` wich depending of the value of `DEBUG_MODE` (assigned in the header file), this is done to avoid having to use a linked list in production code


## Doc

```c
void* _malloc(size_t size, char* name)
```
a replacement for malloc, using `safe_malloc` if `DEBUG_MODE` == 1, else redirects to the standard malloc except in case of standard malloc error where it changes the error from `NULL` to `POINTER_MALLOC_FAIL`

```c
void _free(void* pointer);
```
a replacement for free, using standard free is `DEBUG_MODE` == 0 else using `safe_free`

```c
int initialize_safer_pointers()
```
returns `POINTER_SUCCESS` or `POINTER_ERROR` if the program could not allocate memory using `malloc`
on success, it allocates the struct for the list and initializes it


```c
void exit_safer_pointers()
```
prints the unfreed pointers and safely frees them


```c
typedef struct node{
    void* p;
    char* name;
    struct node* next;
} p;
```

the struct used to contain a pointer, also a node in the pointer list,  it contains a `void* p` to the struct targeted by the allocation and a name to be printed when not freed properly

```c
p* safe_malloc(size_t size, char* name)
```
allocates a node (or 'p') and allocates the size given as parameter, the "p" parameter of the returned pointer points to an allocated memory of the given size. it also takes a name, that will be printed in case of unfreed node. on `malloc` error, it returns `POINTER_MALLOC_FAIL`

here is a working example of this function, more can be found [here](test_safe_pointers.c)

```c
typedef struct test_struct{
    int num;
    char* array;
} test;


p* _test_pointer1 = safe_malloc(sizeof(test), "_test_pointer1");
SAFE_CAST(_test_pointer1, test)->array = "test";
SAFE_CAST(_test_pointer1, test)->num = 4;
```


```c
int safe_free(p* pointer)
```
frees a node and the pointer it pointed to, also removes it from the list of pointers.
if the pointer is not valid, it returns `POINTER_INVALID_INPUT` else `POINTER_SUCCESS`, it can also return `POINTER_NOT_FOUND` if the user manually removed the pointer already

## Optimization

When going to production, using a linkedlist to store all pointers is not the most efficient solution, if during testing your code correctly frees all pointers, you can use some simplifications that's why there is a `DEBUG_MODE` definition, when set to 0 and when using `_malloc` and `_free` a check is performed before redirecting to the traditional `free` call or the `safe_free` (same goes for malloc with an added check to return `POINTER_MALLOC_FAIL` instead of null)
```c
char* str = _malloc(sizeof(char)*8, "string example");
_free(str);
```
this code will not add any pointers to the linkedlist if `DEBUG_MODE` == 0