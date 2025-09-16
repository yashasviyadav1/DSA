# Range Searching

Range Searching: 

- 1D searching
    - Naive approach
    - sorted array + binary search
    - Balanced Tree implementation using AVL for range searching
    - Interval Trees
    - Segment Trees
- 2D searching
    - upcoming topic

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

## Comparison Summary

- *Where k = number of elements in the query result*
- 

| Approach | Preprocessing | Query | Update | Space | Best For |
| --- | --- | --- | --- | --- | --- |
| Naive | O(1) | O(n) | O(1) | O(n) | Rare queries, frequent updates |
| Sorted Array + Binary Search | O(n log n) | O(log n + k) | O(n) | O(n) | Static data, frequent queries |
| AVL Tree | O(n log n) | O(log n + k) | O(log n) | O(n) | Dynamic, balanced operations |
| Interval Tree | O(n log n) | O(log n + k) | O(log n) | O(n) | Interval overlap queries |
| Segment Tree | O(n) | O(log n) | O(log n) | O(n) | Range aggregation queries |