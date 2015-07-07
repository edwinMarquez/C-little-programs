/*************************************************************************************************************

Edwin Samuel Márquez Hernández
images by Sergio Armando Márquez
NOTA:
Compilar incluir las librerias -lSDL -lSDL_image

EL programa se debe ejecutar desde consola, toma el dato de el numero de discos, es aceptado un rango de 
de 1 a 7 discos, al tener el dato abre una ventana donde despues de dos segundos se simula de forma gráfica
cada una de las instrucciones para armar la torre de Hanoi que se va describiendo desde mensajes en la consola
al finalizar espera un tiempo y se cierra.
El algoritmo utilizado para esta aplicacion a sido el que decia estar tomado de un libro de pascal.
El programa hace uso de las imagenes en la carpeta "imagenes".


***************************************************************************************************************/
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


#define AGUJA1X  197//in this i define the position of the three needles 
#define AGUJA2X  399
#define AGUJA3X  601

//Estructura para el control sobre los discos........... 
struct discos{
 SDL_Surface *imagen;
 SDL_Rect posicion;
 char aguja;
};


//Declaracion de variables globales....................

 int cantDiscos=0;       //numero de discos que se usaran
 int DiscoEnAguja[3]={0,0,0};
 SDL_Surface *screen;  //pantalla de fondo
 SDL_Surface *fondo;   //to load the background image
 SDL_Rect paraFondo = {0,0,800,500};  //posicion del fondo
 struct discos disco[7];   
 

//prototipo de funciones................................

void startSDL(void);
void cleanImgs(void);
void MoverTorre(int h, int orig, int dest, int aux);
void MoverDisco(int orig, int dest);
void AnimacionDisco(int orig, int dest);


//...........MAIN.........................................
int main(void){

 int i=0; //variable usualmente utilizada para los bucles
 fondo = IMG_Load("./imagenes/fondo2.jpg");
 
 //consulto la cantidad de discos antes de cargar las imagenes a usar.. :F
 do{
   printf("\nNumero de discos: ");
   scanf("%d", &cantDiscos);
   if(cantDiscos > 7 || cantDiscos< 1)printf("Ingreso un valor no correcto de discos(1-7)..\n ");
   else break;
 }while(1);

//cargo todas la imagenes de discos
 disco[0].imagen = IMG_Load("./imagenes/1.jpg");
 disco[1].imagen = IMG_Load("./imagenes/2.jpg");
 disco[2].imagen = IMG_Load("./imagenes/3.jpg");
 disco[3].imagen = IMG_Load("./imagenes/4.jpg");
 disco[4].imagen = IMG_Load("./imagenes/5.jpg");
 disco[5].imagen = IMG_Load("./imagenes/6.jpg");
 disco[6].imagen = IMG_Load("./imagenes/7.jpg");

//coloco los discos en la primera aguja;


 DiscoEnAguja[0]--;
 for(i=cantDiscos;i>=0;i--){
   disco[i].posicion.x = AGUJA1X-((60+i*20)/2);
   disco[i].posicion.y = 477-(DiscoEnAguja[0]*23);
   disco[i].posicion.h = disco[i].imagen->h;
   disco[i].posicion.w = disco[i].imagen->w;
   disco[i].aguja = 1;
   DiscoEnAguja[0]++;
 }


 startSDL();

//dibujo lo primero a mostrarse
 SDL_BlitSurface(fondo,NULL,screen,&paraFondo);
 for(i=0;i<cantDiscos; i++){
   SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
 }
 SDL_Flip(screen);
 SDL_Delay(2000);

//empieza la solucion al problema..
    printf("La solucion es:\n");
    MoverTorre(cantDiscos, 1, 3, 2);


 SDL_Flip(screen);
 SDL_Delay(3000);

 cleanImgs();
 IMG_Quit();
 SDL_Quit();
return 0;
}


//Funciones.......................................................

void startSDL(void){
if(SDL_Init(SDL_INIT_VIDEO) == -1 ){
   printf("Error: %s",SDL_GetError());
   SDL_Quit();
   exit(1);
 }
 screen = SDL_SetVideoMode(800, 500, 32, SDL_HWSURFACE);
 SDL_WM_SetCaption("Test screen", NULL);
}

void cleanImgs(void){
SDL_FreeSurface(disco[0].imagen);
SDL_FreeSurface(disco[1].imagen);
SDL_FreeSurface(disco[2].imagen);
SDL_FreeSurface(disco[3].imagen);
SDL_FreeSurface(disco[4].imagen);
SDL_FreeSurface(disco[5].imagen);
SDL_FreeSurface(disco[6].imagen);
}


void MoverTorre(int h, int orig, int dest, int aux)
{
    if(h > 0){
        MoverTorre(h - 1, orig, aux, dest);
        MoverDisco(orig, dest);
	AnimacionDisco(orig, dest);
        MoverTorre(h - 1, aux, dest, orig);
    }
}


void MoverDisco(int orig, int dest)
{
    printf("Pase el disco que esta en el tope de la aguja %d", orig);
    printf(" hacia la aguja %d\n", dest);
}

void AnimacionDisco(int orig, int dest){
  
  int i=0,j=0;
  int agujaDestino=0;
  int agujaOrigen=0;
  int centroDiscos =0;

  agujaDestino = (dest==1)?AGUJA1X:(dest==2)?AGUJA2X:AGUJA3X; //guardo el valor del centro de la aguja
  agujaOrigen =  (orig==1)?AGUJA1X:(orig==2)?AGUJA2X:AGUJA3X;
  

  for(i=0; i<cantDiscos; i++){
    if(disco[i].aguja==orig)break;
  }
   
  centroDiscos = (agujaOrigen-((60+i*20)/2))+(((agujaDestino-((60+i*20)/2))-(agujaOrigen-((60+i*20)/2)))/2);
//muevo el disco hacia arriba hasta el pixel 211

   while(1){
     SDL_BlitSurface(fondo,&disco[i].posicion,screen,&disco[i].posicion);
     disco[i].posicion.y -= 5; 
     if(disco[i].posicion.y <= 216 && disco[i].posicion.y >= 206){
       disco[i].posicion.y = 211;
       SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
       SDL_Flip(screen);
       SDL_Delay(1);
       break;
     }
     SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
     SDL_Flip(screen);
     SDL_Delay(1);
   }//fin del while
   

//muevo el disco a la derecha o a la izquierda segun sea el caso 

if(orig < dest){
while(1){
     SDL_BlitSurface(fondo,&disco[i].posicion,screen,&disco[i].posicion);
     disco[i].posicion.x += 5;

     if( disco[i].posicion.x < centroDiscos ) disco[i].posicion.y -= 1; // agujaDestino-((60+i*20)/2);
     else disco[i].posicion.y += 1;

     if(disco[i].posicion.x <= (agujaDestino-((60+i*20)/2)+5) && disco[i].posicion.x >= (agujaDestino-((60+i*20)/2)-5)){
       disco[i].posicion.x = agujaDestino-((60+i*20)/2);
       SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
       SDL_Flip(screen);
       SDL_Delay(1);
       break;
     }
     SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
     SDL_Flip(screen);
     SDL_Delay(1);
   }//fin del while
} 
else{
   while(1){
     SDL_BlitSurface(fondo,&disco[i].posicion,screen,&disco[i].posicion);
     disco[i].posicion.x -= 5;

     if(disco[i].posicion.x > centroDiscos) disco[i].posicion.y -= 1; 
     else disco[i].posicion.y += 1;

     if(disco[i].posicion.x <= (agujaDestino-((60+i*20)/2)+5) && disco[i].posicion.x >= (agujaDestino-((60+i*20)/2)-5)){
       disco[i].posicion.x = agujaDestino-((60+i*20)/2);
       SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
       SDL_Flip(screen);
       SDL_Delay(1);
       break;
     }
     SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
     SDL_Flip(screen);
     SDL_Delay(1);
   }//fin del while
} 


//muevo el disco hacia abajo..

   while(1){
     SDL_BlitSurface(fondo,&disco[i].posicion,screen,&disco[i].posicion);
     disco[i].posicion.y += 3; 
     if(disco[i].posicion.y <= (477-(DiscoEnAguja[(dest-1)]*23)+5) && disco[i].posicion.y >= (477-(DiscoEnAguja[(dest-1)]*23)-5)){
       disco[i].posicion.y = 477-(DiscoEnAguja[(dest-1)]*23);
       SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
       SDL_Flip(screen);
       SDL_Delay(2);
       break;
     }
     SDL_BlitSurface(disco[i].imagen,NULL,screen,&disco[i].posicion);
     SDL_Flip(screen);
     SDL_Delay(2);
   }//fin del while

   DiscoEnAguja[(orig-1)]--;
   disco[i].aguja = dest;
   DiscoEnAguja[(dest-1)]++;

}





