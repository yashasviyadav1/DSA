#include <bits/stdc++.h> 

/* ✔️⭐Approach 2 (using BFS - Kahn's Algo)

        explanation :- in kahn's algo we use a d.s inorder instead of visited 
        
      ☑️solved at codestudio : https://www.codingninjas.com/codestudio/problems/topological-sort_982938?topList=love-babbar-dsa-sheet-problems&leftPanelTab=0&utm_source=youtube&utm_medium=affiliate&utm_campaign=Lovebabbar
   
     ✅T : O(E+V) 
     ✅S : O(E+V) - for queue and AdjList (no visited vector used)

*/

// Fun.2 : main function
void createAdjList(vector<vector<int>> &edges, unordered_map<int,list<int>> &AdjList){
    for(int i=0; i < edges.size(); i++){
        int node1 = edges[i][0];
        int node2 = edges[i][1];

        AdjList[node1].push_back(node2); // coz directed graph
    }
}

// Main fun
vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)  {
     
     // step 1: create a AdjList 
    unordered_map<int,list<int>> AdjList;
    createAdjList(edges, AdjList);

    // step 2 : create a vector<int> 'indegree' and initially set all indegrees of all the nodes as 0
    vector<int> indegree(v,0);
    for(int i=0; i < AdjList.size(); i++)
        for(auto neigh:AdjList[i])
            indegree[neigh]++;
    

    // step 3 : create a queue 'q' then traverse the inorder vector insert all the nodes with indegree 0 into the queue 
    queue<int> q;
    for(int i=0; i<indegree.size(); i++)
        if(!indegree[i])
            q.push(i);
    
    vector<int> topoOrder;
    // step 4 : do BFS using q
    while(!q.empty()){
        
        // fetch the front node and pop it, also save it into vector 'topoOrder'
        int front = q.front();
        q.pop();
        topoOrder.push_back(front);

        // now explore all the neighbours of front node, and decrement their indegrees of neighbours by 1, and if a neighbours indegree becomes 0, then push it into the q
        for(int neigh:AdjList[front]){
            indegree[neigh]--;
            if(indegree[neigh] == 0)
                q.push(neigh);
        }
    }

    // if the topoOrder is not of length == number of Verticies (means graph is cyclic) 
    if(topoOrder.size() != v) return {};

    // else no cycle found , so the correct order of topoOrder is 'topoOorder'
    return topoOrder;
}
