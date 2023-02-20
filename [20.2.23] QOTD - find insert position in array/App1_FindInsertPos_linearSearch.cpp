// leetcode link  https://leetcode.com/problems/search-insert-position

/*  ✔️Approach - 1 (linear search)

    T:O(N)
    S:O(N)
*/

class Solution {
public:
    // Main func
    int searchInsert(vector<int>& nums, int target) {
        
        for(int i = 0; i < nums.size(); i++){
            // when an element is found greater then or eq to target, return this index
            if(nums[i] >= target) return i;
        }


        // if we reached here that means target is greater then all values of 'nums' so correct position for it is 'size'
        return nums.size();
    }
};