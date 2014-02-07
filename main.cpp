#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "core.h"
using namespace  std;
/* Main program */
int main() {

    int matrixADimention;
    double *matrixA=NULL;
    double *vectorB=NULL;
    double *matrixCopyA=NULL;
    double *vectorCopyB=NULL;
    char choice=0;
    std::cout.precision(50);

    while(1){
        while(1){
            choice = 0;
            std::cout<<"Rodzaj akcji:"<<std::endl;
            std::cout<<"U Dane wpisane w konsoli"<<std::endl;
            std::cout<<"F Dane wczytane z pliku"<<std::endl;
            while(choice != 'F' && choice !='U')
                std::cin>>choice;

            if(choice == 'F'){
                std::string URL;
                std::cout<<"Podaj ścieżkę do pliku z macierzą A"<<std::endl;
                std::cin>>URL;
                matrixA=getMatrixFromFile(URL,matrixADimention,'M');
                if(matrixA==NULL){
                    std::cout<<"Could not get matrix from file"<<std::endl;
                    break;
                }
                std::cout<<"Podaj sciezke do pliku z wektorem B"<<std::endl;
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
                cout<<"Podaj rozmiar macierzy A"<<std::endl;
                matrixADimention=getIntFromUser(true);

                matrixA = new double[matrixADimention*matrixADimention];
                vectorB = new double[matrixADimention];

                for(int i=0;i<matrixADimention;i++)
                    for(int j=0;j<matrixADimention;j++){
                        std::cout<<"Podaj element macierzy A "<<i<<" "<<j<<std::endl;
                        matrixA[matrixADimention*i+j] = getIntFromUser();
                    }

                for(int i=0;i<matrixADimention;i++){
                    std::cout<<"Podaj element wektora B "<<i<<std::endl;
                    vectorB[i] = getIntFromUser();
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

            bool resultQR=false;
            bool resultLU= false;
            //QR
            if(type == 1)
                resultQR = computeLinearEquationUsingQR('T',matrixADimention,matrixA,vectorB);
            //LU
            else if(type == 2)
                resultLU = computeLinearEquationUsingLU('T',matrixADimention, matrixA, vectorB);
            //Both
            else if (type ==3){
                matrixCopyA = new double[matrixADimention*matrixADimention];
                vectorCopyB = new double[matrixADimention];
                for(int i=0;i<matrixADimention*matrixADimention;i++)
                    matrixCopyA[i]=matrixA[i];
                for(int i=0;i<matrixADimention;i++)
                    vectorCopyB[i]=vectorB[i];
                resultQR = computeLinearEquationUsingQR('T',matrixADimention,matrixA,vectorB);
                resultLU = computeLinearEquationUsingLU('T',matrixADimention, matrixCopyA, vectorCopyB);


            }
            else
                std::cout<<"This should never happen"<<std::endl;

            if((resultQR || resultLU) && (type ==1 || type==2)){
                cout<<"Wynik: "<<endl;
                for(int i=0;i<matrixADimention;i++)
                    std::cout<<vectorB[i]<<std::endl;

                saveVectorToFile(vectorB,matrixADimention);

            }
            else if(resultQR && resultLU && type ==3){
                cout<<"Wynik QR: "<<endl;
                for(int i=0;i<matrixADimention;i++)
                    std::cout<<vectorB[i]<<std::endl;
                cout<<"Wynik LU: "<<endl;
                for(int i=0;i<matrixADimention;i++)
                    std::cout<<vectorCopyB[i]<<std::endl;

                    saveVectorToFile(vectorB,matrixADimention);
                    saveVectorToFile(vectorCopyB,matrixADimention);

            }
            else
                std::cout<<"Could not solve equation"<<std::endl;

            //Free memory
            if(vectorCopyB!=NULL){
                delete[] vectorCopyB;
                vectorCopyB=NULL;
            }
            if(matrixCopyA!=NULL){
                 delete[] matrixCopyA;
                matrixCopyA=NULL;
            }
            delete[] matrixA;
            delete[] vectorB;
            matrixA=NULL;
            vectorB=NULL;
        }
    }

    return 0;
}
