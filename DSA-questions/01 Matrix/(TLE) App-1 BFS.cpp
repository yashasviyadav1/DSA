// TLE - 01 Matrix - 1st Approach   

/*⚠️TLE - Approach - 1 (simple BFS + deltaArr + visited)

     TLE at leetcode : https://leetcode.com/problems/01-matrix/description/
    
    // idea : for each '1' cell of the matrix, apply a BFS to find out closest neighbour with value 0

   T : O((E+V)^2)
   S : O(E+V)

*/

/*
class Solution {
    
private:
    class Triple{
        public:
            int row,col,dist;
            Triple(int row, int col, int dist){
                this -> row = row;
                this -> col = col;
                this -> dist = dist;
            }
    };
    bool areCoordiInRange(vector<vector<int>> &mat, int row, int col){
        int rowSize = mat.size();
        int colSize = mat[0].size();
        if( (row < rowSize && row >= 0) && (col < colSize && col >= 0) )
            return true;
        return false;
    }

    // BFS
    int minDistWithBFS(vector<vector<int>> &mat, int row, int col){
        
        int rowSize = mat.size();
        int colSize = mat[0].size();
        
        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false)); // to maintain visited cells

        queue<Triple*> q;
        q.push(new Triple(row,col,0)); // at start distance is 0
        visited[row][col] = true; 

        while(!q.empty()){

            // fetch front, and if front is 0, means shortest distant 0 cell found, return the dist
            int frontRow = q.front() -> row;
            int frontCol = q.front() -> col;
            int frontDist = q.front() -> dist;
            q.pop();

            if(mat[frontRow][frontCol] == 0)
                return frontDist;

            // if front is not the '0' cell, then push all neigh of 'frontCell' into, q and increment the dist by 1
            // l, r, u, d
            vector<int> deltaRow = {0, 0, -1, +1};
            vector<int> deltaCol = {-1, +1, 0, 0};

            for(int i=0; i < deltaRow.size(); i++){

                int row = frontRow + deltaRow[i];
                int col = frontCol + deltaCol[i];

                if(areCoordiInRange(mat,row,col) && !visited[row][col]){  // check : coordinates should be in range of matrix

                    // if neigh found with val=0, then return the 'frontDis + 1' do not search further 
                    if(mat[row][col] == 0) 
                        return frontDist + 1;

                    // if not 0, then push it into q, to search further
                    q.push(new Triple(row,col,frontDist + 1));
                    visited[row][col] = true; // this is imp so that we do not come to the same cell again and again.
                }
            }
        }

        // reached here means no cell found with val 0 in whole matrix
        return -1;
    }

public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        
        int rowSize = mat.size();
        int colSize = mat[0].size();

        vector<vector<int>> ans(rowSize, vector<int>(colSize, 0));// to store min distance 

        for(int row = 0; row < rowSize; row++)
            for(int col = 0; col < colSize; col++)
                if(mat[row][col] == 1){  //find min distance for cell with value 1
                    int minDist = minDistWithBFS(mat, row, col);
                    if(minDist == -1) // means there is no cell in matrix with value 0, so no need to search nearest neighbour for any other cell, return matrix
                        return ans;
                    ans[row][col] = minDist;// means a closest neigh with val 0 found 
                }
                
        return ans;
    }
};

*/