#include "../inc/text-client.h"
int main(int argc, char **argv){
    TextClient client("/sm_p3", "/sem_p3", argv[1], "hello");
    client.runClient();
    return 0;
}