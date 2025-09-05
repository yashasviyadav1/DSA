# Find First and Last Position of Element in Sorted Array

### Solved at : [Leetcode](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/), [CodeStudio](https://www.naukri.com/code360/problems/first-and-last-position-of-an-element-in-sorted-array_1082549)

## ✔️Approach - 1 (using Binary Search)
```java
class Solution {
    // using binary Search
    // Time: O(logN) Space : O(1)

    public int[] searchRange(int[] nums, int target) {
        int n = nums.length;
        int startPos = -1;
        int low = 0, high = n-1;
        while(low <= high){
            int mid = low + (high-low)/2;
            if(nums[mid] == target){ // possible first occ, store it, and search on left coz 1st occ of target might be on left side
                startPos = mid;
                high = mid - 1;
            }
            else if(target < nums[mid]) // target is on left
                high = mid - 1; 
            else low = mid + 1; // target is on right
        }

        low = 0;
        high = n-1;
        int endPos = -1;
        while(low <= high){
            int mid = low + (high-low)/2;
            if(nums[mid] == target){// possible last occ, but last occ might be on right side 
                endPos = mid;
                low = mid + 1;
            }
            else if(target < nums[mid]) // target is on left 
                high = mid - 1;
            else low = mid + 1;// target is on right 
        }

        int[] ans = new int[2];
        ans[0] = startPos;
        ans[1] = endPos;
        return ans;
    }
}
```
