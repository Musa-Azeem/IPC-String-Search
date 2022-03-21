#include "../inc/text-client.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>

TextClient::TextClient(std::string path, std::string search_str){
    this->path = path;
    this->search_str = search_str;
}
int TextClient::runClient(){
    // 
    return 0;
}