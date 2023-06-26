/* ✔️⭐ Approach 2 (BFS from desti '0' cells to '1' cells)

        explanation :- As we saw in the prv approach, of BFS if we go on from each cell to finding nearest neigh with '0' data in its cell then it will take a lot of time approx equal to O((n*m)^2), so to improve this we can modify this approach 1 futher, what we can do is rather then applying BFS from src '1' cells to desti '0' cells, we can apply BFS from '0' (desti) to src '1' and this way since we are appling BFS we can find the shortest distances.

        T : o(n*m)
        S : O(n*m) 

        ☑️solved at leetcode : https://leetcode.com/problems/01-matrix/description/

*/

class Solution {
    
private:
    class Triple{ // to store row, col, dist together
        public:
            int row, col, dist;
            Triple(int row,int col, int dist){
                this -> row = row;
                this -> col = col;
                this -> dist = dist;
            }
    };
    
    bool isCoordinateInRange(vector<vector<int>> &mat, int row, int col){
        int rowSize = mat.size();
        int colSize = mat[0].size();
        if( (row >= 0 && row < rowSize) && (col < colSize && col >= 0) )
            return true;
        return false;
    }

public:
    // main 
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        
        int rowSize = mat.size();
        int colSize = mat[0].size();

        // BFS 
        // in queue we need to store coordinates as well as curr distace travelled , then in q push all the '0' cells coordinates with starting distance = 0 
        
        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false)); 
        queue<Triple*> q;
        for(int row=0; row < rowSize; row++)
            for(int col=0; col < colSize; col++)
                if(mat[row][col] == 0){
                    q.push(new Triple(row, col, 0));
                    visited[row][col] = true;
                }
        
        // now to store all the min distance we need a 2d matrix 'ans', also we need to maintain the visited cells (so that we do not get trapped into inifinite loop)
        vector<vector<int>> ans(rowSize, vector<int>(colSize, INT_MAX)); // initially all dist = infinity

        while(!q.empty()){

            int frontRow = q.front() -> row;
            int frontCol = q.front() -> col;
            int frontDist = q.front() -> dist;
            q.pop();

            ans[frontRow][frontCol] = frontDist; // since we reached a cell 'frontCell' so by default BFS takes us via shortest path (least edge) to a desti, so store this into ans

            // lets explore all 4 neigh of frontCell (l,r,u,d)
            vector<int> deltaRow = {0, 0, -1, +1};
            vector<int> deltaCol = {-1, +1, 0, 0};
            
            for(int i=0; i < 4; i++){

                int row = frontRow + deltaRow[i];
                int col = frontCol + deltaCol[i];

                // if neigh is in range and not visited already, then store it into the q, and store the 'frontDist + 1' for this 'neigh' into 'ans'
                if( isCoordinateInRange(mat, row, col) && !visited[row][col] ){
                    q.push(new Triple(row,col, frontDist + 1 ));
                    ans[row][col] = frontDist + 1;
                    visited[row][col] = true;
                }
            }
        }

        return ans;
        
    }
};
