
// note : dont use unordered_map<int,bool> for visited, rather use a vector to avoid TLE error 
#include <bits/stdc++.h> 
#include<iostream>
#include<unordered_map>
#include<stack>
#include<list>
#include<vector>
using namespace std;

// ✔️(Solved) - Topological Sort - 1 approach 

/* ✔️⭐Approach - 1 (improved) (using DFS, and a stack, 'visited vector' (improvement), AdjList map)

    T : O(V+E)
    S : O(3*(V+E))

    ☑️solved at code studio : https://www.codingninjas.com/codestudio/problems/topological-sort_982938?topList=love-babbar-dsa-sheet-problems&leftPanelTab=0&utm_source=youtube&utm_medium=affiliate&utm_campaign=Lovebabbar
    ☑️solved at gfg : https://practice.geeksforgeeks.org/problems/topological-sort/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article

*/

// Fun.2 : createAdjList()
void createAdjList(vector<vector<int>> &edges, unordered_map<int,list<int>> &AdjList){

    for(int i = 0; i < edges.size(); i++){
        int node1 = edges[i][0];     
        int node2 = edges[i][1];

        AdjList[node1].push_back(node2); // coz its a directed graph
    }
}

// fun.3 
void topoDFS(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, stack<int> &stk, int src){

    // visit the src node
    visited[src] = true;

    // traverse all the neighbours of the src node, and call dfs for unvisited ones 
    for(int neigh:AdjList[src]){
        if(!visited[neigh]){
            topoDFS(AdjList, visited, stk, neigh);
            //node : if we insert the neigh node into stk 'at this line' then what will happen is that all the nodes will be in stack except the node that called this fun. from the component loop (in main func)

        }
    }

    // when a node's all childs are explored, then loop ends and call will return now, so store this node into stk
    stk.push(src);
}

// Main func
vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)  {
    
    // create a AdjList, by calling function 2, also create a visited map, and a special stack
    unordered_map<int,list<int>> AdjList;
    vector<bool> visited(v,false); // did not use map just to not get a TLE error 
    createAdjList(edges, AdjList);

    stack<int> stk; // we used stk coz we needed a LIFO structure for our topological order

    // call fun.3 DFS for all unvisited components of the graph 
    for(int i = 0; i < v; i++){
        if(!visited[i]){
            topoDFS(AdjList, visited, stk, i);
        }
            
    }

    // when stack is filled, fetch all elements from top to bottom and store them into a vector
    vector<int> topoOrder;
    while(!stk.empty()){
        topoOrder.push_back(stk.top());
        stk.pop();
    }

    // return the TS order
    return topoOrder;


    
}