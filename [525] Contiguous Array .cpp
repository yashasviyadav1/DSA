class Solution {
/*⭐✔️Approach - 2 (using map)
    
    idea : we imagine 1 as 1 and 0 as -1, so that whenever we add equal number of 1's and 0's then we get 0, and when we get one means are 1's and 0's in the respective subarray are equal, so this way we can update the max len of subarray with equal 1's and 0's.
        we basically have 2 condintions that are important, 
            1) whenevert we get a '0' as sum that means starting from index 0, till the index we are currently on, then number of 0's and 1's are equal
            2) when a entry for current sum is already present in the map, that means starting from the '1st' index of this sum till the index we are on, the number of 1's and 0's have become equal

    ✅ T : O(n)
     S : O(n)
     ☑️link : https://leetcode.com/problems/contiguous-array
     
*/
public:
    int findMaxLength(vector<int>& nums) {

        // lets create a map, to store the 1st occurrence of each sum that comes our way
        unordered_map<int,int> sumToFirstIndex;
        sumToFirstIndex[0] = -1; // so that we can use the general formula only (to avoid a extra if cond)

        int resultingMaxLen = 0; // need to maximize this length
        int sum = 0;
        for(int index=0; index < nums.size(); index++){

            int ele = nums[index];

            // we imagine 0 as -1 and 1 as 1 (as per algo), so when 1 comes, add 1, when 0 comes add -1
            if(ele == 1) sum++;
            else sum--;

            // now if a entry for this sum is already present in map, then use it for finding 'currLen' of current subarray with equal 1's and 0's , else create 1 entry for this sum 
            int currLen;
            if(sumToFirstIndex.count(sum) != 0){ // entry present
                currLen = index - sumToFirstIndex[sum];
                resultingMaxLen = max(resultingMaxLen, currLen); // updating maxLen if we found bigger one
            }
            else // no entry present
                sumToFirstIndex[sum] = index;
        }

        return resultingMaxLen;
    }
};
