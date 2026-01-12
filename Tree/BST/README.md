# Binary Search Tree (BST) - Complete Guide 🌳

## What is a BST?

A Binary Search Tree is a data structure where:
- Each node has **at most 2 children**
- **Left child** < Parent
- **Right child** > Parent

```
        20
       /  \
      10   30
     /    /  \
    5    25   35
```

---

## Node Structure

```c
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;
```

---

## Core Operations

### 1. Create Node
```c
Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
```

---

### 2. Insert
**Logic:** Go left if smaller, right if larger

```c
Node* insert(Node* root, int val) {
    if (root == NULL) return createNode(val);
    
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    
    return root;
}
```

---

### 3. Search
**Logic:** Compare and traverse left/right

```c
Node* search(Node* root, int val) {
    if (root == NULL || root->data == val) return root;
    
    if (val < root->data)
        return search(root->left, val);
    else
        return search(root->right, val);
}
```

---

### 4. Delete
**Three cases:**

| Case | Condition | Action |
|------|-----------|--------|
| 1 | No children | Return NULL |
| 2 | One child | Return that child |
| 3 | Two children | Replace with inorder successor |

```c
Node* deleteNode(Node* root, int val) {
    if (root == NULL) return NULL;
    
    if (val < root->data)
        root->left = deleteNode(root->left, val);
    else if (val > root->data)
        root->right = deleteNode(root->right, val);
    else {
        // Case 1 & 2
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3
        Node* successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }
    return root;
}
```

---

## Traversals

### Depth-First (Recursive)

| Type | Order | Output (for tree above) |
|------|-------|------------------------|
| **Inorder** | Left → Root → Right | 5, 10, 20, 25, 30, 35 |
| **Preorder** | Root → Left → Right | 20, 10, 5, 30, 25, 35 |
| **Postorder** | Left → Right → Root | 5, 10, 25, 35, 30, 20 |

```c
void inorder(Node* n)   { if(n) { inorder(n->left);  printf("%d ", n->data); inorder(n->right);  }}
void preorder(Node* n)  { if(n) { printf("%d ", n->data); preorder(n->left);  preorder(n->right); }}
void postorder(Node* n) { if(n) { postorder(n->left); postorder(n->right); printf("%d ", n->data);}}
```

### Breadth-First (Queue-based)

**Output:** 20, 10, 30, 5, 25, 35 (level by level)

```c
void bfs(Node* root) {
    Queue* q = createQueue(100);
    enqueue(q, root);
    
    while (!isEmpty(q)) {
        Node* node = dequeue(q);
        printf("%d ", node->data);
        if (node->left)  enqueue(q, node->left);
        if (node->right) enqueue(q, node->right);
    }
    freeQueue(q);
}
```

---

## Utility Functions

```c
// Find minimum (leftmost node)
Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

// Calculate height
int height(Node* root) {
    if (!root) return 0;
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

// Count nodes
int count(Node* root) {
    if (!root) return 0;
    return 1 + count(root->left) + count(root->right);
}

// Free entire tree (use postorder!)
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
```

---

## Time Complexity

| Operation | Average | Worst (unbalanced) |
|-----------|---------|-------------------|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Delete | O(log n) | O(n) |
| Traversal | O(n) | O(n) |

---

## Quick Reference

```
BST Property:    left < root < right
Sorted Output:   Use Inorder traversal
Copy Tree:       Use Preorder traversal
Delete Tree:     Use Postorder traversal
Level Order:     Use Queue (BFS)
```

---

## Common Mistakes to Avoid

| Mistake | Fix |
|---------|-----|
| Not saving insert result | `root->left = insert(root->left, val)` |
| Modifying tree in search | Don't assign, just return |
| Forgetting NULL checks | Always check before accessing |
| Memory leaks | Free nodes when deleting |

