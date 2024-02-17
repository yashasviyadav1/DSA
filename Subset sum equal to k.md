# Subset sum equal to k 

#### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/subset-sum-equal-to-k_1550954/)

## ✔️⭐Approach - 3 (bottom up dp - tabulation)
```java
import java.util.* ;
import java.io.*; 

public class Solution {
    // tabulation Approach
  // Time : O(n)
// Space : O(n) - dp grid only

    public static boolean subsetSumToK(int n, int k, int arr[]){
        
        // converting top down dp into tabulation
        boolean[][] dp = new boolean[n][k+1]; // dp
        for(int index = 0; index < n; index++) // base case 1
            dp[index][0] = true;
        if(k >= arr[0]) // consider k = 5, arr[0] = 50 and we access arr[0][50] out of bound will be thrown
            dp[0][arr[0]] = true; // base case 2 

        // in rec our i was goidn from n-1 to 0 here it goes reverse it
        // in rec our target goes from k to 0 reverse it 
        for(int index=1; index < n; index++){ 
            for(int target=1; target <= k; target++){

                boolean notPick = dp[index-1][target];  
                boolean pick = false; 
                if(target >= arr[index])
                    pick = dp[index-1][target-arr[index]];

                // if any of the calls have ans true means we found a subset with sum k 
                dp[index][target] = pick || notPick;
            }
        }
            
        return dp[n-1][k];
    }
}
```

## ✔️ Approach - 2 (top down dp - memoization)
```java
import java.util.* ;
import java.io.*; 

public class Solution {
    // Top down DP Approach
  // Time : O(n)
// Space : O(2n) - recursve + dp grid
    public static boolean solve(int[] arr, int[][] dp, int index, int target){
        if(target == 0) return true; // target achieved already
        if(index == 0) return target == arr[index]; // reached last, pick last if target achieved 
        if(dp[index][target] != -1){
            return (dp[index][target] == 1)? true : false;
        }

        // not picked ith element soo target is same for remaining 0 to i-1 array
        boolean notPick = solve(arr, dp, index-1, target);  
        // pick only when curr element is smaller then array (eg 4,1,3) t=2 so no need to pick 3 coz target will become negative
        boolean pick = false; 
        if(target >= arr[index])
            pick = solve(arr, dp, index-1, target-arr[index]); // picked arr[i] so target reduced

        // if any of the calls have ans true means we found a subset with sum k 
        boolean ans = pick || notPick;
        dp[index][target] = (ans==true)?(1):(0);
        return ans;
    } 
    public static boolean subsetSumToK(int n, int k, int arr[]){
        // 2 changing states index and target as we move so 2d dp
        // dp[index][target]    index goes from n-1 to 0 total n, target goes from k to 0  i.e k+1 space(coz we only pick element with target >= element)
        int[][] dp = new int[n][k+1];
        for(int[] row:dp) 
            Arrays.fill(row, -1); 

        return solve(arr, dp, n-1, k); // is there a subset with sum = k, in arr 0 to n-1
    }
}

```
## ⚠️[TLE] Approach - 1 (bruteforce)
```java
import java.util.* ;
import java.io.*; 

public class Solution {
// Approach - 1 [TLE] (finding all the subsets)
// time : O(2^n)
// Space : O(n) - recursive stack space

    public static boolean solve(int[] arr, int index, int target){
        if(target == 0) return true; // target achieved already
        if(index == 0) return target == arr[index];
        
        // pick current index
        boolean notPick = solve(arr, index-1, target);  // not picked ith element soo target is same for remain
        boolean pick = false; 
        if(target >= arr[index])
            pick = solve(arr, index-1, target-arr[index]);

        // if any of the calls have ans true means we found a subset with sum k 
        return pick || notPick;
    } 
    public static boolean subsetSumToK(int n, int k, int arr[]){
        return solve(arr, n-1, k); // is there a subset with sum = k, in arr 0 to n-1
    }
}

```
