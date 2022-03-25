#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <semaphore.h>
#include <errno.h>
// #include "inc/shared-memory-struct.h"
using std::cout;
using std::endl;
int main(){
    // char sm_name[9]="/shareme";
    std::string sm_name = "/share";
    int sm_fd;
    shm_unlink(&sm_name[0]);
    if ( sm_fd = shm_open(&sm_name[0], O_CREAT|O_RDWR|O_EXCL, S_IRUSR|S_IWUSR) < 0)
        cout << "error creating" << endl;
    int success = ftruncate(sm_fd, sizeof(int));
    if(success < 0)
        cout << success << "Error sizing" << errno <<endl;
    int * sm_ptr = static_cast<int *>(mmap(0, sizeof(int), PROT_WRITE|PROT_READ, MAP_SHARED, sm_fd, 0));
    if(sm_ptr==MAP_FAILED)
        cout << "failed map" <<endl;
    sm_ptr[0] = 345;
    munmap(sm_ptr, sizeof(int));
    close(sm_fd);
    return 0;
}