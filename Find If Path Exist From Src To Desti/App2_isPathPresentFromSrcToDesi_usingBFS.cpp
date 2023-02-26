/* ✔️⭐Approach - 2 (simple BFS + parent D.S)

        explanation :- we will do a bfs of the graph from src and store the parent who droped each node into queue, at last when bfs is done, we will start from the desti to reach node src using their parents, and if we are able to reach the 'src' from 'desti' return true, if we cant reach (i.e parent becomes -1) that means src and desti are in 2 different components, so return false

         ✅T : O(V+E) - for doing BFS
         ✅S : O(V+E) - for queue , visited vector, AdjList unordered_map

    🔍 note : initialize the parent of each node with -1, this will help us to find if path exist or not at the end 

*/

// [Solved at ☑️] Leetcode : https://leetcode.com/problems/find-if-path-exists-in-graph

/*
class Solution {
    
    
private:
    // fun.2
    void createAdjList(vector<vector<int>> &edges, unordered_map<int,list<int>> &AdjList){

        for(int i=0; i<edges.size(); i++){
            int node1 = edges[i][0];
            int node2 = edges[i][1];
            AdjList[node1].push_back(node2);
            AdjList[node2].push_back(node1);
        }
    }

    // fun.3 
    void BFS(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, vector<int> &childToParent, int src, int desti){

        // create a queue and store the src node into it, also mark it visited, and set its parent as -1 (becuase that means we are starting BFS for this component from src node)
        queue<int> q;
        q.push(src);
        visited[src] = true;
        childToParent[src] = -1;

        // loop while q is non empty
        while(!q.empty()){

            // fetch front node, remove it from the queue, then all its non visited nodes into queue, and set their parent as 'front', also mark neigh as visited
            int front = q.front();
            q.pop();

            for(auto neigh:AdjList[front]){
                if(!visited[neigh]){
                    q.push(neigh);
                    childToParent[neigh] = front;
                    visited[neigh] = true;
                }
            }
        }

    }

public:
    bool validPath(int n, vector<vector<int>>& edges, int src, int desti) {
        if(n == 1 || src == desti) return true; // when only 1 node is present is the graph, src and desti is that node itself

        // creating AdjList, visited vector<bool>
        unordered_map<int,list<int>> AdjList;
        vector<bool> visited(n,false); // all nodes are unvisted initially 
        createAdjList(edges, AdjList);

        // we also need a d.s to store the childToParent mapping which we can do using vector<int> where index is the child and value is parent
        vector<int> childToParent(n,-1); // initially all have parent -1

        // now call simple BFS for src node, which will fill the parent D.S's indexes with their respective parents who droped them into queue first
        BFS(AdjList, visited, childToParent, src, desti);

        // now we have all parents, so lets track our way back from desti to src, and if we reach src , return true, if we reached parent = -1, then means no way is present from the src to desti, return false
        int child = desti;
        int parent;
        while(child != -1){
            parent = childToParent[child];
            if(parent == src) return true;
            child = parent;
        }

        return false;



        
    }
};
*/