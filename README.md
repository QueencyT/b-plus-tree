
# B+ Tree - Map & Multimap

## Overview

B+ Tree is a custom, template-based implementation developed from scratch in C++, featuring dynamic insertion, deletion, searching, and ordered traversal.

The project extends the B+ Tree structure to implement custom Map and Multimap containers. These data structures support key-value associations, ordered iteration, and range-based queries without relying on standard library map implementations.

Unlike conventional B-Trees, which store data throughout internal and leaf nodes, B+ Trees organize data entries in leaf nodes while using internal keys to guide searches. The leaf nodes are linked together, enabling sequential traversal of sorted data.

---

## Key Features

- **Custom B+ Tree:** Implements a multiway search tree with dynamic insertion, deletion, and structural rebalancing.
- **Linked Leaf Nodes:** Connects leaf nodes to support sequential traversal of sorted keys.
- **Map Implementation:** Provides key-value associations using a B+ Tree-backed container.
- **Multimap Implementation:** Associates individual keys with multiple values using dynamically managed vectors.
- **Ordered Iteration:** Implements custom iterators for traversing stored entries.
- **Range Queries:** Provides `lower_bound()` and `upper_bound()` operations for ordered key retrieval.
- **Dynamic Tree Rebalancing:** Handles node splitting, redistribution, and merging during tree modifications.
- **Deep Copy and Memory Management:** Supports copy construction, assignment, and recursive node deallocation.
- **GoogleTest Integration:** Includes tests and debugging scenarios for B+ Tree, Map, and Multimap operations.

---

## System Architecture

The implementation consists of three primary layers: the underlying B+ Tree, key-value representations, and associative container interfaces.

### 1. <ins>B+ Tree Implementation</ins>

The `BPlusTree<T>` class serves as the underlying data structure for storing and organizing ordered keys.

Each tree node contains:

- An array of sorted keys.
- Pointers to child subtrees.
- Key and child counts.
- A `next` pointer linking adjacent leaf nodes.

The implementation uses a minimum key count of 1 and a maximum of 2 keys per node, corresponding to a 2-3-4-style configuration.

Tree operations use recursive algorithms and structural adjustments to manage insertion and deletion.

**Insertion and Node Splitting**

When inserting a key, the tree recursively locates the appropriate leaf node.

If the node exceeds its maximum capacity, it is split, and a separator key is promoted to its parent.

The `loose_insert()` and `fix_excess()` functions manage this process.

**Deletion and Rebalancing**

Deletion uses recursive removal and structural adjustments to handle nodes that fall below their minimum key capacity.

The implementation includes functions for:

- Redistributing keys between sibling nodes.
- Borrowing keys from neighboring subtrees.
- Merging adjacent nodes.
- Adjusting the root when necessary.

These operations are designed to preserve the B+ Tree's structure as keys are removed.

### 2. <ins>Linked-Leaf Traversal and Iterators</ins>

The B+ Tree maintains links between consecutive leaf nodes, allowing stored data entries to be visited in sorted order.

The custom `Iterator` tracks:

- A pointer to the current leaf node.
- An index identifying the current key.

Incrementing an iterator advances through the keys in the current leaf and follows the `next` pointer when the end of a leaf is reached.

The implementation provides:

- `begin()` and `end()` for sequential traversal.
- `find()` for locating a matching key.
- `lower_bound()` for locating the first key greater than or equal to a target.
- `upper_bound()` for locating the first key strictly greater than a target.

These operations form the foundation of ordered traversal and range-based queries.

### 3. <ins>Map Implementation</ins>

The `Map<K, V>` class provides a key-value associative container built on top of:

```cpp
BPlusTree<Pair<K, V>>
```

Each `Pair` stores:

- A unique key.
- Its associated value.

Comparison operators use the key to determine ordering within the B+ Tree.

The Map interface exposes operations for insertion, element access, searching, iteration, and range queries.

For example:

```text
Key       Value
----------------
101       Alice
102       Bob
103       Charlie
```

This design separates the underlying tree algorithms from the key-value interface.

### 4. <ins>Multimap Implementation</ins>

The `MMap<K, V>` class extends the B+ Tree indexing approach to support multiple values associated with a single key.

It uses:

```cpp
BPlusTree<MPair<K, V>>
```

Each `MPair` contains:

```cpp
K key;
vector<V> value_list;
```

Instead of duplicating an index key for every associated value, each key maintains a vector of values.

For example:

```text
Major Index

"CS"       -> [101, 103, 105]
"Math"     -> [102, 106]
"Physics"  -> [104]
```

Here, each key represents a major, while the associated values represent student record identifiers.

This structure allows multiple records to share a field value while retaining a single ordered index entry for that key.

---

## Design Rationale

Using a B+ Tree as the underlying structure for both Map and Multimap provides a reusable approach to ordered associative storage.

The multiway tree structure supports hierarchical key organization and dynamic structural adjustments, while linked leaf nodes enable sequential traversal without repeatedly descending through the tree. Map provides one value per key, whereas Multimap associates a key with a vector of values, supporting repeated field values without duplicating index keys.

Separating the tree structure from the Map and Multimap interfaces also promotes code reuse, allowing multiple associative containers to share the same underlying indexing implementation.

---

## Supported Operations

| Operation | B+ Tree | Map | Multimap |
|-----------|---------|-----|----------|
| Insert | Yes | Yes | Yes |
| Remove | Yes | Yes | Not implemented in wrapper |
| Search | Yes | Yes | Yes |
| Key-Value Access | — | Yes | Yes |
| Multiple Values per Key | — | No | Yes |
| Ordered Iteration | Yes | Yes | Yes |
| Lower Bound | Yes | Yes | Yes |
| Upper Bound | Yes | Yes | Yes |
| Clear | Yes | Yes | Yes |
| Deep Copy | Yes | Via underlying tree | Via underlying tree |

---

## Core Components

| Component | Responsibility |
|-----------|----------------|
| `bplustree.h` | Implements B+ Tree insertion, deletion, searching, linked leaves, iterators, and tree operations |
| `btree_array_funcs.h` | Provides array insertion, deletion, splitting, merging, and copying utilities |
| `map.h` | Implements a B+ Tree-backed associative Map container |
| `multimap.h` | Implements a B+ Tree-backed Multimap container |
| `pair.h` | Defines key-value pairs used by Map |
| `mpair.h` | Defines key-vector pairs used by Multimap |
| `btree.h` | Contains a separate B-Tree implementation |
| `basic_test.cpp` | Exercises B+ Tree, Map, and Multimap functionality |
| `testB.cpp` | Provides additional GoogleTest and debugging scenarios |

---

## Time Complexity

For a correctly maintained B+ Tree with a fixed maximum number of keys per node:

| Operation | Complexity |
|-----------|------------|
| Tree Search | O(log n) |
| Tree Insertion | O(log n) |
| Tree Deletion | O(log n) |
| Sequential Traversal | O(n) |
| Current Iterator-Based Lower/Upper Bound | O(n) |
| Deep Copy | O(n) |

The current `lower_bound()`, `upper_bound()`, and iterator-based `find()` implementations perform sequential traversal rather than logarithmic tree descent.

These operations could be optimized by navigating directly to the relevant leaf through the tree's internal separator keys.

---

## Testing

The project includes C++ test programs using **GoogleTest**, along with console-based structural inspection.

The tests exercise:

- B+ Tree insertion and node splitting.
- Searching for existing and nonexistent keys.
- Deletion and tree rebalancing.
- Sequential traversal using custom iterators.
- Map key-value insertion and retrieval.
- Multimap storage of multiple values per key.
- Lower-bound and upper-bound operations.
- Tree copying and memory cleanup.

The testing code also includes exploratory scenarios for structural debugging and randomized operations.

---

## Project Information

**Language:** C++  
**Data Structures:** B+ Tree, Map, Multimap  
**Testing:** GoogleTest  
**Core Concepts:** Balanced search trees, associative containers, iterators, recursion, templates, and dynamic memory management

**Developer:** Queency Tan
