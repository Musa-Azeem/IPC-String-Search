#include "../inc/text-server.h"
#include "../inc/ipc_names.h"

int main(){
    TextServer server(SM_NAME, SEM_NAME);
    if(server.runServer() < 1)
        return 1;
    return 0;
}