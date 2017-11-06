//Cruz Vera Edgar
//Rodriguez Aparicio Yair
//Santamaria Guerrero Diego
//Sistemas operativos
//Proyecto final: algoritmo de planificacion de procesos SRTF

#include <conio.h>
#include <iostream.h>
#include <stdlib.h>
#define numProcesos 10
#define N 5
#define LinpPag 100

//Estructura de tabla de mapa de memoria
struct MMT{
	int numMarco;
   int locIni;
   int estadoTMM;
   MMT *sig;
}*iM=NULL, *fM=NULL, *nuevoM=NULL, *auxM=NULL;

//Estrucutura de PCB
struct PCB
{
	int idProceso;
   int nPag;
   int tLlegada;
   int ciclos;
   int memoria;
   char cpuES[10];
   int archivos;
   int nDisp;
   char tipo[10];
   int estado;
   int trp;
   PCB *sig;
} *piPCB=NULL, *pfPCB=NULL, *paPCB=NULL,*pnPCB=NULL,*pcomPCB=NULL;

//Estructura de tabla de tareas
struct JT{
	int tarea;
   int seleccion;
   JT *sig;
}*iJ=NULL, *fJ=NULL, *nuevoJ=NULL, *auxJ=NULL;

//Estructura de tabla de mapa de memoria
struct PMT{
	int numPagina;
   int estado;
   PMT *sig;
}*iP[N], *fP[N], *nuevoP[N], *auxP[N];

struct vector{
	int dec;
   char uso[50];
   vector *sig;
}*ini, *aux, *fin;

//Declaracion de funciones
void crearMMT(int valor1);
void mostrarMMT();
void cambiarEstadoA2();

void cambiarEstadoA2()
{
  	paPCB=piPCB;
   while(paPCB!=NULL){
   	paPCB->estado=2;
      paPCB=paPCB->sig;
   }
}

//funcion crear vector de interrupciones
void crearVEC(){
   int vec=5;
   int i=0;
	do{
   	if(ini==NULL){
      	ini=(vector*)malloc(sizeof(vector));
         ini->dec=0;
         strcpy(ini->uso,"Error: Division por cero");
         ini->sig=NULL;
         fin=ini;
         i++;
      }
      else{
      	aux=(vector*)malloc(sizeof(vector));
         aux->dec=1+rand()%(5);
         if(aux->dec==3)
         	strcpy(aux->uso,"Interrupcion INT");
         if(aux->dec==2)
            strcpy(aux->uso,"Interrupcion No enmascarable");
         if(aux->dec==4)
            strcpy(aux->uso,"Overflow");
         if(aux->dec==1)
            strcpy(aux->uso,"Excepciones para depuracion");
         aux->sig=NULL;
         fin->sig=aux;
         fin=aux;
         i++;
      }
   }while(i<vec);
}//fin funcion crear vector de interrupciones

//funcion crear tabla de tareas
void crearJT(){
	int i=1;
   do{
   	if(iJ==NULL){
      	iJ = (JT *)malloc(sizeof(JT));
         iJ->tarea = i;
         iJ->sig = NULL;
         fJ = iJ;
      }
      else{
      	nuevoJ = (JT *)malloc(sizeof(JT));
         nuevoJ->tarea = i;
         fJ->sig = nuevoJ;
         fJ = nuevoJ;
         fJ->sig = NULL;
      }
      i++;
   }while(i<=N);
}//fin funcion crear tabla de tareas

//Funcion crear PCB
void crearPCB(){
		int i =1;
      int x=0;
      int cont=1;
      int cont2=0;
      int marcos=0;
      auxJ=iJ;
	   do{
   		auxP[i] = iP[i];
      	while(auxP[i]!=NULL){
      		if(auxP[i]->estado==1){
            	if(piPCB==NULL){
              		paPCB = (PCB *)malloc(sizeof(PCB));
               	paPCB->idProceso=cont++;
               	paPCB->tLlegada = cont2++;
               	paPCB->ciclos = 1+rand()%(10);
               	paPCB->estado = 1;
               	paPCB->memoria =rand()%(101-1);
                  x=rand()%(501-1);
                  if((x%2)==0){
                  	strcpy(paPCB->cpuES,"CPU");
                     paPCB->nDisp =0;
                  }
                  else{
                  	strcpy(paPCB->cpuES,"ES");
                     paPCB->nDisp =rand()%(7-1);
                  }
                  paPCB->archivos =rand()%(11-1);
                  if((x%2)==0)
                  	strcpy(paPCB->tipo,"SISTEMA");
                  else
                  	strcpy(paPCB->tipo,"USUARIO");
                     marcos++;

                  paPCB->sig = NULL;
                  piPCB = paPCB;
                  pfPCB=piPCB;
               }
            	else{
            		paPCB = (PCB *)malloc(sizeof(PCB));
               	paPCB->idProceso=cont++;
               	paPCB->tLlegada = cont2++;
               	paPCB->ciclos = 1+rand()%(10);
               	paPCB->estado = 1;
               	paPCB->memoria =rand()%(101-1);
                  x=rand()%(501-1);
                  if((x%2)==0){
                  	strcpy(paPCB->cpuES,"CPU");
                     paPCB->nDisp =0;
                  }
                  else{
                  	strcpy(paPCB->cpuES,"ES");
                     paPCB->nDisp =rand()%(7-1);
                  }
                  paPCB->archivos = rand()%(11-1) ;
                  if((x%2)==0)
                  	strcpy(paPCB->tipo,"SISTEMA");
                  else
                  	strcpy(paPCB->tipo,"USUARIO");

                     paPCB->sig = NULL;
                     pfPCB->sig=paPCB;
                     pfPCB=paPCB;
                     marcos++;
            	}
         	}
            auxP[i] = auxP[i]->sig;
      	}
         i++;
   }while(i<=5);

crearMMT(marcos);

}//fin funcion crear PCB

//funcion mostrar MMT
void mostrarMMT(){
   nuevoM = iM;
   cout<<"\nNum.Marco\tLoc Ini\t\tEstado\n";
   while(nuevoM!=NULL){
   	cout<<nuevoM->numMarco<<"\t\t"<<nuevoM->locIni<<"\t\t"<<nuevoM->estadoTMM<<endl;
      nuevoM = nuevoM->sig;
   }
}//fin funcion mostrar MMT

//funcion crear MMT
void crearMMT(int valor1){
	int Marcos=valor1;
	int i=0;
   do{
   	if(iM==NULL){
      	iM = (MMT *)malloc(sizeof(MMT));
         iM->numMarco = i;
         iM->locIni = (i+100);
         iM->estadoTMM = 0;
         iM->sig=NULL;
         fM = iM;
      }
      else{
      	nuevoM = (MMT *)malloc(sizeof(MMT));
         nuevoM->numMarco = i;
         nuevoM->locIni = (i+100);
         nuevoM->estadoTMM = 0;
         fM->sig = nuevoM;
         fM = nuevoM;
      }
      i++;
   }while(i<Marcos);
   mostrarMMT();
}//fin crear MMT

//Funcion crear PMT
void crearPMT(){
	int cont;
	int i=1;
   int j,x;
   auxJ = iJ;
   do{
   	cont=0;
   	for(j=0;j<5;j++){
      	if(iP[i]==NULL){
         	iP[i]=(PMT *)malloc(sizeof(PMT));
            iP[i]->numPagina = j;
            iP[i]->estado = rand()%2;
            if(iP[i]->estado==1)
            	cont++;
            iP[i]->sig = NULL;
            fP[i] = iP[i];
         }
         else{
         	nuevoP[i] = (PMT *)malloc(sizeof(PMT));
            nuevoP[i]->numPagina = j;
            nuevoP[i]->estado = rand()%2;
            if(nuevoP[i]->estado==1)
            	cont++;
            nuevoP[i]->sig = NULL;
            fP[i]->sig = nuevoP[i];
            fP[i] = nuevoP[i];
         }
      }
      i++;
      auxJ->seleccion=cont;
      auxJ = auxJ->sig;
   }while(i<=N);
}//fin funcion crear PMT

//funcion Mostrar tabla de vector de interrupciones
void mostrarVEC(){
   aux = ini;
   cout<<"\nVector interrupciones\n";
   cout<<"Dec\t"<<"Uso"<<endl;
   while(aux!=NULL){
   	cout<<aux->dec<<"\t"<<aux->uso<<endl;
      aux = aux->sig;
   }
}//fin funcion mostrar vector de interrupciones

//funcion mostrar PMT
void mostrarPMT(){
	int i=1, j;
   do{
   	auxP[i] = iP[i];
   	cout<<"\nTabla J"<<i<<endl;
      cout<<"Pagina\tEstado\n";
      while(auxP[i]!=NULL){
      	cout<<"P"<<auxP[i]->numPagina<<"\t"<<auxP[i]->estado<<endl;
         auxP[i] = auxP[i]->sig;
      }
      i++;
   }while(i<=5);
}//fin mostrar PMT

//funcion Mostrar tabla de tareas
void mostrarJT(){
   auxJ = iJ;
   cout<<"\nTarea\n";
   while(auxJ!=NULL){
   	cout<<"J"<<auxJ->tarea<<"\tSeleccion: "<<auxJ->seleccion<<endl;
      auxJ = auxJ->sig;
   }
}//fin funcion mostrar JT

//funcion Mostrar PCB
void mostrarPCB(){
	paPCB=piPCB;
   cout<<"\nProceso\tT.lleg\tCiclos\tEstado\tMemoria\tCPU/ES\tNum_Dispvt Archivos\tTipo"<<endl;
   while(paPCB!=NULL){
      cout<<paPCB->idProceso<<"\t"<<paPCB->tLlegada<<"\t"<<paPCB->ciclos<<"\t"<<paPCB->estado<<"\t"<<paPCB->memoria<<"\t"<<paPCB->cpuES<<"\t";
      cout<<paPCB->nDisp<<"\t\t"<<paPCB->archivos<<"\t"<<paPCB->tipo<<endl;
      paPCB=paPCB->sig;
   }
   system("pause>NULL");
}//fin mostrar PCB

//funcion SRTF
void SRTF(){
    pcomPCB=piPCB;                                 //este puntero compara el siguiente dato inmediato de la PCB en ciclos
    pnPCB=piPCB;                                   //este es el puntero auxiliar para recorrer la PCB en ciclos
    pcomPCB=pcomPCB->sig;                          //saltamos al dato n+1
    float tps=0;                                   //tiempo promedio del sistema
    mostrarPCB();                                  //llamdo de la funcion mostrar la PCB
    while((pnPCB!=NULL)&&(pcomPCB!=NULL)){         //Este ciclo sirve para recorrer la PCB mientras existan ciclos
            pnPCB->estado=3;                       //cambiamos el estado a 3 en el proceso n
            while(pnPCB->ciclos>0){                //Este ciclo sirve mientras haya ciclos en ese proceso
            	pnPCB->ciclos--;                    //decrementa los ciclos
               mostrarPCB();                       //muestra la PCB
               if(pnPCB->ciclos>pcomPCB->ciclos){  //si el ciclo del siguiente porceso es menor
               	pnPCB->estado=2;                 //estado a 2
                  pnPCB=pnPCB->sig;                //pasa al siguiente ciclo
                  pnPCB->estado=3;                 //El estado pasa a 3
                  pnPCB->ciclos--;                 //decrementa los ciclos
                  mostrarPCB();                    //muestra la tabla
                  pcomPCB=pcomPCB->sig;            //recorremos al siguiente proceso para verificar si es menor o mayor
               }
               if(pnPCB->ciclos>=1){               //si el proceso n aun tiene ciclos
            		pnPCB->ciclos--;                 //decrementa los ciclos del proceso n
                  mostrarPCB();                    //muestra la PCB
               }
               if(pnPCB->ciclos==0){               //si ya no hay ciclos
                  	pnPCB->estado=5;              //cambia el estado del proceso n a 5
               }
               if(pcomPCB==NULL){                  //si el porceso n+1 ya no existe en lista
               	pcomPCB=piPCB;                   //regresa al principio al puntero comparar
               }
            }													//fin while ciclos
//++++++++++++++++++++++++++++++++++++++++++++++++ En estas condiciones se manejan las interrupciones
        		if(pnPCB->idProceso==9){               //mostrar una interrupcion en el proceso 10
        			aux=ini;
               while(aux!=NULL){
               		if(aux->dec==0){
               			cout<<"\nInterrupcion"<<endl;
            				cout<<"Dec\t"<<"Uso"<<endl;
            				cout<<aux->dec<<"\t"<<aux->uso<<endl;
            				cout<<"Proceso:"<<pnPCB->idProceso+1<<endl;
               		}
            		aux=aux->sig;
           	 		}
        		}
        		if(pnPCB->idProceso==7){               //mostrar una interrupcion en el proceso 8
            	aux=ini;
               while(aux!=NULL){
               	if(aux->dec==3){
               		cout<<"\nInterrupcion"<<endl;
            			cout<<"Dec\t"<<"Uso"<<endl;
            			cout<<aux->dec<<"\t"<<aux->uso<<endl;
            			cout<<"Proceso:"<<pnPCB->idProceso+1<<endl;
               	}
            	aux=aux->sig;
            	}
         	}
         	if(pnPCB->idProceso==3){               //mostrar una interrupcion en el proceso 4
        			aux=ini;
        			while(aux!=NULL){
               	if(aux->dec==2){
               		cout<<"\nInterrupcion"<<endl;
            			cout<<"Dec\t"<<"Uso"<<endl;
            			cout<<aux->dec<<"\t"<<aux->uso<<endl;
            			cout<<"Proceso:"<<pnPCB->idProceso+1<<endl;
               	}
            	aux=aux->sig;
            	}
         	}
            if(pnPCB->idProceso==2){              //mostrar una interrupcion en el proceso 3
        			aux=ini;
               while(aux!=NULL){
               		if(aux->dec==4){
               			cout<<"\nInterrupcion"<<endl;
            				cout<<"Dec\t"<<"Uso"<<endl;
            				cout<<aux->dec<<"\t"<<aux->uso<<endl;
            				cout<<"Proceso:"<<pnPCB->idProceso+1<<endl;
               		}
            		aux=aux->sig;
           	 		}
        		}
            if(pnPCB->idProceso==5){             //mostrar una interrupcion en el proceso 6
        			aux=ini;
               while(aux!=NULL){
               		if(aux->dec==1){
               			cout<<"\nInterrupcion"<<endl;
            				cout<<"Dec\t"<<"Uso"<<endl;
            				cout<<aux->dec<<"\t"<<aux->uso<<endl;
            				cout<<"Proceso:"<<pnPCB->idProceso+1<<endl;
               		}
            		aux=aux->sig;
           	 		}
        		}
        pnPCB=pnPCB->sig;                       //pasamos al sigueinte proceso n
        pcomPCB=pcomPCB->sig;                   //pasamos al siguiente proceso n+1 para hacer la comparacion
    }
    pnPCB=piPCB;                                //el puntero de recorrer la PCB regresa al pricipio
    while(pnPCB!=NULL){                         //mientras existan datos en PCB
    	pnPCB->estado=3;                          //cambia el estado a 3
    	if(pnPCB->ciclos>0){                      //si existen ciclos en ese proceso
      	while(pnPCB->ciclos>0){                //mistras los ciclos sean mayores a cero
         	pnPCB->ciclos--;                    //decrementa los ciclos
            mostrarPCB();                       //muestra la tabla de PCB
         }
      }
      if(pnPCB->ciclos==0){                     //si ya no hay ciclos  en es proceso
      	pnPCB->estado=5;                       //cambia el estado a 5
      }
      pnPCB=pnPCB->sig;                         //pasa all siguiente proceso
    }
   /* pnPCB=piPCB;
    cout<<endl;
    cout<<"TRP :"<<endl;
    int no=0;
    tps=0;
    while(pnPCB!=NULL){
        cout<<"P"<<pnPCB->idProceso<<": "<<pnPCB->trp<<"ms"<<endl;
        tps=tps+pnPCB->trp;
        pnPCB=pnPCB->sig;
        no++;
    }
    cout<<"\n\nTiempo Promedio del Sistema: "<<tps/no<<"ms"<<endl;
    */
}//fin funcion SRTF

void main(){
	crearJT();
   crearPMT();
   mostrarPMT();
   mostrarJT();
	crearPCB();
   mostrarPCB();
   cambiarEstadoA2();
   crearVEC();                     //esta funcion crea el vector de interrupciones
   mostrarVEC();                   //muestra las interrupciones creadas
   system("pause");
   SRTF();                         //esta funcion realiza en algoritmo SRTF
   cout<<"Algoritmo SRTF terminado con exito"<<endl;
   system("pause>NULL");
}