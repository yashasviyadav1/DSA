#include<iostream>
#include<list>
#include<vector>
#include<stack>
#include<utility>
#include<unordered_map>
using namespace std;

/*(✔️)

    Question :- write a class Graph for a weighted, acyclic directed graph and then insert nodes into it, also write a method 
              inside this class , method name = shrtDistsFromSrc() to find the shortest distances of all the nodes from the given 'source' node
              and at last print all the shortes distances stored in vector<int> 'dist' 

*/

// lets create a weighted weighted graph class 
class Graph{

    public: 
        unordered_map<int,list<pair<int,int>>> AdjList;

    // method to insert edge from 'node1'  to 'node2', with specified weight
    void insertEdges(int node1, int node2, int weight){
        AdjList[node1].push_back(make_pair(node2, weight)); // directed graph
    }

    // method to print the AdjList of the Weightes directed graph 
    void printAdj(){
        for(auto i:AdjList){
            cout << i.first << " -> ";
            for(auto neighPair:i.second){
                cout << neighPair.first << " "; // here we, printing only node's data, not the weight
            } 
            cout << endl;
        }
    }

    // method to find the topological order of the given directed acyclic graph using DFS
    void topoOrderFinder(vector<bool> &visited, stack<int> &stk, int V, int src){

        visited[src] = true;

        // explore all the neighbours, and for the unvisited ones, call this fun
        for(auto neighPair:AdjList[src]){
            // note : 1st ele of pair is the neigh , and second is the weight between src and neigh
            if(!visited[neighPair.first]){
                topoOrderFinder( visited, stk, V, neighPair.first);
            }
        }

        // when a src's all childs are explored, and we are returning then store this src into the stk (note : do not unvisit 'src' other wise topoOrder will be wrong)
        stk.push(src);
    }

    // method to find all the shortest distances from the 'src' node to all other nodes
    void shrtDistsFromSrc(stack<int> &topoStk, vector<int> &dist, int src){

        // as the src's distance from itself is always 0
        dist[src] = 0;

        // loop the process while topoStk is non empty , fetch the top, pop it
        while(!topoStk.empty()){

            int topNode = topoStk.top();
            topoStk.pop();

            // now if the topNodes distance from 'src' is infinity then skip iteration
            if(dist[topNode] == INT_MAX) continue; 

            // else, explore all the nodes to which we can move from 'topNode' and if this path from src to reach 'neigh' is shorter then what is already stored in the distance[neigh] then update this distance, else neglict 
            for(auto neighPair:AdjList[topNode]){

                int neigh = neighPair.first;
                int weight = neighPair.second;

                // VIMP. line : lets say we have node ( 1 -> 2 ) and in the distance array if the prv path to reach 2 from src was 8, but the new path to reach 2 from 'src' via topNode is 3 then 3 < 8 so update the distance[2] = 3
                if((dist[topNode] + weight) < dist[neigh])
                    dist[neigh] = dist[topNode] + weight;

            }
        }

    }
};

int main(){

    cout << "- - - - - - - - - - - - " << endl;

    // creating a graph 
    
    int V = 6; // verticies

    Graph g;
    g.insertEdges(0,1,5);
    g.insertEdges(0,2,3);
    g.insertEdges(1,2,2);
    g.insertEdges(1,3,6);
    g.insertEdges(2,3,7);
    g.insertEdges(2,4,4);
    g.insertEdges(2,5,2);
    g.insertEdges(3,4,-1);
    g.insertEdges(4,5,-2);

    // printing AdjList of the graph 
    g.printAdj();


    // so for a topoorder we need a 'visited' and a 'stack', to find it using DFS
    stack<int> topoStk;
    vector<bool> visited(V,false);
    int src = 0;
    g.topoOrderFinder(visited, topoStk ,V, src);

    // now our topoSort is stored in stack, lets print it 
    /* cout << "Topo-order : ";
        while(!topoStk.empty()){
            cout << topoStk.top() << " "; 
            topoStk.pop();
        } cout << endl;
    */
    
    //now we have topoorder, so lets find the all node's shortest pair, from 'source' node and store all the shortest distances into 'dist' vector
    vector<int> dist(V,INT_MAX); // initialize all distances from infinity
    int source = 1;
    g.shrtDistsFromSrc(topoStk, dist, source);

    //lets print the shortest distances
    cout << "shortest distances : ";
    for(int i=0; i < dist.size(); i++){
        cout << dist[i] << " ";
    }cout << endl;
    
    // output : 2147483647 0 2 6 5 3 ☑️

    cout << "- - - - - - - - - - - - " << endl;

}