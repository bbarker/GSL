/* blas/source_tbmv_c.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Gerard Jungman
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * Author:  G. Jungman
 * RCS:     $Id$
 */

{
  int nounit = (Diag == CblasNonUnit);

  size_t i;
  size_t j;
  size_t ix, jx;

  if ((order == CblasRowMajor && TransA == CblasNoTrans && Uplo == CblasUpper)
      || (order == CblasColMajor && TransA == CblasTrans && Uplo == CblasLower))
    {

      /* form  x := A*x */
      ix = OFFSET (N, incX);
      for (i = 0; i < N; i++)
	{
	  BASE temp_r = 0.0;
	  BASE temp_i = 0.0;
	  const size_t j_min = i + 1;
	  size_t jx = OFFSET (N, incX) + incX * j_min;
	  for (j = j_min; j < N; j++)
	    {
	      const BASE x_real = REAL (X, jx);
	      const BASE x_imag = IMAG (X, jx);
	      const BASE A_real = REAL (A, lda * i + j);
	      const BASE A_imag = IMAG (A, lda * i + j);

	      temp_r += A_real * x_real - A_imag * x_imag;
	      temp_i += A_real * x_imag + A_imag * x_real;

	      jx += incX;
	    }
	  if (nounit)
	    {
	      const BASE x_real = REAL (X, ix);
	      const BASE x_imag = IMAG (X, ix);
	      const BASE A_real = REAL (A, lda * i + i);
	      const BASE A_imag = IMAG (A, lda * i + i);

	      REAL (X, ix) = temp_r + (A_real * x_real - A_imag * x_imag);
	      IMAG (X, ix) = temp_i + (A_real * x_imag + A_imag * x_real);
	    }
	  else
	    {
	      REAL (X, ix) += temp_r;
	      IMAG (X, ix) += temp_i;
	    }
	  ix += incX;
	}
    }
  else
    if ((order == CblasRowMajor && TransA == CblasNoTrans && Uplo == CblasLower) 
        || (order == CblasColMajor && TransA == CblasTrans && Uplo == CblasUpper))
    {

      ix = OFFSET (N, incX) + (N - 1) * incX;

      for (i = N; i > 0 && i--;)
	{
	  BASE temp_r = 0.0;
	  BASE temp_i = 0.0;
	  const size_t j_max = i;
	  jx = OFFSET (N, incX);
	  for (j = 0; j < j_max; j++)
	    {
	      const BASE x_real = REAL (X, jx);
	      const BASE x_imag = IMAG (X, jx);
	      const BASE A_real = REAL (A, lda * i + j);
	      const BASE A_imag = IMAG (A, lda * i + j);

	      temp_r += A_real * x_real - A_imag * x_imag;
	      temp_i += A_real * x_imag + A_imag * x_real;

	      jx += incX;
	    }
	  if (nounit)
	    {
	      const BASE x_real = REAL (X, ix);
	      const BASE x_imag = IMAG (X, ix);
	      const BASE A_real = REAL (A, lda * i + i);
	      const BASE A_imag = IMAG (A, lda * i + i);

	      REAL (X, ix) = temp_r + (A_real * x_real - A_imag * x_imag);
	      IMAG (X, ix) = temp_i + (A_real * x_imag + A_imag * x_real);
	    }
	  else
	    {
	      REAL (X, ix) += temp_r;
	      IMAG (X, ix) += temp_i;
	    }
	  ix -= incX;
	}
    }
  else
    if ((order == CblasRowMajor && TransA == CblasTrans && Uplo == CblasUpper)
	|| (order == CblasColMajor && TransA == CblasNoTrans && Uplo == CblasLower))
    {
      /* form  x := A'*x */

      ix = OFFSET (N, incX) + (N - 1) * incX;
      for (i = N; i > 0 && i--;)
	{
	  BASE temp_r = 0.0;
	  BASE temp_i = 0.0;
	  const size_t j_max = i;
	  jx = OFFSET (N, incX);
	  for (j = 0; j < i; j++)
	    {
	      const BASE x_real = REAL (X, jx);
	      const BASE x_imag = IMAG (X, jx);
	      const BASE A_real = REAL (A, lda * j + i);
	      const BASE A_imag = IMAG (A, lda * j + i);

	      temp_r += A_real * x_real - A_imag * x_imag;
	      temp_i += A_real * x_imag + A_imag * x_real;

	      jx += incX;
	    }
	  if (nounit)
	    {
	      const BASE x_real = REAL (X, ix);
	      const BASE x_imag = IMAG (X, ix);
	      const BASE A_real = REAL (A, lda * i + i);
	      const BASE A_imag = IMAG (A, lda * i + i);

	      REAL (X, ix) = temp_r + (A_real * x_real - A_imag * x_imag);
	      IMAG (X, ix) = temp_i + (A_real * x_imag + A_imag * x_real);
	    }
	  else
	    {
	      REAL (X, ix) += temp_r;
	      IMAG (X, ix) += temp_i;
	    }
	  ix -= incX;
	}

    }
  else
    if ((order == CblasRowMajor && TransA == CblasTrans && Uplo == CblasLower)
	|| (order == CblasColMajor && TransA == CblasNoTrans && Uplo == CblasUpper))
    {
      ix = OFFSET (N, incX);
      for (i = 0; i < N; i++)
	{
	  BASE temp_r = 0.0;
	  BASE temp_i = 0.0;
	  const size_t j_min = i + 1;
	  jx = OFFSET (N, incX) + j_min * incX;
	  for (j = j_min; j < N; j++)
	    {
	      const BASE x_real = REAL (X, jx);
	      const BASE x_imag = IMAG (X, jx);
	      const BASE A_real = REAL (A, lda * j + i);
	      const BASE A_imag = IMAG (A, lda * j + i);

	      temp_r += A_real * x_real - A_imag * x_imag;
	      temp_i += A_real * x_imag + A_imag * x_real;

	      jx += incX;
	    }
	  if (nounit)
	    {
	      const BASE x_real = REAL (X, ix);
	      const BASE x_imag = IMAG (X, ix);
	      const BASE A_real = REAL (A, lda * i + i);
	      const BASE A_imag = IMAG (A, lda * i + i);

	      REAL (X, ix) = temp_r + (A_real * x_real - A_imag * x_imag);
	      IMAG (X, ix) = temp_i + (A_real * x_imag + A_imag * x_real);
	    }
	  else
	    {
	      REAL (X, ix) += temp_r;
	      IMAG (X, ix) += temp_i;
	    }
	  ix += incX;
	}
    }
  else if (order == CblasRowMajor && TransA == CblasConjTrans && Uplo == CblasUpper)
    {
      /* form  x := A'*x */

      ix = OFFSET (N, incX) + (N - 1) * incX;
      for (i = N; i > 0 && i--;)
	{
	  BASE temp_r = 0.0;
	  BASE temp_i = 0.0;
	  const size_t j_max = i;
	  jx = OFFSET (N, incX);
	  for (j = 0; j < j_max; j++)
	    {
	      const BASE x_real = REAL (X, jx);
	      const BASE x_imag = IMAG (X, jx);
	      const BASE A_real = REAL (A, lda * i + j);
	      const BASE A_imag = IMAG (A, lda * i + j);

	      temp_r += A_real * x_real - (-1.0) * A_imag * x_imag;
	      temp_i += A_real * x_imag + (-1.0) * A_imag * x_real;

	      jx += incX;
	    }
	  if (nounit)
	    {
	      const BASE x_real = REAL (X, ix);
	      const BASE x_imag = IMAG (X, ix);
	      const BASE A_real = REAL (A, lda * i + i);
	      const BASE A_imag = IMAG (A, lda * i + i);

	      REAL (X, ix) =
		temp_r + (A_real * x_real - (-1.0) * A_imag * x_imag);
	      IMAG (X, ix) =
		temp_i + (A_real * x_imag + (-1.0) * A_imag * x_real);
	    }
	  else
	    {
	      REAL (X, ix) += temp_r;
	      IMAG (X, ix) += temp_i;
	    }
	  ix -= incX;
	}
    }
  else if (order == CblasRowMajor && TransA == CblasConjTrans && Uplo == CblasLower)
    {

      ix = OFFSET (N, incX);
      for (i = 0; i < N; i++)
	{
	  BASE temp_r = 0.0;
	  BASE temp_i = 0.0;
	  const size_t j_min = i + 1;
	  jx = OFFSET (N, incX) + j_min * incX;
	  for (j = j_min; j < N; j++)
	    {
	      const BASE x_real = REAL (X, jx);
	      const BASE x_imag = IMAG (X, jx);
	      const BASE A_real = REAL (A, lda * i + j);
	      const BASE A_imag = IMAG (A, lda * i + j);

	      temp_r += A_real * x_real - (-1.0) * A_imag * x_imag;
	      temp_i += A_real * x_imag + (-1.0) * A_imag * x_real;

	      jx += incX;
	    }
	  if (nounit)
	    {
	      const BASE x_real = REAL (X, ix);
	      const BASE x_imag = IMAG (X, ix);
	      const BASE A_real = REAL (A, lda * i + i);
	      const BASE A_imag = IMAG (A, lda * i + i);

	      REAL (X, ix) =
		temp_r + (A_real * x_real - (-1.0) * A_imag * x_imag);
	      IMAG (X, ix) =
		temp_i + (A_real * x_imag + (-1.0) * A_imag * x_real);
	    }
	  else
	    {
	      REAL (X, ix) += temp_r;
	      IMAG (X, ix) += temp_i;
	    }
	  ix += incX;
	}
    }
  else if (order == CblasColMajor && TransA == CblasConjTrans && Uplo == CblasUpper)
    {
      /* form  x := A*x */

      ix = OFFSET (N, incX);
      for (i = 0; i < N; i++)
	{
	  BASE temp_r = 0.0;
	  BASE temp_i = 0.0;
	  const size_t j_min = i + 1;
	  size_t jx = OFFSET (N, incX) + incX * j_min;
	  for (j = j_min; j < N; j++)
	    {
	      const BASE x_real = REAL (X, jx);
	      const BASE x_imag = IMAG (X, jx);
	      const BASE A_real = REAL (A, lda * i + j);
	      const BASE A_imag = IMAG (A, lda * i + j);

	      temp_r += A_real * x_real - (-1.0) * A_imag * x_imag;
	      temp_i += A_real * x_imag + (-1.0) * A_imag * x_real;

	      jx += incX;
	    }
	  if (nounit)
	    {
	      const BASE x_real = REAL (X, ix);
	      const BASE x_imag = IMAG (X, ix);
	      const BASE A_real = REAL (A, lda * i + i);
	      const BASE A_imag = IMAG (A, lda * i + i);

	      REAL (X, ix) =
		temp_r + (A_real * x_real - (-1.0) * A_imag * x_imag);
	      IMAG (X, ix) =
		temp_i + (A_real * x_imag + (-1.0) * A_imag * x_real);
	    }
	  else
	    {
	      REAL (X, ix) += temp_r;
	      IMAG (X, ix) += temp_i;
	    }
	  ix += incX;
	}
    }
  else if (order == CblasColMajor && TransA == CblasConjTrans && Uplo == CblasLower)
    {
      ix = OFFSET (N, incX) + (N - 1) * incX;

      for (i = N; i > 0 && i--;)
	{
	  BASE temp_r = 0.0;
	  BASE temp_i = 0.0;
	  const size_t j_max = i;
	  jx = OFFSET (N, incX);
	  for (j = 0; j < j_max; j++)
	    {
	      const BASE x_real = REAL (X, jx);
	      const BASE x_imag = IMAG (X, jx);
	      const BASE A_real = REAL (A, lda * i + j);
	      const BASE A_imag = IMAG (A, lda * i + j);

	      temp_r += A_real * x_real - (-1.0) * A_imag * x_imag;
	      temp_i += A_real * x_imag + (-1.0) * A_imag * x_real;

	      jx += incX;
	    }
	  if (nounit)
	    {
	      const BASE x_real = REAL (X, ix);
	      const BASE x_imag = IMAG (X, ix);
	      const BASE A_real = REAL (A, lda * i + i);
	      const BASE A_imag = IMAG (A, lda * i + i);

	      REAL (X, ix) =
		temp_r + (A_real * x_real - (-1.0) * A_imag * x_imag);
	      IMAG (X, ix) =
		temp_i + (A_real * x_imag + (-1.0) * A_imag * x_real);
	    }
	  else
	    {
	      REAL (X, ix) += temp_r;
	      IMAG (X, ix) += temp_i;
	    }
	  ix -= incX;
	}
    }
  else
    {
      BLAS_ERROR ("unrecognized operation");
    }
}
