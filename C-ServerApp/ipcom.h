#ifndef IPCOM_H_INCLUDED
#define IPCOM_H_INCLUDED

/*
    Definir aqui todas las headers que se requiera en la implementacion de los
    metodos para evitar errores al momento de implementar el codigo
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>

int read_in(int client_d,char *buff,int len);
int open_listener_socket();
void bind_port(int socket,int port);
int send_msg(int socket,char *msg);
void handle_shutdown(int sig);

//Declaracion de puntero de una funcion sin parametros
typedef void (*onclose_handler)();
//Con esta funcion definimos el puntero de la funcion que se va ejecutar al cerrar la aplicacion
void set_on_close(onclose_handler event);

//Declaracion de puntero de una funcion sin parametros
typedef void (*onread_handler)(int hnd_client);
//Con esta funcion definimos el puntero de la funcion que se va ejecutar al cerrar la aplicacion
void init_read(int hnd_listener,onread_handler on_event);




#endif // IPCOM_H_INCLUDED
