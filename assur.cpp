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

    // A Recursive DFS based function used by Tarjan()
    void FindSCC(int nextVert, int disc[], int low[], stack<int> *st, bool stackMember[]);

public:
    Graph(int numVert, int pinned);
    void addEdge(int v, int w);
    void Tarjan();
};

Graph::Graph(int numVert, int pinned)
{
    this->numVert = numVert;
    adj = new list<int>[numVert];
    this->pinned = pinned;
}

//add edge to graph
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

// finds and prints strongly connected components using DFS traversal
//u = next vertex, disc = discovery times of verticies, low = earliest visited
//st = connections, stackmember = check if node in a stack
void Graph::FindSCC(int nextVert, int disc[], int low[], stack<int> *st, bool stackMember[])
{
    static int time = 0;

    // Initialize
    disc[nextVert] = low[nextVert] = ++time;
    st->push(nextVert);
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
            FindSCC(v, disc, low, st, stackMember);

            // Tarjan Case 1: Check if  subtree with 'v' has a connection to one of the ancestors of 'u'
            low[nextVert] = min(low[nextVert], low[v]);
        }

            // Tarjan Case 2: Update low value of 'u' only of 'v' is still in stack
        else if (stackMember[v] == true)
            low[nextVert] = min(low[nextVert], low[v]);
    }

    // print
    //temp for printing
    int w = 0;
    int assur = 0;
    if (low[nextVert] == disc[nextVert])
    {
        while (st->top() != nextVert)
        {
            w = (int) st->top();
            if (w < pinned){
                assur = 1;
            }
            cout << w << " ";
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        cout << w;
        if (assur == 1) {
            cout << " <-- Assur Graph" << "\n";
            assur = 0;
        } else {
            cout << " <-- Separated Isostatic Graph\n";
        }

        stackMember[w] = false;
        st->pop();
    }
}

// Tarjans Algorithm
void Graph::Tarjan()
{
    int *disc = new int[numVert];
    int *low = new int[numVert];
    bool *stackMember = new bool[numVert];
    stack<int> *st = new stack<int>();

    // Initialize arrays
    for (int i = 0; i < numVert; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }

    // Call the recursive  function to find strongly connected components
    for (int i = 0; i < numVert; i++)
        if (disc[i] == NIL)
            FindSCC(i, disc, low, st, stackMember);
}

int main()
{
    int numPinned;
    int numVerticies;

    std::cout << "How many pinned vertices are there?" << std::endl;
    cin >> numPinned;
    std::cout << "How many other vertices are there?" << std::endl;
    cin >> numVerticies;

    //{{x coord, y coord, isValid}, {0,2,1}};
//    vector<int> edges[numPinned+numVerticies + 1];
    int checker = 0;
    int counter = 0;
    int totalVert = numPinned + numVerticies;
    //to keep track of all verts the pins point to
    int pinnedLinks [numPinned][numVerticies];
    cout << "\n";
    Graph g1(totalVert, numPinned);

/*       for (int i = 0; i < totalVert; i++) {
           for (int j = 0; j < totalVert; j++) {
               if ((i == j) || (i < numPinned)) {
                   continue;
               }
               if (j == 0) {
                   counter = 0;
               }
               cout << "Does vertex " << i << " have an edge in the direction of  vertex " << j
                    << "? (enter 1 for yes, 0 for no)" << "\n";
               cin >> checker;
               if (checker == 1) {
                   g1.addEdge(i, j);
                   if (j < numPinned) {
                       g1.addEdge(j, i);
                   }
                   checker = 0;
               }
           }
       }*/

   //EX 1 separating two strongly cluster components, keeping the pinned verts with the correct group
   //0 and 1 are pinned
    g1.addEdge(3, 0);g1.addEdge(0, 3);
    g1.addEdge(2, 1);g1.addEdge(1, 2);
    g1.addEdge(2, 4);
    g1.addEdge(3, 2);
    g1.addEdge(4, 3);g1.addEdge(4, 5);

    g1.addEdge(5, 7);g1.addEdge(6, 5);
    g1.addEdge(7, 6);


 //EX 2 when pinned vertexes get separated
 /*   g1.addEdge(3, 0);g1.addEdge(3, 1);g1.addEdge(0, 3);g1.addEdge(1, 3);
    g1.addEdge(4, 3);g1.addEdge(4, 2);g1.addEdge(2, 4);
*/

    g1.Tarjan();

    return 0;
}

