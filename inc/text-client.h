#ifndef TEXT_CLIENT_H
#define TEXT_CLIENT_H

#include "./shared-memory-manager.h"
#include <string>
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
        static void *threaded_search(void *ptr);
        sem_t thread_sem;
};

struct ThreadArgs{
    size_t start_idx;
    size_t stop_idx;
    TextClient *client;
};

#endif