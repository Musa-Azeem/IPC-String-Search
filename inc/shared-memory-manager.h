#ifndef SHAREDMEMORYMANAGER
#define SHAREDMEMORYMANAGER

#include "./shared-memory-struct.h"
#include <string>

class SharedMemoryManager{
    public:
        SharedMemoryManager(std::string sm_name): sm_name(sm_name){};
    protected:
        // const std::string sm_name = SM_NAME;
        const std::string sm_name;
        SmStruct *sm_struct_ptr;
};

#endif