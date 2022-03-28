/*
Written by Musa Azeem
This file defines ipc locations shared between the text-client and text-server
Definitions:
    SEM_NAME    location for first named semaphore used in TextClient and TextServer classes
    SM_NAME     location for shared memory used in TextClient and TextServer classes
*/
#ifndef IPC_NAMES_H
#define IPC_NAMES_H

#define SEM_NAME "/csce311_semaphore"
#define SM_NAME "/csce311_shared_memory"

#endif
