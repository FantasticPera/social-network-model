#include "Graph.h"

using namespace std;


Graph::Graph(const Graph& someGraph): Matrix(someGraph){
    List<string> emptyList;
    nodeNames = emptyList;

    for (int i = 0; i < someGraph.nodeNames.getNumOfElem(); i++) {
        nodeNames.addElem(someGraph.nodeNames.getElem(i));
    }
}

void Graph::deleteGraph()
{
    deleteMatrix();
    nodeNames.deleteList();
}

void Graph::setWeight(int i, int j, float weight) {
    if (i == j) {
        cout << "Error - Node cannot interact with itself." << endl;
        return;
    }
    if (i >= 0 and i < n and j >= 0 and j < n) {
        NodeMatrix* curr = head;
        for (int row = 0; row < i; row++) {
            curr = curr->down;
        }
        for (int col = 0; col < j; col++) {
            curr = curr->right;
        }
        if (weight > 1) curr->weight = 1;
        if (weight < 0) curr->weight = 0;
        else curr->weight = weight;
    }
    else {
        cout << "Index out of range." << endl;
    }
}

void Graph::setWeight(std::string node1, std::string node2, float weight) {
    int i = nodeNames.getIndex(node1);
    int j = nodeNames.getIndex(node2);
    if (i == -1 or j == -1) return;
    if (i == j) {
        cout << "Error - Node cannot interact with itself." << endl;
        return;
    }
    if (i >= 0 and i < n and j >= 0 and j < n) {
        NodeMatrix* curr = head;
        for (int row = 0; row < i; row++) {
            curr = curr->down;
        }
        for (int col = 0; col < j; col++) {
            curr = curr->right;
        }
        if (weight > 1) curr->weight = 1;
        if (weight < 0) curr->weight = 0;
        else curr->weight = weight;
    }
    else {
        cout << "Index out of range." << endl;
    }
}

float Graph::getWeight(std::string row, std::string col) {
    int i = nodeNames.getIndex(row);
    int j = nodeNames.getIndex(col);
    if (i == -1 or j == -1) return -1;
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

void Graph::addNode(std::string nodeName) {
    

    n++;
    nodeNames.addElem(nodeName);
    
    if (head == nullptr) head = new NodeMatrix();
    else {
        NodeMatrix* row = head;
        while (row->down != nullptr) {
            NodeMatrix* col = row;
            while (col->right != nullptr) {
                col = col->right;
            }
            col->right = new NodeMatrix();
            row = row->down;
        }

        NodeMatrix* col = row;
        while (col->right != nullptr) {
            col = col->right;
        }
        col->right = new NodeMatrix();

        row->down = new NodeMatrix();
        row = row->down;
        col = row;
        for (int i = 0; i < n - 1; i++) {
            col->right = new NodeMatrix();
            col = col->right;
        }
    }

}


void Graph::like(std::string nodeName1, std::string nodeName2) {
    if (nodeName1 == nodeName2) {
        cout << "Error - Node cannot interact with itself." << endl;
        return;
    }
    float weight = getWeight(nodeName1, nodeName2);
    if (weight == 0) {
        cout << "Error - " << nodeName1 << " does not follow " << nodeName2 << "." << endl;
        return;
    }
    setWeight(nodeName1, nodeName2, weight + 0.1);
}

void Graph::removeNode(std::string nodeName) {
    int nodeIndex = nodeNames.getIndex(nodeName);
    if (nodeIndex < 0 or nodeIndex > n - 1) {
        cout << "Error - Index out of range." << endl;
        return;
    }
    
    if (n == 2 and nodeIndex == 0) {
        NodeMatrix* currRow = head;
        head = head->down;
        delete currRow->right;
        delete currRow;
        currRow = head;
        head = head->right;
        delete currRow;

        n = 1;
        nodeNames.removeElem(nodeName);
        return;
    }

    //za vrstu
    NodeMatrix* currRow = head;
    NodeMatrix* prevRow = nullptr;
    for (int i = 0; i < nodeIndex; i++) {
        prevRow = currRow;
        currRow = currRow->down;
    }
    if (prevRow != nullptr) {
        prevRow->down = currRow->down;
    }
    else {
        head = currRow->down; // za nultu kolonu i vrstu
    }

    NodeMatrix* currCol = currRow;
    while (currCol != nullptr) {
        NodeMatrix* temp = currCol;
        currCol = currCol->right;
        delete temp;
    }

    //za kolonu
    currRow = head;
    bool headChange = false;
    while (currRow != nullptr) {
        NodeMatrix* currCol = currRow;
        NodeMatrix* prevCol = nullptr;
        for (int i = 0; i < nodeIndex; i++) {
            prevCol = currCol;
            currCol = currCol->right;

        }
        if (prevCol != nullptr) {
            prevCol->right = currCol->right;
        }
        else {
            currRow->right = currCol->right;
            if (currRow->down != nullptr) {
                NodeMatrix* newHead = currRow->right;
                NodeMatrix* nextRow = currRow->down;
                NodeMatrix* nextHead = nextRow->right;
                newHead->down = nextHead;
                if (headChange == false) {
                    head = currRow->right;
                    headChange = true;
                }
            }
        }
        NodeMatrix* temp = currCol;
        currRow = currRow->down;
        delete temp;
    }

    n--;
    nodeNames.removeElem(nodeName);


}





void Graph::transpose() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
                float temp = Matrix::getWeight(i, j);
                setWeight(i, j, Matrix::getWeight(j, i));
                setWeight(j, i, temp);
            }
        }
    }
}


List<string> Graph::DFS(string nodeName) {

    List<string> tempList;
    bool* visited = new bool[n];
    Stack stack(n);

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    stack.push(nodeNames.getIndex(nodeName));
    while (!stack.isEmpty()) {
        int nodeIndex = stack.pop();
        if (!visited[nodeIndex]) {
            visited[nodeIndex] = true;
            //POSETA
            tempList.addElem(nodeNames.getElem(nodeIndex));
            for (int i = 0; i < n; i++) {
                if (!visited[i] and Matrix::getWeight(nodeIndex, i) != 0) {
                    stack.push(i);
                }
            }

        }
    }
    delete[] visited;
    return tempList;
}

List<int> Graph::findEndTimes() {
    Graph graphCopy = *this;
    List<int> endTimes;
    int counter = 0; //broji vreme

    for (int i = 0; i < n; i++) {
        endTimes.addElem(0);
        
    }

    while (graphCopy.getNumOfNodes() != 0) {
        
        List<string> DFSList;

        DFSList = graphCopy.DFS(graphCopy.nodeNames.getElem(0));
        int nCopy = graphCopy.getNumOfNodes();

        //inicijalizacije
        Stack stack(nCopy);
        Stack stackDFS(nCopy);
        
        bool* visited = new bool[nCopy];

        for (int i = 0; i < nCopy; i++) {
            visited[i] = false;
        }

        
        

        stack.push(graphCopy.nodeNames.getIndex(DFSList.getElem(0)));

        while (!stack.isEmpty()) {
            counter++;
            bool pushed = false;
            bool duplicateRemoved = false;

            int nodeIndex = stack.pop();
            if (!visited[nodeIndex]) {
                visited[nodeIndex] = true;
                stackDFS.push(nodeNames.getIndex(graphCopy.nodeNames.getElem(nodeIndex)));
                for (int i = 0; i < nCopy; i++) {
                    if (!visited[i] and graphCopy.Matrix::getWeight(nodeIndex, i) != 0) {
                        stack.push(i);
                        pushed = true;
                    }
                }
            }
            else duplicateRemoved = true;

            if (!pushed and !duplicateRemoved) {

                while (!stackDFS.isEmpty()) {
                    int currIndex = graphCopy.nodeNames.getIndex(nodeNames.getElem(stackDFS.peek()));
                    bool hasUnvisitedNeighbor = false;

                    for (int j = 0; j < nCopy; j++) {
                        if (graphCopy.Matrix::getWeight(currIndex, j) != 0 and !visited[j]) {
                            hasUnvisitedNeighbor = true;
                            break;
                        }
                    }

                    if (hasUnvisitedNeighbor) break;

                    

                    int currIndex1 = stackDFS.pop();
                    graphCopy.removeNode(graphCopy.nodeNames.getElem(currIndex));
                    nCopy = graphCopy.getNumOfNodes();
                    counter++;
                    endTimes.setElem(counter, currIndex1);

                }
            }



        }


        delete[] visited;
    }
    
    return endTimes;
}

List<string> Graph::findLargestComponent() {
    
    Graph transposedGraph = *this;
    transposedGraph.transpose();
    
    
    List<string> finalList;
    List<int> endTimes = findEndTimes();

    while (!transposedGraph.isEmpty()) {
        int max = 0;
        int maxIndex;
        for (int i = 0; i < n; i++) {
            if (endTimes.getElem(i) > max) {
                max = endTimes.getElem(i);
                maxIndex = i;
            }
        }
        if (max == 0) break;

        List<string> currList = transposedGraph.DFS(nodeNames.getElem(maxIndex));
        if (currList.getNumOfElem() > finalList.getNumOfElem()) {
            finalList = currList;
        }

        for (int i = 0; i < currList.getNumOfElem(); i++) {
            string nodeName = currList.getElem(i);
            endTimes.setElem(0, nodeNames.getIndex(nodeName));
            transposedGraph.removeNode(nodeName);
        }

    }




    return finalList;
}

string Graph::findMostPopularUser(int k)
{
    string MPU; //Most popular user
    if (k > n or k <= 0) return MPU;

    List<float> PopularityRates;

    for (int i = 0; i < n; i++) {
        int numOfFollowers = n-1;
        float currUserValue = 0;
        for (int j = 0; j < n; j++) {
            
            if (i == j) continue;
            List<string> MLP = findMLP(nodeNames.getElem(j), nodeNames.getElem(i));
            if (MLP.getNumOfElem() < 2) { // znaci nema konekcije izmedju
                numOfFollowers--;
                continue;
            }
            float temp = 1;
            for (int p = MLP.getNumOfElem() - 1; p > 0; p--) {
                temp *= getWeight(MLP.getElem(p), MLP.getElem(p - 1));
            }

            currUserValue += temp;

        }

        currUserValue = currUserValue * numOfFollowers / (n - 1);

        PopularityRates.addElem(currUserValue);
    }

    int counter = 0;
    
    int maxValueIndex;
    while (counter != k) {
        float maxValue = 0;
        int currMaxValueIndex = -1;

        for (int i = 0; i < n; i++) {
            if (PopularityRates.getElem(i) >= maxValue) {
                maxValue = PopularityRates.getElem(i);
                currMaxValueIndex = i;
            }
        }

        if (currMaxValueIndex == -1) return MPU; // znaci ni jedan cvor nije povezan jedan sa drugim

        PopularityRates.setElem(-1, currMaxValueIndex); // ovaj maksimum nije taj
        maxValueIndex = currMaxValueIndex;
        counter++;
    }

    MPU = nodeNames.getElem(maxValueIndex);

    return MPU;
}

List<std::string> Graph::findMLP(std::string node1, std::string node2)
{
    int indexNode1 = nodeNames.getIndex(node1);
    int indexNode2 = nodeNames.getIndex(node2);
    List<string> finalPath;
    if (indexNode1 == -1 or indexNode2 == -1) {
        return finalPath;
    }

    //neki dijkstra kao
    bool* visited = new bool[n]; //imitacija skupa obradjenih
    float* pathWeights = new float[n];
    int* pathInstructions = new int[n];


    //inicijalizacija oba vektora 
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        if (Matrix::getWeight(indexNode1, i) != 0) {
            pathWeights[i] = Matrix::getWeight(indexNode1, i);
            pathInstructions[i] = indexNode1;
        }
        //nema konekcije izmedju node-va
        else {
            pathWeights[i] = 0; //neka mala velicina, jer trazimo max verovatnocu
            pathInstructions[i] = -1; // nije povezano
        }
    }

    visited[indexNode1] = true;

    for (int i = 0; i < n; i++) {
        float maxWeight = 0;
        int maxWeightIndex = indexNode1;
        for (int j = 0; j < n; j++) {
            if (pathWeights[j] > maxWeight and !visited[j]) {
                maxWeight = pathWeights[j];
                maxWeightIndex = j;
            }
        }
        if (pathWeights[maxWeightIndex] == 0) break;
        visited[maxWeightIndex] = true;

        for (int j = 0; j < n; j++) {
            float float1 = pathWeights[maxWeightIndex];
            float float2 = Matrix::getWeight(maxWeightIndex, j);
            float float3 = pathWeights[j];
            if (!visited[j]) {
                if (float1 * float2 > float3) {
                    pathWeights[j] = pathWeights[maxWeightIndex] * Matrix::getWeight(maxWeightIndex, j);
                    pathInstructions[j] = maxWeightIndex;
                }
            }
        }

    }

    //rekonstrukcija puta
    
    
    if (pathInstructions[indexNode2] == -1) return finalPath; // nema konekcije
    
    int temp = indexNode2;

    while (temp != indexNode1) {
        finalPath.addElem(nodeNames.getElem(temp));
        temp = pathInstructions[temp];
    }
    finalPath.addElem(nodeNames.getElem(temp));


    delete[] pathWeights;
    delete[] pathInstructions;
    return finalPath;
}

void Graph::printNodeNames() {
    nodeNames.print();
}

