/*
Written by Musa Azeem
TextServer header
This class defines the TextServer class
Constructors:
    default:            (string sm_name, string sem_name)
        initializes     sm_name, sem_name
Class variables:
    variables inherited from SharedMemoryManager
Class functions:
    runServer           runs shared memory server
*/
#ifndef TEXT_SERVER_H
#define TEXT_SERVER_H

#include "shared-memory-manager.h"
#include <string>

class TextServer: SharedMemoryManager {
    public:
        TextServer(std::string sm_name, std::string sem_name);
        int runServer();
};

#endif