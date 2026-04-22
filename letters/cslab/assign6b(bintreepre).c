#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure as defined in the assignment
struct node {
    char data;
    struct node* left;
    struct node* right;
};

// Function to create a new node
struct node* createNode(char data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Search for the index of a value in the in-order array
int search(char arr[], int start, int end, char value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) return i;
    }
    return -1;
}

/**
 * Reconstructs the tree recursively.
 * postIdx is passed by pointer to maintain the global position in the post-order array.
 */
struct node* buildTree(char in[], char post[], int inStart, int inEnd, int* postIdx) {
    if (inStart > inEnd) return NULL;

    // The last element in post-order is the root
    struct node* root = createNode(post[*postIdx]);
    (*postIdx)--;

    // If node has no children, return
    if (inStart == inEnd) return root;

    // Find index of this root in in-order to split left and right subtrees
    int inIdx = search(in, inStart, inEnd, root->data);

    // Build right subtree before left because post-order is (Left, Right, Root)
    // and we are traversing post-order from end to start.
    root->right = buildTree(in, post, inIdx + 1, inEnd, postIdx);
    root->left = buildTree(in, post, inStart, inIdx - 1, postIdx);

    return root;
}

void printPreOrder(struct node* node, FILE* fp) {
    if (node == NULL) return;
    fprintf(fp, "%c ", node->data);
    printPreOrder(node->left, fp);
    printPreOrder(node->right, fp);
}

int getHeight(struct node* node) {
    if (node == NULL) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main() {
    FILE *inFile = fopen("ip.txt", "r");
    FILE *outFile = fopen("op.txt", "w");

    if (!inFile || !outFile) {
        printf("Error opening files.\n");
        return 1;
    }

    char inOrder[100], postOrder[100];
    
    // Read the two strings from the file
    if (fscanf(inFile, "%s %s", inOrder, postOrder) != 2) {
        printf("Invalid input format.\n");
        return 1;
    }

    int n = strlen(inOrder);
    int postIdx = n - 1;

    // Construct the tree
    struct node* root = buildTree(inOrder, postOrder, 0, n - 1, &postIdx);

    // Output results to op.txt
    printPreOrder(root, outFile);
    fprintf(outFile, "\n%d\n", getHeight(root));

    fclose(inFile);
    fclose(outFile);

    return 0;
}