#include<stdio.h>

typedef struct {
    int vertices;
    int adjmat[100][100];
}Graph;

void creategraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->vertices= vertices;

    for(int i=0; i<vertices; i++) {
        for(int j=0; j<vertices; j++) {
        graph->adjmat[i][j] = 0;
    }
}
}

void createedge(Graph* g, int src, int dest) {
    g->adjmat[src][dest]= 1;
    g->adjmat[dest][src]= 1;
}



