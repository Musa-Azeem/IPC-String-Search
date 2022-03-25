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
// #include "inc/shared-memory-struct.h"
using std::cout;
using std::endl;
int main(){
    char sm_name[9]="/shareme";
    int sm_fd;
    if( sm_fd= shm_open(sm_name, O_RDONLY, 0660) <0)
        cout << "error oppening" << endl;
    int * sm_ptr = static_cast<int *>(mmap(0, sizeof(int), PROT_READ, MAP_SHARED, sm_fd, 0));
    if(sm_ptr==MAP_FAILED)
        cout << "failed map" <<endl;
    int x = sm_ptr[0];
    cout << x << endl;
    munmap(sm_ptr, sizeof(int));
    close(sm_fd);
    shm_unlink(sm_name);
    return 0;
}