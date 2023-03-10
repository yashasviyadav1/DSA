
/* ✔️⭐App-1 (Prim's Algo)

    explanation - applying prims algo.

    T : O ( ( V + E ) l o g V )
    S : O( V + E)

    📝note : prim's algo can be used to find 2 things 
        1) total cost of all nodes in a min spanning tree 
        2) to know how nodes will be connected in a min spanning tree
    
    ☑️solved at leetcode : https://leetcode.com/problems/min-cost-to-connect-all-points/

*/

class Solution {

    public:
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
    // main function
    int minCostConnectPoints(vector<vector<int>>& points) {
        
        // creating a adj list from these given coordinates 
        unordered_map<int,list<pair<int,int>>> AdjList;      // AdjList(ele -> list of pair(node,weight))
        
        for(int i=0; i<points.size(); i++){
            int x1 = points[i][0];
            int y1 = points[i][1];
            for(int j = i+1; j < points.size(); j++){
                int x2 = points[j][0];
                int y2 = points[j][1];
                
                int manhatanDist = abs(x2 - x1) + abs(y2 - y1);

                AdjList[i].push_back({j,manhatanDist});  // undirected graph 
                AdjList[j].push_back({i,manhatanDist});
            }
        }

        // now we have the AdjList so lets implement the Prim's Algo , to find sum of all node's cost in minSpanning tree
        // we need to keep track of the visited nodes
        vector<bool> visited(points.size(),false);
        
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
                MST.push_back({parent,node}); // this step is not necessary for this question - because here they have not asked for how the nodes will connect in the min spanning tree, here they have only asked to return the minSpanning tree's cost of all nodes
                MSTcost += weight;
            }
            
            // now explore all neigh of 'node' and then for all the non visited neigh create 'triple' and push them in minheap 
            for(auto neighPair:AdjList[node]){
                
                int neigh = neighPair.first;
                int weight = neighPair.second;
                
                if(!visited[neigh])
                    minHp.push(new triple(weight, neigh, node)); // 'node' is the parent of 'neigh'
                
            }
            
            delete topTriple; // free up memo
        }

        // returning cost of min spanning tree 
        return MSTcost; 

    }
};

