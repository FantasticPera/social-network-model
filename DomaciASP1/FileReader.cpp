#include "FileReader.h"

using namespace std;

Graph FileReader::readFile(std::string fileName) {
    List<string> nullList;
    Graph nullGraph(0, nullList);

    if (fileName.find_first_of(' ') != string::npos) {
        cout << "Invalid file name." << endl;
        return nullGraph;
    }

    ifstream inFile;
    inFile.open(fileName);

    if (!inFile.is_open()) {
        cout << "An error occurred while opening the file." << endl;
        return nullGraph;
    }

    string line;
    int rowNum = 1;
    int n, numOfBranches;
    List<string> nodeNames;
    Graph tempGraph(0, nullList); // Prazan graf

    while (getline(inFile, line)) {
        if (rowNum == 1) {
            try {
                n = stoi(line);
            }
            catch (...) {
                cout << "Unexpected value in line 1." << endl;
                return nullGraph;
            }

        }
        else if (rowNum == 2) { // citanja broja grana grafa, zavisi od n*(n-1)
            try {
                numOfBranches = stoi(line);
            }
            catch (...) {
                cout << "Unexpected value in line 2." << endl;
                return nullGraph;
            }
            if (numOfBranches > n * (n - 1)) {
                cout << "Error - number of branches exceeds maximum value for given number of nodes" << endl;
                return nullGraph;
            }
        }
        else if (rowNum == 3) { // citanje imena cvorova grafa, zavisi od n
            int counter = 1;
            string tempString;
            for (char c : line) {
                if (c == ' ') {
                    if (counter > n) {
                        cout << "Error - Unexpected number of elements in line 3." << endl;
                        return nullGraph;
                    }
                    else {
                        nodeNames.addElem(tempString);
                        tempString.clear();
                        counter++;
                    }
                }
                else {
                    tempString += c;
                }
                
            }
            if (!tempString.empty()) nodeNames.addElem(tempString);
            if (counter != n) {
                cout << "Error - Unexpected number of elements in line 3." << endl;
                return nullGraph;
            }
            Graph tempGraph1(n, nodeNames);
            tempGraph = tempGraph1;
        }
        //Citanje grana
        else {
            if (rowNum > 3 + numOfBranches) {
                cout << "Error - unexpected number of lines in file." << endl;
                return nullGraph;
            }

            int counter = 1;
            string tempString;
            float weight;
            string node1, node2;


            for (char c : line) {
                if (c == ' ') {
                    if (counter > 3) {
                        cout << "Error - Unexpected number of elements in Branches." << endl;
                        return nullGraph;
                    }
                    else {
                        if (counter == 1) {
                            node1 = tempString;
                        }
                        else if (counter == 2) {
                            node2 = tempString;
                        }
                        counter++;
                        tempString.clear();
                    }
                }
                else {
                    tempString = tempString + c;
                }

            }
            if (!tempString.empty()) {
                try {
                    weight = stof(tempString);
                }
                catch (invalid_argument& e) {
                    cout << "Unexpected weight value." << endl;
                    return nullGraph;
                }

            }
            if (counter != 3) {
                cout << "Error - Unexpected number of elements in Branches." << endl;
                return nullGraph;
            }
            tempGraph.setWeight(node1, node2, weight);

        }


        rowNum++;
    }

    inFile.close();
    return tempGraph;
}

