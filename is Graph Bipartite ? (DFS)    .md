## Is Graph Bipartite ?
☑️solved at leetcode :- [link](https://leetcode.com/problems/is-graph-bipartite/description)
------
### ⭐ Approach - 1 (DFS + nodeToColor array)
```cpp
 idea :- so for a graph to be bipartite every 2 adjacent verticies should not have the same color, so we take 2 colors (0,1) and can apply DFS and color each of the nodes, now before coloring, we check if this 'neigh' node and the 'src' node i.e the 2 adj nodes have same color? if yes then its not a bipartite graph, else it is a bipartite graph.

        ✅T : O(E+V)
        ✅S : O(E+V)
```
![graph (1)](https://github.com/YashasviCodes/DSA-Questions/assets/124666305/cd179ae3-55b9-4533-b73e-c47a1d1fe158)
![graph](https://github.com/YashasviCodes/DSA-Questions/assets/124666305/6797fd36-1867-4ce7-98fd-c89363cf8aaf)
in above fig, 2 adj nodes have same color found, therefore it is not a Bipartite Graph.
### code :- 
```cpp
class Solution {
        
private:
    void createAdjList(vector<vector<int>> &graph, unordered_map<int,list<int>> &AdjList){

        for(int i=0; i < graph.size(); i++){
            int node = i;
            AdjList[node];
            for(int j=0; j < graph[i].size(); j++){
                int neigh = graph[i][j];
                AdjList[i].push_back(neigh);
            }
        }
    }

    bool DFS(unordered_map<int,list<int>> &AdjList, vector<int> &nodeToColor, int currColor, int src){
        
        // color the 'src' node, with its respective 'currColor'
        nodeToColor[src] = currColor;
        
        // if any of its neigh already has been colored with the same color as the src (or its parent) then it can never be a bipartite graph
        for(int neigh:AdjList[src]){
            
            if(nodeToColor[neigh] == currColor) // adj nodes with same color found, not BIPARTITE graph
                return false; // not bipartite
                
            else if(nodeToColor[neigh] == -1){ // else if the neigh doest have same color as parent(src) and the neigh is not yet colored, then color it by DFS
                bool isBipartite = DFS(AdjList, nodeToColor, !currColor, neigh);
                if(!isBipartite) return false; // not bipartite
            }
        }
        return true;// bipartite 
    }

public:
    // main 
    bool isBipartite(vector<vector<int>>& graph) {

        // AdjList
        unordered_map<int,list<int>> AdjList;
        createAdjList(graph, AdjList);
        int V = AdjList.size();

        // lets say there are 2 colors, B=0, Y=1, -1(not yet color)
	    vector<int> nodeToColor(V, false); 
	    for(int i=0; i < V; i++) nodeToColor[i] = -1; // initially all nodes are uncolored 
	    
	    // calling DFS for all components of the graph 
	    int currColor = 0; // color first node as currColor
	    for(int node=0; node<V; node++){
	        
	        if(nodeToColor[node] == -1){ // if a node is not colored, then call DFS to color it
	            bool isBipartiteGraph = DFS(AdjList, nodeToColor, currColor, node);
	            if(!isBipartiteGraph)
	                return false; // if graph is not bipartite return false
	        }
	    }
	    
	    return true; // reached here means graph is bipartite

    
    }
};
```
