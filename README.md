# safe_pointers

> [!WARNING]
> This repository does not make every pointer operation safe, it only allows you to debug and make safer use of pointers

How does it make it safer?

The main goal is not avoid having forgotten non freed pointers that were allocated, it helps that by storing every pointer in a list and at the end of a program freeing every pointer in that list.


An example of output for two lists, one with all freed pointers and the other with two unfreed pointers
```
[SUCCESS] POINTERS : All pointers where freed
[FAILURE] POINTERS : Unfreed pointer : pointer never freed
[FAILURE] POINTERS : Unfreed pointer : pointer2 never freed
```

## Usage

When allocating memory you can use `safe_malloc()` wich allocates memory for the struct you want while also adding the allocation in the list

When starting a program, you need to call `initialize_safer_pointers()` wich initializes the list correctly in the global variable `p_list* POINTER_LIST`

On exiting a program safely, you need to call `exit_safer_pointers()` wich will print all unfreed pointers and free them for you

When freeing memory, you can call `safe_free()` wich will remove the allocation from the list of allocations and free the node

For a working example, check the [test](test_safe_pointers.c)



## Utils

For using these helper functions, there are some parameters and utilies

### logging

You can choose to log errors such as malloc fails with the `LOG_ERRORS` definition in the `safe_pointers.h` file, you can also choose a std for the output of infos such as success on exiting in the `POINTER_INFO_STD` definition

### casting

when allocating a struct, you will have to use typecast to allow for autocompletion, the macro `SAFE_CAST` is there to help


## Doc


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

