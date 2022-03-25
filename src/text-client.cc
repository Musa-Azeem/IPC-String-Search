#include "../inc/text-client.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <semaphore.h>

TextClient::TextClient(std::string sm_name, std::string sem_name, std::string path, std::string search_str)
    : SharedMemoryManager(sm_name, sem_name) {
    this->path = path;
    this->search_str = search_str;
}
int TextClient::runClient(){
    std::string sem_name = "/semaphorep3";
    int sm_fd;
    int success;

    //Open Semaphore created by Server
    sem_t *sem = sem_open(&sem_name[0], 0);
    if(sem == SEM_FAILED)
        std::cout << "Error opening semaphore" << std::endl;
    
    // STEP 1: Create a shared memory location and initializing with necessary structure
    // Create and open shared memory
    shm_unlink(&sm_name[0]);    //unlink if already exists
    sm_fd = shm_open(&sm_name[0], 
                     O_CREAT|O_RDWR|O_EXCL, 
                     S_IRUSR | S_IWUSR);
    if(sm_fd == -1)
        std::cerr << "Error opening shared memory" << std::endl;

    // Set size of shared memory
    success = ftruncate(sm_fd, SIZE);
    if(success < 0)
        std::cerr << "Error setting size of shared memory" << std::endl;
    
    // Map shared memory to structure
    sm_struct_ptr = static_cast<SmStruct*>(
        mmap(0,
             SIZE, 
             PROT_WRITE | PROT_READ, 
             MAP_SHARED, 
             sm_fd, 
             0));
    if(sm_struct_ptr == MAP_FAILED)
        std::cerr << "Error mapping memory to structure" << std::endl;
    close(sm_fd);

    // Initialize structure with path string
    strncpy(sm_struct_ptr->path, &path[0], path.size());

    // Unblock Server once path has been added to shared memory
    sem_post(sem);

    // wait for text-server to save lines to shm
    // std::cout << "unlocked server" << std::endl;
    // std::cout << "waiting" << std::endl;
    // sem_wait(sem);
    // std::cout << "done waiting" << std::endl;
    //create threads to search

    sem_close(sem);
    // shm_unlink(&sm_name[0]);
    return 0;
}