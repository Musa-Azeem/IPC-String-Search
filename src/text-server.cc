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
#include <csignal>
#include <signal.h>

TextServer::TextServer(std::string sm_name, std::string sem_name)
    : SharedMemoryManager(sm_name, sem_name)
    {}
int TextServer::runServer(){
    int sm_fd;
    int success;
    std::string path;
    size_t buffer_size;
    std::vector<std::string> file_lines;

    // Step 1: Start Server
    std::cout << "SERVER STARTED" << std::endl;

    // Destroy semphores if they exist
    sem_destroy(sem);
    sem_unlink(&sem_name[0]);
    sem_destroy(sem_two);
    sem_unlink(&sem_name_two[0]);

    // Create semaphores
    sem = sem_open(&sem_name[0], 
                          O_CREAT | O_EXCL, 
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 
                          0);
    if(sem == SEM_FAILED){
        std::cerr << "Error creating semaphore 1" << std::endl;
        return(-1);
    }
    sem_two = sem_open(&sem_name_two[0], 
                          O_CREAT | O_EXCL, 
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 
                          0);
    if(sem_two == SEM_FAILED){
        std::cerr << "Error creating semaphore 1" << std::endl;
        return(-1);
    }

    // Stay open for client connections
    while(true){
        // Remove file_lines from last run
        file_lines.clear();

        // Use semaphore to wait for Client to write path to shared memory
        sem_wait(sem);  

        // Step 2: Recieve filename and path from client
        // Step 3: Open shared Memory created by Client

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
                SHM_SIZE,
                PROT_WRITE | PROT_READ, 
                MAP_SHARED,
                sm_fd, 
                0));
        if(sm_struct_ptr == MAP_FAILED){
            std::cerr << "Error mapping memory to structure" << std::endl;
            return(-1);
        }

        // Recieve the filename and path from client
        path = sm_struct_ptr->path;
        buffer_size = sm_struct_ptr->buffer_size;

        std::clog << "CLIENT REQUEST RECEIVED" << std::endl;
        std::clog << "\tMEMORY OPEN" << std::endl;

        // Step 4: Use path to open file and write its contents to shared memory
        // Open file
        std::clog << "\tOpening: " << path << std::endl;
        std::ifstream in_file;
        in_file.open(path);
        if(in_file){
            size_t bytes_read;
            std::string line;
            file_lines.push_back("");
            while(getline(in_file, line)){
                if((bytes_read+line.size()+1) < buffer_size){
                    // Add lines to same string until it reaches shared memory's buffer size
                    file_lines.back() += line+"\n";
                    bytes_read += line.size() + 1;
                }
                else{
                    // Once string reaches shared memory's buffer size, create new element in vector
                    file_lines.push_back(line+"\n");
                    bytes_read = line.size()+1;
                }
            }
        }
        else{
            // Indicate to client if file open failed
            file_lines.push_back(INV);
        }
        // Close file
        in_file.close();
        std::clog << "\tFile Closed" << std::endl;

        // Add EOT character to last file lines
        file_lines.back() += EOT;

        // Write file lines to shared memory
        for(auto line : file_lines){
            strncpy(sm_struct_ptr->buffer, &line[0], line.size()+1);
            sem_post(sem_two);
            sem_wait(sem);
        }

        // Close shared memory
        close(sm_fd);
        munmap(sm_struct_ptr, SHM_SIZE);
        std::clog << "\tMemory Closed" << std::endl;
    }
    return(1);
}