# Frog Jump (DP) 
#### solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/frog-jump_3621012?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf)


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
