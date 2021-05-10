#include "common_socket.h"

void socket_init
(socket_t* self, int fd){
	self->fd = fd;
}

void socket_uninit
(socket_t* self){
	if (!self) {return;}
    if (shutdown(self->fd, SHUT_RDWR) == -1) {
		fprintf(stderr, "socket_uninit-->shutdown: %s\n", strerror(errno));
    } 
    if (close(self->fd) == -1) {
		fprintf(stderr, "socket_uninit-->close: %s\n", strerror(errno));
    }
}

bool socket_bind_and_listen
(socket_t* self, const char* hostname, const char* servicename){
    bool bind_error = false;
	int val = 1;
	struct addrinfo *addr, *addr_list;
    struct addrinfo hints;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(hostname,servicename,&hints,&addr_list);

	for (addr = addr_list; addr && !bind_error; addr = addr->ai_next) {
        self->fd = socket
        (addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if (bind(self->fd, addr->ai_addr, addr->ai_addrlen) == 0) 
            bind_error = true;
    }
    freeaddrinfo(addr_list);
    
    if (!bind_error) {
		fprintf(stderr, "socket_bind_and_listen-->bind: %s\n", strerror(errno));
        return false;
    }

	socket_init(self, self->fd);

	if (listen(self->fd, 10) < 0) {
		socket_uninit(self);
		fprintf(stderr, "socket_bind_and_listen-->listen: %s\n", strerror(errno));
		return false;
	}
	return true;
}

int socket_accept
(socket_t* listener, socket_t* peer){
	int fd = -1;
    
	if ((peer->fd = accept(listener->fd, NULL, NULL)) < 0) {
		fprintf(stderr, "socket_accept-->accept: %s\n", strerror(errno));
        return fd;
	}
    
    fd = 0;
	return fd;
}

void socket_connect
(socket_t* self, const char* hostname, const char* servicename){
	self->fd=0;
    
    bool is_connected = false;
    int s = 0;
    struct addrinfo hints;
    struct addrinfo* results;
    struct addrinfo* addr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    s = getaddrinfo(hostname,servicename,&hints,&results);

    if (s != 0) {
        printf("Error en getaddrinfo: %s\n", gai_strerror(s));
        return;
    }

    for (addr = results; addr != NULL && !is_connected ; addr = addr->ai_next) {
        self->fd = socket
        (addr->ai_family, addr->ai_socktype, addr->ai_protocol);

        if (self->fd == -1){
            printf("Error: %s\n", strerror(errno));
        }else{
            s = connect(self->fd, addr->ai_addr, addr->ai_addrlen);
            if ( s == -1 ){
                perror("Error");
                printf("%s\n",strerror(errno));
                close(self->fd);
            }
            is_connected = (s != -1);
        }
    }
    freeaddrinfo(results);

    if ( is_connected == false ){
        return;
    }
}

//https://stackoverflow.com/questions/2952895/copying-a-short-int-to-a-char-array
void _socket_short_to_char(short int size,unsigned  char* buffer){
    buffer[0] = (size >> 8) & 0xff;
    buffer[1] = size & 0xff;
}

//https://stackoverflow.com/questions/25787349/convert-char-to-short/25787777
short int _socket_char_to_short(unsigned char* buffer){  
    short int pshort;

    pshort = (buffer[0] << 8) | buffer[1];
    
    return pshort;
}
