#include <stdlib.h>
#include <stdio.h>

/*
 * ============================================================================
 * CIRCULAR DOUBLY LINKED LIST IMPLEMENTATION
 * ============================================================================
 * 
 * This file implements a Circular Doubly Linked List (CDLL) data structure.
 * 
 * Properties:
 * - Each node has pointers to both next and previous nodes
 * - The last node's 'next' points to the head (first node)
 * - The head's 'prev' points to the last node (tail)
 * - Allows traversal in both forward and backward directions
 * - No NULL pointers in a non-empty list (circular nature)
 * 
 * Operations supported:
 * - Insert at beginning: O(1)
 * - Insert at end: O(1)
 * - Delete from beginning: O(1)
 * - Delete from end: O(1)
 * - Print forward/backward: O(n)
 * ============================================================================
 */

/*
 * Structure definition for a node in the Circular Doubly Linked List
 * 
 * Members:
 *   data - Integer value stored in the node
 *   next - Pointer to the next node in the list
 *   prev - Pointer to the previous node in the list
 */
struct DCNode
{
    int data;
    struct DCNode *next;
    struct DCNode *prev;
};

/* 
 * Global head pointer - points to the first node in the list
 * NULL indicates an empty list
 */
struct DCNode *head = NULL;

/*
 * Creates a new node with the given value
 * 
 * Parameters:
 *   value - The integer value to store in the new node
 * 
 * Returns:
 *   Pointer to the newly created node
 * 
 * Note: The new node's next and prev pointers are initialized to NULL
 *       The caller is responsible for setting up proper links
 */
struct DCNode *createNode(int value)
{
    /* Allocate memory for the new node */
    struct DCNode *newNode = (struct DCNode *)malloc(sizeof(struct DCNode));

    /* Initialize node members */
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

/*
 * Inserts a new node at the beginning of the list
 * 
 * Parameters:
 *   value - The integer value to insert
 * 
 * Returns:
 *   Pointer to the newly inserted node
 * 
 * Algorithm:
 *   1. Create a new node
 *   2. If list is empty, make the node point to itself (both next and prev)
 *   3. Otherwise:
 *      - Get the tail (last node) via head->prev
 *      - Insert new node between tail and current head
 *      - Update head to point to new node
 */
struct DCNode *insertAtBeginning(int value)
{
    struct DCNode *node = createNode(value);

    /* Special case: Empty list - node becomes the only element */
    if (head == NULL)
    {
        /* Single node points to itself in both directions */
        node->next = node;
        node->prev = node;

        head = node;
        return node;
    }
    
    /* Get the tail node (last node in the circular list) */
    struct DCNode *tail = head->prev;

    /* Link new node to the current head */
    node->next = head;
    head->prev = node;
    
    /* Link new node to the tail (maintaining circular property) */
    node->prev = tail;
    tail->next = node;

    /* Update head to point to the new first node */
    head = node;
    
    return node;
}

/*
 * Inserts a new node at the end of the list
 * 
 * Parameters:
 *   value - The integer value to insert
 * 
 * Returns:
 *   Pointer to the newly inserted node
 * 
 * Algorithm:
 *   1. Create a new node
 *   2. If list is empty, make the node point to itself
 *   3. Otherwise:
 *      - Get the current tail via head->prev
 *      - Insert new node between tail and head
 *      - New node becomes the new tail
 */
struct DCNode *insertAtEnd(int value)
{
    struct DCNode *node = createNode(value);

    /* Special case: Empty list - node becomes the only element */
    if (head == NULL)
    {
        /* Single node points to itself in both directions */
        node->next = node;
        node->prev = node;

        head = node;
        return node;
    }
    
    /* Get the current tail node */
    struct DCNode *tail = head->prev;

    /* Link new node to the tail and head */
    node->prev = tail;
    node->next = head;

    /* Update tail's next to point to new node */
    tail->next = node;

    /* Update head's prev to point to new tail */
    head->prev = node;

    return node;
}

/*
 * Deletes the first node from the list
 * 
 * Returns:
 *   The data value of the deleted node
 *   -1 if the list is empty
 * 
 * Algorithm:
 *   1. If list is empty, return -1
 *   2. If only one node exists, free it and set head to NULL
 *   3. Otherwise:
 *      - Save the current head for deletion
 *      - Update head to point to next node
 *      - Relink new head with tail to maintain circular property
 *      - Free the old head
 */
int deleteFromBeginning()
{
    int deletedval;
    
    /* Case 1: Empty list */
    if (head == NULL)
    {
        return -1;
    }
    
    /* Case 2: Single node in the list (node points to itself) */
    if (head->next == head)
    {
        struct DCNode *temp = head;
        deletedval = temp->data;
        free(temp);
        head = NULL;  /* List becomes empty */
        return deletedval;
    }

    /* Case 3: Multiple nodes in the list */
    struct DCNode *temp = head;           /* Save node to delete */
    struct DCNode *tail = head->prev;     /* Get the tail node */
    
    head = head->next;                    /* Move head to next node */
    head->prev = tail;                    /* New head's prev points to tail */
    tail->next = head;                    /* Tail's next points to new head */

    deletedval = temp->data;
    free(temp);                           /* Free the old head */
    
    return deletedval;
}

/*
 * Deletes the last node from the list
 * 
 * Returns:
 *   The data value of the deleted node
 *   -1 if the list is empty
 * 
 * Algorithm:
 *   1. If list is empty, return -1
 *   2. If only one node exists, free it and set head to NULL
 *   3. Otherwise:
 *      - Get the current tail (head->prev)
 *      - Update the new tail (second to last node)
 *      - Relink new tail with head to maintain circular property
 *      - Free the old tail
 */
int deleteFromEnd()
{
    int deletedval;
    
    /* Case 1: Empty list */
    if (head == NULL)
    {
        return -1;
    }
    
    /* Case 2: Single node in the list */
    if (head->next == head)
    {
        struct DCNode *temp = head;
        deletedval = temp->data;
        free(temp);
        head = NULL;  /* List becomes empty */
        return deletedval;
    }

    /* Case 3: Multiple nodes in the list */
    struct DCNode *tail = head->prev;     /* Get the current tail */
    struct DCNode *temp = tail;           /* Save node to delete */

    tail = tail->prev;                    /* New tail is the second to last node */
    tail->next = head;                    /* New tail's next points to head */
    head->prev = tail;                    /* Head's prev points to new tail */

    deletedval = temp->data;
    free(temp);                           /* Free the old tail */

    return deletedval;
}

/*
 * Prints all elements of the list in forward direction
 * (from head towards tail)
 * 
 * Uses do-while loop since we need to traverse the entire circular list
 * starting and ending at head
 */
void printForward()
{
    /* Handle empty list */
    if (head == NULL)
    {
        printf("LL is empty\n");
        return;
    }
    
    struct DCNode *curr = head;
    
    /* Traverse until we come back to head */
    do
    {
        printf("%d\t", curr->data);
        curr = curr->next;
    } while (curr != head);
    
    printf("\n");  /* Added newline for better formatting */
}

/*
 * Prints all elements of the list in backward direction
 * (from tail towards head)
 * 
 * Starts from tail (head->prev) and traverses using prev pointers
 * Uses do-while loop to handle circular traversal
 */
void printBackward()
{
    /* Handle empty list */
    if (head == NULL)
    {
        printf("LL is empty\n");
        return;
    }
    
    struct DCNode *curr = head->prev;  /* Start from tail */
    
    /* Traverse backward until we come back to tail */
    do
    {
        printf("%d\t", curr->data);
        curr = curr->prev;
    } while (curr != head->prev);
    
    printf("\n");  /* Added newline for better formatting */
}

/*
 * ============================================================================
 * MAIN FUNCTION - Test Driver
 * ============================================================================
 * 
 * Comprehensive test suite demonstrating all operations:
 * - Insert at end
 * - Insert at beginning
 * - Delete from beginning
 * - Delete from end
 * - Forward and backward traversal
 * - Edge cases (empty list, single element)
 */
int main() {
    printf("=== CIRCULAR DOUBLY LINKED LIST DEMO ===\n\n");
    
    /* 
     * Test 1: Insert at end
     * Building list: 10 <-> 20 <-> 30 <-> (circular back to 10)
     */
    printf("--- Inserting 10, 20, 30 at end ---\n");
    insertAtEnd(10);
    insertAtEnd(20);
    insertAtEnd(30);
    printf("Forward:  ");
    printForward();   /* Expected: 10  20  30 */
    printf("Backward: ");
    printBackward();  /* Expected: 30  20  10 */
    
    /* 
     * Test 2: Insert at beginning
     * List becomes: 5 <-> 10 <-> 20 <-> 30 <-> (circular)
     */
    printf("\n--- Inserting 5 at beginning ---\n");
    insertAtBeginning(5);
    printf("Forward:  ");
    printForward();   /* Expected: 5  10  20  30 */
    printf("Backward: ");
    printBackward();  /* Expected: 30  20  10  5 */
    
    /* 
     * Test 3: Insert at beginning again
     * List becomes: 1 <-> 5 <-> 10 <-> 20 <-> 30 <-> (circular)
     */
    printf("\n--- Inserting 1 at beginning ---\n");
    insertAtBeginning(1);
    printf("Forward:  ");
    printForward();   /* Expected: 1  5  10  20  30 */
    
    /* 
     * Test 4: Delete from beginning
     * Removes 1, list becomes: 5 <-> 10 <-> 20 <-> 30 <-> (circular)
     */
    printf("\n--- Deleting from beginning ---\n");
    int deleted = deleteFromBeginning();
    printf("Deleted: %d\n", deleted);  /* Expected: 1 */
    printf("Forward:  ");
    printForward();   /* Expected: 5  10  20  30 */
    
    /* 
     * Test 5: Delete from end
     * Removes 30, list becomes: 5 <-> 10 <-> 20 <-> (circular)
     */
    printf("\n--- Deleting from end ---\n");
    deleted = deleteFromEnd();
    printf("Deleted: %d\n", deleted);  /* Expected: 30 */
    printf("Forward:  ");
    printForward();   /* Expected: 5  10  20 */
    printf("Backward: ");
    printBackward();  /* Expected: 20  10  5 */
    
    /* 
     * Test 6: Delete until empty
     * Tests deletion down to single element and empty list
     */
    printf("\n--- Deleting all nodes ---\n");
    deleteFromBeginning();  /* Removes 5, list: 10 <-> 20 */
    deleteFromEnd();        /* Removes 20, list: 10 (single node) */
    printf("Forward:  ");
    printForward();         /* Expected: 10 */
    deleteFromBeginning();  /* Removes 10, list becomes empty */
    printf("Forward:  ");
    printForward();         /* Expected: LL is empty */
    
    /* 
     * Test 7: Delete from empty list
     * Edge case - should return -1
     */
    printf("\n--- Attempting delete from empty list ---\n");
    deleted = deleteFromBeginning();  /* Returns -1 */
    printf("Delete result: %d\n", deleted);  /* Expected: -1 */
    
    return 0;
}