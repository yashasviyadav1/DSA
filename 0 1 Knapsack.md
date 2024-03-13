#  0 1 Knapsack 

#### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/0-1-knapsack_920542)

## ✔️Approach - 5 (Space optimization to single 1d array)
```java
public class Solution{
    // (space optimization - 2) 
    // T:O(n*limit)     S:O(limit)
    static int knapsack(int[] wt, int[] value, int n, int k) {

        // tabulation to space optimization -2 
        int[] prev = new int[k+1];
        for(int limit=0; limit <= k; limit++)        // base cases 
            if(wt[0] <= limit)
                prev[limit] = value[0];
        
        for(int index=1; index < n; index++){
            for(int limit=k; limit >= 0; limit--){ // we have to run this loop in rev coz other as we move from left to right we would overwrite the left values before using them, that would result in wrong ans
                int notPick = prev[limit]; // not picked current wt
                int pick = 0;
                if(wt[index] <= limit) // pick current wt's value only if it is nore more then limit
                    pick = value[index] + prev[limit-wt[index]]; // add current val
                prev[limit] = Math.max(notPick, pick);
            }
        }
        return prev[k];
    }
}
```
## ✔️ Approach - 4 (Space Optimization to 2 1d ararys)
```java
import java.util.* ;
import java.io.*; 

public class Solution{

    // Approach - 3.1 (space optimization to 2 1d arrays) 
    // T : O(n*knapSackLimit) 
    // S : O(n*knapSackLimit) -> only dp


    static int knapsack(int[] weight, int[] value, int n, int knapsackWeightLimit) {
  
        //  Tabulation to space optimization to 2 1d arrays
        int[] prev = new int[knapsackWeightLimit+1]; // for 0th index (initially ) 

        for(int remWeightLimit=weight[0]; remWeightLimit <= knapsackWeightLimit; remWeightLimit++){
            prev[remWeightLimit] = value[0]; // base case 1
        }
       
        // step 3 : we have ans for index 0 , lets find for remaining
        for(int index=1; index < n; index++){

            int[] curr = new int[knapsackWeightLimit+1]; // for 1st index initially 

            for(int remWeightLimit=0; remWeightLimit <= knapsackWeightLimit; remWeightLimit++){
   
                int pick = 0; 
                if(weight[index] <= remWeightLimit){
                    pick = value[index] + prev[remWeightLimit - weight[index]];
                }
                int notPick = prev[remWeightLimit];

                // we find maxValuePicked after picking the current weight and not picking as well, now whichever gives us max value we choose that
                curr[remWeightLimit] = Math.max(pick, notPick);
            }
            prev = curr;
        }

        return prev[knapsackWeightLimit];

    }
}
```

## ✔️Approach - 3 (Top down dp - memoization)
```java
import java.util.* ;
import java.io.*; 

public class Solution{

    // Approach - 2 (tabulation) 
    // bottom up dp
    // T : O(n*knapSackLimit) 
    // S : O(n*knapSackLimit) -> only dp


    static int knapsack(int[] weight, int[] value, int n, int knapsackWeightLimit) {
 
        // memoization to tabulation
        // step1 : dp
        // dp[index][remainingWeightLimit]   stores the max possible value that can be robbed till from 0 to index with remWeightLimit
        // remainning weight limit can be from 0 to knapsackWeightLimit     
        int[][] dp = new int[n][knapsackWeightLimit + 1]; // +1 coz if limit is 10 then totalweightpicked can be 10 as well
    
        // if we have only 1 cell then we can pick that only if its weight is less then knapsack limit
        // current cell's weight is 2 then we can pick it if remWeights is from 2 to limit  
        for(int remWeightLimit=weight[0]; remWeightLimit <= knapsackWeightLimit; remWeightLimit++){
            dp[0][remWeightLimit] = value[0]; // base case 1
        }
       
        // step 3 : we have ans for index 0 , lets find for remaining
        for(int index=1; index < n; index++){
            for(int remWeightLimit=0; remWeightLimit <= knapsackWeightLimit; remWeightLimit++){
                // pick the current weight only if that will not exceed the limit 
                // i.e the current weight shoudld not be more then the remWeightLimit
                int pick = 0; 
                if(weight[index] <= remWeightLimit){
                    pick = value[index] + dp[index-1][remWeightLimit - weight[index]];
                }
                int notPick = dp[index-1][remWeightLimit];

                // we find maxValuePicked after picking the current weight and not picking as well, now whichever gives us max value we choose that
                dp[index][remWeightLimit] = Math.max(pick, notPick);
            }
        }

        return dp[n-1][knapsackWeightLimit];

    }
}
```

## ✔️Approach - 2 (bottom up dp - memoization)
```java

public class Solution{

    // Approach - 1 (memoization pick and not pick) 
    // top down dp
    // T : O(n*knapSackLimit) 
    // S : O(n*knapSackLimit) -> rec stack + dp
    private static int solve(int[] weight, int[] value, int[][] dp, int index, int remWeightLimit){
        if(index == 0){ // reached last element, and if this weights is <= remLimimit then only we can have its value
            if(weight[0] <= remWeightLimit)
                return value[0];
            return 0; 
        }
        if(dp[index][remWeightLimit] != -1) return dp[index][remWeightLimit];  

        // pick the current weight only if that will not exceed the limit 
        // i.e the current weight shoudld not be more then the remWeightLimit
        int pick = 0; 
        if(weight[index] <= remWeightLimit){
            pick = value[index] + solve(weight, value, dp, index-1, remWeightLimit - weight[index]);
        }
        int notPick = solve(weight, value, dp, index-1, remWeightLimit);

        // we find maxValuePicked after picking the current weight and not picking as well, now whichever gives us max value we choose that
        return dp[index][remWeightLimit] = Math.max(pick, notPick);
    }   

    static int knapsack(int[] weight, int[] value, int n, int knapsackWeightLimit) {

        int index = n-1, totalWeightPicked = 0; 

        // dp[index][remainingWeightLimit]   
        // remainning weight limit can be from 0 to knapsackWeightLimit     
        int[][] dp = new int[n][knapsackWeightLimit + 1]; // +1 coz if limit is 10 then totalweightpicked can be 10 as well
        for(int[] row:dp) Arrays.fill(row, -1);
         
        return solve(weight, value, dp, index, knapsackWeightLimit); // this would return the max total value picked by robber in his knapsack


    }
}
```

## ⚠️[TLE] Approach - 1 (bruteforce pick and not pick)
```java

public class Solution{

    // Approach - 1 (memoization pick and not pick) 
    // top down dp
    // T : O(2^n) - 2 choices for each of the n cells  
    // S : O(n) -> rec stack 
    private static int solve(int[] weight, int[] value, int index, int remWeightLimit){
        if(index == 0){ // reached last element, and if this weights is <= remLimimit then only we can have its value
            if(weight[0] <= remWeightLimit)
                return value[0];
            return 0; 
        }  

        // pick the current weight only if that will not exceed the limit 
        // i.e the current weight shoudld not be more then the remWeightLimit
        int pick = 0; 
        if(weight[index] <= remWeightLimit){
            pick = value[index] + solve(weight, value, index-1, remWeightLimit - weight[index]);
        }
        int notPick = solve(weight, value, index-1, remWeightLimit);

        // we find maxValuePicked after picking the current weight and not picking as well, now whichever gives us max value we choose that
        return Math.max(pick, notPick);
    }   

    static int knapsack(int[] weight, int[] value, int n, int knapsackWeightLimit) {

        int index = n-1, totalWeightPicked = 0; ;
         
        return solve(weight, value, index, knapsackWeightLimit); // this would return the max total value picked by robber in his knapsack


    }
}
```
