# Frog Jump (DP) 
#### solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/frog-jump_3621012?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf)

##✔️⭐ Approach - 3 (recursive bruteforce + dp)
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
