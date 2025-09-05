/*✔️⭐ Approach - 1 (using DFS, backtracking)

            explanation : - idea is very simple, what we do is we know the src is node 0, and desti is last node of graph (eg. there are 5 nodes in graph, then the desti node is 4), so we will traverse all posssible paths from the 'src' to the desti, and keeep track of the path along which we are traverling (using backtracking), and this way we can find all possible ways using DFS concept
    
         ✅T : O(E+V) 
         ✅S : O(E+V) - for AdjList, visited vector, rec call stack currPath vec 

         
    ☑️ solved at leetcode : https://leetcode.com/problems/all-paths-from-source-to-target/description/

*/

class Solution {

    
private:
    // function.2 : to create AdjList from the given 'graph'
    void createAdjList(vector<vector<int>> &graph, unordered_map<int,list<int>> &AdjList){
        // note : the graph is not the normal 2d 'edges' 2d vec 

        int rowSize = graph.size();
        for(int i=0; i < rowSize; i++){
            int colSize = graph[i].size();
            AdjList[i]; // creating a block for the key
            for(int j = 0; j < colSize; j++){
                AdjList[i].push_back(graph[i][j]);
            }
        }
    }

private:
    // fun.3 : function that cause till the very depth of the 'src' node, and then keeps track of the path from where it reached there, it is a rec backtracking function
    void dfs(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, vector<vector<int>> &allPaths, vector<int> &currPath, int src, int desti){
        
        // base case - if we reached destination, then store the curr path into ans, and return 
        if(src == desti){
            allPaths.push_back(currPath);
            return;
        }

        visited[src] = true;

        // explore all the ndoes of src, from the adjList if it is not visited
        for(auto neigh:AdjList[src]){
            if(!visited[neigh]){
                currPath.push_back(neigh);
                dfs(AdjList, visited, allPaths, currPath, neigh, desti);
                currPath.pop_back(); // backtrack
            }
        }

        visited[src] = false;
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        
        // create AdjList, and visited vector
        unordered_map<int,list<int>> AdjList;
        createAdjList(graph, AdjList);
        vector<bool> visited(AdjList.size(), false);

        // now do dfs of the graph , and maintain a 2d vec ans, and a curr length
        int src = 0, desti = AdjList.size()-1;
        vector<vector<int>> allPaths;
        vector<int> currPath;

        currPath.push_back(0);
        dfs(AdjList, visited, allPaths, currPath, src, desti);

        return allPaths;
    }
};