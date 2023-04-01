//✔️(Solved) - number of islands 
//☑️leetcode link : https://leetcode.com/problems/number-of-islands/description/

/* ✔️⭐Approach - 1 (Recursive DFS)

     idea : start dfs for a valid node that has not been visited yet 
            while going to its depth make sure to mark the path as visited, and ones its done, increment the 'islandsCount' means we found a valid island

        eg. grid is given 

            [1,1,1,1,0],
            [1,1,0,1,0],
            [1,1,0,0,0],
            [0,0,0,0,0]
        
        when row=0,col=0 lets do its DFS  (left right up down)
            c-0
        r-0  -> -> -> V
             |-> X    X    (x means return )
            
        so this path will be visited as true, and 'islandsCount == 1'
                        

    ✅ T : O(n*m) - for recursive stack
    ✅ S : O(n*m) - for visited matrix 
*/


class Solution {
private:
    // fun.3 
    bool isSafeToMove(vector<vector<char>> &grid, vector<vector<bool>> &visited, int row, int col){

        int rowSize = grid.size();
        int colSize = grid[0].size();

        if( (row >= 0 && row < rowSize) && (col >= 0 && col < colSize) && !visited[row][col] && grid[row][col] == '1')
            return true;
        return false;
    }
    // fun. : does a dfs traversal of src 'row,col' and visits the node it comes accross during the traversal
    void DFS(vector<vector<char>> &grid, vector<vector<bool>> &visited,  int row, int col){

        visited[row][col] = true;

        // go to left
        int newRow = row;
        int newCol = col-1;
        if(isSafeToMove(grid,visited,newRow,newCol))
            DFS(grid, visited, newRow, newCol);
        
        // right
        newRow = row;
        newCol = col+1;
        if(isSafeToMove(grid,visited,newRow,newCol))
            DFS(grid, visited, newRow, newCol);

        // up
        newRow = row-1;
        newCol = col;
        if(isSafeToMove(grid,visited,newRow,newCol))
            DFS(grid, visited, newRow, newCol);
        
        // down
        newRow = row+1;
        newCol = col;
        if(isSafeToMove(grid,visited,newRow,newCol))
            DFS(grid, visited, newRow, newCol);

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
                    DFS(grid, visited, row, col);
                    // ones all the depths of the 'row''col' are explored, increment the island count
                    islandsCount++;
                }
            }
        }
        return islandsCount;
    }
};
