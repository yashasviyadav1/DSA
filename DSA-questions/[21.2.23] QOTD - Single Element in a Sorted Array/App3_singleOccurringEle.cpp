// ☑️leetcode link : https://leetcode.com/problems/single-element-in-a-sorted-array

/* ✔️⭐⭐Approach 2.1 (improved version of app-2) - improved B.S

        T : O(logN)
        S : O(1)

*/
class Solution {
public:
    
    // main function
    int singleNonDuplicate(vector<int>& nums) {

        int low = 0, high = nums.size()-1;
        int mid;
        while(low < high){

            mid = low + (high - low)/2;

            // if mid is odd, decrement it by 1 (so that after decrementing odd index becomes even andd we only have to compare mid, mid+1 indexed elements to be same)
            if(mid % 2 == 1) mid--;

            // now if even index(mid) and odd index(mid+1) are same then search in the right, else search on the left
            if(nums[mid] == nums[mid+1]) 
                low = mid + 2; // in normal BS we do mid + 1, but here mid is already decremented by 1 before so do this 
            else high = mid; // already decremented 
        }
        
        // when low,high submerged/overlapped
        return nums[low];
    }
};