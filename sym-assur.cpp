#include<iostream>
#include <list>
#include <stack>
#define NIL -1
using namespace std;
int center = 0;
int vertLoc[6][2] = {{1,1}, {2,2}, {4,2}, {5,1}, {1,3}, {5,3}};

class Graph
{
    //number of verticies
    int numVert;
    //number of pinned verticies
    int pinned;
    list<int> *adj;

    // A Recursive DFS based function used by Tarjan()
    void FindSCC(int nextVert, int disc[], int low[], stack<int> *st, bool stackMember[], bool sym);

public:
    Graph(int numVert, int pinned);
    void addEdge(int v, int w);
    void Tarjan(bool symmetric);
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
//st = connections, stackmember = check if node in a stack, sym = is the graph symmetrical
void Graph::FindSCC(int nextVert, int disc[], int low[], stack<int> *st, bool stackMember[], bool sym)
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
            FindSCC(v, disc, low, st, stackMember, sym);

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
    int reflection = 0;
    if (low[nextVert] == disc[nextVert])
    {
        while (st->top() != nextVert)
        {
            w = (int) st->top();
            //if its symmetric and the verts are on the right side of the graph, its the reflection
            if (sym && (center < vertLoc[w][0])){
                reflection = 1;
            }
            cout << w << " ";
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        cout << w;
        if (reflection == 1){
            cout << " <-- Reflection across x = " << center << "\n";
            reflection = 0;
        }else
            cout << " <-- Left side of graph\n";

        stackMember[w] = false;
        st->pop();
    }
}

// Tarjans Algorithm
void Graph::Tarjan(bool sym)
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
            FindSCC(i, disc, low, st, stackMember, sym);
}


bool isSymmetric(int total, int coords[][2], int edges[][10]) {

    int hitCounter = 0;
    for (int i = 0; i < total; i++) {
        //check the vertexes are symmetrical
        for (int j = 0; j < total; j++) {
            if (i == j) {
                continue;
            }
            //if two vertexs are on the same level
            if (coords[i][1] == coords[j][1]) {
                hitCounter++;
                if (center == 0) {
                    //determine rightmost point to make sure center is positive
                    if (coords[j][0] > coords[i][0]) {
                        //center = difference of the two plus leftmost x coord
                        center = ((coords[j][0] - coords[i][0]) / 2) + coords[i][0];
                        cout << "center: " << center << "\n";
                    }
                    if (coords[i][0] > coords[j][0]) {
                        //center = difference of the two plus leftmost x coord
                        center = ((coords[i][0] - coords[j][0]) / 2) + coords[j][0];
                        cout << "center: " << center << "\n";
                    }
                }
                if ((coords[j][0] - center) != (center - coords[i][0])) {
                    return false;
                }
                //check edges
                //first edge i has comp to first edge j has
                //if the y coord of their edge is not equal
                if (coords[edges[i][0]][1] != coords[edges[j][0]][1]) {
                    return false;
                }
                //if the larger x coord - center != center - smallest x coord
                if (coords[edges[i][0]][0] > coords[edges[j][0]][0]) {
                    if((coords[edges[i][0]][0]- center) != (center - coords[edges[j][0]][0])) {
                        return false;
                    }
                }
                if (coords[edges[j][0]][0] > coords[edges[i][0]][0]) {
                    if((coords[edges[j][0]][0]- center) != (center - coords[edges[i][0]][0])) {
                        return false;
                    }
                }
            }
            //if there are no other vertex on the level and center is 0, center is the vert loc
            //if there are no other vertex on the level and center isnt 0, check that the vert is on center and if not return false
            if (j == total - 1) {
                if (center == 0) {
                    center == coords[i][1];
                }
                if ((hitCounter == 0) && (center != coords[i][1])) {
                    return false;
                }
            }
        }
    }
    return true;
}
// Driver program to test above function
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
    int counter, edgeCounter = 0;
    int totalVert = numPinned + numVerticies;
    //to keep track of all verts the pins point to
    //int vertLoc[totalVert][2];
    //int vertEdges[totalVert][10];

    cout << "\n";
    Graph g1(totalVert, numPinned);

    /*      for (int i = 0; i < totalVert; i++){
              cout << "Enter the x coordinate of vertex " << i << "\n";
              cin >> vertLoc[i][0];
              cout << "Enter the y coordinate of vertex " << i << "\n";
              cin >> vertLoc[i][1];
          }*/
    /*       for (int i = 0; i < totalVert; i++) {
               edgeCounter = 0;
              for (int j = 0; j < totalVert; j++) {
                  if (i == j){
                      continue;
                  }
                  if (j == 0){
                      counter = 0;
                  }
                  cout << "Does vertex " << i << " have an edge in the direction of  vertex " << j << "? (enter 1 for yes, 0 for no)"<< "\n";
                  cin >> checker;
                  if(checker == 1){
                          g1.addEdge(i, j);
                          vertEdges[i][edgeCounter] = j;
                          edgeCounter++;
                          if (j < numPinned) {
                              g1.addEdge(j, i);
                          }
                      checker = 0;
                  }
              }
          }*/
    int vertLoc[6][2] = {{1,1}, {2,2}, {4,2}, {5,1}, {1,3}, {5,3}};
    int vertEdges[6][10] = {{1}, {4}, {5}, {2}, {0}, {3}};
    cout << "Vertex 1 x coord: " << vertLoc[1][0] << " Y coord: " << vertLoc[1][1] << "\n";

    bool test = false;
    test = isSymmetric(totalVert, vertLoc, vertEdges);
    cout << "\n\n Is symmetric? " << test << "\n\n";

    g1.addEdge(0, 1);g1.addEdge(1, 4);g1.addEdge(4, 0);
    g1.addEdge(3, 2);g1.addEdge(2, 5);g1.addEdge(5, 3);

/* EX 1 separating two strongly cluster components, keeping the pinned verts with the correct group
    g1.addEdge(3, 0);g1.addEdge(0, 3);
    g1.addEdge(2, 1);g1.addEdge(1, 2);
    g1.addEdge(2, 4);
    g1.addEdge(3, 2);
    g1.addEdge(4, 3);g1.addEdge(4, 5);

    g1.addEdge(5, 7);g1.addEdge(6, 5);
    g1.addEdge(7, 6);*/


/* EX 2 when pinned vertexes get separated
    g1.addEdge(3, 0);g1.addEdge(3, 1);g1.addEdge(0, 3);g1.addEdge(1, 3);
    g1.addEdge(4, 3);g1.addEdge(4, 2);g1.addEdge(2, 4);
*/

    g1.Tarjan(test);

    return 0;
}