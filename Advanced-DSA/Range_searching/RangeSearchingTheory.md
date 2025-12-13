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
    - PST: Priority Search Trees
    - K-Dimensional Tree (KD Tree)

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


<!-- ![image backup](https://i.ibb.co/MDqxtR7P/image.png) --> 
![image](https://private-user-images.githubusercontent.com/124666305/523498266-519fa744-44d7-424d-b6ee-8da8b62ed662.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjUxMzY1MDIsIm5iZiI6MTc2NTEzNjIwMiwicGF0aCI6Ii8xMjQ2NjYzMDUvNTIzNDk4MjY2LTUxOWZhNzQ0LTQ0ZDctNDI0ZC1iNmVlLThkYThiNjJlZDY2Mi5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUxMjA3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MTIwN1QxOTM2NDJaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1hMmIyODE2ZDZkNWFmMDI4YWE0MzZjNmUxZjkxMGViMWYzYjg4MmM0N2EzZTRmYmRiZmViNDc3Y2FkNDEwOGVkJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.rouy4g2z9ZkaqY8TCasTHG5GccRdteVnKsU5WFS9Z9E)
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
<!-- backup image url -->
<!-- ![image also availble in freeform app on mac](https://i.ibb.co/QBMFHVm/image.png) -->

![github url for image](https://private-user-images.githubusercontent.com/124666305/523500094-dc149ecf-8eee-421c-a5e8-a991ab64e629.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjUxMzc3MDEsIm5iZiI6MTc2NTEzNzQwMSwicGF0aCI6Ii8xMjQ2NjYzMDUvNTIzNTAwMDk0LWRjMTQ5ZWNmLThlZWUtNDIxYy1hNWU4LWE5OTFhYjY0ZTYyOS5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUxMjA3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MTIwN1QxOTU2NDFaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1mYmNmYzBlODFlNjc3OTQyNjJkM2M2NTA5ZjNiOTllMDM3NTZjN2JmN2I1NzE2NTQ3ZDEzZWY0ODE4MTg2MjYwJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.9AxpSUfA3AxJM_1cdSxCR9uNH1hx-JCz1nV9nAp-OCM)
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


## **PST - Priority Search Trees**

**Basic idea**: in a query like find all points which are in range [x0,x1] && [y, infinity] here y is has a unbounded value so for this we use a max heap to represent y and for x (bounded in values) we make it as if a BST.

similarly for values of [-infinity, y] or we can say y <= y0 we can use a min heap to represent y coordinates, note that we are not using 2 data structures rather a single tree where each point(x,y) in the tree node represent max heap node, but it is build like a BST

eg. 
![](https://i.ibb.co/zH4Jfm7H/image.png)
 

Priority Search Trees (PSTs) offer a specialized and more memory-efficient alternative to 2D Range Trees, particularly excelling in specific types of queries where 2D Range Trees can be less optimal. 

While both are used for querying points in a two-dimensional space, their underlying structures and ideal use cases differ significantly.

> The primary advantage of a Priority Search Tree lies in its efficiency for **three-sided range queries**. This is a query that is bounded on three sides and infinite on one, for example, finding all points `(x, y)` such that `x1 <= x <= x2` and `y >= y_min`. takes time: **`O(log n + k)`** for three-sided queries
> 

> 2D Range Tree is designed for **four-sided orthogonal range queries,** where the query is a standard rectangle defined by `x1 <= x <= x2` and `y1 <= y <= y2`.
> 

### Basic Idea behind PST

Priority Search Trees uses Heaps for storing nodes based on y coordinates (the unbound range) and for x they use the Binary Search Trees

### Which Heap does PST uses for storing the y coordinates (Min Heap or Max Heap) ?

PSTs can use either max-heap or min-heap property depending on what type of queries you want to optimize for:

**Max-Heap PST** (What we built)

- **Heap Property**: Parent.y ≥ Child.y (maximum y at root)
- **Optimised For**: Queries of type `[x₁, x₂] × [y₀, +∞)`
- **Query**: "Find all points in x-range [x₁, x₂] with y ≥ y₀"
- **Use Cases**: "Points above a threshold", "higher priority items"

**Min-Heap PST**

- **Heap Property**: Parent.y ≤ Child.y (minimum y at root)
- **Optimised For**: Queries of type `[x₁, x₂] × (-∞, y₀]`
- **Query**: "Find all points in x-range [x₁, x₂] with y ≤ y₀"
- **Use Cases**: "Points below a threshold", "lower priority items"

building a PST from scratch: 

![](https://i.ibb.co/B2rxcWz7/image.png)

### Max-Heap PST Query Design

***Overview***

Design for efficiently answering 2D range queries of the form:
**"Find all points with x ∈ [x₁, x₂] and y ≥ y₀"**

**Core Data Structure Components**

1. **PST Node Structure**

```java
PSTNode:
├── Point (x, y, optional_data)
├── Left Child Pointer
├── Right Child Pointer  
└── Splitting X-value (for BST property) // this node will have the value based on which on left are values <= splitXnode and on right are values > splitXNode

this splitXNode is used for querying purpose efficintly
```

Reasons for using `SplittingXValue` in node: 

- while querying deciding which way to go left or right after `curr` node using current nodes `x` value might result wrong because `curr` node’s `x` might not be the actual splitting boundary, explained below:-
- **During Construction Time:**
    
    ```java
    At root node (4,13):
    - We have remaining elements: [(1,6), (3,2), (5,10), (8,5)]
    - We calculate splitX = 3.0 based on these remaining elements (eg. 4 elements (0,1,2,3) median index = 1, 
    	fetch value at index 1 (3,2) splitNodeX = 3 
    - so (on left we send values <= splitNodeX) on (right we send values > splitNodeX)
    - We split: Left gets [(1,6)], Right gets [(3,2), (5,10), (8,5)]
    
    				(4,13)
    				/.    \
    		 (1,16).  (3,2), (5,10), (8,5)
    		 
    ```
    
- **Main Reason to store the `splitNodeX`  is that During the Query Time:**
    
    ```java
    At node (4,13):
    - we can not decide to go left or right based on current nodes x value i.e 4 ❌ (because we while creation we had remaining elements)
    - Now We DON'T have the remaining elements anymore!
    - We only have the node's point: (4,13)
    - We need to know: "How do I decide which subtree to visit?"
    - so for that we stored the splitNodeX in the Node already to compare
    
    note: note if we used the curr.x value to compare to go left or right for query x=[3,5) y >= 5 thenwe would have 
    			end up in left sub tree how ? curr nodes 4,13's x = 4 > 3 so we go left for smaller values, and we end up in wrong tree
    			so this is the reason we use splitXNode to remember that on what basis we divided the tree for X nodes at the time of creation.
    ```
    

**2. Tree Properties**

- **Max-Heap Property**: Parent.y ≥ Child.y
- **BST Property**: Left subtree x < splitting_x ≤ Right subtree x
- **Balance**: O(log n) height via median splitting

**Query Algorithm Design**

Phase 1: Tree Traversal Strategy

Decision Tree at Each Node:

```java
At node N with point (x, y):

1. Y-PRUNING CHECK:
   if N.y < y₀:
       └── PRUNE: Skip entire subtree (key optimization!)
   
2. POINT INCLUSION CHECK:
   if x₁ ≤ N.x ≤ x₂ AND N.y ≥ y₀:
       └── INCLUDE: Add point to result set
   
3. SUBTREE EXPLORATION:
   Determine which children to visit based on x-range overlap
```

**Phase 2: Subtree Selection Logic**

X-Range Overlap Analysis:

```java
Given query range [x₁, x₂] and node's splitting value S:

LEFT SUBTREE (x < S):
├── Visit if: x₁ <= S

RIGHT SUBTREE (x ≥ S):  
├── Visit if: x₂ > S

BOTH SUBTREES:
└── Visit if: x₁ <= S ≤ x₂ (range spans splitting point)
```

### time complexity

1. **Your sorting optimization is crucial** - by sorting once at the beginning instead of at every recursive call, you avoided the O(n log²n) trap and achieved optimal O(n log n) construction time.
2. **Query performance is optimal** - O(log n + k) is the theoretical best you can achieve for this type of 2D range query, and your implementation achieves it.
3. **The y-pruning is powerful** - when the heap property allows early termination, queries can run in O(1) time in the best case.
4. **Space efficiency is excellent** - O(n) space is optimal for storing n points with additional structure.

The time complexity you wrote in your comment was mostly correct, but let me clarify: the overall construction is O(n log n), not O(n log n) + O(n log n). The sorting and tree building both contribute O(n log n) terms, but they're sequential, so the total remains O(n log n).



----
----

## **K-Dimensional Trees (K-D Trees)**

A k-D tree is a binary tree that recursively partitions k-dimensional space by splitting along different dimensions at each level. It's particularly effective for:

- Range searching in k-dimensional space
- Nearest neighbour searches
- Point location queries

<!-- ![backup image url](https://i.ibb.co/4gDj2H74/image.png) -->
![github img url](https://private-user-images.githubusercontent.com/124666305/523502938-aa9e1978-a0d3-47a0-9031-ea86ee3f6515.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjUxMzk5MzAsIm5iZiI6MTc2NTEzOTYzMCwicGF0aCI6Ii8xMjQ2NjYzMDUvNTIzNTAyOTM4LWFhOWUxOTc4LWEwZDMtNDdhMC05MDMxLWVhODZlZTNmNjUxNS5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUxMjA3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MTIwN1QyMDMzNTBaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1hNWZhNWRjYjQ0NzJhYmY4YTQwMjA0MzM1NTI2MWY1MGYwMTAxZGU1NWY2OTk4ZTE5MmZjOTdiMjdhNzgzMmNiJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.hAiyPw67hMZoWAhzecgDr_Y7f-utnx89uyZjDHmBO3A)


![](https://i.ibb.co/Nn71yJ32/image.png)

![](https://i.ibb.co/nNS5cNhf/image.png)


### Basic Idea

- At each level of the tree, we split the points along a different dimension
- Typically cycle through dimensions: level 0 splits on x-coordinate, level 1 on y-coordinate, level 2 on z-coordinate, etc.
- Each internal node stores a point and represents a splitting hyperplane
- Left subtree contains points with smaller coordinate values in the splitting dimension
- Right subtree contains points with larger coordinate values

### Construction Algorithm

```java
buildKDTree(points, depth):
    if points is empty:
        return null
    
    axis = depth % k  // cycle through dimensions
    
    // Sort points by the current axis
    sort points by axis-th coordinate
    
    // Choose median as the splitting point
    median = points.length / 2
    
    node = new Node(points[median])
    node.left = buildKDTree(points[0...median-1], depth + 1)
    node.right = buildKDTree(points[median+1...end], depth + 1)
    
    return node
```

### Time Complexity

- Construction: `O(n log²n)` using sorting at each level
- Can be optimised to `O(n log n)` using Q*uickselect* for median finding

**Recurrence Relation:**

- `T(n) = 2T(n/2) + O(n log n) = **O(n log² n)**` with sorting
- `T(n) = 2T(n/2) + O(n) = **O(n log n)**` with quickselect

### Building a k-D Tree: where `k=3`

Let's take these 3D points:
**Points: `[(3,6,1), (17,15,20), (13,15,10), (6,12,1), (9,1,25), (2,7,3), (10,19,5)]`**

### Step 1: Root Node (Depth 0, Split on X-axis)

- Current points: [(3,6,1), (17,15,20), (13,15,10), (6,12,1), (9,1,25), (2,7,3), (10,19,5)]
- Sort by x-coordinate: [(2,7,3), (3,6,1), (6,12,1), (9,1,25), (10,19,5), (13,15,10), (17,15,20)]
- Median index: 3 → **(9,1,25)** becomes root
- Left subtree: [(2,7,3), (3,6,1), (6,12,1)]
- Right subtree: [(10,19,5), (13,15,10), (17,15,20)]

```
             (9,1,25) [x-split at x=9]
            /                        \
[(2,7,3), (3,6,1), (6,12,1)]     [(10,19,5), (13,15,10), (17,15,20)]
```

### Step 2: Left Subtree (Depth 1, Split on Y-axis)

- Points: [(2,7,3), (3,6,1), (6,12,1)]
- Sort by y-coordinate: [(3,6,1), (2,7,3), (6,12,1)]
- Median: **(2,7,3)**
- Left subtree: [(3,6,1)]
- Right subtree: [(6,12,1)]

### Step 3: Right Subtree of Root (Depth 1, Split on Y-axis)

- Points: [(10,19,5), (13,15,10), (17,15,20)]
- Sort by y-coordinate: [(13,15,10), (17,15,20), (10,19,5)]
- Median: **(17,15,20)**
- Left subtree: [(13,15,10)]
- Right subtree: [(10,19,5)]

### Step 4: Depth 2 Nodes (Split on Z-axis)

**Left-Left: (3,6,1)** - becomes leaf (single point)

**Left-Right: (6,12,1)** - becomes leaf (single point)

**Right-Left: (13,15,10)** - becomes leaf (single point)

**Right-Right: (10,19,5)** - becomes leaf (single point)

```java
                    (9,1,25) [x-split, depth=0]
                   /                        \
                  /                          \
          (2,7,3) [y-split, depth=1]    (17,15,20) [y-split, depth=1]
         /                 \             /                         \
        /                   \           /                           \
   (3,6,1) [z-split]    (6,12,1)  (13,15,10) [z-split]         (10,19,5)
   [leaf, depth=2]      [z-split]  [leaf, depth=2]             [z-split]
                        [leaf, depth=2]                        [leaf, depth=2]
```

### Dimension Cycling in 3D

**Pattern: axis = depth % 3**

- **Depth 0**: axis = 0 % 3 = 0 (X-axis)
- **Depth 1**: axis = 1 % 3 = 1 (Y-axis)
- **Depth 2**: axis = 2 % 3 = 2 (Z-axis)
- **Depth 3**: axis = 3 % 3 = 0 (X-axis again)
- **Depth 4**: axis = 4 % 3 = 1 (Y-axis again)

### How k-D Trees Stand Out vs Normal Searching

**Normal/Naive Searching in 3D Space**

Without k-D trees, how would we search for points in 3D space?

**Linear Search Approach:**

```java
*// Find all points in range [x1,x2] × [y1,y2] × [z1,z2]*
vector<Point> rangeSearch(vector<Point>& points, Range3D range) {
    vector<Point> result;
    for (Point p : points) {  *// O(n) - check every single point*
        if (p.x >= range.x1 && p.x <= range.x2 &&
            p.y >= range.y1 && p.y <= range.y2 &&
            p.z >= range.z1 && p.z <= range.z2) {
            result.push_back(p);
        }
    }
    return result;
}
```

**Time Complexity: `O(n)`** - Must check every single point!

**k-D Tree's Smart Elimination Strategy**

The key insight: **k-D trees eliminate entire regions of space without checking individual points!**

**Example: Range Search [4,12] × [5,18] × [2,15]**

```java
Using our previous tree with root (8,14,8):

                    (8,14,8) [X-split at x=8]
                   /                         \
        (2,7,3) [Y-split]              (12,3,18) [Y-split]
       /              \                /                \
   ...                ...           ...                ...
```

**Step 1: At root (8,14,8), X-split at x=8**

- Query range: x ∈ [4,12]
- Since 4 ≤ 8 ≤ 12, we need to search BOTH subtrees
- But notice: if our query was x ∈ [1,6], we could **completely skip the right subtree!**

**Step 2: Left child (2,7,3), Y-split at y=7**

- Query range: y ∈ [5,18]
- Since 5 ≤ 7 ≤ 18, search both subtrees
- But if query was y ∈ [10,18], we'd **skip the left subtree entirely!**

The Power of Pruning: 

**Example showing massive elimination:**
Suppose we search for range [15,20] × [10,25] × [5,30]:

```java
rangeSearchKD(root=(8,14,8), range=[15,20]×[10,25]×[5,30]):
    *// x-split at 8, query x ∈ [15,20]// Since 15 > 8, we can COMPLETELY IGNORE left subtree!// This eliminates potentially thousands of points with one comparison!*
    return rangeSearchKD(rightChild, range)
```

**Comparison:**

- **Linear search**: Check all n points → O(n)
- **k-D tree**: Eliminate half the points with one comparison → O(√n + k) average

### [Optimisation] QuickSelect: a way to convert finding median from `nlogn` → `n` for median finding

We find median of array at each level (for building of tree only)

- how we usually find median is by sorting array and then taking the middle element, and recursively call for left and right subtrees. this results in `O(n*logn)` time for finding median and total time of building k-d tree : `O(n*logn*logn)`
- We can optimise this by using quick select (the pivot concept taken from quick sort), this results in `O(n)` time for median finding and total k-d tree building in `O(n*logn)`

> ⭐️ The Quick Select Approach is used to find the `kth` smallest or larger element in a unsorted array in linear time
> 

Complete Step-by-Step Example of how does quick select find the median in linear time: 

**Problem**: Find the **4th smallest element** (k=4) in array: `[12, 3, 5, 7, 19, 26, 18, 4, 15]`

Let's trace through the algorithm completely:

### Initial Setup

```java
Array: [12, 3, 5, 7, 19, 26, 18, 4, 15]
Indices: 0  1  2  3   4   5   6  7   8
Goal: Find 4th smallest (k=3, since 0-indexed)
Call: quickSelect(arr, left=0, right=8, k=3)
```

---

Step 1: First Partition Call

**Choose Pivot**

```java
Array: [12, 3, 5, 7, 19, 26, 18, 4, 15]
Pivot = arr[right] = arr[8] = 15
```

**Partition Process**

**Goal**: Put all elements ≤ 15 on left, > 15 on right

```java
i = left - 1 = -1  *// i tracks the "small elements" boundary*
j loops from left=0 to right-1=7

j=0: arr[0]=12 ≤ 15? YES
     i++; i=0
     swap(arr[0], arr[0]) → [12, 3, 5, 7, 19, 26, 18, 4, 15]
     
j=1: arr[1]=3 ≤ 15? YES  
     i++; i=1
     swap(arr[1], arr[1]) → [12, 3, 5, 7, 19, 26, 18, 4, 15]
     
j=2: arr[2]=5 ≤ 15? YES
     i++; i=2  
     swap(arr[2], arr[2]) → [12, 3, 5, 7, 19, 26, 18, 4, 15]
     
j=3: arr[3]=7 ≤ 15? YES
     i++; i=3
     swap(arr[3], arr[3]) → [12, 3, 5, 7, 19, 26, 18, 4, 15]
     
j=4: arr[4]=19 ≤ 15? NO
     Do nothing
     
j=5: arr[5]=26 ≤ 15? NO  
     Do nothing
     
j=6: arr[6]=18 ≤ 15? NO
     Do nothing
     
j=7: arr[7]=4 ≤ 15? YES
     i++; i=4
     swap(arr[4], arr[7]) → [12, 3, 5, 7, 4, 26, 18, 19, 15]
```

**Final Pivot Placement**

```java
swap(arr[i+1], arr[right])
swap(arr[5], arr[8]) → [12, 3, 5, 7, 4, 15, 18, 19, 26]

Final state: [12, 3, 5, 7, 4, 15, 18, 19, 26]
              ←--≤15--------→ ↑   ←--→15--→
                           pivot
                          index=5
```

**Decision Point**

```java
Pivot is at index 5
We want k=3 (4th smallest element)
Since k=3 < pivotIndex=5, search LEFT side
Call: quickSelect(arr, left=0, right=4, k=3)
```

---

**Step 2: Second Partition Call**

```java
Array: [12, 3, 5, 7, 4, 15, 18, 19, 26]
Focus on: [12, 3, 5, 7, 4] (indices 0-4)
Pivot = arr[4] = 4
```

**Partition Process**

```java
i = -1

j=0: arr[0]=12 ≤ 4? NO
     Do nothing
     
j=1: arr[1]=3 ≤ 4? YES
     i++; i=0  
     swap(arr[0], arr[1]) → [3, 12, 5, 7, 4, 15, 18, 19, 26]
     
j=2: arr[2]=5 ≤ 4? NO
     Do nothing
     
j=3: arr[3]=7 ≤ 4? NO  
     Do nothing
```

### Final Pivot Placement

```java
swap(arr[i+1], arr[right])  
swap(arr[1], arr[4]) → [3, 4, 5, 7, 12, 15, 18, 19, 26]

Final state: [3, 4, 5, 7, 12, 15, 18, 19, 26]
              ↑  ↑   ←--→4--→
            ≤4  pivot   >4
                index=1
```

Decision Point

```java
Pivot is at index 1
We want k=3  
Since k=3 > pivotIndex=1, search RIGHT side
Call: quickSelect(arr, left=2, right=4, k=3)
```

---

**Step 3: Third Partition Call**

Current Array and Setup

```java
Array: [3, 4, 5, 7, 12, 15, 18, 19, 26]
Focus on: [5, 7, 12] (indices 2-4)
Pivot = arr[4] = 12
```

**Partition Process**

```java
i = 1  *// left-1 = 2-1 = 1*

j=2: arr[2]=5 ≤ 12? YES
     i++; i=2
     swap(arr[2], arr[2]) → [3, 4, 5, 7, 12, 15, 18, 19, 26]
     
j=3: arr[3]=7 ≤ 12? YES
     i++; i=3  
     swap(arr[3], arr[3]) → [3, 4, 5, 7, 12, 15, 18, 19, 26]
```

**Final Pivot Placement**

```java
swap(arr[i+1], arr[right])
swap(arr[4], arr[4]) → [3, 4, 5, 7, 12, 15, 18, 19, 26]

Pivot is at index 4
We want k=3
Since k=3 < pivotIndex=4, search LEFT side  
Call: quickSelect(arr, left=2, right=3, k=3)
```

**Step 4: Fourth Partition Call**

Current Array and Setup

```java
Array: [3, 4, 5, 7, 12, 15, 18, 19, 26]
Focus on: [5, 7] (indices 2-3)
Pivot = arr[3] = 7
```

Partition Process

```java
i = 1  *// left-1 = 2-1 = 1*

j=2: arr[2]=5 ≤ 7? YES
     i++; i=2
     swap(arr[2], arr[2]) → [3, 4, 5, 7, 12, 15, 18, 19, 26]
```

Final Pivot Placement

```java
swap(arr[i+1], arr[right])
swap(arr[3], arr[3]) → [3, 4, 5, 7, 12, 15, 18, 19, 26]

Pivot is at index 3
We want k=3
Since k=3 == pivotIndex=3, WE FOUND IT!
```

Final Result

---

**Answer**: The **4th smallest element** is `arr[3] = 7`

**Verification**:
Sorted array would be: `[3, 4, 5, 7, 12, 15, 18, 19, 26]`
4th smallest (index 3): `7` ✓

## Time Complexity Analysis

**Each step eliminated roughly half the elements:**

- Step 1: 9 elements → 5 elements
- Step 2: 5 elements → 3 elements
- Step 3: 3 elements → 2 elements
- Step 4: 2 elements → Found!

**Pattern**: n → n/2 → n/4 → n/8 → ...

**Work done**: O(n) + O(n/2) + O(n/4) + ... = O(n)

**Visual Summary**

```java
Initial: [12, 3, 5, 7, 19, 26, 18, 4, 15]
                                       ↑ pivot=15

Step 1:  [12, 3, 5, 7, 4] | [15] | [18, 19, 26]
                       ↑ pivot=4        

Step 2:  [3] | [4] | [5, 7, 12]
                ↑ pivot=4  

Step 3:  [5, 7] | [12]
             ↑ pivot=7 

Step 4:  [5] | [7] 
               ↑ FOUND! k=3
```

This is why QuickSelect is so powerful - it eliminates large portions of the search space at each step, giving us O(n) average time complexity!

so quick select keeps dividing the array: 

```java
TO(n) = O(n) + O(n/2) + O(n/4)....  => O(n). - average case

but in word case: O(n*n)
```

### QuickSelect visualised

see left to right

<!-- ![backup image url](https://i.ibb.co/35xYPtc4/image.png) -->

![github img url](https://private-user-images.githubusercontent.com/124666305/523503841-03607125-bb5f-4287-89ea-3c57ad48453b.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjUxNDA2NzEsIm5iZiI6MTc2NTE0MDM3MSwicGF0aCI6Ii8xMjQ2NjYzMDUvNTIzNTAzODQxLTAzNjA3MTI1LWJiNWYtNDI4Ny04OWVhLTNjNTdhZDQ4NDUzYi5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUxMjA3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MTIwN1QyMDQ2MTFaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT05MWI3N2UzYzRkNGI4YTdmOWVhZjE1NGUwYjU2NjdmOGRmZTJjYTA5YjRmYzExN2RjYjE1YjZlZTBlYThkYmJiJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.UtbJWbfruE2ixOeFm7z1k3NRtFnL2ZC_wCQk3nEMkso)

---