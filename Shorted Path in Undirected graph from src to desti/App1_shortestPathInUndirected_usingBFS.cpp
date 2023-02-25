#include<iostream>
#include<unordered_map>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;

/* ✔️⭐Approach - 2 (using BFS + parent D.S)

    explanation : here we will do simple BFS to find out for every node which parent pushed them into the queue, and then when the BFS is done, we will start from desti 
                    to reach src via there parents.

    T : O(E+V)
    S : O(E+V)

   ☑️solved at code studio : https://www.codingninjas.com/codestudio/problems/shortest-path-in-an-unweighted-graph_981297?leftPanelTab=0

*/

// code : 

/*
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
void BFS(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, vector<int> &childToParent, int src){

	// src node has no parent 
	childToParent[src] = -1;
	visited[src] = true;

	// create a queue and insert the src into it, and visit it 
	queue<int> q;
	q.push(src);

	// run loop while q is non empty 
	while(!q.empty()){

		// fetch the front node
		int front = q.front();
		q.pop();

		// explore all its neighbours, and store the unvisted neigh into queue, and mark their parents as 'src', and visit them
		for(auto neigh:AdjList[front]){
			if(!visited[neigh]){
				q.push(neigh);
				visited[neigh] = true;
				childToParent[neigh] = front;
			}
		}
	}
}

// Main function
vector<int> shortestPath( vector<pair<int,int>> edges , int n , int m, int src , int desti){
	
	// we need to maintain 'AdjList', visited vec<bool> , and a 'parent' D.S which we will use to keep track of who pushed a node into q first
	unordered_map<int,list<int>> AdjList;
	vector<bool> visited(n+1,false); // we created size of n+1 coz here nodes start from 1 (not 0)
	vector<int> childToParent(n+1); // we created size of n+1 coz here nodes start from 1 (not 0)
	createAdjList(edges, AdjList);
	
	// now call BFS for the src node 
	BFS(AdjList, visited, childToParent, src);

	// now we for all nodes we know that which node droped them into the queue first, so now we can track the path from desti node to the src node by using their parents
	vector<int> ans;
	ans.push_back(desti);

	int child = desti;
	int parent;

	while(child != src){
		parent = childToParent[child];
		ans.push_back(parent);
		child = parent;
	}


	// now ans has the shortest path (but in rev order)
	reverse(ans.begin(), ans.end());

	return ans;
}

*/