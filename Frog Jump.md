# Frog Jump (DP) 
#### solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/frog-jump_3621012?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf)

## Approach - 4.1 (Tabulation + space optimisation)
```java
import java.util.* ;
import java.io.*; 
public class Solution {

/*
    Approach - 4.1 (Tabulation + Space Optimization)
    T : O(n)
    S : O(1)  
*/
    private static int minEnergyReqTab(int[] heights, int n){

        int prev2 = 0; // base 
        int prev1 = 0;  // these are indices 

        // now dp will be executed for 1,2,3...n
        for(int index = 1; index < n; index++){
            
            int energyConsume1 = prev1 + Math.abs(heights[index] - heights[index-1]);
            int energyConsume2 = Integer.MAX_VALUE;
            
            if(index > 1) // do not take 2nd jump from index < 2
                energyConsume2 = prev2 + Math.abs(heights[index] - heights[index - 2]);

            int curr = Math.min(energyConsume1, energyConsume2);
            prev2 = prev1;
            prev1 = curr;
        }

        // we need to find min total energy req for (n-1)th step
        return prev1;
    }


    public static int frogJump(int n, int heights[]) {

        return minEnergyReqTab(heights, n);
    }

}
```
## Approach - 4 (Tabulation or bottom up dp)
```java
import java.util.* ;
import java.io.*; 
public class Solution {

/*
    Approach - 4 (Tabulation or Bottom up approach)
    T : O(n)
    S : O(n) - only dp space
*/
    private static int minEnergyReqTab(int[] heights, int n){

        int[] dp = new int[n];
        Arrays.fill(dp, -1);
        dp[0] = 0; // base 

        // now dp will be executed for 1,2,3...n
        for(int index = 1; index < n; index++){
            
            int energyConsume1 = dp[index-1] + Math.abs(heights[index] - heights[index-1]);
            int energyConsume2 = Integer.MAX_VALUE;
            if(index > 1) // do not take 2nd jump from index < 2
                energyConsume2 = dp[index - 2] + Math.abs(heights[index] - heights[index - 2]);

            dp[index] = Math.min(energyConsume1, energyConsume2);
        }

        // we need to find min total energy req for (n-1)th step
        return dp[n - 1];
    }


    public static int frogJump(int n, int heights[]) {
        
        return minEnergyReqTab(heights, n);
    }

}

```
## ✔️⭐ Approach - 3 (recursive bruteforce + dp)

java code :- 
```java
import java.util.* ;
import java.io.*; 
public class Solution {

    private static int minEnergyReq(int n, int[] dp, int[] heights){
        if(n == 0) return 0; // to reach index 0 there is no energy consume
        if(dp[n] != -1) return dp[n];

        // to reach nth stair
        int energyConsume1 = minEnergyReq(n-1, dp, heights) + Math.abs(heights[n] - heights[n-1]);
        
        int energyConsume2 = Integer.MAX_VALUE;
        if(n > 1) // do not take 2nd jump from index < 2
            energyConsume2 = minEnergyReq(n-2, dp, heights) + Math.abs(heights[n] - heights[n-2]);

        // choose the way which will consume less energy
        return dp[n] = Math.min(energyConsume1, energyConsume2);

    }
    public static int frogJump(int n, int heights[]) {
        // there are n steps and we need to reach n-1 so find ans for n-1 so we need dp of size n
        int[] dp = new int[n];
        Arrays.fill(dp, -1);
        
        return minEnergyReq(n-1, dp, heights); 
    }

}
```
C++ code :- 
```cpp
#include <bits/stdc++.h> 
using namespace std;
/* ✔️⭐Approach - 3 (bruteforce + dp)

    idea : to find the min energy used to reach nth stair, we first need to find min energy used to reach n-1th stair and n-2th stair,
            then find if which of the stairs (n-1 or n-2)th takes less energy to reach nth stair
            every time we find solution for lets say nth stair we would store it in the dp array, so that we do not have to calculate again
            
    Time : O(n)
    Space : O(n)
*/

int minEnergyUsedToReach(int n, vector<int> &heights, vector<int> &dp){

    // base case - to reach 1st stair no enevry used (coz we already at that)
    if(n == 1) return 0;
    if(n == 2) return abs(heights[0] - heights[1]);

    if(dp[n] != -1)  // ans already calculated for nth stair
        return dp[n];

    // to reach nth stair first find minEnergyUsed to reach n-1 th and n-2 th stair, then find which will take least energy to reach the nth stair 
    return dp[n] = min(
        (minEnergyUsedToReach(n-1, heights, dp) + abs(heights[n-1] - heights[n-2]) ),
        (minEnergyUsedToReach(n-2, heights, dp) + abs(heights[n-1] - heights[n-3]) )
    );
}

int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n+1, -1);
    return minEnergyUsedToReach(n, heights, dp);
}


```

## ⚠️[TLE] Approach - 2  (recursive bruteforce)
```cpp
#include <bits/stdc++.h> 
using namespace std;

/* ⚠️Approach - 2 (bruteforce)

    idea : to find the min energy used to reach nth stair, we first need to find min energy used to reach n-1th stair and n-2th stair,
            then find if which of the stairs (n-1 or n-2)th takes less energy to reach nth stair


    T : O(2^n)
    S : O(n)

*/

int frogJump(int n, vector<int> &heights)
{
    // base case - to reach 1st stair no enevry used (coz we already at that)
    if(n == 1) return 0;
    if(n == 2) return abs(heights[0] - heights[1]);

    // to reach nth stair first find minEnergyUsed to reach n-1 th and n-2 th stair, then find which will take least energy to reach the nth stair 
    return min(
        (frogJump(n-1, heights) + abs(heights[n-1] - heights[n-2]) ),
        (frogJump(n-2, heights) + abs(heights[n-1] - heights[n-3]) )
    );
}

```

## [TLE] ✔️⚠️Approach - 1 (bruteforce based on choices) 
```cpp
#include <bits/stdc++.h> 
using namespace std;

void solve(int n, vector<int> &heights, int currStair, int currEnergyUsed, int &finalMinTotalEnergy){

    // base case - if reached nth stair and energy used is lesser then 'min' then update the result 
    if(currStair > n) return;
    if(currStair == n){
        if(finalMinTotalEnergy > currEnergyUsed)
            finalMinTotalEnergy = currEnergyUsed;
        return;
    }

    // we have 2 choices, either take 1 step or take 2 step
    int newCurrEnergyUsed = currEnergyUsed + abs(heights[currStair-1] - heights[currStair]); // jumping currStair --> currStair + 1 
    solve(n, heights, currStair + 1, newCurrEnergyUsed, finalMinTotalEnergy);    
    newCurrEnergyUsed = currEnergyUsed + abs(heights[currStair-1] - heights[currStair + 1]); // jumping currStair --> currStair + 2
    solve(n, heights, currStair + 2, newCurrEnergyUsed, finalMinTotalEnergy);

}

int frogJump(int n, vector<int> &heights)
{
    int currEnergyUsed = 0;
    int finalMinTotalEnergy = INT_MAX; // minimize this
    int currStair = 1;

    solve(n, heights, currStair, currEnergyUsed, finalMinTotalEnergy);
    
    return finalMinTotalEnergy;
}
```
