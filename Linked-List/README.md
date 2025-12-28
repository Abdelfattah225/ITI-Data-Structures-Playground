# Linked List Implementation in C

# Linked List
---

## 📁 Files

| File | Description |
|------|-------------|
| `singly_linked_list.c` | Singly linked list implementation |
| `doubly_linked_list.c` | Doubly linked list implementation |

---

## 🔗 Data Structures

### Singly Linked List
```
[data|next] -> [data|next] -> [data|next] -> NULL
```

### Doubly Linked List
```
NULL <- [prev|data|next] <-> [prev|data|next] <-> [prev|data|next] -> NULL
```

---

## ⚡ Operations

| Operation | Singly | Doubly |
|-----------|--------|--------|
| Insert at beginning | ✅ O(1) | ✅ O(1) |
| Insert at end | ✅ O(n) | ✅ O(n) |
| Insert at position | ✅ O(n) | ✅ O(n) |
| Insert sorted | ✅ O(n) | ❌ |
| Delete from beginning | ✅ O(1) | ✅ O(1) |
| Delete from end | ✅ O(n) | ✅ O(1)* |
| Delete by value | ✅ O(n) | ✅ O(n) |
| Delete at position | ✅ O(n) | ❌ |
| Search | ✅ O(n) | ❌ |
| Get length | ✅ O(n) | ✅ O(n) |
| Get middle | ✅ O(n) | ❌ |
| Reverse | ✅ O(n) | ✅ O(n) |
| Print forward | ✅ O(n) | ✅ O(n) |
| Print backward | ❌ | ✅ O(n) |

*\*With tail pointer*

---

## 🚀 Quick Start

### Compile & Run

```bash
# Singly Linked List
gcc singly_linked_list.c -o sll
./sll

# Doubly Linked List
gcc doubly_linked_list.c -o dll
./dll
```

### Basic Usage

```c
// Singly
struct Node* head = NULL;
insertAtEnd(&head, 10);
insertAtEnd(&head, 20);
printList(head);          // 10 -> 20 -> NULL

// Doubly
struct DNode* head = NULL;
insertAtEndD(&head, 10);
insertAtEndD(&head, 20);
printForward(head);       // 10 <-> 20 <-> NULL
```

---

## 🆚 When to Use?

| Use Singly When | Use Doubly When |
|-----------------|-----------------|
| Memory is limited | Need backward traversal |
| Only forward traversal needed | Frequent delete from end |
| Simpler implementation preferred | Need to delete a node given only its pointer |

---

## 📊 Memory Comparison

| Type | Memory per Node |
|------|-----------------|
| Singly | `data` + 1 pointer |
| Doubly | `data` + 2 pointers |

---

## 🧪 Sample Output

```
Original list: 10 -> 20 -> 30 -> 40 -> 50 -> NULL
Length: 5
Middle element: 30
Reversed list: 50 -> 40 -> 30 -> 20 -> 10 -> NULL
```

---
