#include <stdio.h>
#include <stdlib.h>

#define M 3 // Order of the B-Tree

typedef struct BTreeNode {
    int keys[M - 1];
    struct BTreeNode *children[M];
    int numKeys;
    int isLeaf;
} BTreeNode;

BTreeNode *root = NULL;

// --- 1. Create Node ---
BTreeNode *createNode(int isLeaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < M; i++) node->children[i] = NULL;
    return node;
}

// --- 2. Search ---
BTreeNode* search(BTreeNode* node, int key) {
    int i = 0;
    while (i < node->numKeys && key > node->keys[i]) i++;
    
    if (i < node->numKeys && node->keys[i] == key) return node;
    if (node->isLeaf) return NULL;
    
    return search(node->children[i], key);
}

// --- 3. Split Child ---
void splitChild(BTreeNode *parent, int index, BTreeNode *child) {
    int mid = (M - 1) / 2;
    BTreeNode *newNode = createNode(child->isLeaf);
    newNode->numKeys = mid;

    // Move half the keys to the new node
    for (int j = 0; j < mid; j++)
        newNode->keys[j] = child->keys[j + mid + 1];

    // If not leaf, move child pointers
    if (!child->isLeaf) {
        for (int j = 0; j <= mid; j++)
            newNode->children[j] = child->children[j + mid + 1];
    }

    child->numKeys = mid; // Reduce original node size

    // Shift parent children to make room
    for (int j = parent->numKeys; j > index; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[index + 1] = newNode;

    // Shift parent keys to make room
    for (int j = parent->numKeys - 1; j >= index; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[index] = child->keys[mid];
    parent->numKeys++;
}

// --- 4. Insert Non-Full ---
void insertNonFull(BTreeNode *node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) i--;
        i++;
        if (node->children[i]->numKeys == M - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// --- 5. Main Insert Wrapper ---
void insert(int key) {
    if (!root) {
        root = createNode(1);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        if (root->numKeys == M - 1) {
            BTreeNode *newRoot = createNode(0);
            newRoot->children[0] = root;
            splitChild(newRoot, 0, root);
            int i = (key > newRoot->keys[0]) ? 1 : 0;
            insertNonFull(newRoot->children[i], key);
            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }
}

// --- 6. Traversal (For Testing) ---
void traverse(BTreeNode *node) {
    int i;
    for (i = 0; i < node->numKeys; i++) {
        if (!node->isLeaf) traverse(node->children[i]);
        printf("%d ", node->keys[i]);
    }
    if (!node->isLeaf) traverse(node->children[i]);
}

int main() {
    int vals[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for(int i=0; i<8; i++) insert(vals[i]);

    printf("B-Tree Traversal: ");
    traverse(root);
    printf("\n");

    return 0;
}