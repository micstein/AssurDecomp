#include<iostream>
#include <list>
#include <stack>
#define NIL -1
using namespace std;

class Graph
{
    //number of verticies
    int numVert;
    //number of pinned verticies
    int pinned;
    list<int> *adj;

    // A Recursive DFS based function used by Assur()
    void FindSCC(int nextVert, int disc[], int low[], stack<int> *graphStack, bool stackMember[]);

public:
    Graph(int numVert, int pinned);
    void addEdge(int from, int to);
    void Assur();
};

Graph::Graph(int numVert, int pinned)
{
    this->numVert = numVert;
    adj = new list<int>[numVert];
    this->pinned = pinned;
}

//add edge to graph
void Graph::addEdge(int from, int to)
{
    adj[from].push_back(to);
}

// finds and prints strongly connected components using DFS traversal
//u = next vertex, disc = discovery times of verticies, low = earliest visited
//graphStack = stack, stackmember = check if node is member of a stack
void Graph::FindSCC(int nextVert, int disc[], int low[], stack<int> *graphStack, bool stackMember[])
{
    static int time = 0;

    // Initialize
    disc[nextVert] = low[nextVert] = ++time;
    graphStack->push(nextVert);
    stackMember[nextVert] = true;

    // traverse adjacent vertices
    list<int>::iterator i;
    for (i = adj[nextVert].begin(); i != adj[nextVert].end(); ++i)
    {
        //current adjacent
        int v = *i;

        // recursion if current adjacent hasnt been visited
        if (disc[v] == -1)
        {
            FindSCC(v, disc, low, graphStack, stackMember);
            // Tarjan Case 1
            low[nextVert] = min(low[nextVert], low[v]);
        }

            // Tarjan Case 2
        else if (stackMember[v] == true)
            low[nextVert] = min(low[nextVert], low[v]);
    }

    // print
    int vert = 0;
    int assur = 0;
    if (low[nextVert] == disc[nextVert])
    {
        while (graphStack->top() != nextVert)
        {
            vert = (int) graphStack->top();
            if (vert < pinned){
                assur = 1;
            }
            cout << vert << " ";
            stackMember[vert] = false;
            graphStack->pop();
        }
        vert = (int) graphStack->top();
        cout << vert;
        if (assur == 1) {
            cout << " <-- Assur Graph" << "\n";
            assur = 0;
        } else {
            cout << " <-- Separated Isostatic Graph\n";
        }

        stackMember[vert] = false;
        graphStack->pop();
    }
}

// Assur Algorithm
void Graph::Assur()
{
    int *disc = new int[numVert];
    int *low = new int[numVert];
    bool *stackMember = new bool[numVert];
    stack<int> *graphStack = new stack<int>();

    // Initialize arrays
    for (int i = 0; i < numVert; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }

    // Call the recursive  function to find strongly connected components
    for (int i = 0; i < numVert; i++) {
        if (disc[i] == NIL) {
            FindSCC(i, disc, low, graphStack, stackMember);
        }
    }
}

int main()
{
    int numPinned;
    int numVerticies;
    int checker = 0;
    int counter = 0;

    std::cout << "How many pinned vertices are there?" << std::endl;
    cin >> numPinned;
    std::cout << "How many other vertices are there?" << std::endl;
    cin >> numVerticies;
    if ((numPinned<0)||(numVerticies<0)) {
        cout << "Input out of bounds\n";
        return 0;
    }
    int totalVert = numPinned + numVerticies;
    Graph g1(totalVert, numPinned);
    cout << "\n";

//    for (int i = 0; i < totalVert; i++) {
//        for (int j = 0; j < totalVert; j++) {
//               if ((i == j) || (i < numPinned)) {
//                   continue;
//               }
//               if (j == 0) {
//                   counter = 0;
//               }
//               cout << "Does vertex " << i << " have an edge in the direction of  vertex " << j
//                    << "? (enter 1 for yes, 0 for no)" << "\n";
//               cin >> checker;
//               if ((checker < 0) || (checker > 1)){
//                   cout << "Invalid Answer\n";
//                   j--;
//               }
//               if (checker == 1) {
//                   g1.addEdge(i, j);
//                   if (j < numPinned) {
//                       g1.addEdge(j, i);
//                   }
//                   checker = 0;
//               }
//           }
//       }

    //EX 1 separating two strongly cluster components, keeping the pinned verts with the correct group
    //0 and 1 are pinned
/*    g1.addEdge(3, 0);g1.addEdge(0, 3);
    g1.addEdge(2, 1);g1.addEdge(1, 2);
    g1.addEdge(2, 4);
    g1.addEdge(3, 2);
    g1.addEdge(4, 3);g1.addEdge(4, 5);

    g1.addEdge(5, 7);g1.addEdge(6, 5);g1.addEdge(6, 3);g1.addEdge(6, 4);
    g1.addEdge(7, 6);
*/

    //EX 2 when pinned vertexes get separated
/*    g1.addEdge(3, 0);g1.addEdge(3, 1);g1.addEdge(0, 3);g1.addEdge(1, 3);
    g1.addEdge(4, 3);g1.addEdge(4, 2);g1.addEdge(2, 4);
*/

    //EX 3 Large Example
/*    g1.addEdge(3, 0);g1.addEdge(0, 3);
    g1.addEdge(2, 1);g1.addEdge(1, 2);
    g1.addEdge(2, 4);g1.addEdge(2, 5);
    g1.addEdge(3, 2);g1.addEdge(4, 1);g1.addEdge(1, 4);
    g1.addEdge(4, 3);g1.addEdge(5, 4);

    //Non assur SCC
    g1.addEdge(6, 3);g1.addEdge(6, 9);g1.addEdge(9, 2);
    g1.addEdge(7, 6);g1.addEdge(9, 7);

    //Loners
    g1.addEdge(8, 7);g1.addEdge(10, 9);
*/

    //Excavator Example
    g1.addEdge(2, 1);g1.addEdge(2, 0);g1.addEdge(2, 3);
    g1.addEdge(1, 2);g1.addEdge(0, 2);
    g1.addEdge(6, 1);g1.addEdge(1, 6);
    g1.addEdge(3, 6);g1.addEdge(6, 2);
    g1.addEdge(4, 6);g1.addEdge(4, 3);
    g1.addEdge(5, 4);g1.addEdge(5, 6);

    g1.Assur();

    return 0;
}

