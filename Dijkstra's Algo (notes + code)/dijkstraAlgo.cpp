// Solved(✔️) - Dijkstra's Algorithm - 1 approach 

// ☑️solved at codeStudio : https://www.codingninjas.com/codestudio/problems/dijkstra-s-shortest-path_920469?leftPanelTab=0

//-----------------------------------------------------------------------------------
/*[✔️⭐⭐[App-1.1] more faster then prv App-1]
    
    Title = Dijkstra's Algo Using Set<pair(minDis to reach node ,node) >  

    explanation :- what we do here is we use a set(minDis to reach node,node) and using this every time we pop the front 
                    of this set, we will get the pair with least 'minDis'.
                    (we can also use minHeap instead of this), so every time we will follow a 2 step process after fetching the front 
                        step 1 -> Relaxation :- here if the minDis[front] + distance between neigh and front is lesser then the minDist[neigh] then we will update the minDist[neigh]
                                                and also insert this new pair for node -> 'neigh' into the set, make sure to delete the prv entry of the 'neigh' from the set if exists any

                        step 2 -> find the next node to do the same process (for this we will choose the node with the min Distance, which is not yet explored i.e present in the set)  

    note: .find() .insert() .erase() takes O(logN) times to perform because we are using 'ordered_set' not an UNordered_set

    ✅T : O(E*log*V) - traversing each edge takes E and inserting the verticies into set will take logV
    ✅S : O(E+V)

*/

/* // code 

// fun.2 
void createAdjList(vector<vector<int>> &vec, unordered_map<int,list<pair<int,int>>> &AdjList){

    for(int i=0; i < vec.size(); i++){
        int node1 = vec[i][0];
        int node2 = vec[i][1];
        int weight = vec[i][2];

        // undirected graph
        AdjList[node1].push_back({node2, weight});
        AdjList[node2].push_back({node1, weight});

    }
}

// fun.3 
void dijkstraMinDis(unordered_map<int,list<pair<int,int>>> &AdjList, set<pair<int,int>> &set, vector<int> &minDist, int src){

    // initially we can reach the src itself in 0 distance, and insert its pair{0,src} into the set also
    minDist[src] = 0;
    set.insert({0,src});

    // run a loop while set is non empty
    while(!set.empty()){

        // fetch the top node of set (the one with the minimum distance)
        pair<int,int> frontPair = *(set.begin()); 
        set.erase(set.begin()); // pop the front 

        int frontMinDis = frontPair.first;
        int frontNode = frontPair.second;

        // explore all the neighbours of this frontnode
        for(auto neighPair:AdjList[frontNode]){

            int neigh = neighPair.first;
            int weight = neighPair.second; // this weight is the 'distance from frontNode to neigh'
            
            // now update the min distance to reach the 'neigh' node if and only if the new path distance is smaller then the prv.
            if(minDist[frontNode] + weight < minDist[neigh]){
                
                // now after a node's distance to reach is updated, we need to update that 'neigh''s min distance in the set also, so for that (find if there already exist a node 'neigh' in the set, if yes then delete it) and then insert the new pair into the set
                auto prvEntry = set.find({minDist[neigh] ,neigh});
                if(prvEntry != set.end()){ // another entry for 'neigh' exists
                    set.erase(prvEntry);
                }

                // updation of minDist of 'neigh'
                minDist[neigh] = minDist[frontNode] + weight;

                // insertion of new pair in set
                set.insert({minDist[neigh],neigh});
            }
        }

    }
}

// main function
vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source) {

    // we need a 'AdjList', a 'minDist' (to return at the end), and a set<pair<int,int>> to store the {minDis to reach node, node}
    unordered_map<int,list<pair<int,int>>> AdjList;
    vector<int> minDist(vertices,INT_MAX); // initially all nodes can be reached only in inf distance 
    set<pair<int,int>> set; // order this on basis of the pair.first i.e min dist

    // create AdjList by fun.2
    createAdjList(vec, AdjList);

    // now to apply dijkstra call fun.3
    dijkstraMinDis(AdjList, set, minDist, source);

    return minDist;


    
}
*/

//---------------------------------------------------------------------------------------------

/* App-1 : ✔️⭐Dijkstra's Algo Using Set<pair(minDis to reach node ,node) >  

    explanation :- what we do here is we use a set(minDis to reach node,node) and using this every time we pop the front 
                    of this set, we will get the pair with least 'minDis'.
                    (we can also use minHeap instead of this), so every time we will follow a 2 step process after fetching the front 
                        step 1 -> Relaxation :- here if the minDis[front] + distance between neigh and front is lesser then the minDist[neigh] then we will update the minDist[neigh]
                                                and also insert this new pair for node -> 'neigh' into the set, make sure to delete the prv entry of the 'neigh' from the set if exists any

                        step 2 -> find the next node to do the same process (for this we will choose the node with the min Distance, which is not yet explored i.e present in the set)  

    note: since we are taking O(N) time to find the pair present in the set with 2nd element as 'neigh' so it takes O(n) time, rest .insert() .erase() takes O(logN) times to perform because we are using 'ordered_set' not an UNordered_set

    ✅T : O(E*log*V) - traversing each edge takes E and inserting the verticies into set will take logV
    ✅S : O(E+V)

*/
/* // code 

// fun.2 
void createAdjList(vector<vector<int>> &vec, unordered_map<int,list<pair<int,int>>> &AdjList){

    for(int i=0; i < vec.size(); i++){
        int node1 = vec[i][0];
        int node2 = vec[i][1];
        int weight = vec[i][2];

        // undirected graph
        AdjList[node1].push_back({node2, weight});
        AdjList[node2].push_back({node1, weight});

    }
}

// fun.3 
void dijkstraMinDis(unordered_map<int,list<pair<int,int>>> &AdjList, set<pair<int,int>> &set, vector<int> &minDist, int src){

    // initially we can reach the src itself in 0 distance, and insert its pair{0,src} into the set also
    minDist[src] = 0;
    set.insert({0,src});

    // run a loop while set is non empty
    while(!set.empty()){

        // fetch the top node of set (the one with the minimum distance)
        pair<int,int> frontPair = *(set.begin()); 
        set.erase(set.begin()); // pop the front 

        int frontMinDis = frontPair.first;
        int frontNode = frontPair.second;

        // explore all the neighbours of this frontnode
        for(auto neighPair:AdjList[frontNode]){

            int neigh = neighPair.first;
            int weight = neighPair.second; // this weight is the 'distance from frontNode to neigh'
            
            // now update the min distance to reach the 'neigh' node if and only if the new path distance is smaller then the prv.
            if(minDist[frontNode] + weight < minDist[neigh]){
                minDist[neigh] = minDist[frontNode] + weight;

                // now after a node's distance to reach is updated, we need to update that 'neigh''s min distance in the set also, so for that (find if there already exist a node 'neigh' in the set, if yes then delete it) and then insert the new pair into the set
                for(auto iter = set.begin(); iter != set.end() ;iter++){
                    if(iter -> second == neigh){
                        set.erase(iter);
                        break;
                    }
                }

                set.insert({minDist[neigh],neigh});
            }
        }

    }
}

// main function
vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source) {

    // we need a 'AdjList', a 'minDist' (to return at the end), and a set<pair<int,int>> to store the {minDis to reach node, node}
    unordered_map<int,list<pair<int,int>>> AdjList;
    vector<int> minDist(vertices,INT_MAX); // initially all nodes can be reached only in inf distance 
    set<pair<int,int>> set; // order this on basis of the pair.first i.e min dist

    // create AdjList by fun.2
    createAdjList(vec, AdjList);

    // now to apply dijkstra call fun.3
    dijkstraMinDis(AdjList, set, minDist, source);

    return minDist;


    
}
*/