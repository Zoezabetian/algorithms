# BFS Algorithm in C
## Description

This C program uses a BFS algorithm to explore all vertices of a graph in breadth-first order. It starts from a source vertex and explores all its neighboring vertices before moving on to the neighbors' neighbors. BFS is useful for finding the shortest path in an unweighted graph, determining the distance between nodes, and exploring nodes level by level. This implementation uses a queue to manage the exploration order and ensures that each vertex is processed in the correct sequence.

## Files Included

- `List.h`: Header file with declarations for the List ADT.
- `List.c`: Source file that implements the List ADT functions declared in `List.h`.
- `Graph.h`: Header file with declarations for the Graph ADT.
- `Graph.c`: Source file that implements the Graph ADT functions declared in `Graph.h`.
- `shortestPath.c`: Main application file that uses the Graph ADT for generating adjacency lists and finding shortest paths between vertices.
- `Makefile`: A makefile with instructions for compiling the project.

## Build and Run Instructions

**To Build:**  
Run the command: `make`

**To Run:**  
Execute the program: `./shortestPath <input file> <output file>`

