#include "../inc/text-server.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <semaphore.h>


int TextServer::runServer(){
    std::string sem_name = "/semaphorep3";
    int sm_fd;
    int success;
    // Create semaphore
    sem_unlink(&sem_name[0]);   //unlink if exists
    sem_t *sem = sem_open(&sem_name[0], O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0); //TODO add modes
    if(sem == SEM_FAILED)
        std::cout << "Error creating semaphore" << std::endl;
    std::cout << "waiting" << std::endl;
    sem_wait(sem);
    // Step 1: Start Server
    // Step 2: Recieve filename and path from client
    sm_fd = shm_open(&sm_name[0], O_RDWR| O_EXCL, S_IRUSR | S_IWUSR);
    if(sm_fd == -1)
        std::cerr << "Error opening shared memory" << std::endl;
    sm_struct_ptr = static_cast<SmStruct*>(mmap(0, sizeof(SmStruct), PROT_WRITE | PROT_READ, MAP_SHARED, sm_fd, 0));
    close(sm_fd);
    if(sm_struct_ptr == MAP_FAILED)
        std::cerr << "Error mapping memory to structure" << std::endl;
    std::cout << sm_struct_ptr->path << std::endl;
    
    //AFTER READING path and search str
    //save lines of text to saved mem
    std::cout << "saving stuff to shm" << std::endl;
    sleep(3);
    //signal client to search
    // sem_post(sem);
    std::cout << "unlocked client" << std::endl;
    sem_unlink(&sem_name[0]);
    return(0);
}