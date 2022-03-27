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
#include <pthread.h>

struct thread_args{
    size_t start_idx;
    size_t stop_idx;
};

TextClient::TextClient(std::string sm_name, std::string sem_name, std::string path, std::string search_str)
    : SharedMemoryManager(sm_name, sem_name) {
    this->path = path;
    this->search_str = search_str;
}
int TextClient::runClient(){
    int sm_fd;
    int success;

    //Open Semaphores created by Server
    sem_t *sem = sem_open(&sem_name[0], 0);
    if(sem == SEM_FAILED){
        std::cerr << "Error opening semaphore" << std::endl;
        return(-1);
    }
    sem_t *sem_two = sem_open(&sem_name_two[0], 0);
    if(sem_two == SEM_FAILED){
        std::cerr << "Error opening semaphore" << std::endl;
        return(-1);
    }
    // STEP 1: Create a shared memory location and initializing with necessary structure
    // Create and open shared memory
    shm_unlink(&sm_name[0]);    //unlink if already exists
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
    sm_struct_ptr->bufferSize = BUFFER_SIZE;
    strncpy(sm_struct_ptr->path, &path[0], path.size());

    // Unblock Server once path has been added to shared memory
    sem_post(sem);

    // Step 3: Read lines of text from shared memory to local storage
    // std::vector<std::string> sm_file_lines;
    while(file_lines.empty() || file_lines.back().find(EOT) == std::string::npos){
        // Loop until EOT character is found
        // Wait for server to store first lines into shared memory
        sem_wait(sem_two);
        file_lines.push_back(std::string(sm_struct_ptr->buffer));
        sem_post(sem);
    }

    // Remove EOT
    file_lines.back().erase(file_lines.back().find(EOT), 
                            sizeof(EOT));

    // Step 4: Search file lines for search strings with threads
    if(file_lines.back() == INV){
        // print "Invalid File" and skip search if server was unable to open file
        std::cerr << "Invalid File" << std::endl;
    }
    else{
        // Call search method with threads, passing 1/4 of lines to each thread
        std::cout << file_lines.size() << std::endl;
        std::vector<pthread_t> threads(N_THREADS);
        std::vector<size_t> idxs(N_THREADS);
        for(int i=0; i<N_THREADS; i++){
            idxs[i] = i*(file_lines.size() / N_THREADS);
            std::cout << idxs[i] << std::endl;
            pthread_create(&threads[i], 
                           nullptr, 
                           threaded_search, 
                           static_cast<void *>(&idxs[i]));
        }
        for(auto thread : threads){
            pthread_join(thread, nullptr);
        }

    }

    // Clean up
    sem_close(sem);
    sem_close(sem_two);
    close(sm_fd);
    munmap(sm_struct_ptr, SHM_SIZE);
    shm_unlink(&sm_name[0]);

    return(1);
}

void *TextClient::threaded_search(void *ptr){
    // Each thread searches file_lines and adds found lines to found_lines
    size_t start_idx = *static_cast<size_t*>(ptr);
    std::cout << start_idx << std::endl;
    // for(int i=start_idx; i<)
    return nullptr;
}

