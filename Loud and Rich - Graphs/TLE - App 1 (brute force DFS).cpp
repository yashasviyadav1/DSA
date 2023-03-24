
// 851. Loud And Rich 
// ☑️leetcode link : https://leetcode.com/problems/loud-and-rich/description/

// ⚠️[TLE] Approach - 1 (bruteforce DFS)
// T : O(V+E)^2
// S : O(V+E)

 // code 

class Solution { 
    
private:
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

    void DFS(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, vector<int> &quiet, int &leastQuietNode, int src){
        visited[src] = true;

        for(int neigh:AdjList[src]){
            if(!visited[neigh])
                DFS(AdjList, visited, quiet, leastQuietNode, neigh);
        }

        // if we found a new quieter node reachable from 'i' then update the leastQuietNode
        if(quiet[src] < quiet[leastQuietNode])
            leastQuietNode = src;
        visited[src] = false;
    }

public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int> quiet)    
    {
        
        // step 1 : create adj list, such that u->v means v is more welthier then u 
        unordered_map<int,list<int>> AdjList;
        createAdjList(richer, AdjList);

        int V = quiet.size(); // imp
        
        vector<bool> visited(V, false);
        vector<int> ans;

        // step 2 : for the nodes traverse till their depths to find out the ans 
        for(int i = 0; i < V; i++ ){  
            
            int leastQuietNode = i; // initially 
            DFS(AdjList, visited, quiet, leastQuietNode, i);
            ans.push_back(leastQuietNode);
            cout << "working : ";
            cout << "least quiet node : " << leastQuietNode << endl;
        }

        return ans;
    }
};
