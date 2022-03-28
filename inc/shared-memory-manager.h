/*
Written by Musa Azeem
SharedMemoryManager Class header
This file defines the SharedMemoryManager class
Constructors:
    Default:            (string sm_name, string sem_name)
        Initializes:    sm_name, sem_name, sem_name_two
Class variables:
    sm_name         name of shared memory
    sem_name        name of named semaphore
    sem_name_two    name of second named semaphore
    sm_struct_ptr   pointer to a SmStruct to be mapped to shared memory
    EOT             constant end of file signal character
    INV             constant invalid file signal string
    sem             first semaphore
    sem_two         second semaphore
*/
#ifndef SHARED_MEMORY_MANAGER_H
#define SHARED_MEMORY_MANAGER_H

#include "./shared-memory-struct.h"
#include <string>
#include <semaphore.h>

class SharedMemoryManager{
    public:
        SharedMemoryManager(std::string sm_name, std::string sem_name)
            :sm_name(sm_name), sem_name(sem_name), sem_name_two(sem_name+"_two"){};
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