## Skip Lists
an extension to linked lists.

![Skip list image](https://i.ibb.co/Y7crbH77/image.png)
![skip list image 2](https://i.ibb.co/JWKK9sCJ/image.png)

Key Advantages of Skip Lists
Here are the notes on the four key advantages of skip lists:

1. Simplicity with strong expected guarantees: Skip lists achieve the same expected O(log n) performance as complex balanced trees (like AVL or Red-Black trees) but use much simpler logic. Instead of requiring complicated rotations and strict structural rules, they rely on simple coin flips and pointer updates.
2. Robustness to (most) adversarial patterns: The randomized promotion of nodes makes the skip list's structure independent of the input order. This prevents the systematic worst-case scenarios that happen when deterministic structures, like a simple Binary Search Tree, are given sorted data (which makes them degenerate into a slow linked list).
3. Good constant factors & memory locality: In practice, skip list operations are often faster than tree rotations due to having a smaller 'constant factor' (fewer instructions per operation). While they are a linked structure, their upper levels are sparse, meaning the CPU cache can process the short runs on each level efficiently, leading to good memory locality.
4. Concurrency friendliness: Modifying a skip list involves localized pointer changes, not whole-structure rotations. This makes it naturally suited for multi-threaded environments and allows for high-performance, lock-free or lock-minimal designs, such as Java's ConcurrentSkipListMap.

```java
// pseudo code 
x ← head
for ℓ = H down to 0:
    while x.next[ℓ] ≠ NIL and x.next[ℓ].key < k:
        x ← x.next[ℓ]
# x is predecessor on level 0
candidate ← x.next[0]
return (candidate ≠ NIL and candidate.key == k)

```

### The Core Problem with using `<=` and not `<`: Losing the "Path"

The fundamental issue with using `<=` is that you lose the "path" of **predecessor nodes**.

When you insert or delete a node, you need to stitch it into (or out of) the fabric of the skip list on *every level*. To do this, you absolutely must know which node comes *just before* the target location on each level.

- Using **`<`** guarantees that the search algorithm's primary result is this exact path of predecessors.
- Using **`<=`** causes the search to jump ahead to the target node on the highest possible level, forgetting which nodes led to it on the levels below.

### Insertion in Skip Lists

Inserting a key is a three-step process: **Search, Create, and Splice**.

1. **Search & Find Predecessors**: First, perform the standard search for the key's location. The goal is to find and save the node that comes *just before* the new node's position on every single level. These are stored in a `prev` array.
2. **Create Node & Get Height**: Create the new node for the key and assign it a **random height**. This height determines how many 'express lanes' the node will be a part of.
3. **Splice In**: Loop from the bottom level up to the new node's height. On each level, perform a **'splice' operation** to link the new node in.

**Dry Run: Inserting Key `55`**

Let's assume the new node `55` gets a random height of 2 (so it exists on Level 0 and Level 1). The search step finds the predecessors: `prev[1] = 30` and `prev[0] = 50`.

**1. Before the Splice:**

```
Level 1:  ... ---> 30 ----------------------> 90
Level 0:  ... ---> 50 ----------------------> 60

```

**2. The Splice Operation:**
The code loops and performs the splice on each level.

- **On Level 0:** It splices `55` after `prev[0]` (node `50`).
    
    ```
    ... -> 50 ---> 55 ---> 60
    
    ```
    
- **On Level 1:** It splices `55` after `prev[1]` (node `30`).
    
    ```
    ... -> 30 ---> 55 ---> 90
    
    ```
    

**3. Final Result:**
The `newNode(55)` is now fully linked into the list.

```
Level 1:  ... ---> 30 ---> 55 ----------------------> 90
                   |        |
Level 0:  ... ---> 50 ---> 55 ---> 60 -> ...

```

*(Note: The vertical lines are just for conceptual clarity; `30` and `50` are not vertically connected in the actual structure.)*

### Deletion Algorithm (Simplified)

Deletion is very similar to insertion but in reverse.

1. **Search & Find Predecessors**: Just like with insertion, search for the key to be deleted and collect its predecessor on each level in a `prev` array.
2. **Verify Target**: Check that the node after the predecessor (`prev[0].next[0]`) is actually the node you want to delete. If not, the key doesn't exist.
3. **Bypass (Relink)**: Loop through the levels of the target node. On each level, swing the predecessor's pointer to point to the node *after* the target node, effectively **bypassing and unlinking** the target from the list.

**Dry Run: Deleting Key `30`**

The search finds the predecessors for `30`: `prev[1] = -∞` and `prev[0] = 10`.

**1. Before Deletion:**

```
Level 1:  -∞ ------> 30 ----------------------> 90
Level 0:  -∞ -> 10 -> 30 -> 40 -> ...

```

**2. The Bypass Operation:**

- **On Level 0:** It bypasses `30` by linking `prev[0]` (node `10`) to what `30` was pointing to (`40`).
    
    ```
    ... -> 10 ----------> 40 -> ...
    
    ```
    
- **On Level 1:** It bypasses `30` by linking `prev[1]` (node `∞`) to what `30` was pointing to (`90`).
    
    ```
    -∞ ----------------------------> 90
    
    ```
    

**3. Final Result:**
Node `30` is now completely unlinked from the list and can be garbage collected.

### Advanced Concurrency (The Lock-Free Secret of Skip Lists)

Skip lists are excellent for multi-threaded systems because they can avoid slow traditional locks.

1. **CAS (Compare-and-Swap)**: This is an atomic CPU instruction that performs a conditional update. It's used to 'swing' pointers for insertions and deletions, but only if the pointer hasn't been changed by another thread in the meantime. This is the **action that replaces a lock**.
2. **Hazard Pointers / Epochs**: These are advanced memory management techniques that act as a **safety net for CAS**. They prevent a dangerous race condition (the 'ABA problem') by ensuring that memory for a deleted node isn't reused until it's safe for all threads.

### Understanding Deterministic Skip Lists

what we learnt before was non deterministic skip lists (as the height was not fixed or the overall structure is not fixed for the list) as there could be gap of any number between nodes at any level.

A **deterministic skip list** is a type of skip list that achieves the same efficient `O(log n)` search times as a regular skip list but does so without any randomness. Instead of using coin flips to determine the height of nodes, it uses a **strict, fixed set of rules** to maintain its structure.

This approach transforms the skip list from a data structure with *highly probable* good performance into one with **guaranteed worst-case** good performance.

### The Core Rule: The "Determiner"

The defining feature of a deterministic skip list is its balancing rule. The most common is the **1-2 Rule**:

> The 1-2 Rule: Between any two consecutive nodes on a higher level (Level i), there must be either one or two nodes on the level immediately below it (Level i-1).
> 

This rule is the "determiner" because it dictates exactly how the list must be structured. Any operation that violates this rule forces an immediate rebalancing action.

### The Structure: A Perfect Balance

Because of the strict rule, a deterministic skip list looks perfectly balanced and highly structured, similar to a B-tree.

**Example of a valid deterministic skip list:**

```
Level 3:  -∞ ----------------------------> 80 ----------------------------------> +∞
           |                                |
Level 2:  -∞ ------------> 40 -----------> 80 ------------>120 ----------------> +∞
           |               |               |                |
Level 1:  -∞ ---->20 ----> 40 ---->60 ---->80---->100 ---> 120 ----> 140 --------> +∞
           |       |       |       |       |       |         |         |
Level 0:  -∞--10--20--30--40--50--60--70--80--90--100--110--120--130--140--150--> +∞

```

*Notice the perfect alignment and predictable spacing, which is a direct result of the rule, not chance.*

### How Operations Work

Operations are about maintaining the 1-2 Rule.

### **Insertion**

When you insert a node, you add it to the bottom level and then check if the rule has been broken.

- **Violation:** If an insertion creates a "gap" of **three** nodes on a lower level between two higher-level nodes, the rule is violated.
- **Fix (Promotion):** To fix this, the middle of the three nodes is **promoted** to the level above. This promotion might cascade upwards if it causes another violation on a higher level.

**Diagram of a Forced Promotion:**

**1. Invalid State (Gap of 3):**
Inserting node `35` violates the rule between `20` and `40`.

```
Level 1:  ... -> 20 ------> 40 ----> ...
                 |          |
Level 0:  ... --20--30--35--40-- ...

```

**2. After Forced Promotion:**
Node `30` is promoted to Level 1 to fix the gap.

```
Level 1:  ...-> 20 -> 30 --> 40 ----> ...
                |    |       |
Level 0:  ... --20---30--35--40-- ...

```

### **Deletion**

Deletion works in reverse.

- **Violation:** If deleting a node creates a "gap" of **zero** nodes on a lower level, the rule is violated.
- **Fix (Demotion/Merge):** To fix this, a node from the level above is **demoted**, or two adjacent nodes are merged. This ensures the gaps are always filled.

### Key Points & Trade-Offs

### **Important Points**

- **No Randomness:** The structure is determined entirely by the sequence of operations. The same inserts and deletes will **always** produce the exact same final structure.
- **Worst-Case Guarantee:** The primary advantage is a **guaranteed `O(log n)`** time complexity for all operations. There is no "unlucky" case.

### **The Trade-Off: Complexity**

- **The Downside:** The deterministic skip list loses the main appeal of its randomized cousin: **simplicity**. The logic for handling promotions and demotions is complex and similar to the rebalancing rotations in balanced binary trees (like AVL or Red-Black Trees).
- **Practical Use:** Because of this complexity, if a developer needs a guaranteed `O(log n)` data structure, they will typically use a well-tested library implementation of a balanced tree. Therefore, deterministic skip lists are more of an academic concept than a commonly used tool in the industry.

### Summary: Randomized vs. Deterministic

| Feature | Randomized Skip List | Deterministic Skip List |
| --- | --- | --- |
| **Balancing Method** | Random coin flips (probabilistic) | Fixed rules (e.g., the 1-2 Rule) |
| **Performance** | **Expected** `O(log n)` (extremely high probability) | **Guaranteed** worst-case `O(log n)` |
| **Implementation** | Relatively simple and elegant | Complex, requires logic similar to tree rotations |
| **Structure** | Varies with each build | Always the same for the same sequence of operations |
| **Primary Use Case** | Concurrent libraries (e.g., Java), databases (Redis) | Real-time systems, applications needing hard guarantees |