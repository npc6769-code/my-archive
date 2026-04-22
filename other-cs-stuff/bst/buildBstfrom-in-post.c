#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct bintreenode {
    char data;
    struct bintreenode *left;
    struct bintreenode *right;
}node;

node* createnode(char data) {
    node* newnode = malloc(sizeof(node));
    if(newnode==NULL) {
        printf("Allocation failed");
        return NULL;
    }

    newnode->data = data;
    newnode->left = newnode->right = NULL;

    return newnode;
}

int search(char inorder[], int instart, int inend, char data) {

    for(int i=instart; i<=inend; i++) {
        if(data == inorder[i]) {
           return i;
        }
    }

    return -1;
    }

    node* buildtreeInPost(char inorder[], char postorder[], int instart, int inend, int* postindex) {
        if(instart>inend) return NULL;

        node* root = createnode(postorder[*postindex]);
        (*postindex)--;

        if(instart==inend) return root;
        int inindex = search(inorder, instart, inend, root->data);

        root->right = buildtreeInPost(inorder, postorder, inindex+1, inend, postindex);
        root->left = buildtreeInPost(inorder, postorder, instart, inindex-1, postindex);

        return root;
    }

    node* buildtreeInPre(char inorder[], char preorder[], int instart, int inend, int* preindex) {
        if(instart>inend) return NULL;

        node* root = createnode(preorder[*preindex]);
        (*preindex)++;

        if(instart==inend) return root;

        int inindex = search(inorder, instart, inend, root->data);

        root->left = buildtreeInPre(inorder, preorder, instart, inindex-1, preindex);
        root->right = buildtreeInPre(inorder, preorder, inindex+1, inend, preindex);

        return root;
    }

    void preordertraversal(node* root) {
        printf("%c ", root->data);
        preordertraversal(root->left);
        preordertraversal(root->right);
        printf("\n");
    }

    void postordertraversal(node* root) {
        postordertraversal(root->left);
        postordertraversal(root->right);
        printf("%c ", root->data);
        printf("\n");
    }

    int main() {
        char inorder[20];
        char preorder[20];
        char postorder[20];

        printf("Enter the inorder Traversal: ");
        scanf("%s", inorder);
        printf("Enter the preorder traversal: ");
        scanf("%s", preorder);
        printf("Enter the postorder traversal: ");
        scanf("%s", postorder);

        int n = strlen(inorder);

        node *preRoot = buildtreeInPost(inorder, postorder, 0, n, n-1);
        
        printf("")
    }
