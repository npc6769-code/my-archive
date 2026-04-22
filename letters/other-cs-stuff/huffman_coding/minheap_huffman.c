#include<stdio.h>
#include<stdlib.h>

struct huffnode {
    char data;
    int freq;
    struct huffnode *left, *right;
};

struct priorityqueue {
    int size;
    int capacity;
    struct huffnode* array[100];
};

struct huffnode* createnode(char data, int freq) {
    struct huffnode* node = malloc(sizeof(struct huffnode));

    if(node==NULL) {
        printf("Allocation failed!");
        return NULL;
    }

    node->data = data;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;


    return node;
}

struct priorityqueue* createpriorityqueue(int capacity) {
    struct priorityqueue* pq = malloc(sizeof(struct priorityqueue));

    if(pq==NULL) {
        printf("Allocation failed!");
        return NULL;
    }

    pq->size = 0;
    pq->capacity=capacity;

    return pq;
}

void swap(struct huffnode**a, struct huffnode** b) {
    struct huffnode* temp = *a;
    *a = *b;
    *b = temp;
}

void heapifydown(struct priorityqueue* pq, int pos) {
    int smallest = pos;
    int left = 2*pos + 1;
    int right = 2*pos + 2;

    if(left < pq->size && pq->array[left]->freq < pq->array[smallest]->freq) 
    smallest = left;

    if(right < pq->size && pq->array[right]->freq < pq->array[smallest]->freq)
    smallest=right;

    if(smallest!=pos) {
        swap(&pq->array[pos], &pq->array[smallest]);
        heapifydown(pq, smallest);
    }
}

void heapifyup(struct priorityqueue* pq, int pos) {
    int parent = (pos-1)/2;
    if(pos>0 && pq->array[pos]->freq < pq->array[parent]->freq) {
        swap(&pq->array[pos], &pq->array[parent]);
        heapifyup(pq, parent);
    }
}

void insertpriorityqueue(struct priorityqueue* pq, struct huffnode* node) {
    pq->array[pq->size] = node;
    pq->size++;
    heapifyup(pq, pq->size -1);
}

struct huffnode* extractmin(struct priorityqueue* pq) {
    struct huffnode* temp=pq->array[0];
    pq->array[0]=pq->array[pq->size-1];
    pq->size--;
    heapifydown(pq, 0);
    return temp;
}

struct huffnode* buildhuffmantree(char data[], int freq[], int size) {
    struct huffnode *left, *right, *newnode;
    
    struct priorityqueue* pq = createpriorityqueue(size);

    for(int i=0; i<size; i++) {
        insertpriorityqueue(pq, createnode(data[i], freq[i]));
    }

    while(pq->size >1) {
        left = extractmin(pq);
        right = extractmin(pq);
        newnode = createnode('$', left->freq + right->freq);
        newnode->left = left;
        newnode->right = right;
        insertpriorityqueue(pq, newnode);
    }
    return extractmin(pq);
}

void printhcodes(struct huffnode* root, int arr[], int top) {
    if(root->left) {
        arr[top] = 0;
        printhcodes(root->left, arr, top+1);
    }

    if(root->right) {
        arr[top] = 1;
        printhcodes(root->right, arr, top+1);
    }

    if(!root->left && !root->right) {
        printf("%c ", root->data);
        for(int i=0; i<top; i++) 
        printf("%d", arr[i]);
        printf("\n");
    }
}

int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]);

    struct huffnode* root = buildhuffmantree(arr, freq, size);
    int codearr[100], top=0;
    printf("huffmancodes: \n");
    printhcodes(root, codearr, top);

    return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     