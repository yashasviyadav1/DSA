# Count Subsets with Sum K

#### Solved at [CodeStudio](https://www.codingninjas.com/studio/problems/number-of-subsets_3952532) (there is some issue with their testcases)

#### Prerequisite : subsets with k sum (codestudio)

## Approach - 4 (Tabulation + Space optimization) 
```java
import java.util.*;
import java.io.*;

public class Solution {

    //App-4 (tabulation + Space optmization)
    // Time : O(n*k)
    // Space : O(2*k) - 2 1s arrays only
    private static int MOD = 100000000 + 7; //1e9 + 

    public static int findWays(int nums[], int k) {
 
        // tabulation to space optimization
        int[] prev = new int[k+1]; // this will be for index=0 row initially
        prev[0] = 1; // for all rows, if target is 0 we found 1 subset with target sum
        
        // base - if target at 1st element == 1st element means subset found with sum k
        if(nums[0] <= k){
            prev[nums[0]] = 1;
        }

        // since i=0 is calculated and target=0 is calculated, we go futher
        for(int index=1; index < nums.length; index++){
            int[] curr = new int[k+1];
            curr[0] = 1; // for all rows, if target is 0 we found 1 subset with target sum
        
            for(int target=1; target <= k; target++){
                int notPick = prev[target];
                int pick = 0;
                if(nums[index] <= target)
                    pick = prev[target-nums[index]];

                curr[target] = ((pick)%MOD + (notPick)%MOD)%MOD;
            }
            prev = curr;
        }

        int ans = prev[k];
        // for cases like {0,0,1,2} k=3 here expout : 4 our wrong output would be 0
        int zerosCount = 0;
        for(int ele:nums) if(ele==0) zerosCount++;
        return ((int)(Math.pow(2,zerosCount)) * ans);
  

    }
}
```

## Approach - 3 (tabulation - bottom up dp)
```java
import java.util.*;
import java.io.*;

public class Solution {

    //App-3 bottom up dp (tabulation)
    // Time : O(n*k)
    // Space : O(n*k) - dp only  
    private static int MOD = 100000000 + 7; //1e9 + 

    public static int findWays(int nums[], int k) {
 
        // memoization to tabulation
        int[][] dp = new int[nums.length][k+1];
        // base- if target is 0 we found 1 subset with target sum
        for(int index=0; index < nums.length; index++) 
            dp[index][0] = 1;

        // base - if target at 1st element == 1st element means subset found with sum k
        if(nums[0] <= k){
            dp[0][nums[0]] = 1;
        }

        // since i=0 is calculated and target=0 is calculated, we go futher
        for(int index=1; index < nums.length; index++){
            for(int target=1; target <= k; target++){
                int notPick = dp[index-1][target];
                int pick = 0;
                if(nums[index] <= target)
                    pick = dp[index-1][target-nums[index]];

                dp[index][target] = ((pick)%MOD + (notPick)%MOD)%MOD;
            }
        }

        int ans = dp[nums.length-1][k];
        // for cases like {0,0,1,2} k=3 here expout : 4 our wrong output would be 0
        int zerosCount = 0;
        for(int ele:nums) if(ele==0) zerosCount++;
        return ((int)(Math.pow(2,zerosCount)) * ans);


    }
}
```

## Approach - 2 (top down dp - memoization)
```java
import java.util.*;
import java.io.*;

public class Solution {

    //App-2 bruteforce (dp)
    // Time : O(2^n)
    // Space : O(n) - recursive only
    private static int MOD = 100000000 + 7; //1e9 + 7
    private static int countKSumSubsets(int[] nums, int[][] dp, int index, int target){
        if(target == 0) return 1;  
        if(index == 0) return (target == nums[0]) ? 1 : 0;
        if(dp[index][target] != -1) return dp[index][target];

        int notPick = countKSumSubsets(nums, dp, index-1, target);
        int pick = 0;
        if(nums[index] <= target)
            pick = countKSumSubsets(nums, dp, index-1, target-nums[index]);

        return dp[index][target] =pick + notPick;
    }
    public static int findWays(int nums[], int k) {
        int[][] dp = new int[nums.length][k+1];
        for(int[] row:dp) Arrays.fill(row, -1); //dp[i][k] means how many subsets exists in array from 0 to i with sum == k

        int ans = countKSumSubsets(nums, dp, nums.length-1, k);

        int zerosCount = 0;
        for(int ele:nums) if(ele==0) zerosCount++;

        // for cases like {0,0,1,2} k=3 here expout : 4 our wrong output would be 0
        ans = ((int)(Math.pow(2,zerosCount)) *ans);

        return (ans) % MOD;
    }
}
```

## ⚠️[TLE] Approach - 1 (Bruteforce)
```java
import java.util.*;
import java.io.*;

public class Solution {

    //App-1 bruteforce (pick and not pick)
    // Time : O(2^n)
    // Space : O(n) - recursive only
    private static int countKSumSubsets(int[] nums, int[][] dp, int index, int target){
        if(target == 0) return 1;  
        if(index == 0) return (target == nums[0]) ? 1 : 0;
        if(dp[index][target] != -1) return dp[index][target];

        int notPick = countKSumSubsets(nums, dp, index-1, target);
        int pick = 0;
        if(nums[index] <= target)
            pick = countKSumSubsets(nums, dp, index-1, target-nums[index]);

        return dp[index][target] = pick + notPick;
    }
    public static int findWays(int nums[], int k) {
        int[][] dp = new int[nums.length][k+1];
        for(int[] row:dp) Arrays.fill(row, -1); //dp[i][k] means how many subsets exists in array from 0 to i with sum == k

        int ans = countKSumSubsets(nums, dp, nums.length-1, k);
        return (ans) % (1000000007);
    }
}
```
