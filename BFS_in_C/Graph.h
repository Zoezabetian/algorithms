#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1
#define UNDEF -2
#define INF INT_MAX

typedef struct VertexObj
{
    List adjacencyList; //  neighbors of vertex i
    int color;          //  color of vertex i
    int parent;         //  parent of vertex i
    int distance;       // the distance from the (most recent) source to vertex i
} VertexObj;

typedef VertexObj *Vertex;

typedef struct GraphObj
{
    Vertex *vertexArray; // array of pointers to VertexObj structures, where each element
                         // in array is a pointer to a VertexObj, representing the
                         // qualities and attributes of a corresponding vertex in the graph

    int numVertices;      // number of vertices in the graph
    int numEdges;         // number of edges in the graph
    int mostRecentSource; // the label of the vertex that was most recently used as source for BFS
} GraphObj;

typedef GraphObj *Graph;

// returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n);

// frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL
void free(Graph *pG);

// returns number of vertices (called the order of the graph)
int getOrder(Graph G);

// the number of edges (called the size of the graph)
int getSize(Graph G);

// returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G);

// will return the parent of vertex u in the BFS tree created by BFS(),
// or NIL if BFS() has not yet been called. precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getParent(Graph G, int u);

// returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called. precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u);

// appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists
// precondition: getSource(G)!=NIL, so BFS() must be called before getPath() is called
// also has precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
void getPath(List L, Graph G, int u);

// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);

// inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v
// to the adjacency List of u. Must maintain these lists in sorted order by increasing labels.
// precondition: two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);

// inserts a new directed edge from u to v, i.e. v is added to
// the adjacency List of u (but not u to the adjacency List of v).
// precondition: two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);

// runs the BFS algorithm on the Graph G with source s, setting
// the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s);

// prints the adjacency list representation of G to the file pointed to by 'out'
void printGraph(FILE *out, Graph G);

