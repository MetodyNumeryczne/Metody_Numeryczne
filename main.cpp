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
    double *matrixCopyA=NULL;
    double *vectorCopyB=NULL;

    char choice='F'; //U- data from user, F- data from File
    while(1){
        if(choice == 'F'){
            std::string URL;
            std::cout<<"Podaj ścieżkę do pliku z macierzą A";
            std::cin>>URL;
            matrixA=getMatrixFromFile(URL,matrixADimention,'M');
            if(matrixA==NULL){
                std::cout<<"Could not get matrix from file";
                break;
            }
            std::cout<<"Podaj sciezke do pliku z wektorem B";
            std::cin>>URL;
            int tempDimention;
            vectorB=getMatrixFromFile(URL,tempDimention,'V');
            if(vectorB==NULL || tempDimention!=matrixADimention){
                std::cout<<"Błąd podczas odczytu wektora B";
                delete[] matrixA;
                matrixA=NULL;
                if(vectorB!=NULL){
                    delete[] vectorB;
                    vectorB=NULL;
                }
                break;
            }

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
    }
            //Chose QR or LU
            std::cout<<"1.Compute Equation using QR"<<std::endl;
            std::cout<<"2.Compute Equation using LU"<<std::endl;
            std::cout<<"3.Compute Equation using both factorizations"<<std::endl;

            int type=0;
            while(type!=1 && type!=2 && type!=3){
                type=getIntFromUser();
            }

            bool result=false;
            //QR
            if(type == 1)
                result = computeLinearEquationUsingQR('T',matrixADimention,matrixA,vectorB);
            //LU
            else if(type == 2)
                result = computeLinearEquationUsingLU('T',matrixADimention, matrixA, vectorB);
            //Both
            else if (type ==3){
                matrixCopyA = new double[matrixADimention*matrixADimention];
                vectorCopyB = new double[matrixADimention];
                for(int i=0;i<matrixADimention*matrixADimention;i++)
                    matrixCopyA[i]=matrixA[i];
                for(int i=0;i<matrixADimention;i++)
                    vectorCopyB[i]=vectorB[i];
                result = computeLinearEquationUsingQR('T',matrixADimention,matrixA,vectorB);
                if(result==false)
                    break;
                result = computeLinearEquationUsingLU('T',matrixADimention, matrixCopyA, vectorCopyB);
            }
            else
                std::cout<<"This should never happen";

            if(result && (type ==1 || type==2)){
                cout<<"Wynik: "<<endl;
                for(int i=0;i<matrixADimention;i++)
                    std::cout<<vectorB[i]<<std::endl;
            }
            else if(result && type ==3){
                cout<<"Wynik QR: "<<endl;
                for(int i=0;i<matrixADimention;i++)
                    std::cout<<vectorB[i]<<std::endl;
                cout<<"Wynik LU: "<<endl;
                for(int i=0;i<matrixADimention;i++)
                    std::cout<<vectorCopyB[i]<<std::endl;
                delete[] matrixCopyA;
                delete[] vectorCopyB;
            }
            else
                std::cout<<"Could not solve equation";

            delete[] matrixA;
            delete[] vectorB;
            matrixA=NULL;
            vectorB=NULL;
        }

    return 0;
}
