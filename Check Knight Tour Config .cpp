// 19 Mar 23 - contest question 2 
// ☑️leetcode link : https://leetcode.com/problems/check-knight-tour-configuration/description/

class Solution {
    /* ✔️⭐Approach - 1 (recursion)

        explanation :- what we will do is we are initially at coordinates (0,0) so we would maintain the currRow, currCol, and currMove = 0(initially) and we will check all possible 8 moves(at max) using if conditions and if we found any next move having value = 'currMove+1' means we found a next move, in that case we will move to that cell recursively solve for the rest cells, and if did not found any valid next move from the 8 possible moves then in that case, return false. as asnwer.

        ✅T : O(N) 
        S : O(N) only recursive stack

       🔍correction in prv code : no need for visited array because there can never be a case when a cell has 2 values i.e we can never visit the same cell again.

    */
private:
    // fun.3 
    pair<int,int> findNextMove(vector<vector<int>> &grid, int currRow, int currCol, int &currMove){
        
        int n = grid.size();
        
        // check all possible valid move, and if any move is not visited and is next move as well, then return those new coordinates
        if( ( (currRow-2 >= 0 && currRow - 2 <= n-1) && (currCol-1 >= 0 && currCol-1 <= n-1)) && grid[currRow - 2][currCol - 1] == currMove + 1) //1
            return {currRow-2, currCol-1};
        
        if( ( (currRow - 2 >= 0 && currRow - 2 <= n-1) && (currCol + 1 >= 0 && currCol + 1 <= n-1)) && grid[currRow - 2][currCol + 1] == currMove + 1)  //2
            return {currRow-2, currCol+1};
        
        if(( (currRow + 2 >= 0 && currRow + 2 <= n-1) && (currCol - 1 >= 0 && currCol - 1 <= n-1)) && grid[currRow + 2][currCol - 1]  == currMove + 1)
            return {currRow + 2,currCol - 1};
        
        if(( (currRow + 2 >= 0 && currRow + 2 <= n-1) && (currCol + 1 >= 0 && currCol + 1 <= n-1)) && grid[currRow + 2][currCol + 1]  == currMove + 1)
            return {currRow + 2 ,currCol + 1};
        
        if(( (currRow + 1 >= 0 && currRow + 1 <= n-1) && (currCol + 2 >= 0 && currCol + 2 <= n-1)) && grid[currRow + 1 ][currCol + 2]  == currMove + 1)
            return {currRow + 1 ,currCol + 2};
        
        if(( (currRow + 1>= 0 && currRow + 1 <= n-1) && (currCol - 2 >= 0 && currCol - 2 <= n-1)) && grid[currRow + 1][currCol - 2]  == currMove + 1)
            return {currRow + 1, currCol - 2};
        
        if(( (currRow - 1 >= 0 && currRow - 1 <= n-1) && (currCol + 2 >= 0 && currCol + 2 <= n-1)) && grid[currRow - 1][currCol + 2]  == currMove + 1)
            return {currRow - 1, currCol + 2};
        
        if(( (currRow - 1 >= 0 && currRow - 1 <= n-1) && (currCol - 2 >= 0 && currCol - 2 <= n-1)) && grid[currRow - 1][currCol - 2]  == currMove + 1)
            return {currRow - 1, currCol - 2};
        
        // no move found 
        return {-1,-1};
        
    }
    
    // fun.2 
    bool isGridValid(vector<vector<int>> &grid, int currRow, int currCol, int &currMove){
        
        // base case - if we are already on last move cell, then return true - valid grid
        if(currMove >= grid.size()*grid.size() - 1) return true;
        
        // find the next move from curr cell 
        pair<int,int> nextMovePair = findNextMove(grid, currRow, currCol, currMove);
        
        // if no move found, return false, else recursively move to the next cell
        if(nextMovePair.first == -1 && nextMovePair.second == -1) return false;
        
        return isGridValid(grid, nextMovePair.first, nextMovePair.second, ++currMove);
        
    }
public: // main fun,
    bool checkValidGrid(vector<vector<int>>& grid) {
        
        // we need tp maintain currRow,currCol, and currMove 
        int currRow = 0, currCol = 0;
        int currMove = 0; // currently on cell {0,0}
        return isGridValid(grid, currRow, currCol, currMove);
        
    }
};
