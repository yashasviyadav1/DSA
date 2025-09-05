// ☑️leetcode link : https://leetcode.com/problems/single-element-in-a-sorted-array

/* ✔️⭐Approach -2 (using binary search(with some additional steps) )
    
         ✅T : O(logN)
         ✅S : O(1)
*/

class Solution {
    

public:
    int singleNonDuplicate(vector<int>& nums) {
        
        // exception case : for array with only 1 element 
        if(nums.size() == 1) return nums[0];

        int low = 0, high = nums.size()-1;
        int mid;

        while(low < high){

            mid = low + (high-low)/2;
            int element = nums[mid];

            // [IMP] edge case :- when mid reached left OR right end of the array , that means that the single occuring element is at 'mid' the start/end so return the mid element
            if(mid == 0 || mid == nums.size()-1 ){
                return nums[mid];
            }

            // when mid element is the element occuring single time in nums
            if(nums[mid-1] != element && nums[mid+1] != element) return nums[mid];

            // else  if we reached here means another ocrurence of 'arr[mid]' exist
            else{

                //finding index of second occrence of nums[mid], and the first occurence index 
                int firstOccurIndex;
                int secondOccurIndex;
                if(nums[mid-1] == element){
                    firstOccurIndex = mid-1;
                    secondOccurIndex = mid;
                }
                else{
                    firstOccurIndex = mid;
                    secondOccurIndex = mid + 1;
                }
                
                // when the ist occurene's index is odd, second's index is even that means the 'singleOccuringElement; will be on the left of mid
                if(firstOccurIndex % 2 != 0)
                    high = mid - 1;
                
                // when the 1st occurene is even and second is odd, go to right 
                else low = mid + 1;
            }


        }

        // when low and high overlapped/merged (means single occurrence is found)
        return nums[low];
    }
};