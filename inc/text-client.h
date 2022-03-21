#ifndef TEXT_CLIENT
#define TEXT_CLIENT
#include "./inc/shared-memory-manager.h"
// #include "./shared-memory-struct.h"
#include <string>

class TextClient: SharedMemoryManager {
    public:
        TextClient(std::string path, std::string search_str);
        int runClient();
    private:
        std::string path;
        std::string search_str;
};

#endif