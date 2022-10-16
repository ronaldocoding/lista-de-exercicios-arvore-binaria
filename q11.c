#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0

typedef struct NodeTree {
    int key;
    struct NodeTree *left;
    struct NodeTree *right;
} NodeTree;

typedef struct NodeQueue {
    NodeTree  *nodeTree;
    struct NodeQueue *next;
} NodeQueue;

// Binary Tree functions
NodeTree *createNode(int newKey);
NodeTree *binarySearch(NodeTree *root, int searchedKey);
NodeTree *searchNode(NodeTree *root, int searchedKey, NodeTree **parentNode);
NodeTree *getGreatestNode(NodeTree *root);
NodeTree *getLeastNode(NodeTree *root);
bool isTreeEmpty(NodeTree *root);
bool insertNode(NodeTree **root, NodeTree *newNode);
bool removeNode(NodeTree **node, int searchedKey);
void initializeTree(NodeTree **root);
void destroyTreeAux(NodeTree *root);
void destroyTree(NodeTree **root, NodeTree *rootParent);
void printInOrder(NodeTree *root);
void printPreOrder(NodeTree *root);
void printPosOrder(NodeTree *root);
void printPreOrderWithParentheses(NodeTree *root);
int getTreeHeightRecursively(NodeTree *root);
int getTreeHeightInterative(NodeTree *root);

// Queue functions
NodeQueue *createNodeQueue(NodeTree *newNode);
void enqueue(NodeQueue **head, NodeQueue **tail, NodeTree *newNode);
NodeQueue *dequeue(NodeQueue **head);
int getQueueSize(NodeQueue **head, NodeQueue **tail);

int main() {
    NodeTree *bst;
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
    printPosOrder(bst);
    printf("\n");
    printPreOrder(bst);
    printf("\n");
    printInOrder(bst);
    printf("\n");
    NodeTree *searchedNode = binarySearch(bst, 71);
    printPreOrder(searchedNode);
    printf("\n");
    NodeTree *parentNode;
    NodeTree *newSearchedNode = searchNode(bst, 83, &parentNode);
    printPreOrder(newSearchedNode);
    printf("\n");
    printPreOrder(parentNode);
    printf("\n");
    printPreOrderWithParentheses(bst);
    printf("\n");
    destroyTree(&newSearchedNode, bst);
    printPreOrder(bst);
    printf("\n");
    NodeTree *greatestNode = getGreatestNode(bst);
    printf("%d\n", greatestNode->key);
    NodeTree *leastNode = getLeastNode(bst);
    printf("%d\n", leastNode->key);
    printPreOrderWithParentheses(bst);
    printf("\n");
    printf("\n");

    NodeTree *newBst = NULL;
    insertNode(&newBst, createNode(15));
    insertNode(&newBst, createNode(11));
    insertNode(&newBst, createNode(28));
    insertNode(&newBst, createNode(6));
    insertNode(&newBst, createNode(13));
    insertNode(&newBst, createNode(18));
    insertNode(&newBst, createNode(32));
    insertNode(&newBst, createNode(30));
    insertNode(&newBst, createNode(35));
    insertNode(&newBst, createNode(17));
    insertNode(&newBst, createNode(16));
    insertNode(&newBst, createNode(16));
    insertNode(&newBst, createNode(16));
    insertNode(&newBst, createNode(16));
    insertNode(&newBst, createNode(16));
    insertNode(&newBst, createNode(16));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));
    insertNode(&newBst, createNode(5));

    int treeHeight = getTreeHeightRecursively(newBst);
    printf("A altura da árvore é: %d\n\n", treeHeight);

    NodeTree *newBst2 = NULL;
    insertNode(&newBst2, createNode(15));
    insertNode(&newBst2, createNode(6));
    insertNode(&newBst2, createNode(21));
    insertNode(&newBst2, createNode(3));
    insertNode(&newBst2, createNode(8));
    insertNode(&newBst2, createNode(18));
    insertNode(&newBst2, createNode(25));
    insertNode(&newBst2, createNode(16));
    insertNode(&newBst2, createNode(20));

    treeHeight = getTreeHeightInterative(newBst2);
    printf("A altura da árvore é: %d\n\n", treeHeight);

    return 0;
}

NodeTree *createNode(int newKey) {
    NodeTree *newNode = (NodeTree *) malloc(sizeof(NodeTree));
    newNode->key = newKey;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

NodeTree *binarySearch(NodeTree *root, int searchedKey) {
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

NodeTree *searchNode(NodeTree *root, int searchedKey, NodeTree **parentNode) {
    *parentNode = NULL;
    if(isTreeEmpty(root)) {
        return NULL;
    } else {
        NodeTree *currentNode = root;
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

NodeTree *getGreatestNode(NodeTree *root) {
    if(isTreeEmpty(root)) return NULL;
    if(isTreeEmpty(root->right)) return root;
    return getGreatestNode(root->right);
}

NodeTree *getLeastNode(NodeTree *root) {
    if(isTreeEmpty(root)) return NULL;
    if(isTreeEmpty(root->left)) return root;
    return getLeastNode(root->left);
}

NodeTree *greaterLeft(NodeTree *node, NodeTree **previous) {
    *previous = node;
    node = node->left;
    while(node->right) {
        *previous = node;
        node = node->right;
    }
    return node;
}

bool isTreeEmpty(NodeTree *root) {
    return root == NULL;
}

bool insertNode(NodeTree **root, NodeTree *newNode) {
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

bool removeNode(NodeTree **root, int searchedKey) {
    NodeTree *current, *parentNode, *substitute, *substituteParent;
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

void initializeTree(NodeTree **root) {
    *root = NULL;
}

void destroyTreeAux(NodeTree *root) {
    if(!isTreeEmpty(root)) {
        destroyTreeAux(root->left);
        destroyTreeAux(root->right);
        root->left = NULL;
        root->right = NULL;
        free(root);
    }
}

void destroyTree(NodeTree **root, NodeTree *rootParent) {
    destroyTreeAux(*root);
    NodeTree *parentNode;
    searchNode(rootParent, (*root)->key, &parentNode);
    if(!isTreeEmpty(parentNode)) {
        if(parentNode->left == *root) parentNode->left = NULL;
        else parentNode->right = NULL;
    }
    *root = NULL;
}

void printInOrder(NodeTree *root) {
    if(isTreeEmpty(root)) return;
    printInOrder(root->left);
    printf("%d ", root->key);
    printInOrder(root->right);
}

void printPreOrder(NodeTree *root) {
    if(isTreeEmpty(root)) return;
    printf("%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPosOrder(NodeTree *root) {
    if(isTreeEmpty(root)) return;
    printPosOrder(root->left);
    printPosOrder(root->right);
    printf("%d ", root->key);
}

void printPreOrderWithParentheses(NodeTree *root) {
    if(isTreeEmpty(root)) return;
    printf("%d ", root->key);
    printf(" (");
    printPreOrderWithParentheses(root->left);
    printPreOrderWithParentheses(root->right);
    printf(") ");
}

NodeQueue *createNodeQueue(NodeTree *newNode) {
    NodeQueue *newNodeQueue = (NodeQueue *) malloc(sizeof(NodeQueue));
    newNodeQueue->nodeTree = newNode;
    newNodeQueue->next = NULL;
    return newNodeQueue;
}

void enqueue(NodeQueue **head, NodeQueue **tail, NodeTree *newNode) {
    NodeQueue *newNodeQueue = createNodeQueue(newNode);
    if(*head == NULL) {
        *head = *tail = newNodeQueue;
    } else {
        (*tail)->next = newNodeQueue;
        *tail = newNodeQueue;
    }
    
}

NodeQueue *dequeue(NodeQueue **head) {
    if(*head == NULL) return NULL;
    NodeQueue *oldHead = *head;
    *head = (*head)->next;
    return oldHead;
}

int getQueueSize(NodeQueue **head, NodeQueue **tail) {
    int size = 0;
    NodeQueue *auxQueueHead = NULL;
    NodeQueue *auxQueueTail = NULL;
    while(*head != NULL) {
        enqueue(&auxQueueHead, &auxQueueTail, dequeue(head)->nodeTree);
        size++;
    }
    while(auxQueueHead != NULL) {
        enqueue(head, tail, dequeue(&auxQueueHead)->nodeTree);
    }
    return size;
}
 
// Recursive way
int getTreeHeightRecursively(NodeTree *root) {
    if(root == NULL) return -1;
    int leftHeight = getTreeHeightRecursively(root->left);
    int rightHeight = getTreeHeightRecursively(root->right);
    if(leftHeight > rightHeight) return leftHeight + 1;
    else return rightHeight + 1;
}

// Iterative way using queue
int getTreeHeightInterative(NodeTree *root) {
    int treeHeight = -1;
    NodeQueue *head = NULL;
    NodeQueue *tail = NULL;
    enqueue(&head, &tail, root);
    while(head != NULL) {
        treeHeight++;
        int queueSize = getQueueSize(&head, &tail);
        while(queueSize > 0) {
            NodeQueue *nodeQueue = dequeue(&head);
            if(nodeQueue->nodeTree->left != NULL)
                enqueue(&head, &tail, nodeQueue->nodeTree->left);
            if(nodeQueue->nodeTree->right != NULL)
                enqueue(&head, &tail, nodeQueue->nodeTree->right);
            queueSize--;
        }
    }
    return treeHeight;
}
