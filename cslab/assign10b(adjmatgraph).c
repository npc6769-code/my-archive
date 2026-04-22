#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure for Kahn's Algorithm
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

// Function to compute in-degrees of all vertices
void computeIndegree(int adj[MAX][MAX], int V, int indegree[]) {
    for (int i = 0; i < V; i++) {
        indegree[i] = 0;
        for (int j = 0; j < V; j++) {
            if (adj[j][i] == 1) {
                indegree[i]++;
            }
        }
    }
}

int main() {
    FILE *inFile = fopen("input.txt", "r");
    FILE *outFile = fopen("output.txt", "w");

    if (!inFile || !outFile) {
        printf("Error: Could not open files.\n");
        return 1;
    }

    int V, E;
    if (fscanf(inFile, "%d %d", &V, &E) != 2) {
        printf("Error: Invalid input format.\n");
        return 1;
    }

    int adj[MAX][MAX] = {0};
    int u, v;

    // Construct the directed graph
    for (int i = 0; i < E; i++) {
        if (fscanf(inFile, "%d %d", &u, &v) == 2) {
            if (u >= 0 && u < V && v >= 0 && v < V) {
                adj[u][v] = 1;
            }
        }
    }

    // Task 3: Display Adjacency Matrix
    fprintf(outFile, "Adjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fprintf(outFile, "%d ", adj[i][j]);
        }
        fprintf(outFile, "\n");
    }

    // Task 4 & 5: Compute and display Indegree
    int indegree[MAX];
    computeIndegree(adj, V, indegree);

    fprintf(outFile, "\nIndegree:\n");
    int zeroIndegreeFound = 0;
    for (int i = 0; i < V; i++) {
        fprintf(outFile, "%d: %d\n", i, indegree[i]);
        if (indegree[i] == 0) zeroIndegreeFound = 1;
    }

    // Check if topological sort is possible
    if (!zeroIndegreeFound) {
        fprintf(outFile, "\nTopological sort cannot be obtained (Cycle detected).\n");
        fclose(inFile); fclose(outFile);
        return 0;
    }

    // Task 6: Topological Sorting using a Queue
    struct Queue q;
    initQueue(&q);
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            enqueue(&q, i);
        }
    }

    int topoOrder[MAX];
    int count = 0;

    while (!isEmpty(&q)) {
        int curr = dequeue(&q);
        topoOrder[count++] = curr;

        for (int i = 0; i < V; i++) {
            if (adj[curr][i] == 1) {
                indegree[i]--;
                if (indegree[i] == 0) {
                    enqueue(&q, i);
                }
            }
        }
    }

    // Task 7: Cycle Detection and Output Order
    if (count != V) {
        fprintf(outFile, "\nCycle detected! The graph is not a DAG.\n");
    } else {
        fprintf(outFile, "\nOne Valid Topological Order:\n");
        for (int i = 0; i < count; i++) {
            fprintf(outFile, "%d ", topoOrder[i]);
        }
        fprintf(outFile, "\n");
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}