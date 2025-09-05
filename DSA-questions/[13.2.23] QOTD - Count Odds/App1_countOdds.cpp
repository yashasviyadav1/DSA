// leetcode link : https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/description/

class Solution {
public:
    // ✔️Approach - 1(naive approach) [ T : O(n) S : O(1) ]
    int countOdds(int low, int high) {

        int oddCount = 0;
        for(int i=low; i<=high; i++){
            if(i % 2 != 0)
                oddCount++;
        }

        return oddCount;
        
    }
};