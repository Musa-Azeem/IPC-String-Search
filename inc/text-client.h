/*
Written by Musa Azeem
TextClient header
This file defines the TextClient class and one related constant
Definitions:
    N_THREADS           Number of threads used to search file lines
Constructors:
    default             (string sm_name, string sem_name, string path, string search_str)
        initializes     sm_name, sem_name, path, and search_str
Class Variables:
    variables inherited from SharedMemoryManager
    path                path and filename of file to search
    search_str          string to search for
    file_lines          lines of file read from shared memory
    found_lines         lines of file that search_str was found in
    thread_sem          unnamed semaphore to synchronize threads
Class Functions:
    runClient           runs shared memory client
    threaded_search     threads search file lines for search string
*/
#ifndef TEXT_CLIENT_H
#define TEXT_CLIENT_H

#include "./shared-memory-manager.h"
#include <string>
#include <vector>
#include <semaphore.h>

#define N_THREADS 4

class TextClient: SharedMemoryManager {
    public:
        TextClient(std::string sm_name, std::string sem_name, std::string path, std::string search_str);
        int runClient();
    private:
        std::string path;
        std::string search_str;
        std::vector<std::string> file_lines;
        std::vector<std::string> found_lines;
        sem_t thread_sem;
        static void *threaded_search(void *ptr);
};

#endif