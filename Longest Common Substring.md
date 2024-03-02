# Longest Common Substring 

#### Solved at : [Codestudio](https://www.codingninjas.com/studio/problems/longest-common-substring_1235207?leftPanelTabValue=PROBLEM)
same as : Longest common subarray 

prerequisite : longest common subseq 

## ✔️Approach - 1 (Tabulation - bottom up dp)
finding len of longest common substring and then printing the substring
```java
public class Solution {

    // Tabulation (bottom up dp)
    // Time : O(n*m)  Space : O(n*m)
    public static int lcs(String str1, String str2){
        int n = str1.length();
        int m = str2.length();
        int[][] dp = new int[n+1][m+1]; // index shifted so +1

        int maxLen = 0;
        int row=0, col=0; // storing coordinates where our longest common substr is located 

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(str1.charAt(i-1) == str2.charAt(j-1)) // char matched, also index is shifted so before accesing string make sure to do -1
                    dp[i][j] = 1 + dp[i-1][j-1];
                
                else dp[i][j] = 0; // curr char not matched so no common substring

                if(dp[i][j] > maxLen){
                    maxLen = dp[i][j];
                    row = i;
                    col = j;
                }

            }
        }

        // printing our longest common substring 
        String longCommonSubstr = "";
        while(row > 0 && col > 0 && dp[row][col] != 0){ // when longComLen becomes 0 stop
            // before accessing org strings char make sure to do -1 (index shifted) 
            longCommonSubstr = str1.charAt(row-1) + longCommonSubstr; // insert common char at start of string, since we are traversing in rev order
            row--;
            col--;
        }
        System.out.println(longCommonSubstr);


        return maxLen;
    }
}

```
