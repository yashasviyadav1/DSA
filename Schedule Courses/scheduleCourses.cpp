
// Solved(✔️) - Schedule courses - 1 approach 

// ☑️solved at leetcode : https://leetcode.com/problems/course-schedule/description/

/* ⭐✔️Approach - 1 (using loop detection technique using DFS)
        
        note : we used vector<bool> instead of un_maps for visited and dfsvisited just to make this function optimal 

        explanation :- 
            given courses from (0 to numCourses-1) we assume the each course as node of a directed graph, and then we will make a adjList using that, and at alst use DFS to detect a loop in this graph, we have created, if there is a loop found in graph then that means all courses can not be complete so return false.  else if no loop exists then return true  

        coding steps : 
                    
            -> // fun.2 : function to create an AdjList from a 2d vector of edges

            ->// fun.3 : loop detection in directed graphs
                step 1 : visit the src node in both visited maps/vectors
                step 2 : explore all the neighbours of 'src' node and call dfs for unvisited neighbours  
                    step 3 : when a node if visited as well as dfsVisited, means loop found
                        step 3.1 : loop found, return true 
                    step 4 : call this fun. recursively for the non visited nodes 
                        step 4.1 : if loop found, return 'true'
                step 5 : when all the neighbours of src are explored, or a src has no neighbours, then unvisit the dfsVisited for that 'src' and return false (no loop found) 
                

            -> // Main function

                step 1 : lets create a adj list from the prerequisite vector , visited vector<bool> and vissitedDFS vector of bool
                step 2 : now lets call dfs for all components (use loop coz there can be some couses that doesnt exist in the prereq vector i.e they doesnt need any prereq couse to complete them), and lets detect loop
                        step 3 :  if loop found means  cant complete all courses
                step 4 : reached here means we can complete all the courses
    

        T : O(V + E) 
        S : O(V + E) for 2 vectors (visited) and for recursive call stack 
    */
    
class Solution {
public:
    
    // fun.2 : function to create an AdjList from a 2d vector of edges
    void createAdjList(vector<vector<int>> &prereq, unordered_map<int,list<int>> &AdjList){

        for(int i= 0; i<prereq.size(); i++){
            int node1 = prereq[i][0];
            int node2 = prereq[i][1];

            AdjList[node1].push_back(node2);
        }
    }

    // fun.3 : loop detection in directed graphs
    bool DFSLoopDetection(unordered_map<int,list<int>> &AdjList, vector<bool> &visited, vector<bool> &DFSvisited, int src){

        // visit the src node in both visited maps/vectors
        DFSvisited[src] = true;
        visited[src] = true;

        // explore all the neighbours of 'src' node and call dfs for unvisited neighbours  
        for(int neigh:AdjList[src]){
            // when a node if visited as well as dfsVisited, means loop found
            if(visited[neigh] && DFSvisited[neigh]){
                // loop found
                return true;
            }

            // call call recursively for the non visited nodes 
            else if(!visited[neigh]){
                int ans = DFSLoopDetection(AdjList, visited, DFSvisited, neigh);
                // if loop found 
                if(ans) return true;
            }
        }


        // when all the neighbours of src are explored, or a src has no neighbours, then unvisit the dfsVisited for that 'src' and return false (no loop found) 
        DFSvisited[src] = false;
        return false;
    }


    // Main function
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        // lets create a adj list from the prerequisite vector , visited vector<bool> and vissitedDFS vector of bool
        unordered_map<int,list<int>> AdjList;
        vector<bool> visited(numCourses, false);
        vector<bool> DFSvisited(numCourses, false);
        createAdjList(prerequisites, AdjList);

        // now lets call dfs for all components (use loop coz there can be some couses that doesnt exist in the prereq vector i.e they doesnt need any prereq couse to complete them), and lets detect loop
        for(int i = 0; i < numCourses; i++){
            if(!visited[i]){
                int loopFound = DFSLoopDetection(AdjList, visited, DFSvisited, i);
                if(loopFound) return false; // cant complete all courses
            }
        }

        // reached here means we can complete all the courses
        return true; 
        
    }
};