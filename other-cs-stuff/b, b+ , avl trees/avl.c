#include<stdio.h>
#include<stdlib.h>

typedef struct bintreenode{
    int data;
    struct bintreenode* left;
    struct bintreenode* right;
    int height;
}node;

int height(node* n) {
    return (n == NULL) ? 0 : n->height;
}

int max(int a, int b) {
    return (a>b) ? a : b;
}

node *newnode(int data) {
    node* newnode = malloc(sizeof(node));

    if(newnode==NULL) {
        printf("Allocation failed");
        return NULL;
    }

    newnode->data = data;
    newnode->left = newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

node* rotateright(node* y) {
    node* x= y->left;
    node* z= x->right;

    x->right=y;
    y->left = z;

    y->height = max(height(y->left), height(y->right)) +1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

node* rotateleft(node* y) {
    node* x = y->right;
    node* z = x->left;

    x->left = y;
    y->right = z;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

int getbalance(node* n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

node* insert(node* n, int key) {
    if(n==NULL) return newnode(key);

    if(key < n->data)
    n->left = insert(n->left, key);

    else if (key > n->data) 
    n->right = insert(n->right, key);

    else 
    return n;

    n->height = max(height(n->left), height(n->right)) + 1;
    int balance = getbalance(n);

    if(balance>1 && key < n->left->data)
    return rotateright(n);

    if(balance < -1 && key > n->right->data) 
    return rotateleft(n);

    if(balance>1 && key > n->left->data) {
    n->left = rotateleft(n->left);
    return rotateright(n);
    }

    if(balance < -1 && key < n->right->data) {
        n->right = rotateright(n->right);
        return rotateleft(n);
    }

    return n;
}

node* minvaluenode(node *root) {
    node *curr = root;
    while(curr->left!=NULL) 
    curr = curr->left;

    return curr;
}

node* deletenode(node* root, int key) {
    if(root ==NULL) return root;

    if(key < root->data)
    root->left = deletenode(root->left, key);

    else if(key > root->data) 
    root->right = deletenode(root->right, key);

    else{
        if(root->left == NULL || root->right == NULL ) {
            node* temp = root->left ? root->left : root->right;

            if(temp==NULL) {
                temp = root;
                root = NULL;
            }

            else {
                *root = *temp;
            }

            free(temp);
        }

        else {
            node* temp = minvaluenode(root->right);
            root->data = temp->data;
            root->right = deletenode(root->right, temp->data);
        }
    }

    if(root==NULL) return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getbalance(root);

    if(balance>1 && key< root->left->data) 
    return rotateright(root);

    if(balance>1 && key >root->left->data) {
        root->left = rotateleft(root->left);
        return rotateright(root);
    }

    if(balance<-1 && key>root->right->data)
    return rotateleft(root);

    if(balance<-1 && key<root->right->data){
        root->right = rotateright(root->right);
        return rotateleft(root);
    }

    return root;

    
}

void preorder(node* n) {
    if(n == NULL) return;
    
    printf("%d ", n->data);
    preorder(n->left);
    preorder(n->right);
}

int main() {
    node* n = NULL;

    int choice, val;

    do {
        printf(("\n1.Insert\n2.Display tree (preorder)\n3.Delete a node\n4.Exit\n\n"));
        
scanf("%d", &choice);

switch(choice) {
    case 1 : {
        printf("Enter the value: ");
        scanf("%d", &val);

        n = insert(n, val);
        break;
    }

    case 2 : {
        printf("Tree: ");
        preorder(n);
        printf("\n");
        break;
    }

    case 3 : {
        int key;
        printf("Enter the key: ");
        scanf("%d", &key);
       n = deletenode(n, key);
    }

    case 4 : {
        printf("Exiting.....\n");
    }

    default : 
    printf("Invalid choice\n");
}}
    while(choice!=4);

    return 0;
    
}