/* dposl.f -- translated by f2c (version 19971204).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;


/*     dposl solves the double precision symmetric positive definite */
/*     system a * x = b */
/*     using the factors computed by dpoco or dpofa. */

/*     on entry */

/*        a       double precision(lda, n) */
/*                the output from dpoco or dpofa. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*        b       double precision(n) */
/*                the right hand side vector. */

/*     on return */

/*        b       the solution vector  x . */

/*     error condition */

/*        a division by zero will occur if the input factor contains */
/*        a zero on the diagonal.  technically this indicates */
/*        singularity but it is usually caused by improper subroutine */
/*        arguments.  it will not occur if the subroutines are called */
/*        correctly and  info .eq. 0 . */

/*     to compute  inverse(a) * c  where  c  is a matrix */
/*     with  p  columns */
/*           call dpoco(a,lda,n,rcond,z,info) */
/*           if (rcond is too small .or. info .ne. 0) go to ... */
/*           do 10 j = 1, p */
/*              call dposl(a,lda,n,c(1,j)) */
/*        10 continue */

/*     linpack.  this version dated 08/14/78 . */
/*     cleve moler, university of new mexico, argonne national lab. */

/*     subroutines and functions */

/*     blas daxpy,ddot */

/* Subroutine */ int dposl(doublereal *a, integer *lda, integer *n, 
	doublereal *b)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    extern doublereal ddot(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer k;
    static doublereal t;
    extern /* Subroutine */ int daxpy(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static integer kb;


/*     internal variables */


/*     solve trans(r)*y = b */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    --b;

    /* Function Body */
    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	i__2 = k - 1;
	t = ddot(&i__2, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
	b[k] = (b[k] - t) / a[k + k * a_dim1];
/* L10: */
    }

/*     solve r*x = y */

    i__1 = *n;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n + 1 - kb;
	b[k] /= a[k + k * a_dim1];
	t = -b[k];
	i__2 = k - 1;
	daxpy(&i__2, &t, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
/* L20: */
    }
    return 0;
} /* dposl_ */
