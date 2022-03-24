#include <iostream>
#include "inc/shared-memory-struct.h"
int main(){
    SmStruct sm = {};
    std::cout << sizeof(sm) << std::endl;
}