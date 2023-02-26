
// This approach gives right output, but takes lot of time because its a recursive algo.
// [⚠️TLE at ] Leetcode : https://leetcode.com/problems/find-if-path-exists-in-graph/description/

/* ⚠️(TLE TC-12/29) Approach - 1 (simple DFS)

        explanation : do a dfs of 'src' node and return true if destination can be reached, else return false, when all depths are explored and no way found to reach the desti
    
         T : O(V+E)
         S : O(V+E)

*/

/* // code : 
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

    // fun.3: this function does a dfs and return true when destination can be reached , else return false
    bool DFS(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, int src, int desti){
        // base case - if we reached the desti node ,return true
        if(src == desti) return true;

        // visit the src node and call dfs for all the unvisited neighbours of the 'src' node
        visited[src] = true;

        for(auto neigh:AdjList[src]){
            if(!visited[neigh]){
                bool ans = DFS(AdjList, visited, neigh, desti);
                if(ans) return true; // when desti is found , retur true
            }
        }

        // when all the depths of src are explored and no desti found, return true
        visited[src] = false;
        return false;
    }
public:
    bool validPath(int n, vector<vector<int>>& edges, int src, int desti) {

        // creating AdjList, visited vector<bool>
        unordered_map<int,list<int>> AdjList;
        vector<bool> visited(n,false); // all nodes are unvisted initially 
        createAdjList(edges, AdjList);

        // now call simple dfs for src node
        bool ans = DFS(AdjList, visited, src, desti);

        return ans;

        
    }
};

*/