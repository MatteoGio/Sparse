/*
  \file
  \authors sol-lab 2015/16
  \brief secondo file di test frammento 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sparse.h"



/** numero rige e colonne */
#define N 15
#define M 10

int main (void) {
  smatrix_t * a, *b, *c;
  int i,j;

  
  
  /* creazione matrici vuote test operazioni */
  a = new_smat(N,M);  
  b = new_smat(N,M);



  /* inserisco elementi */
  for (i=0; i < N ; i ++) 
    for (j=0; j < M ; j ++) { 
      put_elem(a,i,j,1.0) ;
      put_elem(b, i, j ,1.0) ;
    
  }

  /* stampo le matrici create */
  print_smat(stdout,a);
  print_smat(stdout,b);

  /* calcolo la matrice somma */
  c = sum_smat(a,b);

  /* ... la stampo */
  print_smat(stdout,c);

  /* dealloco le matrici b e c */
  free_smat(&b);
  free_smat(&c);

  
  /* modifico la matrice a */
  for (i=0; i< N ; i++)
    for (j=0; j < M ; j ++) 
      put_elem(a,i,j,((3*i)+(2*j)));
  
  /* la stampo */
  
  print_smat(stdout,a);
	
  /* creo una nuova matrice b sparsa */
	
	
  b = new_smat(N,M);
  put_elem(b,2,1,-8.0) ;
  put_elem(b,2,4,-14.0) ;
  put_elem(b,0,1,-2.0) ;
  put_elem(b,0,4,-8.0) ;
  put_elem(b,3,5,-23.0) ;
  for(j=0; j < M; j++)
    put_elem(b,4,j, -(12+(2*j)));  
  
  
  /* la stampo */
  
  print_smat(stdout,b);
  
  /* calcolo la somma */
  c = sum_smat(a,b);
  
  /* la stampo */
  print_smat(stdout,c);
  
  /* dealloco tutte le matrici */
  free_smat(&a);
  free_smat(&b);
  free_smat(&c);
  
  return EXIT_SUCCESS;

}
