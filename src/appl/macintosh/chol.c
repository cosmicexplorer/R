/* chol.f -- translated by f2c (version 19971204).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* ----------------------------------------------------------------------- */

/*  R : A Computer Langage for Statistical Data Analysis */
/*  Copyright (C) 1996, 1997  Robert Gentleman and Ross Ihaka */

/*  This program is free software; you can redistribute it and/or modify */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation; either version 2 of the License, or */
/*  (at your option) any later version. */

/*  This program is distributed in the hope that it will be useful, */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/*  GNU General Public License for more details. */

/*  You should have received a copy of the GNU General Public License */
/*  along with this program; if not, write to the Free Software */
/*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/* ----------------------------------------------------------------------- */

/*     chol performs the choleski decomposition of a symmetric */
/*     positive-definite matrix.  this is just a wrapper for the */
/*     linpack routine dpofa. */

/*     on entry */

/*         a         double precision(lda,n) */
/*                   the upper triangle of the matrix to be factorized */
/*                   is contained in the upper triangle of a. */

/*         lda       integer */
/*                   the leading dimension of a. */

/*         n         integer */
/*                   the number or rows and columns of the matrix */
/*                   to be factorized. */

/*     on return */

/*         v         double precision(n,n) */
/*                   the square-root (choleski) factor. */

/*         info      integer */
/*                   the error indicator from dpofa.  this will be */
/*                   zero unless the matrix being factorized is */
/*                   not positive definite. */

/*     this version dated aug 25, 1996. */
/*     ross ihaka, university of auckland. */

/* Subroutine */ int chol(doublereal *a, integer *lda, integer *n, 
	doublereal *v, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, v_dim1, v_offset, i__1, i__2;

    /* Local variables */
    static integer i__, j;
    extern /* Subroutine */ int dpofa(doublereal *, integer *, integer *, 
	    integer *);


    /* Parameter adjustments */
    v_dim1 = *n;
    v_offset = v_dim1 + 1;
    v -= v_offset;
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    if (i__ > j) {
		v[i__ + j * v_dim1] = 0.;
	    } else {
		v[i__ + j * v_dim1] = a[i__ + j * a_dim1];
	    }
/* L10: */
	}
/* L20: */
    }
    dpofa(&v[v_offset], n, n, info);
    return 0;
} /* chol_ */
