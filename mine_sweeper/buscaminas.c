#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MINAS 5

//Nota algunos de los caracteres ascii utilizados son diferentes para linux como el 178 o el 007 que produce un sonido

void crear_tablero(char T1[7][7],char T0[7][7]);// ,struct minas *mina
void dibujar_tablero(char T0[7][7], int muerte);
void pedir_dato(char *i, char *j, int *poner_bandera);
void procesar(char T0[7][7], char T1[7][7],char *i,char *j, int *muerte, int *victoria, int poner_bandera);


int main(void){
    
//    struct minas mina[20];
    char T0[7][7];//={{178,178,178,178,178,178,178},];
    char T1[7][7];//={{48,48,48,48,48,48,48},};
    char i, j;
    int muerte=0;
    int victoria=0; // este contador servira para saber cuando perdio
    int poner_bandera=0; //marca ? si el usuario decide no saber si es mina o no
    int terminar_juego=0;
    
     //crea el escenario
    while(1){  //while para jugar mas de una partida.   
    crear_tablero(T1,T0);
    
    while(1){
    dibujar_tablero(T0, muerte);
    if(muerte==1){
                  printf("\n ¡ ¡¡MUERTE !! ! ");
                  break;
                  }
    if(victoria==28){
                     printf("¡¡FELICIDADES A GANADO!!");
                     }
    pedir_dato(&i, &j, &poner_bandera);
    procesar(T0, T1, &i, &j, &muerte, &victoria, poner_bandera);
    poner_bandera=0;   //reinicia el contador para saber si el usuario desear marcar como mina o no
    }
    printf("¿Desea terminar el juego? (s)(n)\n"); //este getchar es para que en windows no se salga de la consola al probarlo.
    int respuesta; //esta variable solo servira como una auxiliar.
    respuesta = getchar();
    while(getchar() != '\n');
    if(respuesta == 's'){return 0;}
    if(respuesta != 's')printf("\nEntonces continuar jugando");
    muerte=0;
    victoria=0;
}//  fin del while != terminar juego
    return 0;
    }
    
    
void crear_tablero(char T1[7][7],char T0[7][7]){ // ,struct minas *mina
     int i=0,j=0, contador, bandera;
     
     for(i=0;i<7;i++){
                      for(j=0;j<7; j++){
                                   T1[i][j]=48;
                                   T0[i][j]=178;
                                   }
                      }
     //creando las minas aleatoriamente.
     srand(time(NULL)); //generar numeros aleatorios para poner la bomba
     for(i=0; i<MINAS; i++){
     while(1){
                   int fila=0, columna=0;
                   fila= rand() % 7;
                   columna =rand() % 7;
                   if(T1[fila][columna] != -2){
                 T1[fila][columna]=254; //colocando la mina.
                 break;
                 } // fin del if
              } //fin del while
     }// fin del for
                      
     
     //colocando los numeros.
     i=0;j=0;
     for(i=0; i<7;i++){
              for(j=0; j<7; j++){
                       contador=0;
                       if(i-1>=0 && j-1 >=0){   //cuenta si mina arriva izquierda
                                if(T1[i-1][j-1]==-2){
                                                    contador++;
                                                    }
                                                    }
                        if(j-1>=0){        
                                if(T1[i][j-1]==-2){ //cuenta si mina izquierda
                                                  contador++;
                                                  }
                                                  }
                         if(i-1>=0){                                        
                                if(T1[i-1][j]== -2){ //cuenta si mina arriva
                                               contador++;
                                               }
                                               }
                         
                         if(i-1>=0 && j+1 < 7){   //cuenta si mina arriva derecha
                                  if(T1[i-1][j+1]==-2){
                                                      contador++;
                                                      }
                                }
                        if(j+1 <7){ //cuenta si mina derecha
                               if(T1[i][j+1]==-2){
                                                 contador++;
                                                 }                        
                               }
                               
                        if(i+1 < 7 && j+1 < 7){ //cuenta si mina abajo derecha
                               if(T1[i+1][j+1]== -2){
                                                contador++;
                                                }
                               }
                        if(i+1<7){
                                  if(T1[i+1][j]==-2){ //cuenta si mina abajo
                                                    contador++;
                                                    }
                                  }
                        if(i+1<7 && j-1 >=0){ //cuenta si mina abajo izquierda
                                 if(T1[i+1][j-1]== -2){
                                                  contador++;
                                                  }
                                 }
                        if(contador>0 && T1[i][j] != -2){
                                       T1[i][j] = contador+48;
                                       }                   
                       }// fin del for j
              
              } // fin del for i
     
     
     
     
}// fin de la funcion dibujar_tablero.    
    
void dibujar_tablero(char T0[7][7], int muerte){
     int i=0, j=0;
     if(muerte==0)printf("\n\n\n\n\t\t\t  %c%c\n",002,007);
     else printf("\n\n\n\n\t\t\t  %c%c\n",'X',007);
     printf("\t   1    2    3    4    5    6    7\n");
     printf("\t=====================================\n");
     for(i=0; i<7;i++){
              printf("fila %d  ",i+1);
              for(j=0; j<7; j++){
                       printf("| %2c ",T0[i][j]);
                       }
                       printf(" |\n");
                       printf("\t=====================================\n");
              }
     }

void pedir_dato(char *i, char *j, int *poner_bandera){
     char fila, columna;
     int bandera =0;
     int marcarbandera=0;
     
     while (bandera ==0){
     printf("\nIngrese fila: ");
     fila=getchar();
     while(getchar()!= '\n');
     if(fila<'1' || fila > '7'){
                 printf("\nError ingresando fila...\n");
                 }
     else{
          *i = fila-48;
          bandera=1;
          }
          }//fin del while
     bandera=0;
     while (bandera ==0){  //pidiendo la columna
     printf("\nIngrese columna : ");
     columna=getchar();
     while(getchar()!= '\n');
     
     if(columna<'1' || columna > '7'){
                 printf("\nError ingresando columna...\n");
                 getchar();
                 }
     else{
          *j = columna-48;
          bandera=1;
          }
          }//fin del while
         
     bandera=0;
     
     while (bandera ==0){  //pidiendo si es mina o no
     printf("\nDesea marcar como mina(0) o presionarla(1), ingrese 1 o 0 : ");
     marcarbandera = getchar();
     while(getchar()!= '\n');
     if(marcarbandera != '0' && marcarbandera != '1'){
                 printf("\nError ingresando dato...\n");
                 getchar();
                 }
     else{
          if(marcarbandera == '0'){*poner_bandera = 1;}
          bandera=1;
          }
          }//fin del while
     }
     
     
void procesar(char T0[7][7], char T1[7][7],char *i,char *j, int *muerte, int *victoria, int poner_bandera){
     
     if(poner_bandera == 1){ T0[*i-1][*j-1] = 63; 
          }
          
          else{
               int validar_victoria=0;
     if(T0[*i-1][*j-1] != T1[*i-1][*j-1]){
     if(T0[*i-1][*j-1] != 63)validar_victoria=1;
     T0[*i-1][*j-1] = T1[*i-1][*j-1];
     if (validar_victoria == 1)*victoria = *victoria+1; 
     if( T0[*i-1][*j-1] == -2){                                //mina
                         *muerte=1;
                         }
     }//fin del if
     else{
          printf("\nYa ingreso esa posicion");
          }
          }//fin del primer else
     }//fin del void procesar
