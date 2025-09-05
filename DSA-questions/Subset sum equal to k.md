# Subset sum equal to k 

#### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/subset-sum-equal-to-k_1550954/)
#### Solved at : [GFG](https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1)

##### Concept : 
Finding the base case is the most important :
if we have single element lets say `arr[0] = '5'` then target can only be achieved if either target is 5 (i.e `target == arr[0]`) or target is 0.
so :
```java
if(index==0){ // reached last ele, and it can make target
    if(target == 0 || arr[0] == target) return true;
    else return false;
}
```

## ✔️⭐Approach- 4 (tabulation with space optimization)
```java
import java.util.* ;
import java.io.*; 

public class Solution {
    // space optimization 
    // T:O(n*Sum) S:O(2*Sum) 
    
    public static boolean subsetSumToK(int N, int sum, int arr[]){
        // tabulation to space optimization
        boolean[]prev = new boolean[sum+1];
        // base cases
        prev[0] = true;
        if(arr[0] <= sum) prev[arr[0]] = true;
        
        for(int index=1; index <N; index++){
            boolean[] curr = new boolean[sum+1];
            for(int target=0; target <= sum; target++){
                
                boolean pick = false;
                if(arr[index] <= target)
                    pick = prev[target-arr[index]];
                boolean notPick = prev[target];
                
                curr[target] = pick || notPick;
            }
            prev = curr;
        }
        
        return prev[sum];
    }
}


```

## ✔️⭐Approach - 3 (bottom up dp - tabulation)
```java
import java.util.* ;
import java.io.*; 

public class Solution {
    // bottom up dp (tabulation)
    // T:O(n*Sum) S:O(n*Sum) 
    
    public static boolean subsetSumToK(int N, int sum, int arr[]){
        boolean[][] dp = new boolean[N][sum+1];
        // base cases
        dp[0][0] = true;
        if(arr[0] <= sum) dp[0][arr[0]] = true;
        
        for(int index=1; index <N; index++){
            for(int target=0; target <= sum; target++){
                
                boolean pick = false;
                if(arr[index] <= target)
                    pick = dp[index-1][target-arr[index]];
                boolean notPick = dp[index-1][target];
                
                dp[index][target] = pick || notPick;
            }
        }
        
        return dp[N-1][sum];
    }
}

```

## ✔️ Approach - 2 (top down dp - memoization)
```java
import java.util.* ;
import java.io.*; 

public class Solution {
    // top down dp (memoization)
    // T:O(n*Sum) S:O(n*Sum) 
    static private boolean solve(int[] arr, int[][] dp, int index, int target){
        if(index==0){ // reached last ele, and it can make target
            if(target == 0 || arr[0] == target) return true;
            else return false;
        }
        if(dp[index][target] != -1) return (dp[index][target] == 1)? true : false;

        // pick the current element so target will be reduced
        // do not pick element if it is greater then target (we do not want target to be -ve)
        boolean pick = false;
        if(arr[index] <= target)
            pick = solve(arr, dp, index-1, target-arr[index]);

        // not picking curr element so target remains same, we just move
        boolean notPick = solve(arr,dp, index-1, target);
        boolean ans = pick || notPick;
        dp[index][target] = (ans == true)?1:0; 
        return ans;
    }
    public static boolean subsetSumToK(int n, int k, int arr[]){
        // 2 changing states index and target as we move so 2d dp
        // dp[index][target]    index goes from n-1 to 0 total n, target goes from k to 0  i.e k+1 space(coz we only pick element with target >= element)
        int[][] dp = new int[n][k+1];
        for(int[] row:dp) 
            Arrays.fill(row, -1); 

        boolean ans = solve(arr, dp, n-1, k); // is there a subset with sum = k, in arr 0 to n-1

        return ans;
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
