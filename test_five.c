/* Test test_five.c by Giorgi Matteo, 517183 & Quarta Andrea, 517881 */

#include <stdio.h>
#include <stdlib.h>
#include "sparse.h"
#define N 3
#define M 3

#define FILE1 "my_output1.txt"
#define FILE2 "my_output2.txt"
#define FILE_BIN "binario.bin"

int main(void){

	FILE *f, *g, *b;
	if( (f=fopen(FILE1, "w"))==NULL ){
		fprintf(stderr,"fopen:");
		perror(FILE1);
		return (EXIT_FAILURE);
	}
	if( (g=fopen(FILE2, "w"))==NULL ){
		fprintf(stderr,"fopen:");
		perror(FILE2);
		return (EXIT_FAILURE);
	}
	if( (b=fopen(FILE_BIN, "wb"))==NULL ){
		fprintf(stderr,"fopen:");
		perror(FILE_BIN);
		return (EXIT_FAILURE);
	}

	/* New empty matrices my_matrix1, my_matrix2 my_matrix3 */
	smatrix_t* my_matrix1 = new_smat(N, M); perror("new my_matrix1 -->");
	smatrix_t* my_matrix2 = new_smat(M, N); perror("new my_matrix2 -->");
	smatrix_t* my_matrix3 = new_smat(-1, N); perror("new my_matrix3 -->");
	printf("\n");

	/* Inserting elements in my_matrix1 */
	put_elem(my_matrix1, 0, 1, 1); perror("my_matrix1 put1 -->");
	put_elem(my_matrix1, 0, 2, 1); perror("my_matrix1 put2 -->");
	put_elem(my_matrix1, -1, 0, 1); perror("my_matrix1 put3 -->");
	put_elem(my_matrix1, 2, 0, 1); perror("my_matrix1 put4 -->");
	printf("\n");

	/* Inserting elements in my_matrix2 */
	put_elem(my_matrix2, 0, 0, 1); perror("my_matrix2 put1 -->");
	put_elem(my_matrix2, 1, 0, 1); perror("my_matrix2 put2 -->");
	put_elem(my_matrix2, 1, 1, 1); perror("my_matrix2 put3 -->");
	put_elem(my_matrix2, 2, 2, 1); perror("my_matrix2 put4 -->");
	printf("\n");

	/* New matrices somma, prodotto, trasposta*/
	smatrix_t* somma = sum_smat(my_matrix1, my_matrix2); perror("somma -->");
	smatrix_t* prodotto = prod_smat(my_matrix1, my_matrix2); perror("prodotto -->");
	smatrix_t* trasposta = transp_smat(somma); perror("trasposta -->");
	printf("\n");

	/* Print matrices on file f and on stdout */
	print_smat(f, my_matrix1); print_smat(stdout, my_matrix1);
	print_smat(f, my_matrix2); print_smat(stdout, my_matrix2);
	print_smat(f, somma); print_smat(stdout, somma);
	print_smat(f, prodotto); print_smat(stdout, prodotto);
	print_smat(f, trasposta); print_smat(stdout, trasposta);

	/* Save my_matrix1 on file g and checking the result */
	if( save_smat(g, my_matrix1) == -1 ){
		perror("save -->");
		return (EXIT_FAILURE);
	} perror("save -->");
	fclose(g);

	/* Load new matrix from file g */
	g = fopen("my_output2.txt", "r");
	smatrix_t* mat = load_smat(g); perror("load -->");

	/* Print loaded matrix in file f */
	print_smat(f, mat);
	printf("\n");

	/* Save my_matrix1 in binary file b and checking the result */
	if( savebin_smat(b, my_matrix1) == -1 ){
		perror("savebin -->");
		return (EXIT_FAILURE);
	} perror("savebin -->");
	fclose(b);

	/* Load new matrix from binary file b */
	b = fopen("binario.bin", "rb");
	smatrix_t* matbin = loadbin_smat(b); perror("loadbin -->");

	/* Print loaded matrix in file f */
	print_smat(f, matbin);

	/* Close files */
	fclose(f);
	fclose(g);
	fclose(b);

	/* Free memory */
	free_smat(&my_matrix1);
	free_smat(&my_matrix2);
	free_smat(&somma);
	free_smat(&prodotto);
	free_smat(&trasposta);
	free_smat(&mat);
	free_smat(&matbin);

	return EXIT_SUCCESS;
}