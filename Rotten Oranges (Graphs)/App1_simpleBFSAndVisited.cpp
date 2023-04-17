
// ✔️(Solved) - Rotten Oranges - 1 Approach (simple BFS with size + visited)

//leetcode link : https://leetcode.com/problems/rotting-oranges/description/
//gfg link : https://practice.geeksforgeeks.org/problems/rotten-oranges2536/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article

/*✔️⭐Approach - 1 (BFS + visited copy )

            explanation :- store all the rotten oranges coordinates into this, queue , now apply BFS level wise (using size) so that we can find the number of levels (i.e time), now for every rotten orange it can rot its neighbours in 4 directions (left right up down) so if th neigh is not already rotten, then make sure to rote its coodinates into the queue. make sure to create a 'visited' copy of the original grid, and make changes in this copy rather then original grid

            T : O(n*m)
            S : O(n*m)

*/

// code - 
class Solution {
    
private:
    bool isCoordiUnrotten(vector<vector<int>> &visited, int row, int col){
        // return true, when the cell (row,col) is in range of grid, and also has data as 1 (i.e unrotten or safe orange)
        int rowSize = visited.size();
        int colSize = visited[0].size();

        if( (row < rowSize && row >= 0) && (col < colSize && col >= 0) && visited[row][col] == 1) 
            return true;

        return false; // when either cell is not in range, or cell already has a unrotten orange present in it 
    }
public:
    int orangesRotting(vector<vector<int>>& grid) {

        int rowSize = grid.size();
        int colSize = grid[0].size();

        // lets create a copy of original grid, and also push the rotten oranges coordinates into q 
        queue<pair<int,int>> q;
        vector<vector<int>> visited(rowSize, vector<int>(colSize)); 
        for(int i=0; i < rowSize; i++){
            for(int j=0; j < colSize; j++){
                visited[i][j] = grid[i][j];
                if(grid[i][j] == 2) // rotten
                    q.push({i,j}); 
            }
        }

        // BFS 
        int time = -1; 
        while(!q.empty()){

            int size = q.size();
            for(int i=0; i < size; i++){
                // fetch the front orange, and delete it from the queue.
                pair<int,int> frontCoordi = q.front();
                q.pop();

                int frontRow = frontCoordi.first;
                int frontCol = frontCoordi.second;

                // left neigh
                int row = frontRow, col = frontCol - 1;
                if(isCoordiUnrotten(visited, row, col)){  // only rotten an orange if it is not empty and in range (val=1)
                    
                    // rotten the neigh orange
                    visited[row][col] = 2;
                    q.push({row,col});
                }

                // right neigh
                row = frontRow, col = frontCol + 1;
                if(isCoordiUnrotten(visited, row, col)){  // only rotten an orange if it is not empty and in range (val=1)
                    
                    // rotten the neigh orange
                    visited[row][col] = 2;
                    q.push({row,col});
                }

                // up neigh
                row = frontRow-1, col = frontCol; 
                if(isCoordiUnrotten(visited, row, col)){  // only rotten an orange if it is not empty and in range (val=1)
                    
                    // rotten the neigh orange
                    visited[row][col] = 2;
                    q.push({row,col});
                }

                // down neigh
                row = frontRow + 1, col = frontCol;
                if(isCoordiUnrotten(visited, row, col)){  // only rotten an orange if it is not empty and in range (val=1)
                    
                    // rotten the neigh orange
                    visited[row][col] = 2;
                    q.push({row,col});
                }

            }
            time++;
        }

        // ones the queue is empty, check if atleast 1 cell is safe orange (val=1) then return -1, all oranges can not be rotten
        bool rottenOrgFound = false;
        for(int row=0; row < rowSize; row++){
            for(int col=0; col < colSize; col++){
                if(visited[row][col] == 1) 
                    return -1;
                if(visited[row][col] == 2)
                    rottenOrgFound = true;
            }
        }

        // if reached here means there is no safe orange(unrotten orange val=1),means there can be either rotten (val=2) or empty(val=0) oranges in the bucket, so if there are rotten oranges, then return the time, else if no  rotten orange, then return 0 (coz all are empty oranges) so no time taken
        if(rottenOrgFound == true) return time;
        else return 0;

        
    }
};
