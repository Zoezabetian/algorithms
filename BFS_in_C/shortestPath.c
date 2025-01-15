#define _POSIX_C_SOURCE 200809L  // adding for strdup func

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
    fscanf(inputFile, "%d", &n); // Read the number of vertices
    Graph G = newGraph(n);

    while (1)
    {
        fscanf(inputFile, "%d %d", &u, &v);
        if (u == 0 && v == 0)
            break;
        addEdge(G, u, v);
    }
    // Print adjacency list representation of the graph
    printGraph(outputFile, G);
    // fprintf(outputFile, "\n");
    List L = newList();
    bool isFirstDistanceLine = true; // Add this flag to check if it's the first distance line

    // Read source-destination pairs and perform operations
    while (1)
    {
        fscanf(inputFile, "%d %d", &u, &v);
        if (u == 0 && v == 0)
            break;
        BFS(G, u);
        getPath(L, G, v);
        int distance = getDist(G, v);
        if (!isFirstDistanceLine) {
            fprintf(outputFile, "\n\n");
        }
        else {
            fprintf(outputFile, "\n");
        }
        if (distance != INF)
        {
            fprintf(outputFile, "The distance from %d to %d is %d\n", u, v, distance);
            fprintf(outputFile, "A shortest %d-%d path is: ", u, v);
            printList(outputFile, L);
            // fprintf(outputFile, "\n\n"); // Two newlines for spacing after each set
        }
        else
        {
            fprintf(outputFile, "The distance from %d to %d is infinity\n", u, v);
            fprintf(outputFile, "No %d-%d path exists", u, v);
        }
        isFirstDistanceLine = false;
        clear(L); // Clear the list for the next iteration
    }
    // Close files and free memory
    fclose(inputFile);
    fclose(outputFile);
    free(&G);
    free(inputFileName);
    free(outputFileName);

    return 0;
}
