#include <stdlib.h>
#include <stdio.h>

/*
 * Structure definition for a Singly Linked List Node
 * Each node contains:
 * - data: the integer value stored in the node
 * - Next: pointer to the next node in the list (NULL if last node)
 * 
 * Unlike doubly linked lists, singly linked lists can only traverse forward
 */
struct Node
{
    int data;
    struct Node *Next;
};

/* Global head pointer - initialized to NULL (empty list) */
struct Node *head = NULL;

/*
 * CreateNode - Allocates and initializes a new singly linked list node
 * @value: the integer value to store in the new node
 * 
 * Returns: pointer to the newly created node
 * 
 * Memory is allocated on the heap, so node persists after function returns
 * Next pointer is initialized to NULL (node is isolated initially)
 */
struct Node *CreateNode(int value)
{
    // Allocate memory for the new node
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));

    // Initialize the node's fields
    new->data = value;
    new->Next = NULL;

    return new;
}

/*
 * printList - Traverses and prints all elements in the list
 * @HEAD: pointer to the first node of the list
 * 
 * Output format: "LL elements: val1 -> val2 -> ... -> NULL"
 * 
 * Time Complexity: O(n) - must visit every node
 */
void printList(struct Node *HEAD)
{
    struct Node *current = HEAD;
    printf("LL elements: ");
    
    // Traverse until we reach the end (NULL)
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->Next;  // Move to next node
    }
    printf("NULL\n");
}

/*
 * insertAtBeginning - Inserts a new node at the start of the list
 * @head: double pointer to the head (allows modification of head pointer)
 * @value: the integer value to insert
 * 
 * Time Complexity: O(1) - constant time, no traversal needed
 * 
 * Before: head -> [A] -> [B] -> ...
 * After:  head -> [NEW] -> [A] -> [B] -> ...
 */
void insertAtBeginning(struct Node **head, int value)
{
    // Create the new node
    struct Node *new = CreateNode(value);

    // Point new node to current head
    new->Next = *head;
    
    // Update head to point to new node
    *head = new;
}

/*
 * insertAtEnd - Inserts a new node at the end of the list
 * @head: double pointer to the head
 * @value: the integer value to insert
 * 
 * Time Complexity: O(n) - must traverse entire list to find the end
 * 
 * Before: ... -> [Y] -> [Z] -> NULL
 * After:  ... -> [Y] -> [Z] -> [NEW] -> NULL
 */
void insertAtEnd(struct Node **head, int value)
{
    // Create the new node
    struct Node *new = CreateNode(value);
    
    // Special case: if list is empty, new node becomes the head
    if (*head == NULL)
    {
        *head = new;
        return;
    }

    // Traverse to find the last node (node whose Next is NULL)
    struct Node *curr = *head;
    while (curr->Next != NULL)
    {
        curr = curr->Next;
    }
    
    // Link the last node to our new node
    curr->Next = new;
}

/*
 * insertAtPosition - Inserts a new node at a specific position (0-indexed)
 * @head: double pointer to the head
 * @value: the integer value to insert
 * @position: the index where to insert (0 = beginning)
 * 
 * Time Complexity: O(n) - must traverse to the position
 * 
 * Example: Insert at position 2 in list [A, B, C, D]
 * Result: [A, B, NEW, C, D]
 */
void insertAtPosition(struct Node **head, int value, int position)
{
    // Special case: inserting at beginning (position 0)
    if (position == 0)
    {
        insertAtBeginning(head, value);
        return;
    }

    // Create the new node
    struct Node *newNode = CreateNode(value);

    // Traverse to the node just BEFORE the target position
    struct Node *current = *head;
    for (int i = 0; i < position - 1; i++)
    {
        // Check if we've gone past the end
        if (current == NULL)
        {
            printf("Position out of range!\n");
            return;
        }
        current = current->Next;
    }

    // Insert: new node points to what was at position
    // Previous node now points to new node
    newNode->Next = current->Next;
    current->Next = newNode;
}

/*
 * insertSorted - Inserts a value in sorted (ascending) order
 * @head: double pointer to the head
 * @value: the integer value to insert
 * 
 * Assumes: List is already sorted in ascending order
 * Maintains: Sorted order after insertion
 * 
 * Time Complexity: O(n) - may need to traverse entire list
 * 
 * Example: Insert 25 into [10, 20, 30, 40]
 * Result: [10, 20, 25, 30, 40]
 */
void insertSorted(struct Node **head, int value)
{
    struct Node *newNode = CreateNode(value);

    // Case 1: Empty list OR value should be first (smaller than head)
    if (*head == NULL || (*head)->data >= value)
    {
        newNode->Next = *head;
        *head = newNode;
        return;
    }

    // Case 2: Find correct position in the middle or end
    struct Node *curr = *head;

    // Move until we find position where:
    // curr->data < value <= curr->Next->data
    // We stop when next node is NULL or next node's data >= value
    while (curr->Next != NULL && curr->Next->data < value)
    {
        curr = curr->Next;
    }

    // Insert after curr
    newNode->Next = curr->Next;
    curr->Next = newNode;
}

/*
 * deleteFromBeginning - Removes and returns the first node
 * @head: double pointer to the head
 * 
 * Returns: data value of deleted node, or -1 if list is empty
 * 
 * Time Complexity: O(1) - constant time
 * 
 * Before: head -> [A] -> [B] -> ...
 * After:  head -> [B] -> ...
 */
int deleteFromBeginning(struct Node **head)
{
    // Check if list is empty
    if (*head == NULL)
    {
        printf("List is empty!\n");
        return -1;
    }

    struct Node *temp = *head;           // Save reference to node being deleted
    int deletedvalue = temp->data;       // Save the data before freeing
    (*head) = (*head)->Next;             // Move head to second node
    free(temp);                          // Free the old head

    return deletedvalue;
}

/*
 * deleteFromEnd - Removes and returns the last node
 * @head: double pointer to the head
 * 
 * Returns: data value of deleted node, or -1 if list is empty
 * 
 * Time Complexity: O(n) - must traverse to find second-to-last node
 * 
 * Before: ... -> [Y] -> [Z] -> NULL
 * After:  ... -> [Y] -> NULL
 */
int deleteFromEnd(struct Node **head)
{
    // Case 1: Empty list
    if (*head == NULL)
    {
        printf("List is empty!\n");
        return -1;
    }
    
    // Case 2: Only one node in list
    if ((*head)->Next == NULL)
    {
        int deletedValue = (*head)->data;
        free(*head);
        *head = NULL;                    // List is now empty
        return deletedValue;
    }

    // Case 3: Multiple nodes - find second-to-last
    struct Node *curr = *head;
    while (curr->Next->Next != NULL)    // Stop when curr->Next is the last node
    {
        curr = curr->Next;
    }

    // curr is now second-to-last, curr->Next is last
    int deletedValue = curr->Next->data;
    free(curr->Next);                    // Free the last node
    curr->Next = NULL;                   // Second-to-last becomes last

    return deletedValue;
}

/*
 * deleteByValue - Searches for and deletes the first node with matching value
 * @head: double pointer to the head
 * @value: the value to search for and delete
 * 
 * Returns: the deleted value, or -1 if not found/empty
 * 
 * Time Complexity: O(n) - may need to search entire list
 */
int deleteByValue(struct Node **head, int value)
{
    // Case 1: Empty list
    if (*head == NULL)
    {
        printf("List is empty!\n");
        return -1;
    }
    
    // Case 2: Value is in the first node (head)
    if ((*head)->data == value)
    {
        return deleteFromBeginning(head);
    }

    // Case 3: Search for value in rest of list
    struct Node *curr = *head;
    while (curr->Next != NULL)
    {
        // Look ahead to next node
        if (curr->Next->data == value)
        {
            struct Node *temp = curr->Next;          // Node to delete
            int deletedvalue = curr->Next->data;
            curr->Next = curr->Next->Next;           // Bypass the deleted node
            free(temp);
            return deletedvalue;
        }
        curr = curr->Next;
    }
    
    // Note: Function should return -1 here if value not found
    // (Missing return statement - potential bug)
}

/*
 * deleteAtPosition - Deletes the node at a specific position (0-indexed)
 * @head: double pointer to the head
 * @position: the index of node to delete
 * 
 * Returns: data value of deleted node, or -1 if invalid position
 * 
 * Time Complexity: O(n) - must traverse to the position
 */
int deleteAtPosition(struct Node** head, int position) {
    // Case 1: Empty list
    if (*head == NULL) {
        printf("List is empty!\n");
        return -1;
    }
    
    struct Node* temp;
    int deletedVal;
    
    // Case 2: Delete at position 0 (head)
    if (position == 0) {
        temp = *head;
        deletedVal = temp->data;
        *head = (*head)->Next;           // Move head to second node
        free(temp);
        return deletedVal;
    }
    
    // Case 3: Delete at other positions
    struct Node* curr = *head;
    
    // Traverse to node just BEFORE target position
    for (int i = 0; i < position - 1; i++) {
        if (curr->Next == NULL) {        // Check if position is valid
            printf("Position out of range!\n");
            return -1;
        }
        curr = curr->Next;
    }
    
    // Check if target position exists
    if (curr->Next == NULL) {
        printf("Position out of range!\n");
        return -1;
    }
    
    // Delete the node at position
    temp = curr->Next;                   // Node to delete
    deletedVal = temp->data;
    curr->Next = temp->Next;             // Bypass deleted node
    free(temp);
    
    return deletedVal;
}

/*
 * search - Finds the position of a value in the list
 * @head: pointer to the first node
 * @value: the value to search for
 * 
 * Returns: position (0-indexed) if found, -1 if not found
 * 
 * Time Complexity: O(n) - may need to search entire list
 */
int search(struct Node* head, int value) {
    struct Node* curr = head;
    int counter = -1;                    // Will be 0 after first increment
    
    // Traverse the list
    while (curr != NULL)
    {
        counter++;
        if (curr->data == value) {
            printf("Found it at pos: %d", counter);
            return counter;
        }
        curr = curr->Next;
    }
    
    return -1;                           // Value not found
}

/*
 * getLength - Counts the number of nodes in the list
 * @head: pointer to the first node
 * 
 * Returns: the number of nodes in the list
 * 
 * Time Complexity: O(n) - must count every node
 */
int getLength(struct Node* head) {
    struct Node* curr = head;
    int len = 0;
    
    // Traverse and count each node
    while (curr != NULL)
    {
        len++;
        curr = curr->Next;
    }
    return len;
}

/*
 * getElementAt - Retrieves the data at a specific position
 * @head: pointer to the first node
 * @position: the index to retrieve (0-indexed)
 * 
 * Returns: data value at position, or -1 if invalid
 * 
 * Time Complexity: O(n) - must traverse to the position
 */
int getElementAt(struct Node* head, int position) {
    // Case 1: Empty list
    if (head == NULL) {
        printf("List is empty!\n");
        return -1;
    }
    
    struct Node* curr = head;
    
    // Traverse to the target position
    for (int i = 0; i < position; i++) {
        if (curr == NULL) {
            printf("Position out of range!\n");
            return -1;
        }
        curr = curr->Next;
    }

    // Check if position is valid
    if (curr == NULL) {
        printf("Position out of range!\n");
        return -1;
    }
    
    return curr->data;
}

/*
 * getMiddle - Finds the middle element using the "slow & fast pointer" technique
 * @head: pointer to the first node
 * 
 * Returns: data value of middle node, or -1 if empty
 * 
 * Algorithm (Floyd's Tortoise):
 * - slow pointer moves 1 step at a time
 * - fast pointer moves 2 steps at a time
 * - When fast reaches end, slow is at middle
 * 
 * Time Complexity: O(n) - single pass through list
 * Space Complexity: O(1) - only two pointers
 * 
 * For even-length lists, returns the second middle element
 * Example: [1,2,3,4] -> returns 3 (position 2)
 * Example: [1,2,3,4,5] -> returns 3 (position 2)
 */
int getMiddle(struct Node* head) {
    // Empty list check
    if (head == NULL) {
        printf("List is empty!\n");
        return -1;
    }
    
    struct Node* slow = head;            // Moves 1 node at a time
    struct Node* fast = head;            // Moves 2 nodes at a time

    // Continue while fast can make two more moves
    while (fast != NULL && fast->Next != NULL)
    {
        slow = slow->Next;               // Move slow by 1
        fast = fast->Next->Next;         // Move fast by 2
    }
    
    // This check is redundant since slow starts at head
    // and only moves if the list has elements
    if (slow == NULL) {
        printf("Position out of range!\n");
        return -1;
    }

    return slow->data;                   // slow is now at middle
}

/*
 * reverseList - Reverses the entire linked list in-place
 * @head: double pointer to the head
 * 
 * Algorithm: Iteratively reverse the direction of all Next pointers
 * 
 * Time Complexity: O(n) - single pass through list
 * Space Complexity: O(1) - only three pointers
 * 
 * Before: head -> [A] -> [B] -> [C] -> NULL
 * After:  head -> [C] -> [B] -> [A] -> NULL
 * 
 * Visual step-by-step:
 * Initial: NULL <- prev    curr -> [A] -> [B] -> [C] -> NULL
 * Step 1:  NULL <- [A]     curr -> [B] -> [C] -> NULL
 * Step 2:  NULL <- [A] <- [B]     curr -> [C] -> NULL
 * Step 3:  NULL <- [A] <- [B] <- [C]     curr -> NULL
 */
void reverseList(struct Node** head) {
    struct Node* prev = NULL;            // Will become the new tail (initially NULL)
    struct Node* curr = *head;           // Current node being processed
    struct Node* next = NULL;            // Temporary storage for next node

    while (curr != NULL)
    {
        // Step 1: Save the next node (before we lose the reference)
        next = curr->Next;

        // Step 2: Reverse the link - point current back to previous
        curr->Next = prev;
        
        // Step 3: Move prev and curr one step forward
        prev = curr;
        curr = next;
    }
    
    // prev is now pointing to the last node (new head)
    *head = prev;
}

/*
 * main - Test driver for the singly linked list implementation
 * 
 * Tests performed:
 * 1. Build a list with insertAtEnd
 * 2. Print the list
 * 3. Get length
 * 4. Search for values (existing and non-existing)
 * 5. Find middle element
 * 6. Reverse the list
 * 7. Find middle of reversed list
 */
int main() {
    struct Node* head = NULL;            // Local head pointer (shadows global)
    
    // Build list: 10 -> 20 -> 30 -> 40 -> 50
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);
    insertAtEnd(&head, 50);
    
    printf("Original list: ");
    printList(head);
    
    // Test getLength
    printf("\nLength: %d\n", getLength(head));
    
    // Test search - existing value
    printf("\nSearch 30: position %d\n", search(head, 30));
    // Test search - non-existing value
    printf("Search 99: position %d\n", search(head, 99));
    
    // Test getMiddle (for 5 elements, middle is element 3 = 30)
    printf("\nMiddle element: %d\n", getMiddle(head));
    
    // Test reverse
    printf("\nReversing list...\n");
    reverseList(&head);
    printf("Reversed list: ");
    printList(head);
    
    // After reverse: 50 -> 40 -> 30 -> 20 -> 10
    // Middle is still 30
    printf("\nMiddle of reversed: %d\n", getMiddle(head));
    
    return 0;
}