#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Simple Queue for Kahn's Algorithm
int queue[MAX];
int front = -1, rear = -1;

void enqueue(int v) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = v;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

// Separate function to compute indegree as requested
void getIndegree(int V, int adj[MAX][MAX], int indegree[MAX]) {
    for (int j = 0; j < V; j++) {
        indegree[j] = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i][j] == 1) indegree[j]++;
        }
    }
}

int main() {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) return 1;

    int V, E;
    fscanf(fin, "%d %d", &V, &E);

    int adj[MAX][MAX] = {0};
    int u, v, i, j;

    // Read edges and build matrix
    for (i = 0; i < E; i++) {
        fscanf(fin, "%d %d", &u, &v);
        if (u >= 0 && u < V && v >= 0 && v < V) adj[u][v] = 1;
    }

    // Output Adjacency Matrix
    fprintf(fout, "Adjacency Matrix:\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            fprintf(fout, "%d ", adj[i][j]);
        }
        fprintf(fout, "\n");
    }

    // Compute and Output Indegree
    int indegree[MAX];
    getIndegree(V, adj, indegree);
    fprintf(fout, "\nIndegree:\n");
    for (i = 0; i < V; i++) fprintf(fout, "%d: %d\n", i, indegree[i]);

    // Topological Sort Logic
    for (i = 0; i < V; i++) {
        if (indegree[i] == 0) enqueue(i);
    }

    int topoOrder[MAX], count = 0;
    while (front != -1 && front <= rear) {
        int curr = dequeue();
        topoOrder[count++] = curr;

        for (i = 0; i < V; i++) {
            if (adj[curr][i] == 1) {
                indegree[i]--;
                if (indegree[i] == 0) enqueue(i);
            }
        }
    }

    // Detect Cycle and Print Order
    if (count < V) {
        fprintf(fout, "\nCycle detected. Topological sort cannot be obtained.\n");
    } else {
        fprintf(fout, "\nOne Valid Topological Order:\n");
        for (i = 0; i < count; i++) fprintf(fout, "%d ", topoOrder[i]);
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}