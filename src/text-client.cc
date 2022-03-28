/*
Written by Musa Azeem
This file defines the functions of the TextClient class
Functions:  
    Default constructor:
        calls parent constructor to initialize sm_name, sem_name, and sem_name_two
        initializes path and search_str with given strings
    runClient:
        This functions runs the text client:
        1.1) opens necessary semaphores, one for threads and two for synchornization with server
        1.2) creates shared memory and maps it to a "SmStruct" 
        2.1) passes file path and sizes to server through shared memory structure
        2.2) unblocks server with "sem" to read file path
        3) reads file lines from shared memory buffer as server writes to it
            reads until EOT character is found
            synchronizes with two semaphores
            splits each buffer read into lines, adding each line to "file_lines"
        4.1) if client recieves "INV" as file lines, it print "Invalid File" to stderr
        4.2) use threads to search 1/4 of "file_lines" per thread, each thread adds found lines to "found_lines"
            each thread is run with threaded_search function
            each thread is given a start and stop index to search
            the last thread created searches until the end of the lines to ensure no lines are missed
        4.3) wait for all threads to complete
        5) print all found lines
        6) destroy shared memory and close / destroy semaphores
        7) Return 1 on successful completion
    threaded_search:
        This static function is passed to threads to search a portion of "file_lines"
        It is given a start index, stop index, and instance of TextClient through a ThreadArgs struct
        Threads search the client's file_lines from start index to stop index,
            adding any found lines to client's "found_lines" member
        return a nullptr, which is unused
*/
#include "../inc/text-client.h"     // Using TextClient
#include "../inc/thread-args.h"     // Using ThreadArgs
#include <sys/mman.h>               // Using shared memory               
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <sstream>

TextClient::TextClient(std::string sm_name, std::string sem_name, std::string path, std::string search_str)
    : SharedMemoryManager(sm_name, sem_name) {
    this->path = path;
    this->search_str = search_str;
}
int TextClient::runClient(){
    int sm_fd;
    int success;

    // Open Semaphore for threads
    success = sem_init(&thread_sem, 0, 1);
    if(success < 0){
        std::cerr << "Error opening thread semaphore" << std::endl;
    }

    // Open Semaphores created by Server
    sem = sem_open(&sem_name[0], 0);
    if(sem == SEM_FAILED){
        std::cerr << "Error opening semaphore" << std::endl;
        return(-1);
    }
    sem_two = sem_open(&sem_name_two[0], 0);
    if(sem_two == SEM_FAILED){
        std::cerr << "Error opening semaphore" << std::endl;
        return(-1);
    }

    // STEP 1: Create a shared memory location and initialize with necessary structure
    // Unlink shared memory if it already exists
    shm_unlink(&sm_name[0]);

    // Create and open shared memory
    sm_fd = shm_open(&sm_name[0], 
                     O_CREAT|O_RDWR|O_EXCL, 
                     S_IRUSR | S_IWUSR);
    if(sm_fd == -1){
        std::cerr << "Error opening shared memory" << std::endl;
        return(-1);
    }
    // Set size of shared memory
    success = ftruncate(sm_fd, SHM_SIZE);
    if(success < 0){
        std::cerr << "Error setting size of shared memory" << std::endl;
        return(-1);
    }
    // Initialize structure - Map shared memory to structure
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

    // Step 2: Send file path to server through shared memory
    sm_struct_ptr->path_length = PATH_LEN;
    sm_struct_ptr->buffer_size = BUFFER_SIZE;
    strncpy(sm_struct_ptr->path, &path[0], path.size());

    // Unblock Server once path has been added to shared memory
    sem_post(sem);

    // Step 3: Read lines of text from shared memory to local storage
    std::string line;
    // Loop until EOT character is found
    while(file_lines.empty() || file_lines.back().find(EOT) == std::string::npos){
        // Wait for server to store lines into shared memory
        sem_wait(sem_two);
        // Split each buffer read by \n, and store in file_lines
        std::stringstream ss(sm_struct_ptr->buffer);
        while(std::getline(ss, line, '\n')){
            file_lines.push_back(line);
        }
        sem_post(sem);
    }

    // Remove EOT
    file_lines.back().erase(file_lines.back().find(EOT), sizeof(EOT));

    // Step 4: Search file lines for search strings with threads
    if(file_lines.back() == INV){
        // print "Invalid File" and skip search if server was unable to open file
        std::cerr << "Invalid File" << std::endl;
    }
    else{
        // Call search method with threads, passing 1/4 of lines to each thread
        std::vector<pthread_t> threads(N_THREADS);
        std::vector<ThreadArgs> args(N_THREADS);
        for(int i=0; i<N_THREADS; i++){
            args[i].client = this;
            args[i].start_idx = i*(file_lines.size() / N_THREADS);
            if(i != N_THREADS-1)
                args[i].stop_idx = (i+1)*(file_lines.size() / N_THREADS);
            else
                args[i].stop_idx = file_lines.size();
            pthread_create(&threads[i], 
                           nullptr, 
                           threaded_search, 
                           static_cast<void *>(&args[i]));
        }
        for(auto thread : threads){
            pthread_join(thread, nullptr);
        }

        // Step 5: Print found lines to stdout
        int i = 1;
        for(auto line : found_lines){
            std::cout << i << "\t"+line << std::endl;
            i++;
        }
    }

    // Step 6: Destroy shared memory location
    close(sm_fd);
    munmap(sm_struct_ptr, SHM_SIZE);
    shm_unlink(&sm_name[0]);

    // Close semaphores
    sem_destroy(&thread_sem);
    sem_close(sem);
    sem_close(sem_two);
    
    // Step 7: Return 1 if successful, which will prompt mian to return 0
    return(1);
}

void *TextClient::threaded_search(void *ptr){
    // Each thread searches file_lines and adds found lines to found_lines
    ThreadArgs args = *static_cast<ThreadArgs*>(ptr);
    for(int i=args.start_idx; i<args.stop_idx; i++){
        if(args.client->file_lines[i].find(args.client->search_str) != std::string::npos){
            sem_wait(&args.client->thread_sem);
            args.client->found_lines.push_back(args.client->file_lines[i]);
            sem_post(&args.client->thread_sem);
        }
    }
    return nullptr;
}

