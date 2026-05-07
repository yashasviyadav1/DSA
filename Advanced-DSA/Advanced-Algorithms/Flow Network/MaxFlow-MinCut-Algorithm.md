# Maxflow-Mincut Theorem

## 1. Statement of the Theorem
The Maxflow-Mincut Theorem is a fundamental principle in network flow theory. It states that in any flow network, the maximum amount of flow passing from the source node ($s$) to the sink node ($t$) is exactly equal to the capacity of the minimum $s-t$ cut.

Mathematically: **Max Flow = Min Cut**

<i><b>A cut in a graph is a partition of vertices into two disjoint subsets, forming a "cut-set" of edges that bridge these subsets.</i></b>

![](https://i.ibb.co/WNCqsJxt/image.png)
![](https://i.ibb.co/NgqzNF8F/image.png)


## 2. Core Definitions
To properly explain the theorem, the terminology must be established:

* **$s-t$ Cut:** A partition of the network's vertices into two disjoint sets, $S$ and $T$, such that the source $s \in S$ and the sink $t \in T$. This cut physically severs all paths from the source to the sink.
* **Capacity of a Cut, denoted as $c(S, T)$:** The sum of the capacities of all **forward edges** (edges originating in Set $S$ and terminating in Set $T$). Backward edges (from $T$ to $S$) are explicitly ignored in this calculation.
* **Minimum Cut:** The specific $s-t$ cut in the network that yields the smallest possible total capacity.

## 3. Significance of the Theorem
* **Duality:** It establishes a beautiful duality between a maximization problem (pushing as much flow as possible) and a minimization problem (finding the cheapest way to sever the network).
* **Guarantee of Optimality:** It provides a mathematical halting condition for algorithms like Ford-Fulkerson. When an algorithm finds a flow that equals the capacity of any cut, it proves unequivocally that the absolute maximum flow has been reached.
* **Identifying the Bottleneck:** The edges that make up the minimum cut identify the absolute physical bottleneck of the entire system. To increase the overall network flow, engineers must upgrade the pipes specifically located in the minimum cut.

## 4. Proof of the Theorem
The proof is established in two logical phases: proving that Flow can never exceed the Cut (Weak Duality), and proving that at maximum flow, they are exactly equal (Strong Duality).

### Part 1: Weak Duality (Max Flow $\le$ Min Cut)
![Part1-diagram](https://i.ibb.co/M5C990BQ/image.png)
* By the law of flow conservation, the net flow across any $s-t$ cut must equal the total flow of the network.
* The flow across a cut is calculated as the flow on forward edges minus the flow on backward edges.
* Because the flow on any individual forward edge can never exceed its physical capacity, the total flow across the cut can never exceed the total capacity of those forward edges.
* Therefore, the total flow is strictly bounded by the capacity of the cut: $Flow \le c(S, T)$. This means the maximum flow can never be larger than the minimum cut.

### Part 2: Strong Duality (Max Flow = Min Cut)
![Part-2-Diagram](https://i.ibb.co/jZ4FRJzh/image.png)

To prove they are exactly equal, we analyze the network at the exact moment the Ford-Fulkerson algorithm terminates.

1. **The Halting Condition:** The algorithm stops when there are no more augmenting paths from $s$ to $t$ in the residual graph.
2. **Defining the Cut:** At this point of termination, we define Set $S$ as all nodes that can still be reached from the source $s$ in the residual graph. We define Set $T$ as all remaining nodes, which includes the sink $t$.
3. **Analyzing the Boundary:** Because there is no path from $S$ to $T$ in the residual graph, two things must be physically true about the original network edges crossing this boundary:
    * Every forward edge from $S$ to $T$ must be completely saturated (Flow = Capacity). If they weren't, we could still traverse them in the residual graph.
    * Every backward edge from $T$ to $S$ must be completely empty (Flow = 0). If there was flow, we would have a residual backward edge from $S$ to $T$ to undo it.
4. **The Exact Match:** Because the forward edges are 100% full and the backward edges are 0% full, the total flow passing from $S$ to $T$ is exactly equal to the combined capacity of those forward edges.
5. **Equation:** Therefore, at this specific terminating cut, $Flow = c(S, T)$.

### Conclusion
Since we proved in Part 1 that flow can never exceed any cut, and we proved in Part 2 that the algorithm finds a flow exactly equal to a specific cut, that specific cut must be the **Minimum Cut**, and the flow must be the **Maximum Flow**.
