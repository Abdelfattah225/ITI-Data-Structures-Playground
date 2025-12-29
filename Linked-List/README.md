```markdown
# Linked List Cheat Sheet 📝

Quick reference for interview preparation.

---

## 📁 Files

| File | Type |
|------|------|
| `singly_linked_list.c` | Linear, one direction |
| `doubly_linked_list.c` | Linear, two directions |
| `circular_singly_linked_list.c` | Circular, one direction |
| `circular_doubly_linked_list.c` | Circular, two directions |

---

## 🔗 Visual Reference

```
SINGLY:           [10|→] → [20|→] → [30|→] → NULL

DOUBLY:      NULL ← [←|10|→] ↔ [←|20|→] ↔ [←|30|→] → NULL

CIRCULAR SINGLY:  [10|→] → [20|→] → [30|→] ─┐
                    ↑________________________│

CIRCULAR DOUBLY:  ┌─← [←|10|→] ↔ [←|20|→] ↔ [←|30|→] ←─┐
                  └─→                               →──┘
```

---

## ⏱️ Time Complexity

| Operation | SLL | DLL | CSLL | CDLL |
|-----------|:---:|:---:|:----:|:----:|
| Insert at head | O(1) | O(1) | O(n) | O(1) |
| Insert at tail | O(n) | O(n) | O(n) | O(1) |
| Delete at head | O(1) | O(1) | O(n) | O(1) |
| Delete at tail | O(n) | O(1) | O(n) | O(1) |
| Search | O(n) | O(n) | O(n) | O(n) |

> **CDLL wins** for insert/delete at both ends!

---

## 🧠 Key Concepts

### Node Structure
```c
// Singly
struct Node {
    int data;
    struct Node *next;
};

// Doubly
struct DNode {
    int data;
    struct DNode *next;
    struct DNode *prev;
};
```

### Empty List Check
```c
if (head == NULL)  // All types
```

### Single Node Check
```c
// Linear
if (head->next == NULL)

// Circular
if (head->next == head)
```

### Find Tail
```c
// Linear Singly - O(n)
while (curr->next != NULL)
    curr = curr->next;

// Circular Singly - O(n)
while (curr->next != head)
    curr = curr->next;

// Circular Doubly - O(1)
tail = head->prev;
```

### Traversal Pattern
```c
// Linear
while (curr != NULL) {
    // process
    curr = curr->next;
}

// Circular (use do-while!)
do {
    // process
    curr = curr->next;
} while (curr != head);
```

---

## 🔑 Interview Tips

### Common Operations to Know

1. **Reverse a linked list**
2. **Find middle element** (slow/fast pointer)
3. **Detect cycle** (Floyd's algorithm)
4. **Merge two sorted lists**
5. **Remove nth node from end**

### Edge Cases to Handle

- ✅ Empty list (`head == NULL`)
- ✅ Single node
- ✅ Two nodes
- ✅ Operation on head/tail
- ✅ Value not found (for search/delete)

### Common Mistakes to Avoid

- ❌ Forgetting to update `head` after deletion
- ❌ Not handling empty list
- ❌ Memory leaks (forgetting `free()`)
- ❌ Infinite loop in circular lists
- ❌ Losing reference to nodes during pointer manipulation

---

## 🆚 When to Use What?

| Type | Use When |
|------|----------|
| **Singly** | Simple stack/queue, memory limited |
| **Doubly** | Need backward traversal, browser history |
| **Circular Singly** | Round-robin scheduling, circular buffer |
| **Circular Doubly** | Music playlist, undo/redo with wrap-around |

---

## 💾 Memory Per Node

| Type | Size |
|------|------|
| Singly | `data` + 1 pointer (8 bytes on 64-bit) |
| Doubly | `data` + 2 pointers (16 bytes on 64-bit) |

---

## ⚡ Quick Code Patterns

### Insert at Beginning (Singly)
```c
newNode->next = head;
head = newNode;
```

### Insert at Beginning (Circular Doubly)
```c
newNode->next = head;
newNode->prev = head->prev;  // tail
head->prev->next = newNode;  // tail->next = new
head->prev = newNode;
head = newNode;
```

### Delete from Beginning (Singly)
```c
temp = head;
head = head->next;
free(temp);
```

### Delete from End (Circular Doubly)
```c
tail = head->prev;
tail->prev->next = head;
head->prev = tail->prev;
free(tail);
```

---

## 🧪 Compile & Test

```bash
gcc singly_linked_list.c -o sll && ./sll
gcc doubly_linked_list.c -o dll && ./dll
gcc circular_singly_linked_list.c -o csll && ./csll
gcc circular_doubly_linked_list.c -o cdll && ./cdll
```

---

## 📌 Remember!

```
┌─────────────────────────────────────────────────┐
│  Linear → ends with NULL                        │
│  Circular → ends point back to head             │
│  Singly → only next pointer                     │
│  Doubly → both prev and next pointers           │
│                                                 │
│  CDLL = O(1) for both head AND tail operations! │
└─────────────────────────────────────────────────┘
```
