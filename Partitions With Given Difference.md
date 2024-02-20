#  Partitions With Given Difference

#### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/partitions-with-given-difference_3751628)
prerequisites : subset with k sum, subset with min diff

## ✔️Approach - 4 (tabulation + space optimization)
```java
import java.util.* ;
import java.io.*; 
public class Solution {
	// Approach -4  (bottom up dp - tabulation + SPACE OPTMIZATION)
	// T : O(n*targetSum)   Space : O(2*targetSum) - only dp space

	static int MOD = 1000000000 + 7; // 10^9 + 7 (req in que)

	public static int countPartitions(int n, int diff, int[] arr) {	

		// given that both partitions combined to form arr i.e union
		// so, sum1 - sum2 = diff(given) 
		// totalsum - sum2 - sum2 = diff
		// sum2 = (totalSum-diff)/2  
		// our que is not reduced to find no of partitions with sum == (totalSum-diff)/2  
		int totalSum = 0;
		for(int ele:arr) totalSum += ele;

		// edge cases diff=10 {0 0 3 6}
		if(diff > totalSum) return 0;
		// edge case -> totalSum - d should not be odd (coz all elements are here ints so sum of ints cant be decimal)
		if((totalSum - diff) % 2 != 0) return 0;

		int targetSum = (totalSum - diff)/2;  // if we find a partition with 'targetSum' then that parition will surely have 'diff' with the other partition
		

		// tabulation to space opimization

		int[] prev = new int[targetSum + 1];  //target = 0 to targetSum

		//base cases to dp
		if(arr[0] == 0)
			prev[0] = 2; // 1st case from memo - target already achieved and last ele is 0, 2 subsets 
		else prev[0] = 1;  // 2nd case from memo - target alrady achieved and last ele not 0, 1 subset

		if(arr[0] != 0 && arr[0] <= targetSum) // old base case - arr[0] != 0 is there for cases like {0}
			prev[arr[0]] = 1;

		// rest for remaining index=0 cells it is already 0

		for(int index=1; index<n; index++){ // 0 already calculated
			int[] curr = new int[targetSum+1];
			for(int target=0; target<=targetSum; target++){
	
				// find noOfPartitions possible by picking and not picking the current element
				int pick = 0; 
				if(arr[index] <= target)// pick cur ele only if that will not make target -ve
					pick = prev[target-arr[index]];
				int notPick = prev[target];

				curr[target] = (pick + notPick)%MOD;// return all noOfPartitions
	
			}
			prev = curr;
		} 

		return prev[targetSum];
		
	}
}
```
## ✔️Approach - 3 (bottom up tabulation - dp)
```java
import java.util.* ;
import java.io.*; 
public class Solution {
	// Approach -3  (bottom up dp - tabulation)
	// T : O(n*targetSum)   Space : O(n*targetSum) - only dp space

	static int MOD = 1000000000 + 7; // 10^9 + 7 (req in que)

	public static int countPartitions(int n, int diff, int[] arr) {	

		// given that both partitions combined to form arr i.e union
		// so, sum1 - sum2 = diff(given) 
		// totalsum - sum2 - sum2 = diff
		// sum2 = (totalSum-diff)/2  
		// our que is not reduced to find no of partitions with sum == (totalSum-diff)/2  
		int totalSum = 0;
		for(int ele:arr) totalSum += ele;

		// edge cases diff=10 {0 0 3 6}
		if(diff > totalSum) return 0;
		// edge case -> totalSum - d should not be odd (coz all elements are here ints so sum of ints cant be decimal)
		if((totalSum - diff) % 2 != 0) return 0;

		int targetSum = (totalSum - diff)/2;  // if we find a partition with 'targetSum' then that parition will surely have 'diff' with the other partition
		

		// memoization to tabulation
		// step 1 : dp
		int[][] dp = new int[n][targetSum + 1]; // index -> 0 to n-1    target = 0 to targetSum

		// step 2 : set base cases to dp
		if(arr[0] == 0)
			dp[0][0] = 2; // 1st case from memo - target already achieved and last ele is 0, 2 subsets 
		else dp[0][0] = 1;  // 2nd case from memo - target alrady achieved and last ele not 0, 1 subset

		if(arr[0] != 0 && arr[0] <= targetSum) // old base case - arr[0] != 0 is there for cases like {0}
			dp[0][arr[0]] = 1;

		// rest for remaining index=0 cells it is already 0

		for(int index=1; index<n; index++){ // 0 already calculated
			for(int target=0; target<=targetSum; target++){
	
				// find noOfPartitions possible by picking and not picking the current element
				int pick = 0; 
				if(arr[index] <= target)// pick cur ele only if that will not make target -ve
					pick = dp[index-1][target-arr[index]];
				int notPick = dp[index-1][target];

				dp[index][target] = (pick + notPick)%MOD;// return all noOfPartitions
	
			}
		} 

		return dp[n-1][targetSum];
		
	}
}
```

## ✔️Approach - 2 (top down memoization - dp)
```java
import java.util.* ;
import java.io.*; 
public class Solution {
	// Approach -2  (Top down dp-memoization)
	// T : O(n*targetSum)   Space : O(n*targetSum)

	static int MOD = 1000000000 + 7; // 10^9 + 7 (req in que)
	private static int countPart(int[] arr, int[][] dp, int index, int target){

		// the prev test case (target == 0) return 1 was not able to handle some edge cases like when we had 0s in array it doesnt count them
		// coz whever target achieved that base case would return failed for{0,0,1} 
		// what we do is since 0 might also be in our array, we will now check if the target is achieved or not only at the end of array

		if(index == 0){ // reached the end of array
			// target is achieved and curr element is 0, then we we have 1 partition (without 0) and 2nd partition (with 0) so basically 2 partitions possibles with targetSum 
			// target is achievable by picking this element or target is already achieved then return 1
 			// reached end and target not achieved
			if(target == 0 && arr[0] == 0) return 2; 
			if(target == 0 || target == arr[0]) return 1; 
			return 0;
		}
		if(dp[index][target] != -1) return dp[index][target];
		
		// find noOfPartitions possible by picking and not picking the current element
		int pick = 0; 
		if(arr[index] <= target)// pick cur ele only if that will not make target -ve
			pick = countPart(arr, dp, index-1, target-arr[index]);
		int notPick = countPart(arr, dp, index-1, target);

		return dp[index][target] = (pick + notPick)%MOD;// return all noOfPartitions
	} 
	public static int countPartitions(int n, int diff, int[] arr) {
		
		// given that both partitions combined to form arr i.e union
		// so, sum1 - sum2 = diff(given) 
		// totalsum - sum2 - sum2 = diff
		// sum2 = (totalSum-diff)/2  
		// our que is not reduced to find no of partitions with sum == (totalSum-diff)/2  
		int totalSum = 0;
		for(int ele:arr) totalSum += ele;

		// edge cases diff=10 {0 0 3 6}
		if(diff > totalSum) return 0;
		// edge case -> totalSum - d should not be odd (coz all elements are here ints so sum of ints cant be decimal)
		if((totalSum - diff) % 2 != 0) return 0;

		int targetSum = (totalSum - diff)/2;  // if we find a partition with 'targetSum' then that parition will surely have 'diff' with the other partition
		
		int[][] dp = new int[n][targetSum + 1]; // index -> 0 to n-1    target = 0 to targetSum
		for(int[] row:dp) Arrays.fill(row, -1);
		return countPart(arr, dp, n-1, targetSum);
		
	}
}
```

## Approach -1 (bruteforce - pick and notpick)
```java
import java.util.* ;
import java.io.*; 
public class Solution {
	// Approach -1 (bruteforce - pick,notpick)
	// T : O(2^n)   Space : O(n)

	static int MOD = 1000000000 + 7;
	private static int countPart(int[] arr, int index, int target){

		// the prev test case (target == 0) return 1 was not able to handle some edge cases like when we had 0s in array it doesnt count them
		// coz whever target achieved that base case would return failed for{0,0,1} 
		// what we do is since 0 might also be in our array, we will now check if the target is achieved or not only at the end of array

		if(index == 0){ // reached the end of array
			// target is achieved and curr element is 0, then we we have 1 partition (without 0) and 2nd partition (with 0) so basically 2 partitions possibles with targetSum 
			// target is achievable by picking this element or target is already achieved then return 1
 			// reached end and target not achieved
			if(target == 0 && arr[0] == 0) return 2; 
			if(target == 0 || target == arr[0]) return 1; 
			return 0;
		}
		
		// find noOfPartitions possible by picking and not picking the current element
		int pick = 0; 
		if(arr[index] <= target)// pick cur ele only if that will not make target -ve
			pick = countPart(arr, index-1, target-arr[index]);
		int notPick = countPart(arr, index-1, target);

		return (pick + notPick)%MOD;// return all noOfPartitions
	} 
	public static int countPartitions(int n, int diff, int[] arr) {
		
		// given that both partitions combined to form arr i.e union
		// so, sum1 - sum2 = diff(given) 
		// totalsum - sum2 - sum2 = diff
		// sum2 = (totalSum-diff)/2  
		// our que is not reduced to find no of partitions with sum == (totalSum-diff)/2  
		int totalSum = 0;
		for(int ele:arr) totalSum += ele;

		// edge cases diff=10 {0 0 3 6}
		if(diff > totalSum) return 0;
		// edge case -> totalSum - d should not be odd (coz all elements are here ints so sum of ints cant be decimal)
		if((totalSum - diff) % 2 != 0) return 0;

		int targetSum = (totalSum - diff)/2;  // if we find a partition with 'targetSum' then that parition will surely have 'diff' with the other partition
		return countPart(arr, n-1, targetSum);
		
	}
}
```
