#ifndef SHAREDMEMORYMANAGER
#define SHAREDMEMORYMANAGER
#define SM_NAME "/text-shared-mem"
#define SM_SIZE 4096

#include "./shared-memory-struct.h"
#include <string>

class SharedMemoryManager{
    public:
        SharedMemoryManager();
    protected:
        const std::string sm_name = SM_NAME;
        sm_struct sm_obj;
};

#endif