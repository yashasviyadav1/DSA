#  Array partition with minimum difference

#### Solved at : [CodeStudio](https://www.codingninjas.com/studio/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494)

## ⭐✔️Approach - 1 (Tabulation + partitionWithKSum logic)
```java
public class Solution {
/*  Approach - 1 (Tabulation + partitionWithKSum logic)
     prerequisite partitionWithKSum
        explanation : we need to partition array such that the diff of the 2 subsets is mimnimum
                      so what dp[index][target] gives is whether there exists a subset in array from 0 to n-1 which has a sum == 'target'
                      so if we find out partition1 sum we can easily find out partition2 sum by substracting it from the totalSum of array
                      so lets loop the n-1th index of dp[][] coz dp[n-1] dels with complete array 
                      we loop the last row and wherever we find that a sum is possible then we try to minimize the diff of 2 partitions 
        
    time : O(n*totalSum)
    Space : O(n*totalSum)
*/
    public static int minSubsetSumDifference(int []arr, int n) {
        // lets first apply the partition With k sum logic
        // note in this question only the tabulation of the partition with k sum will be used not the memoization (coz here we need the last row of dp)
        int totalSum = 0;
        for(int ele:arr) totalSum += ele;

        int k = totalSum;
        // min sum a partition can have is 0 to totalSum 
        boolean[][] dp = new boolean[n][k+1]; // here dp[index][targetSum] , dp[i][k] means in array from index 0 to i can we make a partition with k sum
        
        // base cases
        //if target is 0 it is achieved
        for(int index = 0; index < n; index++)
            dp[index][0] = true;
        // if index 0's element == target means its is achieved
        // means for array with only 0 index (single ele array) only 'target' is achieved when that element == target, rest all index = 0 cells are false
        if(arr[0] <= k)
            dp[0][arr[0]] = true;
        
        // DP
        
        for(int index=1; index < n; index++){// all index 0's cells are covered
            for(int target=1; target <= k; target++){// all target 0 cells are covered in base

                boolean pick = false;
                if(arr[index] <= target){// pick only if the current element is not more then target
                    pick = dp[index-1][target - arr[index]];
                }
                boolean notPick = dp[index-1][target];
                dp[index][target] = pick || notPick;
            }
        }

        // now we have our dp filled, now we want to find the minAbsDiff of 2 partitions, from complete array
        // so for complete array ans is in last row of the dp i.e row n-1
        int minAbsDiff = Integer.MAX_VALUE;
        for(int sum=0; sum <= totalSum; sum++){ // single partition can have sum from 0 to totalSum(all ele included) only

            // if part1 can have ele sum == k, then only continue
            if(dp[n-1][sum] == true){
                int part1Sum = sum;
                int part2Sum = totalSum - part1Sum;
                int diff = Math.abs(part1Sum - part2Sum);
                minAbsDiff = Math.min(minAbsDiff, diff);
            } 
        } 

        return minAbsDiff;
        
    }
}
```
