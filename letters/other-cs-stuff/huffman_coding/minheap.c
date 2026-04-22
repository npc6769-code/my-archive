#include<stdio.h>
#include<stdlib.h>

typedef struct package {
    int packageid;
    int destinationcode;
    int deadline;
}node;

typedef struct {
    int size;
    node* arr[100];
}minheap;

node* createnode(int pid, int des, int dead) {
    node* newnode = malloc(sizeof(node));

    if(newnode==NULL) {
        printf("Allocation failed");
        return NULL;
    }

    newnode->packageid=pid;
    newnode->destinationcode=des;
    newnode->deadline=dead;

    return newnode;
}

minheap* createheap(int capacity) {
    minheap* heap = malloc(sizeof(heap));

    heap->size=0;
    return heap;
}

void swap(node **a, node **b) {
    node *temp=*a;
    *a=*b;
    *b=temp;
}

void heapifyup(minheap* pq, int pos) {
    int parent = (pos-1)/2;
    if(pos>0 && pq->arr[pos]->deadline < pq->arr[parent]->deadline)
    swap(&pq->arr[pos], &pq->arr[parent]);
    heapifyup(pq, parent);
}

void heapifydown(minheap* pq, int pos) {
    int left = 2*pos + 1;
    int right = 2*pos + 2;
    int smallest = pos;

    if(left < pq->size && pq->arr[smallest]->deadline > pq->arr[left]->deadline)
    smallest=left;

    if(right < pq->size && pq->arr[smallest]->deadline > pq->arr[right]->deadline)
    smallest=right;

    if(smallest!=pos) {
        swap(&pq->arr[smallest], &pq->arr[pos]);
    heapifydown(pq, smallest);
}}

node* extractmin(minheap* pq) {
    node* temp = pq->arr[0];
    pq->arr[0] = pq->arr[pq->size-1];
    pq->size--;
    heapifydown(pq, 0);

    return temp;
}

void insertheap(minheap *pq, node* n) {
    pq->arr[pq->size] = n;
    pq->size++;
    heapifyup(pq, pq->size-1);
}

int main() {
    
}