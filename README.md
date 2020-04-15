# AssurDecomp
Assur Decomposition and Symmetry-adapted Assur Decomposition

INPUT
In both assur.cpp and sym-assur.cpp there is an option to input your own graph or to use example graphs already inputted that just 
need to be commented out. Inputting all the information can be tedious. 
These examples intend to showcase the different conditions the program passes.


assur.cpp

Ex 1. Vertex 0 and 1 are pinned verticies. They are connected to a SCC made up of 2-4. Vert 5-7 are SCC but not SCC to the other verts.

Todo: example of separating pinned verts, ex of a larger graph with more separations


sym-assur.cpp
note: for this file you have to uncomment out the vertLoc array at the top as well as the addedge calls in main

Ex 1. Ideal scenario. Symmytrical graph, Two SCCs, one the reflection of the other

Ex 2. Symmytrical graph, Two SCCs with an additional not strongly connnected vert

todo: a non symmetric example, example with vertexes with multiple edges
