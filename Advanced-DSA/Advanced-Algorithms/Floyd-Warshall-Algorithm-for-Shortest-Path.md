
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