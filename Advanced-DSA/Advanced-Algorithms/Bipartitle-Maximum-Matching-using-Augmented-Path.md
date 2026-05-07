# Maximum Matching in Bipartite Graphs

This document explains the characterization and algorithmic approach to finding the maximum matching in a bipartite graph, followed by a step-by-step dry run.

## Part 1: The Essential Characterisation (Theory)

### Definitions
* **Bipartite Graph ($G = (U \cup V, E)$):** A graph where vertices are divided into two distinct sets ($U$ and $V$). Edges only connect a vertex in $U$ to a vertex in $V$. (Example: Applicants in set $U$, Jobs in set $V$).
* **Free Vertex:** A vertex that is not currently part of any matching.
* **Alternating Path:** A path whose edges strictly alternate between being "unmatched" and "matched."
* **Augmenting Path:** An alternating path that starts at a free vertex in $U$ and ends at a free vertex in $V$.

### The Golden Theorem (Berge's Lemma)
> A matching $M$ in a graph $G$ is a maximum matching if and only if there are no $M$-augmenting paths in $G$.

**Explanation:** Because an augmenting path starts and ends on free vertices, it always contains exactly one more unmatched edge than matched edge. By "flipping" the status of all edges in this path (XOR operation), the total matching size increases by 1.

---

## Part 2: The Algorithm (Augmenting Path / DFS)

1.  **Initialise:** Start with an empty matching ($M = \emptyset$). All vertices are "free."
2.  **Iterate:** Loop through every vertex $u$ in the left set ($U$).
3.  **Search (DFS/BFS):** If $u$ is a free vertex, start a search to find an augmenting path.
    * Look at all neighbors $v$ of $u$.
    * If $v$ is free, you found a path! Match them.
    * If $v$ is already matched to someone else (let's call them $u'$), follow the matched edge back to $u'$, and recursively try to find a different free neighbour for $u'$ to match with.
4.  **Augment:** If the search successfully finds a path ending in a free vertex in $V$, "flip" all edges along that path (matched becomes unmatched, unmatched becomes matched).
5.  **Terminate:** When every vertex in $U$ has been checked and no more augmenting paths can be found, the algorithm stops. The current matching $M$ is the **Maximum Matching**.

---

## Part 3: Step-by-Step Dry Run
Graph:
```
0--------B----------1
|
A----------2
```
Find Maximum Matching for the bipartite Graph

### Graph Setup
* **Set U:** $\{A, B\}$
* **Set V:** $\{0, 1, 2\}$
* **Edges:** $(A, 0), (A, 2), (B, 0), (B, 1)$

### Initial State
* **Matching ($M$):** Empty
* **Free Vertices in U:** $\{A, B\}$
* **Free Vertices in V:** $\{0, 1, 2\}$

### Step 1: Processing Vertex A
1.  Pick free vertex **A**.
2.  Check neighbor **0**.
3.  Is **0** free? **Yes**.
4.  **Action:** Match them immediately.
5.  **Current Matching:** $M = \{(A, 0)\}$

### Step 2: Processing Vertex B (The Bumping Logic)
1.  Pick free vertex **B**.
2.  Check neighbor **0**.
3.  Is **0** free? **No**. (Matched to $A$).
4.  **Search:** Can we find a new match for $A$?
5.  Check $A$'s other neighbors. $A$ also connects to **2**.
6.  Is **2** free? **Yes**.
7.  **Path Found:** We found an augmenting path: $B 	o 0 	o A 	o 2$.
    * $B-0$: Unmatched
    * $0-A$: Matched
    * $A-2$: Unmatched

### Step 3: Augmenting (Flipping Edges)
We flip the status of the edges in the path $B 	o 0 	o A 	o 2$:
* $(B, 0)$: Becomes **Matched**.
* $(0, A)$: Becomes **Unmatched**.
* $(A, 2)$: Becomes **Matched**.

**Current Matching:** $M = \{(B, 0), (A, 2)\}$

### Step 4: Termination
1.  Check vertex list in $U$: Both $A$ and $B$ are matched.
2.  No more free vertices in $U$ to initiate searches.
3.  **Final Result:** The Maximum Matching is $\{(B, 0), (A, 2)\}$ with a **size of 2**.

---
*Note: The algorithm ensures that even if an initial sub-optimal choice is made, the "bumping" mechanism (recursively finding new matches for already matched vertices) eventually reaches the maximum cardinality.*