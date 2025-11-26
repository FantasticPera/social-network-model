#include <iostream>
#include "Matrix.h"
#include "Graph.h"
#include "FileReader.h"
#include "List.h"

using namespace std;

void printMenu() {
    cout << "===== OPTION MENU =====" << endl;
    cout << "1. Read file" << endl;
    cout << "2. Add node" << endl;
    cout << "3. Remove node" << endl;
    cout << "4. Add branch/follow" << endl;
    cout << "5. Remove branch/unfollow" << endl;
    cout << "6. Print graph" << endl;
    cout << "7. Delete graph" << endl;
    cout << "8. Like user" << endl;
    cout << "9. Print the largest component of interconnected users" << endl;
    cout << "10. Print the most probable path from one user to another" << endl;
    cout << "11. Print the k-th most popular user" << endl;
    cout << "0. Exit" << endl;
    cout << "=======================" << endl << endl;
}

int main() {
    bool fileOpened = false;
    List<string> nullList;
    Graph graph(0, nullList);

    printMenu();

    while (true) {
        



        string choiceString;
        int choice;
        cout << "Enter your choice: ";
        getline(cin, choiceString);
        try {
            choice = stoi(choiceString);
        } 
        catch(...){
            choice = -1;
        }
        

        switch (choice) {

        case 1: {

            graph.deleteGraph();
            fileOpened = false;

            if (!fileOpened) {
                string fileName;
                cout << "Enter file name: ";
                getline(cin, fileName);

                graph = FileReader::readFile(fileName);
                if (graph.isEmpty()) {
                    cout << "Error - error processing file." << endl;
                    continue;
                }
                else {
                    fileOpened = true;
                }
            }
            break;
        }
            
        case 2: {
            string nodeName;
            cout << "Enter node name: ";
            getline(cin, nodeName);
            graph.addNode(nodeName);
            break;
        }
        case 3: {

            string nodeName;
            cout << "Enter node name: ";
            getline(cin, nodeName);
            graph.removeNode(nodeName);
            break;
        }
        case 4: {
            string nodeName1, nodeName2;
            float weight;
            cout << "Enter first node name: ";
            getline(cin, nodeName1);
            cout << "Enter second node name: ";
            getline(cin, nodeName2);
            cout << "Enter weight: ";
            cin >> weight;
            cin.ignore();
            graph.setWeight(nodeName1, nodeName2, weight);
            break;
        }
        case 5: {
            string nodeName1, nodeName2;
            cout << "Enter first node name: ";
            getline(cin, nodeName1);
            cout << "Enter second node name: ";
            getline(cin, nodeName2);
            graph.setWeight(nodeName1, nodeName2, 0);
            break;
        }
        case 6: {
            if (graph.getNumOfNodes() < 1) {
                cout << "There are no users on this network. (Graph is empty)" << endl;
            }
            else {
                cout << endl;
                graph.print();
                cout << "Nodes: (the order corresponds to the position of the row/column in the matrix)" << endl;
                graph.printNodeNames();
                cout << endl;
            }
            break;
        }
        case 7: {
            graph.deleteGraph();
            fileOpened = false;
            break;
        }
        case 8: {
            string nodeName1, nodeName2;
            cout << "Enter first node name: ";
            getline(cin, nodeName1);
            cout << "Enter second node name: ";
            getline(cin, nodeName2);
            graph.like(nodeName1, nodeName2);
            break;
        }
        case 9: {
            List<string> LargestComponent = graph.findLargestComponent();
            if (LargestComponent.getNumOfElem() < 2) {
                cout << "Error - no components found." << endl;
                break;
            }
            cout << "Largest component is: ";
            LargestComponent.print();
            cout << endl;
            break;
        }
        case 10: {
            string nodeName1, nodeName2;
            cout << "Enter first node name: ";
            getline(cin, nodeName1);
            cout << "Enter second node name: ";
            getline(cin, nodeName2);
            cout << endl;
            List<string> MLP;
            MLP = graph.findMLP(nodeName1, nodeName2);
            //nisu povezani
            if (MLP.getNumOfElem() == 0) {
                cout << "No connection found between given usernames." << endl;
                break;
            }

            cout << "Most probable path is: " << endl;
            for (int i = MLP.getNumOfElem()-1; i >= 0; i--) {
                cout << MLP.getElem(i);
                if (i > 0) {
                    cout << " - (" << graph.getWeight(MLP.getElem(i), MLP.getElem(i - 1)) << ") -> ";
                }
            }
  
           
            cout << endl;
            break;
        }
        case 11: {
            string kString;
            int k;
            cout << "Enter k: ";

            getline(cin, kString);
            try {
                k = stoi(kString);
            }
            catch (...) {
                cout << "Error - k must be an integer." << endl;
                break;
            }

            if (k > graph.getNumOfNodes() or k < 1) {
                cout << "Error - k is out of range." << endl;
                break;
            }

            cout << "The " << k << ". most popular user on the network is: " << graph.findMostPopularUser(k) << endl;
            break;
        }
        case 0: {
            cout << "Exiting..." << endl;
            return 0;
        }
        default: {
            cout << "Error - Invalid choice." << endl;
            break;
        }
        }
    }

    return 0;
}
