/* Library sparse.c by Giorgi Matteo, 517183 & Quarta Andrea, 517881 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sparse.h"

/*
Macro SWAP takes two void pointers (A) and (B), the size (SIZE) of the pointed variables
and exchange byte per byte the content of the two pointers.
*/
#define SWAP(A, B, SIZE)								\
	do{													\
		size_t __size = (SIZE);							\
		char *__a=(char*)(A), *__b=(char*)(B), __tmp;	\
		while(__size--){								\
			__tmp = *__a;								\
			*__a++ = *__b;								\
			*__b++ = __tmp;								\
		}												\
	} while(0)

/*
Macro MIN_INDEX takes two elem_t pointers
and elaborate which one has the minimum column index
*/
#define MIN_INDEX(M, A) ( ((M)->col) < ((A)->col) ? (M) : (A) )

/*
Macro INS_TAIL takes the matrix (MAT), the head (HEAD) and the tail (TAIL) of the current row,
the column index (J) and the value (D) of the of the new element.
Therefore it insert on tail of the current row.
*/
#define INS_TAIL(MAT, HEAD, TAIL, J, D)														\
	do{																						\
		if( (D)!=0 ){																		\
			elem_t *__new;																	\
			if( (__new=new_elem((J), (D))) == NULL ) free_smat( &(MAT) );					\
			else *(TAIL) = *(HEAD)==NULL ? (*(HEAD) = __new) : ((*(TAIL))->next = __new);	\
		}																					\
	} while(0);

/*MY AUXILIARY FUNCTIONS (see bottom)*/
static elem_t *put(elem_t *e, unsigned j, double d);
static elem_t *new_elem(unsigned j, double d);

/********************************************************************************************************************************************************************************/

smatrix_t *new_smat(unsigned n, unsigned m){
	errno = 0;
	smatrix_t *matrice;
	elem_t **pmat;								/*pointer to the array of lists*/
	if( (matrice=malloc(sizeof(smatrix_t)))==NULL || (pmat=calloc(n, sizeof(elem_t*)))==NULL ){
		if(matrice!=NULL) free(matrice);		/*there could have been an allocation problem on calloc*/
		errno = ENOMEM;							/*not enough memory available or wrong call to malloc or calloc*/
		return NULL;
	}
	matrice->mat = pmat;						/*setting the fields*/
	matrice->nrow = n;
	matrice->ncol = m;
	return matrice;
}

/********************************************************************************************************************************************************************************/

bool_t is_equal_smat(smatrix_t *a, smatrix_t *b){
	errno = 0;
	if(a==NULL || b==NULL){																	/*one of the two matrices could be NULL*/
		errno = EINVAL;																		/*invalid argument passed to function*/
		return FALSE;
	}
	bool_t ret = TRUE;
	int nrow_a=a->nrow, nrow_b=b->nrow, ncol_a=a->ncol, ncol_b=b->ncol, i;
	if( (nrow_a != nrow_b) || (ncol_a != ncol_b) ) return FALSE;						  	/*cheking if the matrices have the same number of columns and rows*/
	elem_t *row_a, *row_b;
	for(i=0; i<nrow_a && ret; i++){															/*scanning matrix a*/
		for(row_a=(a->mat)[i], row_b=(b->mat)[i]; row_a!=NULL && row_b!=NULL && ret; row_a=row_a->next, row_b=row_b->next)	/*scanning current row*/
			if( row_a->col != row_b->col || row_a->val != row_b->val ) ret = FALSE;			/*ret has the purpose to interrupt the cycle setting itself to false*/
		if( ret && (row_a != NULL || row_b != NULL) ) ret = FALSE;							/*cheking if one of the matrices has elements left*/
	}
	return ret;
}

/********************************************************************************************************************************************************************************/

int put_elem(smatrix_t *m, unsigned i, unsigned j, double d){
	errno = 0;
	if(m==NULL || i>=m->nrow || j>=m->ncol){	/*the matrix could be NULL or one of the indexes could be out of range or negative*/
		errno = EINVAL;							/*invalid argument passed to function*/
		return -1;
	}
	(m->mat)[i] = put((m->mat)[i], j, d);		/*calling recursive function put*/
	if(errno==ENOMEM) return -1;				/*cheking if the function new_elem, eventually called by put, has set errno*/
	return 0;
}

/********************************************************************************************************************************************************************************/

int get_elem(smatrix_t *m , unsigned i, unsigned j, double *pd){
	errno = 0;
	if(m==NULL || pd==NULL){											/*the matrix or the double* pointer could be NULL*/
		errno = EINVAL;													/*invalid argument passed to function*/
		return -1;
	}
	if(i>=m->nrow || j>=m->ncol){										/*one of the indexes could be out of range or negative*/
		errno = ENOTSUP;												/*operation not supported*/
		return -1;
	}
	elem_t *cols_mat;
	for(cols_mat=(m->mat)[i]; cols_mat->col!=j && cols_mat!=NULL; cols_mat=cols_mat->next) ;	/*scanning row i of the matrix searching for column j*/
	*pd = cols_mat->col==j ? cols_mat->val : 0;							/*setting pointed variable value*/
	return 0;
}

/********************************************************************************************************************************************************************************/

void free_smat(smatrix_t **pm){
	errno = 0;
	if(pm==NULL || *pm==NULL){													/*the matrix or its pointer could be NULL*/
		errno = EINVAL;															/*invalid argument passed to function*/
		return;
	}
	elem_t **prow = (*pm)->mat, *aux, *oux; int i;
	for(i=0; i<(*pm)->nrow; i++)												/*scanning the matrix*/
		for(aux=prow[i]; aux!=NULL; oux=aux, aux=aux->next, free(oux)) ;		/*scanning current row freeing each element*/
	free(prow);
	free(*pm);
	*pm = NULL;
}

/********************************************************************************************************************************************************************************/

smatrix_t *sum_smat(smatrix_t *a, smatrix_t *b){
	errno = 0;
	if(a==NULL || b==NULL){																		/*one of the two matrices could be NULL*/
		errno = EINVAL;																			/*invalid argument passed to function*/
		return NULL;
	}
	if( a->nrow != b->nrow || a->ncol != b->ncol ){												/*checking if the sum is doable*/
		errno = ENOTSUP;																		/*operation not supported*/
		return NULL;
	}
	int i;
	smatrix_t *m_somma = new_smat(a->nrow, a->ncol);
	if(errno==ENOMEM) return NULL;
	elem_t *min, *aux, *tail=NULL;
	for( i=0; i<a->nrow; i++ )																	/*scanning the matrices*/
		for( min=(a->mat)[i], aux=(b->mat)[i]; min!=NULL || aux!=NULL; min=min->next ){			/*scanning both matrices rows*/
			if( (min!=NULL && aux==NULL) || (min==NULL && aux!=NULL) ){							/*one of the rows might have come to the end*/
				if(min==NULL) SWAP( &min, &aux, sizeof(min) );
				INS_TAIL(m_somma, (m_somma->mat)+i, &tail, min->col, min->val);					/*inserting on the tail of each row in O(1)*/
				if(errno==ENOMEM) return NULL;
				continue;
			}
			if( min->col == aux->col ){															/*each current element has the same colum index*/
				INS_TAIL(m_somma, (m_somma->mat)+i, &tail, min->col, (min->val)+(aux->val));	/*inserting on the tail of each row in O(1)*/
				if(errno==ENOMEM) return NULL;
				aux = aux->next;
			}
			else{
				if( min!=MIN_INDEX(min, aux) ) SWAP( &min, &aux, sizeof(min) );					/*setting min to point the minimum between itself and aux*/
				INS_TAIL(m_somma, (m_somma->mat)+i, &tail, min->col, min->val);					/*inserting on the tail of each row in O(1)*/
				if(errno==ENOMEM) return NULL;
			}
		}
	return m_somma;
}

/********************************************************************************************************************************************************************************/

smatrix_t *prod_smat(smatrix_t *a, smatrix_t *b){
	errno = 0;
	if(a==NULL || b==NULL){																/*one of the two matrices could be NULL*/
		errno = EINVAL;																	/*invalid argument passed to function*/
		return NULL;
	}
	if( a->ncol != b->nrow ){															/*checking if the product is doable*/
		errno = ENOTSUP;																/*operation not supported*/
		return NULL;
	}
	int nrow_a=a->nrow, ncol_b=b->ncol, i, j;
	double *tmp = calloc(ncol_b, sizeof(double));										/*auxiliary array allocated for partial summation*/
	smatrix_t *m_prodotto = new_smat(nrow_a, ncol_b);
	if(errno==ENOMEM) return NULL;
	elem_t *row_a, *row_b, *tail=NULL;
	for(i=0; i<nrow_a; i++){															/*scanning matrix a*/
		for( row_a=(a->mat)[i]; row_a!=NULL; row_a = row_a->next )						/*scanning current row of matrix a*/
			for( row_b = (b->mat)[row_a->col]; row_b!=NULL; row_b = row_b->next )		/*scanning current row of matrix b, saving partial summation into the auxiliary array*/
				tmp[row_b->col] += (row_a->val)*(row_b->val);
		for(j=0; j<ncol_b; j++){														/*copying auxiliary array into m_prodotto inserting on the tail of each row in O(1)*/
			INS_TAIL(m_prodotto, (m_prodotto->mat)+i, &tail, j, tmp[j]);
			if(errno==ENOMEM) return NULL;
			tmp[j] = 0;
		}
	}
	free(tmp);
	return m_prodotto;
}

/********************************************************************************************************************************************************************************/

smatrix_t *transp_smat(smatrix_t *a){
	errno = 0;
	if(a==NULL){																				/*the matrix could be NULL*/
		errno = EINVAL;																			/*invalid argument passed to function*/
		return NULL;
	}
	smatrix_t *m_transp = new_smat(a->ncol, a->nrow);
	elem_t *aux, **tail=malloc((a->ncol)*sizeof(elem_t*));										/*auxiliary array of tails to each row*/
	if(errno==ENOMEM || tail==NULL) return NULL;
	int i;
	for(i=0; i<(a->nrow); i++)																	/*scanning the matrix top down*/
		for(aux=(a->mat)[i]; aux!=NULL; aux=aux->next){											/*scanning current row*/
			INS_TAIL(m_transp, (m_transp->mat)+(aux->col), tail+(aux->col), i, aux->val);		/*inserting on the tail of each row in O(1)*/
			if(errno==ENOMEM) return NULL;
		}
	free(tail);
	return m_transp;
}

/********************************************************************************************************************************************************************************/

smatrix_t *load_smat(FILE *fd){
	errno = 0;
	if(fd==NULL){													/*the file could be NULL or not opened*/
		errno = EINVAL;												/*invalid argument passed to function*/
		return NULL;
	}
	int n_row, n_col, row_el, col_el; double val;
	if( fscanf(fd, "%d %d", &n_row, &n_col)<2 ){					/*scanning first two elements of the file: number of rows and columns*/
		errno = EIO;												/*input output error*/
		return NULL;
	}
	smatrix_t *matrice = new_smat(n_row, n_col);
	if(errno==ENOMEM) return NULL;
	while( fscanf(fd, "%d", &row_el)==1 ){							/*scanning one element of the file: the first int of the row*/
		if( fscanf(fd, "%d %lf", &col_el, &val)<2 ){				/*scanning two elements of the file: the second int and the float*/
			free_smat(&matrice);
			errno = EIO;											/*input output error*/
			return NULL;
		}
		if( put_elem(matrice, row_el, col_el, val)<0 ){				/*inserting element*/
			free_smat(&matrice);
			return NULL;
		}
	}
	return matrice;
}

/********************************************************************************************************************************************************************************/

int save_smat(FILE *fd, smatrix_t *m){
	errno = 0;
	if(fd==NULL || m==NULL){													/*the matrix could be NULL or the file not opened*/
		errno = EINVAL;															/*invalid argument passed to function*/
		return -1;
	}
	int n_row=m->nrow, n_col=m->ncol, i;
	if( fprintf(fd, "%d\n%d\n", n_row, n_col)<2 ){								/*saving first two elements into the file*/
		errno = EIO;															/*input output error*/
		return -1;
	}
	elem_t *row;
	for(i=0; i<n_row; i++)														/*scanning matrix m*/
		for(row=(m->mat)[i]; row!=NULL; row=row->next)							/*scanning current row of matrix m*/
			if( fprintf(fd, "%d %d %lf\n", i, row->col, row->val)<3 ){			/*saving three elements into the file*/
				errno = EIO;													/*input output error*/
				return -1;
			}
	return 0;
}

/********************************************************************************************************************************************************************************//*

The binary file used in savebin_smat is composed by a bunch of numbers written in the right order to be read by loadbin_smat.
For each matrix we have:
--> one integer that represent the amount of rows of the matrix;
--> one integer that represent the amount of columns of the matrix;
--> a sequence of two integers and one float for each element, that represent the row and column indexes and the value of the element itself.

Function loadbin_smat will read the numbers in the given sequence.
If there will be an error of any kind, the function will read the wrong amount of byte and return a lesser value than expected,
therefore the matrix will be deallocate and a NULL value will be returned.

*//********************************************************************************************************************************************************************************/

smatrix_t *loadbin_smat(FILE *fd){
	errno = 0;
	if(fd==NULL){																				/*the file could be NULL or not opened*/
		errno = EINVAL;																			/*invalid argument passed to function*/
		return NULL;
	}
	int n_row, n_col, row_el, col_el; double val;
	if( fread(&n_row, sizeof(int), 1, fd)<1 || fread(&n_col, sizeof(int), 1, fd)<1 ){			/*scanning first two elements of the binary file: number of rows and columns*/
		errno = EIO;																			/*input output error*/
		return NULL;
	}
	smatrix_t *matrice = new_smat(n_row, n_col);
	if(errno==ENOMEM) return NULL;
	while( fread(&row_el, sizeof(int), 1, fd)==1 ){												/*scanning one element of the binary file: the first int of the row*/
		if( fread(&col_el, sizeof(int), 1, fd)<1 || fread(&val, sizeof(double), 1, fd)<1 ){		/*scanning two elements of the binary file: the second int and the float*/
			free_smat(&matrice);
			errno = EIO;																		/*input output error*/
			return NULL;
		}
		if( put_elem(matrice, row_el, col_el, val)<0 ){											/*inserting element*/
			free_smat(&matrice);
			return NULL;
		}
	}
	return matrice;
}

/********************************************************************************************************************************************************************************/

int savebin_smat(FILE *fd, smatrix_t *m){
	errno = 0;
	if(fd==NULL || m==NULL){																		/*the matrix could be NULL or the file not opened*/
		errno = EINVAL;																				/*invalid argument passed to function*/
		return -1;
	}
	int n_row=m->nrow, n_col=m->ncol, i;
	if( fwrite(&n_row, sizeof(int), 1, fd)<1 || fwrite(&n_col, sizeof(int), 1, fd)<1 ){				/*saving first two elements into the binary file*/
		errno = EIO;																				/*input output error*/
		return -1;
	}
	elem_t *row;
	for(i=0; i<n_row; i++)																			/*scanning matrix m*/
		for(row=(m->mat)[i]; row!=NULL; row=row->next)												/*scanning current row of matrix m*/
			if( fwrite(&i, sizeof(int), 1, fd)<1 || fwrite(&(row->col), sizeof(int), 1, fd)<1 || fwrite(&(row->val), sizeof(double), 1, fd)<1 ){	/*saving three elements into the binary file*/
				errno = EIO;																		/*input output error*/
				return -1;
			}
	return 0;
}

/********************************************************************************************************************************************************************************/

/*MY AUXILIARY FUNCTIONS*/

/*
Function put takes the pointer (e) to the head of the row where we want to insert the new element,
the index of column (j), the value of element (d) and returns the pointer of the same row,
modified with the new element.
*/
static elem_t *put(elem_t *e, unsigned j, double d){
	if(d==0){
		if( e==NULL ) return NULL;				/*end of the row*/
		if( e->col==j ){						/*element already present: need to be removed*/
			elem_t* aux = e->next;
			free(e);
			return aux;
		}
		e->next = put(e->next, j, d);
		return e;
	}
	if( e!=NULL && e->col==j ){					/*element already present: need to be overwritten*/
		e->val = d;
		return e;
	}
	if( (e!=NULL && e->col>j) || e==NULL ){		/*element not found yet or the row has come to the end*/
		elem_t *aux = new_elem(j, d);
		if(aux==NULL) return e;
		aux->next = e;
		return aux;
	}
	e->next = put(e->next, j, d);
	return e;
}

/*
Function new_elem takes the index of column (j), the value of element (d)
and returns a new element to be inserted into the matrix.
In case of an unsuccessful allocation of the struct elem_t, it sets errno to ENOMEM and return NULL.
*/
static elem_t *new_elem(unsigned j, double d){
	errno = 0;
	elem_t *aux;
	if( (aux=calloc(1, sizeof(elem_t)))==NULL ){
		errno = ENOMEM;							/*not enough memory available or wrong call to calloc*/
		return NULL;
	}
	aux->col = j;								/*setting the fields*/
	aux->val = d;
	return aux;
}
