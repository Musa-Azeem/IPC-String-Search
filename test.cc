#include "inc/shared-memory-struct.h"
#include <iostream>
int main(){
    SmStruct sm;
    std::cout << sizeof(SmStruct) << std::endl;
    std::cout << sizeof(sm.buffer) << std::endl;
    std::cout << sm.bufferSize << std::endl;
    std::cout << SHM_SIZE-(2*sizeof(size_t))-PATH_LEN << std::endl;
    std::cout << BUFFER_SIZE << std::endl;

}