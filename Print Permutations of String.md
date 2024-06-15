# Print Unique Permutations of a given String

### Solved at : [GFG](https://www.geeksforgeeks.org/problems/permutations-of-a-given-string2041/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article)

Concept : 
![image](https://github.com/yashasviyadav1/dsa-questions/assets/124666305/c8422651-7f16-4330-8234-f4d49ee24b40)

## ✔️Approach - 1 (Backtracking Bruteforce)
```java

// Approach - bruteforce
// Time : O(n^n + nlogn)exponential Space : O(n) - char array
class Solution {

    // we canot direcly swap characters in string coz string is immutable in java
    // so creating a new string with swapped char i and j
    private String stringCharSwap(String str, int i, int j){
        char[] charArr = str.toCharArray();
        char temp = charArr[i];
        charArr[i] = charArr[j];
        charArr[j] = temp;
        return String.valueOf(charArr);
    }

    // left,right keeps track of out string that we have to find permutations of
    private void permutations(String str, Set<String> ans, int left, int right){
        
        // left and right meet means remaining string is already fixed and we are at single char now which has only 1 permutatio so add this string as it is
        if(left == right){ 
            ans.add(str);
            return; 
        }
        
        // we have left now we iterate on whole string and we fix each char at the left index by swaping it, now we fixed char at left index so for remaining string (left+1, right) call the permutation 
        for(int i=left; i <= right; i++){
            str = stringCharSwap(str, left, i); // fixing char at left
            permutations(str, ans, left+1, right);
            str = stringCharSwap(str, left, i); // backtrack
        }
    }
    public List<String> find_permutation(String str) {
        
        // using tree set coz we need uniq permutations and in sorted order lexicographically
        Set<String> ans = new TreeSet<>(); // for cases like ABB we only need uniq permutations
        int n = str.length();
        permutations(str, ans, 0, n-1);
        
        List<String> result = new ArrayList<>();
        ans.forEach((perm) -> result.add(perm));
        
        return result;
    }
}
```
