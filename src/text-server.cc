#include "../inc/text-server.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <semaphore.h>
#include <fstream>
#include <vector>

TextServer::TextServer(std::string sm_name, std::string sem_name)
    : SharedMemoryManager(sm_name, sem_name) 
    {}
int TextServer::runServer(){
    // std::string sem_name = "/semaphorep3";
    const char EOT = '\004';
    std::string INV = "_INVALID_FILE";
    int sm_fd;
    int success;
    std::vector<std::string> file_lines;
    // Step 1: Start Server
    // Create semaphore
    sem_unlink(&sem_name[0]);   //unlink if exists
    sem_t *sem = sem_open(&sem_name[0], 
                          O_CREAT | O_EXCL, 
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 
                          0);
    if(sem == SEM_FAILED){
        std::cerr << "Error creating semaphore" << std::endl;
        return(-1);
    }
    std::cout << "SERVER STARTED" << std::endl;

    // Use semaphore to wait for Client to write path to shared memory
    sem_wait(sem);  

    // Step 2: Recieve filename and path from client
    // Step 3: Open shared Memory created by Client
    std::clog << "CLIENT REQUEST RECEIVED" << std::endl;

    // Open Memory
    sm_fd = shm_open(&sm_name[0], 
                    O_RDWR| O_EXCL, 
                    S_IRUSR | S_IWUSR);
    if(sm_fd == -1){
        std::cerr << "Error opening shared memory" << std::endl;
        return(-1);
    }
    // Map shared memory to structure
    sm_struct_ptr = static_cast<SmStruct*>(
        mmap(0, 
            SIZE,
            PROT_WRITE | PROT_READ, 
            MAP_SHARED,
            sm_fd, 
            0));
    close(sm_fd);
    if(sm_struct_ptr == MAP_FAILED){
        std::cerr << "Error mapping memory to structure" << std::endl;
        return(-1);
    }
    std::clog << "\tMEMORY OPEN" << std::endl;

    // Step 4: Use path to open file and write its contents to shared memory
    // Open file and read lines 
    std::ifstream in_file;
    in_file.open(sm_struct_ptr->path);
    if(in_file){
        std::string line;
        while(getline(in_file, line)){
            file_lines.push_back(line);
        }
    }
    else{
        file_lines.push_back(INV);
    }

    //TODO modify file_lines so that each element is string of size buffer_size

    // Add EOT character to last file lines
    file_lines.back() += EOT;

    // Write file lines to shared memory
    for(auto line : file_lines){
        // line += '\0';
        strncpy(sm_struct_ptr->buffer, &line[0], line.size()+1);
        sem_post(sem);
        sleep(.5);
        sem_wait(sem);
    }
    //AFTER READING path and search str
    //save lines of text to saved mem
    //signal client to search
    // sem_post(sem);
    sem_unlink(&sem_name[0]);
    return(1);
}