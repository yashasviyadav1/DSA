#  Rod cutting problem

#### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/rod-cutting-problem_800284)
prerequisite : unbound knapsack 

## ✔️Approach - 5 (space optimization-2)
```java
import java.util.*;
public class Solution {

	// Approach - 5 (space optimization to single 1d arrays)
	// T: O(n*n)
	// S:O(n) - dp

	public static int cutRod(int price[], int n) {
		

		//  tabulation to space optmization-2
		int[]prev = new int[n+1];
		
		for(int N=0; N <= n; N++){ // base case s2
			prev[N] = N*price[0]; // all index 0 cells filled
		}

		for(int index=1; index < n; index++){ //s3 loop and copy rec
			for(int N=0; N <= n; N++){
				int pick = Integer.MIN_VALUE; // we need to maximize ans
				// currLenofRod should not be more then totalLen needed(to avoid -ve N)
				// 1 based indexing so rodLen of 'index' is index+1
				// picked rodLen, so reqRodLen picees reduce, do not move coz we can pick a pack any no of times
				if((index+1) <= N){
					pick = price[index] + prev[N-(index+1)]; 
				}
				int notPick = prev[N]; // did not pick so move
				prev[N] = Math.max(pick, notPick); // maximize cost
			}
		}

		return prev[n];


	}
}
```

## ✔️Approach - 4 (space optimization-1)
```java
import java.util.*;
public class Solution {

	// Approach - 4 (space optimization to 2 1d arrays)
	// T: O(n*n)
	// S:O(2*n) - dp

	public static int cutRod(int price[], int n) {
		

		//  tabulation to space optmization-1
		int[]prev = new int[n+1];
		
		for(int N=0; N <= n; N++){ // base case s2
			prev[N] = N*price[0]; // all index 0 cells filled
		}

		for(int index=1; index < n; index++){ //s3 loop and copy rec
			int[] curr = new int[n+1];
			for(int N=0; N <= n; N++){
				int pick = Integer.MIN_VALUE; // we need to maximize ans
				// currLenofRod should not be more then totalLen needed(to avoid -ve N)
				// 1 based indexing so rodLen of 'index' is index+1
				// picked rodLen, so reqRodLen picees reduce, do not move coz we can pick a pack any no of times
				if((index+1) <= N){
					pick = price[index] + curr[N-(index+1)]; 
				}
				int notPick = prev[N]; // did not pick so move
				curr[N] = Math.max(pick, notPick); // maximize cost
			}
			prev = curr;
		}

		return prev[n];


	}
}
```

## ✔️Approach - 3 (bottom up dp - tabulation)
```java
import java.util.*;
public class Solution {

	// Approach - 3 (bottom up dp-tabulation)
	// T: O(n*n) ~ O(N)
	// S:O(n*n) - dp

	public static int cutRod(int price[], int n) {
		

		// memoization to tabulation
		int[][] dp = new int[n][n+1];//s1
		
		for(int N=0; N <= n; N++){ // base case s2
			dp[0][N] = N*price[0]; // all index 0 cells filled
		}

		for(int index=1; index < n; index++){ //s3 loop and copy rec
			for(int N=0; N <= n; N++){
				int pick = Integer.MIN_VALUE; // we need to maximize ans
				// currLenofRod should not be more then totalLen needed(to avoid -ve N)
				// 1 based indexing so rodLen of 'index' is index+1
				// picked rodLen, so reqRodLen picees reduce, do not move coz we can pick a pack any no of times
				if((index+1) <= N){
					pick = price[index] + dp[index][N-(index+1)]; 
				}
				int notPick = dp[index-1][N]; // did not pick so move
				dp[index][N] = Math.max(pick, notPick); // maximize cost
			}
		}

		return dp[n-1][n];


	}
}
```

## ✔️Approach - 2 (top down dp - memoization)
```java
import java.util.*;
public class Solution {

	// Approach - 2 (top down dp-memoization)
	// T: O(n*n) ~ O(N)
	// S:O(n) - rec + dp

	// returns max cost obtained after selling 'target' pieces
	private static int solve(int[] price, int[][] dp, int index, int N){
		if(index == 0){
			// index 0 means rodLen is 1 , index 1 means rod length is 2
			// for index0 rodLen=1, so no of rods nedded to make 'N' length will be N rods  
			// so totalprice = N*price[index]
			return N*price[0];
		}
		if(dp[index][N] != -1) return dp[index][N];

		int pick = Integer.MIN_VALUE; // we need to maximize ans
		 // currLenofRod should not be more then totalLen needed(to avoid -ve N)
		 // 1 based indexing so rodLen of 'index' is index+1
		 // picked rodLen, so reqRodLen picees reduce, do not move coz we can pick a pack any no of times
		if((index+1) <= N){
			pick = price[index] + solve(price, dp, index, N-(index+1)); 
		}
		
		int notPick = solve(price, dp, index-1, N); // did not pick so move
		return dp[index][N] = Math.max(pick, notPick); // maximize cost
	}
	public static int cutRod(int price[], int n) {
		int[][] dp = new int[n][n+1];
		for(int[] row:dp) Arrays.fill(row, -1);
		int N = n; // req rod length
		return solve(price, dp, n-1, N);
	}
}
```

## ⚠️[TLE] Approach - 1 (recursive bruteforce) 
```java
public class Solution {

	// Approach - 1 (bruteforce)
	// T: O(2^n) ~ O(N)
	// S:O(n) - rec

	// returns max cost obtained after selling 'target' pieces
	private static int solve(int[] price, int index, int N){
		if(index == 0){
			// index 0 means rodLen is 1 , index 1 means rod length is 2
			// for index0 rodLen=1, so no of rods nedded to make 'N' length will be N rods  
			// so totalprice = N*price[index]
			return N*price[0];
		}

		int pick = Integer.MIN_VALUE; // we need to maximize ans
		 // currLenofRod should not be more then totalLen needed(to avoid -ve N)
		 // 1 based indexing so rodLen of 'index' is index+1
		 // picked rodLen, so reqRodLen picees reduce, do not move coz we can pick a pack any no of times
		if((index+1) <= N){
			pick = price[index] + solve(price, index, N-(index+1)); 
		}
		
		int notPick = solve(price, index-1, N); // did not pick so move
		return Math.max(pick, notPick); // maximize cost
	}
	public static int cutRod(int price[], int n) {
		int N = n; // N is total rod length required
		return solve(price, n-1, N);
	}
}
```
