#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT
#include <vector>
#include <string>

struct SmStruct{
    const size_t path_length = 512;
    char path[512];
    // const size_t kSearch_len = 512;
    // char search_str[512];
    const size_t bufferSize = 4096 - sizeof(int); // 4096 of mem - sizeof(int)
    char buffer[4096-sizeof(size_t)-sizeof(size_t)-512];      //extended by external code
};

#endif