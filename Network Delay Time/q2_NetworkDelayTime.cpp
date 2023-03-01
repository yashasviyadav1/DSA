
// Network Delay Time - tried 3 approaches (Dijkstra's Algo✔️ ,BFS❌, simple all nodes shortest finding algo❌)

/*✔️⭐ Approach - 3 (using Dijkstra's Algo)

        explanation :- using Dijkstra's Algo to find all the minTimeReq for a signal to reach every node, ones we have that stored in vector<int> 'minDist', then we will check if any node cant not be reached, then return -1, else return the max value of the 'minDist' vector

        ✅T : O(ELogV)
        ✅S : O(E+V)

    ☑️solved at leetcode : https://leetcode.com/problems/network-delay-time/description/

*/

/*

class Solution {
private:
    // fun.2 
    void createAdjList(vector<vector<int>> &edges, unordered_map<int,list<pair<int,int>>> &AdjList){

        for(int i=0; i < edges.size(); i++){

            int node1 = edges[i][0];
            int node2 = edges[i][1];
            int weight = edges[i][2];
            AdjList[node1].push_back({node2,weight});   // directed weighted graph 
        }
    }

    // fun.3
    void dijkstrasAlgo(unordered_map<int,list<pair<int,int>>> &AdjList, vector<int> &minDist, int src){

        // now we need to maintain a set<pair<int,int>> set(min dist to reach node, node) and insert src node with mindist 0 into it, also mark mindistance of src as 0 
        set<pair<int,int>> set;
        minDist[src] = 0;
        set.insert({0,src});

        // traverse while set is non empty
        while(!set.empty()){

            // fetch the top node of set, then remove it from the set as well
            auto frontPair = *(set.begin()); // * because .begin() given address of the bigning key
            set.erase(set.begin());

            int frontNode = frontPair.second;
            int frontMinDis = frontPair.first;

            // now we need to eplore all the neigh of the frontNode 
            for(auto neighPair:AdjList[frontNode]){

                // now do the relaxation step, (make sure if uou update a mindis for a node, then delete its prv entry if present in the set, and then insert the node with its new mindist)
                int neigh = neighPair.first;
                int weight = neighPair.second;

                if(minDist[frontNode] + weight < minDist[neigh]){

                    // serarching for prv entry 
                    auto prvEntry = set.find({minDist[neigh],neigh});
                    if(prvEntry != set.end()){ // entry found
                        set.erase(prvEntry);
                    }
                    
                    minDist[neigh] = minDist[frontNode] + weight;
                    set.insert({minDist[neigh],neigh}); // insert new entry for 'neigh'
                }
            }
        }


    }
public:
    // main function
    int networkDelayTime(vector<vector<int>>& times, int n, int src) {
        
        // for dijkstras algo, we need 'set(pair)' or 'minHp(pair)' (ordered on basis of min dis) 'minDist' vector, and a adjList
        unordered_map<int,list<pair<int,int>>> AdjList;
        vector<int> minDist(n+1,INT_MAX); // initially all the nodes are at inf distance
        minDist[0] = -999; // garbage value for not which is not present in the graph

        createAdjList(times, AdjList);

        dijkstrasAlgo(AdjList, minDist, src);

        // after we have all the minDistances in the vector, we will traverse it, and if we find a node with INF times, return -1, else return the node with max time req
        int minTimeDelay = 0;
        for(int i=0; i < minDist.size(); i++){
            if(minDist[i] == INT_MAX) return -1;
            minTimeDelay = max(minTimeDelay,minDist[i]);
        }

        return minTimeDelay;
    }
};

*/