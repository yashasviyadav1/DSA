// (Solved)✔️ - Surrounded Regions - 1 Approach (DFS)

// ☑️solved at leetcode : https://leetcode.com/problems/surrounded-regions/description/
// ☑️solved at gfg : https://practice.geeksforgeeks.org/problems/replace-os-with-xs0052/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article

class Solution {
    /* ✔️⭐App-1 (DFS)
         
         idea : by observation it is clear that we can only convert those 'O' cells to 'X' which have neighbours of value either 'X' or value 'O' (only those can be converted to 'X'),
         so that means if there is any cell on border of the matrix with value 'O', we can not convert it to 'X' at any cost because border 'O' cells have empty end on at least 1 side,
         so by intuition, we can see that if we somehow find all the cells with value 'O' which are neigh of 'border cells' (with value O), then we can visit them via DFS and at last 
         we would know which cells can be converted and which ones can not. 
         
         
         T : O(E+V)
         S : O(E+V)
    */
private:

    // check if a cell is on any of the border of matrix or not. 
    bool isBorderCell(vector<vector<char>> &board, int row, int col){
        
        int rowSize = board.size();
        int colSize = board[0].size();
        // for a cell to be on boarder of matrix there are few conditions:-
        //1. either row should be 1st or last row of matrix , OR
        //2. col should be 1st or last col of matrix 
        if( (row == 0 || row == rowSize - 1) || (col == 0 || col == colSize - 1) )
            return true;
        return false;
    }

    // checks if any cell is in range of matrix walls, as well as with value 'O' or not
    bool isSafeToMove(vector<vector<char>> &board, int row, int col){
        int rowSize = board.size();
        int colSize = board[0].size();

        if((row < rowSize && row >= 0) && (col < colSize && col >= 0) && board[row][col] == 'O')
            return true;
        return false;
    }

    void DFS(vector<vector<char>> &board, vector<vector<bool>> &visited, int row, int col){
        
        visited[row][col] = true;
        
        // go till the depth of all the '0' valued neigh of curr cell which is not visited 
        // l, r, u, d
        vector<int> deltaRow = {0, 0, -1, +1};
        vector<int> deltaCol = {-1, +1, 0, 0};

        for(int i=0; i<4; i++){
            int newRow = row + deltaRow[i];
            int newCol = col + deltaCol[i];
            
            if( isSafeToMove(board, newRow, newCol) && !visited[newRow][newCol] ) // it is safe to move if the neigh is '0' and in range and not visited
                DFS(board, visited, newRow, newCol);
        } 
    }

public:
    // main
    void solve(vector<vector<char>>& board) {
        
        int rowSize = board.size();
        int colSize = board[0].size();

        // we need to maintain the visited nodes
        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false));

        // since we can never convert the '0' valued cells on the boarder of the matrix, so lets only call DFS for them and mark their neigh with value '0' as visited, because as we can not convert boarder '0' cells so as we can not convert their neigh with value '0' too 
        for(int row=0; row<rowSize; row++){
            for(int col=0; col<colSize; col++){
                if( board[row][col] == 'O' && !visited[row][col] && isBorderCell(board,row,col))
                    DFS(board, visited, row, col);
            }
        }

        // convert all the non visited 'O' value cells into 'X'
        for(int row=0; row < rowSize; row++){
            for(int col=0; col < colSize; col++){
                if(board[row][col] == 'O' && !visited[row][col] )
                    board[row][col] = 'X';
            }
        }
    }
};
