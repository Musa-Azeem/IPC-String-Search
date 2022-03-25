#include "inc/shared-memory-struct.h"
#include <iostream>
int main(){
    SmStruct sm;
    std::cout << sizeof(SmStruct) << std::endl;
    std::cout << sizeof(sm.buffer) << std::endl;
    std::cout << sm.bufferSize << std::endl;
}