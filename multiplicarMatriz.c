
/*!
  \file   multiplicarMatriz.c
  \brief  Programa secuencial de multiplicación de dos matrices cuadradas 
  \author Francisco Jesus Arcos Romero
  \date   15/04/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Funciones de memoria
int ** reservaMemoria(int ** m, int numCol, int numFil);
int ** rellenaMatriz(int ** m, int numCol, int numFil);
int ** rellenaMatrizCero(int ** m, int numCol, int numFil);
int ** liberarMatriz (int ** m, int numFil, int numCol);


int main () {

	clock_t start;
	srand (time(NULL));
	int i,j,k=0;
	int numCol;
	int numFil;
	int ** A;			//Matriz A
	int ** B;			//Matriz B
	int ** C;			//Matriz C Resultado
	numCol=768;
	numFil=768;

	//Reserva de Memoria y relleno de matriz
	A=reservaMemoria(A,numCol, numFil);
	A=rellenaMatriz(A,numCol, numFil);
	B=reservaMemoria(B,numCol, numFil);
	B=rellenaMatriz(B,numCol, numFil);
	C=reservaMemoria(C,numCol, numFil);
	C=rellenaMatrizCero(C,numCol, numFil);
    	
    	start = clock();
/*
	for(i=0;i<numFil;i++){
		for(j=0;j<numFil;j++){
			for(k=0;k<numFil;k++){
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
*/

	//Mejorar el código cambiando el bucle mas interno por el del medio, accediendo de forma consecutiva

	for(i=0;i<numFil;i++){
		for(k=0;k<numFil;k++){
			for(j=0;j<numFil;j++){
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}


 
/*

	//Emperora el caso a mucho
	for(j=0;j<numFil;j++){
		for(k=0;k<numFil;k++){
			for(i=0;i<numFil;i++){
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
*/
      
    	printf("Se ha ejecutado en %.12f segundos\n",(double)(clock() - start) / CLOCKS_PER_SEC);  

	    //Matriz resultado
	    /*
		for(i=0;i<numFil;i++){
			for (j=0;j<numFil;j++){
				printf ("%d ",C[i][j]);
			}
			printf ("\n");
		}
		*/

	//liberar memoria
	liberarMatriz(A, numFil, numCol);
	liberarMatriz(B, numFil, numCol);
	liberarMatriz(C, numFil, numCol);
	return 0;
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
		for (j=0;j<numFil;j++){
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

//
//
