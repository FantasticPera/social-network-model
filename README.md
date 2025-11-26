Operations:

1. Loading a set of users and the relationships between them from a text file of a given format and forming a graph.
2. Adding a node to the graph and removing a node from the graph.
3. Adding and removing an edge between two nodes in the graph.
4. Printing the graph representation.
5. Deleting the graph from memory.
6. Performing a “like” action on a user’s post by another user, where one user indicates that they like another user’s post.
7. Finding the largest component in the graph, representing a subset of users who are all mutually connected.
8. Printing all users on the most probable path from one given user to another given user.
9. Efficiently determining the k-th person with the greatest influence on the social network.
______________________________________________________________________________________________

Graph representation:

The Matrix class, as the name suggests, represents a matrix. I implemented the matrix so that each element is represented as a NodeMatrix, which has pointers to the right (right) and down (down). The first column connects all the rows via the down pointer, and the columns are connected via the right pointer. The matrix includes methods setWeight, getWeight, getNumOfNodes, isEmpty, deleteMatrix, and print (which outputs the entire matrix in a neat format). I also added a copy constructor and an assignment operator for easier handling within the project later.

The Graph class inherits from the Matrix class and additionally contains a private member nodeNames, which is a list of the names of the nodes in the graph. This class implements all the methods required by this assignment, as well as some additional helper methods. In the following text, I will describe and explain the functionality of all the new methods in this class, following the order of the assignment requirements.
______________________________________________________________________________________________

Operations description:

1. Loading a set of users and the relationships between them from a text file

The FileReader class, specifically its readFile method, reads a file whose name is entered by the user in the console. It constructs a graph based on the data provided in the file and validates the data, returning an error if the data is invalid. FileReader first reads the first line of the file, which contains a number representing the number of nodes in the graph. Then it reads the second line, which contains a number representing the number of edges in the graph; this number must not exceed n*(n-1), where n is the number of nodes. Next, it reads the third line, which contains the names of the nodes and passes them to the Graph object. Finally, it reads all remaining lines in the file (according to the number of edges) and records the connections between nodes in the graph.
-----------------------------------------------------------------------------------------------
2. Adding and removing nodes in the graph

The method void Graph::addNode(string nodeName) adds a node to the graph by adding a new row and column to the matrix, adding the name to the nodeNames list, and incrementing the number of nodes n by 1. It also handles the cases when the graph was empty or had only one element.

The method void Graph::removeNode(string nodeName) deletes a row and column in the matrix corresponding to the index of nodeName. If the first element is removed, the head of the matrix becomes the next element along the diagonal (down then right), the column is relinked, and the first row and column are deleted. If the last element in the list is removed, the last row and column are simply deleted. For all other cases, elements are relinked and the specified row and column are removed. I encountered an issue when the graph contained only two nodes and I wanted to delete the first one, so I had to handle this case separately in an if statement.
-----------------------------------------------------------------------------------------------
3. Adding and removing edges between two nodes

For both adding and removing an edge, the method void Graph::setWeight(string node1, string node2) is used. It retrieves the positions of node1 and node2 from the nodeNames list and iterates through the matrix until it finds the corresponding indices. If the value is greater than 1, it sets it to 1; if it is less than 0, it sets it to 0—this is not considered an error. If node1 or node2 does not exist, the method getIndex detects this and the operation is aborted.

The difference between adding and removing an edge is that when adding, the user is prompted for the weight of the connection, whereas when removing, the weight is simply set to 0. A user cannot follow/unfollow themselves.
-----------------------------------------------------------------------------------------------
4. Printing the graph representation

The method void Graph::print() is called here, which works the same way as in the Matrix class. It also prints the nodeNames list.
-----------------------------------------------------------------------------------------------
5. Deleting the graph from memory

The method void Graph::deleteGraph() is called here. It simply calls void Matrix::deleteMatrix(), which iterates through the matrix and deletes each NodeMatrix, sets the number of nodes n to 0, and clears the nodeNames list.
-----------------------------------------------------------------------------------------------
6. “Liking” a user’s post

The method void Graph::like(string node1, string node2) works intuitively. It takes the current value of the edge and increments it by 0.1. If the value exceeds 1, the setWeight method prevents it from going higher. A user cannot “like” themselves.
-----------------------------------------------------------------------------------------------
7. Finding the largest component of mutually connected users

To solve this, the following methods are used:

List<std::string> DFS(std::string nodeName)

List<int> findEndTimes()

List<std::string> findLargestComponent()

void transpose()

The DFS method returns a list containing the order in which nodes are visited during depth-first traversal. It uses helper structures such as a stack and a boolean vector visited. Nodes are added to the stack, and while the stack is not empty, unvisited neighbors of the popped node are added and its visited status is set to true. Each visited node is added to the returned list.

The findEndTimes method returns a list of finishing times for all nodes in the graph. While graphCopy is not empty, DFS is performed to ensure a complete traversal. Then, DFS is performed starting from the first element in the DFS list, this time with a time counter. When a node is successfully added in DFS (i.e., it has an unvisited neighbor), it is pushed onto stackDFS. If a node has no further neighbors, nodes are popped from stackDFS until empty, finishing times are recorded, and processed nodes are removed from graphCopy.

The transpose method transposes the graph by swapping [i,j] with [j,i] in the matrix.

The findLargestComponent method returns a list of the largest mutually connected component. It uses the list of end times and the transposed graph (similar to the CONN-COMP algorithm from the book). First, it selects the largest value from the end times list and performs DFS starting from that index. If this DFS list is larger than the previous largest, it is saved. Processed nodes are removed from the transposed graph, and their finishing times are set to -1 to prevent reprocessing. When all nodes have been traversed and the transposed graph is empty, the final list of nodes is returned.
-----------------------------------------------------------------------------------------------
8. Printing all users on the most likely path between two given users

The method List<string> findMLP(string node1, string node2) (MLP = Most Likely Path) is used here. It is based on Dijkstra’s algorithm, but instead of summing path weights, the weights are multiplied, and the goal is to maximize the value rather than minimize it.

The pathWeights vector stores the weights of neighboring nodes from the starting node (indexNode1). If a node is not connected, its value is 0. The pathInstructions vector stores the predecessor of each node for path reconstruction. Unconnected nodes have a value of -1.

After running the modified Dijkstra algorithm, the path is reconstructed by starting from indexNode2 and following the predecessors in pathInstructions until indexNode1 is reached. This produces a list in reverse order, which is acceptable.
-----------------------------------------------------------------------------------------------
9. Efficiently determining the k-th most influential user

Before explaining the method string findMostPopularUser(int k), I considered who should be the most influential user. The number of followers is the most important factor, as it directly impacts influence. Another factor is the “strength of following,” i.e., the probability that a post reaches a follower’s feed. A user with many followers but very low reach (e.g., 0.01) cannot be considered influential.

The formula I devised is: Influence = TotalRawValue(node) * numberOfFollowers / (totalUsers - 1)

Where numberOfFollowers represents users who can receive the posts, and TotalRawValue is the sum of all probabilities that a post reaches the user’s followers (including indirect followers).

The findMostPopularUser method calculates the influence of all users, stores it in a list PopularityRates, finds the k-th largest value, and returns the corresponding user’s name.
______________________________________________________________________________________________




