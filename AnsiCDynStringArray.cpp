// AnsiCDynStringArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <assert.h>

extern "C" {
    #include "include/ansi_c_mem_track.h"
    #include "include/ansi_c_dynstringarray.h"
}

bool test_dynstringarray()
{
    // create
    DynStringArray* arr1 = NULL;
    int ret = ansi_c_dynstringarray_create(&arr1);
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr1) == 0);

    // push
    ret = ansi_c_dynstringarray_push(arr1, "hello");
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr1) == 1);
    assert(strcmp(ansi_c_dynstringarray_get(arr1, 0), "hello") == 0);

    // init
    ansi_c_dynstringarray_init(arr1, 3, "first", "second", "third");
    assert(ansi_c_dynstringarray_size(arr1) == 3);
    assert(strcmp(ansi_c_dynstringarray_get(arr1, 0), "first") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr1, 1), "second") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr1, 2), "third") == 0);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray Init");
    MemoryUsageInfo meminfo=ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // resize
    ret = ansi_c_dynstringarray_resize(arr1, 5);
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr1) == 5);
    
    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray resize");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // clear
    ansi_c_dynstringarray_clear(&arr1);
    assert(ansi_c_dynstringarray_size(arr1) == 0);

    // destroy
    ansi_c_dynstringarray_destroy(&arr1);
    assert(arr1 == NULL);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray destroy");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);
    size_t s = 0;
    const MemoryBlock** mb = ansi_c_mem_track_get_unfreed_blocks_info(&s);
    ansi_c_mem_track_log_unfreed_blocks_info(NULL, mb, s);

    return true;
}

bool test_dynstringarray_large_data(size_t blocksize)
{
    // create
    DynStringArray* arr = NULL;
    int ret = ansi_c_dynstringarray_create(&arr);
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr) == 0);

    // push
    const size_t n = blocksize;
    for (size_t i = 0; i < n; i++) {
        char str[200];
        sprintf_s(str, 200, "hello%zd", i);
        ret = ansi_c_dynstringarray_push(arr, str);
        assert(ret == 0);
        assert(ansi_c_dynstringarray_size(arr) == i + 1);
        assert(strcmp(ansi_c_dynstringarray_get(arr, i), str) == 0);
    }

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray push");
    MemoryUsageInfo meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // resize
    ret = ansi_c_dynstringarray_resize(arr, n + blocksize);
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr) == n + blocksize);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray resize");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // clear
    ansi_c_dynstringarray_clear(&arr);
    assert(ansi_c_dynstringarray_size(arr) == 0);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray clear");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // destroy
    ansi_c_dynstringarray_destroy(&arr);
    assert(arr == NULL);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray destroy");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    size_t s = 0;
    const MemoryBlock** mb = ansi_c_mem_track_get_unfreed_blocks_info(&s);
    ansi_c_mem_track_log_unfreed_blocks_info(NULL, mb, s);

    return true;
}

void test_dynstringarray_removeAt() {
    // create
    DynStringArray* arr = NULL;
    int ret = ansi_c_dynstringarray_create(&arr);
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr) == 0);

    // push
    ret = ansi_c_dynstringarray_push(arr, "hello");
    assert(ret == 0);
    ret = ansi_c_dynstringarray_push(arr, "world");
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr) == 2);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray push");
    MemoryUsageInfo meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // removeAt
    char buffer[10];
    ret = ansi_c_dynstringarray_removeAt(arr, 1, buffer, sizeof(buffer));
    assert(ret == 1);
    assert(ansi_c_dynstringarray_size(arr) == 1);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 0), "hello") == 0);
    assert(strcmp(buffer, "world") == 0);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray removeAt");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // clear
    ansi_c_dynstringarray_clear(&arr);
    assert(ansi_c_dynstringarray_size(arr) == 0);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray clear");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // destroy
    ansi_c_dynstringarray_destroy(&arr);
    assert(arr == NULL);

    ansi_c_mem_track_log_message(NULL, "Info", "After dynstringarray destroy");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    size_t s = 0;
    const MemoryBlock** mb = ansi_c_mem_track_get_unfreed_blocks_info(&s);
    ansi_c_mem_track_log_unfreed_blocks_info(NULL, mb, s);
}

bool test_dynstringarray_set()
{
    DynStringArray* arr = NULL;
    int ret = ansi_c_dynstringarray_create(&arr);
    assert(ret == 0);

    ret = ansi_c_dynstringarray_push(arr, "hello");
    assert(ret == 0);

    ret = ansi_c_dynstringarray_push(arr, "world");
    assert(ret == 0);

    ret = ansi_c_dynstringarray_set(arr, 0, "hi there");
    assert(ret == 0);

    ret = ansi_c_dynstringarray_set(arr, 1, "");
    assert(ret == 0);

    assert(ansi_c_dynstringarray_size(arr) == 2);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 0), "hi there") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 1), "") == 0);

    // Log memory usage information
    ansi_c_mem_track_log_message(NULL, "Info", "After dynamic string array set");
    MemoryUsageInfo meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // Destroy the dynamic string array
    ansi_c_dynstringarray_destroy(&arr);

    // Log memory usage information
    ansi_c_mem_track_log_message(NULL, "Info", "After dynamic string array destroy");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // Log unfreed memory blocks
    size_t s = 0;
    const MemoryBlock** mb = ansi_c_mem_track_get_unfreed_blocks_info(&s);
    ansi_c_mem_track_log_unfreed_blocks_info(NULL, mb, s);

    return true;
}

bool test_dynstringarray_insert() {
    DynStringArray* arr = NULL;
    int ret = ansi_c_dynstringarray_create(&arr);
    assert(ret == 0);

    ret = ansi_c_dynstringarray_push(arr, "hello");
    assert(ret == 0);

    ret = ansi_c_dynstringarray_push(arr, "world");
    assert(ret == 0);

    ret = ansi_c_dynstringarray_push(arr, "foo");
    assert(ret == 0);

    ret = ansi_c_dynstringarray_insert(arr, 0, "hi");
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr) == 4);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 0), "hi") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 1), "hello") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 2), "world") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 3), "foo") == 0);

    ret = ansi_c_dynstringarray_insert(arr, 2, "there");
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr) == 5);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 0), "hi") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 1), "hello") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 2), "there") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 3), "world") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 4), "foo") == 0);

    ret = ansi_c_dynstringarray_insert(arr, 5, "sixth");
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr) == 6);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 0), "hi") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 1), "hello") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 2), "there") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 3), "world") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 4), "foo") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 5), "sixth") == 0);

    ret = ansi_c_dynstringarray_insert(arr, 4, "fourth");
    assert(ret == 0);
    assert(ansi_c_dynstringarray_size(arr) == 7);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 0), "hi") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 1), "hello") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 2), "there") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 3), "world") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 4), "fourth") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 5), "foo") == 0);
    assert(strcmp(ansi_c_dynstringarray_get(arr, 6), "sixth") == 0);

    // Log memory usage information
    ansi_c_mem_track_log_message(NULL, "Info", "After dynamic string array set");
    MemoryUsageInfo meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // Destroy the dynamic string array
    ansi_c_dynstringarray_destroy(&arr);

    // Log memory usage information
    ansi_c_mem_track_log_message(NULL, "Info", "After dynamic string array destroy");
    meminfo = ansi_c_mem_track_get_info();
    ansi_c_mem_track_print_info(NULL, &meminfo);

    // Log unfreed memory blocks
    size_t s = 0;
    const MemoryBlock** mb = ansi_c_mem_track_get_unfreed_blocks_info(&s);
    ansi_c_mem_track_log_unfreed_blocks_info(NULL, mb, s);

    return true;
}

int main()
{
    // initialize
    ansi_c_mem_track_init();

    ansi_c_mem_track_log_message(NULL, "Info", "Begin of test -----------------------------");
    ansi_c_mem_track_log_message(NULL, "Info", "Testing all funcions of dynstringarray ----");
    test_dynstringarray();
    ansi_c_mem_track_log_message(NULL, "Info", "Large data test of dynstringarray ---------");
    test_dynstringarray_large_data(100000);
    ansi_c_mem_track_log_message(NULL, "Info", "test ansi_c_dynstringarray_removeAt -------");
    test_dynstringarray_removeAt();
    ansi_c_mem_track_log_message(NULL, "Info", "test ansi_c_dynstringarray_set ------------");
    test_dynstringarray_set();
    ansi_c_mem_track_log_message(NULL, "Info", "test test_dynstringarray_insert -----------");
    test_dynstringarray_insert();
    ansi_c_mem_track_log_message(NULL, "Info", "End of test -------------------------------");
    // Deinit
    ansi_c_mem_track_deinit();
}

