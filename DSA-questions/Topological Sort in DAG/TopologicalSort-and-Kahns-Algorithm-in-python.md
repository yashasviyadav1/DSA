# 1.Topological Sort [using DFS]
A Topological Sort is a linear ordering of vertices such that:
For every directed edge `u → v`,
u appears before v in the ordering.

Only possible for a DAG (Directed Acyclic Graph)

If there is a cycle → No valid topological ordering

DFS	
-------
`Time	O(V + E)
Space	O(V)`


![topological-sort-dfs-img](https://i.ibb.co/6JTV7zg2/image.png)

```py
### Topological Sort
### only works in DAG (Directed Acyclic graph)
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


""" 	  2
		 /  \
		0    3
		 \  /
		  1
		 /
		4
directed edge between 0 -> 1, 0 -> 2, 1 -> 4, 2 -> 3, 3 -> 1

Top sort: [0, 2, 3, 1, 4]

"""
```
---

# Kahn's Algorithm - for Topological Sort or cycle detection

Kahn's Algo (BFS (Kahn’s Algorithm) ⭐ MOST IMPORTANT)
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

`Time: O(V + E)
Space:	O(V)`
```py
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

