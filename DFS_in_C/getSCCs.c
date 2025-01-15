#define _POSIX_C_SOURCE 200809L // adding for strdup func

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <string.h>
#include <limits.h>

static void parseArgs(const int argc,
                      char *argv[],
                      char **inputFileName,
                      char **outputFileName)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    *inputFileName = strdup(argv[1]);
    *outputFileName = strdup(argv[2]);
}

int main(int argc, char *argv[])
{
    char *inputFileName;
    char *outputFileName;

    parseArgs(argc, argv, &inputFileName, &outputFileName);

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");
    if (inputFile == NULL || outputFile == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int n, u, v;
    fscanf(inputFile, "%d", &n); // read the number of vertices
    Graph G = newGraph(n);

    while (1)
    {
        fscanf(inputFile, "%d %d", &u, &v);
        if (u == 0 && v == 0)
            break;
        addArc(G, u, v);
    }
    // Print adjacency list representation of the graph
    fprintf(outputFile, "Adjacency list representation of G:\n");
    printGraph(outputFile, G);

    if (G == NULL)
    {
        fprintf(stdout, "Error: calling FindComponents() on NULL Graph\n");
        return -1;
    }

    List S = newList();
    for (int i = 1; i <= getOrder(G); i++)
    {
        append(S, i);
    }

    DFS(G, S); // Perform DFS on G

    Graph GT = transpose(G);
    DFS(GT, S); // Perform 2nd call of DFS on GT

    List *SCCs = malloc(getOrder(G) * sizeof(List));
    for (int i = 0; i < getOrder(G); i++)
    {
        SCCs[i] = newList(); // each element of array is a List that will store SCCs
    }

    List currentSCC = newList(); // will store current SCC list for vertex being processed

    int SCCcount = 0;

    for (moveFront(S); index(S) >= 0; moveNext(S))
    {
        int v = get(S); // v = vertex
        if (GT->vertexArray[v]->parent == NIL)
        { // parent must be NIL to start an SCC
            if (length(currentSCC) > 0)
            {                                          // if not an empty list:
                SCCs[SCCcount] = copyList(currentSCC); // copy currentSCC list to array
                SCCcount++;                            // increment strongly connected count
                clear(currentSCC);                     // clear list to make way for new SCC
            }
        }
        append(currentSCC, v); // appends vertex to current SCC list
    }
    if (length(currentSCC) > 0)
    {
        SCCs[SCCcount] = copyList(currentSCC); // handle the last SCC
        SCCcount++;
    }

    fprintf(outputFile, "\nG contains %d strongly connected components:", SCCcount);
    for (int i = SCCcount - 1; i >= 0; i--)
    { // reverse order for printing SCCs to match output file
        fprintf(outputFile, "\nComponent %d: ", SCCcount - i);
        printList(outputFile, SCCs[i]);
        freeList(&SCCs[i]);
    }

    // free dynamically allocated resources and close files
    free(currentSCC);
    free(SCCs);
    fclose(inputFile);
    fclose(outputFile);
    freeGraph(&G);
    freeGraph(&GT);
    free(inputFileName);
    free(outputFileName);

    return 0;
}
