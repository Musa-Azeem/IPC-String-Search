#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT
#include <vector>
#include <string>
#define SIZE 4096
#define PATHSIZE 512

struct SmStruct{
    const size_t file_path_length = PATHSIZE;
    char file_path[PATHSIZE];
    const size_t bufferSize = SIZE - sizeof(size_t) - 512;
    char path[SIZE-sizeof(size_t)-512-sizeof(size_t)];
};

#endif