#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

struct Node {
    char data;
    int freq;
    struct Node *left, *right;
    int isLeaf;
};

struct MinHeap {
    int size;
    struct Node* array[MAX_CHARS];
};

// --- Node & Heap Helpers ---

struct Node* createNode(char data, int freq) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    node->isLeaf = (data != '\0');
    return node;
}

void swapNodes(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

// Custom comparison based on assignment rules
int compareNodes(struct Node* a, struct Node* b) {
    if (a->freq != b->freq) return a->freq - b->freq;
    // Rule 2: Internal node vs Leaf node (Internal node higher priority)
    if (a->isLeaf != b->isLeaf) return a->isLeaf - b->isLeaf;
    // Rule 1: Lexicographical order for same freq leaves
    return (unsigned char)a->data - (unsigned char)b->data;
}

void heapify(struct MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && compareNodes(heap->array[left], heap->array[smallest]) < 0)
        smallest = left;
    if (right < heap->size && compareNodes(heap->array[right], heap->array[smallest]) < 0)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&heap->array[smallest], &heap->array[idx]);
        heapify(heap, smallest);
    }
}

struct Node* extractMin(struct MinHeap* heap) {
    struct Node* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return temp;
}

void insertHeap(struct MinHeap* heap, struct Node* node) {
    heap->size++;
    int i = heap->size - 1;
    while (i && compareNodes(node, heap->array[(i - 1) / 2]) < 0) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

// --- Huffman Logic ---

void generateCodes(struct Node* root, char* code, int top, char codes[MAX_CHARS][MAX_CHARS]) {
    if (root->left) {
        code[top] = '1'; // Rule 4: Left edge is 1
        generateCodes(root->left, code, top + 1, codes);
    }
    if (root->right) {
        code[top] = '0'; // Rule 4: Right edge is 0
        generateCodes(root->right, code, top + 1, codes);
    }
    if (!root->left && !root->right) {
        code[top] = '\0';
        strcpy(codes[(unsigned char)root->data], code);
    }
}

// --- Analysis Helpers ---

int getHeight(struct Node* root) {
    if (!root || (!root->left && !root->right)) return 0;
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    return (lh > rh ? lh : rh) + 1;
}

int countNodes(struct Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(struct Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    if (!in || !out) return 1;

    char str[1000];
    fscanf(in, "%s", str);

    int freq[MAX_CHARS] = {0};
    int distinctCount = 0;
    for (int i = 0; str[i]; i++) {
        if (freq[(unsigned char)str[i]] == 0) distinctCount++;
        freq[(unsigned char)str[i]]++;
    }

    fprintf(out, "Character Frequencies:\n");
    struct MinHeap heap = {0};
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            fprintf(out, "%c : %d\n", i, freq[i]);
            insertHeap(&heap, createNode((char)i, freq[i]));
        }
    }

    // Task 2: Build Tree
    while (heap.size > 1) {
        struct Node* left = extractMin(&heap);
        struct Node* right = extractMin(&heap);
        // Rule 3: First extracted becomes left, second becomes right
        struct Node* top = createNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertHeap(&heap, top);
    }
    struct Node* root = extractMin(&heap);

    // Task 3: Generate Codes
    char hCodes[MAX_CHARS][MAX_CHARS] = {{0}};
    char tempCode[MAX_CHARS];
    generateCodes(root, tempCode, 0, hCodes);

    fprintf(out, "\nHuffman Codes:\n");
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) fprintf(out, "%c : %s\n", i, hCodes[i]);
    }

    // Task 4: Encode
    fprintf(out, "\nEncoded string:\n");
    for (int i = 0; str[i]; i++) fprintf(out, "%s", hCodes[(unsigned char)str[i]]);

    // Task 5: Analysis
    fprintf(out, "\n\nHeight of Huffman Tree: %d", getHeight(root));
    fprintf(out, "\nTotal nodes: %d", countNodes(root));
    fprintf(out, "\nLeaf nodes: %d\n", countLeaves(root));

    fclose(in); fclose(out);
    return 0;
}