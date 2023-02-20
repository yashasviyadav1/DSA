// leetcode link  https://leetcode.com/problems/search-insert-position

/* ⭐✔️Approach -2 (using binary search)

        T : O(LogN)
        S : O(1)

*/
class Solution {

public:
    int searchInsert(vector<int>& nums, int target) {
        
        int low = 0, high = nums.size()-1;
        int mid;

        while(low <= high){

            mid = low + (high-low)/2;

            // when target is found, return the index
            if(nums[mid] == target)
                return mid;
            
            // when target is smaller then the nums[mid], then search for correct position in left
            else if(nums[mid] > target) high = mid - 1;

            // similarly when target is greater search in right
            else low = mid + 1;
        }

        return low;
    }
};