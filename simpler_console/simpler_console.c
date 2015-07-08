#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#define SIZE 200 
#define MPARAM 200 //maximo numero de parametros, maximum number of parameters


int cortar_en_piezas(char *cadena, char **retorno); //obtengo parametros, I take the parameters
void liberar_params(char **params);



int main(int argc, char* argv, char** envp){ //ha! sorpresa tercer parametro, wild thrird parameter appears
 char linea_comandos[SIZE]; //tamaño maximo que concedere, maximum size to be given to the command line
 char *params[MPARAM];
 char extralines[800];

 params[0] = NULL; //in case of mistakes
 pid_t pid;


 printf("\n******************************\n");
 while(1){
   printf("ingresad vuestros comandos:~$ "); //it says input your commands
   fgets(linea_comandos,SIZE, stdin);
   linea_comandos[strlen(linea_comandos) -1] = '\0'; //al final deja un salto de linea, put and end of line at the end
   if(strncmp(linea_comandos, "exit", SIZE) == 0 ){
     printf("\nHasta la vista .\n");
     break;
   }else if(strncmp(linea_comandos, "", SIZE) == 0 ){
     continue;
   }
   cortar_en_piezas(linea_comandos,params);
   if((pid=fork())<0){
     printf("Ha ocurrido un error, sorry bro");
     return 0;
   }else if(pid == 0){
     if(execve(params[0],params,envp) == -1){ 
       if(errno == ENOENT){
         strcpy(extralines,"/bin/"); //directorio estandar, standar directories
         strcat(extralines,params[0]);
         if(execve(extralines,params,envp) == -1){
           if(errno == ENOENT){
             strcpy(extralines,"/usr/bin/");
             strcat(extralines,params[0]);
             if(execve(extralines,params,envp) == -1){
               printf("Error ejecutando parametro: %s\n",strerror(errno));
             }
           }else printf("Error ejecutando parametro: %s\n",strerror(errno));
         }
       }else printf("Error ejecutando parametro: %s\n",strerror(errno));
     }
     _exit(0);
   }else{
     wait();
   }
   liberar_params(params);
   printf("\n");
 }
return 0;
}

int cortar_en_piezas(char *cadena, char **retorno){
  int iniciosub = 0;
  int finalsub = 0;
  int contador = 0; //la cadena actual que estoy asignando

  while(cadena[finalsub] != '\0'){
    if(cadena[finalsub] != ' '){
     finalsub++;        
    }else{
     retorno[contador] = (char *)malloc((finalsub-iniciosub+1)*sizeof(char));
     retorno[contador] = strndup(cadena+iniciosub, finalsub-iniciosub);
     finalsub += 1;
     iniciosub = finalsub;
     contador++;
    }
  }
  retorno[contador] = strndup(cadena+iniciosub, finalsub-iniciosub);
  retorno[++contador] = NULL;
  return 0;
}

void liberar_params(char **params){
  int iterador = 0;
  while(params[iterador] != NULL){
    free(params[iterador]);
    iterador++;
  }
}

