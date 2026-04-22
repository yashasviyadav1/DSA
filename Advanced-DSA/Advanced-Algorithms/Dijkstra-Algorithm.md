## Dijkstra's Algorithm
Aim: To Find shortest distance from src node to all other nodes in the directed graph

Dijkstra’s Algorithm is just a greedy algorithm. It is the exact logic your brain uses when trying to find the fastest route on a map: always take the shortest known path available right now, and keep updating your map as you discover shortcuts.

1. The Core Concept (How it thinks)Imagine you are standing in City A (your start point). You want to know the absolute shortest distance to every other city.
2. You start by writing down a distance of 0 for City A, and $\infty$ (infinity) for every other city because you haven't explored them yet.You look at the roads directly connected to City A. You write down the length of those roads as the new "shortest known distance" to those neighboring cities.
3. The Greedy Choice: You look at all the cities you know about, pick the one that is closest to you, and "visit" it.
4. From that new city, you look at its neighbors. If traveling through this new city gives you a shorter total trip to a neighbor than what you previously wrote down, you cross out the old number and write down the new, shorter shortcut.
5. You repeat this until you have visited every city.


**Time & Space:**

Time: O(E * logV) - for each edge we are inserting a vertex into minHeap of V nodes (1 insertion takes logV)
Space: O(V+E) for storing, minHeap, distance array




```py
import heapq
import math

def dijkstra(adjList, src):
	V = len(adjList)
	# we need a shortestDistanceFromSrc 1d array where each index i stores shortest Distance from src to i node
	shortestDistanceFromSrc = [math.inf]*V
	shortestDistanceFromSrc[src] = 0

	# initialize it with src--->src distance as 0
	# and remaining all nodes distance from src is infinity because we have not explored them
	minHeap = [] # using list, then will use heapq module to use list as minHeap, by defaul minHeap sorts based on each nodes 1st element
	heapq.heappush(minHeap, (0, src)) # tuple = (distance, nodeno.)
	while len(minHeap) > 0:
		distFromSrcToNode, node = heapq.heappop(minHeap)
		
		# if distance from src to this node stored minHeap Top node > stored in distace array, then means we already have found the smaller distance to reach this node, so skip this node
		if distFromSrcToNode > shortestDistanceFromSrc[node]:
			continue
		else:
			# visit all neigh of this node
			for neighTuple in adjList[node]:
				neigh, distFromNodeToNeigh = neighTuple
				distFromSrcToNeigh = distFromSrcToNode + distFromNodeToNeigh # computing distance form src-to-neigh via src--->node---->neigh

				# found a smaller distance path from src->neigh via 'node', so update array and push this node in minHeap
				if shortestDistanceFromSrc[neigh] > distFromSrcToNeigh:
					shortestDistanceFromSrc[neigh] = distFromSrcToNeigh
					heapq.heappush(minHeap, (distFromSrcToNeigh, neigh))

	return shortestDistanceFromSrc

# for directed graph
def buildAdjList(edges, V):
	adjList = [[] for i in range(V)] # initializing adjList with V empty arrays
	for edge in edges:
		node1 = edge[0]
		node2 = edge[1]
		weight = edge[2]
		adjList[node1].append((node2, weight))
	return adjList

V = 4
edges = [(0, 1, 4), (0, 2, 1), (1, 3, 1), (2, 1, 2), (2, 3, 5)]
"""
From 0 to 0 :  0
From 0 to 1 :  3
From 0 to 2 :  1
From 0 to 3 :  4
"""


adjList = buildAdjList(edges, V)
src = 0
shortestDistanceFromSrc = dijkstra(adjList, src)

print(f"Shortest Distance From {src} to all nodes: ")
for i in range(len(shortestDistanceFromSrc)):
	print(f"From {src} to {i} : ", shortestDistanceFromSrc[i])



"""
# Other edge cases to test  - pass
edges = [(0, 1, 10), (0, 1, 2), (1, 2, 5)]
V = 3

## infinite loop test - pass
edges = [(0, 1, 4), (1, 2, 3), (2, 0, 1), (1, 1, 5), (2, 3, 2)]
V = 4
"""
```