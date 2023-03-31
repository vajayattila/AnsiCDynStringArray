/**
    *
    *   @file ansi_c_dynstringarray.h
    *   @brief A dynamic array of C strings implementation.
    *   This header file provides the implementation for a dynamic array of C strings.
    *   It allows for adding and removing elements from the array dynamically, as well as resizing
    *   the array as needed. It also provides functionality for creating an array from a variable number
    *   of arguments.
    * 
    *   Dependencies: https://github.com/vajayattila/AnsiCMemTrack.git
    * 
    *	@author Attila Vajay
    *	@email vajay.attila@gmail.com
    *	@git https://github.com/vajayattila/AnsiCDynStringArray.git
    *   @date 2023.03.27.-2023.03.31.
    *   @version 1.0
    *   @license MIT License
    *   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
    *   (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
    *   publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
    *   subject to the following conditions:
    *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
    *   ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    *   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    *   For more information, see the file LICENSE.
    */
#ifndef ANSI_C_DYNSTRINGARRAY_H
#define ANSI_C_DYNSTRINGARRAY_H

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief The default capacity of a dynamic string array if none is specified.
 */
#define DYNSTRINGARRAY_DEFAULT_CAPACITY 10

/**
    * @brief The dyn_arr_alloc_mode enum specifies the allocation mode for a DynStringArray. This value is 
    * automatically set during initialization depending on the chosen initialization mode.
    *
    * The DynStringArray can be initialized with two allocation modes: DYN_ARR_DYNAMIC and DYN_ARR_STATIC.
    * - DYN_ARR_DYNAMIC: Allocates memory dynamically using malloc() for the entire structure.
    * - DYN_ARR_STATIC: Uses a statically allocated structure and initializes its data to NULL.
    *
    * @code{.c}
    * // Example initialization with static allocation
    * DynStringArray arr1, *arr1ptr=&arr1;
    * DynStringArray_create(&arr1ptr);
    *
    * // Example initialization with dynamic allocation
    * DynStringArray* arr2 = NULL;
    * DynStringArray_create(&arr2);
    * @endcode
    * @see DynStringArray, DynStringArray_init
    */
typedef enum {
    DYN_ARR_DYNAMIC,
    DYN_ARR_STATIC
} dyn_arr_alloc_mode;

/**
 * @brief A dynamic string array structure
 * The structure contains a pointer to an array of strings, its current size, its current capacity,
 * and the current allocation mode. Additionally, it also stores the system-assigned object ID for
 * the structure and the data array.
 * @see dyn_arr_alloc_mode
 */
typedef struct {
    char** data; /*< Pointer to the array of strings*/
    size_t size; /*< Current size of the array*/
    size_t capacity; /*< Current capacity of the array*/
    dyn_arr_alloc_mode alloc_mode; /*< Current allocation mode*/
    size_t system_object_id; /*< System - assigned object ID for the structure*/
    size_t data_object_id; /*<System - assigned object ID for the data array*/
} DynStringArray;

/**
 * @brief Creates a new empty dynamic string array.
 * The @p arr parameter points to a pointer to a DynStringArray structure. This function allocates memory for
 * the structure and initializes its fields. The array data is initially empty, with a default capacity of
 * DYNSTRINGARRAY_DEFAULT_CAPACITY.
 * @param[in,out] arr A pointer to a pointer to a DynStringArray structure to be created.
 * @return 0 if the creation was successful, -1 otherwise.
 * @see DynStringArray, DYNSTRINGARRAY_DEFAULT_CAPACITY, ansi_c_dynstringarray_destroy
 */
int ansi_c_dynstringarray_create(DynStringArray** arr);

/**
 * @brief Frees the memory of a dynamically allocated DynStringArray object and sets its pointer to NULL.
 *
 * @param arr A double pointer to a DynStringArray object.
 *
 * @see DynStringArray, ansi_c_dynstringarray_create
 */
void ansi_c_dynstringarray_destroy(DynStringArray** arr);

/**
 * @brief Clears a DynStringArray by freeing its data buffer and resetting its size and capacity to default values.
 *
 * If the DynStringArray has dynamic allocation, its data buffer will be freed using the custom memory tracking system.
 * The size and capacity of the DynStringArray are reset to their default values.
 *
 * @param arr The pointer to the DynStringArray to clear. The pointer itself will be set to NULL by the function.
 * @see ansi_c_dynstringarray_create, ansi_c_dynstringarray_destroy
 */
void ansi_c_dynstringarray_clear(DynStringArray** arr);

/**
 * @brief Resizes the specified dynamic string array.
 *
 * Resizes the specified dynamic string array to a new size.If the new size is less than the current size,
 * the elements at the end of the array are removed.If the new size is greater than the current size,
 * new NULL elements are added to the end of the array.If the new size is equal to the current size, nothing
 * happens.
 *
 * If the reallocation of memory fails, the function returns - 1, otherwise it returns 0.
 *
 * @param arr The dynamic string array to resize.
 * @param new_size The new size of the dynamic string array.
 * @return int Returns 0 on success, -1 on failure.
 */
int ansi_c_dynstringarray_resize(DynStringArray * arr, size_t new_size);

/**
 * @brief Adds a string value to the end of the dynamic string array.
 * If the dynamic string array is full, the function automatically resizes the array by increasing its capacity.
 * @param arr A pointer to the dynamic string array.
 * @param value A pointer to the string value to be added to the array.
 * @return 0 on success, a non-zero value on failure.
 * @see ansi_c_dynstringarray_resize
 */
int ansi_c_dynstringarray_push(DynStringArray* arr, const char* value);

/**
 * @brief Removes the string at the specified index from the dynamic string array.
 * @param arr A pointer to the dynamic string array.
 * @param index The index of the string to be removed.
 * @param buffer A pointer to a buffer to store the removed string. Can be NULL if the string does not need to be saved.
 * @param buf_size The size of the buffer in bytes. If the buffer is not large enough to store the string, it will be truncated to fit.
 * @return The new size of the dynamic string array.
 */
size_t ansi_c_dynstringarray_removeAt(DynStringArray* arr, size_t index, char* buffer, size_t buf_size);

/**
 * @brief Returns the number of elements in the dynamic string array.
 * @param arr A pointer to the dynamic string array.
 * @return The number of elements in the dynamic string array.
 */
size_t ansi_c_dynstringarray_size(DynStringArray* arr);

/**
 * @brief Initializes a dynamic string array with a given number of string values.
 *
 * The function can be called with a variable number of arguments, where each argument is a string value to be added to the array.
 *
 * @param arr A pointer to the dynamic string array.
 * @param count The number of string values to be added to the array.
 * @param ... A variable number of arguments, each argument is a string value to be added to the array.
 * @return void
 */
void ansi_c_dynstringarray_init(DynStringArray* arr, size_t count, ...);

/**
 * @brief Returns the string value at the given index in the dynamic string array.
 * @param arr A pointer to the dynamic string array.
 * @param index The index of the string value to retrieve.
 * @return A pointer to the string value at the given index.
 * @see ansi_c_dynstringarray_size
 */
const char* ansi_c_dynstringarray_get(const DynStringArray* arr, size_t index);

/**
 * @brief Sets the string value at the given index in the dynamic string array.
 *
 * If the specified index is greater than or equal to the current size of the array, the function does nothing and returns -1.
 *
 * If the new string value is larger than the previously stored string value at the specified index, the function
 * automatically resizes the array by increasing its capacity.
 *
 * If the reallocation of memory fails, the function returns -1, otherwise it returns 0.
 *
 * @param arr A pointer to the dynamic string array.
 * @param index The index of the string value to set.
 * @param value A pointer to the new string value to set.
 * @return 0 on success, -1 on failure.
 * @see ansi_c_dynstringarray_resize
 * @see ansi_c_dynstringarray_push
 * @see ansi_c_dynstringarray_get
 */
int ansi_c_dynstringarray_set(DynStringArray* arr, size_t index, const char* value);

/**
 * @brief Inserts the given string value into the dynamic string array at the specified index.
 * @param arr A pointer to the dynamic string array.
 * @param index The index at which to insert the string value.
 * @param value A pointer to the string value to insert.
 * @return 0 on success, -1 on failure.
 * @see ansi_c_dynstringarray_push
 */
int ansi_c_dynstringarray_insert(DynStringArray* arr, size_t index, const char* value);


#endif /* ANSI_C_DYNSTRINGARRAY_H */
