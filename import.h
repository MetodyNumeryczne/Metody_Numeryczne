#ifndef IMPORT_H
#define IMPORT_H

//For QR linear equation
extern "C" void dgels_(const char *trans, const int *M, const int *N, const int *nrhs,
                       double *A, const int *lda, double *b, const int *ldb, double *work,
                       const int * lwork, int *info);
//For LU linear equation
extern "C" void  dgetrs_(char *trans, int *n, int *nrhs, double *a,
                         int *lda, int *ipiv, double *b, int *ldb, int *info);
#endif // IMPORT_H


