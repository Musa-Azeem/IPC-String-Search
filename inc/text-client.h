#ifndef TEXT_CLIENT
#define TEXT_CLIENT
#include "./shared-memory-manager.h"
// #include "./shared-memory-struct.h"
#include <string>

class TextClient: SharedMemoryManager {
    public:
        TextClient(std::string sm_name, std::string sem_name, std::string path, std::string search_str);
        int runClient();
    private:
        std::string path;
        std::string search_str;
        std::vector<std::string> file_lines;
        std::vector<std::string> found_lines;
        void *threaded_search(void *ptr);
};

#endif