//✔️(Solved) - number of islands 
//☑️leetcode link : https://leetcode.com/problems/number-of-islands/description/

/* ✔️⭐Approach - 2 (iterative BFS)

     idea : find a valid land (non visited and non zero) then do a depth wise traversal of that land, and mark all its neighbours as visited, ones BFS for 'src' land is done, increment the islandsCount by 1, and find another valid land.

    ✅ T : O(n*m) - for queue 
    ✅ S : O(n*m) - for visited matrix 
*/

/*
class Solution {
private:
    // fun.3 : returns true if a cell (row,col) is valid neigh , else return false 
    bool isSafeNeigh(vector<vector<char>> &grid, vector<vector<bool>> &visited, int row, int col){

        // valid neigh : one with value as '1', non visited, in range of row and coloumns
        // invalid neigh : rest all are invalid cells
        int rowSize = grid.size();
        int colSize = grid[0].size();

        if( (row >= 0 && row < rowSize) && (col >= 0 && col < colSize) && !visited[row][col] && grid[row][col] == '1')
            return true;
        return false;
    }
    
    // simple BFS traversal 
    void BFS(vector<vector<char>> &grid, vector<vector<bool>> &visited, int srcRow, int srcCol){

        // for BFS we need queue(row,col)
        queue<pair<int,int>> q;     
        q.push({srcRow,srcCol});
        visited[srcRow][srcCol] = true;
        
        while(!q.empty()){

            int frontRow = q.front().first;
            int frontCol = q.front().second;
            q.pop();
            
            // visit and insert into q (all unvisited and non 0 neigh from its all 4 directions of 'front')
            // left Neighbour
            int neighRow = frontRow, neighCol = frontCol-1; 
            if(isSafeNeigh(grid,visited,neighRow,neighCol)){
                visited[neighRow][neighCol] = true;
                q.push({neighRow,neighCol});
            }

            // right Neighbour
            neighRow = frontRow, neighCol = frontCol+1; 
            if(isSafeNeigh(grid,visited,neighRow,neighCol)){
                visited[neighRow][neighCol] = true;
                q.push({neighRow,neighCol});
            }

            // upper Neighbour
            neighRow = frontRow-1, neighCol = frontCol; 
            if(isSafeNeigh(grid,visited,neighRow,neighCol)){
                visited[neighRow][neighCol] = true;
                q.push({neighRow,neighCol});
            }

            // below Neighbour
            neighRow = frontRow+1, neighCol = frontCol; 
            if(isSafeNeigh(grid,visited,neighRow,neighCol)){
                visited[neighRow][neighCol] = true;
                q.push({neighRow,neighCol});
            }
        }

        return;
    }
public:
    // main function
    int numIslands(vector<vector<char>>& grid) {

        int rowSize = grid.size();
        int colSize = grid[0].size();

        // we need to maintain the visited nodes 
        vector<vector<bool>> visited(rowSize, vector<bool>(colSize,false));

        // call solve for all the (non 0 && non visited nodes only)
        int islandsCount = 0;

        for(int row=0; row < rowSize; row++){
            for(int col=0; col < colSize; col++){
                if(!(visited[row][col]) && (grid[row][col] == '1') ){
                    BFS(grid, visited, row, col);
                    islandsCount++; // when src is completely breadth wise traversed,  increment the islandsCount 
                }
            }
        }
        return islandsCount;
    }
};

*/