#ifndef TEXTSERVER
#define TEXTSERVER
#include "shared-memory-manager.h"
#include <string>
class TextServer: SharedMemoryManager {
    public:
        TextServer(std::string sm_name): SharedMemoryManager(sm_name) {};
        int runServer();
};

#endif