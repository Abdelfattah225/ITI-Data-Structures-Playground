#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Queue structure to hold tree node pointers
typedef struct Queue
{
    Node **array; // Array of Node pointers
    int front;
    int rear;
    int capacity;
} Queue;

// Create a queue
Queue *createQueue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->array = (Node **)malloc(capacity * sizeof(Node *));

    if (queue->array == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    return queue;
}

// Check if queue is empty
int isEmpty(Queue *queue)
{
    return queue->rear < queue->front;
}

// Add node pointer to queue
void enqueue(Queue *queue, Node *node)
{
    queue->rear++;
    queue->array[queue->rear] = node;
}

// Remove and return front node pointer
Node *dequeue(Queue *queue)
{
    Node *node = queue->array[queue->front];
    queue->front++;
    return node;
}

// Free queue memory
void freeQueue(Queue *queue)
{
    free(queue->array);
    free(queue);
}

// Function to create a new node

Node *createNode(int val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void inorderTraversal(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    inorderTraversal(node->left);
    printf("%d\t", node->data);
    inorderTraversal(node->right);
}

void preorderTraversal(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%d\t", node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void postorderTraversal(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    printf("%d\t", node->data);
}

void breadthFirstTraversal(Node *root, int capacityOfQueue)
{
    // Handle empty tree
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return;
    }

    Queue *Q = createQueue(capacityOfQueue);
    enqueue(Q, root);
    while (!isEmpty(Q))
    {
        Node *dequeueNode = dequeue(Q);
        printf("%d\t", dequeueNode->data);
        if (dequeueNode->left != NULL)
            enqueue(Q, dequeueNode->left);
        if (dequeueNode->right != NULL)
            enqueue(Q, dequeueNode->right);
    }
    freeQueue(Q);
}

void printHeader(const char *title)
{
    printf("\n");
    printf("================================\n");
    printf("  %s\n", title);
    printf("================================\n");
    printf("  ");
}

void printTreeStructure()
{
    printf("\n");
    printf("        Tree Structure\n");
    printf("        ==============\n");
    printf("              20\n");
    printf("             /  \\\n");
    printf("           10    30\n");
    printf("           /    /  \\\n");
    printf("          5    25   35\n");
}

Node *insert(Node *root, int val)
{
    if (root == NULL)
    {
        root = createNode(val);
        return root;
    }
    if (val > root->data)
    {
        root->right = insert(root->right, val);
    }
    else if (val <= root->data)
    {
        root->left = insert(root->left, val);
    }

    return root;
}

Node *search(Node *root, int val)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (val == root->data)
    {
        return root;
    }
    if (val > root->data)
    {
        return search(root->right, val);
    }
    else if (val <= root->data)
    {
        return search(root->left, val);
    }

    return root;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Node *root)
{
    // Base case: empty tree
    if (root == NULL)
    {
        return 0;
    }

    // Recursive case
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + max(leftHeight, rightHeight);
}

int countNodes(Node *root)
{
    // Base case: empty tree
    if (root == NULL)
    {
        return 0;
    }
    int leftcnt = countNodes(root->left);
    int rightcnt = countNodes(root->right);

    return leftcnt + rightcnt + 1;
}

Node* findMin(Node* root){
    if(root==NULL)
    {
        return NULL;
    }
    while (root->left  != NULL)
    {
        root = root->left;
    }
    return root;
}


Node* deleteNode(Node* root, int val) {
    // Step 1: Base case - tree is empty
    if (root == NULL) {
        return NULL;
    }
    
    // Step 2: Search for the node
    if (val < root->data) {
        // Go left
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data) {
        // Go right
        root->right = deleteNode(root->right, val);
    }
    else {
        
        // Case 1: No children (leaf)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // Case 2a: Only right child
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        
        // Case 2b: Only left child
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 3: Two children
        else {
            // Find inorder successor (min in right subtree)
            Node* successor = findMin(root->right);
            
            // Copy successor's value to current node
            root->data = successor->data;
            
            // Delete the successor from right subtree
            root->right = deleteNode(root->right, successor->data);
        }
    }
    
    return root;
}

// int main(void)
// {
//     Node *root = createNode(20);
//     root->left = createNode(10);
//     root->left->left = createNode(5);

//     root->right = createNode(30);
//     root->right->left = createNode(25);
//     root->right->right = createNode(35);

//     printTreeStructure();

//     printHeader("Inorder (Left -> Root -> Right)");
//     inorderTraversal(root);

//     printHeader("Preorder (Root -> Left -> Right)");
//     preorderTraversal(root);

//     printHeader("Postorder (Left -> Right -> Root)");
//     postorderTraversal(root);

//     printHeader("Breadth-First (Level by Level)");
//     breadthFirstTraversal(root, 6);

//     printf("\n\n");

// int main(void)
// {
//     Node *root = NULL;

//     root = insert(root, 20);
//     root = insert(root, 10);
//     root = insert(root, 30);
//     root = insert(root, 5);
//     root = insert(root, 25);
//     root = insert(root, 35);

//     printf("Inorder: ");
//     inorderTraversal(root);
//     printf("\n");

//     // Test searchNode
//     Node *result = search(root, 25);
//     if (result != NULL)
//         printf("Found node with value: %d\n", result->data);
//     else
//         printf("Node 25 not found!\n");

//     result = search(root, 100);
//     if (result != NULL)
//         printf("Found node with value: %d\n", result->data);
//     else
//         printf("Node 100 not found!\n");

//     printf("Tree Height: %d\n", height(root)); // Expected: 3

//     printf("Total Nodes: %d\n", countNodes(root));      // Expected: 6
//     printf("Empty Tree Nodes: %d\n", countNodes(NULL)); // Expected: 0
//     return 0;
// }


int main(void) {
    Node *root = NULL;

    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 25);
    root = insert(root, 35);

    printf("Before delete:\n");
    printf("Inorder: ");
    inorderTraversal(root);
    printf("\nCount: %d\n", countNodes(root));

    // Delete leaf node
    root = deleteNode(root, 5);
    printf("\nAfter deleting 5 (leaf):\n");
    printf("Inorder: ");
    inorderTraversal(root);
    printf("\n");

    // Delete node with one child
    root = deleteNode(root, 10);
    printf("\nAfter deleting 10 (no children now):\n");
    printf("Inorder: ");
    inorderTraversal(root);
    printf("\n");

    // Delete node with two children
    root = deleteNode(root, 30);
    printf("\nAfter deleting 30 (two children):\n");
    printf("Inorder: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("\nFinal count: %d\n", countNodes(root));

    return 0;
}