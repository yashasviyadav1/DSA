
#include<unordered_map>
#include<list>
#include<vector>
#include<string>
#include<queue>
#include<iostream>
using namespace std;

/*✔️⭐ Approach - 1 (using BFS)

    T : O(V + E)
    S : O(3*(V + E)) - visited map, childToparent map, AdjList map
    
    ☑️solved at code studio : https://www.codingninjas.com/codestudio/problems/cycle-detection-in-undirected-graph_1062670?leftPanelTab=0
    ☑️solved at gfg : https://practice.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1

*/

// function to create a AdjList from given edges 2d vector 
void createAdjList(vector<vector<int>> &edges, unordered_map<int,list<int>> &AdjList){

    for(int i = 0; i < edges.size(); i++){
        int node1 = edges[i][0];
        int node2 = edges[i][1];

        (AdjList[node1]).push_back(node2);
        (AdjList[node2]).push_back(node1);
    }
}

bool BFSLoopDetection(unordered_map<int,list<int>> &AdjList, unordered_map<int,bool> &visited,  unordered_map<int,int> &childToParent, int src){

    // visit the src node, and create a queue and push src into it
    queue<int> q;
    q.push(src);
    childToParent[src] = -1; // when there is no parent of a node
    
    // lets do traversal breath wise untill queue becomes empty
    while(!q.empty()){

        // fetch the front and visit it 
        int front = q.front();
        visited[front] = true; 
        
        q.pop();

        // explore all the neighbours of the front
        for(int neigh:AdjList[front]){

            // when a neighbour of front is not visited, push it into queue and then save its parent as front
            if(!visited[neigh]){
                q.push(neigh);
                childToParent[neigh] = front;
            }

            // els ewhen a neighbour is already visitesd, but is not the parent of front that means that loop found 
            else if (childToParent[front] != neigh) return true; // loop found
        }
    }
    
    // when all the nodes of a component are exolored breadth wise , but no loop is found so return false 
    return false;
}

// Main function
string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    // extra space used 
    unordered_map<int,bool> visited;
    unordered_map<int,int> childToParent;

    // creating a AdjList
    unordered_map<int,list<int>> AdjList;
    createAdjList(edges, AdjList);

    // lets traverse all components of a graph iff it is not already visited, and if atleast 1 of the components havae a loop then return true 
    for(int i =1; i <= n; i++){

        if(!visited[i]){
            int ans = BFSLoopDetection(AdjList, visited, childToParent, i);
            if(ans) return "Yes";
        }
    }

    // when all components are checked and no cycle found then return false
    return "No";
    
}
