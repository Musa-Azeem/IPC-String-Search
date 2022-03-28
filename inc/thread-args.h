/*
Written by Musa Azeem
ThreadArgs header
This file defines the ThreadArgs struct
Struct variables:
    start_idx       index of file lines to start search
    stop_idx        index of file lines to stop search
    client          pointer to instance of TextClient class
*/
#ifndef THREAD_ARGS_H
#define THREAD_ARGS_H

#include <unistd.h>
#include "text-client.h"

struct ThreadArgs{
    size_t start_idx;
    size_t stop_idx;
    TextClient *client;
};

#endif