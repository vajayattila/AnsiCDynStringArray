
# AnsiCDynStringArray
## Overview
The AnsiCDynStringArray library provides a dynamic array of C strings in C99. It is designed to be lightweight, portable, and easy to use.

## Features
- Dynamically resizable array of C strings
- Memory management using `ansi_c_mem_track` library
- Simple and easy-to-use API

## Usage Guide
To use the AnsiCDynStringArray library in your C program, follow these steps:
* Include the ansi_c_mem_track.h and ansicdynstringarray.h header file in your C or C++ source file.
```c
// In C enviroment:
#include "ansicdynstringarray.h"
#include "include/ansi_c_mem_track.h"

// in C++ enviroment:
extern "C" {
    #include "include/ansi_c_mem_track.h"
    #include "include/ansi_c_dynstringarray.h"
}
```
* Initialize AnsiCMemTrack library
```c
ansi_c_mem_track_init();
```
* Declare a DynStringArray pointer variable.
```c
DynStringArray* myArray=NULL;
```
* Call the `ansi_c_dynstringarray_create` function to create the dynamic string array.
```c
if (ansi_c_dynstringarray_create(&myArray)!=0) {
    // handle error
}
```
* Add string elements to the array using the `ansi_c_dynstringarray_push` function.
```c
if (ansi_c_dynstringarray_push(myArray, "hello") != 0) {
    // handle error
}

if (ansi_c_dynstringarray_push(myArray, "world") != 0) {
    // handle error
}
```
* Access the elements of the array using array indexing.
```c
printf("%s\n", ansi_c_dynstringarray_get(myArray, 0)); // prints "hello"
printf("%s\n", ansi_c_dynstringarray_get(myArray, 1)); // prints "world"
```
* When you're done using the dynamic string array, call the `ansi_c_dynstringarray_destroy` function to free its memory.
```c
ansi_c_dynstringarray_destroy(&myArray);
```
* Deinitalize AnsiCMemTrack library
```c
ansi_c_mem_track_deinit();
```

## Enums
## dyn_arr_alloc_mode Enum

The `dyn_arr_alloc_mode` enum specifies the allocation mode for a `DynStringArray`. This value is automatically set during initialization depending on the chosen initialization mode.

### Values

- `DYN_ARR_DYNAMIC`: Allocates memory dynamically using `malloc()` for the entire structure.
- `DYN_ARR_STATIC`: Uses a statically allocated structure and initializes its data to `NULL`.

### Example

```c
// Example initialization with static allocation
DynStringArray arr1, *arr1ptr=&arr1;
ansi_c_dynstringarray_create(&arr1ptr); // DYN_ARR_STATIC

// Example initialization with dynamic allocation
DynStringArray* arr2 = NULL;
ansi_c_dynstringarray_create(&arr2); // DYN_ARR_DYNAMIC
```

## Structures
### DynStringArray
The `DynStringArray` struct represents a dynamic array of strings.

#### Fields
- `size` - the number of strings currently in the array.
- `capacity` - the maximum number of strings the array can hold.
- `data` - a pointer to an array of string pointers.
- `data_object_id` - the unique ID assigned to the data array by the `ansi_c_mem_track` library.
- `system_object_id` - the unique ID assigned to the `DynStringArray` struct by the `ansi_c_mem_track` library.

## Functions: 

### `ansi_c_dynstringarray_create`
Creates a new empty dynamic string array. The arr parameter points to a pointer to a `DynStringArray` structure. This function allocates memory for the structure and initializes its fields. The array data is initially empty, with a default capacity of `DYNSTRINGARRAY_DEFAULT_CAPACITY`.

#### Parameters
* `arr` : A pointer to a pointer to a DynStringArray structure to be created.

#### Return Value
Returns 0 if the creation was successful, -1 otherwise.

#### See Also
* `DynStringArray`
* `DYNSTRINGARRAY_DEFAULT_CAPACITY`
* `ansi_c_dynstringarray_destroy`

#### Example 
```c
// Example initialization with static allocation
DynStringArray arr1, *arr1ptr=&arr1;
ansi_c_dynstringarray_create(&arr1ptr);

// Example initialization with dynamic allocation
DynStringArray* arr2 = NULL;
ansi_c_dynstringarray_create(&arr2);
```
In the static allocation example, a `DynStringArray` variable `arr1` is declared and a pointer `arr1ptr` is created pointing to it. `ansi_c_dynstringarray_create` is then called with the address of `arr1ptr`, which initializes the array data to `NULL` and sets the allocation mode to `DYN_ARR_STATIC`.

In the dynamic allocation example, a `DynStringArray` pointer variable `arr2` is declared and set to `NULL`. `ansi_c_dynstringarray_create` is then called with the address of `arr2`, which allocates memory dynamically for the `DynStringArray` structure and initializes its fields. The allocation mode is set to `DYN_ARR_DYNAMIC`.

### `ansi_c_dynstringarray_destroy`
Frees the memory of a dynamically allocated `DynStringArray` object and sets its pointer to `NULL`.

#### Usage
```c
DynStringArray* arr = NULL;
// ... initialization of the dynamic string array
ansi_c_dynstringarray_destroy(&arr);
```
#### Parameters
- `arr` : A double pointer to a `DynStringArray` object to be destroyed (in `DYN_ARR_DYNAMIC` mode) and set to `NULL`.
#### Return value
None.
#### Example
```c
DynStringArray* arr = NULL;
ansi_c_dynstringarray_create(&arr);
ansi_c_dynstringarray_push(arr, "Hello");
ansi_c_dynstringarray_push(arr, "World");
ansi_c_dynstringarray_destroy(&arr);
assert(arr == NULL);
```

#### See also
- `DynStringArray`
- `ansi_c_dynstringarray_create`

## `ansi_c_dynstringarray_clear`

Clears a DynStringArray by freeing its data buffer and resetting its size and capacity to default values.

If the DynStringArray has dynamic allocation, its data buffer will be freed using the custom memory tracking system.
The size and capacity of the DynStringArray are reset to their default values.

### Parameters

- `arr`: The pointer to the DynStringArray to clear. The pointer itself will be set to NULL by the function.

### Return value

The function does not return a value.

### Example

```c
// Create a DynStringArray
DynStringArray* arr = NULL;
if (ansi_c_dynstringarray_create(&arr)!=0) {
    // handle error
}

// Add some strings
ansi_c_dynstringarray_push(arr, "hello");
ansi_c_dynstringarray_push(arr, "world");

// Clear the DynStringArray
ansi_c_dynstringarray_clear(&arr);

// The array should now be empty
printf("Size: %zu, Capacity: %zu\n", arr->size, arr->capacity); // prints "Size: 0, Capacity: 2"

// Destroy the DynStringArray
ansi_c_dynstringarray_destroy(&arr);
```
#### See also
- `ansi_c_dynstringarray_create`
- `ansi_c_dynstringarray_destroy`

## `ansi_c_dynstringarray_resize`

Resizes the specified dynamic string array to a new size. If the new size is less than the current size, the elements at the end of the array are removed. If the new size is greater than the current size, new `NULL` elements are added to the end of the array. If the new size is equal to the current size, nothing happens.

If the reallocation of memory fails, the function returns -1, otherwise it returns 0.

### Parameters:
- `arr`: The dynamic string array to resize.
- `new_size`: The new size of the dynamic string array.

### Return Value:
Returns 0 on success, -1 on failure.

### Example:
```c
DynStringArray* arr = NULL;
ansi_c_dynstringarray_create(&arr);

// Add some elements to the array
ansi_c_dynstringarray_push(arr, "hello");
ansi_c_dynstringarray_push(arr, "world");
printf("Size of array: %d\n", arr->size); // prints "Size of array: 2"

// Resize the array to a smaller size
ansi_c_dynstringarray_resize(arr, 1);
printf("Size of array: %d\n", arr->size); // prints "Size of array: 1"
printf("First element: %s\n", ansi_c_dynstringarray_get(arr, 0)); // prints "First element: hello"

// Resize the array to a larger size
ansi_c_dynstringarray_resize(arr, 3);
printf("Size of array: %d\n", arr->size); // prints "Size of array: 3"
printf("Third element: %s\n", ansi_c_dynstringarray_get(arr, 2)); // prints "Third element: (null)"

// Clean up the array
ansi_c_dynstringarray_destroy(&arr);
```

## `ansi_c_dynstringarray_push`

Adds a string value to the end of the dynamic string array. If the dynamic string array is full, the function automatically resizes the array by increasing its capacity.

### Parameters:
- `arr`: A pointer to the dynamic string array.
- `value`: A pointer to the string value to be added to the array.

### Return Value:
Returns 0 on success, a non-zero value on failure.

### See Also:
- `ansi_c_dynstringarray_resize`

### Example:
```c
DynStringArray* arr = NULL;
ansi_c_dynstringarray_create(&arr);

// Add some elements to the array
ansi_c_dynstringarray_push(arr, "hello");
ansi_c_dynstringarray_push(arr, "world");
printf("Size of array: %d\n", arr->size); // prints "Size of array: 2"
printf("First element: %s\n", ansi_c_dynstringarray_get(arr, 0)); // prints "First element: hello"
printf("Last element: %s\n", ansi_c_dynstringarray_get(arr, 1)); // prints "Last element: world"

// Clean up the array
ansi_c_dynstringarray_destroy(&arr);
```

## `ansi_c_dynstringarray_removeAt`

Removes the string at the specified index from the dynamic string array.

### Parameters:
- `arr`: A pointer to the dynamic string array.
- `index`: The index of the string to be removed.
- `buffer`: A pointer to a buffer to store the removed string. Can be NULL if the string does not need to be saved.
- `buf_size`: The size of the buffer in bytes. If the buffer is not large enough to store the string, it will be truncated to fit.

### Return Value:
The new size of the dynamic string array.

### Example:
```c
DynStringArray* arr = NULL;
ansi_c_dynstringarray_create(&arr);

// Add some elements to the array
ansi_c_dynstringarray_push(arr, "hello");
ansi_c_dynstringarray_push(arr, "world");
printf("Size of array: %d\n", arr->size); // prints "Size of array: 2"

// Remove the element at index 1
char removed[10];
ansi_c_dynstringarray_removeAt(arr, 1, removed, 10);
printf("Size of array: %d\n", arr->size); // prints "Size of array: 1"
printf("Removed string: %s\n", removed); // prints "Removed string: world"

// Clean up the array
ansi_c_dynstringarray_destroy(&arr);
```

## `ansi_c_dynstringarray_size`

Returns the number of elements in the dynamic string array.

### Parameters:
- `arr`: A pointer to the dynamic string array.

### Return Value:
The number of elements in the dynamic string array.

### Example:
```c
DynStringArray* arr = NULL;
ansi_c_dynstringarray_create(&arr);

// Add some elements to the array
ansi_c_dynstringarray_push(arr, "hello");
ansi_c_dynstringarray_push(arr, "world");
printf("Size of array: %d\n", ansi_c_dynstringarray_size(arr)); // prints "Size of array: 2"

// Clean up the array
ansi_c_dynstringarray_destroy(&arr);
```

## `ansi_c_dynstringarray_init`

Initializes a dynamic string array with a given number of string values.

The function can be called with a variable number of arguments, where each argument is a string value to be added to the array.

### Parameters:
- `arr`: A pointer to the dynamic string array.
- `count`: The number of string values to be added to the array.
- `...`: A variable number of arguments, each argument is a string value to be added to the array.

### Return Value:
`void`

### Example:
```c
DynStringArray* arr = NULL;
ansi_c_dynstringarray_init(&arr, 3, "hello", "world", "from chatbot");
printf("Size of array: %d\n", ansi_c_dynstringarray_size(arr)); // prints "Size of array: 3"
printf("First element: %s\n", ansi_c_dynstringarray_get(arr, 0)); // prints "First element: hello"
printf("Last element: %s\n", ansi_c_dynstringarray_get(arr, 2)); // prints "Last element: from chatbot"

// Clean up the array
ansi_c_dynstringarray_destroy(&arr);
```

## `ansi_c_dynstringarray_get`

Returns the string value at the given index in the dynamic string array.

### Parameters:
- `arr`: A pointer to the dynamic string array.
- `index`: The index of the string value to retrieve.

### Return Value:
A pointer to the string value at the given index.

### See Also:
- `ansi_c_dynstringarray_size`

### Example:
```c
DynStringArray* arr = NULL;
ansi_c_dynstringarray_create(&arr);

// Add some elements to the array
ansi_c_dynstringarray_push(arr, "hello");
ansi_c_dynstringarray_push(arr, "world");
printf("First element: %s\n", ansi_c_dynstringarray_get(arr, 0)); // prints "First element: hello"

// Clean up the array
ansi_c_dynstringarray_destroy(&arr);
```

## `ansi_c_dynstringarray_set`

Sets the string value at the given index in the dynamic string array.

### Parameters
- `arr`: A pointer to the dynamic string array.
- `index`: The index of the string value to set.
- `value`: A pointer to the new string value to set.

### Return Value
- `0` on success
- `-1` on failure.

### Errors
If the specified index is greater than or equal to the current size of the array, the function does nothing and returns -1.

If the new string value is larger than the previously stored string value at the specified index, the function automatically resizes the array by increasing its capacity.

If the reallocation of memory fails, the function returns -1.

### See Also
- `ansi_c_dynstringarray_resize`
- `ansi_c_dynstringarray_push`
- `ansi_c_dynstringarray_get`

### Example
```c
#include "ansi_c_dynstringarray.h"
#include <stdio.h>

int main() {
    DynStringArray* arr = NULL;
    ansi_c_dynstringarray_create(&arr);

    // Adding initial values
    ansi_c_dynstringarray_push(arr, "apple");
    ansi_c_dynstringarray_push(arr, "banana");
    ansi_c_dynstringarray_push(arr, "cherry");

    // Printing out the original values
    printf("Original values:\n");
    for (size_t i = 0; i < ansi_c_dynstringarray_size(arr); i++) {
        printf("%s\n", ansi_c_dynstringarray_get(arr, i));
    }

    // Setting a new value at index 1
    ansi_c_dynstringarray_set(arr, 1, "orange");

    // Printing out the modified values
    printf("Modified values:\n");
    for (size_t i = 0; i < ansi_c_dynstringarray_size(arr); i++) {
        printf("%s\n", ansi_c_dynstringarray_get(arr, i));
    }

    ansi_c_dynstringarray_destroy(&arr);
    return 0;
}
```

## `ansi_c_dynstringarray_insert`

Inserts the given string value into the dynamic string array at the specified index.

### Parameters
* `arr` - A pointer to the dynamic string array.
* `index` - The index at which to insert the string value.
* `value` - A pointer to the string value to insert.

### Return Value
Returns 0 on success, -1 on failure.

### See Also
* `ansi_c_dynstringarray_push`

### Example
```c
#include <stdio.h>
#include "dynstringarray.h"

int main() {
    DynStringArray* arr=NULL;
    int ret = ansi_c_dynstringarray_create(&arr);
    if (ret != 0) {
        printf("Error creating dynamic string array!\n");
        return 1;
    }

    // Insert some strings into the array
    ret = ansi_c_dynstringarray_insert(arr, 0, "world");
    if (ret != 0) {
        printf("Error inserting string into dynamic string array!\n");
        ansi_c_dynstringarray_destroy(&arr);
        return 1;
    }

    ret = ansi_c_dynstringarray_insert(arr, 0, "hello");
    if (ret != 0) {
        printf("Error inserting string into dynamic string array!\n");
        ansi_c_dynstringarray_destroy(&arr);
        return 1;
    }

    ret = ansi_c_dynstringarray_insert(arr, 2, "goodbye");
    if (ret != 0) {
        printf("Error inserting string into dynamic string array!\n");
        ansi_c_dynstringarray_destroy(&arr);
        return 1;
    }

    // Print the strings in the array
    for (size_t i = 0; i < ansi_c_dynstringarray_size(arr); i++) {
        printf("%s ", ansi_c_dynstringarray_get(arr, i));
    }
    printf("\n");

    // Clean up
    ansi_c_dynstringarray_destroy(&arr);
    return 0;
}
```

## Requirements

- C99 compiler
- `AnsiCMemTrack` library

Note: The `AnsiCDynStringArray` library does not directly use `malloc()` and `free()` functions for memory allocation and deallocation. Instead, it relies on the `AnsiCMemTrack` library for memory management. This library provides a way to track memory usage and detect memory leaks. Please make sure to include and link this library to your project when using `AnsiCDynStringArray`. You can find the library and usage instructions in the [AnsiCMemTrack repository](https://github.com/vajayattila/AnsiCMemTrack).

### Note
The C11 support is only required for building the test application and not for using the AnsiCMemTrack library itself.

## License
The AnsiCDynStringArray library is licensed under the MIT License. See the `LICENSE` file for more information.