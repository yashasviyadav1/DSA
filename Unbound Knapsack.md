# Unbound Knapsack 

#### Solved at : [Code Studio](https://www.codingninjas.com/studio/problems/unbounded-knapsack_1215029)
Prerequisite : 0 1 Knapsack (bounded knapsack)

`
in bounded knapsack, any element can be picked only ones
in unbounded knapsack, any element can be picked any no of times
`

## ✔️Approach - 4 (Space Optimization)
```java
import java.util.*;
public class Solution {

    // Approach-4 (Space optimization)
    // Time > O(n*limit)  Space : O(2*limit) -> 2 1d arrays
    
    public static int unboundedKnapsack(int n, int knapLimit, int[] value, int[] weight) {
        // limit means  weight limit of knapsack (bag)
        // Tabulation to space optimization
        int[] prev = new int[knapLimit + 1];
        
        for(int L=0; L <= knapLimit; L++){ //base case
            prev[L] = value[0]*(L/weight[0]);
        }

        for(int index=1; index < n; index++){
            int[] curr = new int[knapLimit + 1];
            for(int limit=0; limit <= knapLimit; limit++){
                
                int pick = 0;
                if(weight[index] <= limit) // make sure limit never goes -ve, picked current weight ones, so limit reduces, also add current weights value ones, since its a unbound knapsack so we can use a weight any no of times, in these ques we never move after picking
                    pick = value[index] + curr[limit-weight[index]]; 
                int notPick = prev[limit];
                curr[limit] = Math.max(notPick , pick); // return whichever can take us to larger value 
            }
            prev = curr;
        }

        return prev[knapLimit];
    }
}

```

## ✔️Approach - 3 (Bottom Up DP - tabulation)
```java
import java.util.*;
public class Solution {

    // Approach-3 (bottom up dp, tabulation)
    // Time > O(n*limit)  Space : O(n*limit) -> dp

    public static int unboundedKnapsack(int n, int knapLimit, int[] value, int[] weight) {
        // limit means  weight limit of knapsack (bag)
        int[][] dp = new int[n][knapLimit + 1];
        
        for(int L=0; L <= knapLimit; L++){ //base case
            dp[0][L] = value[0]*(L/weight[0]);
        }

        for(int index=1; index < n; index++){
            for(int limit=0; limit <= knapLimit; limit++){
                
                int pick = 0;
                if(weight[index] <= limit) // make sure limit never goes -ve, picked current weight ones, so limit reduces, also add current weights value ones, since its a unbound knapsack so we can use a weight any no of times, in these ques we never move after picking
                    pick = value[index] + dp[index][limit-weight[index]]; 
                int notPick = dp[index-1][limit];
                dp[index][limit] = Math.max(notPick , pick); // return whichever can take us to larger value 
            }
        }

        return dp[n-1][knapLimit];
    }
}

```

## Approach - 2 (Top Down DP - memoization)
```java
import java.util.*;
public class Solution {

    // Approach -2 (top down dp, memoization)
    // Time > O(n*limit)  Space : O(n*limit) -> dp,rec stack
    
    // this fun returns total value that is pickable 
    private static int solve(int[] value, int[] weight, int[][] dp, int index, int limit){
        if(index == 0){
            // if last wt=4  weightLimit=8 , so here we can pick 8/4 = 2 weights
            // if last wt=4  weightLimit=14 , so here we can pick 14/4= 3 weights
            // if last wt=5  weightLimit=2  , so here we can pick 2/5 = 0 weights 
            return value[index]*(limit/weight[index]); // return the value we picked
        }  
        if(dp[index][limit] != -1) return dp[index][limit]; 

        int pick = 0;
        if(weight[index] <= limit) // make sure limit never goes -ve
            // picked current weight ones, so limit reduces, also add current weights value ones, since its a unbound knapsack so we can use a weight any no of times, in these ques we never move after picking
            pick = value[index] + solve(value, weight, dp, index, limit-weight[index]); 
        int notPick = solve(value, weight, dp, index-1, limit);

        return dp[index][limit] = Math.max(notPick , pick); // return whichever can take us to larger value 
    }
    public static int unboundedKnapsack(int n, int limit, int[] value, int[] weight) {
        // limit means  weight limit of knapsack (bag)
        int[][] dp = new int[n][limit+1];
        for(int[] row:dp) Arrays.fill(row, -1);

        return solve(value, weight, dp, n-1, limit);
    }
}

```

## [TLE] Approach - 1 (bruteforce pick and not pick)
```java
public class Solution {

    // Approach -1 (bruteforce pick and not pick)
    // Time > O(2^n)  Space : O(n)
    // this fun returns total value that is pickable 
    private static int solve(int[] value, int[] weight, int index, int limit){
        if(index == 0){
            // if last wt=4  weightLimit=8 , so here we can pick 8/4 = 2 weights
            // if last wt=4  weightLimit=14 , so here we can pick 14/4= 3 weights
            // if last wt=5  weightLimit=2  , so here we can pick 2/5 = 0 weights 
            return value[index]*(limit/weight[index]); // return the value we picked
        }  

        int pick = 0;
        if(weight[index] <= limit) // make sure limit never goes -ve
            // picked current weight ones, so limit reduces, also add current weights value ones, since its a unbound knapsack so we can use a weight any no of times, in these ques we never move after picking
            pick = value[index] + solve(value, weight, index, limit-weight[index]); 
        int notPick = solve(value, weight, index-1, limit);

        return Math.max(notPick , pick); // return whichever can take us to larger value 
    }
    public static int unboundedKnapsack(int n, int limit, int[] value, int[] weight) {
        return solve(value, weight, n-1, limit);
    }
}

```
