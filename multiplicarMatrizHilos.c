
/*!
  \file   multiplicarMatrizHilos.c
  \brief  Programa paralelo de multiplicación de dos matrices cuadradas  usando Pthread
  \author Francisco Jesus Arcos Romero
  \date   15/04/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <omp.h>		//Libreria para usar el contador de tiempo de omp

#define numHilos 128

//Funciones de memoria
int ** reservaMemoria(int ** m, int numCol, int numFil);
int ** rellenaMatriz(int ** m, int numCol, int numFil);
int ** rellenaMatrizCero(int ** m, int numCol, int numFil);
int ** liberarMatriz (int ** m, int numFil, int numCol);

void * multiplicar (void * num);

int ** A;			//Matriz A
int ** B;			//Matriz B
int ** C;			//Matriz C Resultado
int numCol;
int numFil;         		


int main () {


	double inicio,fin;				//variable para contar tiempoi ejecucionS
	srand (time(NULL));		
	numCol=768;					//Numero de columnas de la matriz 768
	numFil=768;					//Numero de filas de la matriz 768
	pthread_t hilos[numHilos];
	int v[numHilos];
	int h,i,j,k,m=0;

	//Reserva de Memoria y relleno de matriz
	A=reservaMemoria(A, numCol, numFil);
	A=rellenaMatriz(A, numCol, numFil);
	B=reservaMemoria(B, numCol, numFil);
	B=rellenaMatriz(B, numCol, numFil);
	C=reservaMemoria(C, numCol, numFil);
	C=rellenaMatrizCero(C, numCol, numFil);

	//Comienza a contar el reloj

	inicio=omp_get_wtime();			
    	
    	//Bucle for para crear los hilos
	for(h=0 ; h<numHilos; h++){
		v[h]=h;
		if( pthread_create(&hilos[h], NULL, multiplicar, (void *) &v[h]) != 0){
			perror("Error en el create.\n");
			printf("Errno value = %d\n", errno);
			exit(EXIT_FAILURE);
		}
	}

	//Bucle for para recibir los hilos.
	for(h=0 ; h<numHilos; h++){
		if(pthread_join (hilos[h], NULL) != 0){
			perror("Error en el join.\n");
			printf("Errno value = %d\n", errno);
			exit(EXIT_FAILURE);			
		}
	}

	//Termina la cuenta
   	fin=omp_get_wtime();	

	printf("Tiempo : %11.9f segundos\n",fin-inicio);

    //Imprimir Matriz resultado
    /*
    	printf("Matriz Resultado\n");
	for(i=0;i<numFil;i++){
		for (j=0;j<numCol;j++){
			printf ("%d ",C[i][j]);
		}
		printf ("\n");
	}
    */

	//liberar memoria
	liberarMatriz(A, numFil, numCol);
	liberarMatriz(B, numFil, numCol);
	liberarMatriz(C, numFil, numCol);

	exit(EXIT_SUCCESS);
}

//Funcion que multiplica dos matrices 

void * multiplicar (void * num){

int inicio, fin, intervalo;
int i,j,k,m=0;

int * numhilo=(int*)num;

intervalo=numFil/numHilos;
inicio=*numhilo*intervalo;
fin=(inicio+intervalo);

	for(i=inicio;i<fin;i++){
		for (k=0;k<numCol;k++){	
			for (j=0;j<numCol;j++){
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
				//printf ("hilo %d k=%d C[%d][%d]=%d\n",*numhilo, k,i,j, C[i][j]);
			}
		}
	}
	
pthread_exit(NULL);

}


//Reserva de memoria de una matriz

int ** reservaMemoria(int ** m, int numCol, int numFil){

	int i;

	// Reserva de Memoria 
	m = (int **)malloc(numFil*sizeof(int*)); 
	
	for (i=0; i<numFil;i++) 
		m[i] = (int*)malloc(numCol*sizeof(int)); 

	return m;

}

//Relleno de una matriz

int ** rellenaMatriz(int ** m, int numCol, int numFil){

	int i,j;

	for (i=0;i<numFil;i++){
		for (j=0;j<numCol;j++){
			m[i][j]=(rand () % 9) + 1;
		}
	}

	return m;

}

//Relleno de una matriz a cero

int ** rellenaMatrizCero(int ** m, int numCol, int numFil){

	int i,j;

	for (i=0;i<numFil;i++){
		for (j=0;j<numFil;j++){
			m[i][j]=0;
		}
	}

	return m;

}

//Liberar Matriz

int ** liberarMatriz (int ** m, int numFil, int numCol)
{
	int  i;
	if (m == NULL){
  		return (NULL);
  	}

	if (numFil < 1 || numCol < 1) {  /* verifica parametros recibidos */
		printf ("** Error: Parametro invalido **\n");
		return (m);
	}

	for (i=0; i<numFil; i++){
		free (m[i]); /* libera as linhas da matriz */
	} 	

	free (m);      /* libera a matriz */

	return (NULL); /* retorna um ponteiro nulo */
}
