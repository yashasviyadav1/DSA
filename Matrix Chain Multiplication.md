# Matrix Chain Multiplication

### Solved at : [GFG](https://www.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1)
![Flow - Frame 8](https://github.com/yashasviyadav1/dsa-questions/assets/124666305/edb048d8-c968-46da-bdb4-ed562da4d78a)
![Flow - Frame 9](https://github.com/yashasviyadav1/dsa-questions/assets/124666305/550efe78-e2a2-4b83-b4dc-266bc8038c36)
Why we use this Formula? 
![image](https://github.com/yashasviyadav1/dsa-questions/assets/124666305/c3adf69f-4bfd-4160-af50-eae7ef5e0ab3)

## ✔️Approach - 3 (bottom up dp - tabulation)
running j from i+1 coz i==j is base case and also j is always on right of i
```java
class Solution{
    // Approach -3 (bottom up dp - tabulation)
    // T:O(n*n*n) S:O(N^2 + N) - dp
    
    // returns the min operations/multiplication steps required to do
    // multiplication of all matricies from index i to j
    
    static int matrixMultiplication(int N, int arr[])
    {
        // tabulation
        // 2 changing states i, j both goes from(0 -> N-1) so N spaces
        int[][] dp = new int[N][N];
        // base case
        for(int i=0; i < N; i++)
            dp[i][i] = 0;
        
        // iteration
        for(int i=N-1; i >= 1; i--){
            for(int j=i+1; j < N; j++){ // not from 1 to N-1 coz i should be on left of j always so j starts from i
                // doing partitioning
                // trying all types of partioning and from every one of them choosing the ope that required min steps/operations
                int minOperations = (int)1e9; // minimize
                for(int k=i; k < j; k++){
                    int steps = arr[i-1]*arr[k]*arr[j] + dp[i][k] + dp[k+1][j];
                    minOperations = Math.min(minOperations, steps);
                }
                dp[i][j] = minOperations;
            }
        }
        
        return dp[1][N-1];
    }
}
```
not running j from i+1
```java
// TABULATION - bottom up dp - T:O(n*n*n) S:O(n*n)
class Solution{

    static int matrixMultiplication(int N, int arr[])
    {
        // TABULATION
        int[][] dp = new int[N][N]; 
        
        // base
        for(int x=0; x < N; x++)
            dp[x][x] = 0;
            
        // iteration
        for(int i=N-1; i >= 1; i--){
            for(int j=1; j <= N-1; j++){
                if(i == j) continue; // making sure base case does'nt get overwritten
                int minOperations = (int)1e9;
                for(int k=i; k <= j-1; k++){
                    int operations = arr[i-1]*arr[k]*arr[j] + dp[i][k] + dp[k+1][j];
                    minOperations = Math.min(minOperations, operations);
                }
                dp[i][j] = minOperations;
            }        
        }
        
        return dp[1][N-1];
    }
}
```

## ✔️Approach - 2 (top down dp - memoization)
```java

class Solution{
    // Approach -2 (top dpwm dp - memoization)
    // T:O(n*n*n) S:O(N^2 + N) - rec
    
    // returns the min operations/multiplication steps required to do
    // multiplication of all matricies from index i to j
    private static int MCM(int[] arr, int[][] dp, int i, int j){
        // base case
        if(i == j) return 0; // single matrix can't be multiplied so 0 steps
        if(dp[i][j] != -1) return dp[i][j];
        // doing partitioning
        // trying all types of partioning and from every one of them choosing the ope that required min steps/operations
        int minOperations = (int)1e9; // minimize
        for(int k=i; k < j; k++){
            int steps = arr[i-1]*arr[k]*arr[j] + MCM(arr, dp, i, k) + MCM(arr, dp, k+1, j);
            minOperations = Math.min(minOperations, steps);
        }
        return dp[i][j] = minOperations;
    }
    
    static int matrixMultiplication(int N, int arr[])
    {
        // 2 changing states i, j both goes from(0 -> N-1) so N spaces
        int[][] dp = new int[N][N];
        for(int[] row:dp) Arrays.fill(row, -1);
        return MCM(arr, dp, 1, N-1);
    }
}
```

## ⚠️[TLE] Approach -1 (bruteforce)
```java

class Solution{
    // Approach -1 (BRUTEFORCE)
    // T:exponential S:O(N) - rec
    
    // returns the min operations/multiplication steps required to do
    // multiplication of all matricies from index i to j
    private static int MCM(int[] arr, int i, int j){
        // base case
        if(i == j) return 0; // single matrix can't be multiplied so 0 steps
        // doing partitioning
        // trying all types of partioning and from every one of them choosing the ope that required min steps/operations
        int minOperations = (int)1e9; // minimize
        for(int k=i; k < j; k++){
            int steps = arr[i-1]*arr[k]*arr[j] + MCM(arr, i, k) + MCM(arr, k+1, j);
            minOperations = Math.min(minOperations, steps);
        }
        return minOperations;
    }
    
    static int matrixMultiplication(int N, int arr[])
    {
        return MCM(arr, 1, N-1);
    }
}
```
