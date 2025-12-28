#include <stdlib.h>
#include <stdio.h>

/*
 * Structure definition for a Doubly Linked List Node
 * Each node contains:
 * - data: the integer value stored in the node
 * - prev: pointer to the previous node in the list
 * - next: pointer to the next node in the list
 */
struct DNode
{
    int data;
    struct DNode *prev;
    struct DNode *next;
};

/*
 * CreateNode - Allocates and initializes a new doubly linked list node
 * @val: the integer value to store in the new node
 * 
 * Returns: pointer to the newly created node
 * 
 * Note: Both prev and next pointers are initialized to NULL
 */
struct DNode *CreateNode(int val)
{
    // Allocate memory for the new node
    struct DNode *newNode = (struct DNode *)malloc(sizeof(struct DNode));

    // Initialize pointers to NULL (node is isolated initially)
    newNode->next = NULL;
    newNode->prev = NULL;
    // Store the value
    newNode->data = val;

    return newNode;
}

/*
 * printForward - Traverses and prints the list from head to tail
 * @head: pointer to the first node of the list
 * 
 * Output format: "Forward: val1 <-> val2 <-> ... <-> NULL"
 */
void printForward(struct DNode *head)
{
    struct DNode *curr = head;
    printf("Forward: ");
    
    // Traverse until we reach the end (NULL)
    while (curr != NULL)
    {
        printf("%d <-> ", curr->data);
        curr = curr->next;  // Move to next node
    }
    printf("NULL\n");
}

/*
 * printBackward - Traverses and prints the list from tail to head
 * @tail: pointer to the last node of the list
 * 
 * Output format: "Backward: valN <-> valN-1 <-> ... <-> NULL"
 */
void printBackward(struct DNode *tail)
{
    struct DNode *curr = tail;
    printf("Backward: ");

    // Traverse backwards until we reach the beginning (NULL)
    while (curr != NULL)
    {
        printf("%d <-> ", curr->data);
        curr = curr->prev;  // Move to previous node
    }
    printf("NULL\n");
}

/*
 * insertAtBeginningD - Inserts a new node at the start of the list
 * @head: double pointer to the head (allows modification of head pointer)
 * @value: the integer value to insert
 * 
 * Time Complexity: O(1)
 * 
 * Before: head -> [A] <-> [B] <-> ...
 * After:  head -> [NEW] <-> [A] <-> [B] <-> ...
 */
void insertAtBeginningD(struct DNode **head, int value)
{
    struct DNode *newNode = CreateNode(value);

    // New node's next points to current head
    newNode->next = *head;
    
    // If list is not empty, update old head's prev pointer
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }

    // Update head to point to new node
    *head = newNode;
}

/*
 * insertAtEndD - Inserts a new node at the end of the list
 * @head: double pointer to the head
 * @value: the integer value to insert
 * 
 * Time Complexity: O(n) - must traverse to find the end
 * 
 * Before: ... <-> [Y] <-> [Z] -> NULL
 * After:  ... <-> [Y] <-> [Z] <-> [NEW] -> NULL
 */
void insertAtEndD(struct DNode **head, int value)
{
    struct DNode *newNode = CreateNode(value);
    
    // Special case: If list is empty, new node becomes the head
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    
    // Traverse to find the last node
    struct DNode *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    // Link the new node at the end
    temp->next = newNode;      // Last node points to new node
    newNode->prev = temp;      // New node points back to last node
}

/*
 * deleteFromBeginningD - Removes the first node from the list
 * @head: double pointer to the head
 * 
 * Returns: the data value of the deleted node, or -1 if list is empty
 * 
 * Time Complexity: O(1)
 */
int deleteFromBeginningD(struct DNode **head)
{
    int deletedval;
    
    // Check if list is empty
    if (*head == NULL)
    {
        printf("List is empty!\n");
        return -1;
    }

    struct DNode *temp = *head;      // Store reference to node being deleted
    deletedval = temp->data;         // Save the value before deletion
    (*head) = (*head)->next;         // Move head to second node
    
    // If list still has nodes, clear the new head's prev pointer
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    
    free(temp);                      // Free the old head node
    return deletedval;
}

/*
 * deleteFromEndD - Removes the last node from the list
 * @head: double pointer to the head (needed if list becomes empty)
 * @tail: double pointer to the tail
 * 
 * Returns: the data value of the deleted node, or -1 if list is empty
 * 
 * Time Complexity: O(1) - since we have direct access to tail
 */
int deleteFromEndD(struct DNode **head, struct DNode **tail)
{
    int deletedval;

    // Check if list is empty
    if (*tail == NULL)
    {
        printf("List is empty!\n");
        return -1;
    }
    
    struct DNode *temp = *tail;      // Store reference to node being deleted
    (*tail) = (*tail)->prev;         // Move tail to second-to-last node
    
    // If list still has nodes, clear the new tail's next pointer
    if ((*tail) != NULL)
    {
        (*tail)->next = NULL;
    }
    else
    {
        // List is now empty, update head too
        *head = NULL;
    }

    deletedval = temp->data;         // Save the value
    free(temp);                      // Free the old tail node
    return deletedval;
}

/*
 * deleteByValueD - Searches for and deletes the first node with matching value
 * @head: double pointer to the head
 * @value: the value to search for and delete
 * 
 * Returns: the deleted value, or -1 if not found/empty
 * 
 * Time Complexity: O(n) - may need to search entire list
 */
int deleteByValueD(struct DNode **head, int value)
{
    int deletedval;
    
    // Check if list is empty
    if (*head == NULL)
    {
        printf("List is empty!\n");
        return -1;
    }

    struct DNode *curr = *head;
    
    // Search for the node containing the value
    while (curr != NULL && curr->data != value)
    {
        curr = curr->next;
    }

    // Value not found in the list
    if (curr == NULL)
    {
        printf("Value %d not found!\n", value);
        return -1;
    }
    
    int deletedValue = curr->data;
    
    // Update the previous node's next pointer (bypass current node)
    if (curr->prev != NULL)
    {
        curr->prev->next = curr->next;
    }
    else
    {
        // Current node is the head, update head pointer
        *head = curr->next;
    }
    
    // Update the next node's prev pointer (bypass current node)
    if (curr->next != NULL)
    {
        curr->next->prev = curr->prev;
    }

    free(curr);                      // Free the deleted node
    return deletedValue;
}

/*
 * insertAtPositionD - Inserts a new node at a specific position (0-indexed)
 * @head: double pointer to the head
 * @value: the integer value to insert
 * @position: the index where to insert (0 = beginning)
 * 
 * Time Complexity: O(n) - must traverse to the position
 * 
 * Example: Insert at position 2 in list [A, B, C, D]
 * Result: [A, B, NEW, C, D]
 */
void insertAtPositionD(struct DNode **head, int value, int position)
{
    // Special case: inserting at beginning
    if (position == 0)
    {
        insertAtBeginningD(head, value);
        return;
    }
    
    struct DNode *newNode = CreateNode(value);
    struct DNode *curr = *head;

    // Traverse to the node just before the target position
    for (size_t i = 0; i < position - 1; i++)
    {
        if (curr == NULL)
        {
            printf("Position out of range!\n");
            free(newNode);           // Clean up allocated memory
            return;
        }
        curr = curr->next;
    }
    
    // Check if we've gone past the end
    if (curr == NULL)
    {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }

    // Insert new node after curr
    newNode->next = curr->next;      // New node points to what was after curr
    newNode->prev = curr;            // New node points back to curr
    
    // Update the node after new node (if it exists)
    if (curr->next != NULL)
    {
        curr->next->prev = newNode;
    }
    
    curr->next = newNode;            // curr now points to new node
}

/*
 * reverseDLL - Reverses the entire doubly linked list in-place
 * @head: double pointer to the head
 * 
 * Algorithm: Swap prev and next pointers for every node
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * 
 * Before: head -> [A] <-> [B] <-> [C] -> NULL
 * After:  head -> [C] <-> [B] <-> [A] -> NULL
 */
void reverseDLL(struct DNode** head) {
    // Empty list, nothing to reverse
    if (*head == NULL) {
        return;
    }
    
    struct DNode* curr = *head;
    struct DNode* temp = NULL;

    // Traverse the list and swap prev/next for each node
    while (curr != NULL)
    {
        // Swap the prev and next pointers
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;

        // Move to the next node (which is now in prev due to swap)
        curr = curr->prev;
    }
    
    // After loop, temp points to the old prev of the last processed node
    // The new head is temp->prev (the last node we processed)
    if (temp != NULL) {
        (*head) = temp->prev;
    }
}

/*
 * getLengthD - Counts the number of nodes in the list
 * @head: pointer to the first node
 * 
 * Returns: the number of nodes in the list
 * 
 * Time Complexity: O(n)
 */
int getLengthD(struct DNode* head) {
    int count = 0;
    struct DNode* curr = head;
    
    // Traverse and count each node
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

/*
 * main - Test driver for the doubly linked list implementation
 * 
 * Tests performed:
 * 1. Build a list with insertAtEndD
 * 2. Print forward and get length
 * 3. Insert at specific position
 * 4. Delete by value (middle, first, last)
 * 5. Reverse the list
 * 6. Print backward
 */
int main() {
    struct DNode* head = NULL;
    
    // Build list: 10 <-> 20 <-> 30 <-> 40 <-> 50
    insertAtEndD(&head, 10);
    insertAtEndD(&head, 20);
    insertAtEndD(&head, 30);
    insertAtEndD(&head, 40);
    insertAtEndD(&head, 50);
    
    printf("Original list:\n");
    printForward(head);
    printf("Length: %d\n", getLengthD(head));
    
    // Test insert at position (insert 25 between 20 and 30)
    printf("\nInsert 25 at position 2:\n");
    insertAtPositionD(&head, 25, 2);
    printForward(head);
    
    // Test delete by value - middle element
    printf("\nDelete 30:\n");
    deleteByValueD(&head, 30);
    printForward(head);
    
    // Test delete by value - first element (head)
    printf("\nDelete 10 (first):\n");
    deleteByValueD(&head, 10);
    printForward(head);
    
    // Test delete by value - last element (tail)
    printf("\nDelete 50 (last):\n");
    deleteByValueD(&head, 50);
    printForward(head);
    
    // Test reverse functionality
    printf("\nReverse the list:\n");
    reverseDLL(&head);
    printForward(head);
    
    // Find tail by traversing to the end
    struct DNode* tail = head;
    while (tail != NULL && tail->next != NULL) {
        tail = tail->next;
    }
    
    // Print backward to verify prev pointers are correct
    printBackward(tail);
    
    return 0;
}