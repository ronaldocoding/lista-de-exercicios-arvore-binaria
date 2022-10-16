#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int newKey);
Node *binarySearch(Node *root, int searchedKey);
Node *searchNode(Node *root, int searchedKey, Node **parentNode);
Node *getGreatestNode(Node *root);
Node *getLeastNode(Node *root);
bool isTreeEmpty(Node *root);
bool insertNode(Node **root, Node *newNode);
bool removeNode(Node **node, int searchedKey);
void initializeTree(Node **root);
void destroyTreeAux(Node *root);
void destroyTree(Node **root, Node *rootParent);
void printInOrder(Node *root);
void printPreOrder(Node *root);
void printPosOrder(Node *root);
void printPreOrderWithParentheses(Node *root);
Node *getParentNode(Node *root, int searchedValue);

int main() {
    Node *bst;
    initializeTree(&bst);
    insertNode(&bst, createNode(49));
    insertNode(&bst, createNode(28));
    insertNode(&bst, createNode(83));
    insertNode(&bst, createNode(18));
    insertNode(&bst, createNode(40));
    insertNode(&bst, createNode(71));
    insertNode(&bst, createNode(97));
    insertNode(&bst, createNode(69));
    insertNode(&bst, createNode(72));
    insertNode(&bst, createNode(92));
    insertNode(&bst, createNode(99));
    insertNode(&bst, createNode(44));
    insertNode(&bst, createNode(32));
    insertNode(&bst, createNode(11));
    insertNode(&bst, createNode(19));

    Node *parentNode = getParentNode(bst, 71);
    printf("%d\n\n", parentNode->key);
 
    return 0;
}

Node *createNode(int newKey) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = newKey;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *binarySearch(Node *root, int searchedKey) {
    if(isTreeEmpty(root)) {
        return NULL;
    } else {
        if(root->key == searchedKey) {
            return root;
        } else {
            if(searchedKey > root->key) {
                return binarySearch(root->right, searchedKey);
            } else {
                return binarySearch(root->left, searchedKey);
            }
        }
    }
}

Node *searchNode(Node *root, int searchedKey, Node **parentNode) {
    *parentNode = NULL;
    if(isTreeEmpty(root)) {
        return NULL;
    } else {
        Node *currentNode = root;
        while(currentNode != NULL) {
            if(currentNode->key == searchedKey) {
                return currentNode;
            } else {
                *parentNode = currentNode;
                if(searchedKey > currentNode->key) {
                    currentNode = currentNode->right;
                } else {
                    currentNode = currentNode->left;
                }
            }
        }
    }
    return NULL;
}

Node *getGreatestNode(Node *root) {
    if(isTreeEmpty(root)) return NULL;
    if(isTreeEmpty(root->right)) return root;
    return getGreatestNode(root->right);
}

Node *getLeastNode(Node *root) {
    if(isTreeEmpty(root)) return NULL;
    if(isTreeEmpty(root->left)) return root;
    return getLeastNode(root->left);
}

Node *greaterLeft(Node *node, Node **previous) {
    *previous = node;
    node = node->left;
    while(node->right) {
        *previous = node;
        node = node->right;
    }
    return node;
}

bool isTreeEmpty(Node *root) {
    return root == NULL;
}

bool insertNode(Node **root, Node *newNode) {
    if(isTreeEmpty(*root)) {
        *root = newNode;
        return true;
    } else {
        if(newNode->key > (*root)->key) {
            if(isTreeEmpty((*root)->right)) {
                (*root)->right = newNode;
                return true;
            } else {
                return insertNode(&(*root)->right, newNode);
            }
        } else {
            if(isTreeEmpty((*root)->left)) {
                (*root)->left = newNode;
                return true;
            } else {
                return insertNode(&(*root)->left, newNode);
            }
        }
    }
}

bool removeNode(Node **root, int searchedKey) {
    Node *current, *parentNode, *substitute, *substituteParent;
    substitute = NULL;
    current = searchNode(*root, searchedKey, &parentNode);
    if(current == NULL) return false;
    if(!current->left || !current->right) {
        if(!current->left) substitute = current->right;
        if(!current->right) substitute = current->left;
        if(!parentNode) {
            *root = substitute;
        } else {
            if(parentNode->key > searchedKey) parentNode->left = substitute;
            else parentNode->right = substitute;
        }
        free(current);
        return true;
    } else {
        substitute = greaterLeft(current, &substituteParent);
        current->key = substitute->key;
        if(substituteParent->left == substitute) {
            substituteParent->left = substitute->left;
        } else {
            substituteParent->right = substitute->right;
        }
        free(substitute);
        return true;
    }
}

void initializeTree(Node **root) {
    *root = NULL;
}

void destroyTreeAux(Node *root) {
    if(!isTreeEmpty(root)) {
        destroyTreeAux(root->left);
        destroyTreeAux(root->right);
        root->left = NULL;
        root->right = NULL;
        free(root);
    }
}

void destroyTree(Node **root, Node *rootParent) {
    destroyTreeAux(*root);
    Node *parentNode;
    searchNode(rootParent, (*root)->key, &parentNode);
    if(!isTreeEmpty(parentNode)) {
        if(parentNode->left == *root) parentNode->left = NULL;
        else parentNode->right = NULL;
    }
    *root = NULL;
}

void printInOrder(Node *root) {
    if(isTreeEmpty(root)) return;
    printInOrder(root->left);
    printf("%d ", root->key);
    printInOrder(root->right);
}

void printPreOrder(Node *root) {
    if(isTreeEmpty(root)) return;
    printf("%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPosOrder(Node *root) {
    if(isTreeEmpty(root)) return;
    printPosOrder(root->left);
    printPosOrder(root->right);
    printf("%d ", root->key);
}

void printPreOrderWithParentheses(Node *root) {
    if(isTreeEmpty(root)) return;
    printf("%d ", root->key);
    printf(" (");
    printPreOrderWithParentheses(root->left);
    printPreOrderWithParentheses(root->right);
    printf(") ");
}

Node *getParentNode(Node *root, int searchedValue) {
    if(root == NULL) return NULL;
    Node *nodeParent = NULL;
    Node *current = root;
    while(current != NULL) {
        if(current->key > searchedValue) {
            nodeParent = current;
            current = current->left;
        } else if(current->key == searchedValue) {
            return nodeParent;
        } else {
            nodeParent = current;
            current = current->right;
        }
    }
    return nodeParent;
}
