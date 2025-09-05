#include<algorithm>

//CodeStudio Link : https://www.codingninjas.com/codestudio/problems/minimum-spanning-tree_631769?topList=love-babbar-dsa-sheet-problems&leftPanelTab=0&utm_source=youtube&utm_medium=affiliate&utm_campaign=Lovebabbar

/*⭐✔️ Min Spanning Tree using 'KRUSKAL's Algo' (using 'Union Find' (Disjoint sets))

    Approach :-

        for the Kruskal's Algo we need to use the Disjoint Sets Data Structure
   (i.e 'Find Parent' and 'Union Sets')

       📝 Disjoint Sets :-
            |
            |-> Find Ultimate Parent
            |
            |-> Find Union Set  (using rank and path compression for optimised
   Time Complexity)

        Disjoint Sets are used to :-
            |
            |-> to check if 2 verticies belong to same component or not (int T:O(1))
            |-> for cycle detection
            |-> KRUSKAL's Algo 

      📝  Kruskals Algo :- 
          step1 : for this we do not need any Adj List, all we need is edges 2d vector, with weights
          step2 : sort this edges vector or the basis of ascending weights
          step3 : now traverse this vector, and for every pair of edge present in the 'edges' vector
            step 3.1 : find the ultimate parents of both edges 
            step 3.2 : if(ulti parent of both edges are equal) then do not include this edge in minimum spanning tree
            step 3.3 : else if(both edges have different ultimate parents) then find 'Union Set' of these 2 different components and make them 1 . and make sure to add this edge into our minimum spanning tree
          step 4 : ones loop breaks, return the minSpanning Tree formed 


      note :- 

          lets say 2 components are :- 

              3(rank=1)   4  (rank=1)
             / \         / \
            1   2       5   6
           /
          0

            Here parent of 0 means the just above node of 0 i.e 1 and the ultimate parent means the topmost node i.e 3
            parent[0] = 1
            ultimateParent[0] = 3

            
    ✅T : O(ElogE) - sort edges + O(E+V) for finding the parent in worst case + O(1) 
    ✅S : O(E+V) 



*/
class cmp{
  public:
  bool operator()(vector<int> &edge1, vector<int> &edge2){
    return edge1[2] < edge2[2]; // asc on basic of weight 
  }
};

// fun.2
void makeSet(int V, vector<int> &parent, vector<int> &rank){

  for(int i=0; i < V; i++){
    parent[i] = i;
    rank[i] = 0;
  }
}

// fun.4 : this will find and return the ultimate parent of a vertex (with functionality of path compression to reduce time)
int findParent(vector<int> &parent, int node){

  // base case - if we are already on the ultimate parent (node with parent equals to itself), thne 'node' is our ultimate parent
  if(parent[node] == node) return node;

  parent[node] = findParent(parent, parent[node]); // compresss the path while returning from the top to bottom
  return parent[node];
}

// fun.3 : if are part of diff components, then this fun will perform union of the 2 components and make them 1
void UnionSet(int ultiParentOfU, int ultiParentOfV, vector<int> &parent, vector<int> &rank){

  // if comp1 is heavier then comp2 (rank[compU] > rank[compV]) then add compV will be attached to compU 
  if(rank[ultiParentOfU] > rank[ultiParentOfV])
    parent[ultiParentOfV] = ultiParentOfU;
  
  // if comp2 is heavier then compU gets attached to compV
  else if(rank[ultiParentOfV] > rank[ultiParentOfU])
    parent[ultiParentOfU] = ultiParentOfV;

  // when both components are of equal ranks, then attach any 1 to other, and increment the main components rank by 1
  else if(rank[ultiParentOfU] == rank[ultiParentOfV]){
    parent[ultiParentOfV] = ultiParentOfU;
    rank[ultiParentOfU]++;
  }
  
}

// main fun
int minimumSpanningTree(vector<vector<int>>& edges, int V) // V is number of verticies
{
  //edges(u,v,weight)
  // for kruskals algo we do not need AdjList, we only need edges sorted on the basis of the weights
  sort(edges.begin(), edges.end(), cmp());

  // kruskals' algo is implemented using Union Find (Disjoint Sets) so lets create and initialize those needed D.S
  vector<int> parent(V);
  vector<int> rank(V); 
  makeSet(V, parent, rank);

  // now we need to traverse this sorted edges vector
  int MSTweight = 0;
  for(int i=0; i < edges.size(); i++){

    // fetch the 2 verticies, with weight
    int u = edges[i][0];
    int v = edges[i][1];
    int weight = edges[i][2];

    //find the ultimate parents of u and v 
    int ultiParentOfU = findParent(parent,u);
    int ultiParentOfV = findParent(parent,v); 

    // now if the 2 verticies have same ultimate parent (means u and v are part of same component), then we do not need to include it into the min Spanning Tree
    if(ultiParentOfU == ultiParentOfV)
      continue;
    
    // if both are part of diff comp (i.e both have diff ultimate parents ), then perform union on both verticies (and component) and add them to the MST
    else{
      UnionSet(ultiParentOfU,ultiParentOfV,parent,rank);
      MSTweight += weight;
    }
  }

  return MSTweight;
    
}
