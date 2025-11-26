#include "Matrix.h"


using namespace std;

Matrix::Matrix() : n(0), head(nullptr) {}

Matrix::Matrix(int n) : n(n) {
    if (n < 1) return;
    head = new NodeMatrix();
    NodeMatrix* currRow = head;
    for (int i = 0; i < n; i++) {
        NodeMatrix* currCol = currRow;
        for (int j = 0; j < n - 1; j++) {
            currCol->right = new NodeMatrix();
            currCol = currCol->right;
        }
        
        if (i < n - 1) {
            currRow->down = new NodeMatrix();
            currRow = currRow->down;
        }
    }

}

Matrix::~Matrix() {
    deleteMatrix();
}

Matrix::Matrix(const Matrix& someMatrix) : n(someMatrix.n) {
    copyMatrix(someMatrix);
}

Matrix& Matrix::operator=(const Matrix& someMatrix) {
    if (this != &someMatrix) {
        deleteMatrix();
        n = someMatrix.n;
        copyMatrix(someMatrix);
    }
    return *this;
}

void Matrix::setWeight(int i, int j, float weight) {
    if (i >= 0 and i < n and j >= 0 and j < n) {
        NodeMatrix* curr = head;
        for (int row = 0; row < i; row++) {
            curr = curr->down;
        }
        for (int col = 0; col < j; col++) {
            curr = curr->right;
        }
        curr->weight = weight;
    }
    else {
        cout << "Index out of range." << endl;
    }
}

float Matrix::getWeight(int i, int j) {
    if (i >= 0 and i < n and j >= 0 and j < n) {
        NodeMatrix* curr = head;
        for (int row = 0; row < i; row++) {
            curr = curr->down;
        }
        for (int col = 0; col < j; col++) {
            curr = curr->right;
        }
        return curr->weight;
    }
    else {
        cout << "Index out of range." << endl;
        return -1;
    }
}

int Matrix::getNumOfNodes() {
    return n;
}

bool Matrix::isEmpty() {
    if (getNumOfNodes() == 0) return true;
    return false;
}

void Matrix::print() {
    NodeMatrix* currRow = head;
    while (currRow) {
        NodeMatrix* currCol = currRow;
        while (currCol) {
            cout << setw(5) << setprecision(2) << fixed << currCol->weight << ' ';
            currCol = currCol->right;
        }
        currRow = currRow->down;
        cout << endl;
        
    }
}

void Matrix::copyMatrix(const Matrix& someMatrix) {
    
    if (someMatrix.head == nullptr) {
        head = nullptr;
        return;
    }

    head = new NodeMatrix(someMatrix.head->weight);
    NodeMatrix* currRow = head;
    NodeMatrix* someMatrixRow = someMatrix.head;
    for (int i = 0; i < n; i++) {
        NodeMatrix* currCol = currRow;
        NodeMatrix* someMatrixCol = someMatrixRow;
        for (int j = 0; j < n - 1; j++) {
            currCol->right = new NodeMatrix(someMatrixCol->right->weight);
            currCol = currCol->right;
            someMatrixCol = someMatrixCol->right;
        }
        if (i < n - 1) {
            currRow->down = new NodeMatrix(someMatrixRow->down->weight);
            currRow = currRow->down;
            someMatrixRow = someMatrixRow->down;
        }
    }


}

void Matrix::deleteMatrix() {
    
    NodeMatrix* currRow = head;
    while (currRow) {
        NodeMatrix* currCol = currRow;
        currRow = currRow->down;
        while (currCol) {
            NodeMatrix* temp = currCol;
            currCol = currCol->right;
            delete temp;
        }
    }
    head = nullptr;
    n = 0;
}
