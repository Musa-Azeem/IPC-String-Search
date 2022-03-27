#ifndef SHAREDMEMORYMANAGER_H
#define SHAREDMEMORYMANAGER_H

#include "./shared-memory-struct.h"
#include <string>
#include <semaphore.h>

class SharedMemoryManager{
    public:
        SharedMemoryManager(std::string sm_name, std::string sem_name)
            :sm_name(sm_name), sem_name(sem_name), sem_name_two(sm_name+"_two"){};
    protected:
        const std::string sm_name;
        const std::string sem_name;
        const std::string sem_name_two;
        SmStruct *sm_struct_ptr;
        const char EOT = '\004';
        const std::string INV = "_INVALID_FILE";
        sem_t *sem;
        sem_t *sem_two;
};

#endif