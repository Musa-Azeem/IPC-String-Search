#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT
#include <vector>
#include <string>

struct SmStruct{
    const size_t file_path_length = 512;
    char file_path[512];
    const size_t kSearch_len = 512;
    char search_str[512];
    const size_t bufferSize = 4096 - sizeof(int) - 512 - sizeof(int) -512; // 4096 of mem - sizeof(int)
    char path[4096-sizeof(int)-512-sizeof(int)-512];      //extended by external code
    // std::vector<std::string> file_lines;
    // char file_lines[2000];
};

#endif