#include <stdio.h>
#include <stdlib.h>

// Global variable to track the total number of rotations
int totalRotations = 0;

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Helper function to get height of a node
int height(struct Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

// Helper to get max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

// Right rotation (LL Case)
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    totalRotations++;
    return x;
}

// Left rotation (RR Case)
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    totalRotations++;
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// --- Traversals ---

void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void postOrder(struct Node *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

// Task 2: Node Details using Inorder
void displayDetails(struct Node *root) {
    if (root != NULL) {
        displayDetails(root->left);
        
        printf("%d\t", root->key);
        if (root->left) printf("%d\t", root->left->key); else printf("NULL\t");
        if (root->right) printf("%d\t", root->right->key); else printf("NULL\t");
        printf("%d\t%d\n", root->height - 1, getBalance(root)); // Height as 0-indexed per sample
        
        displayDetails(root->right);
    }
}

int main() {
    struct Node *root = NULL;
    int n, val;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) return 0;

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("\nInorder traversal: ");
    inOrder(root);
    printf("\n");

    printf("\nNode\tLeft\tRight\tHeight\tBalance\n");
    printf("    \tChild\tChild\t      \tFactor\n");
    displayDetails(root);

    printf("\nTotal rotations performed: %d\n", totalRotations);

    printf("\nInorder: "); inOrder(root);
    printf("\nPreorder: "); preOrder(root);
    printf("\nPostorder: "); postOrder(root);
    printf("\n");

    return 0;
}