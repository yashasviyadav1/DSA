// ☑️leetcode link : https://leetcode.com/problems/minimum-height-trees/description/

/* ✔️⭐Approach - 2 (using 'TopoSort' alike (not exact) idea of inorder and removing leafs)
        explanation :- here what we do is we store the indegrees of each and every node of undirected graph into a vector<int> 'inorder' and then in 1st iteration of while loop, we will pop each node and then decrement the indegree of the neighbours of the front node by 1, i.e we basically remove all the leaf nodes (i.e nodes with indegree 1) then we repeat this untill we have 2 or lesser nodes left that are not explored yet, these left nodes in the queue are the ones that can be root with a minimum height
     
        ✅T : O(4*(E+V)) => O(E+V)
        ✅S : O(E+V) - for AdjList, queue, inorder

*/ 

class Solution {
    
private:
    void createAdjList(vector<vector<int>> &edges, unordered_map<int,list<int>> &AdjList){

        for(int i=0; i < edges.size(); i++){
            int node1 = edges[i][0];
            int node2 = edges[i][1];
            // undirected graph
            AdjList[node1].push_back(node2); 
            AdjList[node2].push_back(node1);
        }
    }

public:
    // main func
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        
        // exception case - if the tree has only 1 node , so that node 0 is the ans 
        if(n==1) return {0}; 

        // step 1 : we first need to create a adjlist
        unordered_map<int,list<int>> AdjList;
        createAdjList(edges, AdjList);

        // step 2: now create a vector<int> inorder, and map index to nodes, and values to the respective values 
        vector<int> indegree(n,0); // initially all the nodes have ind 0
        for(auto i:AdjList){
            indegree[i.first] = i.second.size();
        }

        // step 3 : create a queue for BFS ,and push all the nodes with indegree 1 into it 
        queue<int> q;
        for(int i=0; i < indegree.size(); i++)
            if(indegree[i] == 1)
                q.push(i);

        // step 4 : what we will do is we will remove the leaf nodes per iteration, so we need to maintain how many 'unexploredNodes' are still left , so when only 2 or lesser nodes are left in the graph that are unexplored, that means they are the ones which can be the root with min height 
        int unexploredNodes = n; // initially all are unexplored

        while(unexploredNodes > 2){

            int size = q.size();

            // lets say curr q has 'n' nodes, so explore all of them and their neighbours
            for(int i=0; i < size; i++){
                int front = q.front();
                q.pop();
                indegree[front]--;
                // explore all the neighbours of the front and decrement their indegrees by 1 (because we have explored a leaf ), whenever a neighbours indegree becomes 1, that means we got a new leaf, so store it into q
                for(auto neigh:AdjList[front]){
                    indegree[neigh]--;
                    if(indegree[neigh] == 1)
                        q.push(neigh);
                }
            }

            // since 'size' nodes are explored so decrement the 'unexploredNode'
            unexploredNodes -= size;

        }

        // now the nodes left in the queue are the nodes that can be roots with minimum heights 
        vector<int> ans;
        while(!q.empty()){
            ans.push_back(q.front());
            q.pop();
        }

        return ans;

    }
};