#ifndef GSL_MATRIX_SHORT_H
#define GSL_MATRIX_SHORT_H

#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector_short.h>

typedef struct gsl_matrix_short_struct gsl_matrix_short;

struct gsl_matrix_short_struct
{
  size_t size1;
  size_t size2;
  size_t tda;
  short * data;
  gsl_block_short * block;
} ;

gsl_matrix_short * 
gsl_matrix_short_alloc (size_t n1, size_t n2);

gsl_matrix_short * 
gsl_matrix_short_calloc (size_t n1, size_t n2);

gsl_matrix_short * 
gsl_matrix_short_alloc_from_block (gsl_block_short * b, size_t offset, 
                                   size_t n1, size_t n2, size_t d2);

gsl_matrix_short * 
gsl_matrix_short_alloc_from_matrix (gsl_matrix_short * m,
                                    size_t k1, size_t k2,
                                    size_t n1, size_t n2);

gsl_vector_short * 
gsl_vector_short_alloc_row_from_matrix (gsl_matrix_short * m,
                                        size_t i);

gsl_vector_short * 
gsl_vector_short_alloc_col_from_matrix (gsl_matrix_short * m,
                                        size_t j);

void gsl_matrix_short_free (gsl_matrix_short * m);

short * gsl_matrix_short_ptr(const gsl_matrix_short * m, size_t i, size_t j);
short   gsl_matrix_short_get(const gsl_matrix_short * m, size_t i, size_t j);
void    gsl_matrix_short_set(gsl_matrix_short * m, size_t i, size_t j, short x);

int gsl_matrix_short_fread (FILE * stream, gsl_matrix_short * m) ;
int gsl_matrix_short_fwrite (FILE * stream, const gsl_matrix_short * m) ;
int gsl_matrix_short_fscanf (FILE * stream, gsl_matrix_short * m);
int gsl_matrix_short_fprintf (FILE * stream, const gsl_matrix_short * m, const char * format);
 
int gsl_matrix_short_get_row(gsl_vector_short * v, const gsl_matrix_short * m, size_t i);
int gsl_matrix_short_get_col(gsl_vector_short * v, const gsl_matrix_short * m, size_t j);
int gsl_matrix_short_set_row(gsl_matrix_short * m, size_t i, const gsl_vector_short * v);
int gsl_matrix_short_set_col(gsl_matrix_short * m, size_t j, const gsl_vector_short * v);

int gsl_matrix_short_swap_rows(gsl_matrix_short * m, size_t i, size_t j);
int gsl_matrix_short_swap_cols(gsl_matrix_short * m, size_t i, size_t j);
int gsl_matrix_short_swap_rowcol(gsl_matrix_short * m, size_t i, size_t j);

int gsl_matrix_short_memcpy(gsl_matrix_short * dest, const gsl_matrix_short * src);

int gsl_vector_short_view_row_from_matrix (gsl_vector_short * v, gsl_matrix_short * m, size_t i);
int gsl_vector_short_view_col_from_matrix (gsl_vector_short * v, gsl_matrix_short * m, size_t j);

int gsl_matrix_short_view_from_vector (gsl_matrix_short * m, 
                                       gsl_vector_short * base,
                                       size_t offset, 
                                       size_t n1, size_t n2, size_t d2);

extern int gsl_check_range ;

/* inline functions if you are using GCC */

#ifdef HAVE_INLINE
extern inline 
short
gsl_matrix_short_get(const gsl_matrix_short * m, 
		     const size_t i, const size_t j)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= m->size1)
    {
      GSL_ERROR_RETURN("first index out of range", GSL_EINVAL, 0) ;
    }
  else if (j >= m->size2)
    {
      GSL_ERROR_RETURN("second index out of range", GSL_EINVAL, 0) ;
    }
#endif
  return m->data[i * m->tda + j] ;
} 

extern inline 
void
gsl_matrix_short_set(gsl_matrix_short * m, 
		     const size_t i, const size_t j, const short x)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= m->size1)
    {
      GSL_ERROR_RETURN_NOTHING("first index out of range", GSL_EINVAL) ;
    }
  else if (j >= m->size2)
    {
      GSL_ERROR_RETURN_NOTHING("second index out of range", GSL_EINVAL) ;
    }
#endif
  m->data[i * m->tda + j] = x ;
}
#endif

#endif /* GSL_MATRIX_SHORT_H */
