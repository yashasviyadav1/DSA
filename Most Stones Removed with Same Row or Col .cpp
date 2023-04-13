//(Solved) - Most Stones Removed with same row or col - 1 approach 
//☑️solved at leetcode : https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/


/* ✔️⭐Approach - 1 (simple DFS)

        explanation : see lets say we are standing at stone with coordinates (0,0) now if we go till the depth of (0,0) then the maximum number of stones that can be removed will be equal to number of stones that comes while traversing till the depth of origin, so apply a DFS , and find the number of stones that can never be removed, ones we have it subtract this from total stones,
        
            (max no of stones that can be removed = Total no of stones - no of stones we canot remove )

            if graph is like   for TC1 i.e  stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]], where the verticies of graph are indicies of stones 

                  3-----5
                  |     |
            1-----------4
            |     |
            0-----2    

            so here if we apply DFS from 0 which will go like 0 -> 1 -> 4 -> 5 -> 3 -> 2
            so this means that other then 0 all the nodes can be removed some way or other, so when the DFS ends we increment the 'unRemovableNodes' count by 1, and we find another unvisited nodes, and loop this process , till all nodes are visited, and at last we return 'removableNodes = total nodes - unremovable nodes'
            i.e ans = 6 - 1 => 5☑️

        T : O((E+V)^2)
        ✅S : O(E+V)

        ☑️solved at leetcode : https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/

*/

   
class Solution {
private:
    void DFS(unordered_map<int,list<int>> &AdjList, unordered_set<int> &visited, int srcStone){
        
        visited.insert(srcStone);

        for(int neigh:AdjList[srcStone])
            if(visited.count(neigh) == 0) // if neigh is not visited, call DFS for it
                DFS(AdjList, visited, neigh);
    }
public:
    // main 
    int removeStones(vector<vector<int>>& stones) {

        // since we can not store the coordinate pair into the unordered map, so we can create this map by simply using 'index' of the coordinate rather then the coordinate pair itself , and then we can connect every stone with the other stones that share same row or col 
        unordered_map<int,list<int>> AdjList;
        for(int i=0; i < stones.size()-1; i++)
            for(int j=i+1; j < stones.size(); j++)
                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]){//if 2 stones share same row OR same col, connect them 
                    AdjList[i].push_back(j);
                    AdjList[j].push_back(i);
                }

        // now we also need to maintain the visited nodes during DFS
        unordered_set<int> visited;

        // now lets apply DFS for only the unvisited Stones
        // note : if a node if univisted (means we found a node that can not be removed)
        int unRemovableStones = 0;
        for(int i=0; i < stones.size(); i++){
            if(visited.count(i) == 0){
                DFS(AdjList, visited, i);
                unRemovableStones++; // another stone found that can not be removed
            }
        }
        
        int maxRemovableStones = stones.size() - unRemovableStones;

        return maxRemovableStones; 
    }
};

