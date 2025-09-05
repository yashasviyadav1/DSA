#include <vector>
#include<unordered_map>
#include<iostream>
#include<list>
using namespace std;

/*✔️⚠️[TLE] Approach - 1 (using simple dfs)

    T : O(E+V)
    S : O(E+V)

    ⚠️TLE at code studio : https://www.codingninjas.com/codestudio/problems/shortest-path-in-an-unweighted-graph_981297?leftPanelTab=0

    note : why did we got TLE, because DFS is implemented using recursion and in this the stack gets filled, and then it gets empty which is slower then BFS 

*/

// code 

// fun.2 
void createAdjList(vector<pair<int,int>> &edges, unordered_map<int,list<int>> &AdjList){

	for(int i=0; i < edges.size(); i++){
		int node1 = edges[i].first;
		int node2 = edges[i].second;
		// undirected graph
		AdjList[node1].push_back(node2);
		AdjList[node2].push_back(node1);
	}
}

// fun.3 
void dfs(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, vector<int> &ans, vector<int> &currPath, int src, int desti){
	
	// base case - if we reached the desti, then store the currPath as ans (if currPath length is smaller then that of ans)
    if(src == desti) {
		if(ans.size() == 0 ||ans.size() > currPath.size())
			ans = currPath;
        return;
	}

	// now visit the curr node, and then call dfs for all its non visited neighbours
	visited[src] = true;

	for(auto neigh:AdjList[src]){
		// when a neighbour is not visited, store it into the currPath and call dfs for it, while returning remove it from the currPath
		if(!visited[neigh]){
			currPath.push_back(neigh);
			dfs(AdjList, visited, ans, currPath, neigh, desti);
			currPath.pop_back();
		}
	}
	
	// when all the neighbours of a node are visited, unvisit the src
	visited[src] = false;
}

// main function
vector<int> shortestPath( vector<pair<int,int>> edges , int n , int m, int src , int desti){

	// we need to create an adjList, and also maintain visited nodes
	unordered_map<int,list<int>> AdjList;
	vector<bool> visited(n,false);
	createAdjList(edges, AdjList);

	// now we will maintaining a vector<int> 'ans' and a vector<int> 'currPath' 
	vector<int> ans, currPath;
	currPath.push_back(src); // include src

	// do a dfs for src node and return ans at the end 
	dfs(AdjList, visited, ans, currPath, src, desti);
	
	return ans;



}

