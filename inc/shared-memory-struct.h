#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT
#include <vector>
#include <string>
#define SIZE 4096
#define PATHLEN 512

struct SmStruct{
    size_t path_length;
    char path[PATHLEN];
    size_t bufferSize = SIZE - (2*sizeof(size_t)) - 512;
    char buffer[SIZE-(2*sizeof(size_t))-512];
};

#endif