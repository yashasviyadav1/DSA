#  Ninja’s Training

## Solved at : [Code Studio](https://www.codingninjas.com/studio/problems/ninja-s-training_3621003?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos)

## ⭐✔️Approach - 3 (Space optimisation)
```java
import java.util.*;
public class Solution {

    /*  Tabulation  + space optimization

        T : O(n)
        S : O(4) 

    */
    private static int solve(int[][] points, int[][] dp, int currDay, int prevPerformed){
        // last day
        if(currDay < 0) return 0;
        
        if(dp[currDay][prevPerformed] != -1) return dp[currDay][prevPerformed];

        // we are on some day, explore all the tasks of that day cols (tasks)
        int maxi = 0;
        for(int task=0; task < 3; task++){ 
            if(task == prevPerformed) // cant perform
                continue;
            maxi = Math.max(maxi, points[currDay][task] + solve(points,dp, currDay-1, task)); // curr task becomes the new prev for next one 
        }
        return dp[currDay][prevPerformed] = maxi;
    }

    
    public static int ninjaTraining(int n, int points[][]) {

        // memoisation
        // there are 2 changing parameters so to store state we need 2d dp
        // but since for computing each row of dp we only need its prev row so we can space optimize
        int[] prev = new int[4]; 
        for(int j=0; j < 4; j++)
                prev[j] = -1;

        //base cases ->  currDay=0
        // for day-0 if prev = 1 then  dp[0][1] will have max of merits of cell(0,0) and cell(0,2) 
        prev[0] = Math.max(points[0][1], points[0][2]);        
        prev[1] = Math.max(points[0][0], points[0][2]);         
        prev[2] = Math.max(points[0][0], points[0][1]); 
        prev[3] = Math.max(points[0][0], Math.max(points[0][1], points[0][2])); // means no task is done preveously 

        // step 3 - since we have ans for day0 we start from 1 till end
        for(int currDay=1; currDay < points.length; currDay++){
            int[] dp = new int[4]; // we are computing this
            for(int prevPerformed = 0; prevPerformed <= 3; prevPerformed++){
                int maxi = 0;
                // copy memo code and replace fun with dp
                for(int task=0; task < 3; task++){ 
                    if(task == prevPerformed) // cant perform
                        continue;
                    dp[prevPerformed] = Math.max( dp[prevPerformed], points[currDay][task] + prev[task]); // curr task becomes the new prev for next one 
                }
            }

            // imp shifting
            prev = dp;
        }
    
        return prev[3];

    }

}
```
## ✔️⭐Approach - 2 (tabulation , bottom up dp)
```java
import java.util.*;
public class Solution {

    /*  Tabulation 

        T : O(n)
        S : O(n) - no rec stack

    */
    private static int solve(int[][] points, int[][] dp, int currDay, int prevPerformed){
        // last day
        if(currDay < 0) return 0;
        
        if(dp[currDay][prevPerformed] != -1) return dp[currDay][prevPerformed];

        // we are on some day, explore all the tasks of that day cols (tasks)
        int maxi = 0;
        for(int task=0; task < 3; task++){ 
            if(task == prevPerformed) // cant perform
                continue;
            maxi = Math.max(maxi, points[currDay][task] + solve(points,dp, currDay-1, task)); // curr task becomes the new prev for next one 
        }
        return dp[currDay][prevPerformed] = maxi;
    }

    
    public static int ninjaTraining(int n, int points[][]) {

        // memoisation
        // there are 2 changing parameters so to store state we need 2d dp
        int[][] dp = new int[n][4]; // dp[currDay][lastPerformed]
        for(int i=0; i < n; i++)
            for(int j=0; j < 4; j++)
                dp[i][j] = -1;

        //base cases ->  currDay=0
        // for day-0 if prev = 1 then  dp[0][1] will have max of merits of cell(0,0) and cell(0,2) 
        dp[0][0] = Math.max(points[0][1], points[0][2]);        
        dp[0][1] = Math.max(points[0][0], points[0][2]);         
        dp[0][2] = Math.max(points[0][0], points[0][1]); 
        dp[0][3] = Math.max(points[0][0], Math.max(points[0][1], points[0][2])); // means no task is done preveously 

        // step 3 - since we have ans for day0 we start from 1 till end
        for(int currDay=1; currDay < points.length; currDay++){
            for(int prevPerformed = 0; prevPerformed <= 3; prevPerformed++){
                int maxi = 0;
                // copy memo code and replace fun with dp
                for(int task=0; task < 3; task++){ 
                    if(task == prevPerformed) // cant perform
                        continue;
                    maxi = Math.max(maxi, points[currDay][task] + dp[currDay-1][task]); // curr task becomes the new prev for next one 
                }
                dp[currDay][prevPerformed] = maxi;
            }
        }
    
        int lastDay = points.length-1;
        return dp[lastDay][3];

    }

}

```

## ✔️⭐Approach - 1 (Top down dp, Memoization)
```java
import java.util.*;
public class Solution {

    /*  topDown dp
         |-------tasks
    days |
         |
            2 changing states 
            Time : (n*4*3)
            Space : O(n*4)

    */
    private static int solve(int[][] points, int[][] dp, int currDay, int prevPerformed){
        // last day
        if(currDay < 0) return 0;
        
        if(dp[currDay][prevPerformed] != -1) return dp[currDay][prevPerformed];

        // we are on some day, explore all the tasks of that day cols (tasks)
        int maxi = 0;
        for(int task=0; task < 3; task++){ 
            if(task == prevPerformed) // cant perform
                continue;
            maxi = Math.max(maxi, points[currDay][task] + solve(points,dp, currDay-1, task)); // curr task becomes the new prev for next one 
        }
        return dp[currDay][prevPerformed] = maxi;
    }
    public static int ninjaTraining(int n, int points[][]) {

        // task tange is 0 to 2
        int prevPerformed = 3; // means no task is performed yey

        // there are 2 changing parameters so to store state we need 2d dp
        int[][] dp = new int[n][4]; // dp[currDay][lastPerformed]
        for(int i=0; i < n; i++)
            for(int j=0; j < 4; j++)
                dp[i][j] = -1;

        return solve(points, dp, n-1 ,prevPerformed); 
    }

}
```
