#ifndef Graph_h
#define Graph_h

#include "Matrix.h"
#include "List.h"
#include "Stack.h"


class Graph : public Matrix {
public:
    
    Graph(int n, List<std::string> nodeNames) : Matrix(n), nodeNames(nodeNames) {}
    Graph(const Graph& someGraph);
    void deleteGraph();

    virtual void setWeight(int i, int j, float weight) override;

    
    void setWeight(std::string node1, std::string node2, float weight);
    float getWeight(std::string row, std::string col);

    void addNode(std::string nodeName);
    //Prva osoba lajkuje drugu osobu
    void like(std::string nodeName1, std::string nodeName2);
    void removeNode(std::string nodeName);
    void transpose();
    

    List<std::string> DFS(std::string nodeName);
    List<int> findEndTimes();
    List<std::string> findLargestComponent();
    std::string findMostPopularUser(int k);
    List<std::string> findMLP(std::string node1, std::string node2); //Most likely path

    void printNodeNames();


private:
    List<std::string> nodeNames;
};

#endif
