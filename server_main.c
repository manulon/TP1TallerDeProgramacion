#include "server.h"
#include "common_plaintext.h"

int main(int argc, char* const* argv) {
    server_t server;
    password_t key;

    if (argc != 3) return -1;
  
    password_init(&key,argv[2]);
    server_init(&server,argv,&key);
    
    receive_message_from_client(&server);

    server_uninit(&server);

    return 0;
}