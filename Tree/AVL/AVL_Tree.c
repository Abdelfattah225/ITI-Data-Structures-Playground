#include <stdio.h>
#include <stdlib.h>
typedef struct AVL_Tree
{
    /* === */

    int data;
    int height;
    struct AVL_Tree *left;
    struct AVL_Tree *right;

} AVL_Tree;

AVL_Tree *createNode(int value)
{
    // Allocate memroy for new node;
    AVL_Tree *newNode = (AVL_Tree *)malloc(sizeof(AVL_Tree));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int getHeight(AVL_Tree *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(AVL_Tree *node)
{
    int BF;
    BF = getHeight(node->left) - getHeight(node->right);
    return BF;
}

AVL_Tree *rightRotate(AVL_Tree *z)
{

    // Step 1: Save z's left child in variable y
    AVL_Tree *y = z->left;

    // Step 2: Save y's right child (might be NULL, that's ok)
    AVL_Tree *T3 = y->right;

    // Step 3: Make z become y's right child
    y->right = z;

    // Step 4: Make T3 become z's left child
    z->left = T3;

    // Step 5: Update heights (z first, then y)
    z->height = max(getHeight(z->left), getHeight(z->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Step 6: Return new root
    return y;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

AVL_Tree *leftRotate(AVL_Tree *z)
{
    // Your code here
    // Hint: swap "left" and "right" from rightRotate

    AVL_Tree *y = z->right;

    AVL_Tree *T2 = y->left;

    y->left = z;

    z->right = T2;

    z->height = max(getHeight(z->left), getHeight(z->right)) + 1;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVL_Tree *LR_Rotate(AVL_Tree *node)
{
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

AVL_Tree *RL_Rotate(AVL_Tree *node)
{
    node->right = rightRotate(node->right);
    return leftRotate(node);
}
AVL_Tree *insert(AVL_Tree *node, int value)
{

    // Empty spot found, create new node
    if (node == NULL)
        return createNode(value);

    // Value is smaller → go left
    if (value < node->data)
        node->left = insert(node->left, value);

    // Value is larger → go right
    else if (value > node->data)
        node->right = insert(node->right, value);

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Part C: Get balance factor
    int bf = getBalance(node);

    // LL Case
    if (bf > 1 && value < node->left->data)
        return rightRotate(node);

    // LR Case
    if (bf > 1 && value > node->left->data)
        return LR_Rotate(node);

    // RR Case
    if (bf < -1 && value > node->right->data)
        return leftRotate(node);

    // RL Case
    if (bf < -1 && value < node->right->data)
        return RL_Rotate(node);

    return node;
}

AVL_Tree *minValueNode(AVL_Tree *node)
{
    AVL_Tree *current = node;

    // Keep going left until we reach the end
    while (current->left != NULL)
        current = current->left;

    return current;
}

AVL_Tree *delete(AVL_Tree *node, int value)
{

    // Step 1: Find the node (like BST search)
    if (node == NULL)
        return node;

    if (value < node->data)
        node->left = delete(node->left, value);

    else if (value > node->data)
        node->right = delete(node->right, value);

    // Step 2: Found the node to delete!
    else
    {

        // Case 1 & 2: No child or one child
        if (node->left == NULL)
        {
            AVL_Tree *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            AVL_Tree *temp = node->left;
            free(node);
            return temp;
        }

        // Case 3: Two children
        AVL_Tree *temp = minValueNode(node->right);

        node->data = temp->data;

        node->right = delete(node->right, node->data);
    }

    // Update height
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Get balance factor
    int bf = getBalance(node);

    // LL Case
    if (bf > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // LR Case
    if (bf > 1 && getBalance(node->left) < 0)
        return LR_Rotate(node);

    // RR Case
    if (bf < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // RL Case
    if (bf < -1 && getBalance(node->right) > 0)
        return RL_Rotate(node);
    return node;
}