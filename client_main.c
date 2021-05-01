#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

int main(int argc, char* argv[]){
    client_t client;
    socket_t socket;

    if(argc != 4) return -1;

    client_init(&client,argv);

    client_send_message_to_server(&client,&socket);
        
    client_receive_encrypted_message_from_server(&client,&socket);

    client_decrypt_message(&client);

    printf("%s \n",client.message);

    client_uninit(&client);
    socket_uninit(&socket);

    return 0;
}
