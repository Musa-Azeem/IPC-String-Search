#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT
#include <vector>
#include <string>

struct SmStruct{
<<<<<<< HEAD
    const size_t file_path_length = 512;
    char file_path[512];
    const size_t kSearch_len = 512;
    char search_str[512];
    const size_t bufferSize = 4096 - sizeof(int) - 512 - sizeof(int) -512; // 4096 of mem - sizeof(int)
    char path[4096-sizeof(int)-512-sizeof(int)-512];      //extended by external code
    // std::vector<std::string> file_lines;
    // char file_lines[2000];
=======
    const size_t path_length = 512;
    char path[512];
    // const size_t kSearch_len = 512;
    // char search_str[512];
    const size_t bufferSize = 4096 - sizeof(int); // 4096 of mem - sizeof(int)
    char buffer[4096-sizeof(size_t)-sizeof(size_t)-512];      //extended by external code
>>>>>>> b83ff07a137c9c8f5f7bf0677384c33cc0506be9
};

#endif