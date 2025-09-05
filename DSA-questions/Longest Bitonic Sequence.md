# Longest Bitonic Sequence

Prerequisite : LIS Algo
---
Varient 1 : A Bitonic Sequence is a sequence of numbers that is first strictly increasing and then strictly decreasing. A strictly ascending order sequence is also considered bitonic, with the decreasing part as empty, and same for a strictly descending order sequence
#### Solved at : [Codestudio](https://www.naukri.com/code360/problems/longest-bitonic-sequence_1062688?leftPanelTabValue=PROBLEM)
## ✔️Approach - 1 (using LIS Algo from longest inc subseq logic with changes) 
```java
import java.util.*;
public class Solution {
    // App-1
    // prerequisite : Longest increasing subseq algo of printing it 
    // running LIS algo frmo left to right then right to left then computing bitonic subseq inc each element one by 1
    // T:O(2(n*n) + (n)) -> O(n*n)
    // S:O(2(n*n))
    public static int longestBitonicSequence(int[] nums, int n) {
        // finding longest inc subseq for each element from left to right
        int[] dp1 = new int[n];
        Arrays.fill(dp1, 1);
        for(int i=0; i < n ; i++){
            for(int prev=0; prev < i; prev++){
                if(nums[i] > nums[prev] && dp1[prev] + 1 > dp1[i])
                    dp1[i] = dp1[prev] + 1;
            }
        }
        
        // finding longest inc subseq for each element from right to left
        int[] dp2 = new int[n];
        Arrays.fill(dp2, 1);
        for(int i=n-1; i >= 0; i--){
            for(int prev=n-1; prev > i; prev--){
                if(nums[i] > nums[prev] && dp2[prev] + 1 > dp2[i])
                    dp2[i] = dp2[prev] + 1;
            }
        }
        
        // finding longest bitonic subsequence
        int longBitonicSubseqLen = 0;
        for(int i=0; i < n; i++){
            // finding longest bitonic subseq including every element 1 by 1
            // including ith element ,adding the longest inc subseq inc ith element on its left
            // with longest inc subseq on its right including ith element 
            // -1 because ith element is being included twice
            longBitonicSubseqLen = Math.max(longBitonicSubseqLen, dp1[i] + dp2[i] - 1);
        }
        
        return longBitonicSubseqLen;
    }
}

```

GfF Varient 2 :  A Bitonic Sequence is a sequence of numbers that is first strictly increasing and then strictly decreasing. A strictly ascending order sequence is not considered as bitonic
#### Solved at : [GFG](https://www.geeksforgeeks.org/problems/longest-bitonic-subsequence0824/1)
## Approach - same approach minor changes
```java


class Solution {
    // App-1
    // prerequisite : Longest increasing subseq algo of printing it 
    // running LIS algo frmo left to right then right to left then computing bitonic subseq inc each element one by 1
    // T:O(2(n*n) + (n)) -> O(n)
    // S:O(2(n*n))
    public static int LongestBitonicSequence(int n, int[] nums) {
        
        // finding longest inc subseq for each element from left to right
        int[] dp1 = new int[n];
        Arrays.fill(dp1, 1);
        for(int i=0; i < n ; i++){
            for(int prev=0; prev < i; prev++){
                if(nums[i] > nums[prev] && dp1[prev] + 1 > dp1[i])
                    dp1[i] = dp1[prev] + 1;
            }
        }
        
        // finding longest inc subseq for each element from right to left
        int[] dp2 = new int[n];
        Arrays.fill(dp2, 1);
        for(int i=n-1; i >= 0; i--){
            for(int prev=n-1; prev > i; prev--){
                if(nums[i] > nums[prev] && dp2[prev] + 1 > dp2[i])
                    dp2[i] = dp2[prev] + 1;
            }
        }
        
        // finding longest bitonic subsequence
        int longBitonicSubseqLen = 0;
        for(int i=0; i < n; i++){
            // finding longest bitonic subseq including every element 1 by 1
            // including ith element ,adding the longest inc subseq inc ith element on its left
            // with longest inc subseq on its right including ith element 
            // -1 because ith element is being included twice
            // with this below condition we add LIS of both sides only when both of their lengths are more then 1
            if(dp1[i] != 1 && dp2[i] != 1) // this case is to make sure of the strcitly inc and decreasing thing
                longBitonicSubseqLen = Math.max(longBitonicSubseqLen, dp1[i] + dp2[i] - 1);
        }
        
        return longBitonicSubseqLen;
        
    }
}
```
