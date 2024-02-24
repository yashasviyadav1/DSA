#  0 1 Knapsack 

#### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/0-1-knapsack_920542)

## ✔️Approach - 2 (Top down dp - memoization)
```java
import java.util.* ;
import java.io.*; 

public class Solution{

    // Approach - 1 (memoization pick and not pick) 
    // top down dp
    // T : O(n*knapSackLimit) 
    // S : O(n*knapSackLimit) -> rec stack + dp
    private static int solve(int[] weight, int[] value, int knapsackWeightLimit, int[][] dp, int index, int totalWeightPicked){
        if(index < 0) // no weight exists so cant pick any value
            return 0;
        if(dp[index][totalWeightPicked] != -1) return dp[index][totalWeightPicked];
        
        // if current weight is picked and will not exceed the knapsack weight limit than only pick the current weight
        int pick = 0; // stores the total value that robber can pick after chooseign the curr weight as well
        if(totalWeightPicked + weight[index] <= knapsackWeightLimit){
            pick = value[index] + solve(weight, value, knapsackWeightLimit, dp, index-1, totalWeightPicked + weight[index]);
        }
        
        int notPick = solve(weight, value, knapsackWeightLimit, dp, index-1, totalWeightPicked);

        return dp[index][totalWeightPicked] = Math.max(pick, notPick);
    }

    static int knapsack(int[] weight, int[] value, int n, int knapsackWeightLimit) {

        int index = n-1, totalWeightPicked = 0; 
        
        // we can not pick weight more than the knapsack limit so totalweightpicked goes form 0 to totalSum 
        // dp[index][totalWeightPicked]  
        int[][] dp = new int[n][knapsackWeightLimit + 1]; // +1 coz if limit is 10 then totalweightpicked can be 10 as well
        for(int[] row:dp) Arrays.fill(row, -1);
         
        return solve(weight, value, knapsackWeightLimit, dp, index, totalWeightPicked); // this would return the max total value picked by robber in his knapsack

    }
}
```

## ⚠️[TLE] Approach - 1 (bruteforce pick and not pick)

```java
import java.util.* ;
import java.io.*; 

public class Solution{
    private static int solve(int[] weight, int[] value, int knapsackWeightLimit, int index, int totalWeightPicked){
        if(index < 0) // no weight exists so cant pick any value
            return 0;
        
        // if current weight is picked and will not exceed the knapsack weight limit than only pick the current weight
        int pick = 0; // stores the total value that robber can pick after chooseign the curr weight as well
        if(totalWeightPicked + weight[index] <= knapsackWeightLimit){
            pick = value[index] + solve(weight, value, knapsackWeightLimit, index-1, totalWeightPicked + weight[index]);
        }
        
        int notPick = solve(weight, value, knapsackWeightLimit, index-1, totalWeightPicked);

        return Math.max(pick, notPick);
    }

    static int knapsack(int[] weight, int[] value, int n, int knapsackWeightLimit) {

        int index = n-1, totalWeightPicked = 0; 
        return solve(weight, value, knapsackWeightLimit, index, totalWeightPicked); // this would return the max total value picked by robber in his knapsack

    }
}
```
