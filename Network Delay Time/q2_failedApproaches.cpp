
// i tried simple BFS + shortest distance to all nodes from single source algo, but it did not worked 

// ----------------failed approach - 2 ----------------------------------------------------
/*❌ Approach - 2 (using 'all nodes shortest distance algo + BFS (instead of TopoSort))
        
        Explanation :- failed at some complex Test case 
                    [[4,2,76],[1,3,79],[3,1,81],[4,3,30],[2,1,47],[1,5,61],[1,4,99],[3,4,68],[3,5,46],[4,1,6],[5,4,7],[5,3,44],[4,5,19],[2,3,13],[3,2,18],[1,2,0],[5,1,25],[2,5,58],[2,4,77],[5,2,74]]
                    
                    V = 5
                    src = 3

         T : O(E+V) => O(E+V) for AdjList + O(E+V) for BFS, + O(E+V) for traversing the distance array (worst case )
         S : O(E+V) - for rec stack, AdjList, visited, queue

*/
/*
class Solution {
    

private:
    // fun.2 
    void createAdjList(vector<vector<int>> &times, unordered_map<int,list<pair<int,int>>> &AdjList){

        for(int i=0; i < times.size(); i++){
            int node1 = times[i][0];
            int node2 = times[i][1];
            int weight = times[i][2];
            AdjList[node1].push_back({node2,weight});
        }
    }

    // fun.3 
    void BFS(unordered_map<int,list<pair<int,int>>> &AdjList, vector<bool> &visited, vector<int> &BFSvector, int src){

        // now create a queue and push src into it
        queue<int> q;
        q.push(src);
        visited[src] = true;

        while(!q.empty()){
            int front = q.front();
            BFSvector.push_back(front);
            q.pop();

            for(auto neighPair:AdjList[front]){
                int neigh = neighPair.first;
                int weight = neighPair.second;
                if(!visited[neigh]){
                    visited[neigh] = true;
                    q.push(neigh);
                }
            }  
        }
    }
    
    // fun.4 
    int findMinTimeForAllNodes(unordered_map<int,list<pair<int,int>>> &AdjList, vector<int> &allMinTime, vector<int> &BFSvector , int src){

        // set the allMinTime[src] = 0 (coz it takes 0 sec to reach a node to itself)
        allMinTime[src] = 0;
        
        // now run a loop while BFSvetcor is non empty, fetch the topNode
        for(int i=0; i < BFSvector.size(); i++){

            int topNode = BFSvector[i];

            // if the allMinTime = INT_MAX, means we cant reach this node from src, return -1 (cant send signals to all nodes)
            if(allMinTime[topNode] == INT_MAX) continue;// coz this means we are at a node, where we have not found a path to reach fromm source yet, but may find in future

            // now explore all childs of the topNode, and if the 'new path from (src -> topNode -> neighbour) takes lesser time, then update this allMinTime[neigh], else leave it as it is
            for(auto neighPair:AdjList[topNode]){
                int neigh = neighPair.first;
                int weight = neighPair.second;
                if(allMinTime[topNode] + weight < allMinTime[neigh])
                    allMinTime[neigh] = allMinTime[topNode] + weight;
            }
        }

        // now we have all the min time required to reach all other nodes starting from the src , lets traverse this vector 'allMinDis' and if any node has minTIme = inf (i.e we cant reach it) return -1, else if loop ends, return whatever is the maximum time of the 
        int maximumTimeDelay = 0;
        for(int i=1; i < allMinTime.size(); i++){ // i starts from 1 because nodes are from 1 to V
            if(allMinTime[i] == INT_MAX) return -1;
            maximumTimeDelay = max(maximumTimeDelay, allMinTime[i]);
        }

        return maximumTimeDelay;
    }
public:
    // main func
    int networkDelayTime(vector<vector<int>>& times, int V, int src) {

        // lets first create a adj list, visited vector, BFS vector, 'time' vector (this will store all the min times taken to reach all other nodes from the source node) 
        unordered_map<int,list<pair<int,int>>> AdjList;
        vector<bool> visited(V, false);
        vector<int> allMinTimes(V + 1, INT_MAX); // initially all the nodes are set to inf time (note : nodes are form 1 to V)
        allMinTimes[0] = -9999; // garbage value for node 0, coz it doesnt exist 

        vector<int> BFSvector;

        // fill AdjList, and BFSvector starting with src calling fun.2, fun.3
        createAdjList(times, AdjList);

        BFS(AdjList, visited, BFSvector, src);


        // now call.fun4 to find all shortes time required to reach all other nodes from the src (using all ndoes shortest path from single src Algorithm)


        int ans = findMinTimeForAllNodes(AdjList,allMinTimes, BFSvector, src);

        return ans;


    }
}; 
*/

//----------------failed approach - 1 -------------------------------------------------

/* ❌Approach - 1 (using 'all nodes shortest distance algo + topoSort)
        
        IMP Note :
        
            this passes when graph is directed acyclic graph
            but fails when graph is weighted directed cyclic graph (because in cyclic grpah toposort order is not correct, which will effect the 'allMinTime' vector)

         T : O(E+V) => O(E+V) for AdjList + O(E+V) for toposort, + O(E+V) for traversing the distance array (worst case )
         S : O(E+V) - for rec stack, AdjList, visited, queue

    */

/*
class Solution {
    

private:
    // fun.2 
    void createAdjList(vector<vector<int>> &times, unordered_map<int,list<pair<int,int>>> &AdjList){

        for(int i=0; i < times.size(); i++){
            int node1 = times[i][0];
            int node2 = times[i][1];
            int weight = times[i][2];
            AdjList[node1].push_back({node2,weight});
        }
    }

    // fun.3 
    void DFStopoOrderFinder(unordered_map<int,list<pair<int,int>>> &AdjList, vector<bool> &visited, stack<int> &topoStack, int src){

        // mark the src as visited, and explore its neighbours, when a neighbour is not visited, then mark it visited, and call DFS for it
        visited[src] = true;

        for(auto neighPair:AdjList[src]){
            int neigh = neighPair.first;
            if(!visited[neigh]){
                visited[neigh] = true;
                DFStopoOrderFinder(AdjList, visited, topoStack, neigh);
            }
        }

        // when all childs are explored, then while returning store the src node into stack (and do not unvisit it)
        topoStack.push(src);
    }
    
    // fun.4 
    int findMinTimeForAllNodes(unordered_map<int,list<pair<int,int>>> &AdjList, vector<int> &allMinTime, stack<int> &topoStack, int src){

        // set the allMinTime[src] = 0 (coz it takes 0 sec to reach a node to itself)
        allMinTime[src] = 0;

        // now run a loop while stack is non empty, fetch the topNode
        while(!topoStack.empty()){

            int topNode = topoStack.top();
            topoStack.pop();

            // if the allMinTime = INT_MAX, means we cant reach this node from src, return -1 (cant send signals to all nodes)
            if(allMinTime[topNode] == INT_MAX) continue;// coz this means we are at a node, where we have not found a path to reach fromm source yet, but may find in future

            // now explore all childs of the topNode, and if the 'new path from (src -> topNode -> neighbour) takes lesser time, then update this allMinTime[neigh], else leave it as it is
            for(auto neighPair:AdjList[topNode]){
                int neigh = neighPair.first;
                int weight = neighPair.second;
                if(allMinTime[topNode] + weight < allMinTime[neigh])
                    allMinTime[neigh] = allMinTime[topNode] + weight;
            }
        }

        // now we have all the min time required to reach all other nodes starting from the src , lets traverse this vector 'allMinDis' and if any node has minTIme = inf (i.e we cant reach it) return -1, else if loop ends, return whatever is the maximum time of the 
        int maximumTimeDelay = 0;
        for(int i=1; i < allMinTime.size(); i++){ // i starts from 1 because nodes are from 1 to V
            if(allMinTime[i] == INT_MAX) return -1;
            maximumTimeDelay = max(maximumTimeDelay, allMinTime[i]);
        }

        return maximumTimeDelay;
    }
public:
    // main func
    int networkDelayTime(vector<vector<int>>& times, int V, int src) {

        // lets first create a adj list, visited vector, topoStack, 'time' vector (this will store all the min times taken to reach all other nodes from the source node) 
        unordered_map<int,list<pair<int,int>>> AdjList;
        vector<bool> visited(V, false);
        vector<int> allMinTimes(V + 1, INT_MAX); // initially all the nodes are set to inf time (note : nodes are form 1 to V)
        allMinTimes[0] = -9999; // garbage value for node 0, coz it doesnt exist 

        stack<int> topoStack;

        // fill AdjList, and topoSort calling fun.2, fun.3
        createAdjList(times, AdjList);
        for(int node=1; node<=V; node++){
            if(!visited[node])
                DFStopoOrderFinder(AdjList, visited, topoStack, node);
        }


        // now call.fun4 to find all shortes time required to reach all other nodes from the src (using all ndoes shortest path from single src Algorithm)

        int ans = findMinTimeForAllNodes(AdjList,allMinTimes, topoStack, src);

        return ans;


    }
}; 

*/