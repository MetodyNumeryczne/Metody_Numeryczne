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
    int *pivot=NULL;

    char choice='U'; //U- data from user, F- data from File
    while(1){
        if(choice == 'F'){

        //...
        }
        if(choice == 'U'){
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


            //Chose QR or LU
            std::cout<<"1.Compute Equation using QR"<<endl;
            std::cout<<"2.Compute Equation using LU"<<endl;

            int type=0;
            while(type!=1 && type!=2){
                type=getIntFromUser();
            }

            bool result=false;
            if(type == 1)
                result = computeLinearEquationUsingQR('T',matrixADimention,matrixA,vectorB);
            else if(type == 2)
                result = computeLinearEquationUsingLU('T',matrixADimention, matrixA, vectorB);
            else
                std::cout<<"This should never happen";

            if(result){
                cout<<"Wynik: "<<endl;
                for(int i=0;i<matrixADimention;i++)
                    std::cout<<vectorB[i]<<std::endl;
            }
            else
                std::cout<<"Could not solve equation";

            delete[] matrixA;
            delete[] vectorB;
        }
    }
    return 0;
}
