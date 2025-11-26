#ifndef Matrix_h
#define Matrix_h


#include "NodeMatrix.h"
#include <iostream>
#include <iomanip>

// radi iskljucivo kao kvadratna matrica
class Matrix {
public:

    Matrix();
    Matrix(int n);

    ~Matrix();

    Matrix(const Matrix& someMatrix);
    Matrix& operator=(const Matrix& someMatrix);

    virtual void setWeight(int i, int j, float weight);
    float getWeight(int i, int j);
    int getNumOfNodes();
    bool isEmpty();
    void print();
    
    void deleteMatrix();

protected:

    int n;
    NodeMatrix* head;
    
    void copyMatrix(const Matrix& someMatrix);
    
};

#endif
