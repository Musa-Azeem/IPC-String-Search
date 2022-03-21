#include "../inc/text-client.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define SM_SIZE 4096

TextClient::TextClient(std::string sm_name, std::string path, std::string search_str): SharedMemoryManager(sm_name) {
    this->path = path;
    this->search_str = search_str;
    // sm_obj.path = path;
    // sm_obj.search_str = search_str;
}
int TextClient::runClient(){
    int sm_fd;
    int success;
    // STEP 1: Create a shared memory location and initializing with necessary structure
    // Create and open shared memory
    sm_fd = shm_open(&sm_name[0], O_CREAT|O_RDWR|O_EXCL, 0666);
    if(sm_fd == -1)
        std::cerr << "Error opening shared memory" << std::endl;
    // Set size of shared memory
    success = ftruncate(sm_fd, sizeof(SmStruct));
    if(success < 0)
        std::cerr << "Error setting size of shared memory" << std::endl;
    // Map shared memory to structure
    sm_struct_ptr = (SmStruct*)mmap(0, sizeof(SmStruct), PROT_WRITE | PROT_READ, MAP_SHARED, sm_fd, 0);
    return 0;
}