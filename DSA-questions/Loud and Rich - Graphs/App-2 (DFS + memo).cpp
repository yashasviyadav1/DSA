// Solved(✔️) - Loud and Rich - 2 approaches (☑️2.DFS + memo , ⚠️TKE 1.bruteforceDFS)

// ☑️leetcode link : https://leetcode.com/problems/loud-and-rich/description/

//--------------------------------------------------------------------------------------

/* ✔️⭐ Approach - 2 (DFS + memoization)

        understanding question statement :- 

                ans =  [x, , , , ]
                        0 1 2 3 4 
                x will be someone with the least value of quietness among all those who are equally or more richer then 0 

        Algorithm :-

            step1 : so for the desired output discussed above, lets say we are filling ans[i]th element, for that we need to go on and find all the nodes richer or equally welthier then ith node, and then find the least quiet node among them. so bsically we need to start from ith node and go on to eq or more welthier node, for that we can design graph such that u -> v means v is welthier then u, in this way we can move from u to v easily.

            step 2 : now we can traverse the graph, so we can apply DFS for finding the least quiet nodes among all those nodes which we can reach strting from i (using DFS is a good option), but we applied DFS for every node of the graph, which gave us Time Limit, so what better we can do is we can remove the repeatitive work but how? 

            step 3 : ones we reached till the depth, then while returning when all neighbours are explored, store the leastQuietNode, and store it into a unordered+map(node,ans for this 'node') , this way we can find the least quiet node for each node only ones, and in the main func, if we ecplored a node again then we will first check =, if we have ans for this node already present in the map (i.e when map[node] !+ -1) then no need to calculate it again.

        ✅T : O(V+E)
        ✅S : O(V+E)  - adjlist, map(memoization), recursive stack 

        \U0001f50dnote : no need for visited array coz it is memtioned in question that there is no test case in which cycle is present 
*/

 
// code :- 
class Solution {   
  
private:
    // Fun.2:  to create AdjList
    void createAdjList(vector<vector<int>> &richer, unordered_map<int,list<int>> &AdjList){
        
        for(int i=0; i < richer.size(); i++){
            int node1 = richer[i][0];
            // note : node2's block is anyways going to be created, so if node1's block doesnt exist, create it
            if(AdjList.find(node1) == AdjList.end())
                AdjList[node1];
            int node2 = richer[i][1];
            AdjList[node2].push_back(node1); // directed graph here this means node1 is richer then node2
        }
    }

    // Fun.3 : to go till depth and find 'LeastQuietNode' for a node 'src'
    int DFS(unordered_map<int,list<int>> &AdjList, vector<int> &quiet, vector<int> &nodeToAnsMap, int src){
        

        int leastQuiet = src;
        for(int neigh:AdjList[src]){
            // calculate the ans for 'neigh' node
            int tempLeastQuiet;
            if(nodeToAnsMap[neigh] == -1)
                tempLeastQuiet = DFS(AdjList, quiet, nodeToAnsMap, neigh);
            
            // already prv calculated ans for 'neigh' node
            else tempLeastQuiet = nodeToAnsMap[neigh];
            
            if(quiet[leastQuiet] > quiet[tempLeastQuiet])
                leastQuiet = tempLeastQuiet;
        }

        nodeToAnsMap[src] = leastQuiet;
        return nodeToAnsMap[src];
    }

public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int> quiet)    
    {

        // step 1 : create adj list, such that u->v means v is more welthier then u 
        unordered_map<int,list<int>> AdjList;
        createAdjList(richer, AdjList);

        int V = quiet.size(); // imp
        
        vector<int> ans;

        // step 1.2 : create a map/vector to store the ans (for memoization purpose) index = node, value = ans for that node
        vector<int> nodeToAnsMap(V,-1); // -1 means the ans is not calculated yet (for ith node)

        // step 2 : for the nodes traverse till their depths to find out the ans 
        for( int i = 0; i < V; i++ ){  
            
            // if ans for a node is already calculated, then store it as it is 
            if(nodeToAnsMap[i] != -1)
                ans.push_back(nodeToAnsMap[i]);
            // if not calculated, then call DFS and calculate it 
            else{
                int ansFori = DFS(AdjList, quiet, nodeToAnsMap, i);
                ans.push_back(ansFori);
            }
        }

        return ans;
    }
};
