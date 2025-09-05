// ☑️solved at gfg : https://practice.geeksforgeeks.org/problems/minimum-spanning-tree/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=minimum-spanning-tree

/* ✔️⭐App-1 (Prim's Algo)

    explanation - applying prims algo.

    T : O ( ( V + E ) l o g V )
    S : O( V + E)

    📝note : prim's algo can be used to find 2 things 
        1) total cost of all nodes in a min spanning tree 
        2) to know how nodes will be connected in a min spanning tree

*/


class Solution
{
    // class triple - to store weight,node,parent together
    class triple{
        public:
            int weight;
            int node;
            int parent;
            triple(int weight, int node, int parent){
                this -> weight = weight;
                this -> node = node;
                this -> parent = parent;
            }
    };
    
    // compare class - to sort min heap based on weight
    class compare{
        public:
            bool operator()(triple* a, triple* b){
                return a->weight > b->weight;
            }
    };

	public:
    // Main func
    int spanningTree(int V, vector<vector<int>> Adj[])
    {
        // we need to keep track of the visited nodes
        vector<bool> visited(V,false);
        
        // we also need to store the (weight,node,parent) in a minheap (based on weight)
        priority_queue<triple*, vector<triple*>, compare> minHp;
        
        // MST to store minSpaning tree  pair(parent,node), also we need to return teh minSpaning trees cost
        int MSTcost = 0;
        vector<pair<int,int>> MST;
        
        // now inserting the initial node in minhp (weigth = 0, node = 0, parent = -1)
        minHp.push(new triple(0,0,-1));
        
        while(!minHp.empty()){
            
            triple* topTriple = minHp.top();
            minHp.pop();
            
            // fetch weight,node, parent from triple
            int weight = topTriple -> weight;
            int node = topTriple -> node;
            int parent = topTriple -> parent;
            
            // VIP. if node is already visited, then that means min edge from this 'node' to some other node is already found, so skip this iteration
            if(visited[node]) continue;
            
            // mark node as visited
            visited[node] = true;
            
            // store the node, parent into MST if parent is not -1 (i.e if node is not the starting node of this algo)
            if(parent != -1){
                MST.push_back({parent,node});
                MSTcost += weight;
            }
            
            // now explore all neigh of 'node' and then for all the non visited neigh create 'triple' and push them in minheap 
            for(auto neighVec:Adj[node]){
                
                int neigh = neighVec[0];
                int weight = neighVec[1];
                
                if(!visited[neigh])
                    minHp.push(new triple(weight, neigh, node)); // 'node' is the parent of 'neigh'
                
            }
            
            
            delete topTriple; // free up memo
        }
        
        
        return MSTcost;
        
    }
};

//--------------------------------------------------------------------------------
