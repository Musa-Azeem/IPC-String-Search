/*
Written by Musa Azeem
SmStruct Header
This file defines the SmStruct class and related constants
Definitions:
    SHM_SIZE        size of shared memory to be created
    PATH_LEN        size of path array in SmStruct
    BUFFER_SIZE     size of buffer in SmStruct, calculated from total size and size of other variables in the struct
Struct variables:
    path_length     length of path array
    path            holds file path
    buffer_size     length of buffer array
    buffer          holds buffer for file lines of file
*/

#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT

#include <string>

#define SHM_SIZE 4096
#define PATH_LEN 512
#define BUFFER_SIZE 3568 // SHM_SIZE - PATH_LEN - 2*sizeof(size_t)

struct SmStruct{
    size_t path_length;
    char path[PATH_LEN];
    size_t buffer_size;
    char buffer[BUFFER_SIZE];
};

#endif