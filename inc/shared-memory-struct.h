#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT
#include <vector>
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