#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

int main(int argc, char* argv[]){
    client_t client;
    socket_t socket;

    if (argc != 4) return -1;

    client_init(&client,argv);

    client_init_connection(&client,&socket);

    client_send_message_to_server(&client,&socket);

    client_uninit(&client);
    socket_uninit(&socket); // iria en uninit connection !!!

    return 0;
}
