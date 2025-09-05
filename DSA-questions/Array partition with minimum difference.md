#  Array partition with minimum difference

#### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494)
```
explanation :
we need to partition array such that the diff of the 2 subsets is mimnimum
so what dp[index][target] gives is whether there exists a subset in array from 0 to n-1 which has a sum == 'target'
so if we find out partition1 sum we can easily find out partition2 sum by substracting it from the totalSum of array
so lets loop the n-1th index of dp[][] coz dp[n-1] dels with complete array 
we loop the last row and wherever we find that a sum is possible then we try to minimize the diff of 2 partitions 
```

## ✔️⭐Approach - 2 (Tabulation + SpaceOptimizaiton + partitionWithKSum logic)
```java
class Solution{
	public int minDifference(int arr[], int n) 
	{ 
	    int totalSum = 0;
	    for(int ele:arr) totalSum += ele;
	    
	    boolean[] prev = new boolean[totalSum + 1]; // max possible sum of partition can be 'totalSum' and min can be 0
	    // using the subset with sum k logic
	    // to find all possible subset1 sum from 0 to totalSum
	    // base cases, if we have only 1 element then target can be achieved if ele==target target==0
	    prev[0] = true;
	    if(arr[0] <= totalSum)
	        prev[arr[0]] = true;
	        
	   // filling the dp table 
	    for(int index=1; index < n; index++){
	        boolean[] curr = new boolean[totalSum + 1];
	        
	        for(int target=0; target <= totalSum; target++){
	            boolean pick = false;
	            if(arr[index] <= target)
	                pick = prev[target-arr[index]];
	            boolean notPick = prev[target];
	            curr[target] = pick || notPick;
	        }
	        prev = curr; 
	    }
	    
	    // minimizing the diff of 2 subsets
	    // since we have ans for whole array in last row
	    int lastRow = n-1;
	    int minDiff = Integer.MAX_VALUE;
	    for(int sum=0; sum <= totalSum; sum++){
	        if(prev[sum] == true) // subset 1 is possible with 'sum'
	        {
	            int part1Sum = sum;
	            int part2Sum = totalSum - part1Sum;
	            int diff = Math.abs(part1Sum-part2Sum);
	            minDiff = Math.min(diff, minDiff);
	        }
	    }
	    
	    return minDiff;
	} 
}
```

## ⭐✔️Approach - 1 (Tabulation + partitionWithKSum logic)
```java


//User function Template for Java

class Solution
{
    // bottom up dp (tabulation)
    // Time : O(n*sum)  Space : O(n*sum)
    // idea : we need to find the min Absolute difference of 2 subsets sum
    // so single partition can have sum in range 0 to 'totalSum of all ele',
    //  we can create a dp table using subset with k sum approach
    // then for all sums from range 0 to totalSum we find the sums which is possible with a partition
    // whichever sum is possible i find the part2 sum then minimize the absolute difference
    

	public int minDifference(int arr[], int n) 
	{ 
	    int totalSum = 0;
	    for(int ele:arr) totalSum += ele;
	    
	    boolean[][] dp = new boolean[n][totalSum + 1]; // max possible sum of partition can be 'totalSum' and min can be 0
	    // using the subset with sum k logic
	    // to find all possible subset1 sum from 0 to totalSum
	    // base cases, if we have only 1 element then target can be achieved if ele==target target==0
	    dp[0][0] = true;
	    if(arr[0] <= totalSum)
	        dp[0][arr[0]] = true;
	        
	   // filling the dp table 
	    for(int index=1; index < n; index++){
	        for(int target=0; target <= totalSum; target++){
	            boolean pick = false;
	            if(arr[index] <= target)
	                pick = dp[index-1][target-arr[index]];
	            boolean notPick = dp[index-1][target];
	            dp[index][target] = pick || notPick;
	        }
	    }
	    
	    // minimizing the diff of 2 subsets
	    // since we have ans for whole array in last row
	    int lastRow = n-1;
	    int minDiff = Integer.MAX_VALUE;
	    for(int sum=0; sum <= totalSum; sum++){
	        if(dp[lastRow][sum] == true) // subset 1 is possible with 'sum'
	        {
	            int part1Sum = sum;
	            int part2Sum = totalSum - part1Sum;
	            int diff = Math.abs(part1Sum-part2Sum);
	            minDiff = Math.min(diff, minDiff);
	        }
	    }
	    
	    return minDiff;
	} 
}
```
