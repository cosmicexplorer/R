/* zsisl.f -- translated by f2c (version 19971204).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;


/*     zsisl solves the double complex symmetric system */
/*     a * x = b */
/*     using the factors computed by zsifa. */

/*     on entry */

/*        a       double complex(lda,n) */
/*                the output from zsifa. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*        kpvt    integer(n) */
/*                the pivot vector from zsifa. */

/*        b       double complex(n) */
/*                the right hand side vector. */

/*     on return */

/*        b       the solution vector  x . */

/*     error condition */

/*        a division by zero may occur if  zsico  has set rcond .eq. 0.0 */
/*        or  zsifa  has set info .ne. 0  . */

/*     to compute  inverse(a) * c  where  c  is a matrix */
/*     with  p  columns */
/*           call zsifa(a,lda,n,kpvt,info) */
/*           if (info .ne. 0) go to ... */
/*           do 10 j = 1, p */
/*              call zsisl(a,lda,n,kpvt,c(1,j)) */
/*        10 continue */

/*     linpack. this version dated 08/14/78 . */
/*     james bunch, univ. calif. san diego, argonne nat. lab. */

/*     subroutines and functions */

/*     blas zaxpy,zdotu */
/*     fortran iabs */

/* Subroutine */ int zsisl(doublecomplex *a, integer *lda, integer *n, 
	integer *kpvt, doublecomplex *b)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublecomplex z__1, z__2, z__3;

    /* Builtin functions */
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *);

    /* Local variables */
    static doublecomplex temp;
    static integer k;
    static doublecomplex denom;
    extern /* Double Complex */ VOID zdotu(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern /* Subroutine */ int zaxpy(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static doublecomplex ak, bk;
    static integer kp;
    static doublecomplex akm1, bkm1;


/*     internal variables. */


/*     loop backward applying the transformations and */
/*     d inverse to b. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    --kpvt;
    --b;

    /* Function Body */
    k = *n;
L10:
    if (k == 0) {
	goto L80;
    }
    if (kpvt[k] < 0) {
	goto L40;
    }

/*           1 x 1 pivot block. */

    if (k == 1) {
	goto L30;
    }
    kp = kpvt[k];
    if (kp == k) {
	goto L20;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L20:

/*              apply the transformation. */

    i__1 = k - 1;
    zaxpy(&i__1, &b[k], &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
L30:

/*           apply d inverse. */

    i__1 = k;
    z_div(&z__1, &b[k], &a[k + k * a_dim1]);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    --k;
    goto L70;
L40:

/*           2 x 2 pivot block. */

    if (k == 2) {
	goto L60;
    }
    kp = (i__1 = kpvt[k], abs(i__1));
    if (kp == k - 1) {
	goto L50;
    }

/*                 interchange. */

    i__1 = k - 1;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k - 1;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L50:

/*              apply the transformation. */

    i__1 = k - 2;
    zaxpy(&i__1, &b[k], &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    i__1 = k - 2;
    zaxpy(&i__1, &b[k - 1], &a[(k - 1) * a_dim1 + 1], &c__1, &b[1], &c__1);
L60:

/*           apply d inverse. */

    z_div(&z__1, &a[k + k * a_dim1], &a[k - 1 + k * a_dim1]);
    ak.r = z__1.r, ak.i = z__1.i;
    z_div(&z__1, &a[k - 1 + (k - 1) * a_dim1], &a[k - 1 + k * a_dim1]);
    akm1.r = z__1.r, akm1.i = z__1.i;
    z_div(&z__1, &b[k], &a[k - 1 + k * a_dim1]);
    bk.r = z__1.r, bk.i = z__1.i;
    z_div(&z__1, &b[k - 1], &a[k - 1 + k * a_dim1]);
    bkm1.r = z__1.r, bkm1.i = z__1.i;
    z__2.r = ak.r * akm1.r - ak.i * akm1.i, z__2.i = ak.r * akm1.i + ak.i * 
	    akm1.r;
    z__1.r = z__2.r - 1., z__1.i = z__2.i;
    denom.r = z__1.r, denom.i = z__1.i;
    i__1 = k;
    z__3.r = akm1.r * bk.r - akm1.i * bk.i, z__3.i = akm1.r * bk.i + akm1.i * 
	    bk.r;
    z__2.r = z__3.r - bkm1.r, z__2.i = z__3.i - bkm1.i;
    z_div(&z__1, &z__2, &denom);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    i__1 = k - 1;
    z__3.r = ak.r * bkm1.r - ak.i * bkm1.i, z__3.i = ak.r * bkm1.i + ak.i * 
	    bkm1.r;
    z__2.r = z__3.r - bk.r, z__2.i = z__3.i - bk.i;
    z_div(&z__1, &z__2, &denom);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    k += -2;
L70:
    goto L10;
L80:

/*     loop forward applying the transformations. */

    k = 1;
L90:
    if (k > *n) {
	goto L160;
    }
    if (kpvt[k] < 0) {
	goto L120;
    }

/*           1 x 1 pivot block. */

    if (k == 1) {
	goto L110;
    }

/*              apply the transformation. */

    i__1 = k;
    i__2 = k;
    i__3 = k - 1;
    zdotu(&z__2, &i__3, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    kp = kpvt[k];
    if (kp == k) {
	goto L100;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L100:
L110:
    ++k;
    goto L150;
L120:

/*           2 x 2 pivot block. */

    if (k == 1) {
	goto L140;
    }

/*              apply the transformation. */

    i__1 = k;
    i__2 = k;
    i__3 = k - 1;
    zdotu(&z__2, &i__3, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    i__1 = k + 1;
    i__2 = k + 1;
    i__3 = k - 1;
    zdotu(&z__2, &i__3, &a[(k + 1) * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    kp = (i__1 = kpvt[k], abs(i__1));
    if (kp == k) {
	goto L130;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L130:
L140:
    k += 2;
L150:
    goto L90;
L160:
    return 0;
} /* zsisl_ */
