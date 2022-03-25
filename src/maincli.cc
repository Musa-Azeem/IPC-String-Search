#include "../inc/text-client.h"
int main(){
    TextClient client("/sm_p3", "/sem_p3", "dat/del", "hello");
    client.runClient();
    return 0;
}