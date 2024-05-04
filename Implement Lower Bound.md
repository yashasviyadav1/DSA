#  Implement Lower Bound

### Solved at : [CodeStudio](https://www.naukri.com/code360/problems/lower-bound_8165382)

note : lower bound is the smallest index `i` such that `arr[i] >= target`

## ✔️Approach - 1 (using binary search) 
```java
public class Solution { 
    // using binary search logic with modifications
    public static int lowerBound(int []arr, int n, int target) {
        int low = 0, high = n-1;
        int ans = n; // initially its n (for casses where target is = 32 array is {2, 5, 6, 4} in this case there is no element >= target) so ans is imaginary index 4
        while(low <= high){
            int mid = low + (high-low)/2;
            if(arr[mid] >= target){ // this can be possible lower bound
                ans = mid;
                high = mid-1; // search for smaller index that can be lower bound
            }
            else{
                low = mid + 1; // means target is on the right of mid
            }
        }
        return ans;
    }
}
```
