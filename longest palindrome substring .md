# Longest Palindrome Substring in a String 

☑️solved on Leetcode : [Link](https://leetcode.com/problems/longest-palindromic-substring/description/) 

example :- 

![image](https://github.com/yashasviyadav1/DSA-Questions/assets/124666305/c696c8e7-48e3-4b00-b416-1ea7bfc38cf2)

![image](https://github.com/yashasviyadav1/DSA-Questions/assets/124666305/06def121-8811-4f33-be36-c85ee10cbef0)

Approach 

```
✔️⭐ Approach - 3 (checking palindrome by expanding each ch to left and right simultaneously)

     idea : see we have 2 ways to check if a string is palindrome or not 
            1) keeping 2 pointers, 1 at start of string and 2nd at its end, and then check if the 2 chars are equal or not (but this is slow technique)
            2) start from middle of string, and keep 2 pointers and 1 goes towards left, 2nd goes towards right, and check same above condition

            also note that here we are checking 2 times, coz in case of 'h(elle)oh'
            our longest palindrome is even length 
            and in case of 'he(lloll)pp' our longest palin is odd length so we need to check both cases.

    T : O(n^2)
    S : O(1)
```
dry run :- 

![image](https://github.com/yashasviyadav1/DSA-Questions/assets/124666305/f7f0ccf4-21ce-458b-8bd0-fecbc393b46a)

Code : - 
```java
class Solution {

    public String longestPalindrome(String str) {

        String result = "";

        for(int i=0; i < str.length(); i++){

            // in case our palindrome is O D D  lengh eg (ehe) then s, e are at same initially
            int start = i, end = i;
            while(start >= 0 && end < str.length()){ // expand from both ends

                if(str.charAt(start) != str.charAt(end)) break; // if substr is not palin, do not go further on this index 'i' 
                else if(end - start + 1 > result.length()) // else if it is palin and longer then 'result'
                    result = str.substring(start, end + 1);
                start--;
                end++;
            }

            // in case palin is E V E N length (heeh)
            start = i;   //we cant update 2 var in 1 line in java
            end = i+1;
            while(start >= 0 && end < str.length()){ // expand from both ends

                if(str.charAt(start) != str.charAt(end)) break; // if substr is not palin, do not go further on this index 'i' 
                else if(end - start + 1 > result.length()) // else if it is palin and longer then 'result'
                    result = str.substring(start, end + 1);
                start--;
                end++;
            }
        }

        return result;
        
    }
}

```
