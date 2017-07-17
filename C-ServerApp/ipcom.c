/*
    No es necesario declarar las headers para
    hacer la comunicacion IP por que ya fueron definidas
    en el header file ipcom.h
*/

#include "ipcom.h"

onclose_handler __on_close_event__;

//Funcion para iniciar a leer las conexiones entrantes
void init_read(int hnd_listener,onread_handler on_event){
     struct sockaddr_storage client_addr;
     unsigned int addr_sz;
     int hnd_client;
     pid_t pid;

     if(listen(hnd_listener,10)==-1){//Indicar la catidad maxima de conexiones a recibir
        printf("\nDemasiadas conexiones por el server esta ocupado!!\n");
        exit(1);
     }

     printf("Esperando conexion del Socket...\n");
     while(1){

        addr_sz = sizeof(client_addr);

        hnd_client = accept(hnd_listener,(struct sockaddr*)&client_addr,&addr_sz);

        if(hnd_client==-1){
            printf("\n\n** ERROR AL CONECTAR CON EL CLIENTE **\n\n");
            exit(1);
        }

        pid = fork();//Crear una copia del proceso usando la funcion fork

        if(!pid){
            //Se creo bien el ChildProcess
            close(hnd_listener);//Cerrar el main socket abierto
            printf("- Cliente Id : %d\n",hnd_client);

            if(send_msg(hnd_client,"\n\nInternet Knock-Knock Protocol Server\r\nVersion 1.0\r\n\nKnock! Knock!\r\n")!=-1){

                on_event(hnd_client);//Ejecutar evento pasandole como valor el socketid del cliente connectado

                printf("\nCerrando la conexion del cliente Id %d\n",hnd_client);
                close(hnd_client);//Cerrar la conexion del cliente
                exit(0);//Cerrar subproceso
            }

        }else if(pid==-1){
            printf("\t**NO SE PUDO CREAR CHILD PROCSESS**\n");
        }

        //Cerrar el socket del cliente en el ParentProcess despues de crear el ChildProcess
        //para continuar aceptando conexiones
        close(hnd_client);

     }

}

//Funcion a ejecutar cuando se precione Ctrl+C en la aplicacion.
void handle_shutdown(int signal){
    printf("\rSignal No: %d \n",signal);
    printf("Cerrando conexiones abiertas...\n");
    __on_close_event__();//Ejecutar funcion
    printf("\n\n** ADIOS! :D **\n\n");
    exit(0);//Cerra aplicacion

}

//Establecer la el puntero de la funcion que se va ejecutar al cerra la aplicacion
void set_on_close(onclose_handler event){
    __on_close_event__ = event;
}

//Escribir mensaje al cliente
int send_msg(int socket,char *msg){
    int r = send(socket,msg,strlen(msg),0);
    return r;
}


//Hacer bind en el puerto donde se va hacer la lectura de lo que el cliente envie
void bind_port(int socket, int port){
     struct sockaddr_in name;
     int reuse = 1;

     name.sin_family = PF_INET;
     name.sin_port = (in_port_t)htons(port);
     name.sin_addr.s_addr = htonl(INADDR_ANY);

     if(setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char *)&reuse,sizeof(int))==-1){
        printf("** NO SE PUEDE REUSAR EL PUERTO %d",port);
        exit(1);
     }

     if(bind(socket,(struct sockaddr *)&name,sizeof(name))==-1){
        printf("** NO SE PUEDE UTILIZAR SOCKET PARA EL PUERTO %d **",port);
        exit(1);
     }
}

//Crear un socket Listener
int open_listener_socket(){
    int s = socket(PF_INET,SOCK_STREAM,0);
    return s;
}

//Leer lo que el cliente escriba
int read_in(int client_d,char *buff,int len){
    char *s = buff;
    int slen = len;
    int c;

    printf("- Esperando respuesta\n");
    c = recv(client_d,s,slen,0);

    while((c > 0) && (s[c-1]!='\n')){
        s+=c;
        slen-=c;
        c = recv(client_d,s,slen,0);

    }

    if(c<0){
        return c;
    }else if(c==0){
        buff[0]='\0';
    }else{
        s[c-1]='\0';
    }

    printf("R = %s\n",buff);

    return len-slen;

}
















