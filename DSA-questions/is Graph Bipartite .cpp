class Solution {
    /*✔️⭐ Approach - 1 (DFS + visited + setA, setB)
        
         idea :- if every time before even checking if a node is visited or not, we will check if it is already present in its parent's set, then its not a bipartite graph
        
            So if a graph is bipartite then its very clear that 2 adj verticies should not be in same set (A or B), so by usiong this condition, what we can do is vefore calling DFS)
 for any vertex we simply check if it is present in the same set as its parent, if yes then graph can not be a bipartite graph, if no then continue the DFS.
 
        ✅T : O(E+V)
        ✅S : O(E+V)

    */
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

    bool DFS(unordered_map<int,list<int>> &AdjList,vector<bool> &visited, unordered_set<int> &setA, unordered_set<int> &setB, int src, bool isItTurnOfA){
        
        visited[src] = true;

        // including 'src' node in its correct set.
        if(isItTurnOfA) setA.insert(src);
        else setB.insert(src);

        for(int neigh:AdjList[src]){

            // if any node found that is already included in its parent's(src's) set, then return false (graph is not bipartite)
            if(isItTurnOfA){
                if(setA.find(neigh) != setA.end()) // already inc in parent's set 'A'
                    return false;
            }
            else{
                if(setB.find(neigh) != setB.end()) // already inc in parent's set 'B'
                    return false;
            }

            // reached here means node was not in its parent set, so if its not visited, then call DFS for it
            if(!visited[neigh]){
                bool isBipartiteGraph = DFS(AdjList, visited, setA, setB, neigh, !isItTurnOfA); // pass the invert of curr set for the neighbour
                if(isBipartiteGraph == false)  
                    return false;
            }
        }

        return true;

    }

public:
    // main 
    bool isBipartite(vector<vector<int>>& graph) {

        // AdjList
        unordered_map<int,list<int>> AdjList;
        createAdjList(graph, AdjList);
        int V = AdjList.size();
         
        // set A, B (for bipartite graph)
        unordered_set<int> setA;
        unordered_set<int> setB;
        vector<bool> visited(V, false);

        bool isItTurnOfA = true; // lets include first node in 'A' set
        for(int node=0; node < V; node++){
            if(!visited[node]){
                bool isBiPartite = DFS(AdjList, visited, setA, setB, node, isItTurnOfA);
                if(!isBiPartite)
                    return false;
            }
        }

        return true;
    
    }
};
