/*
  \file
  \authors sol-lab 2015/16
  \brief primo file di test progetto di recupero
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sparse.h"

/** numero rige e colonne */
#define N 10
#define M 5

int main (void) {
  smatrix_t * a;
  double d;


  /* creazione, stampa, inserimento elementi e lettura deallocazione */
  /* creo matrice vuota */
  a = new_smat(N,M);

  /* stampo matrice vuota */
  printf("Test1:\n");
  print_smat(stdout,a) ;



  /* inserisco alcuni elementi */
  if ( put_elem(a,-1,1,4.0) == 0 ) return EXIT_FAILURE ;
  put_elem(a,1,1,4.0) ;
  put_elem(a,2,2,4.0) ;
  put_elem(a,2,1,4.0) ;
  put_elem(a,2,4,4.0) ;
  put_elem(a,2,3,4.0) ;
  put_elem(a,2,1,5.5) ;
  put_elem(a,3,4,4.0) ;
  if ( put_elem(a,5,8,4.0) == 0 )   return EXIT_FAILURE;
  put_elem(a,8,5,8.0) ;
  put_elem(a,7,5,8.0) ;
  put_elem(a,1,4,8.0) ;
  if ( put_elem(a,5,1,3.0) != 0 )  return EXIT_FAILURE; 
  /* stampo il risultato */
  printf("Test2:\n");
  print_smat(stdout,a) ;


  /* test su get */
  if (( get_elem(a,5,1,&d) !=0 ) || (d != 3)  )  return  EXIT_FAILURE ;
  if (( get_elem(a,5,-1,&d) ==0 )  ) return  EXIT_FAILURE ;
	if (( get_elem(a,2,1,&d) !=0 ) || (d != 5.5)  )  return  EXIT_FAILURE ;
  if (( get_elem(a,5,-1,NULL) ==0 )  ) return  EXIT_FAILURE ;

  /* test su scritture (anche di 0) */
  put_elem(a,0,1,7.0) ;
  put_elem(a,2,1,0) ;
  put_elem(a,2,1,0) ;
  put_elem(a,2,3,0) ;
  put_elem(a,2,4,0) ;
	
  /* stampo il risultato */
  printf("Test3:\n");
  print_smat(stdout,a) ;
	

  /* cancello la matrice */
  free_smat(&a);
  /* controllo sia stato eliminato il puntatore */
  if (a != NULL ) return EXIT_FAILURE;

  return EXIT_SUCCESS;

}

