/* ✔️⭐⭐Approach - 3 (only BFS, no parent d.s )

        // explanation :- while exploring the neighbours of nodes breadth wise, if we reach the desti, then return true, if all the nodes are explored and queue becomes empty, then return false
    
         ✅T : O(V+E)
         ✅S : O(V+E)

    // [Solved at ☑️] Leetcode : https://leetcode.com/problems/find-if-path-exists-in-graph

*/
//code 
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
    bool BFS(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, int src, int desti){

        // create a queue and store the src node into it, also mark it visited, and set its parent as -1 (becuase that means we are starting BFS for this component from src node)
        queue<int> q;
        q.push(src);
        visited[src] = true;

        // if src is desti, return true
        if(src == desti) return true;

        // loop while q is non empty
        while(!q.empty()){

            // fetch front node, remove it from the queue, then all its non visited nodes into queue, and set their parent as 'front', also mark neigh as visited
            int front = q.front();
            q.pop();

            for(auto neigh:AdjList[front]){
                if(!visited[neigh]){

                    // if neigh node is the desti, return true
                    if(neigh == desti) return true;

                    q.push(neigh);
                    visited[neigh] = true;
                }
            }
        }

        // if queue becomes empty
        return false;

    }

public:
    bool validPath(int n, vector<vector<int>>& edges, int src, int desti) {
        if(n == 1 || src == desti) return true; // when only 1 node is present is the graph, src and desti is that node itself

        // creating AdjList, visited vector<bool>
        unordered_map<int,list<int>> AdjList;
        vector<bool> visited(n,false); // all nodes are unvisted initially 
        createAdjList(edges, AdjList);

        // now call simple BFS for src node,and return whetever it gives as output
        bool ans = BFS(AdjList, visited, src, desti);
        return ans;
        
    }
};
