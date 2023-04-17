
// ✔️(Solved) - Rotten Oranges - 2nd Approach (modified BFS using 'DeltaArray' and queue{row,col,level})

//leetcode link : https://leetcode.com/problems/rotting-oranges/description/
//gfg link : https://practice.geeksforgeeks.org/problems/rotten-oranges2536/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article


/* ✔️⭐Approach - 1.1 (optimised BFS with 'deltaArray' for neigbbours & storing level of BFS into queue)

            explanation :- Firsly we will store rotten orange's coordinates into queue with their level's , now make sure to create a copy of the original grid, make changes into this copy grid (visited), now we know a rotten orange can rot its 4 neighbours, so rather then putting 4 conditions for 4 neighbours we can shorten the code by using the concept of 'deltaArray', now after then we fetch the front Rotten orange from the queue, then we will check for its 4 neighbours, and whenever we found a neigh orange to be safe (unrotten with val=1) we will rot  that and store this newly rotten orange into the queue, and repeat this untill our queue becoems empty. 

            T : O(n*m)
            S : O(n*m)

*/

// code 
/*
class Solution {
    
private:
    // to store (row,col,level of BFS), note : we could also have used pair(pair(int,int),int) i.e {{row,col},level}, but for clean code i prefer this 
    class Triple{
        public:
        int row,col,time; // this time is the level of queue
        Triple(int row, int col, int time){
            this->row = row;
            this->col = col;
            this->time = time;
        }
    };

    // this function returns true iff : the coordi (row,col) is not alredy rotten and are in range of grid
    bool isCoordiSafe(vector<vector<int>> &visited, int row, int col){
        int rowSize = visited.size();
        int colSize = visited[0].size();

        if( (row < rowSize && row >= 0) && (col < colSize && col >= 0) && visited[row][col] == 1) 
            return true;

        return false; // when either cell is not in range, or cell already has a unrotten orange present in it 
    }
public:
    // main func
    int orangesRotting(vector<vector<int>>& grid) {

        int rowSize = grid.size();
        int colSize = grid[0].size();

        // lets create a copy of original grid, and also push the rotten oranges coordinates into q with there time taken to get rot.(or their level of BFS)
        queue<Triple*> q; // q(row,col,level)

        vector<vector<int>> visited(rowSize, vector<int>(colSize)); 
        for(int row=0; row < rowSize; row++){
            for(int col=0; col < colSize; col++){
                visited[row][col] = grid[row][col];
                if(grid[row][col] == 2) // rotten orange found
                    q.push(new Triple(row,col,0)); // initially at level 0 (or time is 0 ) 
            }
        }

        // BFS - here i applied BFS optimally, by using 'deltaArrays' in place of 4 if conditions for 4 neighbours, and rather then apply BFS with size concept, i applied BFS by store level's into queue itself at each instance. 
        int maxTime = 0; 
        while(!q.empty()){
            
                // fetch the front orange, and delete it from the queue.
                Triple* frontCoordi = q.front();
                q.pop();

                int frontRow = frontCoordi -> row;
                int frontCol = frontCoordi -> col;
                int currTime = frontCoordi -> time; // or current level of BFS

                //update the max time taken till now 
                maxTime = max(maxTime, currTime);

                //we know every cell has 4 neigh, so to avoid the repeated work,lets create deltaRow,deltaCol
                vector<int> deltaRow = {0, 0, -1, +1};
                vector<int> deltaCol = {-1, +1, 0, 0};

                for(int i=0; i < deltaRow.size(); i++){
                    
                    // find neigh coordinates (left, right, up, down)
                    int row = frontRow + deltaRow[i];
                    int col = frontCol + deltaCol[i];
                    if(isCoordiSafe(visited, row, col)){ // if a neigh is unrotten them rot it, and save in queue
                        visited[row][col] = 2;
                        q.push(new Triple(row,col,currTime + 1)); // it would take 1 min to rot the neigh thats why added 1 to currTime
                    }
                }

        }
        // ones the queue is empty, check if atleast 1 cell is safe orange (val=1) then return -1, because this means all oranges could not be rotten
        bool rottenOrgFound = false;
        for(int row=0; row < rowSize; row++){
            for(int col=0; col < colSize; col++){
                if(visited[row][col] == 1) 
                    return -1;
            }
        }

        // reach here means our ans is saved in 'time' 
        return maxTime;

        
    }
};

*/