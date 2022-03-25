#ifndef SHAREDMEMORYMANAGER
#define SHAREDMEMORYMANAGER

#include "./shared-memory-struct.h"
#include <string>

class SharedMemoryManager{
    public:
        SharedMemoryManager(std::string sm_name, std::string sem_name)
            :sm_name(sm_name), sem_name(sem_name), sem_name_two(sm_name+"_two"){};
            //TODO mv to .cc and check for /
    protected:
        // const std::string sm_name = SM_NAME;
        const std::string sm_name;
        const std::string sem_name;
        const std::string sem_name_two;
        SmStruct *sm_struct_ptr;
        const char EOT = '\004';
        const std::string INV = "_INVALID_FILE";
};

#endif