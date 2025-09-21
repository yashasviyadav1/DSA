# Range Searching

Range Searching: 

- 1D searching
    - Naive approach
    - sorted array + binary search
    - Balanced Tree implementation using AVL for range searching
    - Interval Trees
    - Segment Trees
- 2D searching
    - naive approch (O(n)
    - 2 Dimensional Range Tree

## Computational Geometry:
Computational geometry is the subfield of computer science that deals with designing, analyzing, and implementing algorithms for problems involving geometric objects like points, lines, and polygons

## One Dimensional :Range Searching

One Dimensional Range Searching is a fundamental problem in computational geometry where we need to efficiently answer queries about elements within a specified range on a one-dimensional line. Given a set of points on a line, we want to preprocess them to quickly answer range queries.

### Problem Definition

**Input**: A set S of n points on a real line, typically represented as an array of values.

**Query Types**:

- **Range Query**: Report all points in range [a, b]
- **Range Count**: Count number of points in range [a, b]
- **Range Sum**: Sum of all points in range [a, b]
- **Range Min/Max**: Find minimum/maximum point in range [a, b]

**Operations**:

- **Static**: Points don't change after preprocessing
- **Dynamic**: Support insertions and deletions
- **Updates**: Support point value modifications


## Approaches for One Dimensional Range Searching

### 1. Naive Approach

**Method**: Store points in an unsorted array and scan linearly for each query

**Complexity Analysis**:

- **Preprocessing**: O(1) - no preprocessing needed
- **Storage**: O(n)
- **Range Query**: O(n) - scan entire array
- **Range Count**: O(n)
- **Insert/Delete**: O(1) - just append or mark as deleted

**Advantages**:

- Simple implementation
- Fast updates
- No preprocessing time
- Memory efficient

**Disadvantages**:

- Slow queries
- Not suitable for frequent queries

**Use Case**: When updates are very frequent and queries are rare.

---

### 2. Sorted Array + Binary Search

**Method**: Sort the array once, then use binary search to find range boundaries.

**Complexity Analysis**:

- **Preprocessing**: O(n log n) - sorting
- **Storage**: O(n)
- **Range Query**: O(log n + k) where k = number of points in range
- **Range Count**: O(log n)
- **Insert**: O(n) - need to maintain sorted order
- **Delete**: O(n) - need to shift elements

**Advantages**:

- Excellent query performance
- Simple to implement
- Memory efficient
- Good for range counting

**Disadvantages**:

- Expensive insertions/deletions
- Static or semi-static scenarios only
- Range sum requires additional preprocessing

**Use Case**: Static data with frequent queries, or when query performance is critical.

---

### 3. Binary Search Tree (BST) with AVL Balancing

we already did the AVL implementation earlier so we use the same code, now we only need to add 1 new function i.e `rangeSearch(low,high)`

→ insert all elements into a avl tree

→ now pass the low and high of the range to function rangeSearch of AVL

→ now we have 3 conditions

```java
rangeSearch(curr, low, high){
	-> our curr node is larger then the lowbound of range, means this curr may or may not be in range, and since it is larger then low,
	   means there can be smaller elements on left subtree that might be in range, so go left
	-> we have already traversed left, now if our curr element is in range then include this in array (as smaller element already are
	   there add this)
	-> our curr is smaller then high means it may or may not be in range, since its smaller then high on its right subtree there can 
	   be larger nodes that migth be in range, so go right
```

**Method**: Store points in a balanced binary search tree to maintain sorted order dynamically.

**AVL Balancing**: Maintains tree height as O(log n) through rotations.

**Complexity Analysis**:

- **Preprocessing**: O(n log n) - build balanced tree
- **Storage**: O(n)
- **Range Query**: O(log n + k) where k = number of points in range
- **Range Count**: O(log n) with size augmentation
- **Range Sum**: O(log n) with sum augmentation
- **Insert/Delete**: O(log n) with rebalancing

**Advantages**:

- Efficient dynamic operations
- Balanced performance for all operations
- Can be augmented for additional information (size, sum)
- Maintains sorted order

**Disadvantages**:

- More complex implementation
- Higher constant factors than arrays
- Requires rebalancing operations

**Use Case**: Dynamic scenarios with frequent insertions, deletions, and queries.

---

### 4. Interval Tree

![image.png](https://i.ibb.co/KcnM4161/image.png)

**Method**: Specialized tree structure for storing intervals and answering interval overlap queries.

**Complexity Analysis**:

- **Preprocessing**: O(n log n) - build tree
- **Storage**: O(n)
- **Interval Search**: O(log n) - find any overlapping interval
- **All Overlapping**: O(log n + k) where k = number of overlapping intervals
- **Insert/Delete**: O(log n)

**Advantages**:

- Specialized for interval queries
- Efficient overlap detection
- Dynamic operations supported
- Can find all overlapping intervals

**Disadvantages**:

- More complex than BST
- Specific to interval problems
- Not suitable for point queries

**Use Case**: When dealing with intervals rather than points, such as time ranges, geometric intervals.

---

### 5. Segment Tree

```java

Segment Trees (sum of elements)
arr = {5, 8, 6, 3, 2, 7, 2, 6}

                              38 [0, 7]
                      /                     \
                     /                       \
              22 [0, 3]                            16 [4, 7]
             /          \                        /           \
            /            \                      /             \
        13 [0, 1]    9 [2, 3]               8 [4, 5]            8 [6, 7]
      /      \        /      \                /     \            /     \
     /        \      /        \              /       \          /       \
 5 [0,0]   8 [1,1]  6 [2,2]   3 [3,3]      2 [4,4]  7 [5,5]  2 [6,6]  6 [7,7]
```

**Method**: Binary tree where each node represents a range and stores aggregate information about that range.

**Tree Structure**:

- Each leaf represents a single element
- Each internal node represents the union of its children's ranges
- Each node stores aggregate information (sum, min, max, etc.)

**Note: The 4*n size for segment tree is a safe upper bound to ensure we never run out of space**

**Algorithm**: Build the tree bottom-up where each leaf represents a single array element and each internal node represents the union of its children's ranges. Each node stores aggregate information about its range. For range queries, traverse the tree and combine results from nodes whose ranges intersect with the query range. Use three cases: complete overlap (return node's value), no overlap (return identity), and partial overlap (recurse on children).

**Complexity Analysis**:

- **Preprocessing**: O(n) - build tree
- **Storage**: O(4n) ≈ O(n)
- **Range Query**: O(log n)
- **Point Update**: O(log n)
- **Range Update**: O(log n) with lazy propagation

**Advanced Features**:

- **Lazy Propagation**: Efficient range updates
- **Persistent Segment Tree**: Multiple versions
- **Dynamic Segment Tree**: Handle large coordinate ranges

**Advantages**:

- Excellent query and update performance
- Very versatile - works with any associative operation
- Can handle range updates efficiently
- Well-balanced between all operations

**Disadvantages**:

- More complex implementation
- Higher space complexity
- Overkill for simple problems

**Use Case**: When you need both efficient queries and updates, especially for associative operations like sum, min, max, GCD.

***how to figure out weather it is `No overlap` or `Complete overlap` or `Partial overlap` between curr node and query:*** 

![](https://i.ibb.co/MDqxtR7P/image.png)

---

### Comparison Summary

- *Where k = number of elements in the query result*
- 

| Approach | Preprocessing | Query | Update | Space | Best For |
| --- | --- | --- | --- | --- | --- |
| Naive | O(1) | O(n) | O(1) | O(n) | Rare queries, frequent updates |
| Sorted Array + Binary Search | O(n log n) | O(log n + k) | O(n) | O(n) | Static data, frequent queries |
| AVL Tree | O(n log n) | O(log n + k) | O(log n) | O(n) | Dynamic, balanced operations |
| Interval Tree | O(n log n) | O(log n + k) | O(log n) | O(n) | Interval overlap queries |
| Segment Tree | O(n) | O(log n) | O(log n) | O(n) | Range aggregation queries |

---

## Two Dimensional :Range Searching

In **1D range searching**, you had:

- A set of points on a **line** (say `x`axis).
- Queries like: “Give me all points between `x1` and `x2`”.

In **2D range searching**:

- You now have **points on a plane** (each point has `(x, y)` coordinates).
- Queries look like:
    
    “Give me all points that lie inside a rectangle `[x1, x2] × [y1, y2]`.”
    
    (This rectangle is just the set of points where `x1 ≤ x ≤ x2` and `y1 ≤ y ≤ y2`.)
    

So basically:

- In 1D → intervals on a line.
- In 2D → rectangles on a plane.

### Example

Suppose you have points:

`P = {(2,3), (4,7), (5,1), (7,2), (8,6), (9,4)}`

Now query: **“All points with 4 ≤ x ≤ 8 and 2 ≤ y ≤ 6”**.

- Rectangle is from `(4,2)` (bottom-left) to `(8,6)` (top-right).
- Answer = `{(4,7 ❌), (5,1 ❌), (7,2 ✅), (8,6 ✅), (9,4 ❌)}`.
    
    So final result = `{(7,2), (8,6)}`.
    

---

### Why do we care about 2D Range Searching?

- **Databases** → queries like “find all hotels within latitude/longitude range”.
- **Graphics/Games** → finding all objects in a rectangular region of the screen.
- **Geographical maps** → retrieve all cities in a rectangular area.

### Approaches

1. **Naïve method**
    
    Just scan through all `n` points and check if each lies inside the rectangle.
    
    - Time: `O(n)` per query.
    - Simple but slow if many queries.
2. **Better structures**
    
    To answer faster, we build **special data structures**:
    
    - **2D Range Trees**
    - **Priority Search Trees**
    - **k-d Trees**
    
    These structures let you answer queries much faster than `O(n)`.

### Step-by-Step Roadmap

Here’s how we’ll cover it (without jumping too fast):

1. Naïve 2D range searching.
2. Idea of **divide-and-conquer** for splitting space.
3. Introduction to **Range Trees** (simple version first).
4. How queries work in a range tree.
5. Space and time complexities (gradually).
6. Advanced variations like Priority Search Trees and k-d Trees.

---
---
## **2D Range Tree**

Visualizing a 2D range Tree: 
![mage also availble in freeform app on mac](https://i.ibb.co/CXh8LLL/image.png)

Querying in a 2D range Tree: 
![image also availble in freeform app on mac](https://i.ibb.co/QBMFHVm/image.png)
### Introduction

A 2D Range Tree is a balanced data structure used to efficiently answer orthogonal range queries (queries of the form: find all points within a rectangular region in 2D space).

It extends the concept of a 1D range tree (like a balanced BST) into two dimensions.

### Structure

The primary structure is a balanced BST on the x-coordinates of the points.

Each node in this tree additionally stores a secondary balanced BST (called y-subtree) containing all the points in its subtree, sorted by their y-coordinates.

### Each node
- x-coordinate (primary key)
- y-subtree (all points in its subtree sorted by y)

### Query Algorithm

Given a query rectangle: [x1, x2] × [y1, y2], we want all points p = (px, py) with:

`x1 ≤ px ≤ x2`   and   `y1 ≤ py ≤ y2`

- **Split at root**:
    - Traverse down the x-tree to find the **lowest common ancestor (LCA)** of `x1` and `x2`.
    - This LCA splits the problem into two symmetric parts (left and right subtrees).
- **Canonical vs Non-Canonical Nodes**:
    - **Canonical node**: A subtree that lies **completely inside the x-range [x1, x2]**.
        - For such nodes, we can **directly query their y-subtree** for `[y1, y2]`.
    - **Non-canonical node**: A node that is a boundary case (x close to x1 or x2).
        - For these, we **check the single node’s coordinates explicitly** (not the whole subtree).
- **Processing**:
    - Walk down from the split node towards `x1`:
        - Whenever you move right, the **entire left child** is canonical → query its y-subtree.
        - Continue until reaching `x1` boundary.
    - Similarly walk down from split node towards `x2`:
        - Whenever you move left, the **entire right child** is canonical → query its y-subtree.
        - Continue until reaching `x2` boundary.

### Optimization Insight

- Yes, we only query y-subtrees for canonical nodes.
- For boundary (non-canonical) nodes, we check just the node’s y-coordinate (not its subtree).
- This avoids unnecessary traversal and improves efficiency.

### Complexity

- **Building**: `O(n log n)`
- **Querying**: `O(log² n + k)`
    - `log² n` = traversals in x + querying multiple y-subtrees.
    - `k` = number of reported points.
- **Space**: `O(n log n)` (each point is stored in multiple y-subtrees).

### Why Y-subtrees are needed

- **Naïve idea:** Search only in X-tree with condition `(a ≤ x ≤ b ∧ c ≤ y ≤ d)`.
    
    → Correct but inefficient: for every x in [a,b], you must check every point individually.
    
    → Cost = Θ(#points with x ∈ [a,b]).
    
- **With Y-subtrees:**
    
    When an X-subtree is **fully inside [a,b]**, you don’t descend further.
    
    Instead, you query its Y-subtree for y ∈ [c,d].
    
    → Cost per subtree = `O(log m + r)` where `m` = size of subtree, `r` = reported points.
    
    → Total query time = `O(log² n + k)` (where `k` = output size).


### Canonical vs Non-Canonical Nodes (Definition)

- **Canonical Node**:
    
    A node whose entire x-subtree lies inside `[x1, x2]`.
    
    - We can use its y-subtree directly.
- **Non-Canonical Node**:
    
    A node that partially overlaps the x-range.
    
    - We check only its direct x,y coordinate (not its whole subtree).

### Equality and Hashing

When storing points in **Sets or HashSets**:

- **equals()**: Ensures two points `(x1, y1)` and `(x2, y2)` are considered the same if both coordinates match.
    - Without this, Java compares by **object reference**, so duplicates may slip in.
- **hashCode()**: Required when using `HashSet` or `HashMap`.
    - Ensures objects that are `equal()` hash to the same bucket.
    - Without this, duplicate points may be stored in hash-based structures.