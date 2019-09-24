#include <stdio.h>
#include <stdlib.h>
#include "sparse.h"

static void print_elem_r(FILE * f, elem_t* p)  {
  if ( p == NULL ) return ;
  fprintf(f, "<%d,%f>",p->col,p->val);
  print_elem_r(f,p->next);
  return;
}

void print_smat (FILE * f, smatrix_t * a) { 
  int i;
  
 if ( f == NULL || a == NULL )
    return ;

  
  for (i=0; i< a->nrow ; i++) {
	  if(a->mat[i]!=NULL) {
		  fprintf(f,"%d: ",i);
		  print_elem_r(f,a->mat[i]);
          fprintf(f,"\n");}
  } 
  fprintf(f,"\n");
} 
