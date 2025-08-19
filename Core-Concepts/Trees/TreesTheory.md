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