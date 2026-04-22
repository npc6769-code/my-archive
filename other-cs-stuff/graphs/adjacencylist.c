#include<stdio.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} node;

typedef struct Graph {
    int numvertices;
    node** adjlists;
}Graph;

node* createnode(int vertex) {
    node* newnode = malloc(sizeof(node));
    newnode->vertex = vertex;
    newnode->next = NULL;
    return newnode;
}

Graph* creategraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numvertices= vertices;

    graph->adjlists = malloc(vertices * sizeof(node*));

    for(int i=0; i<vertices; i++) {
        graph->adjlists[i] = NULL;
    }

    return graph;
}

void addedge(Graph* graph, int source, int destination) {
    node* newnode = createnode(destination);
    newnode->next = graph->adjlists[source];
    graph->adjlists[source] = newnode; 

    newnode=createnode(source);
    newnode->next=graph->adjlists[destination];
    graph->adjlists[destination]= newnode;

}