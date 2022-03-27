#include "../inc/text-client.h"
#include "../inc/ipc-names.h"
#include <iostream>

int main(int argc, char **argv){
    if(argc != 3){
        std::cout << "usage: ./text-client file_path search_string" << std::endl;
        return 1;
    }
    TextClient client(SM_NAME, SEM_NAME, argv[1], argv[2]);
    if(client.runClient() < 0){
        return 1;
    }
    return 0;
}