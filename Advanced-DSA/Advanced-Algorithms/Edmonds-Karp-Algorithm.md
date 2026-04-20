# The Edmonds-Karp Algorithm

## 1. Introduction & The Flaw in Ford-Fulkerson
The Ford-Fulkerson method dictates that we must find an augmenting path, but it does not specify *how* to find it. If we use a naive search method (like Depth-First Search) on a network with a "trap" bottleneck, the algorithm might take a mathematically agonizing 1-unit step at a time, resulting in massive inefficiency or an infinite loop.

**The Edmonds-Karp Fix:** Jack Edmonds and Richard Karp introduced one strict, non-negotiable rule: **Always use Breadth-First Search (BFS)** to find the augmenting path with the *fewest number of edges* (hops), completely ignoring the edge capacities during the search phase.

## 2. Algorithm Steps (Exam Format)

* **Step 1: Initialization**
  Set the initial flow of all edges to 0. Create the initial residual graph G_f.
  
* **Step 2: The BFS Loop**
  Start at the Source (S). Explore the residual graph level-by-level using a Queue and a `Visited` set. 
  * Constraint: You can only traverse an edge if its residual capacity is > 0.
  * Keep track of the "parent" of each node to trace the shortest path back from the Sink (T).
  
* **Step 3: Augment & Update**
  If BFS successfully reaches the Sink (T):
  1. Trace the parent pointers back to S to get the shortest path.
  2. Find the bottleneck (minimum residual capacity) along this exact path.
  3. Add the bottleneck to the Total Flow.
  4. Update the Residual Graph: subtract bottleneck from forward edges, add to backward edges.
  
* **Step 4: Termination**
  Clear the Queue and Visited set. Repeat Steps 2 and 3. When a BFS execution empties the Queue *before* ever reaching the Sink, the algorithm terminates. The Total Flow is the Maximum Flow.

---

## 3. Dry Run: Dodging the "Trap" Network

### The Network Setup
We have a 4-node network `(S, A, B, T)` with a hidden trap.
```
* S -> A: 10
* S -> B: 10
* A -> B: 1 (The Trap Pipe)
* A -> T: 10
* B -> T: 10
```

### Iteration 1: The First BFS
![](https://i.ibb.co/nqPNV1W1/image.png)
![](https://i.ibb.co/N2sMsNFP/image.png)


1. Queue: [S] | Visited: {S}
2. Pop S. Neighbors with capacity: A and B.
   * Queue: [A, B] | Visited: {S, A, B}
3. Pop A. Neighbors with capacity: B and T. 
   * Crucial BFS Check: B is already visited! Ignore it. Add T.
   * Queue: [B, T] | Visited: {S, A, B, T}
4. Pop B. Neighbor T is already visited. Ignore it. 
   * Queue: [T]
5. Pop T. Target reached!
   * Trace back path: S -> A -> T (2 hops! It perfectly avoided the 3-hop trap).
   * Bottleneck: 10.
   * Update Residuals: Forward S->A and A->T drop to 0. Backward edges get +10.
   * Current Max Flow: 10

### Iteration 2: The Second BFS
![](https://i.ibb.co/v455DZJR/image.png)
![](https://i.ibb.co/pvW0vkvW/image.png)

1. Queue: [S] | Visited: {S}
2. Pop S. S->A is 0. S->B has 10 left.
   * Queue: [B] | Visited: {S, B}
3. Pop B. B->T has 10 left.
   * Queue: [T] | Visited: {S, B, T}
4. Pop T. Target reached!
   * Trace back path: S -> B -> T
   * Bottleneck: 10.
   * Update Residuals: Forward S->B and B->T drop to 0.
   * Current Max Flow: 10 + 10 = 20

### Iteration 3: The Halting Condition
![](https://i.ibb.co/gZ0TBn7v/image.png)
1. Queue: [S] | Visited: {S}
2. Pop S. S->A is 0. S->B is 0. 
   * No valid neighbors. 
   * Queue: [Empty]
3. Queue is empty, Sink (T) was never reached. Algorithm Halts.

Absolute Maximum Flow = 20.

---

## 4. Time Complexity Analysis

The time complexity of the Edmonds-Karp algorithm is strictly bounded to **O(V * E^2)**. 

For a master's level exam, you must prove this bound by breaking it into two parts:

### Part 1: Time Per Search
Every iteration runs a standard Breadth-First Search (BFS) across the edges. In the worst-case scenario, one BFS takes **O(E)** time.

### Part 2: Maximum Number of Iterations (The Proof)
1. The Critical Edge: In every augmenting path, at least one edge is filled to maximum capacity. This edge becomes the "Critical Edge" and disappears from the forward residual graph.
2. The Reappearance Rule: For that edge to ever be used again in the forward direction, the algorithm must push flow *backward* across it to undo the jam.
3. The Distance Guarantee: Because we strictly use BFS, the hop-distance from the Source to any node *never decreases* over the course of the algorithm. 
4. The Limit: For an edge to disappear, reappear, and become a Critical Edge a second time, the network must have reshuffled such that the path is now strictly longer (specifically, at least 2 hops longer). 
5. Since the maximum possible path length is the number of vertices (V), a single edge can only be the Critical Edge O(V) times.
6. Since there are E total edges, the absolute maximum number of times *any* edge can be the bottleneck before the network is completely jammed is **O(V * E)**.

### Final Calculation
Total Time = $(Maximum Iterations) * (Time Per Iteration)$

Total Time = $O(V * E) * O(E)$

Total Time = $O(V * E^2)$
