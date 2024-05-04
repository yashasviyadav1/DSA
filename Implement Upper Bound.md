# Implement Upper Bound

### Solved at : [Leetcode](https://www.naukri.com/code360/problems/implement-upper-bound_8165383)


`lower bound` of a `target` is the smallest index `i` such that `arr[i] >= target`.

`upper bound` of a `target` is the smallest index `i` such that `arr[i] > target`

## ✔️Approach - 1 (using Binary Search)
```java
public class Solution {
    // using binary search logic with minor changes
    // T:O(logn) S:O(1)
    public static int upperBound(int []arr, int target, int n){
        int low = 0, high = n-1;
        int ans = n; // for case where target is greater then the last element of array
        while(low <= high){
            int mid = low + (high-low)/2;
            if(arr[mid] > target) // possible ub found , search if there exist a smaller index that can be upper bound
            { 
                ans = mid;
                high = mid - 1;
            }
            else low = mid + 1;
        } 

        return ans;
    }
}

```
