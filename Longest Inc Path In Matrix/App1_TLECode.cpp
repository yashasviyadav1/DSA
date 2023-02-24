// purely bruteforce Approach - hits TLE at test case 135 of 138 

// leetcode link : https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/

/* ⚠️TLE[135 / 138 ]Approach - 1 (recursive backtracking - purely bruteforce)
            
            explanation :- for every node of the matrix, call a function that will explore all teh possible increasing path starting from that 'node' , at the end return the maximum lenght path 

        ⚠️T : O(N*(4^n))
           S : O(N)
*/

class Solution {
    
private:
    // Fun.3 
    bool isSafeToMove(vector<vector<int>> &matrix, vector<vector<bool>> &visited, int newRow, int newCol, int prv){

        int rowSize = matrix.size();
        int colSize = matrix[0].size();

        // when to return false 
        if( (newRow < 0 || newRow >= rowSize) || (newCol < 0 || newCol >= colSize) || visited[newRow][newCol] || matrix[newRow][newCol] <= prv)
            return false;

        return true;
    }

    // Fun.2
    void solveRec(vector<vector<int>> &matrix, vector<vector<bool>> &visited, int &ans, int currLen, int row, int col){

        ans = max(ans, currLen);
        visited[row][col] = true; // visit the curr cell

        int prv = matrix[row][col];

        // move left
        int newRow = row, newCol = col-1;
        if(isSafeToMove(matrix, visited, newRow, newCol, prv)){
            solveRec(matrix, visited, ans, currLen + 1, newRow, newCol)  ;
        }

        // move right
        newRow = row, newCol = col+1;
        if(isSafeToMove(matrix, visited, newRow, newCol, prv)){
            solveRec(matrix, visited, ans, currLen + 1, newRow, newCol);
        }

        // move up
        newRow = row - 1, newCol = col;
        if(isSafeToMove(matrix, visited, newRow, newCol, prv)){
            solveRec(matrix, visited, ans, currLen + 1, newRow, newCol);
        }
        
        // move down 
        newRow = row + 1, newCol = col;
        if(isSafeToMove(matrix, visited, newRow, newCol, prv)){
            solveRec(matrix, visited, ans, currLen + 1, newRow, newCol);
        }
        
        // ones all the paths for a cell are explored, mark it unvisited again 
        visited[row][col] = false;
    }

public:
    // main function
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        
        int rowSize = matrix.size();
        int colSize = matrix[0].size();

        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false)); // initially all are unvisited cells

        // we need to traverse all the nodes of the matrix 
        int ans = INT_MIN;
        for(int row = 0 ; row < rowSize; row++){
            for(int col=0; col < colSize; col++){
                
                int currLen = 0;
                solveRec(matrix, visited, ans, currLen, row, col);
            }
        }
        

        // if path is 1 -> 5 -> 7 (lenght will be 2) so add 1 to it and return 
        return ans + 1;

    }
};