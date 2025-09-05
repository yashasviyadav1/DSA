#include<iostream>
#include<list>
#include<unordered_map>
#include<vector>
using namespace std;

/* ✔️⭐Approach - 1 (using DFS, and 2 types of visited maps)

    basic idea :- but why are we maintaing a 'dfsCallVisited' map ?
                  this is because we are keep track of the calls through which we are reaching the end. 
                  and when a neighbour is visited, as well as its dfs call is viised, that means we are coming from 'neigh' node and along the way we met 'neigh' node again
     
          que :- but why can we not use 1 maps only, to track 'visite' and then while returning from a node we will mark it as 'false'
          ans : because if we do so , when a component ends, 2d loop will call for another node, and then again DFS of the same node will be done, 
                so to optimise the time we used 2 extra spaces
                

    T : O(V+E)
    S : O(V+E)

    ☑️solved at code studio : https://www.codingninjas.com/codestudio/problems/detect-cycle-in-a-directed-graph_1062626?leftPanelTab=0&utm_source=youtube&utm_medium=affiliate&utm_campaign=Lovebabbar
    ⚠️TLE at GFG : https://practice.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article

*/

// fun.2 
void createAdjList(vector<pair<int,int>> &edges, unordered_map<int,list<int>> &AdjList){
  for(int i = 0; i < edges.size(); i++){

    int node1 = edges[i].first;
    int node2 = edges[i].second;

    AdjList[node1].push_back(node2);
  }
}

// fun.3 
bool DFSCycleDetection(unordered_map<int,list<int>> &AdjList, unordered_map<int,bool> &visited, unordered_map<int,bool> &dfsCallVisited, int src){

  visited[src] = true;

  // loop to explore all the neighbours of 'src' node (depth wise)
  for(int neigh:AdjList[src]){

    // when a neighbour is visited, as well as its dfs call is viised, that means we are coming from 'neigh' node and along the way we met 'neigh' node again
    if(visited[neigh] && dfsCallVisited[neigh]) return true; // LOOP FOUND 

    else{
      // before doing a rec call, set its dfsCallVisited as true, and while returning set it again false
      dfsCallVisited[neigh] = true;
      bool ans = DFSCycleDetection(AdjList, visited, dfsCallVisited, neigh);
      dfsCallVisited[neigh] = false;
      if(ans) return ans;
    }
  }

  return false;
}

// Main function 
int detectCycleInDirectedGraph(int n, vector < pair < int, int >> & edges) {


  // creating AdjList, visited map, and special 'DFSvisited' map
  unordered_map<int,list<int>> AdjList;
  unordered_map<int,bool> visited;
  unordered_map<int,bool> dfsCallVisited;

  createAdjList(edges, AdjList);

  // lets traverse all the components of the graph, and if node is not visited, lets do DFS
  for(int i = 1; i <= n; i++){
    if(!visited[i]){
      int ans = DFSCycleDetection(AdjList, visited, dfsCallVisited, i);
      if(ans==1) return 1;
    }
  }

  return 0;




}