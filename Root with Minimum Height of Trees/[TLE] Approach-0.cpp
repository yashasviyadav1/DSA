// ⚠️leetcode link : https://leetcode.com/problems/minimum-height-trees/description/

// Approach - 1 
/* ⚠️works but TLE[ Test Case :66 / 71] Approach - 1(using DFS, brute force)

            explanation :- here what we do is we will do a dfs traversal for each node of this graph, then store the max depth (height) from each node and return the min height nodes at the end

        ⚠️T : O(N^2) - where n is number of nodes in graph (because for every node of graph, we are exploring all nodes of graph again)
        ⚠️S : O(N^2)  

*/
class Solution {
    
private:
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
    void DFS(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, int &maxHeight, int currHeight, int src){

        maxHeight = max(maxHeight, currHeight);

        visited[src] = true;
        for(auto neigh:AdjList[src]){
            if(!visited[neigh])
                DFS(AdjList, visited, maxHeight, currHeight + 1, neigh);
        }
    }

public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        
        // we need a visited vector, AdjList, a map to map 'edgesToDepth'

        vector<bool> visited(n,false);
        unordered_map<int,list<int>> AdjList;
        unordered_map<int,int> edgesToDepth;

        createAdjList(edges, AdjList);

        //now lets do a dfs of each node and then Find its max depth and store it into edgesToDepth
        for(int i = 0; i < n; i++){
            int maxHeight = 0;
            DFS(AdjList, visited, maxHeight, 0, i);
            edgesToDepth[i] = maxHeight; 
            // set all nodes as unvisited again
            fill(visited.begin(), visited.end(), false);
        }

        // now traverse the map and find the min depth 
        int minDepth = INT_MAX;
        for(auto i:edgesToDepth){
            minDepth = min(minDepth,i.second);
        }

        // now lets fetch all the minDepth nodes from map, and store them into a vector 'ans' 
        vector<int> ans;
        /* debug
        for(auto i:edgesToDepth){
            cout << "root node : " << i.first << ", max Depth : " << i.second << endl;
        }
        */
        for(auto i:edgesToDepth){
            if(i.second == minDepth)
                ans.push_back(i.first);
        }

        return ans;

    }
};