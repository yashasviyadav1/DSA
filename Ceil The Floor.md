# Ceil The Floor

### Solved at :  [CodeStudio](https://www.naukri.com/code360/problems/ceiling-in-a-sorted-array_1825401) , [GFG](https://www.geeksforgeeks.org/problems/ceil-the-floor2802/1)
## ✔️Approach - 1 (simple binary search technique)
CodeStudio Varient :- 
```java
import java.util.* ;
import java.io.*; 

/// finding floor and ceil using binary search
// T:O(logN) S:O(1) 
public class Solution {

  // floor = largest no <= target
  // ceil = smaller no >= target   
    public static int[] getFloorAndCeil(int[] arr, int n, int target) {
      int low = 0, high = n-1;
      int ceil = -1;
      while(low <= high){
        int mid = low + (high-low)/2;
        if(arr[mid] >= target)
        {
          ceil = arr[mid];
          high = mid - 1;
        }
        else low = mid + 1;
      }

      int floor = -1;
      low = 0;
      high = n-1;
      while(low <= high){
         int mid = low + (high-low)/2;
        if(arr[mid] <= target){
          floor = arr[mid];
          low = mid + 1;
        }
        else high = mid - 1;
      }

      int[] ans = new int[2];
      ans[0] = floor;
      ans[1] = ceil;

      return ans;
    }
    
}
```

GFG Varient : 
```java

/// finding floor and ceil using binary search
// T:O(nlogn + logN) S:O(1) 

// floor = largest no <= target
// ceil = smallest no >= target   
class Solve {
    Pair getFloorAndCeil(int[] arr, int n, int target) {
        
      Arrays.sort(arr); // imp for binary search
      
      int low = 0, high = n-1;
      int ceil = -1;
      while(low <= high){
        int mid = low + (high-low)/2;
        if(arr[mid] >= target) // possible ceil look for smaller
        {
          ceil = arr[mid];
          high = mid - 1;
        }
        else low = mid + 1;
      }

      // finding floor 
      int floor = -1;
      low = 0;
      high = n-1;
      while(low <= high){
         int mid = low + (high-low)/2;
        if(arr[mid] <= target){ // possible floor, look for larger
          floor = arr[mid];
          low = mid + 1;
        }
        else high = mid - 1;
      }

      // storing ans
      Pair ans = new Pair();
      ans.floor = floor;
      ans.ceil = ceil;
      return ans;
    }
}
```
