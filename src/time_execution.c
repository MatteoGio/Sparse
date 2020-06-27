/* Test time_execution.c by Giorgi Matteo, 517183 & Quarta Andrea, 517881 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sparse.h"
/* colums */
#define N 100000
/* rows */
#define M 100000
/* number of non zero element per row */
#define K 1000

void random_insert(smatrix_t *matrice, int n, int m);
void m_print(smatrix_t *m);

int main(int argc, char const *argv[]){
	time_t t1, t2;
	printf("\nPROVA DEL TEMPO DI ESECUZIONE PER SOMMA, PRODOTTO E TRASPOSTA CON MATRICE %d x %d\n\n" , N, M);
	
	/* New empty matrices my_matrix1, my_matrix2 */
	printf("Alloco matrici my_matrix1 & my_matrix2\n");
	smatrix_t* my_matrix1 = new_smat(N, M);
	smatrix_t* my_matrix2 = new_smat(M, N);
	printf("... allocate...\n\n");

	srand(time(NULL));
	printf("Riempimento casuale di my_matrix1\n");
	t1 = clock();
	random_insert(my_matrix1, N, M);
	t2 = clock();
	printf("... riempita ... ha impiegato: %lf\n\n", (double)(t2-t1)/CLOCKS_PER_SEC);

	printf("Riempimento casuale di my_matrix2\n");
	t1 = clock();
	random_insert(my_matrix2, M, N);
	t2 = clock();
	printf("... riempita ... ha impiegato: %lf\n\n", (double)(t2-t1)/CLOCKS_PER_SEC);


	/* Unlock to print on screen the matrix element disposition */
	#if 0
	m_print(my_matrix1); 
	m_print(my_matrix2);
	#endif


	/* New matrices somma, prodotto, trasposta*/
	printf("... sto facendo la somma ...\n");
	t1 = clock();
	smatrix_t* somma = sum_smat(my_matrix1, my_matrix2); perror("somma-->");
	t2 = clock();
	printf("La somma ha impiegato: %f\n\n", (double)(t2-t1)/CLOCKS_PER_SEC);

	printf("... sto facendo il prodotto ...\n");
	t1 = clock();
	smatrix_t* prodotto = prod_smat(my_matrix1, my_matrix2); perror("prodotto-->");
	t2 = clock();
	printf("Il prodotto ha impiegato: %f\n\n", (double)(t2-t1)/CLOCKS_PER_SEC);

	printf("... sto facendo la trasposta di my_matrix1 ...\n");
	t1 = clock();
	smatrix_t* trasposta = transp_smat(my_matrix1); perror("trasposta-->");
	t2 = clock();
	printf("La trasposta ha impiegato: %f\n\n", (double)(t2-t1)/CLOCKS_PER_SEC);	

	/* Free Memory */
	printf("Libero tutta la memoria\n");
	free_smat(&my_matrix1);
	free_smat(&my_matrix2);
	free_smat(&somma);
	free_smat(&prodotto);
	free_smat(&trasposta);
	return 0;
}

/*
Function used to insert randomly new values into the matrix
*/
void random_insert(smatrix_t *matrice, int n, int m){
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<rand()%K; j++) put_elem(matrice, i, rand()%m, rand()+1);
}

/*
Funcion used to print the matrix and check the element disposition
*/
void m_print(smatrix_t *m){
	int i, j;
	for(i=0; i<m->nrow; i++){
		elem_t* aux;
		for(j=0, aux=(m->mat)[i]; j<m->ncol; j++)
			if(aux!=NULL && aux->col == j){
				printf("_ ");
				aux = aux->next;
			}
			else printf("0 ");
		printf("\n");
	}
	printf("\n");
}