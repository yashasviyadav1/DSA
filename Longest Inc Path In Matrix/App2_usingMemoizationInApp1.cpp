// ☑️leetcode link : https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/

/* ⭐✔️Approach - 2 (implementing cache/dp/memoization into App1)

            explanation :- what we did in approach 1 is for every cell of the 2d matrix, we explored all 4 ways path, and we repeated the same thing for everty other cells, which caused the TLE, but here to improve this issue, once we have any cells Longest increasing sequeunce length, we will simply store it into another 2d vetor 'LIScache[i][j]' where LisCache[i][j] means the LIS length of the cell i,j so that we dont have to do the repeatitive work, and using cache we will achieve this with memoization or dp 

        ✅T : O(N*M)
        ✅S : O(N*M) for recursive stack & LIScache 2d vector 
        
        \U0001f50dnote : we dont need visited because we are travelling along incrasing sequences, so we cant go on the prv nodes again 
*/

// code 
class Solution {
   
private:
    // Fun.3 : this function will return true, if it is safe to move to cell 'currRow' and 'currCol' from the prvValue, else it returns false
    bool isSafeToMove(vector<vector<int>> &matrix, int currRow, int currCol, int prvValue){

        int rowSize = matrix.size();
        int colSize = matrix[0].size();

        // if we got out of row and col range or the cell we are on is not greater then the prv one then return false 
        if((currRow < 0 || currRow >= rowSize) || (currCol < 0 || currCol >= colSize) || matrix[currRow][currCol] <= prvValue)
            return false;

        return true;
    }

    // Fun.2
    int DFS(vector<vector<int>> &matrix, vector<vector<int>> &LIScache, int currRow, int currCol){

        // base case - if we have already calculated the LIS previously for the curr cell then simply return that
        if(LIScache[currRow][currCol] != 0)
            return LIScache[currRow][currCol];

        // initially we have currCellLIS  length = 1 (including itself)
        int currCellLIS = 1;
        int prvValue = matrix[currRow][currCol];  // this we will use in the 'isSafeToMove' function

        // now go to left and find out the LIS from there , and update the currCellLis, if left has greater LIS
        int newRow = currRow, newCol = currCol - 1;
        if(isSafeToMove(matrix, newRow, newCol, prvValue))
            currCellLIS = max(currCellLIS, DFS(matrix, LIScache, newRow, newCol)+1);

        // right 
        newRow = currRow, newCol = currCol + 1;
        if(isSafeToMove(matrix, newRow, newCol, prvValue))
            currCellLIS = max(currCellLIS, DFS(matrix, LIScache, newRow, newCol)+1);

        // up 
        newRow = currRow - 1, newCol = currCol;
        if(isSafeToMove(matrix, newRow, newCol, prvValue))
            currCellLIS = max(currCellLIS, DFS(matrix, LIScache, newRow, newCol)+1);
        // down 
        newRow = currRow + 1, newCol = currCol;
        if(isSafeToMove(matrix, newRow, newCol, prvValue))
            currCellLIS = max(currCellLIS, DFS(matrix, LIScache, newRow, newCol)+1);

        // now when we have explored all the 4 paths from the curr cell, now return the maximum length of the increasing sequence we got , but brfore that make sure to store it into the 'LIScache' 2d vector' (dp)
        LIScache[currRow][currCol] = currCellLIS; //IMP
        return currCellLIS;
    }

public:
    // Main function
    int longestIncreasingPath(vector<vector<int>>& matrix) {

        int rowSize = matrix.size();
        int colSize = matrix[0].size();

        vector<vector<int>> LIScache(rowSize, vector<int>(colSize,0)); // initially all the LIS is 0, we are it 0, instead of 1 so that with 0 we know that a cells LIS is not already calculated. 

        int longestIncSeqLen = 0; // to return at the end

        // note : we dont need visited because we are travelling along incrasing sequences, so we cant go on the prv nodes again 

        // call dfs for those cells only whose LIScache is not yet calculated i.e (has a value of 0)
        for(int row = 0; row < rowSize; row++){
            for(int col = 0; col < colSize; col++){
                if(LIScache[row][col] == 0){
                    LIScache[row][col] = DFS(matrix, LIScache, row, col);
                }
                // ones we have the LIS in hand, just update the ans (if LIS value is more then ans or longestIncSeqLen)
                longestIncSeqLen = max(longestIncSeqLen, LIScache[row][col] );
            }
        }
        
        
        return longestIncSeqLen;
    }
};