#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT
#include <vector>
#include <string>

struct SmStruct{
    std::string path;
    std::vector<std::string> file_lines;
};

#endif