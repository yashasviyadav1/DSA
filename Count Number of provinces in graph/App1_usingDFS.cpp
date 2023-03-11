// (✔️)Solved - Count number of Provinces/Components in a graph - 2 approach (1 DFS ,2 BFS)
// ☑️leetcode link : https://leetcode.com/problems/number-of-provinces

//-----------------------------------------------------------------------------------------------------------------------------------------

/*✔️⭐ Approach - 1 (using simple DFS traversal)

            explanation : we will do a DFS of all the components, and increment the 'provinces' by 1 every time we completely traverse a component 

            Note: the matrix = [[1,1,0],[1,1,1],[0,0,1]]  here eg. if matrix[1][2]==1 means there is an edge between node 2 and node 3 (i.e node = index + 1) , so keep this in mind while creating the AdjList

        ✅T : O(V+E) 
        ✅S : O(V+E)

*/

/*
class Solution {

private:
    // fun.2 : creating AdJlist 
    void createAdjList(vector<vector<int>> &isConnected, unordered_map<int,list<int>> &AdjList){

        // note : indexing starts form 0, but 'matrix[0][1] == 1' means there is an edge between node 1 and node 2 

        int size = isConnected.size();
        for(int i=0; i <size; i++){
            AdjList[i+1]; // note : we added 1 coz nodes are from 1 to n
            for(int j = i+1; j < size; j++){
                if(isConnected[i][j] == 1){ // whenever there is an edge between ith and jth node, save them into AdjList
                    AdjList[i+1].push_back(j+1);
                    AdjList[j+1].push_back(i+1);  // undirected graph 
                }
            }
        }
    }

    // fun.2 
    void DFS(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, int src){

        // visit the src, and go till the depth of all unvisited neigh of src 
        visited[src] = true;

        for(int neigh:AdjList[src])
            if(!visited[neigh])
                DFS(AdjList, visited, neigh);
        

    }
public:
    // main function
    int findCircleNum(vector<vector<int>>& isConnected) {
        
        int V = isConnected.size(); // no. of verticies

        // for dfs we use a AdjList, visited array and recursion
        unordered_map<int,list<int>> AdjList;
        vector<bool> visited(isConnected.size() + 1, false);
        // note : block 0 will not be used
        createAdjList(isConnected, AdjList);

        // call dfs for all components of graph 
        int provinces = 0;
        for(int i=1; i <= V; i++){
            if(!visited[i]){
                DFS(AdjList, visited, i);
                // when a component is completely traversed, then increment the count of provinces
                provinces++; 
            }
        }

        return provinces;
    }
};
*/
