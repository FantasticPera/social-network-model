#ifndef NodeMatrix_h
#define NodeMatrix_h

struct NodeMatrix {
    NodeMatrix* right;
    NodeMatrix* down;
    float weight;
    NodeMatrix(float weight = 0) : weight(weight), right(nullptr), down(nullptr) {}
};


#endif
