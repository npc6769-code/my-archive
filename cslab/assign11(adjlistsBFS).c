#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

// Node structure for adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
    int* distance;
};

// Function to create a node
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(int));
    graph->distance = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        graph->distance[i] = -1; // -1 indicates unreachable
    }
    return graph;
}

// Add edge to undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Check if edge already exists to avoid duplicates from input
    struct Node* temp = graph->adjLists[src];
    while (temp) {
        if (temp->vertex == dest) return;
        temp = temp->next;
    }

    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// BFS Traversal
void bfs(struct Graph* graph, int startVertex) {
    int queue[MAX];
    int front = 0, rear = 0;

    graph->visited[startVertex] = 1;
    graph->distance[startVertex] = 0;
    queue[rear++] = startVertex;

    printf("BFS Traversal: ");

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                graph->distance[adjVertex] = graph->distance[currentVertex] + 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    int N;
    if (fscanf(file, "%d", &N) != 1) return 1;
    fgetc(file); // consume newline

    struct Graph* graph = createGraph(N);

    // Task 1: Graph Construction (Reading adjacency list format)
    char line[MAX * 10];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ":");
        if (!token) continue;
        int u = atoi(token);
        
        token = strtok(NULL, " \t\n");
        while (token) {
            int v = atoi(token);
            addEdge(graph, u, v);
            addEdge(graph, v, u); // Undirected
            token = strtok(NULL, " \t\n");
        }
    }

    printf("Adjacency List:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i);
        struct Node* temp = graph->adjLists[i];
        while (temp) {
            printf("%d%s", temp->vertex, temp->next ? " -> " : "");
            temp = temp->next;
        }
        printf("\n");
    }

    // Task 2: BFS Traversal from Source 0
    int source = 0;
    bfs(graph, source);

    // Task 3: Connectivity Check
    int connected = 1;
    int components = 0;

    // Reset visited for full component counting
    for (int i = 0; i < N; i++) graph->visited[i] = 0;

    for (int i = 0; i < N; i++) {
        if (graph->visited[i] == 0) {
            components++;
            // Internal BFS to mark all nodes in this component
            int q[MAX], f = 0, r = 0;
            graph->visited[i] = 1;
            q[r++] = i;
            while (f < r) {
                int curr = q[f++];
                struct Node* t = graph->adjLists[curr];
                while (t) {
                    if (graph->visited[t->vertex] == 0) {
                        graph->visited[t->vertex] = 1;
                        q[r++] = t->vertex;
                    }
                    t = t->next;
                }
            }
        }
    }

    if (components == 1) {
        printf("The graph is connected.\n");
    } else {
        printf("The graph is NOT connected.\n");
        printf("Number of connected components: %d\n", components);
    }

    // Task 4: Shortest Path (already computed during the first BFS)
    printf("\nVertex\tDistance from Source (%d)\n", source);
    for (int i = 0; i < N; i++) {
        printf("%d\t%d\n", i, graph->distance[i]);
    }

    fclose(file);
    return 0;
}