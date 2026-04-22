#include<stdio.h>
#include<stdlib.h>

struct huffnode {
    char data;
    int freq;
    struct huffnode *left, *right;
};

struct priorityqueue{
    int size;
    int capacity;
    struct huffnode* arr[100];
};

struct huffnode* createhuffnode(char data, int freq) {
    struct huffnode* node = malloc(sizeof(struct huffnode));

    if(node==NULL) {
        printf("allocation failed\n");
        return NULL;
    }

    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

struct priorityqueue* createpriorityqueue(capacity) {
    struct priorityqueue* pq = malloc(sizeof(struct priorityqueue));

    if(pq==NULL) {
        printf("allocation failed\n");
        return NULL;
    }

    pq->size = 0;
    pq->capacity = capacity;

    return pq;
}

void swap(struct huffnode **a, struct huffnode **b) {
    struct huffnode *temp = *a;
    *a = *b;
    *b = temp;
}

void heapifydown(struct priorityqueue* pq, int pos) {
    int smallest = pos;
    int left = 2*pos + 1;
    int right = 2*pos + 2;

    if(left< pq->size && pq->arr[left]->freq < pq->arr[smallest]->freq )
    smallest = left;

    if(right < pq->arr[right]->freq < pq->arr[smallest]->freq)
    smallest = right;

    if(smallest!=pos) {
        swap(&pq->arr[smallest], &pq->arr[left]);
        heapifydown(pq, smallest);
    }
}

void heapifyup(struct priorityqueue* pq, int pos) {
    int parent = (pos-1) /2;

    if(pos<pq->size && pq->arr[pos]->freq < pq->arr[parent]->freq);
    swap(&pq->arr[parent], &pq->arr[pos]);
    heapifyup(pq, parent);
    
}

void insertpriorityqueue(struct priorityqueue* pq, struct huffnode* node) {
    pq->arr[pq->size]=node;
    pq->size++;
    heapifyup(pq, pq->size-1);
}

struct huffnode* extractmin(struct priorityqueue* pq) {
    struct huffnode* temp= pq->arr[0];
    pq->arr[0]= pq->arr[pq->size-1];
    pq->size--;

    heapifydown(pq, 0);
    return temp;
}

struct huffnode* buildhuffmantree(char arr[], int freq[], int size) {
    struct huffnode* left, *right, *newnode;

    struct priorityqueue* pq = createpriorityqueue(size);

    for(int i=0; i<size; i++) {
        insertpriorityqueue(pq, createhuffnode(arr[i], freq[i]));
    }
}