#include "core.h"
#include <iostream>
bool computeLinearEquationUsingLU(char order, int matrixDimention, double *matrixA, double *matrixB){

    if(matrixDimention<=0)
        return false;

    //Create simple pivots for equation solving
    int *pivot = new int[matrixDimention];
    //for(int i=0;i<matrixDimention;i++)
      //  pivot[i]=i+1;


    int ok=1;
    int nrhs=1;

    //LU factorization
    //dgetrf_(&matrixDimention, &matrixDimention, matrixA, &matrixDimention, pivot, &ok);
    dgetrf_(&matrixDimention, &matrixDimention, matrixA, &matrixDimention, pivot, &ok);

    if(ok){
        std::cout<<"Error in LU factorization dgetrf_"<<std::endl;
        return false;
    }

    //Compute Equation using LU factorization
    dgetrs_( &order, &matrixDimention,
             &nrhs, matrixA, &matrixDimention,
             pivot, matrixB, &matrixDimention, &ok);
    delete[] pivot;
    //ok==0 then dgetrs was succesfull
    if(ok)
        return false;
    else
        return true;
}

bool computeLinearEquationUsingQR(char order, int matrixDimention, double *matrixA, double *matrixB){


    if(matrixDimention<=0)
        return false;
    //The number of right hand sides, i.e., the number of
    //columns of the matrices B and X. NRHS >=0.
    int nrhs=1;

    int ok;
    double wkopt;
    double *work;
    int lwork=-1;
    dgels_( &order, &matrixDimention, &matrixDimention, &nrhs, matrixA,
           &matrixDimention, matrixB, &matrixDimention, &wkopt, &lwork,
           &ok );
    if(ok==0)
        lwork=wkopt;
    else
        return false;

    work=new double[lwork];

    dgels_( &order, &matrixDimention, &matrixDimention, &nrhs, matrixA,
           &matrixDimention, matrixB, &matrixDimention, work, &lwork,
           &ok );
    delete[] work;

    if(ok)
        return false;
    else
        return true;
}
int getIntFromUser(bool onlyPositiveNumbers){
    int value=0;

    while(1){
        int temp;
        if(std::cin>>temp){
            value=temp;
            if(onlyPositiveNumbers && temp>0)
                break;
            if(!onlyPositiveNumbers)
                break;
            std::cout<<"Błędnie podana wartość."<<std::endl;
            std::cin.ignore(100,'\n');
        }
        else{
            std::cout<<"Błędnie podana wartość."<<std::endl;
            std::cin.clear();
            std::cin.ignore(100,'\n');
        }
    }
    return value;
}
double* getMatrixFromFile(std::string URL, int &matrixDimention,char type){
    std::ifstream file;
    file.open(URL.data());

    if(!file.is_open()){
        std::cout<<"Could not open file";
        return NULL;
    }
    std::vector<double> data;

    while (true) {
        double x;
        if(file >> x)
            data.push_back(x);
        else
            break;
    }

    if(type=='M'){
        if(!isPerfectSquare(data.size()) || data.size()<1){
            std::cout<<"Dane z pliku nie tworzą macierzy kwadratowej"<<std::endl;
            return NULL;
        }
        matrixDimention=sqrt(data.size());
    }
    else if(type=='V')
        matrixDimention=data.size();
    else
        std::cout<<"Invalid type"<<std::endl;

    double *matrix= new double[data.size()];
    for(int i=0;i<data.size();i++)
        matrix[i]=data.at(i);
    return matrix;


}
bool isPerfectSquare(int n) {
    if (n < 0)
        return false;
    int root(round(sqrt(n)));
    return n == root * root;
}
