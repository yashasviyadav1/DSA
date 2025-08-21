
Index for this page : 
- Trees
- Binary Search Trees (BST)
- AVL Trees
- Red Black Trees
- 2-3 Trees
- B-Tree


---

# Trees

Trees are non-linear data structures that represent hierarchical data. The structures you listed are primarily used for efficient searching, insertion, and deletion operations, often improving upon the limitations of simpler structures like arrays or linked lists.

A **linear** data structure organizes elements in a sequential line, where each item has at most one element before it and one after it.

A **non-linear** data structure organizes elements in a hierarchical or networked way, where an item can be connected to multiple other items, creating branches.

Of course. Here is a detailed overview of the data structures you've listed for your M.Tech CSE coursework. This guide covers the core concepts, trade-offs, and typical use cases for each.

### **Trees**

Trees are non-linear data structures that represent hierarchical data. The structures you listed are primarily used for efficient searching, insertion, and deletion operations, often improving upon the limitations of simpler structures like arrays or linked lists.

---

### **1. Binary Search Trees (BST)**

A **Binary Search Tree** is a rooted binary tree where each node has a key, and it satisfies the BST property:

- For any given node `N`, all keys in its **left subtree** are less than `N`'s key.
- All keys in its **right subtree** are greater than `N`'s key.
- Both the left and right subtrees must also be binary search trees.
- **Performance:** In a balanced BST, operations like search, insertion, and deletion take O(logn) time on average. However, in the worst-case scenario (e.g., inserting elements in sorted order), the tree degenerates into a linked list, making these operations take O(n) time.
- **Use Case:** Serves as the fundamental basis for more advanced tree structures.w

## Key Strategies for BST Insertion & Deletion

These notes summarize the fundamental rules and logic for adding and removing nodes from a Binary Search Tree (BST). The primary goal of these strategies is to perform the operations efficiently while always maintaining the core **BST property**: for any node, all keys in its left subtree are smaller, and all keys in its right subtree are larger.

### Insertion Strategy

The strategy for insertion is straightforward and is always treated like a search operation to find the correct empty spot.

### **Main Points:**

- **Search for an Empty Spot:** The algorithm traverses the tree from the root downwards as if it were searching for the key to be inserted.
- **Follow the BST Rule:**
    - If the new key is **less than** the current node's key, move to the **left child**.
    - If the new key is **greater than** the current node's key, move to the **right child**.
- **Insert at a Null Position:** Continue this process until you reach a `null` pointer (an empty spot). This is where the new node is inserted.
- **No Duplicates:** If the key already exists in the tree, the insertion operation typically does nothing to avoid duplicates.

**Visualization of Inserting `45`:**

```
      50                                50
     /  \                              /  \
    30   70     ---> (find path) --->  30   70
   / \                                / \
  20 40                              20 40
                                         \
                                          45  <-- Insert here

```

### Deletion Strategy

Deletion is more complex because we must ensure the BST property is maintained after the node is removed. The strategy depends entirely on the number of children the node-to-be-deleted has.

### **Case 1: Deleting a Node with Zero Children (a Leaf)**

This is the simplest case.

- **Action:** Simply remove the node from the tree by setting its parent's corresponding child pointer to `null`.

**Visualization:**

```
      50              50
     /              /
    30      --->     30
   /
  20  <-- (Delete)

```

### **Case 2: Deleting a Node with One Child**

This case is also relatively simple.

- **Action:** "Bypass" the node by linking its parent directly to its single child. The node is removed, and its child takes its place.

**Visualization:**

```
      50                      50
     /                       /
    30      ---> (Delete)    40
      \
       40

```

### **Case 3: Deleting a Node with Two Children**

This is the most complex case and requires a specific replacement strategy.

- **The Problem:** You cannot simply remove the node, as it would leave two disconnected children. You must find a replacement node from within the tree that can take its place without violating the BST property.
- **The Solution:** Replace the key of the node to be deleted with the key of either its:
    1. **In-order Successor:** The single smallest key in the node's **right** subtree.
    2. **In-order Predecessor:** The single largest key in the node's **left** subtree.
- **The Two-Step Process:**
    1. **Copy the Value:** Find the successor (or predecessor) and copy its key into the node you intend to delete.
    2. **Delete the Original:** Now, the tree has a duplicate key. Make a recursive call to delete the original successor/predecessor node from its old position. This subsequent deletion will always be an easier Case 1 or Case 2 scenario.

**Visualization (using In-order Successor):**

```
      50  <-- (Delete)
     /  \
    30   70
   / \   / \
  20 40 60 80

Step 1: Find successor of 50 (smallest in right subtree) -> 60
Step 2: Copy 60 to the root node.
      60  <-- (Key replaced)
     /  \
    30   70
   / \   / \
  20 40 60 80  <-- (Duplicate 60)

Step 3: Delete the original 60 (now a Case 2 deletion).
      60
     /  \
    30   70
   / \     \
  20 40    80  <-- Final, valid tree

```

---

## AVL Trees (Theory)

An **AVL Tree** is a self-balancing Binary Search Tree (BST). Its primary advantage over a standard BST is that it **guarantees** that all major operations (search, insert, and delete) will always be completed in **O(log n) time**. It achieves this by ensuring the tree never becomes unbalanced.

The core mechanism is the **Balance Factor**. For every node, the height of its left and right subtrees can differ by at most 1.

- **Balance Factor = height(left subtree) - height(right subtree)**
- A valid Balance Factor must be **1, 0, or 1**. If it becomes **2 or +2**, the tree is unbalanced and must be rebalanced using **rotations**.

### Search Operation

The search functionality in an AVL tree is **identical to that of a standard BST**. You traverse the tree from the root, moving left if the target key is smaller and right if it's larger, until you find the key or reach a null pointer.

- **Strategy:** Standard BST search.
- **Time Complexity:** **O(log n)**. Because the tree's height is guaranteed to be logarithmic, the search path is never long.

### Insertion Operation

Insertion is a two-phase process: **insert**, then **rebalance**.

1. **Phase 1: Standard BST Insert**
    - The new node is always inserted as a leaf, following the standard BST rules to find its correct position.
2. **Phase 2: Rebalance (Bottom-Up)**
    - After insertion, the algorithm retraces its path from the new leaf back up to the root.
    - On this path, it updates the `height` of each ancestor node.
    - After each height update, it calculates the node's **Balance Factor**.
    - If a node's Balance Factor becomes -2 or +2, the algorithm performs the appropriate **rotation** (LL, RR, LR, or RL) to restore balance. This happens only once, at the first unbalanced ancestor found.
- **Strategy:** BST insert followed by a potential single or double rotation on the path back to the root.
- **Time Complexity:** **O(log n)**. The initial insertion takes O(log n), and the rebalancing path is also O(log n).

### Deletion Operation

Deletion is also a two-phase process and is the most complex operation.

1. **Phase 1: Standard BST Delete**
    - The node is deleted using one of the three standard BST deletion cases (leaf, one child, or two children).
2. **Phase 2: Rebalance (Bottom-Up)**
    - Similar to insertion, the algorithm retraces its path from the point of deletion back up to the root.
    - It updates heights and checks the Balance Factor of each ancestor.
    - **Unlike insertion, deletion may require multiple rotations** along the path to the root to fix all potential imbalances.
- **Strategy:** BST delete followed by potential rotations on the path back to the root.
- **Time Complexity:** **O(log n)**. The initial find-and-delete is O(log n), and the rebalancing path is also O(log n).

### Dry Run Examples

### **Insertion Example: Insert `2`**

**Initial Tree:**

```
      4 (BF=1)
     / \
    1   5 (BF=0)
   / \
  0   3 (BF=0)
(BF=0)
```

1. **BST Insert:** Insert `2` as the left child of `3`.

```
			      4 (BF=2) --> unbalanced
			     / \
(BF= -1)  1   5 (BF=0)
			   / \
			  0   3 (BF=1)
			     /
			    2 (BF=0) <---inserted
			    
```

Complete dry run 

![image.png](https://i.ibb.co/0RYQW4LG/image.png)

**Check Balance (Bottom-Up):**

- `2`: New leaf, balanced.
- `3`: Height becomes 2. BF = `height(2) - height(null)` = `1 - 0` = `1`. Balanced.
- `1`: Height becomes 3. BF = `height(0) - height(3)` = `1 - 2` = `1`. Balanced.
- `4`: Height becomes 4. BF = `height(1) - height(5)` = `3 - 1` = `2`. **Unbalanced!**
1. **Identify Case:** The unbalanced node is `4` (Left-heavy). The new node `2` was inserted into the **right** subtree of `4`'s **left** child (`1`). This is a **Left-Right (LR) Case**.
2. **Perform Rotations:**
    - **Step A (Left Rotate on `1`):** The subtree at `1` is rotated left. `3` becomes the new root of this subtree.
    - **Step B (Right Rotate on `4`):** The tree is now in a Left-Left state. A right rotation is performed on the unbalanced node `4`. `3` becomes the new root of the whole tree.
3. **Final Balanced Tree:**

```
      3
     / \
    1   4
   / \   \
  0   2   5

```

### **Deletion Example: Delete `4`**

**Initial Tree:**

```
      4
     / \
    1   5
   / \
  0   3

```

1. **BST Delete (Case 3):** Node `4` has two children.
    - **Find Successor:** The in-order successor (smallest in the right subtree) is `5`.
    - **Copy Value:** Copy `5` into the node to be deleted. The tree is temporarily invalid with two `5`s.
        
        ```
           5 (key replaced)
          / \
         1   5
        / \
        0   3
        
        ```
        
    - **Delete Successor:** Delete the original `5`. This is a Case 1 (leaf) deletion.
2. **Check Balance (Bottom-Up):** After the standard BST deletion, the tree looks like this:
    
    ```
        5 (balancing factor = 2) --> unbalance 
       /
      1
     / \
    0   3
    
    ```
    

* Now, we check balance factors. The root `5` has a BF of `height(1) - height(null)` = `2 - 0` = `2`. **Unbalanced!**
3.  **Identify Case:** The unbalanced node is `5` (Left-heavy). We check the balance factor of its left child (`1`), which is `BF(1) = height(0) - height(3) = 1 - 1 = 0`
4.  **Perform Rotation:** Since the BF of the left child is `0`, this is treated as a **`Left-Left (LL)` Case**. We perform a single **`Right Rotation`** on the unbalanced node `5`.
5.  **Final Balanced Tree:**

```
      1
     / \
    0   5
       /
      3
      
      final tree after deletion

```

### Performance Summary

| Operation | Time Complexity (Worst Case) |
| --- | --- |
| **Search** | **O(log n)** |
| **Insertion** | **O(log n)** |
| **Deletion** | **O(log n)** |

----
----

 


## <b>Red-Black Trees</b>

![red black tree image](https://i.ibb.co/RTZfN2Tg/image.png)

Red Black tree is a BST, is balanced (not very strictly), has an extra color property to the nodes, focuses on making insertion and deletions fast. since rotation are lesser but since it is not strictly balanced therefore searching is bit slower as compared to AVL (which are strictly balanced)


The Problem with AVL Trees
An AVL tree is a perfectionist. It must be perfectly balanced (the height difference between any two subtrees can be at most 1). To maintain this strict balance, an AVL tree might have to perform many rotations after an insertion or deletion, potentially all the way up to the root of the tree. This can be slow if you're constantly adding and removing nodes.

What Red-Black Trees Do Differently
A Red-Black tree is more pragmatic. It's "good enough" balanced. It uses a clever set of rules about node colors to ensure the tree never gets too lopsided, guaranteeing O(log n) performance, but it doesn't enforce the super-strict balance of an AVL tree.

This "less strict" balancing is its main advantage. It means that to restore balance after an insertion or deletion, a Red-Black tree needs far fewer rotations.

Insertion: A Red-Black tree requires at most 2 rotations.

Deletion: A Red-Black tree requires at most 3 rotations.

An AVL tree, on the other hand, could require up to O(log n) rotations for a deletion.


### Properties of Red-Black Trees
A Red-Black Tree have the following properties:

- Node Color: Each node is either red or black.
- Root Property: The root of the tree is always black.
- Red Property: Red nodes cannot have red children (no two consecutive red nodes on any path).
- Black Property: Every path from a node to its descendant null nodes (leaves) has the same number of black nodes.
- Leaf Property: All leaves (NIL nodes) are black.

### Red-Black Tree: Insertion Fixup Scenarios

The insertion fixup process is initiated when a newly inserted **RED** node has a **RED** parent, which violates the rule that no two red nodes can be adjacent. The entire fixup strategy depends on the color of the new node's **uncle** (the parent's sibling).

### Case 1: Uncle is RED (The "Recolor" Case)

This is the non-terminal, propagating case. It solves the local issue but pushes the potential problem higher up the tree.

**The Situation:**

- The new node is **RED**.
- Its parent is **RED**.
- Its uncle is also **RED**.

**The Goal:**
To fix the local "red-red" violation and preserve the black-height by pushing the problem up to the grandparent.

**The Actions:**

1. **Recolor Parent** to **BLACK**.
2. **Recolor Uncle** to **BLACK**.
3. **Recolor Grandparent** to **RED**.

**The Outcome:**
The local violation is solved. The algorithm then treats the **grandparent** as the new problem node and repeats the entire fixup check from that position.

### Case 2: Uncle is BLACK (and forms a "Triangle")

This is a transitional case. Its only purpose is to transform the structure into the final, terminal "line" case.

**The Situation:**

- The new node is **RED**.
- Its parent is **RED**.
- Its uncle is **BLACK**.
- The path from the grandparent to the new node forms a "kink" (e.g., a Left-Right or Right-Left path).

**The Goal:**
To perform a single rotation that "straightens" the kink into a line, setting up the scenario for Case 3.

**The Actions:**

- Perform a **rotation on the parent** towards the new node.
    - For a "Left-Right" triangle, perform a **Left Rotation** on the parent.
    - For a "Right-Left" triangle, perform a **Right Rotation** on the parent.

**The Outcome:**
The "red-red" violation still exists, but the nodes now form a straight line. The algorithm immediately proceeds to Case 3 to solve the problem.

### Case 3: Uncle is BLACK (and forms a "Line")

This is the **terminal case**. It completely solves the violation, and the insertion process ends.

**The Situation:**

- The new node is **RED**.
- Its parent is **RED**.
- Its uncle is **BLACK**.
- The path from the grandparent to the new node is a straight line (e.g., a Left-Left or Right-Right path).

**The Goal:**
To perform a final rotation and recoloring to fix the "red-red" violation and restore all Red-Black Tree properties.

**The Actions:**

1. **Recolor Parent** to **BLACK**.
2. **Recolor Grandparent** to **RED**.
3. **Perform a rotation on the grandparent** away from the new node.
    - For a "Left-Left" line, perform a **Right Rotation** on the grandparent.
    - For a "Right-Right" line, perform a **Left Rotation** on the grandparent.

**The Outcome:**
The violation is resolved. The tree is now a valid Red-Black Tree. **The process is finished.**

## Scenarios under deletion of a node in Red-Black tree

lets take we deleted a `node` whenever its `Red` (we are done)

But if `node` was `BLACK`. then find its sibling lets say `w` in this case

> *2 problems can be caused by deleting nodes* in a red black tree ➖
> 
> - 2 consecutive red nodes can occur (violation)
> - no of black nodes i.e the black height from root to leaf nodes can become different in the different paths (violation)

### **Case 1: Sibling `w` is RED**

- **Situation:** The sibling is **RED**. This means the parent must be **BLACK**.
- **Fix:**
    1. Recolor the sibling `w` to **BLACK**.
    2. Recolor the parent to **RED**.
    3. Perform a **Left Rotation** on the parent.
- **Result:** This doesn't solve the problem, but it transforms it into one of the other cases (Case 2, 3, or 4). We have now ensured that the sibling is **BLACK**, so we can proceed.

### **Case 2: Sibling `w` is BLACK, and both of its children are BLACK**

- **Situation:** The sibling and its children are all **BLACK**. There are no red nodes on that side to help us.
- **Fix:**
    1. Recolor the sibling `w` to **RED**.
- **Result:** We have effectively moved the "double black" problem from `x` up to its parent. We now repeat the entire `deleteFixup` process with the parent as the new `x`. This is the **non-terminal**, propagating case.

### **Case 3: Sibling `w` is BLACK, its left child is RED, and its right child is BLACK**

- **Situation:** The sibling is **BLACK**, but it has a "near" red child that forms a triangle.
- **Fix:**
    1. Recolor the sibling `w` to **RED**.
    2. Recolor `w`'s left child to **BLACK**.
    3. Perform a **Right Rotation** on the sibling `w`.
- **Result:** This transforms the problem into the final, terminal Case 4.

### **Case 4: Sibling `w` is BLACK, and its right child is RED**

- **Situation:** The sibling is **BLACK** and has a "far" red child that forms a line. This is the **terminal** case. (note far child is a child that is away from the problem node x
- **Fix:**
    1. Recolor the sibling `w` to the parent's original color.
    2. Recolor the parent to **BLACK**.
    3. Recolor `w`'s right child to **BLACK**.
    4. Perform a **Left Rotation** on the parent.
- **Result:** The "double black" is resolved, the black-height is restored, and the entire deletion process is complete. We set `x` to the root to terminate the loop.

----
---


## <b>2-3 Trees</b>

There are 2 types of nodes in this tree

- 2 nodes → nodes with 1 data and 2 childs
- 3 nodes → nodes with 2 data values and 3 children

The time complexity of search/insert/delete is O(log N) .

A 2-3 tree is a *B-tree of order 3*.

***Properties of 2-3 tree:***

- Nodes with two children are called 2-nodes. The 2-nodes have one data value and two children
- Nodes with three children are called 3-nodes. The 3-nodes have two data values and three children.
- Data is stored in sorted order.
- It is a balanced tree.
- All the leaf nodes are at same level.
- Each node can either be leaf, 2 node, or 3 node.
- Always insertion is done at leaf.

**Search:** To search a key **K** in given 2-3 tree **T**, we follow the following procedure:

Base cases:

1. If **T** is empty, return False (key cannot be found in the tree).
2. If current node contains data value which is equal to **K**, return True.
3. If we reach the leaf-node and it doesn't contain the required key value **K**, return False.

Recursive Calls:

1. If **K** < currentNode.leftVal, we explore the left subtree of the current node.
2. Else if currentNode.leftVal < **K** < currentNode.rightVal, we explore the middle subtree of the current node.
3. Else if **K** > currentNode.rightVal, we explore the right subtree of the current node.

![image.png](https://i.ibb.co/7tf48WRj/image.png)

### Insertion process in 2-3 Trees

**Insertion:** There are 3 possible cases in insertion which have been discussed below: 

- **Case 1:** Insert in a node with only one data element 

![image.png](https://i.ibb.co/hRbgTqZc/image.png)

- **Case 2:** Insert in a node with two data elements whose parent contains only one data element.

![image.png](https://i.ibb.co/KjzZXb0c/image.png)

• **Case 3:** Insert in a node with two data elements whose parent also contains two data elements. 

 

![image.png](https://i.ibb.co/zhwX6Fdy/image.png)

### Deletion process in the 2-3 trees

*delete the following values from it: `69, 72, 99, 81`*

```java
			  [ 54 ]
             /      \
            /        \
      [ 36 ]          [ 69 | 90 ]
      /    \          /    |       \
     /      \        /     |        \
[ 18 | 27 ] [ 45 ][ 63 ][ 72 | 81 ] [ 99 ]
```

---

### **1. Deleting 69**

### **Step 1.1: Swap with In-order Successor**

First, we locate **69** in an internal node. We can't just delete it. We must **swap** it with its in-order successor, which is the smallest key in its right subtree: **72**.

- Tree *after swapping 69 and 72*:
```
              [ 54 ]
             /       \
            /         \
      [ 36 ]           [ 72 | 90 ]
      /    \          /    |       \
     /      \        /     |        \
[ 18 | 27 ] [ 45 ] [ 63 ] [69|81]   [ 99 ]
```
### **Step 1.2: Delete from Leaf**

Now, our target **69** is in a leaf node `[ 69 | 81 ]`. Since this is a 3-node (it has two keys), we can safely remove **69** without causing an underflow.

- **Final tree after deleting 69**:
```
              [ 54 ]
             /       \
            /         \
      [ 36 ]          [ 72 | 90 ]
      /    \          /    |    \
     /      \        /     |     \
[ 18 | 27 ] [ 45 ] [ 63 ] [ 81 ]  [ 99 ]
```
---

### **2. Deleting 72**

### **Step 2.1: Swap with In-order Successor**

The value **72** is in an internal node. We **swap** it with its in-order successor, **81**.

- Tree *after swapping 72 and 81*:
```
              [ 54 ]
             /      \
            /        \
      [ 36 ]          [ 81 | 90 ]
      /    \          /    |    \
     /      \        /     |     \
[ 18 | 27 ] [ 45 ] [ 63 ] [ 72 ] [ 99 ]
```
### **Step 2.2: Delete from Leaf (Causing Underflow)**

Now we delete **72** from the leaf node `[ 72 ]`. Removing the only key in a node makes it empty, causing an **underflow**. 😱

- Tree *showing the underflow*:
```
              [ 54 ]
             /      \
            /        \
      [ 36 ]          [ 81 | 90 ]
      /    \          /    |    \
     /      \        /     |     \
[ 18 | 27 ] [ 45 ] [ 63 ] [   ]   [ 99 ]
```
### **Step 2.3: Fix Underflow with a Merge**

The empty node's siblings, `[ 63 ]` and `[ 99 ]`, are 2-nodes, so they can't spare a key for rotation. We must **merge**. We'll merge the empty node with its left sibling `[ 63 ]`.

1. Pull down the separating key from the parent `[ 81 | 90 ]`, which is **81**.
2. Combine `[ 63 ]`, the key `81`, and the empty node `[ ]` into a new node `[ 63 | 81 ]`.
3. The parent node becomes `[ 90 ]`.
- **Final tree after deleting 72**: ✅
```
              [ 54 ]
             /      \
            /        \
      [ 36 ]           [ 90 ]
      /    \           /     \
     /      \         /       \
[ 18 | 27 ] [ 45] [ 63 | 81 ] [ 99 ]
```
---

### **3. Deleting 99**

### **Step 3.1: Delete from Leaf (Causing Underflow)**

We locate **99** in a leaf node `[ 99 ]`. Deleting it immediately causes an **underflow**.

- Tree *showing the underflow*:
```
              [ 54 ]
             /      \
            /        \
      [ 36 ]           [ 90 ]
      /    \           /     \
     /      \         /       \
[ 18 | 27 ] [ 45 ][ 63 | 81 ] [    ]
```
### **Step 3.2: Fix Underflow with a Rotation**

The empty node's sibling `[ 63 | 81 ]` is a 3-node, which is "rich" enough to spare a key. We perform a **rotation**.

1. The parent's key `[ 90 ]` moves down into the empty node.
2. The largest key from the rich sibling, **81**, moves up to replace the parent's key.
3. The rich sibling is now just `[ 63 ]`.
- **Final tree after deleting 99**: ✅
```
              [ 54 ]
             /      \
            /        \
      [ 36 ]           [ 81 ]
      /    \           /    \
     /      \         /      \
[ 18 | 27 ] [ 45 ]  [ 63 ]   [ 90 ]
```
---

### **4. Deleting 81**

This one is a bit more complex and involves a propagated underflow.

### **Step 4.1: Swap with In-order Successor**

**81** is in an internal node. We **swap** it with its successor, **90**.

- Tree *after swapping 81 and 90*:
```
              [ 54 ]
             /      \
            /        \
      [ 36 ]           [ 90 ]
      /    \           /    \
     /      \         /      \
[ 18 | 27 ] [ 45 ]  [ 63 ]  [ 81 ]
```
### **Step 4.2: Delete from Leaf (Causing Underflow)**

We delete **81** from the leaf node `[ 81 ]`, which causes an **underflow**.

- Tree *showing the leaf underflow*:
```
              [ 54 ]
             /      \
            /        \
      [ 36 ]           [ 90 ]
      /    \           /    \
     /      \         /      \
[ 18 | 27 ] [ 45 ]   [ 63 ]   [    ]
```

### **Step 4.3: First Merge (Propagating Underflow)**

The sibling `[ 63 ]` is a 2-node, so we must **merge**.

1. Pull down the parent's key `[ 90 ]`.
2. Merge `[ 63 ]`, the key `90`, and the empty node `[ ]` to get `[ 63 | 90 ]`.
3. This leaves the parent node empty, **propagating the underflow up** the tree. 😵
- Tree *showing the propagated underflow*:
```
              [ 54 ]
             /      \
            /        \
      [ 36 ]          [    ]
      /    \             |
     /      \            |
[ 18 | 27 ] [ 45 ]  [ 63 | 90 ]
```
### **Step 4.4: Second Merge (at the Root)**

Now we deal with the empty internal node. Its sibling is `[ 36 ]`, which is a 2-node. We must **merge** again.

1. Pull down the separating key from the root, **54**.
2. Merge `[ 36 ]`, the key `54`, and the empty node `[ ]` to create a new node `[ 36 | 54 ]`.
3. This merge makes the **root node empty**.
- Tree *showing the empty root*:
```
             [    ]
                |
                |
          [ 36 | 54 ]
         /     |     \
        /      |      \
[ 18 | 27 ]  [ 45 ]  [ 63 | 90 ]
```
### **Step 4.5: Fix the Root**

An empty root is removed, and its single child becomes the new root. The height of the tree decreases by one.

- **Final tree after deleting 81**: ✅
```
          [ 36 | 54 ]
         /     |     \
        /      |      \
[ 18 | 27 ]  [ 45 ]  [ 63 | 90 ]
```
A comparision table for Time complexity

| Data Structure | Search | Insertion | Deletion |
| --- | --- | --- | --- |
| **Binary Tree** (General) | Avg: O(n)  Worst: O(n) | Avg: O(n)  Worst: O(n) | Avg: O(n)  Worst: O(n) |
| **Binary Search Tree** (BST) | Avg: O(logn)  Worst: O(n) | Avg: O(logn)  Worst: O(n) | Avg: O(logn)  Worst: O(n) |
| **AVL Tree** | Avg: O(logn)  Worst: O(logn) | Avg: O(logn)  Worst: O(logn) | Avg: O(logn)  Worst: O(logn) |
| **Red-Black Tree** | Avg: O(logn) Worst: O(logn) | Avg: O(logn)  Worst: O(logn) | Avg: O(logn)  Worst: O(logn) |
| **2-3 Tree** | Avg: O(logn)  Worst: O(logn) | Avg: O(logn)  Worst: O(logn) | Avg: O(logn)  Worst: O(logn) |


---
---
---


## B-Trees (not binary trees)

B-Tree is **not a binary tree**. They are both types of search trees, but they have a fundamental structural difference.

A **binary tree** is defined by the rule that each node can have **at most two children** (a left child and a right child).

A **B-Tree**, on the other hand, is a generalization where a node can have **`many children`** (often hundreds or even thousands).

![image.png](https://i.ibb.co/jv2GMgBf/image.png)

---

### Key Differences

Here's a simple breakdown of the distinctions:

- **Number of Children:**
    - **Binary Tree:** Maximum of 2 children per node.
    - **B-Tree:** Can have a large number, *m*, of children per node.
- **Number of Keys:**
    - **Binary Tree:** Each node stores a single key.
    - **B-Tree:** Each node can store many keys (up to *m*1).
- **Primary Use Case:**
    - **Binary Tree:** Generally used for data structures that reside in main memory (RAM).
    - **B-Tree:** Optimized for systems that use secondary storage like hard disks or SSDs (e.g., databases and filesystems).
- **Structure & Performance:**
    - Because binary trees are "tall and skinny," traversing them can require many node lookups. This is fine in fast RAM.
    - B-Trees are "short and wide." By storing many keys in a single node (which corresponds to a disk block), they drastically reduce the number of slow disk reads needed to find data. This is their main advantage. 🌳

In short, while they share the concept of ordering keys to enable efficient searching, a B-Tree's ability to have many children per node makes it a fundamentally different and more complex structure designed specifically for storage systems.

### Applications of B-Trees

- It is used in large databases to access data stored on the disk
- Searching for data in a data set can be achieved in significantly less time using the B-Tree
- With the indexing feature, multilevel indexing can be achieved.
- Most of the servers also use the B-tree approach.
- B-Trees are used in CAD systems to organize and search geometric data.
- B-Trees are also used in other areas such as natural language processing, computer networks, and cryptography.

### Advantages of B-Trees

- B-Trees have a guaranteed time complexity of O(log n) for basic operations like insertion, deletion, and searching, which makes them suitable for large data sets and real-time applications.
- B-Trees are self-balancing.
- High-concurrency and high-throughput.
- Efficient storage utilization.

### Disadvantages of B-Trees

- B-Trees are based on disk-based data structures and can have a high disk usage.
- Not the best for all cases.
- For small datasets, the search time in a B-Tree might be slower compared to a binary search tree, as each node may contain multiple keys.

### **Insert Operation in B-Tree**

![image.png](https://i.ibb.co/1Y4KtVqK/image.png)

![image.png](https://i.ibb.co/5X1MwCjg/image.png)

![image.png](https://i.ibb.co/Mx56GZzt/image.png)

## Insertion in a B-Tree (t = 2)

We are constructing a B-Tree of minimum degree **t = 2**. This means:

- Each node can contain **at most 2t - 1 = 3 keys**.
- Each non-root node must contain **at least t - 1 = 1 key**.
- Root is allowed to have fewer keys initially.

We will insert keys **1 through 10** step by step.

---

### Insert 1

- Tree is empty initially.
- Create a root node and place **1** inside it.

```
[1]

```

---

### Insert 2

- Root has space (max 3 keys).
- Insert **2** into the root.

```
[1, 2]

```

---

### Insert 3

- Root still has space.
- Insert **3**.

```
[1, 2, 3]

```

---

### Insert 4

- Root is full (3 keys).
- Before inserting **4**, split root.
- Middle key **2** moves up, becoming new root.
- Left child: [1], Right child: [3].
- Insert **4** into the correct child → goes to the right child.

```
    [2]
   /   \
[1]   [3,4]

```

---

### Insert 5

- Root [2] is not full.
- Correct child for **5** is [3,4].
- Insert into right child.

```
    [2]
   /   \
[1]   [3,4,5]

```

---

### Insert 6

- Right child [3,4,5] is full.
- Split it: middle key **4** moves up to root.
- Root becomes [2,4].
- Left child: [1], middle child: [3], right child: [5].
- Insert **6** into the correct child → goes to [5].

```
       [2,4]
      /  |   \
   [1] [3] [5,6]

```

---

### Insert 7

- Root [2,4] has space.
- Correct child for **7** is [5,6].
- Insert → [5,6,7].

```
       [2,4]
      /  |     \
   [1] [3] [5,6,7]

```

---

### Insert 8

- Right child [5,6,7] is full.
- Split it: middle key **6** moves up to root.
- Root becomes [2,4,6].
- Children: [1], [3], [5], [7].
- Insert **8** → goes into [7].

```
         [2,4,6]
       /   |   |   \
    [1]  [3] [5] [7,8]

```

---

### Insert 9

- Root [2,4,6] is full (3 keys).
- Split root: middle key **4** becomes new root.
- Left child: [2], right child: [6].
- Distribute subtrees accordingly.
- New root: [4]
    - Left child [2] → children: [1], [3]
    - Right child [6] → children: [5], [7,8]
- Insert **9** → goes to [7,8].

```
          [4]
        /     \
     [2]       [6]
    /   \     /   \
 [1]   [3] [5]  [7,8,9]

```

---

### Insert 10

- Correct child for **10** is [7,8,9].
- [7,8,9] is full.
- Split it: middle key **8** moves up.
- Right child [6] becomes [6,8].
- Children: [5], [7], [9,10].

Final structure:

```
          [4]
        /     \
     [2]       [6,8]
    /   \     /  |   \
 [1]   [3] [5] [7] [9,10]

```

---

### Final B-Tree after inserting 1–10 (t=2)

```
          [4]
        /     \
     [2]       [6,8]
    /   \     /  |   \
 [1]   [3] [5] [7] [9,10]

```

- Root has 1 key ([4]).
- Height of the tree = 2.
- All leaf nodes are at the same depth, so it satisfies B-Tree properties.

## B-Tree Deletion Walkthrough (F, M, G, D, B)

This document explains, step-by-step, the deletions **F → M → G → D → B** in a B-tree of **minimum degree `t = 3`**, including **why** each change was required and which rule/case was applied.

---

### Quick Reference — What `t` means

- `t` (minimum degree) controls node capacity:
    - Keys per non-root node: **`t−1 .. 2t−1`** → here: **`2 .. 5`**.
    - Children per internal node: **`t .. 2t`** → here: **`3 .. 6`**.
- **Root** is special: it may have **fewer** than `t−1` keys (down to 1), and if it becomes empty during deletion, the tree height **shrinks by one**.
- **Preemptive fix rule for deletion:** before descending to a child to delete, ensure that child has **≥ t keys**. If it has only **`t−1`** keys, **fix first** by borrowing or merging. This guarantees no underflow will occur after the recursive deletion.

**Case names used below (CLRS style):**

- **Case 1:** delete from a **leaf** (simple remove).
- **Case 2a / 2b:** delete from an **internal** node by replacing with predecessor/successor from a child that has ≥ `t` keys.
- **Case 2c:** if both adjacent children have only `t−1` keys, **merge** and continue deletion.
- **Case 3a:** **borrow (rotate)** from sibling when the target child has `t−1` keys and a sibling has ≥ `t` keys.
- **Case 3b:** if both siblings have `t−1` keys, **merge with a sibling** (may shrink height if at root).

---

### Initial Tree (before any deletions)

```
                              [ P ]
                    /                      \
              [ C   G   M ]                [ T   X ]
            /     |      |   \            /    |    \
        [A B]  [D E F] [J K L] [N O]   [Q R S] [U V] [Y Z]

```

- This is valid for `t = 3`:
    - Every non-root node has **2..5** keys.
    - Internal nodes have **3..4** children (within **3..6**).

---

### Step 1 — Delete **F** (Case 1: simple leaf delete)

**Where?** In leaf `[D E F]`.

**Action:** Remove `F` directly.

```
Before: [D E F]   →   After: [D E]

```

**Why allowed?** Leaf had 3 keys ≥ `t−1 = 2`; removing one leaves **2 keys**, still legal.

**Tree (only the changed leaf shown):**

```
... [D E] ...

```

---

### Step 2 — Delete **M** (Case 2a: delete from internal, replace with predecessor)

**Where?** Internal node key `M` in `[C  G  M]`.

**Action:** Replace `M` with its **predecessor** from the left child subtree of `M`.

- Predecessor is the **max** key in the left child of `M`, which is `L` from `[J K L]`.
- Because `[J K L]` has **3 ≥ t** keys, we can safely take `L`.

**Operations:**

1. In parent `[C G M]`, replace `M` with `L` → becomes `[C G L]`.
2. In child `[J K L]`, remove `L` → becomes `[J K]`.

**Resulting fragment:**

```
Parent: [C  G  L]
Children around it: ... [D E]   [J K]   [N O]

```

**Why allowed?** Case 2a requires the chosen child to have ≥ `t` keys; here `[J K L]` had 3, so replacement + removal doesn’t underflow it.

---

### Step 3 — Delete **G** (Case 2c: both adjacent children minimal → merge, then delete)

**Where?** Internal node key `G` in `[C  G  L]`.

**Observation:** The two children adjacent to `G` are `[D E]` and `[J K]`, each with **2 = t−1** keys (minimum). Since neither child has ≥ `t` keys, we **cannot borrow**.

**Action (Case 2c):**

- **Merge** left child + key `G` + right child → `[D E G J K]`.
- Remove `G` **inside that merged node** (now it’s a leaf), yielding `[D E J K]`.
- Parent loses `G` and its two children become one merged child.

**Before / After (around the left subtree):**

```
Before parent: [C  G  L]          After parent: [C  L]
Children:  [A B] [D E] [J K] [N O]    →   [A B] [D E J K] [N O]

```

**Full tree snapshot after Step 3:**

```
                              [ P ]
                    /                      \
                 [ C   L ]                [ T   X ]
               /    |    \               /    |    \
            [A B] [D E J K] [N O]    [Q R S] [U V] [Y Z]

```

**Why allowed?** Case 2c explicitly merges when both adjacent children are at minimum (`t−1`). This keeps all nodes within 2..5 keys, and the tree remains valid.

---

### Step 4 — Delete **D** (Requires Case 3b at the root, then Case 1 in leaf)

We want to delete `D` from `[D E J K]`.

**Preemptive fix check at the root:** We are about to descend from the root `[P]` to its left child `[C L]`. That child has **2 = t−1** keys, and its right sibling `[T X]` also has **2 = t−1** keys. With both siblings minimal, we **cannot borrow**; per **Case 3b** we must **merge across the root**.

**Case 3b action (root merge):**

- Merge left child + root key `P` + right child → new root `[C L P T X]`.
- The tree height **shrinks by one**.

**After the root merge (before deleting D):**

```
                     [ C  L  P  T  X ]
                 /      |      |     |     \
              [A B]  [D E J K] [N O] [Q R S] [U V] [Y Z]

```

**Now delete `D` (Case 1 in leaf):**

- In leaf `[D E J K]`, remove `D` → `[E J K]`.

**Snapshot after Step 4:**

```
                     [ C  L  P  T  X ]
                 /      |      |     |     \
              [A B]  [E J K] [N O] [Q R S] [U V] [Y Z]

```

**Why allowed?** Preemptive fix (Case 3b) ensured we would not underflow on the path to the target. The actual deletion then happened in a leaf with ≥ `t−1` keys.

---

### Step 5 — Delete **B** (Case 3a: borrow/rotate from right sibling, then delete)

Target is in the **leftmost leaf** `[A B]`, which currently has **2 = t−1** keys (minimum). Direct deletion would underflow, so we must **fix before deletion**.

**Check siblings:** Right sibling `[E J K]` has **3 ≥ t** keys → we can **borrow**.

**Case 3a action (borrow/rotation):**

1. Move parent separator (`C`) **down** to the underfull child.
2. Move the sibling’s smallest key (`E`) **up** to the parent (replacing `C`).

**Local transformation:**

```
Parent: [ C  L  P  T  X ]  →  [ E  L  P  T  X ]
Left leaf:  [A B]        →  [A B C]
Right leaf: [E J K]      →  [J K]

```

**Now delete `B` from `[A B C]` (leaf, Case 1):**

```
[A B C] → [A C]

```

**Final snapshot after Step 5:**

```
                     [ E  L  P  T  X ]
                 /      |      |     |     \
              [A C]   [J K]  [N O] [Q R S] [U V] [Y Z]

```

**Why allowed?** Borrowing (Case 3a) is permitted because the sibling had ≥ `t` keys. After rotation, the target leaf had 3 keys; deleting `B` leaves 2 keys, which is valid.

---

### Invariant Checks (after each step)

- **Node key counts:** All non-root nodes always remained within **2..5** keys.
- **Root:** Temporarily had 1 key earlier and later expanded/merged as allowed; when merged in Step 4, it legally contained **5** keys and the height reduced by one.
- **Leaf depth:** All leaves remained at the **same depth** throughout.
- **Ordering:** Inorder key order is preserved after each rotation/merge.

---

### Takeaways

1. With `t = 3`, the legal key range per non-root node is **2..5**; children per internal node is **3..6**.
2. **Preemptive fixing** (borrow/merge) happens **before** descending into a child that has only `t−1` keys.
3. **Deleting from an internal node** uses predecessor/successor replacements **only** if the chosen child has ≥ `t` keys; otherwise **merge** and continue.
4. When both sides are minimal at the **root**, merging can **shrink the tree height**.

---

### Glossary of cases used

- **Case 1:** Delete directly from a leaf.
- **Case 2a:** Delete internal key; replace with predecessor from left child (which must have ≥ `t` keys), then delete predecessor from that child.
- **Case 2c:** If both adjacent children have `t−1` keys, **merge** them with the separator key and continue deletion in the merged node.
- **Case 3a:** **Borrow** from a sibling that has ≥ `t` keys; rotate via the parent.
- **Case 3b:** If target child and its siblings all have `t−1` keys, **merge** with a sibling (at root this can reduce height).

---