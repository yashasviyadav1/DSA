/* ✔️⭐App-1 (using recursion)
    T : O(N)
    S : O(N) -recursive call stack 
    
    ☑️solved at leetcode : https://leetcode.com/problems/count-total-number-of-colored-cells/description/
*/

class Solution {
    
public:
    long long coloredCells(int n) {
        
        // base case - if n is 1, boxes = 1
        if(n==1) return 1;

        // recursion will find boxes at (n-1)th minute
        long long boxesAtprvMin = coloredCells(n-1);

        // calculatin boxes at curr minute 
        long long boxesAtNthMinute = boxesAtprvMin + 4*(n-1);
        
        return boxesAtNthMinute;
 
    }
};
