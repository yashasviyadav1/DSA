# Boolean Parenthesization OR Evaluate Boolean Expression to True

### Solved at : [GFG](https://www.geeksforgeeks.org/problems/boolean-parenthesization5610/1)

note : modulo is asked in question due to very large answers

## ✔️Approach - 3 (bottom up dp - tabulation)
```java

//bottom up dp - T:O(n*n*2) S:O(n*n*2)

class Solution{
    static int mod = 1003;
    
    static int countWays(int n, String str){
        
        // tabulation
        int[][][] dp = new int[n][n+1][2]; //+1 coz if i=n-1 j=n so to acces n we need to have n+1 space
                
        // base case
        for(int i=0; i <= n-1; i++){
            for(int j=0; j <= n; j++){
                for(int isTrue=0; isTrue <= 1; isTrue++){
                    if(i > j) dp[i][j][isTrue] = 0; // no char left
                    if(i == j){ // last char
                        if(isTrue == 1) dp[i][j][isTrue] = (str.charAt(i) == 'T')?1:0;
                        else dp[i][j][isTrue] = (str.charAt(i) == 'F')?1:0;
                    }
                }
            }
        }
        
        // iteration
        for(int i=n-1; i >= 0; i--){
            for(int j=i+1; j < n; j++){ // i is always on left of j and i==j is already handled in base case so start frmo j=i+1 
                for(int isTrue=0; isTrue <= 1; isTrue++){
                    int ways=0;
                    for(int k=i+1; k < j; k++){
                        int LT = dp[i][k-1][1];
                        int LF = dp[i][k-1][0];
                        int RT = dp[k+1][j][1];
                        int RF = dp[k+1][j][0];
                        
                        if(str.charAt(k) == '&'){
                            if(isTrue == 1) ways += (LT*RT);
                            else ways += ((LT*RF + LF*RT + LF*RF) % mod);
                        }
                        else if(str.charAt(k) == '|'){
                            if(isTrue == 1) ways += ((LT*RF + LF*RT + LT*RT) % mod);
                            else ways += (LF*RF);
                        }
                        else if(str.charAt(k) == '^'){
                            if(isTrue == 1) ways += ((LT*RF + LF*RT) % mod);
                            else ways += ((LT*RT + LF*RF) % mod);
                        }
                    }
                    dp[i][j][isTrue] = (ways)%mod;
                }
            }
        }
                
        return dp[0][n-1][1];
    }
}
```

## ✔️Approach - 2 (top down dp - memoization)
```java
// Approach -2 (top down dp - memoization) 
// Time : O(n^3) : O(n^3)
class Solution{
    
    static int mod = 1003;
    
    private static int solve(String exp, int[][][] dp, int i, int j, int isTrue){
        if(i > j) return 0; // no expression so no way it gives true
        if(i == j){// single char expression
            if(isTrue == 1) return (exp.charAt(i) == 'T')?1:0; // T req ans we have T so return 1 (1 way found)
            else return (exp.charAt(i) == 'F')?1:0; // F required and char is F so return 1 (1 way)
        }
        if(dp[i][j][isTrue] != -1) return dp[i][j][isTrue];
        
        // we need to iterate on all the bit operators in the expression which are at alternative positions
        // and for each operator choose it and find the 'LT' no of ways in which left part can give us True, 'LF' left false
        // RT - no of ways in whichRight part gives us True, no of ways in which right part gives false
        //       i   j
        // exp = T|F&T eg take this at ith position is the boolean, so operator is at i+1 th position
        int ways = 0; // no of ways in which we can have 'isTrue' from curr expression
        for(int k=i+1; k <= j-1; k = k+2){
            
            int LT = solve(exp, dp, i, k-1, 1);
            int LF = solve(exp, dp, i, k-1, 0); // no of ways in which left part can give us false (0)
            int RT = solve(exp, dp, k+1, j, 1);
            int RF = solve(exp, dp, k+1, j, 0);
            
            // T&T = T   T&F = F  F&T = F  F&F = F
            if(exp.charAt(k) == '&'){
                if(isTrue == 1) ways +=  ((LT*RT) % mod); 
                else ways += ((LT*RF + LF*RT + LF*RF) % mod); // no of ways in which we can have _&_ => F 
            }
            // T|T = T   T|F = T   F|T = T  F|F = F
            else if(exp.charAt(k) == '|'){
                if(isTrue == 1) ways += ((LT*RT + LT*RF + LF*RT) % mod);
                else ways += ((LF*RF) % mod);
            }
            // T^T = F   T^F = T   F^T = T   F^F = F
            else if(exp.charAt(k) == '^'){
                if(isTrue == 1) ways += ((LT*RF + LF*RT) % mod);
                else ways += ((LF*RF + LT*RT) % mod);
            }
        }
        
        return dp[i][j][isTrue] = (ways)%mod;
    }
    static int countWays(int n, String exp){
        int i=0, j = n-1;
        int isTrue = 1;
        int[][][] dp = new int[n][n][2];
        for(int[][] twoD:dp)
            for(int[] row:twoD)
                Arrays.fill(row, -1);
                
        // this means total no of ways expression starting from i to j gives us output as True
        return solve(exp, dp, i, j, isTrue); 
    }
}

```

## ⚠️[TLE] Approach - 1 (bruteforce) 
```java


//User function Template for Java

// Approach -1  
// bruteforce
// Time : exponential Space : O(n)
class Solution{
    private static int solve(String exp, int i, int j, int isTrue){
        if(i > j) return 0; // no expression so no way it gives true
        if(i == j){// single char expression
            if(isTrue == 1) return (exp.charAt(i) == 'T')?1:0; // T req ans we have T so return 1 (1 way found)
            else return (exp.charAt(i) == 'F')?1:0; // F required and char is F so return 1 (1 way)
        }
        
        // we need to iterate on all the bit operators in the expression which are at alternative positions
        // and for each operator choose it and find the 'LT' no of ways in which left part can give us True, 'LF' left false
        // RT - no of ways in whichRight part gives us True, no of ways in which right part gives false
        //       i   j
        // exp = T|F&T eg take this at ith position is the boolean, so operator is at i+1 th position
        int ways = 0; // no of ways in which we can have 'isTrue' from curr expression
        for(int k=i+1; k <= j-1; k = k+2){
            
            int LT = solve(exp, i, k-1, 1);
            int LF = solve(exp, i, k-1, 0); // no of ways in which left part can give us false (0)
            int RT = solve(exp, k+1, j, 1);
            int RF = solve(exp, k+1, j, 0);
            
            // T&T = T   T&F = F  F&T = F  F&F = F
            if(exp.charAt(k) == '&'){
                if(isTrue == 1) ways +=  (LT*RT); 
                else ways += (LT*RF + LF*RT + LF*RF); // no of ways in which we can have _&_ => F 
            }
            // T|T = T   T|F = T   F|T = T  F|F = F
            else if(exp.charAt(k) == '|'){
                if(isTrue == 1) ways += (LT*RT + LT*RF + LF*RT);
                else ways += (LF*RF);
            }
            // T^T = F   T^F = T   F^T = T   F^F = F
            else if(exp.charAt(k) == '^'){
                if(isTrue == 1) ways += (LT*RF + LF*RT);
                else ways += (LF*RF + LT*RT);
            }
        }
        
        return ways;
    }
    static int countWays(int n, String exp){
        int i=0, j = n-1;
        int isTrue = 1;
        
        // this means total no of ways expression starting from i to j gives us output as True
        return solve(exp, i, j, isTrue); 
    }
}
```
