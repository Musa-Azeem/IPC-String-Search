/*
Written by Musa Azeem
This file contains the main method for text-server
    this main method creates an instance of TextServer with
        constant ipc names
    main method returns 1 if server returns an error, 
        and does not terminate otherwise
*/
#include "../inc/text-server.h"
#include "../inc/ipc-names.h"

int main(){
    TextServer server(SM_NAME, SEM_NAME);
    if(server.runServer() < 1)
        return 1;
    return 0;
}