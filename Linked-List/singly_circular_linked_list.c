#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================================
 * CIRCULAR SINGLY LINKED LIST IMPLEMENTATION
 * ============================================================================
 * 
 * This file implements a Circular Singly Linked List (CSLL) data structure.
 * 
 * Properties:
 * - Each node has a pointer only to the next node (singly linked)
 * - The last node's 'next' points back to the head (first node)
 * - Traversal is only possible in forward direction
 * - No NULL pointers in a non-empty list (circular nature)
 * 
 * Operations supported:
 * - Insert at beginning: O(n) - requires traversal to find tail
 * - Insert at end: O(n) - requires traversal to find tail
 * - Delete from beginning: O(n) - requires traversal to update tail
 * - Delete from end: O(n) - requires traversal to find second-to-last
 * - Print list: O(n)
 * - Get length: O(n)
 * 
 * Note: Unlike doubly linked circular list, all operations require O(n)
 *       traversal since we don't have a direct pointer to the tail.
 * ============================================================================
 */

/*
 * Structure definition for a node in the Circular Singly Linked List
 * 
 * Members:
 *   data - Integer value stored in the node
 *   next - Pointer to the next node in the list
 */
struct CNode
{
    int data;
    struct CNode *next;
};

/* 
 * Global head pointer - points to the first node in the list
 * NULL indicates an empty list
 */
struct CNode *head = NULL;

/*
 * Creates a new node with the given value
 * 
 * Parameters:
 *   value - The integer value to store in the new node
 * 
 * Returns:
 *   Pointer to the newly created node
 * 
 * Note: The new node's next pointer is initialized to point to head.
 *       This is useful for maintaining circular property during insertion.
 */
struct CNode *createNode(int value)
{
    /* Allocate memory for the new node */
    struct CNode *newNode = (struct CNode *)malloc(sizeof(struct CNode));
    
    /* Initialize node members */
    newNode->data = value;
    newNode->next = head;  /* Points to head (will be updated during insertion) */

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
 *   2. If list is empty:
 *      - Make the node point to itself
 *      - Set head to this node
 *   3. Otherwise:
 *      - Traverse to find the tail (last node pointing to head)
 *      - Insert new node before current head
 *      - Update tail's next to point to new node
 *      - Update head to new node
 * 
 * Time Complexity: O(n) - requires full traversal to find tail
 */
struct CNode *insertAtBeginning(int value)
{
    struct CNode *node = createNode(value);
    
    /* Case 1: Empty list - node becomes the only element */
    if (head == NULL)
    {
        head = node;
        node->next = head;  /* Single node points to itself */

        return node;
    }

    /* Case 2: Non-empty list - traverse to find tail */
    struct CNode *curr = head;
    
    /* Traverse until we find the last node (node whose next is head) */
    do
    {
        curr = curr->next;
    } while (curr->next != head);
    
    /* Now curr is the tail node */
    
    /* New node's next points to current head */
    node->next = head;

    /* Tail's next now points to new node (new head) */
    curr->next = node;

    /* Update head to point to new node */
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
 *   1. Create a new node (next already points to head)
 *   2. If list is empty:
 *      - Make the node point to itself
 *      - Set head to this node
 *   3. Otherwise:
 *      - Traverse to find the tail
 *      - Set tail's next to new node
 *      - New node becomes the new tail (already points to head)
 * 
 * Time Complexity: O(n) - requires full traversal to find tail
 */
struct CNode *insertAtEnd(int value)
{
    struct CNode *node = createNode(value);

    /* Case 1: Empty list - node becomes the only element */
    if (head == NULL)
    {
        head = node;
        node->next = head;  /* Single node points to itself */
        return node;
    }

    /* Case 2: Non-empty list - traverse to find tail */
    struct CNode *curr = head;

    /* Traverse until we find the last node */
    do
    {
        curr = curr->next;
    } while (curr->next != head);

    /* Now curr is the tail node */
    
    /* Tail's next points to new node (new node becomes new tail) */
    curr->next = node;
    
    /* Note: node->next already points to head from createNode() */
    
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
 *   2. If only one node exists:
 *      - Free the node
 *      - Set head to NULL
 *   3. Otherwise:
 *      - Traverse to find the tail
 *      - Update head to next node
 *      - Update tail's next to new head (maintain circular property)
 *      - Free the old head
 * 
 * Time Complexity: O(n) - requires traversal to find tail
 */
int deleteFromBeginning(void)
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
        struct CNode *temp = head;
        head = NULL;  /* List becomes empty */
        deletedval = temp->data;
        free(temp);
        return deletedval;
    }

    /* Case 3: Multiple nodes - need to find tail */
    struct CNode *temp = head;  /* Save node to delete */
    struct CNode *curr = head;

    /* Traverse to find the tail (last node) */
    do
    {
        curr = curr->next;
    } while (curr->next != head);
    
    /* Now curr is the tail node */
    
    /* Move head to the next node */
    head = head->next;
    
    /* Update tail's next to point to new head */
    curr->next = head;
    
    /* Save data and free old head */
    deletedval = temp->data;
    free(temp);

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
 *   2. If only one node exists:
 *      - Free the node
 *      - Set head to NULL
 *   3. Otherwise:
 *      - Traverse to find the second-to-last node
 *      - Update its next to point to head
 *      - Free the old tail
 * 
 * Time Complexity: O(n) - requires traversal to find second-to-last node
 */
int deleteFromEnd(void)
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
        struct CNode *temp = head;
        head = NULL;  /* List becomes empty */
        deletedval = temp->data;
        free(temp);
        return deletedval;
    }

    /* Case 3: Multiple nodes - find second-to-last node */
    struct CNode *temp = NULL;
    struct CNode *curr = head;
    
    /* Traverse until curr is at second-to-last node */
    /* (curr->next->next == head means curr->next is the tail) */
    while (curr->next->next != head)
    {
        curr = curr->next;
    }

    /* Now curr is second-to-last, curr->next is the tail to delete */
    temp = curr->next;
    deletedval = temp->data;
    
    /* Update second-to-last node to point to head (becomes new tail) */
    curr->next = head;
    
    /* Free the old tail */
    free(temp);
    
    return deletedval;
}

/*
 * Prints all elements of the list in forward direction
 * 
 * Output format: Elements separated by tabs, ending with newline
 * 
 * Uses do-while loop since we need to traverse the entire circular list
 * starting and ending at head
 * 
 * Time Complexity: O(n)
 */
void printList(void)
{
    /* Handle empty list */
    if (head == NULL)
    {
        printf("LL is Empty\n");
        return;
    }

    struct CNode *curr = head;

    /* Traverse and print until we come back to head */
    do
    {
        printf("%d\t", curr->data);
        curr = curr->next;

    } while (curr != head);

    printf("\n");
}

/*
 * Returns the number of nodes in the list
 * 
 * Returns:
 *   Integer count of nodes (0 if list is empty)
 * 
 * Algorithm:
 *   Traverse the entire list counting nodes until we return to head
 * 
 * Time Complexity: O(n)
 */
int getLength(void)
{
    int count = 0;
    
    /* Empty list has length 0 */
    if (head == NULL)
    {
        return count;
    }
    
    struct CNode *curr = head;

    /* Count nodes until we complete the circle */
    do
    {
        count++;
        curr = curr->next;

    } while (curr != head);

    return count;
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
 * - Get length
 * - Print list
 * ============================================================================
 */
int main() {
    
    /*
     * Test 1: Insert at end
     * Building list: 10 -> 20 -> 30 -> 40 -> (circular back to 10)
     */
    printf("=== Inserting 10, 20, 30, 40 at end ===\n");
    insertAtEnd(10);
    insertAtEnd(20);
    insertAtEnd(30);
    insertAtEnd(40);
    printList();  /* Expected: 10  20  30  40 */
    
    /*
     * Test 2: Insert at beginning
     * List becomes: 5 -> 10 -> 20 -> 30 -> 40 -> (circular back to 5)
     */
    printf("\n=== Inserting 5 at beginning ===\n");
    insertAtBeginning(5);
    printList();  /* Expected: 5  10  20  30  40 */
    
    /*
     * Test 3: Get length
     * Should return 5 (nodes: 5, 10, 20, 30, 40)
     */
    printf("\n=== Length of list ===\n");
    printf("Length: %d\n", getLength());  /* Expected: 5 */
    
    /*
     * Test 4: Delete from beginning
     * Removes 5, list becomes: 10 -> 20 -> 30 -> 40 -> (circular)
     */
    printf("\n=== Deleting from beginning ===\n");
    int deleted = deleteFromBeginning();
    printf("Deleted value: %d\n", deleted);  /* Expected: 5 */
    printList();  /* Expected: 10  20  30  40 */
    
    /*
     * Test 5: Delete from end
     * Removes 40, list becomes: 10 -> 20 -> 30 -> (circular)
     */
    printf("\n=== Deleting from end ===\n");
    deleted = deleteFromEnd();
    printf("Deleted value: %d\n", deleted);  /* Expected: 40 */
    printList();  /* Expected: 10  20  30 */
    
    /*
     * Test 6: Length after deletions
     * Should return 3 (nodes: 10, 20, 30)
     */
    printf("\n=== Length after deletions ===\n");
    printf("Length: %d\n", getLength());  /* Expected: 3 */
    
    return 0;
}