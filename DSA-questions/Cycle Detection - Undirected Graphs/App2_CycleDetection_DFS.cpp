#include<iostream>
using namespace std;
#include<unordered_map>
#include<list>
#include<vector>

/* ✔️⭐Approach - 2 (using DFS)

    T : O(V+E)
    T : O(V+E) - rec Stack, visited map, AdjList map

*/

// fun.2 
void createAdjList(vector<vector<int>> &edges, unordered_map<int,list<int>> &AdjList){

    for(int i=0; i < edges.size(); i++){
        int node1 = edges[i][0];
        int node2 = edges[i][1];

        AdjList[node1].push_back(node2);
        AdjList[node2].push_back(node1);
    }
}

// fun.3 
bool DFSCycleDetection(unordered_map<int,list<int>> &AdjList, unordered_map<int,bool> &visited, int src, int parent){

    // visit current src node
    visited[src] = true;
    
    // lets run a loop to traverse all neighbours of 'src' node (depth wise)
    for(int neigh:AdjList[src]){

        // if the neighbour is visited, and is not the parent of 'src' that means there is a loop
        if(visited[neigh] && parent != neigh) return true; // base case
        
        /* note : if we reached here than there can be 2 cases
             case1 : when 'neighbour' of 'src' is not visited,in that case do DFS for it (even if its parent of src, and even if its not parent of src)
             case 2 : when 'neighbour' of 'src' is visited already but 'neigh' is the parent of src, in that case we dont need to DFS it again coz its already explored ones

             so the 2 if conditions handles both these cases very efficiently
        */
        else if(!visited[neigh]){
            int ans = DFSCycleDetection(AdjList, visited, neigh, src);
            if(ans) return true;  
        }
    }
    return false;
}

// main func
string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    // lets create a AdjList of this graph
    unordered_map<int,list<int>> AdjList;
    unordered_map<int ,bool> visited;

    createAdjList(edges, AdjList);

    // lets run a loop for all the components of the graph 
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            int parent = -1;
            bool ans = DFSCycleDetection(AdjList, visited, i, -1);
            if(ans) return "Yes"; // cycle found 
        }
    }

    return "No"; // no cycle 
}

