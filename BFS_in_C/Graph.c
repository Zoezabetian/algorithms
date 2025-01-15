#include "Graph.h"

/*** Constructors-Destructors ***/

Vertex newVertex() {
  Vertex V = malloc(sizeof(VertexObj));
  if (V == NULL) {
    fprintf(stderr, "Error: Unable to allocate memory for Vertex.\n");
    return NULL;
  }

  V->adjacencyList = newList();
  V->color = WHITE;  // white color means undiscovered
  V->parent = NIL;    // indicates no parent
  V->distance = INF;  // infinity distance
  return V;
}

void setVertexQualities(Vertex V, int color, int parent, int distance) {
  V->color = color;
  V->parent = parent;
  V->distance = distance;
}

void resetGraphVertices(Graph G) {  // added this for BFS usage
  if (G == NULL) {
    fprintf(stderr, "Error: calling resetGraphVertices() on NULL Graph\n");
    return;
  }

  for (int i = 1; i <= getOrder(G); i++) {
    setVertexQualities(G->vertexArray[i], WHITE, NIL, INF);
  }
}

// returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges
Graph newGraph(int n) {
  Graph G = malloc(sizeof(GraphObj));
  if (G == NULL) {
    fprintf(stderr, "Error: Unable to allocate memory for Graph.\n");
    return NULL;
  }

  G->numVertices = n;
  G->numEdges = 0;
  G->mostRecentSource = NIL;

  // malloc array
  G->vertexArray =
      malloc((n + 1) * sizeof(VertexObj));  // allocate memory for arrays
                                            // *** n+1 for 1-based findIndexing

  // initialize arrays
  for (int i = 1; i <= n; i++)  {
    Vertex vertex = newVertex();
    G->vertexArray[i] = vertex;
  }
  // printf("function newGraph completed");
  // fflush(stdout);
  return G;
}

// frees all heap memory associated with the Graph *pG, then sets the handle *pG
// to NULL
void free(Graph* pG) {
  if (pG != NULL && *pG != NULL) {
    // Free the memory allocated for each vertex
    for (int i = 1; i <= getOrder(*pG); i++) {
      Vertex V = ((*pG)->vertexArray[i]);
      if (V->adjacencyList != NULL) {
        freeList(&(V->adjacencyList)); // free adjacency list for each vertex
      }
      free(V); // free rest of VertexObj struct
    }
    free((*pG)->vertexArray); // free vertexArray in graphObj

    free(*pG);  // free rest of graph components
    *pG = NULL; //set graph pointer to null
  }
}

/*** Access functions ***/

// returns number of vertices (called the order of the graph)
int getOrder(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error: calling getOrder() on NULL Graph\n");
    return 0;  // what should this return? NIL?
  }
  // printf("function getOrder completed");
  // fflush(stdout);

  return G->numVertices;
}

// the number of edges (called the size of the graph)
int getSize(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error: calling getSize() on NULL Graph\n");
    return 0;  // what should this return? NIL?
  }
  // printf("function getSize completed");
  // fflush(stdout);
  return G->numEdges;
}

// returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called
int getSource(Graph G) {
  // printf("getSource starting");
  // fflush(stdout);

  if (G == NULL) {
    fprintf(stderr, "Error: calling getSource() on NULL Graph\n");
    return NIL;
  }
  if (G->mostRecentSource != NIL) {
    return G->mostRecentSource;
  } else {
    return NIL;
  }
}
// will return the parent of vertex u in the BFS tree created by BFS(),
// or NIL if BFS() has not yet been called. precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getParent(Graph G, int u) {
  // printf("function getParent started");
  // fflush(stdout);
  if (G == NULL) {
    fprintf(stderr, "Error: calling getParent() on NULL Graph\n");
    return NIL;
  }
  int order = getOrder(G);  // for precondition
  if (u < 1 || u > order) {
    fprintf(stderr, "Vertex %d is out of valid range\n", u);
    return NIL;
  }
  if (G->mostRecentSource == NIL) {
    // BFS has not been called yet
    return NIL;
  }
  return G->vertexArray[u]->parent;
}

// returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called. precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u) {
  // printf("function getDist started");
  // fflush(stdout);
  if (G == NULL) {
    fprintf(stderr, "Error: calling getDist() on NULL Graph\n");
    return NIL;
  }
  int order = getOrder(G);  // for precondition
  if (u < 1 || u > order) {
    fprintf(stderr, "Vertex %d is out of valid range\n", u);
    return NIL;
  }
  if (G->mostRecentSource == NIL) {
    // BFS has not been called yet
    return INF;
  }
  return G->vertexArray[u]->distance;
}

/*** Manipulation procedures ***/

// appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists
// precondition: getSource(G)!=NIL, so BFS() must be called before getPath() is
// called also has precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)

void getPath(List L, Graph G, int u) {
  // printf("function getPath started\n");
  // fflush(stdout);

  if (G == NULL || L == NULL) {
    fprintf(stderr, "Error: calling getPath() on NULL Graph or List\n");
    return;
  }

  int order = getOrder(G);
  if (u < 1 || u > order) {
    fprintf(stderr, "Vertex %d is out of valid range\n", u);
    return;
  }

  if (getSource(G) == NIL) {
    // BFS has not been called yet
    // print error here?
    return;
  }
  if (u == G->mostRecentSource) {
    append(L, u);  // Special case: destination is the source
    return;
  }
  clear(L);  // Clear the list to prepare for path insertion
  int currentVertex = u;
  while (currentVertex != G->mostRecentSource) {
    if (G->vertexArray[currentVertex] != NULL &&
        G->vertexArray[currentVertex]->parent != NIL) {
      prepend(L, currentVertex);  // Directly prepend to L
      currentVertex = G->vertexArray[currentVertex]->parent;
    } else {
      append(L, NIL);  // No valid path exists
      return;
    }
  }
  prepend(L, G->mostRecentSource);  // Add the source at the beginning
}

// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error: calling makeNull() on NULL Graph\n");
    return;
  }

  // iterate through each vertex and clear adjacency lists
  for (int i = 1; i <= getOrder(G); i++) {
    clear(G->vertexArray[i]->adjacencyList);
  }

  G->numEdges = 0;
}

// inserts a new edge joining u to v, i.e. u is added to the adjacency List of
// v, and v to the adjacency List of u. Must maintain these lists in sorted
// order by increasing labels. precondition: two int arguments must lie in the
// range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
    // printf("function addEdge started\n");
    // fflush(stdout);

    if (G == NULL || u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Error: addEdge() called with invalid vertices\n");
        return;
    }

    // Add v to u's adjacency list in sorted order
    List uList = G->vertexArray[u]->adjacencyList;
    moveFront(uList);
    while (index(uList) != -1 && v > get(uList)) {
        moveNext(uList);
    }
    if (index(uList) == -1) {
        append(uList, v);
    } else {
        insertBefore(uList, v);
    }

    // Add u to v's adjacency list in sorted order
    List vList = G->vertexArray[v]->adjacencyList;
    moveFront(vList);
    while (index(vList) != -1 && u > get(vList)) {
        moveNext(vList);
    }
    if (index(vList) == -1) {
        append(vList, u);
    } else {
        insertBefore(vList, u);
    } 

    G->numEdges++;
    // printf("function addEdge completed\n");
    // fflush(stdout);
}


// inserts a new directed edge from u to v, i.e. v is added to
// the adjacency List of u (but not u to the adjacency List of v).
// precondition: two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
  // printf("function addArc started");
  // fflush(stdout);

  if (G == NULL || u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
    fprintf(stderr, "Error: addEdge() called with invalid vertices\n");
    return;
  }

  append(G->vertexArray[u]->adjacencyList, v);

  G->numEdges++;
}
// runs the BFS algorithm on the Graph G with source s, setting
// the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s) {
  // printf("function BFS started");
  // fflush(stdout);
  if (G == NULL || s < 1 || s > getOrder(G)) {
    fprintf(stderr, "Error: calling BFS() on NULL Graph\n");
    return;
  }

  
  // initialize all vertices to defaults
  resetGraphVertices(G);

  // initialize source vertex
  setVertexQualities(G->vertexArray[s], GRAY, NIL, 0);  // set source

  List queue = newList();
  append(queue, s);
  while (length(queue) > 0) {
    // dequeue the next vertex
    int u = front(queue);  // gets front element (starting with source)
    deleteFront(queue);    // delete front element now from queue as you will be
                         // using that element below

    // move through u's adjacency list to queue neighbors
    for (moveFront(G->vertexArray[u]->adjacencyList);
         index(G->vertexArray[u]->adjacencyList) >= 0;
         moveNext(G->vertexArray[u]->adjacencyList)) {
      int v = get(G->vertexArray[u]->adjacencyList);
      if (G->vertexArray[v]->color == WHITE) {
        setVertexQualities(G->vertexArray[v], GRAY, u,
                           G->vertexArray[u]->distance + 1);
        append(queue, v);
      }
    }
    // Mark u as processed
    G->vertexArray[u]->color = BLACK;
  }
  // printf("function BFS completed");
  // fflush(stdout);
  freeList(&queue);
  G->mostRecentSource = s;
}

/*** Other operations ***/

// adding this to use to compare integers
int compareIntegers(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

// prints the adjacency list representation of G to the file pointed to by 'out'
void printGraph(FILE* out, Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error: calling printGraph() on NULL Graph\n");
    return;
  }

  for (int i = 1; i <= getOrder(G); i++) {
    fprintf(out, "%d: ", i);

    // create temporary array to store adjacency list elements
    int* tempArray =
        malloc(length(G->vertexArray[i]->adjacencyList) * sizeof(int));
    int index = 0;

    // copy elements from the adjacency list to the temporary array
    moveFront(G->vertexArray[i]->adjacencyList);
    while (index < length(G->vertexArray[i]->adjacencyList)) {
      // assign the retrieved integer from get() to the tempArray
      tempArray[index++] = get(G->vertexArray[i]->adjacencyList);
      moveNext(G->vertexArray[i]->adjacencyList);
    }

    // sort in ascending numerical order
    qsort(tempArray, index, sizeof(int), compareIntegers);

    // Print the sorted elements
    for (int j = 0; j < index; j++) {
      fprintf(out, "%d", tempArray[j]);

      // Print a space only if there are more elements in the list
      if (j < index - 1) {
        fprintf(out, " ");
      }
    }

    // Free the temporary array
    free(tempArray);

    fprintf(out, "\n");
  }
}
