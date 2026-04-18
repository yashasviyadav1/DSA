# Graph Theory (Main Algorithms)
Topics:
- builld adjacency List of directed graph
- Topological Sort DFS
- Topological Sort BFS (Kahn's Algo)
- DFS
- BFS
- Min Spanning Tree (MST)
- Krushkals Algo [Theory]  (for MST)
- Prim's Algo  [Theory] (for MST)
- Cycle Detection in Directed Graphs (DFS)
- Cycle Detection in Unidrected Graphs (DFS)
- Fleury’s Algorithm to find Eulerian Cycle and Path
- Shortest Distance from Source To All Nodes of Undirected Graph  [BFS]

-----

## Topological Sort [using DFS]
A Topological Sort is a linear ordering of vertices such that:
For every directed edge `u → v`,
u appears before v in the ordering.

Only possible for a DAG (Directed Acyclic Graph)

If there is a cycle → No valid topological ordering

![Topological Sort [using DFS]](https://i.ibb.co/fGyBzf4b/image.png)

DFS	
-------
`Time	O(V + E)
Space	O(V)`


```py

def dfs(adjList, stack, visited, node):
	visited[node] = True # visit node
	for neigh in adjList[node]: #then visit all its child
		if not visited[neigh]:
			dfs(adjList, stack, visited, neigh)
	
	# after we visited all connected neighbours of curr node, append it to stack
	stack.append(node)


def topologicalSort(adjList):
	V = len(adjList)
	stack = []
	visited = [False]*V # [False, False, False, False]

	for node in range(0, V): # loop on each neigh (this takes care of case where graph is diconnected so all nodes are always checked with this)
		if not visited[node]:
			dfs(adjList, stack, visited, node)

	topSort = []
	while len(stack):
		top = stack.pop() # pop last insert in topSort array
		topSort.append(top)

	return topSort

def buildAdjList(verticies, edges):
	# first initialize adjacency list size, == no. of verticies
	adjList = [[] for i in range(0, len(verticies))] # looks like this for graph with 4 verticies [[], [], [], []]

	# add entries
	for edge in edges:
		node1 = edge[0]
		node2 = edge[1]
		adjList[node1].append(node2) # if there is edge b/w 1 -> 4 and 1 -> 5 adj list will look like [[],[4, 5],[],[]], index 1 has element 4

	return adjList

verticies = (0, 1, 2, 3, 4) # 5 verticies, in graph 
edges = [(0, 1), (0, 2), (1, 4), (2, 3), (3, 1)] # (0,1) means there is edge between 0 -> 1 or A->B

### create adjecency list
# Adj list is a list of list, eg. index = 0 has list [1, 2] means from node 0 we can go to node 1 and node 2
adjList = buildAdjList(verticies, edges)

topSort = topologicalSort(adjList)
print(topSort)
```

		  2
		 /  \
		0    3
		 \  /
		  1
		 /
		4
directed edge between 0 -> 1, 0 -> 2, 1 -> 4, 2 -> 3, 3 -> 1

Top sort: [0, 2, 3, 1, 4]





-----

Finding Topological Sort, or check for cycle.

## Kahn's Algo (BFS (Kahn’s Algorithm) ⭐ MOST IMPORTANT)
- can be used to find Topological Sort
- can be used to check cycle in graph exists or not, (if topSort.length != total Verticies in graph) means there is a cycle, Because some nodes never reach indegree 0

Idea:
- Compute indegree of each node from the adjacency matrix
- Push nodes with indegree = 0 into a queue
- run loop while q is not empty, 
	- Remove front node, add this node to 'topologicalSort' array, and remove it from graph (not actually, it means virtually 
		remove the node , means simply decrement 1 from its neighbours indegree (that would mean removing the node virtually)
	- if any of neigh's indegree has become 0, push it into queue
- at the end print 'topologicalSort' array


```
from collections import deque

def topo_bfs(V, adj):
    indegree = [0] * V
    
    # calculate indegree
    for u in range(V):
        for v in adj[u]:
            indegree[v] += 1

    q = deque()
    
    # push nodes with indegree 0
    for i in range(V):
        if indegree[i] == 0:
            q.append(i)

    topo = []

    while q:
        node = q.popleft()
        topo.append(node)

        for nei in adj[node]:
            indegree[nei] -= 1
            if indegree[nei] == 0:
                q.append(nei)

    return topo
```

------

## Depth-First Search (in directed graph)

```py
def dfs(adjList, visited, node):
	visited[node] = True
	print(node, end=" ")
	for neigh in adjList[node]:
		if not visited[neigh]:
			dfs(adjList, visited, neigh)

def buildAdjList(verticies, edges):
	# first initialize adjacency list size, == no. of verticies
	adjList = [[] for i in range(0, len(verticies))] # looks like this for graph with 4 verticies [[], [], [], []]

	# add entries
	for edge in edges:
		node1 = edge[0]
		node2 = edge[1]
		adjList[node1].append(node2) # if there is edge b/w 1 -> 4 and 1 -> 5 adj list will look like [[],[4, 5],[],[]], index 1 has element 4

	return adjList

verticies = (0, 1, 2, 3, 4) # 5 verticies, in graph 
edges = [(0, 1), (0, 2), (1, 4), (2, 3), (3, 1)] # (0,1) means there is edge between 0 -> 1 or A->B

### create adjecency list
# Adj list is a list of list, eg. index = 0 has list [1, 2] means from node 0 we can go to node 1 and node 2
adjList = buildAdjList(verticies, edges)

visited = [False]*len(verticies)
print("DFS: - ")
for node in range(0, len(verticies)): # so that it doesn't miss any disconnected graph node
	if not visited[node]:
		dfs(adjList, visited, node)
		print()
```

   			DAG
		  2
		 /  \
		0    3
		 \  /
		  1
		 /
		4
directed edge between 0 -> 1, 0 -> 2, 1 -> 4, 2 -> 3, 3 -> 1

DFS: 0 1 4 2 3 



------



## Breadth-First Search in Graph
```python

def bfs(adjList, visited, node):
	queue = [] # using list as queue
	queue.append(node)
	visited[node] = True
	
	while len(queue) > 0:
		front = queue.pop(0) # pop from front
		print(front, end=" ")
		## for all neighbours of front node, add them to queue if not visited
		for neigh in adjList[front]:
			if not visited[neigh]:
				queue.append(neigh)
				visited[neigh] = True # we are visiting true here and not after poping front because if lets say 1 -> 2 and 1 -> 3 so neigh: 2, 3 and both neigh point to lets say 4, 2->4, 3->4 so in this case 4 will be added in queue twice, so to avoid it, we will visit neigh just after inserting in queue

def buildAdjList(verticies, edges):
	# first initialize adjacency list size, == no. of verticies
	adjList = [[] for i in range(0, len(verticies))] # looks like this for graph with 4 verticies [[], [], [], []]

	# add entries
	for edge in edges:
		node1 = edge[0]
		node2 = edge[1]
		adjList[node1].append(node2) # if there is edge b/w 1 -> 4 and 1 -> 5 adj list will look like [[],[4, 5],[],[]], index 1 has element 4

	return adjList


verticies = (0, 1, 2, 3, 4) # 5 verticies, in graph 
edges = [(0, 1), (0, 2), (1, 4), (2, 3), (3, 1)] # (0,1) means there is edge between 0 -> 1 or A->B

adjList = buildAdjList(verticies, edges) # for DAG
visited = [False]*len(verticies)

print("BFS:- ")
for node in range(0, len(verticies)): # so that it doesn't miss any disconnected graph node
	if not visited[node]:
		bfs(adjList, visited, node)
```

	   			DAG
		  2
		 /  \
		0    3
		 \  /
		  1
		 /
		4
directed edge between 0 -> 1, 0 -> 2, 1 -> 4, 2 -> 3, 3 -> 1

BFS:-  0 1 2 4 3

------


## Minimum Spanning Tree

A Spanning Tree of a graph is:

A subgraph that includes all vertices of the graph
and is a tree (i.e., connected + no cycles)

A spanning tree connects all vertices using the minimum number of edges without cycles

we can draw a conclusion that every connected and undirected
Graph G has at least one spanning tree. A disconnected graph does not have any
spanning tree, as it cannot be spanned to all its vertices.


Original Graph:
```
1 — 2
| \ |
3 — 4
```

Possible Spanning Tree:
```
1 — 2
|
3 — 4
```

1. Multiple Spanning Trees exist
A graph can have many spanning trees

2. If graph is NOT connected
Spanning tree does not exist

in spanning tree: Edges = V - 1




Special Case: Minimum Spanning Tree (MST)
If graph has weights:
👉 Choose spanning tree with minimum total weight

Algorithms:
Kruskal’s Algorithm
Prim’s Algorithm


------



## Finding Min Spanning Tree


#### Krushkal Algo
intiution: selects edges globally based on lowest cost

-> Sort the Edges by weight
-> Take the cheapest weight edge available, but don’t create a cycle. (i.e always choose edge that connects to different components)
-> stop this when selected edges == V-1

![Diagram](https://i.ibb.co/FQcScSf/image.png)

Sorting edges: O(E log E) — the dominant step.
• Union-Find (DSU) operations: For each edge, we perform a find (which
component does this vertex belong to?) and possibly a union (merge two components). With path compression and union by rank, each operation takes nearly
O(1) amortised. For E edges: O(E · α(V )) ≈ O(E), where α is the inverse
Ackermann function.
• Overall: O(E log E)



#### Prims Algo:
intiution: picks 1 node, then builds tree from there

-> start on ranom node
-> maintain a set of 'Nodes-to-choose-from', every time we pick an edge, add than new node to this set
-> add first random node to this set
-> now for all nodes in set, choose the edge from any of thoose node which has lowest cost (Remember: Always choose edge from visited node -> unvisited node)
-> stop when selected edges == V-1 (or we can say 'Nodes-to-choose-from'.size() == V means all nodes selected in Min Spanning tree)

![Diagram](https://i.ibb.co/Nd93vQR9/image.png)


Krushkal and Prims Difference:- 
![](https://i.ibb.co/0VnCvxJS/image.png)

-------

## Cycle Detection in Directed Graphs (DFS)
Core idea:
Use visited + rec_stack

```py
def has_cycle_directed(n, adj):
    visited = [False] * n
    rec_stack = [False] * n

    def dfs(node):
        visited[node] = True
        rec_stack[node] = True

        for neigh in adj[node]:
            if not visited[neigh]:
                if dfs(neigh):
                    return True
            elif rec_stack[neigh]: #neigh is visited and is already in rec stack (in curr flow) -> cycle
                return True  # 🔥 cycle found

        rec_stack[node] = False
        return False

    # handle disconnected graph
    for i in range(n):
        if not visited[i]:
            if dfs(i):
                return True

    return False
```


-------
## Cycle Detection in Unidrected Graphs (DFS)

Use parent (no rec_stack needed)
```py
def has_cycle_undirected(n, adj):
    visited = [False] * n

    def dfs(node, parent):
        visited[node] = True

        for neigh in adj[node]:
            if not visited[neigh]:
                if dfs(neigh, node):
                    return True
            elif neigh != parent: # neigh is visited and is not the parent of node -> cycle
                return True  # 🔥 cycle found

        return False

    # handle disconnected graph
    for i in range(n):
        if not visited[i]:
            if dfs(i, -1):
                return True

    return False
```


Question: for undirected graph, why can't we use the same 'visited' and 'curr_rec_stack' approach ? Why do we use 'visited' and parent concept ???

Answer: Because undirected graph are both ways, means from edge a to b if edge exists then we can come back as well. so in that case our approahc will fail:- 

🟢 Why it FAILS in undirected graph

Take the simplest graph:

A — B
DFS traversal:
Start at A
Go to B
From B → you see A again

Now check:

visited[A] = True
rec_stack[A] = True

👉 According to directed logic → cycle detected ❌ (WRONG)






--------

## Fleury’s Algorithm to find Eulerian Cycle and Path


🔷 Step 0: First check if solution exists

Before running Fleury Check:
	Eulerian Cycle exists if:
		→ All vertices have even degree
	Eulerian Path exists if:
		→ Exactly 2 vertices have odd degree
	Otherwise → ❌ Not possible (Don't apply Fleury's Algo)


🔷 Core Idea of Fleury’s Algorithm
“Don’t remove a bridge unless you have no other choice.”
A bridge = an edge whose removal disconnects the graph.


🔷 Steps of Fleury’s Algorithm
1. Choose starting vertex
If Euler cycle → start anywhere
If Euler path → start from odd degree vertex



2. At each step:

From current node:

Look at all adjacent edges
Pick an edge:
✅ Prefer non-bridge edge
❗ Use bridge only if it's the only option

3. Remove edge after traversing
Delete edge from graph
Move to next vertex
4. Repeat until all edges are used


Example:- 
![fleury's algo](https://i.ibb.co/p6sntN18/image.png)








-----
## Shortest Distance from Source To All Nodes of Undirected Graph [BFS]
![shortest distance](https://i.ibb.co/mVFKWVxP/image.png)
```py
"""
Undirected Graph - Shortest Distance from src to all nodes

Write a Python function that
takes an adjacency list and a source vertex and returns the shortest distance from the
source to every other vertex using BFS


BFS Algo for shortest distance from src to all nodes
Time: O(V + E)
Space: O(V)
"""


def shortestDistFromSrcToAllNodes(adjList, src):
	queue = [] # list as queue
	queue.append(src) # starting from src, distance is 0 for this level

	V = len(adjList)
	visited = [False] * V # so we don't visit nodes again
	visited[src] = True

	distance = 0
	print(f"{'Node':<4} | {'Distance from Src':<2}")
	while len(queue) > 0:
		size = len(queue)

		# distance for all nodes at a level is same, that is why we increment distance after all nodes at this level are processed
		for i in range(0, size):
			front = queue.pop(0) # pop front
			print(f"{front:<4} | {distance:<2}")# remember all nodes at same level from src are of same distance from src
			
			for neigh in adjList[front]:
				if not visited[neigh]:
					visited[neigh] = True
					queue.append(neigh)

		# once all the nodes at curr level are proceessed
		distance += 1



def buildAdjListUndirectedGraph(edges, V):
	adjList = [[] for i in range(0, V)] # list of list(initially empty)
	for edge in edges:
		node1 = edge[0]
		node2 = edge[1]
		adjList[node1].append(node2)
		adjList[node2].append(node1) # coz undirected graph has bidirectional edge
	return adjList

verticies = 7
edges = [(0, 1), (1, 2), (1, 4), (1, 3), (2, 5), (4, 5), (5, 6)]
adjList = buildAdjListUndirectedGraph(edges, verticies)

src = 1
shortestDistFromSrcToAllNodes(adjList, src)



""" Undirected graph
		0 
		  \
		  [1]-------3
		  /	 \
		4	  2
	     \   /
	       5
	       |
	       6

Node | Distance from Src
1    | 0 
0    | 1 
2    | 1 
4    | 1 
3    | 1 
5    | 2 
6    | 3 
"""

```


------


## The Floyd-Warshall algorithm

The Floyd-Warshall algorithm is an All-Pairs Shortest Path (APSP) algorithm.
While algorithms like Dijkstra's or Bellman-Ford find the shortest path from a single starting node to all other nodes, Floyd-Warshall finds the shortest path between every possible pair of nodes in a graph simultaneously.

The Intuition: Finding ShortcutsImagine you want to travel from city $A$ to city $B$. You have a direct flight that costs $500.
However, you notice that if you fly from $A$ to an intermediate city $K$ (costing $100$), and then from $K$ to $B$ (costing $200$), 
your total cost is $300$. 
By routing through an intermediate node $K$, you found a "shortcut" that is cheaper than the direct route.
The algorithm simply takes this idea to the extreme: it systematically checks every single node in the graph to see if it can be used as a shortcut between any other two nodes.


**Working: The Dynamic Programming Idea**
Floyd-Warshall is a classic Dynamic Programming (DP) algorithm. It builds the solution bottom-up.
1. **State Definition:** Let dist[i][j] be the shortest distance from node i to node j.
2. **Initial State (k = 0):** We start with the direct edges given by the graph's adjacency matrix. If there is no direct edge between i and j, the distance is infinity (\infty). The distance from a node to itself is 0.
3. **The Transition (The Core Logic):** We introduce a new variable, k, which represents the **intermediate node**. For every pair of nodes (i, j), we ask:
*Is it faster to go directly from i to j, or to go from i to k, and then from k to j?*
Mathematically, this is expressed as:dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])



**Handling Negative Edges & Cycles**
- Negative Edges: Floyd-Warshall handles negative edge weights perfectly. Because it explores all possible paths systematically via the DP table, it naturally calculates the correct cost even if an edge drops the total weight.
- Negative Cycles: A negative cycle is a loop in the graph where the sum of the edges is less than zero. If you keep going around this loop, your distance approaches -infinity .
- Detection: Floyd-Warshall detects these effortlessly. Before the algorithm starts, the distance from a node to itself, $dist[i][i]$, is set to $0$. After the algorithm finishes, if any diagonal element $dist[i][i]$ is less than zero, it guarantees that node $i$ is part of a negative weight cycle.


**Time and Space Complexity**
Time Complexity: $O(V^3)$, where $V$ is the number of vertices. This is because there are three nested loops: one for the intermediate node $k$, one for the start node $i$, and one for the end node $j$.
Space Complexity: $O(V^2)$ to store the 2D distance matrix


Example:- 
![Graph-1](https://i.ibb.co/pHvgp9Q/image.png)
![Graph-2](https://i.ibb.co/tMkRhK7p/image.png)


```py
""" Floyd Warshall Algorithm

- Finds Shortest Distance from each node to every other node, using Intermediatary Node Logic
- Time: O(V^3)
- Space: O(V^2)

"""
import math


def floydWarshallShortestDist(edges, V):
	# distMatrix[i][j] stores shortest distance to reach from node i ---> node j
	## lets make a V * V matrix
	distanceMatrix = [[math.inf]*V for i in range(V)] # initially marking each pair as inf i.e unreachable 

	# 2. Distance to self is ALWAYS 0 for all nodes
	for i in range(V):
		distanceMatrix[i][i] = 0

	# initialize distanceMatrix, for an edge a ---x---> b (cost = x) mark distanceMatrix[a][b] = x
	for edgeData in edges:
		node1 = edgeData[0]
		node2 = edgeData[1]
		cost = edgeData[2]
		# found a direct edge, update its distance in matrix
		distanceMatrix[node1][node2] = cost

	# now apply algo, make every node as intermediatary node k for each node a and b
	# and check which path is shortest: a ----> b or  a ---> k ----> b whichever is shortest, choose that path (min distance)
	# and update its distance in the matrix
	for k in range(0, V):
		for i in range(0, V):

			# OPTIMIZATION: from i If we can't reach the intermediate node k , then we can't find a smaller distance for i-->j from i-->k + k --> j coz we can't reach k so no need to check j at all
			if distanceMatrix[i][k] == math.inf:
				continue

			for j in range(0, V):
				# remember we can't skip when src == dest (i==j) because we need to detech -ve cycle on node i
				## eg.  i ---[4]-->k --[-5--> i (here i==j i.e cycle) and its a -ve cycle
				if i == k or j == k:#src and intermedediatory node  or src and intermedediatory node are same, then we can't find smaller distance on this node, its time waste so skip that, means if i == k then whats point of doing min(i->j, i-->i + i-->j) ???  
					continue
				else:
					distanceMatrix[i][j] = min(
						distanceMatrix[i][j], 
						distanceMatrix[i][k] + distanceMatrix[k][j])

	return distanceMatrix


#### prints distance matrix
def printDistanceMatrix(distanceMatrix):
	# First, check if the graph has ANY negative cycles
	has_negative_cycle = False
	for i in range(V):
	    if distanceMatrix[i][i] < 0:
	        has_negative_cycle = True
	        break

	if has_negative_cycle:
	    print("WARNING: Graph contains a negative weight cycle. Shortest paths are invalid.\n")

	# finally print distance from each node to every other node
	print(f"{'Node-1':<6} | {'Node-2':<6} | {'Min Distance':<12}")
	for i in range(0, V):
		for j in range(0, V):
			if i == j:
				continue
			else:
				if distanceMatrix[j][j] < 0:# -ve cycle found on this node
					print(f"{i:<6} | {j:<6} | {distanceMatrix[i][j]:<12} -ve cycle found")
				else:
					print(f"{i:<6} | {j:<6} | {distanceMatrix[i][j]:<12}")


# node1, node2, cost
#normal directed graph 
edges = [ (0, 1, 1), 
		  (1, 2, 2), 
		  (2, 3, 6), 
		  (3, 0, 3),
		  (3, 1, 5),
		  (3, 2, 8)
		]

V = 4

# now apply floyd's warshal on this matrix
distanceMatrix = floydWarshallShortestDist(edges, V)
printDistanceMatrix(distanceMatrix)


print("-"*50)
# Test case 2
# directed graph with -ve cycle 
edges = [ 
    (0, 1, 4),  
    (1, 2, 2),  
    (2, 3, 3),  
    (3, 1, -6), 
    (0, 3, 5)
]

distanceMatrix = floydWarshallShortestDist(edges, V)
printDistanceMatrix(distanceMatrix)




"""
Output:- 

Node-1 | Node-2 | Min Distance
0      | 1      | 1           
0      | 2      | 3           
0      | 3      | 9           
1      | 0      | 11          
1      | 2      | 2           
1      | 3      | 8           
2      | 0      | 9           
2      | 1      | 10          
2      | 3      | 6           
3      | 0      | 3           
3      | 1      | 4           
3      | 2      | 6           
--------------------------------------------------


Graph-2:- 

WARNING: Graph contains a negative weight cycle. Shortest paths are invalid.


Node-1 | Node-2 | Min Distance
0      | 1      | -1           -ve cycle found
0      | 2      | 1            -ve cycle found
0      | 3      | 5            -ve cycle found
1      | 0      | inf         
1      | 2      | 1            -ve cycle found
1      | 3      | 5            -ve cycle found
2      | 0      | inf         
2      | 1      | -3           -ve cycle found
2      | 3      | 3            -ve cycle found
3      | 0      | inf         
3      | 1      | -6           -ve cycle found
3      | 2      | -4           -ve cycle found
[Finished in 50ms]


"""
```