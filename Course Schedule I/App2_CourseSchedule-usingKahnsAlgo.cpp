/* ✔️⭐Approach - 2 (using Kahn's Algo to find Topo Sort Order)
         
         ✅T : O(E+V) 
         ✅S : O(E+V) - for queue and AdjList (no visited vector used)
         
    ☑️solved at leetcode : https://leetcode.com/problems/course-schedule


*/

class Solution {
    
private:
    // Fun.2 : to create Adj List from given edges 
    void createAdjList(vector<vector<int>> &prerequisites, unordered_map<int,list<int>> &AdjList){
        for(int i=0; i < prerequisites.size(); i++){
            int node1 = prerequisites[i][0];
            int node2 = prerequisites[i][1];

            AdjList[node1].push_back(node2); // coz directed graph
        }
    }
public:
    // Main function
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        // step 1: create a AdjList 
        unordered_map<int,list<int>> AdjList;
        createAdjList(prerequisites, AdjList);

        // step 2 : create a vector<int> 'indegree' and initially set all indegrees of all the nodes as 0
        vector<int> indegree(numCourses,0);
        for(int i=0; i < AdjList.size(); i++)
            for(auto neigh:AdjList[i])
                indegree[neigh]++;
        

        // step 3 : create a queue 'q' then traverse the inorder vector insert all the nodes with indegree 0 into the queue 
        queue<int> q;
        for(int i=0; i<indegree.size(); i++)
            if(!indegree[i])
                q.push(i);
        
        vector<int> topoOrder;
        // step 4 : do BFS using q
        while(!q.empty()){
            
            // fetch the front node and pop it, also save it into vector 'topoOrder'
            int front = q.front();
            q.pop();
            topoOrder.push_back(front);

            // now explore all the neighbours of front node, and decrement their indegrees of neighbours by 1, and if a neighbours indegree becomes 0, then push it into the q
            for(int neigh:AdjList[front]){
                indegree[neigh]--;
                if(indegree[neigh] == 0)
                    q.push(neigh);
            }
        }

        // if the topoOrder is not of length == number of verticies (that means graph is cyclic) so means we can not complete all the courses , return false
        if(topoOrder.size() != numCourses) return false;

        // else no cycle found , return true 
        return true;
    }
};