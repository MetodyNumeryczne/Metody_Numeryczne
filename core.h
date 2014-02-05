#ifndef CORE_H
#define CORE_H


#include "import.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
bool computeLinearEquationUsingLU(char order, int matrixDimention, double *matrixA, double *matrixB);

bool computeLinearEquationUsingQR(char order, int matrixDimention, double *matrixA, double *matrixB);

int getIntFromUser(bool onlyPositiveNumbers = false);

//gets matrix or vector (type='M' - Matrix, type='V' - Vector) from file specified by url
//Returns NULL if couldn't open file
//Returns NULL if type='M' and number of data is not perfect Square
//Non double data breaks reading from file
//Returns pointer to matrix with size matrixDimention*matirxDimention
double* getMatrixFromFile(std::string URL, int &matrixDimention, char type);
//Save solution to file given by URL
void saveVectorToFile(double *vector, int size);
//Checks if number is perfect square like 1,4,9,16 ... returns true if it is.
bool isPerfectSquare(int n);
#endif // CORE_H
