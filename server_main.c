#include "server.h"
#include "server_plaintext.h"
#include "server_password.h"

int main(int argc, char* const* argv) {
    server_t server;
    password_t key;

    if (argc != 3) return -1;
  
    password_init(&key,argv[2]);
    server_init(&server,argv,&key);

    server_communicate_with_client(&server);

    server_uninit(&server);
    password_uninit(&key);

    return 0;
}
