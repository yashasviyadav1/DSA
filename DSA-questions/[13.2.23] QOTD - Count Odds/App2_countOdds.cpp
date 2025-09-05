
// leetcode link : https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/description/

class Solution {
public:
    /* ✔️⭐Approach - 2 (creating simple formula)

        T : O(1)
        S : O(1)
    */

    int countOdds(int low, int high) {

        // when both low and high are even
        if(low%2 ==0 && high % 2 == 0)
            return (high-low)/2;
        
        // c-1 when both odd, when any one is odd
        else return ((high-low)/2) + 1;
        
    }
};

