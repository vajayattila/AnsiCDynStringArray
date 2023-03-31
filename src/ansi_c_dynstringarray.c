#include <string.h>
#include <stdlib.h>

#include "../include/ansi_c_dynstringarray.h"
#include "../include/ansi_c_mem_track.h"
#include "../include/ansi_c_macro_utils.h"

bool ansi_c_dynstringarray_initdata(DynStringArray** arr, dyn_arr_alloc_mode mode) {
    size_t capacity = DYNSTRINGARRAY_DEFAULT_CAPACITY;  // new min capacity
    char** data = (char**)ansi_c_mem_track_malloc(capacity * sizeof(char*), __FILE__, __FUNCTION__, "char**", (*arr)->data_object_id);
    if (!data) {
        (*arr)->data = NULL;
        (*arr)->capacity = 0;
        return false;
    }
    (*arr)->data = data;
    (*arr)->data[0] = NULL;
    (*arr)->capacity = capacity;
    (*arr)->size = 0;
    (*arr)->alloc_mode = mode;
    return true;
}

int ansi_c_dynstringarray_create(DynStringArray** arr) {
    if (!ansi_c_mem_track_is_initialized()) {
        return false;
    }

    if (*arr == NULL) {
        size_t sysobjid = ansi_c_mem_track_get_next_object_id();
        *arr = ansi_c_mem_track_malloc(sizeof(DynStringArray), __FILE__, __FUNCTION__, "DynStringArray", sysobjid);
        if (*arr == NULL) {
            return -1;
        }
        (*arr)->system_object_id = sysobjid;
        (*arr)->data_object_id = ansi_c_mem_track_get_next_object_id();
        ansi_c_dynstringarray_initdata(arr, DYN_ARR_DYNAMIC);
    }
    else {
        ansi_c_dynstringarray_initdata(arr, DYN_ARR_STATIC);
    }
    return 0;
}

void ansi_c_dynstringarray_clear(DynStringArray** arr) {
    if (*arr) {
        // Free data array and reset capacity
        ansi_c_mem_track_free_by_object_id((*arr)->data_object_id);
        (*arr)->capacity = DYNSTRINGARRAY_DEFAULT_CAPACITY;

        // Allocate new data array and initialize it with NULL
        char** new_data = (char**)ansi_c_mem_track_malloc(
            ((*arr)->capacity * sizeof(char*)), __FILE__, __FUNCTION__, "char**", (*arr)->data_object_id);
        if (new_data) {
            new_data[0] = NULL;
        }
        (*arr)->data = new_data;

        // Reset size and cleanup memory allocations
        (*arr)->size = 0;
        ansi_c_mem_track_cleanup_allocations();
    }
}

void ansi_c_dynstringarray_destroy(DynStringArray** arr) {
    if (*arr != NULL) {
        ansi_c_mem_track_free_by_object_id((*arr)->data_object_id);
        (*arr)->capacity = 0;
        if ((*arr)->alloc_mode == DYN_ARR_DYNAMIC) {
            ansi_c_mem_track_free_by_object_id((*arr)->system_object_id);
            *arr = NULL;
        }
        ansi_c_mem_track_cleanup_allocations();
    }
}

int ansi_c_dynstringarray_resize(DynStringArray* arr, size_t new_size) {
    if (new_size == arr->size) {
        return 0;
    }
    if (new_size < arr->size) {
        for (size_t i = new_size; i < arr->size; i++) {
            ansi_c_mem_track_free(arr->data[i]);
        }
    }
    else {
        size_t new_capacity = arr->capacity;
        while (new_capacity < new_size) {
            new_capacity += DYNSTRINGARRAY_DEFAULT_CAPACITY;
        }
        char** new_data = ansi_c_mem_track_realloc(arr->data, new_capacity * sizeof(char*), arr->data_object_id);
        if (new_data == NULL) {
            return -1;
        }
        for (size_t i = arr->size; i < new_size; i++) {
            new_data[i] = NULL;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->size = new_size;
    return 0;
}

int ansi_c_dynstringarray_push(DynStringArray* arr, const char* value) {
    char* new_value = NULL;
    STRDUP(new_value, strlen(value), value, arr->data_object_id);
    if (new_value == NULL) {
        return -1;
    }

    if (arr->size == arr->capacity) {
        if (ansi_c_dynstringarray_resize(arr, arr->size + 1) != 0) {
            ansi_c_mem_track_free(new_value);
            return -1;
        }
    } else {
        arr->size++;
    }

    arr->data[arr->size-1] = new_value;
    return 0;
}

size_t ansi_c_dynstringarray_removeAt(DynStringArray* arr, size_t index, char* buffer, size_t buf_size) {
    if (index >= arr->size) {
        return arr->size;
    }

    if (buffer && buf_size > 0) {
        size_t len = strlen(arr->data[index]);
        if (len >= buf_size) {
            len = buf_size - 1;
        }
        memcpy(buffer, arr->data[index], len);
        buffer[len] = '\0';
    }

    ansi_c_mem_track_free(arr->data[index]);
    if (index < arr->size - 1) {
        memmove(&arr->data[index], &arr->data[index + 1], (arr->size - index - 1) * sizeof(char*));
    }
    arr->size--;

    return arr->size;
}

size_t ansi_c_dynstringarray_size(DynStringArray* arr) {
    return arr->size;
}

void ansi_c_dynstringarray_init(DynStringArray* arr, size_t count, ...) {
    if (!arr) {
        return;
    }
    va_list args;
    va_start(args, count);
    ansi_c_dynstringarray_clear(&arr);
    for (size_t i = 0; i < count; i++) {
        const char* value = va_arg(args, const char*);
        ansi_c_dynstringarray_push(arr, value);
    }
    va_end(args);
}

const char* ansi_c_dynstringarray_get(const DynStringArray* arr, size_t index) {
    if (index >= arr->size) {
        return NULL;
    }
    return arr->data[index];
}

int ansi_c_dynstringarray_set(DynStringArray* arr, size_t index, const char* value)
{
    if (index >= arr->size) {
        return -1;
    }

    size_t new_str_len = strlen(value), new_buff_size= new_str_len + 1;
    char** poi = &arr->data[index];
    if (strlen(arr->data[index]) < strlen(value)) {
        *poi = ansi_c_mem_track_realloc(*poi, new_buff_size, arr->data_object_id);
        if (*poi == NULL) {
            return -1;
        }
    }
    STRCPY(*poi, new_buff_size, value);
    return 0;
}

int ansi_c_dynstringarray_insert(DynStringArray* arr, size_t index, const char* value)
{
    // If the index is out of range, return an error
    if (index > arr->size) {
        return -1;
    }

    // If inserting at the end of the array, simply push the string
    if (index == arr->size) {
        return ansi_c_dynstringarray_push(arr, value);
    }

    // If the array is full, resize it
    if (arr->size == arr->capacity) {
        size_t new_capacity = arr->capacity + DYNSTRINGARRAY_DEFAULT_CAPACITY;
        char** new_data = ansi_c_mem_track_realloc(arr->data, new_capacity * sizeof(char*), arr->data_object_id);
        if (new_data == NULL) {
            return -1;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }

    // Move the existing strings to make room for the new string
    memmove(&arr->data[index + 1], &arr->data[index], (arr->size - index) * sizeof(char*));

    // Insert the new string into the array
    STRDUP(arr->data[index], strlen(value), value, arr->data_object_id);
    arr->size++;

    return 0;
}
