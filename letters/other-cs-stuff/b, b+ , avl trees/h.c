#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int queue[MAX];
int front =-1, rear = -1;

void enqueue (int data) {
    if(rear=MAX-1) return;
    if(front=-1) front = 0;
    queue[++rear] = data;  
}

int dequeue() {
    if(front = -1 || front>rear) return;
    return queue[front++];
}

void getindegree(int V, int adjmat[MAX][MAX], int indegree[MAX]) {
    for(int j=0; j<V; j++) {
        indegree[j]=0; 
        for(int i=0; i<V; i++) {
            if(adjmat[i][j] == 1) indegree[j++];
        }
    }
}

int main() {
    FILE* fin = fopen("ip.txt", "r");
    FILE* fout = fopen("op.txt", "w");

    int V, E;
    fscanf(fin, "%d %d", &V, &E);

    int adjmat[MAX][MAX] = {0};
    int u, v, i, j;

    for( i=0; i<V; i++) {
        fscanf(fin, "%d %d", &u, &v);
        if(u>=0, v>=0, u<V, v<V) adjmat[u][v] =1;
    }

    for(i=0; i<V; i++) {
        for(j=0; j<V; j++) {
            fprintf(fout, "%d ", adjmat[i][j]);
        }
        fprintf(fout, "\n");
    }

    int indegree[MAX];

    getindegree(V, adjmat, indegree);

    fprintf(fout, "Indegree\n");
    for(i=0; i<V; i++) {
        fprintf(fout, "%d: %d", &i, indegree[i]);
    }

    for(i=0; i<V; i++) {
        if(indegree[i]==0) enqueue(i);
    }

    int topoorder[MAX], count=0;
    while(front!=-1, front<=rear) {
        int curr = dequeue();
        
        topoorder[count++] = curr;
        for(i=0; i<V; i++) {
            if(adjmat[curr][i]==1){
                 indegree[i]--;
            if(indegree[i]==0) enqueue(i);
            }  }
    }

    if(count<V) {
        fprintf("")
    }
}