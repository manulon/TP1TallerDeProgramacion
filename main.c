#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_reader.h"


int main(int argc, char* argv[]){
    file_reader_t file_reader;
    plaintext_t plaintext;
    password_t password;
    
	file_reader_init(&file_reader, argv[1]);
    password_init(&password, argv[2]);

    file_reader_iterator(&file_reader,&plaintext,&password);

    file_reader_uninit(&file_reader);
    password_uninit(&password);

    return 0;
}
