#include "Graph.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h> 

#define WHITE -3
#define GRAY 1
#define BLACK 2
#define NIL 0
#define UNDEF -1
#define INF INT_MAX

Graph test_DFS(Graph G, List S); 

int test_getDiscover(Graph G, List S, int u) {
    test_DFS(G, S);
    return getDiscover(G, u);
}


int test_getFinish(Graph G, List S, int u) {
    test_DFS(G, S);
    return getFinish(G, u);
} 

Graph test_DFS(Graph G, List S){
    DFS(G, S);
    return G;
} 

void test_transpose(FILE *outputFile, Graph G, List S) {
    test_DFS(G, S);
    Graph GT = transpose(G);
    printGraph(outputFile, GT);
}

void test_copyGraph(FILE *outputFile, Graph G, List S) {
    test_DFS(G, S);
    Graph Gcp = copyGraph(G);
    printGraph(outputFile, Gcp); 
}

void test_printGraph(FILE *outputFile, Graph G) {
    printGraph(outputFile, G);
}

int main()
{
    char *outputFileName = "GraphTest-out";

    // Open the output file for writing
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    Graph G1 = newGraph(8);
    List S1 = newList();
    int u1 = 3; // vertex we will use

    for (int i = 1; i <= 8; i++) {
        append(S1, i);
    }
    addArc(G1, 1, 2);
    addArc(G1, 2, 3);
    addArc(G1, 3, 1);
    addArc(G1, 3, 4);
    addArc(G1, 4, 5);
    addArc(G1, 5, 6);
    addArc(G1, 6, 4);
    addArc(G1, 3, 7);
    addArc(G1, 7, 8);
    addArc(G1, 8, 7);

    fprintf(outputFile, "Performing DFS() on Graph G1...");
    fprintf(outputFile, "\nG1 looks like:\n");
    Graph afterDFS1 = test_DFS(G1, S1);
    test_printGraph(outputFile, afterDFS1);

    fprintf(outputFile, "\nTesting getDiscover() on vertex %d of G1...", u1);
    fprintf(outputFile, "\nVertex %d's discover time is ", u1);
    fprintf(outputFile, "%d", test_getDiscover(G1, S1, u1));

    fprintf(outputFile, "\n\nTesting getFinish() on vertex %d of G1...", u1);
    fprintf(outputFile, "\nVertex %d's finish time is ", u1);
    fprintf(outputFile, "%d", test_getFinish(G1, S1, u1));

    fprintf(outputFile, "\n\nTesting transpose() on Graph G1...");
    fprintf(outputFile, "\nTranspose of G1 is:\n");
    test_transpose(outputFile, G1, S1);

    fprintf(outputFile, "\nTesting copyGraph() on Graph G1...");
    fprintf(outputFile, "\nCopy of G1 is:\n");
    test_copyGraph(outputFile, G1, S1);

    Graph G2 = newGraph(7);
    List S2 = newList();
    int u2 = 6;

    for (int i = 1; i <= 7; i++) {
        append(S2, i);
    }
    addArc(G2, 1, 2);
    addArc(G2, 1, 4);
    addArc(G2, 1, 6);
    addArc(G2, 1, 7);
    addArc(G2, 2, 3);
    addArc(G2, 2, 5);
    addArc(G2, 3, 6);
    addArc(G2, 4, 5);
    addArc(G2, 4, 7);
    addArc(G2, 6, 7);

    fprintf(outputFile, "\n----------------------------------------------------------------------------------------------------------");
    fprintf(outputFile, "\n\nPerforming DFS() on Graph G2...");
    fprintf(outputFile, "\nG2 looks like:\n");
    Graph afterDFS2 = test_DFS(G2, S2);
    test_printGraph(outputFile, afterDFS2);

    fprintf(outputFile, "\nTesting getDiscover() on vertex %d of G2...", u2);
    fprintf(outputFile, "\nVertex %d's discover time is ", u2);
    fprintf(outputFile, "%d", test_getDiscover(G2, S2, u2));

    fprintf(outputFile, "\n\nTesting getFinish() on vertex %d of G2...", u2);
    fprintf(outputFile, "\nVertex %d's finish time is ", u2);
    fprintf(outputFile, "%d", test_getFinish(G2, S2, u2));

    fprintf(outputFile, "\n\nTesting transpose() on Graph G2...");
    fprintf(outputFile, "\nTranspose of G2 is:\n");
    test_transpose(outputFile, G2, S2);

    fprintf(outputFile, "\nTesting copyGraph() on Graph G2...");
    fprintf(outputFile, "\nCopy of G2 is:\n");
    test_copyGraph(outputFile, G2, S2);
    fclose(outputFile);


    // now isolating test 4 on Model Graph test
    Graph A = newGraph(100);
    List L = newList();

    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);

    for (uint8_t i = 1; i <= 100; i++) {
        prepend(L, i);
    }

    DFS(A, L);

    if (getDiscover(A, 100) != 1) {
        printf("Test 2 Failed: Expected discover time of vertex 100 to be 1\n");
        return 1;
    }

    if (getDiscover(A, 64) != 73) {
        printf("Test 3 Failed: Expected discover time of vertex 64 to be 73\n");
        return 1;
    }

    if (getDiscover(A, 4) != 80) {
        printf("Test 4 Failed: Expected discover time of vertex 4 to be 80\n");
        return 1;
    }

    printf("All tests passed!\n");
    freeGraph(&A);
    freeList(&L);

    return 0;
}
