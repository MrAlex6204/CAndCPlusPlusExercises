#include <stdio.h>
#include <stdlib.h>
//Implementar nuestro header para realizar la comunicacion IP
#include "ipcom.h"



int hnd_listener;

void fnc_conn_close_event(){//Funcion que se va ejecutar al cerrar con Ctrl+C
    if(hnd_listener){
        printf("- Conexion : %d\n",hnd_listener);
        close(hnd_listener);//Cerrar conexion existente
    }
}

void on_read_event(int hnd_client){
    char buff[255];

    if(read_in(hnd_client,buff,255)!=-1){//Leer lo que el usuario escriba

        //Comparar para ver si escribio Who's there?
        if(strncasecmp("Who's there?",buff,12)){
            send_msg(hnd_client,"You should say 'Who's there?\r\n");
        }else{
            if(send_msg(hnd_client,"I'm Oscar! >\r\n")!=-1){
                read_in(hnd_client,buff,255);//Esperar que el usuario escriba

                if(strncmp("Oscar who?",buff,10)){
                 send_msg(hnd_client,"You should say 'Oscar who?'\r\n");
                }else{
                    send_msg(hnd_client,"Oscar silly question,you get a silly answer!\r\n");
                }
            }

        }

    }else{
        printf("\n\n**ERROR AL LEER EL STREAM DEL CLIENTE**\n\n");
    }

}

int main()
{

    if(signal(SIGINT,handle_shutdown)==-1){
        printf("\nNo se puede implementar la interrupcion Ctrl+C\n");
        exit(1);
    }

    set_on_close(fnc_conn_close_event);//Indicamos la funcion que se va ejecutar al cerrar la conexion con Ctrl+C

    //Abrir socket y obtener el handle id.
    hnd_listener = open_listener_socket();

    if(hnd_listener == -1 ){
        printf("Error al abrir socket!\n");
        exit(1);
    }

    printf("Socket Id : %d\n",hnd_listener);


    bind_port(hnd_listener,30000);//Hacer el bind del port 30000

    //Iniciar la lectura del server, pasando como parametro
    //el puntero de la funcion que va recibir la conexion del cliente
    init_read(hnd_listener,on_read_event);

    return 0;
}








