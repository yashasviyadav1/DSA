# Longest K unique characters substring

#### Solved at : [Leetcode](https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1)

## ✔️Approach - 1 (Variable size Sliding Window + HashMap) 
```java
// variable size sliding window T:O(n) S:O(n)
// expand window to the point where we get window size more than k
// ones we get more than k we shrink the window
// maintain the maxLen of substring/window that has k uniq characters

class Solution {
    public int longestkSubstr(String s, int k) {
        // can't use set coz eg. aab when we shrink window both freq of a will be removed
        HashMap<Character,Integer> hm = new HashMap<>(); 
        
        int maxLen = 0;
        int left = 0;
        for(int right=0; right < s.length(); right++){
            
            char ch = s.charAt(right);
            hm.put(ch, hm.getOrDefault(ch, 0) + 1); // increment freq
            
            // shrink the window to obtain k uniq char
            while(hm.size() > k){
                ch = s.charAt(left);
                hm.put(ch, hm.get(ch) - 1);
                if(hm.get(ch) == 0) hm.remove(ch);
                left++;
            }
            
            // if there are k uniq elements in our window maximize len
            if(hm.size() == k)
                maxLen = Math.max(maxLen, right - left + 1);
        }    
        
        return (maxLen == 0)?-1:maxLen;
    }
}
```
