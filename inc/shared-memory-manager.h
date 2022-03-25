#ifndef SHAREDMEMORYMANAGER
#define SHAREDMEMORYMANAGER

#include "./shared-memory-struct.h"
#include <string>

class SharedMemoryManager{
    public:
        SharedMemoryManager(std::string sm_name, std::string sem_name)
            :sm_name(sm_name), sem_name(sem_name) {};
    protected:
        // const std::string sm_name = SM_NAME;
        const std::string sm_name;
        const std::string sem_name;
        SmStruct *sm_struct_ptr;
};

#endif