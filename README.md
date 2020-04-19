# AssurDecomp
Assur Decomposition and Symmetry-adapted Assur Decomposition

INPUT
In both assur.cpp and sym-assur.cpp there is an option to input your own graph or to use example graphs already inputted that just 
need to be commented out. Inputting all the information can be tedious. 
These examples intend to showcase the different conditions the program passes.


assur.cpp 

Ex 1. Vertex 0 and 1 are pinned verticies. They are connected to a SCC made up of 2-4. Vert 5-7 are SCC but not SCC to the other verts.

Ex 2. Vertex 0, 1, 2 pinned. Separates the assur graph from another graph with a pinned vertex

Ex 3. Pinned vert: 0, 1. Large example showing separation of SCCs and multiple extraneous points

Ex 4. Real life example: Excavator


sym-assur.cpp
note: for this file you have to uncomment out the vertLoc array at the top as well as the addedge calls in main

Ex 1. X Symmytrical graph, Three SCCs. Reflected and separated

Ex 2. Y Symmytrical graph, Two SCCs. Reflected and separated

Ex 3. X and Y symmetrical. 
