// ☑️solved at leetcode : https://leetcode.com/problems/shortest-path-in-binary-matrix/

class Solution {
    /*✔️⭐ Approach - 1 (BFS + visited)

        explanation : there are few cond that we need to take care of       
                            i) we can move only on '0' data cells of grid
                            ii) path should be shortest
                            iii) there are 8 directions in which we can move (use deltaRow and deltaCol with 8 coordinates for this)

            So from the above conditions we observe that BFS is the algo that by default finds the shortest path itself

            ✅T : O(E+V)
            ✅S : O(E+V)
 
    */
private:
    bool isSafeToMove(vector<vector<int>> &grid, vector<vector<bool>> &visited, int row, int col){
        int rowSize = grid.size();
        int colSize = grid[0].size();
        // all conditions verification
        if( (row >= 0 && row < rowSize) && (col >= 0 && col < colSize) && !visited[row][col] && grid[row][col] == 0)
            return true;
        return false;
    }

public:
    // main
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {

        // exception case - if src is 1, cant move further
        if(grid[0][0] == 1) return -1;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false)); // so that we never come to the same cell again 
        // mark the 1 nodes as visited coz we can not visit them anyways
        for(int i=0; i < rowSize; i++)
            for(int j=0; j < colSize; j++)
                if(grid[i][j] == 1)
                    visited[i][j] = true;
        
        // in bfs queue we will be storing cell coordinates and curr path length
        queue< pair<pair<int,int>,int>> q;   // q((cell coordi), currPathLen)
        q.push({{0,0},1});
        visited[0][0] = true;

        while(!q.empty()){

            pair<pair<int,int>,int> front = q.front();
            int frontRow = front.first.first;
            int frontCol = front.first.second;
            int currLen = front.second;
            q.pop();

            // if we reached desti, return currLen (this is shortest len)
            if(frontRow == rowSize - 1 && frontCol == colSize - 1)
                return currLen;

            // else explore all the unvisited neigh out of 8 cells, and push unvisited ones into q 
            vector<int> deltaRow = {0, 0, -1, +1, -1, -1, +1, +1};
            vector<int> deltaCol = {-1, +1, 0, 0, -1, +1, -1, +1}; 

            for(int i=0; i < deltaRow.size(); i++){
                int row = frontRow + deltaRow[i];
                int col = frontCol + deltaCol[i];
                if(isSafeToMove(grid, visited, row, col)){ // push neigh into q if (it is in range of grid, and is not visited, and dos'nt have val 1)
                    q.push( { {row,col}, currLen + 1} );
                    visited[row][col] = true;
                }
            }
        }
        
        return -1; // no way to reach desti

        
    }
};
