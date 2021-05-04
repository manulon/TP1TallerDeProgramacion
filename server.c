#include "server.h"
#include "server_cipher_hill_encryptor.h"
#include "server_password.h"

//Lee los parametros pasados por linea de comandos para
//inicializar el servidor.

void server_init(server_t* self, char* const* argv, password_t* key) {
    self->servicename = argv[1];
    self->key = key;
    self->message_read_length = 0;

    password_map(self->key);
    printf("Servidor inicializado... esperando conexion.. \n");
}

void server_uninit(server_t* self){
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
}

void receive_message_from_client(server_t* self) {
    socket_t socket;
	socket_t peer;
    cipher_hill_encryptor_t encryptor;

    bool bind_and_listen_ok = false;

    bind_and_listen_ok =
        socket_bind_and_listen(&socket, NULL, self->servicename);
    socket_accept(&socket, &peer);
    if ( bind_and_listen_ok == true ){
        ssize_t bytes_received;

        bytes_received = receive_size_from_client(self,&peer);    
        bytes_received += receive_line_from_client(self,&peer);

        while (bytes_received > 0){
            cipher_hill_encryptor_init(&encryptor,self);
            cipher_hill_encryptor_encrypt(&encryptor);

            free(self->message_read);
            self->message_read_length = encryptor.message_to_encrypt_length;
            self->message_read = (unsigned char *)malloc
                ( (self->message_read_length+1) * sizeof(unsigned char));

            for ( int i = 0 ; i < self->message_read_length ; i++ ){
                self->message_read[i] = (encryptor.message_to_encrypt[i] % 26);
            }

            cipher_hill_encryptor_uninit(&encryptor);
            send_encrypted_message_to_client(self,&peer);
            bytes_received = receive_size_from_client(self,&peer);    
            bytes_received += receive_line_from_client(self,&peer);
        }
    }
        socket_uninit(&socket);
        socket_uninit(&peer);
}


ssize_t receive_size_from_client(server_t* self, socket_t* peer){
    unsigned char buffer[2];                     //constante ¡?¡?
    ssize_t bytes_received = 0;
    
    bytes_received = socket_receive(peer, buffer, 2);

    if ( bytes_received > 0 ){
        short int size = _socket_char_to_short(buffer);
        self->message_read_length = size;
    }
    
    return bytes_received;
}

ssize_t receive_line_from_client(server_t* self, socket_t* peer){    
    unsigned char* buffer;

    buffer = (unsigned char *)malloc
    ( (self->message_read_length+1) * sizeof(char));


    ssize_t bytes_received = 0;

    bytes_received = socket_receive(peer, buffer, self->message_read_length);
    
    if ( bytes_received > 0 ){
        self->message_read = (unsigned char *)malloc
        ( (self->message_read_length+1) * sizeof(unsigned char) );

    for (int i=0 ; i < bytes_received ; i++){
            self->message_read[i] = buffer[i];
        }
    }    

    free(buffer);

    return bytes_received;
}

void send_encrypted_message_to_client(server_t* self, socket_t* socket){
    socket_send_size(socket,self->message_read_length);
    socket_send_message(socket,self->message_read,self->message_read_length);
    free(self->message_read);
}
