/* [fine but⚠️TLE] Approach - 1 : Simple DFS approach 

        explanation : - here what we do is we will start from src, and go to the depth of its every neighbour, and whenever we reached the destination, we check did we reached within k stops if yes then maybe we can update the ans if needed, else we cant update, so simply return, in this way we can find the minPrice needed to reach desti within k stops


        T : O(E+V) - for recursion + creating AdjList (sometimes in big TC DFS takes much more time then BFS) 
        S : O(E+V) - for AdjList, visited array

        ☑️TLE at leetcode : https://leetcode.com/problems/cheapest-flights-within-k-stops/description/

*/
/*
class Solution {
    
private:
    void createAdjList(vector<vector<int>> &flights, unordered_map<int,list<pair<int,int>>> &AdjList){
        for(int i=0; i < flights.size(); i++){
            int node1 = flights[i][0];
            int node2 = flights[i][1];
            int weight = flights[i][2];
            AdjList[node1].push_back({node2,weight}); // directed weighted graph
        }
    }

    // fun.3 
    void DFS(unordered_map<int,list<pair<int,int>>> &AdjList, vector<bool> &visited, int &ans, int &k, int currPrice, int stopsCovered, int &desti, int src){

        // if we reached the desti, then check if we reached destination within k stops, if yes then update the ans (if ans is larger),
        if(src == desti){
            if(stopsCovered - 2 <= k) // we sub -2 coz we are not to include the src and desti 
                ans = min(ans, currPrice);
            return;
        }

        // visit the src, and for all the unvisited neigh of the src, call dfs
        visited[src] = true;
        for(auto neighPair:AdjList[src]){
            int neigh = neighPair.first;
            int price = neighPair.second; // this is the price to reach the currNode via its parent current src
            if(!visited[neigh]){
                DFS(AdjList, visited, ans, k, currPrice + price, stopsCovered + 1, desti, neigh); // neigh is the new src
            }
        }

        // after all the neigh of node 'src' are explored, then unvisit it 
        visited[src] = false;
    }


    
public:
    // main function 
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int desti, int k) {
        
        // create a adjlist, then we need to keep track of the 'stops covered till now' as well the dist or prices coverted till now 
        unordered_map<int,list<pair<int,int>>> AdjList;
        createAdjList(flights, AdjList);

        int currPrice = 0, stopsCovered = 1; // initially we have already covered src 
        vector<bool> visited(n,false);

        // now lets apply dfs
        int ans = INT_MAX; // tor return at the end  - we need to minimize the ans(price)
        DFS(AdjList, visited, ans, k ,currPrice, stopsCovered, desti, src);

        // if no path exists within k stops then return -1, else return the ans 
        if(ans == INT_MAX) return -1;
        return ans;
    }
};

*/