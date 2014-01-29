#ifndef CORE_H
#define CORE_H


#include "import.h"

bool computeLinearEquationUsingLU(char order, int matrixDimention, double *matrixA, double *matrixB);

bool computeLinearEquationUsingQR(char order, int matrixDimention, double *matrixA, double *matrixB);

int getIntFromUser(bool onlyPositiveNumbers = false);
#endif // CORE_H
