#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <core.h>
using namespace  std;
/* Main program */
int main() {
    int matrixADimention;
    double *matrixA=NULL;
    double *vectorB=NULL;
    int *ok=new int();
    int *pivot=NULL;
    char choice='U'; //U- data from user, F- data from File
    while(1){
        if(choice = 'F'){

        //...
        }
        if(choice = 'U'){
            cout<<"Podaj rozmiar macierzy A"<<endl;
            matrixADimention=getIntFromUser(true);

            matrixA = new double[matrixADimention*matrixADimention];
            vectorB = new double[matrixADimention];

            for(int i=0;i<matrixADimention;i++)
                for(int j=0;j<matrixADimention;j++){
                    std::cout<<"Podaj element macierzy A "<<i<<" "<<j<<std::endl;
                    std::cin>>matrixA[matrixADimention*i+j];
                }

            for(int i=0;i<matrixADimention;i++){
                std::cout<<"Podaj element wektora B "<<i<<std::endl;
                std::cin>>vectorB[i];
            }

            bool result = computeLinearEquationUsingQR('T',matrixADimention,matrixA,vectorB);

            if(result){
                cout<<"Wynik: "<<endl;
                for(int i=0;i<matrixADimention;i++)
                    std::cout<<vectorB[i]<<std::endl;
            }

            delete[] matrixA;
            delete[] vectorB;
        }
    }
    return 0;
}
