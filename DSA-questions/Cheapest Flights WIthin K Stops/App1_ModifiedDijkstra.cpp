/* ✔️⭐Approach - 2 : Simple BFS (modified Dijkstra for the k constraint)

        explanation : -  we can not implement direct dijkstra algo here coz it finds us the min Price it takes to reach every node in a graph, but here we need to find th emin price path within k stops, so in simple dijkstra (which keeps 'minPrice', 'node' in queue) so here we need a queue  which keeps 1 extra thing i.e 'stops' which is the number of stops it took us to reach a 'node' via particular 'price', so for that we need a 'triple' which store these 3 things, so lets create a class for that

        ✅T : O(E+V)  
        ✅S : O(E+V) 

        ☑️solved at leetcode : https://leetcode.com/problems/cheapest-flights-within-k-stops/

*/

/* // Code 

class Solution {
    

    // coz we need to store 3 things together 'node' with 'price' and 'stops' we took to reach node via particular path
    class triple{
        public:
            int node;
            int price;
            int stops;
            triple(int node, int price, int stops){ // constructor to initialize 
                this -> node = node;
                this -> price = price;
                this -> stops = stops;
            }
    };

private:

    // fun.2
    void createAdjList(vector<vector<int>> &flights, unordered_map<int,list<pair<int,int>>> &AdjList){
        for(int i=0; i < flights.size(); i++){
            int node1 = flights[i][0];
            int node2 = flights[i][1];
            int weight = flights[i][2];
            AdjList[node1].push_back({node2,weight}); // directed weighted graph
        }
    }

    // fun.3 - in this fun we will implement the dijkstras algo but in a modified way in order to find the min Price path within k stops
    void BFSDijkModified(unordered_map<int,list<pair<int,int>>> &AdjList, vector<int> &minPrice, int k, int src){

        minPrice[src] = 0; // to reach src from src will cost 0 

        // we can not implement simple dijkstra (which keeps minPrice, node in queue) so here we need a queue  which keeps 1 extra thing i.e 'stops' which is the number of stops it took us to reach a 'node' via particular 'price', so for that we need a 'triple' which store these 3 things, so lets create a class for that
        queue<triple*> q;
        q.push(new triple(src,0,0)); // for src 

        while(!q.empty()){

            triple* frontTrip = q.front();
            q.pop();

            int frontNode = frontTrip -> node;
            int frontPrice = frontTrip -> price;
            int stops = frontTrip -> stops;

            // IMP. when we reached a node 'front' and it tooks us more then k stops to reach here, that means we can not move further, so skip finding min price for this node (note : even if front is desti, then also its min path must be stored prevliously in the 'minPrice' array )
            if( stops > k ) continue; 

            // now lets explore all neigh of front
            for(auto neighPair:AdjList[frontNode]){
                int neigh = neighPair.first;
                int weight = neighPair.second; // this is the price of traveling between the 'front' & 'neigh' node, basicall the weight of edge 

                // now when found a new min cost path withing k stops to reach 'neigh' via 'frontNode' then update it [note : do not use the dijkstra's original logic, only use the price path 'with' which we reached front, and not the minPrice[front]]  
                if(frontPrice + weight < minPrice[neigh]){
                    minPrice[neigh] = frontPrice + weight;
                    q.push( new triple(neigh, minPrice[neigh], stops + 1) ); // push new triple in queue 
                } 
            } 
        }
        
    }

public:
    // main function 
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int desti, int k) {
        
        // create an adj list
        unordered_map<int,list<pair<int,int>>> AdjList;
        createAdjList(flights, AdjList);

        // we need to store the minPrice
        vector<int> minPrice(n,INT_MAX);

        // now we need to call 'BFSDijkModified' function that will find the within k stops a path with least price possible
        BFSDijkModified(AdjList, minPrice, k, src);

        // now we have all min prices, so lets find the minPrice to reach 'desti' and if its 'INTMAX' means we can not reach the desti within k stops
        if(minPrice[desti] == INT_MAX) return -1;
        return minPrice[desti];


    }
};

*/
