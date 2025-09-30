# Recent Trends

## **1. Recent Trends in Hashing**

Hashing is widely used in modern systems, and research has produced advanced techniques beyond classical chaining/probing.

### (a) Perfect Hashing

- **Idea**: Construct a hash function with *no collisions* for a given static set of keys.
- **Use-case**: When the key set is known in advance and does not change (e.g., reserved keywords in a compiler).
- **Technique**: Two-level hashing – first hash distributes to buckets, second hash eliminates collisions.

---

### (b) Cuckoo Hashing

- **Idea**: Each key has two (or more) possible hash positions.
- **Insertion**: If a slot is occupied, the existing key is "kicked out" (like cuckoo bird) and reinserted at its alternate position.
- **Pros**:
    - O(1) lookup (check only 2 positions).
    - High load factor.
- **Cons**: May require rehashing if cycles form.

---

### (c) Hopscotch Hashing

- **Idea**: Variation of linear probing with a "neighborhood" constraint.
- Each element can reside within a small distance of its ideal hash location.
- Helps cache performance and avoids long probe sequences.

---

### (d) Dynamic / Extendible Hashing

- **Extendible Hashing**: Directory-based method where the number of hash bits used is increased dynamically when buckets overflow.
- **Linear Hashing**: Grows the table gradually without rehashing the whole dataset at once.

---

### (e) Hashing in Distributed Systems

- **Consistent Hashing**:
    - Popular in distributed databases (Cassandra, DynamoDB).
    - Allows nodes (servers) to join/leave with minimal key redistribution.
- **Application**: Load balancing, caching, distributed hash tables (DHTs).

---

**Summary of Recent Trends in Hashing**:

- Perfect Hashing → static datasets.
- Cuckoo Hashing → O(1) lookups.
- Hopscotch Hashing → cache-friendly probing.
- Extendible & Linear Hashing → dynamic datasets.
- Consistent Hashing → distributed systems.

---

## **2. Recent Trends in Trees**

Classical trees like BST, AVL, Red-Black, B-Trees are well studied. Recent research focuses on **cache efficiency, concurrency, and scalability**.

---

### (a) Cache-Oblivious B-Trees

- Optimized for hierarchical memory without knowing cache size or block size.
- Useful in large databases and file systems.

---

### (b) Finger Trees

- General-purpose data structure supporting efficient access to the ends ("fingers") and quick concatenation/splitting.
- Used in functional programming (e.g., Haskell).

---

### (c) Treaps

- Combination of **Binary Search Tree** (ordered by key) + **Heap** (ordered by random priority).
- Randomization balances the tree automatically (expected O(log n) height).
- Simpler than AVL/Red-Black balancing.

---

### (d) Tango Trees

- A type of self-adjusting tree optimized for sequences of searches.
- Uses **preferred paths** and guarantees competitive bounds close to optimal dynamic BSTs.

---

### (e) Cache-Conscious / Fractal Trees

- Modify B-trees to optimize disk access.
- Used in databases like **TokuDB** for MySQL. (f) Concurrent and Lock-Free Trees

---

- Needed in multi-core and distributed environments.
- Lock-free skip lists and search trees allow multiple threads to operate without blocking.