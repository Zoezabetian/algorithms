#include "Graph.h"

typedef struct
{
    int vertex;
    int finishTime;
} VertexFinishTime;

/*** Constructors-Destructors ***/

Vertex newVertex()
{
    Vertex V = malloc(sizeof(VertexObj));
    if (V == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for Vertex.\n");
        return NULL;
    }

    V->adjacencyList = newList();
    V->color = WHITE;  // white color means undiscovered
    V->parent = NIL;   // indicates no parent
    V->distance = INF; // infinity distance
    V->discover = UNDEF;
    V->finish = UNDEF;
    return V;
}

void setVertexQualities(Vertex V, int color, int parent, int distance, int discover, int finish)
{
    V->color = color;
    V->parent = parent;
    V->distance = distance;
    V->discover = discover;
    V->finish = finish;
}

void resetGraphVertices(Graph G)
{ // added this for BFS usage
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling resetGraphVertices() on NULL Graph\n");
        return;
    }

    for (int i = 1; i <= getOrder(G); i++)
    {
        setVertexQualities(G->vertexArray[i], WHITE, NIL, INF, UNDEF, UNDEF);
    }
}

// returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges
Graph newGraph(int n)
{
    Graph G = malloc(sizeof(GraphObj));
    if (G == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for Graph.\n");
        return NULL;
    }

    G->numVertices = n;
    G->numEdges = 0;
    G->mostRecentSource = NIL;
    // malloc array
    G->vertexArray =
        malloc((n + 1) * sizeof(VertexObj)); // allocate memory for arrays
                                             // *** n+1 for 1-based findIndexing

    // initialize arrays
    for (int i = 1; i <= n; i++)
    {
        Vertex vertex = newVertex();
        G->vertexArray[i] = vertex;
    }
    return G;
}

// frees all heap memory associated with the Graph *pG, then sets the handle *pG
// to NULL
void freeGraph(Graph *pG)
{
    if (pG != NULL && *pG != NULL)
    {
        // Free the memory allocated for each vertex
        for (int i = 1; i <= getOrder(*pG); i++)
        {
            Vertex V = ((*pG)->vertexArray[i]);
            if (V->adjacencyList != NULL)
            {
                freeList(&(V->adjacencyList)); // free adjacency list for each vertex
            }
            free(V); // free rest of VertexObj struct
        }
        free((*pG)->vertexArray); // free vertexArray in graphObj

        free(*pG);  // free rest of graph components
        *pG = NULL; // set graph pointer to null
    }
}

/*** Access functions ***/

// returns number of vertices (called the order of the graph)
int getOrder(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling getOrder() on NULL Graph\n");
        return 0; // what should this return? NIL?
    }
    return G->numVertices;
}

// the number of edges (called the size of the graph)
int getSize(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling getSize() on NULL Graph\n");
        return 0; // what should this return? NIL?
    }
    return G->numEdges;
}

// returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called
int getSource(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling getSource() on NULL Graph\n");
        return NIL;
    }
    if (G->mostRecentSource != NIL)
    {
        return G->mostRecentSource;
    }
    else
    {
        return NIL;
    }
}
// will return the parent of vertex u in the BFS tree created by BFS(),
// or NIL if BFS() has not yet been called. precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getParent(Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling getParent() on NULL Graph\n");
        return NIL;
    }
    int order = getOrder(G); // for precondition
    if (u < 1 || u > order)
    {
        fprintf(stderr, "Vertex %d is out of valid range\n", u);
        return NIL;
    }
    return G->vertexArray[u]->parent;
}

// returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called. precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling getDist() on NULL Graph\n");
        return NIL;
    }
    int order = getOrder(G); // for precondition
    if (u < 1 || u > order)
    {
        fprintf(stderr, "Vertex %d is out of valid range\n", u);
        return NIL;
    }
    // if (G->mostRecentSource == NIL)
    // {
    //   // BFS has not been called yet
    //   return INF;
    // }
    return G->vertexArray[u]->distance;
}

// returns discover #
int getDiscover(Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling getDiscover() on NULL Graph\n");
        return NIL;
    }
    int order = getOrder(G); // for precondition
    if (u < 1 || u > order)
    {
        fprintf(stderr, "Vertex %d is out of valid range\n", u);
        return NIL;
    }
    return G->vertexArray[u]->discover;
}

// returns finish #
int getFinish(Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling getFinish() on NULL Graph\n");
        return NIL;
    }
    int order = getOrder(G); // for precondition
    if (u < 1 || u > order)
    {
        fprintf(stderr, "Vertex %d is out of valid range\n", u);
        return NIL;
    }
    return G->vertexArray[u]->finish;
}

/*** Manipulation procedures ***/

// appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists
// precondition: getSource(G)!=NIL, so BFS() must be called before getPath() is
// called also has precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)

void getPath(List L, Graph G, int u)
{
    if (G == NULL || L == NULL)
    {
        fprintf(stderr, "Error: calling getPath() on NULL Graph or List\n");
        return;
    }

    int order = getOrder(G);
    if (u < 1 || u > order)
    {
        fprintf(stderr, "Vertex %d is out of valid range\n", u);
        return;
    }

    if (getSource(G) == NIL)
    {
        return;
    }
    if (u == G->mostRecentSource)
    {
        append(L, u); // Special case: destination is the source
        return;
    }
    clear(L); // Clear the list to prepare for path insertion
    int currentVertex = u;
    while (currentVertex != G->mostRecentSource)
    {
        if (G->vertexArray[currentVertex] != NULL &&
            G->vertexArray[currentVertex]->parent != NIL)
        {
            prepend(L, currentVertex); // Directly prepend to L
            currentVertex = G->vertexArray[currentVertex]->parent;
        }
        else
        {
            append(L, NIL); // No valid path exists
            return;
        }
    }
    prepend(L, G->mostRecentSource); // Add the source at the beginning
}

// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling makeNull() on NULL Graph\n");
        return;
    }

    // iterate through each vertex and clear adjacency lists
    for (int i = 1; i <= getOrder(G); i++)
    {
        clear(G->vertexArray[i]->adjacencyList);
    }

    G->numEdges = 0;
}

// inserts a new edge joining u to v, i.e. u is added to the adjacency List of
// v, and v to the adjacency List of u. Must maintain these lists in sorted
// order by increasing labels. precondition: two int arguments must lie in the
// range 1 to getOrder(G)
void addEdge(Graph G, int u, int v)
{
    if (G == NULL || u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G))
    {
        fprintf(stderr, "Error: addEdge() called with invalid vertices\n");
        return;
    }

    bool edgeAdded = false;

    // add v to u's adjacency list in sorted order if it's not already there
    List uList = G->vertexArray[u]->adjacencyList;
    moveFront(uList);
    while (index(uList) != -1 && v > get(uList))
    {
        moveNext(uList);
    }
    if (index(uList) == -1)
    {
        append(uList, v);
        edgeAdded = true;
    }
    else if (get(uList) != v)
    {
        insertBefore(uList, v);
        edgeAdded = true;
    }

    // add u to v's adjacency list in sorted order if it's not already there
    List vList = G->vertexArray[v]->adjacencyList;
    moveFront(vList);
    while (index(vList) != -1 && u > get(vList))
    {
        moveNext(vList);
    }
    if (index(vList) == -1)
    {
        append(vList, u);
        edgeAdded = true;
    }
    else if (get(vList) != u)
    {
        insertBefore(vList, u);
        edgeAdded = true;
    }

    // then increment edge count if at least one edge was added
    if (edgeAdded)
    {
        G->numEdges++;
    }
}

// inserts a new directed edge from u to v, i.e. v is added to
// the adjacency List of u (but not u to the adjacency List of v).
// precondition: two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v)
{
    List uList = G->vertexArray[u]->adjacencyList;
    moveFront(uList);

    bool arcExists = false;
    while (index(uList) >= 0)
    {
        if (get(uList) == v) // if v already exists in u's adj list then don't add
                             // (u , v) a duplicative time
        {
            arcExists = true;
            break;
        }
        moveNext(uList);
    }

    if (!arcExists)
    {
        append(uList, v);
        G->numEdges++; // increase edge num only if arc didnt already exist
    }
}

// runs the BFS algorithm on the Graph G with source s, setting
// the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s)
{
    if (G == NULL || s < 1 || s > getOrder(G))
    {
        fprintf(stderr, "Error: calling BFS() on NULL Graph\n");
        return;
    }

    // initialize all vertices to defaults
    resetGraphVertices(G);

    // initialize source vertex
    setVertexQualities(G->vertexArray[s], GRAY, NIL, 0, UNDEF, UNDEF); // set source

    List queue = newList();
    append(queue, s);
    while (length(queue) > 0)
    {
        // dequeue the next vertex
        int u = front(queue); // gets front element (starting with source)
        deleteFront(queue);   // delete front element now from queue as you will be
                              // using that element below

        // move through u's adjacency list to queue neighbors
        for (moveFront(G->vertexArray[u]->adjacencyList);
             index(G->vertexArray[u]->adjacencyList) >= 0;
             moveNext(G->vertexArray[u]->adjacencyList))
        {
            int v = get(G->vertexArray[u]->adjacencyList);
            if (G->vertexArray[v]->color == WHITE)
            {
                setVertexQualities(G->vertexArray[v], GRAY, u,
                                   G->vertexArray[u]->distance + 1, UNDEF, UNDEF);
                append(queue, v);
            }
        }
        // Mark u as processed
        G->vertexArray[u]->color = BLACK;
    }
    freeList(&queue);
    G->mostRecentSource = s;
}

/*** Other operations ***/

// adding this to use to compare integers
int compareIntegers(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// prints the adjacency list representation of G to the file pointed to by 'out'
void printGraph(FILE *out, Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling printGraph() on NULL Graph\n");
        return;
    }

    for (int i = 1; i <= getOrder(G); i++)
    {
        fprintf(out, "%d: ", i);

        // create temporary array to store adjacency list elements
        int *tempArray =
            malloc(length(G->vertexArray[i]->adjacencyList) * sizeof(int));
        int index = 0;

        // copy elements from the adjacency list to the temporary array
        moveFront(G->vertexArray[i]->adjacencyList);
        while (index < length(G->vertexArray[i]->adjacencyList))
        {
            // assign the retrieved integer from get() to the tempArray
            tempArray[index++] = get(G->vertexArray[i]->adjacencyList);
            moveNext(G->vertexArray[i]->adjacencyList);
        }

        // sort in ascending numerical order
        qsort(tempArray, index, sizeof(int), compareIntegers);

        // Print the sorted elements
        for (int j = 0; j < index; j++)
        {
            fprintf(out, "%d", tempArray[j]);

            // Print a space only if there are more elements in the list
            if (j < index - 1)
            {
                fprintf(out, " ");
            }
        }

        // Free the temporary array
        free(tempArray);

        fprintf(out, "\n");
    }
}

/***PA 2 FUNCTIONS***/
static void Visit(Graph G, int u, int *time)
{
    G->vertexArray[u]->color = GRAY;
    (*time)++; // increment discover time
    G->vertexArray[u]->discover = *time;

    //** below print statements for testing
    // printf("Discover time of vertex %d: %d\n", u, *time);

    // // Print the adjacency list of vertex u
    // printf("Adjacency list for vertex %d: ", u);
    // for (moveFront(G->vertexArray[u]->adjacencyList); index(G->vertexArray[u]->adjacencyList) >= 0; moveNext(G->vertexArray[u]->adjacencyList))
    // {
    //     int v = get(G->vertexArray[u]->adjacencyList);
    //     printf("%d ", v);
    // }
    // printf("\n");

    // // Print the parent of vertex u
    // printf("Parent of vertex %d: %d\n", u, G->vertexArray[u]->parent);

    // create array to store adjacent vertices
    int numAdjacent = length(G->vertexArray[u]->adjacencyList);
    int *adjArray = (int *)malloc(numAdjacent * sizeof(int));

    // copy adjacency list to the array
    int i = 0;
    for (moveFront(G->vertexArray[u]->adjacencyList); index(G->vertexArray[u]->adjacencyList) >= 0; moveNext(G->vertexArray[u]->adjacencyList))
    {
        adjArray[i] = get(G->vertexArray[u]->adjacencyList);
        i++;
    }

    // sort array in ascending order!!
    for (i = 0; i < numAdjacent - 1; i++)
    {
        for (int j = 0; j < numAdjacent - i - 1; j++)
        {
            if (adjArray[j] > adjArray[j + 1])
            {
                int temp = adjArray[j];
                adjArray[j] = adjArray[j + 1];
                adjArray[j + 1] = temp;
            }
        }
    }

    // visit adjacent vertices in sorted order!!
    for (i = 0; i < numAdjacent; i++)
    {
        int v = adjArray[i];
        if (G->vertexArray[v]->color == WHITE)
        {
            G->vertexArray[v]->parent = u;
            Visit(G, v, time);
        }
    }

    G->vertexArray[u]->color = BLACK;
    (*time)++;
    G->vertexArray[u]->finish = *time;
    free(adjArray);
}

// will use this in sorting
int compareVertexFinishTime(const void *a, const void *b)
{
    VertexFinishTime *v1 = (VertexFinishTime *)a; // cast from void* to VertexFinishTime*
    VertexFinishTime *v2 = (VertexFinishTime *)b; // cast from void* to VertexFinishTime*
    return v2->finishTime - v1->finishTime;       // compare finish times in decreasing order
}

void sortVerticesByFinishTime(List S, Graph G)
{
    if (G == NULL || S == NULL)
    {
        fprintf(stderr, "Error: NULL Graph or List passed to sortVerticesByFinishTime.\n");
        return;
    }
    // pointer to an array of VertexFinishTime structs
    VertexFinishTime *auxArray = malloc((getOrder(G) + 1) * sizeof(VertexFinishTime));

    if (auxArray == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for auxArray.\n");
        exit(EXIT_FAILURE);
    }

    moveFront(S);
    for (int i = 1; i <= getOrder(G); i++)
    {
        int vertex = get(S);
        auxArray[i].vertex = vertex; // auxArray[i] is vertex instance of the VertexFinishTime struct (not a pointer)
        auxArray[i].finishTime = G->vertexArray[vertex]->finish;
        moveNext(S);
    }

    qsort(auxArray + 1, getOrder(G), sizeof(VertexFinishTime), compareVertexFinishTime); // sort using helper func

    clear(S);

    for (int i = 1; i <= getOrder(G); i++)
    {
        append(S, auxArray[i].vertex);
    }

    free(auxArray);
}

void DFS(Graph G, List S)
{
    if (G == NULL || S == NULL)
    {
        fprintf(stderr, "Error: calling DFS() on NULL Graph or List\n");
        return;
    }

    if (length(S) != getOrder(G))
    {
        fprintf(stderr, "Error: The length of List S is not equal to the number of vertices in the graph\n");
        return;
    }

    resetGraphVertices(G);

    int time = 0;
    moveFront(S);
    while (index(S) >= 0)
    {
        int u = get(S);
        if (G->vertexArray[u]->color == WHITE)
        {
            Visit(G, u, &time);
        }
        moveNext(S);
    }
    sortVerticesByFinishTime(S, G);
}

// returns a reference to a new graph object representing the transpose of G
// (reverses the direction of every edge in G)
Graph transpose(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling transpose() on NULL Graph\n");
        return NULL;
    }
    Graph GT = newGraph(G->numVertices);
    for (int u = 1; u <= getOrder(G); u++)
    { // for each vertex u, move through adjacency list
        for (moveFront(G->vertexArray[u]->adjacencyList); index(G->vertexArray[u]->adjacencyList) >= 0; moveNext(G->vertexArray[u]->adjacencyList))
        {
            int v = get(G->vertexArray[u]->adjacencyList); // v is each vertex in list
            addArc(GT, v, u);                              // add v to u
        }
    }
    return GT;
}

// returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Error: calling copyGraph() on NULL Graph\n");
        return NULL;
    }
    Graph copyG = newGraph(G->numVertices);
    for (int i = 1; i <= getOrder(G); i++)
    {
        setVertexQualities(copyG->vertexArray[i], G->vertexArray[i]->color, G->vertexArray[i]->parent, G->vertexArray[i]->distance, G->vertexArray[i]->discover, G->vertexArray[i]->finish);
    }
    for (int u = 1; u <= getOrder(G); u++)
    { // for each vertex u, move through adjacency list
        for (moveFront(G->vertexArray[u]->adjacencyList); index(G->vertexArray[u]->adjacencyList) >= 0; moveNext(G->vertexArray[u]->adjacencyList))
        {
            int v = get(G->vertexArray[u]->adjacencyList);
            addArc(copyG, u, v); // add exact same arc (u,v)
            // for an undirected graph, use addEdge??
        }
    }
    return copyG;
}