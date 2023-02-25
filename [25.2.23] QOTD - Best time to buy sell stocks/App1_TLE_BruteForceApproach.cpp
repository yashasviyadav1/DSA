// ⚠️leetcode link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

/* [TLE⚠️ TC.199/211] brute force approach 

            explanation : for each element consider it as a buyingPrice, and search for a higher selling price on its right of the 'prices' array, keep track of the max profit side by side.

        ⚠️T : O(n^2)
        S : O(1)
*/

// code
class Solution {   

public:
    int maxProfit(vector<int>& prices) {

        int buyingPrice = 0;
        int maxProfit = INT_MIN;

        for(int i=0; i < prices.size(); i++){
            buyingPrice = prices[i];
            for(int j=i+1; j < prices.size(); j++){
                if(prices[j] > buyingPrice)
                    maxProfit = max(maxProfit, prices[j]-buyingPrice);
            }
        }

        // if we found a maxProfit, then return it else return 0
        if(maxProfit != INT_MIN) return maxProfit;
        return 0;
        
    }
};