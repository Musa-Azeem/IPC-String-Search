#ifndef SHARED_MEMORY_STRUCT
#define SHARED_MEMORY_STRUCT
#include <vector>
#include <string>

struct sm_struct{
    std::string path;
    std::string search_str;
    std::vector<std::string> file_lines;
};

#endif