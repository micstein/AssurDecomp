#include<iostream>
#include <list>
#include <stack>
#include <string>
#define NIL -1
using namespace std;

int center = 0;
int ycenter = 0;
bool xsym = false;
bool ysym = false;
//Ex 1: Symmetric along x, center at x = 4
int vertLoc[10][2] = {{1,0}, {7,0}, {1,2}, {3,3}, {1,5}, {7,2}, {5,3}, {7,5}, {3,6}, {5,6}};
//Ex 2 Y symmetry along y = 3
//int vertLoc[10][2] = {{0,0}, {0,6}, {2,2}, {4,2}, {3,0}, {2,4}, {4,4}, {3,6}, {5,6}, {5,0}};
//Ex 3 X and Y Sym
//int vertLoc[14][2] = {{1,0}, {7,0}, {1,6}, {7,6}, {0,2}, {0,4}, {3,3}, {5,3}, {8,2}, {8,4}, {2,1}, {2,5}, {6,5}, {6,1}};

int numPinned;
int numVerticies;
int totalVert;

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
//graphStack = stack, stackmember = check if node in a stack
void Graph::FindSCC(int nextVert, int disc[], int low[], stack<int> *graphStack, bool stackMember[])
{
    // Initialize
    static int time = 0;
    disc[nextVert] = low[nextVert] = ++time;
    graphStack->push(nextVert);
    stackMember[nextVert] = true;

    // traverse adjacent vertices
    list<int>::iterator i;
    for (i = adj[nextVert].begin(); i != adj[nextVert].end(); ++i)
    {
        //current adjacent
        int v = *i;

        //no need to decompose both ways
        if (xsym && ysym) {
            ysym = false;
        }

        //Essence of Sym-Adapted Assur. Only necessary to do half the decomp and then reflect it across center
        if (xsym) {
             if ((vertLoc[nextVert][0]) > center) {
                 continue;
             }
        } else if (ysym) {
            if ((vertLoc[nextVert][1]) > ycenter) {
                continue;
            }
        }

        // recursion if current adjacent hasnt been visited
        if (disc[v] == -1)
        {
            FindSCC(v, disc, low, graphStack, stackMember);
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
    int stackCount = 0;
    int checker[4] = {0,0,0,0};
    if (low[nextVert] == disc[nextVert])
    {
        while (graphStack->top() != nextVert)
        {
            w = (int) graphStack->top();
            if ((w < numPinned) && (xsym)){
                //case 0: x reflected assur
                if (center < vertLoc[w][0])
                    checker[0] = 1;
                //case 1: x sym assur on left side of reflection
                if (center > vertLoc[w][0])
                    checker[1] = 1;
            }
            if ((w < numPinned) && (ysym)){
                //case 2: y sym assur above reflection
                if (center < vertLoc[w][1])
                    checker[2] = 1;
                //case 3: y sym assur below reflection
                if (center > vertLoc[w][1])
                    checker[3] = 1;
            }
            cout << w << " ";
            stackMember[w] = false;
            graphStack->pop();
            stackCount++;
        }
        w = (int) graphStack->top();

        if (xsym) {
            if ((vertLoc[w][0]) < center) {
                cout << w;
            }
        } else if (ysym) {
            if ((vertLoc[w][1]) < ycenter) {
                cout << w;
            }
        }
        //Label the decompositions
        if (((w<numPinned) && (center > vertLoc[w][0]) && (xsym)) || checker[1] ){
                    cout << " <-- Assur Decomp of left side with an equivalent graph reflected across X = " << center << "\n";
        }
        if (((w<numPinned) && (center > vertLoc[w][1]) && (ysym)) || checker[3] ){
            cout << " <-- Assur Decomp of bottom with an equivalent graph reflected across Y = " << ycenter << "\n";
        }
        if ((stackCount < 2) && (vertLoc[w][0] < center) && xsym){
            cout << " <-- Isostatic graph beneath X = " << center << " with an equivalent graph across it\n";
        }
        if ((stackCount < 2) && (vertLoc[w][1] < ycenter) && ysym){
            cout << " <-- Isostatic graph beneath Y = " << ycenter << " with an equivalent graph across it\n";
        }

        stackCount = 0;


        stackMember[w] = false;
        graphStack->pop();
    }
}

// Assur Decomp
void Graph::Assur()
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


bool isXSymmetric(int total, int coords[][2]) {

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

bool isYSymmetric(int total, int coords[][2]) {

    int hitCounter = 0;
    for (int i = 0; i < total; i++) {
        //check the vertexes are symmetrical
        for (int j = 0; j < total; j++) {
            if (i == j) {
                continue;
            }
            //if two vertexs are on the same level
            if (coords[i][0] == coords[j][0]) {
                hitCounter++;
                if (ycenter == 0) {
                    //determine rightmost point to make sure center is positive
                    if (coords[j][1] > coords[i][1]) {
                        //center = difference of the two plus leftmost x coord
                        ycenter = ((coords[j][1] - coords[i][1]) / 2) + coords[i][1];
                        cout << "Y center: " << ycenter << "\n";
                    }
                    if (coords[i][1] > coords[j][1]) {
                        //center = difference of the two plus leftmost x coord
                        center = ((coords[i][1] - coords[j][1]) / 2) + coords[j][1];
                        cout << "Y center: " << ycenter << "\n";
                    }
                }
                if ((coords[j][1] - ycenter) != (ycenter - coords[i][1])) {
                    return false;
                }
            }
            //if there are no other vertex on the level and center is 0, center is the vert loc
            //if there are no other vertex on the level and center isnt 0, check that the vert is on center and if not return false
            if (j == total - 1) {
                if (ycenter == 0) {
                    ycenter == coords[i][0];
                }
                if ((hitCounter == 0) && (ycenter != coords[i][0])) {
                    return false;
                }
            }
        }
    }
    return true;
}

void printXReflection() {
    string reflection = "";
    string left = "";
    for (int i = 0; i < totalVert; i++){
        if (vertLoc[i][0] < center){
            left += to_string(i);
            left += " ";
        }
        else{
            reflection += to_string(i);
            reflection += " ";
        }
    }
    cout << left << " <-- Left side of graph\n";
    cout << reflection << " <-- Reflection\n\n";
}

void printYReflection() {
    string reflection = "";
    string bottom = "";
    for (int i = 0; i < totalVert; i++){
        if (vertLoc[i][1] < ycenter){
            bottom += to_string(i);
            bottom += " ";
        }
        else{
            reflection += to_string(i);
            reflection += " ";
        }
    }
    cout << bottom << " <-- Bottom of graph\n";
    cout << reflection << " <-- Reflection across " << ycenter << "\n\n";
}

int main()
{
    int checker = 0;
    int counter= 0;

    std::cout << "How many pinned vertices are there?" << std::endl;
    cin >> numPinned;
    std::cout << "How many other vertices are there?" << std::endl;
    cin >> numVerticies;
    if ((numPinned<0)||(numVerticies<0)) {
        cout << "Input out of bounds\n";
        return 0;
    }
    totalVert = numPinned + numVerticies;
    cout << "\n";
    Graph g1(totalVert, numPinned);

//    for (int i = 0; i < totalVert; i++){
//        cout << "Enter the x coordinate of vertex " << i << "\n";
//        cin >> vertLoc[i][0];
//        cout << "Enter the y coordinate of vertex " << i << "\n";
//        cin >> vertLoc[i][1];
//    }
//    for (int i = 0; i < totalVert; i++) {
//        for (int j = 0; j < totalVert; j++) {
//        if (i == j){
//            continue;
//        }
//        if (j == 0){
//            counter = 0;
//        }
//        cout << "Does vertex " << i << " have an edge in the direction of  vertex " << j << "? (enter 1 for yes, 0 for no)"<< "\n";
//        cin >> checker;
//        if ((checker < 0) || (checker > 1)){
//             cout << "Invalid Answer\n";
//             j--;
//        }
//        if(checker == 1){
//            g1.addEdge(i, j);
//            if (j < numPinned) {
//                 g1.addEdge(j, i);
//            }
//            checker = 0;
//            }
//        }
//    }

    xsym = isXSymmetric(totalVert, vertLoc);
    cout << "\n\n Is it symmetric across a x axis? " << xsym << "\n";
    if (xsym){
        printXReflection();
    }
    ysym = isYSymmetric(totalVert, vertLoc);
    cout << "\n\n Is it symmetric across a y axis? " << ysym << "\n\n";
    if (ysym){
        printYReflection();
    }

    //EX 1 X symmetry
    g1.addEdge(2, 0);g1.addEdge(0, 2);g1.addEdge(2, 3);
    g1.addEdge(3, 4);g1.addEdge(4, 2);

    g1.addEdge(5, 1);g1.addEdge(1, 5);g1.addEdge(5, 6);
    g1.addEdge(6, 7);g1.addEdge(7, 5);

    g1.addEdge(8, 3);g1.addEdge(8, 9);
    g1.addEdge(9, 6);g1.addEdge(9, 8);

    //EX 2 Y symmetry
//    g1.addEdge(2, 0);g1.addEdge(0, 2);
//    g1.addEdge(2, 3);g1.addEdge(3, 4);g1.addEdge(4, 2);
//
//    g1.addEdge(5, 1);g1.addEdge(1, 5);
//    g1.addEdge(6, 7);g1.addEdge(7, 5);g1.addEdge(5, 6);
//
//    g1.addEdge(8, 6);g1.addEdge(8, 7);
//    g1.addEdge(9, 3);g1.addEdge(9, 4);

    //EX 3
//    g1.addEdge(4, 0);g1.addEdge(0, 4);
//    g1.addEdge(5, 2);g1.addEdge(2, 5);
//    g1.addEdge(9, 3);g1.addEdge(3, 9);
//    g1.addEdge(8, 1);g1.addEdge(8, 10);
//
//    g1.addEdge(4, 6);g1.addEdge(5, 4);g1.addEdge(6, 5);
//    g1.addEdge(7, 9);g1.addEdge(9, 8);g1.addEdge(8, 7);
//
//    g1.addEdge(12, 7);g1.addEdge(13, 7); g1.addEdge(10, 6);g1.addEdge(11, 6);


    g1.Assur();

    return 0;
}
