#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Node for Adjacency List
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node* adjLists[MAX];
    int visited[MAX];
};

// Simple Queue for BFS
int queue[MAX];
int front = -1, rear = -1;

void enqueue(int v) {
    if (front == -1) front = 0;
    queue[++rear] = v;
}

int dequeue() {
    int item = queue[front++];
    if (front > rear) front = rear = -1;
    return item;
}

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to add edge (Undirected)
void addEdge(struct Graph* g, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = g->adjLists[src];
    g->adjLists[src] = newNode;
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    if (!fin) return 1;

    int N;
    fscanf(fin, "%d", &N);
    struct Graph* g = malloc(sizeof(struct Graph));
    g->numVertices = N;

    for (int i = 0; i < N; i++) {
        g->adjLists[i] = NULL;
        g->visited[i] = 0;
    }

    // Task 1: Read and Construct Adjacency List
    int u, v;
    char line[256];
    fgets(line, sizeof(line), fin); // consume newline
    for (int i = 0; i < N; i++) {
        fgets(line, sizeof(line), fin);
        char *ptr = line;
        int offset;
        sscanf(ptr, "%d: %n", &u, &offset);
        ptr += offset;
        while (sscanf(ptr, "%d %n", &v, &offset) == 1) {
            addEdge(g, u, v);
            ptr += offset;
        }
    }

    printf("Adjacency List:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: ", i);
        struct Node* temp = g->adjLists[i];
        while (temp) {
            printf("%d%s", temp->vertex, temp->next ? " -> " : "");
            temp = temp->next;
        }
        printf("\n");
    }

    // Task 2: BFS Traversal & Task 4: Shortest Path
    int source = 0; // Using 0 as sample source
    int distance[MAX];
    for (int i = 0; i < N; i++) distance[i] = -1;

    printf("\nBFS Traversal: ");
    g->visited[source] = 1;
    distance[source] = 0;
    enqueue(source);

    int visitedCount = 0;
    while (front != -1) {
        int curr = dequeue();
        printf("%d ", curr);
        visitedCount++;

        struct Node* temp = g->adjLists[curr];
        while (temp) {
            if (!g->visited[temp->vertex]) {
                g->visited[temp->vertex] = 1;
                distance[temp->vertex] = distance[curr] + 1;
                enqueue(temp->vertex);
            }
            temp = temp->next;
        }
    }

    // Task 3: Connectivity Check
    printf("\n\n%s\n", (visitedCount == N) ? "The graph is connected." : "The graph is NOT connected.");

    // Task 4: Print Distances
    printf("\nVertex\tDistance from Source\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t%d\n", i, distance[i]);
    }

    fclose(fin);
    return 0;
}