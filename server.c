#include "server.h"
#include "server_cipher_hill_encryptor.h"

//Lee los parametros pasados por linea de comandos para
//inicializar el servidor.

void server_init(server_t* self, char* const* argv, password_t* key) {
    self->servicename = argv[1];
    self->key = key;

    password_map(self->key);
    printf("Servidor inicializado... esperando conexion.. \n");
}

void server_uninit(server_t* self){}

void receive_message_from_client(server_t* self) {
    socket_t socket;
	socket_t peer;
    cipher_hill_encryptor_t encryptor;

    socket_bind_and_listen(&socket, NULL, self->servicename);
    socket_accept(&socket, &peer);

    receive_size_from_client(self,&peer);
    
    receive_line_from_client(self,&peer);

    cipher_hill_encryptor_init(&encryptor,self);
    
    cipher_hill_encryptor_encrypt(&encryptor);

    /* no me anda el strcpy
    strncpy(self->message_to_encrypt,plaintext.line);*/

    /*OJO ACA CON LA MEMORIA, SI ES MAS GRANDE QUE EL OTRO SO-NA-MOS*/

    for( int i=0; i<sizeof(encryptor.message_to_encrypt); i++){
        self->message_read[i] = encryptor.message_to_encrypt[i];
    }

    send_encrypted_message_to_client(self,&peer);

    cipher_hill_encryptor_uninit(&encryptor);
    socket_uninit(&socket);
    socket_uninit(&peer);
}

void receive_size_from_client(server_t* self, socket_t* peer){
    char buffer[2];                     //constante ¡?¡?

    socket_receive(peer, buffer, 2);
    
    short int size = _socket_char_to_short(buffer);

    self->message_read_length = size;
}

void receive_line_from_client(server_t* self, socket_t* peer){    
    char buffer[MAX_LINE_SIZE];
    ssize_t bytes_received = 0;
    
    bytes_received = socket_receive(peer, buffer, self->message_read_length);
        
    self->message_read = (char *)malloc( (self->message_read_length) * sizeof(char) );

    for (int i=0 ; i < bytes_received ; i++){
        self->message_read[i] = buffer[i];
    }
}

void send_encrypted_message_to_client(server_t* self, socket_t* socket){
    socket_send_size(socket,(short int)sizeof(self->message_read));
    socket_send_message(socket,self->message_read,self->message_read_length);
}