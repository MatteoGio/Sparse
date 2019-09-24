/*
  \file
  \authors sol-lab 2015/16 
  \brief terzo test frammento 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sparse.h"



/** numero rige e colonne */
#define N 5
#define M 8

int main (void) {
  smatrix_t * a, *b, *c;
  int i,j;

  

  /* creazione matrici test operazioni */
  a = new_smat(N,M);  
  b = new_smat(N,M);


  for (i=0; i < N ; i ++) 
    for (j=0; j < M ; j ++) 
      if (i != j)  {
	put_elem(a,i,j,(1.0)) ;
	put_elem(b, i, j ,(2.0)) ;
    
      }

  /* calcolo la trasposta */
  c = transp_smat(b);
  free_smat(&b);
  
  /* stampo le matrici da moltiplicare */
  print_smat(stdout,a);
  print_smat(stdout,c);


  if ( ( b = prod_smat(a,c) ) == NULL ) return EXIT_FAILURE;

  print_smat(stdout,b);
	
	
  
  free_smat(&a);
  free_smat(&b);
  free_smat(&c);

  return EXIT_SUCCESS;

}
