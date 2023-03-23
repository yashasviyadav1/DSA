// Solved(✔️) - Eventual Safe States - 1 approach (topoSort BFS inorder logic )
// ☑️leetcode link : https://leetcode.com/problems/find-eventual-safe-states/

/*✔️⭐ App-1 (using topoSort's inorder concept)

        explanation :- 
                    step 1 : firstly create a adjlist (but in reverse order) i.e take key as 'node' and its value as the list of all the vertices are pointing to 'node' i.e which are connected to node, now we will reverse all the edges directions, also maintain a vector or map to store all the indegrees of this flipped graph 
                    step 2 : now push the nodes with indegree 0 into queue and apply the inorder logic of kahn's algo
                    step 3 : now at the end of this logic we have our safe nodes in a vector, sort it and return it (asked in the question)


        ✅T : O((V+E)*Log(V+E))
        S : O(V+E) - for queue, Adjlist, indegree vector 

    note : no need for visited vector, coz we are never going to visit the nodes in a cycle in the topological inorder concept
*/

class Solution {

private:
    // fun.2 
    void createAdjList(vector<vector<int>> &graph, unordered_map<int,list<int>> &AdjList, vector<int> &nodeToIndegree, queue<int> &q){

        for(int i=0; i < graph.size(); i++){
            AdjList[i];
            nodeToIndegree[i] = graph[i].size();
            if(nodeToIndegree[i] == 0) q.push(i); // storing 0 indegree nodes into the q 

            // here we will be creating a different type of adjlist, where key -> node, and value will be list of nodes that are pointing to 'node' (all incomming nodes), because we want to backtrack from terminal to non safe nodes (i.e revered adjList)
            for(int node:graph[i])
                AdjList[node].push_back(i);
        } 
    }
    
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

        int V = graph.size();
        // step 1 : create adj list, and also flip the edges of graph (i.e outgoing edge becomes incomming, and incoming edge becomes outgoing) , how to do that? just create a map/vector nodeToInorder(index = node, val = inorder), and now count the outgoing edges inside the graph for each node and save them as the 'indegree' for each node
        vector<int> nodeToIndegree(V);
        unordered_map<int,list<int>> AdjList;

        // also create a queue and store the 0 indegree edges into it 
        queue<int> q;
        createAdjList(graph, AdjList, nodeToIndegree, q); // AdjList created, and edges fliped and after that indegree is stored in the AdjList
;
        // now lets traverse the queue (like we do in Kahn's Algo (BFS Toposort))
        vector<int> safeNodes;
        while(!q.empty()){

            int front = q.front();
            q.pop();

            // store the front node into safeNode
            safeNodes.push_back(front);

            // remove it from graph by decrementing its neighbours indegree by 1 
            for(int neigh:AdjList[front]){
                nodeToIndegree[neigh]--;
                if(nodeToIndegree[neigh] == 0)
                    q.push(neigh);
            }
        }

        // now when the queue becomes empty that means that all the nodes in the 'nodesToInorder' map/vec with value 1 are those which are part of some loop or cycle so they can never be safe nodes, so our safe nodes are already stored in the vector but in random order, so sort this vector and return it
        sort(safeNodes.begin(), safeNodes.end());
        return safeNodes;
        
        
    }
};

