// Solved(✔️) - String Compression - 1 approach 
// QOTD 2 feb 23 
// ☑️leetcode link : https://leetcode.com/problems/string-compression/description/

/* ✔️⭐Approach.1 (using simple loops) 
        
        explanation : here what we do is really simple, we will maintain a string 's' in which we will store the output which is asked in this question and also we will maintain the count for in a integer for the number of times a character is repeated consequetively , so we will traverse the 'chars' do this above procedure, and at the end, we will store this string into the 'chars' and then return.

       ✅T : O(N)
       ✅S : O(N)

*/


class Solution {

public:
    // main fun 
    int compress(vector<char>& chars) {

        string ans = "";
        int count = 0;
        char ch = chars[0];

        for(int i=0; i < chars.size(); i++){

            // if char matches our ch
            if(chars[i] == ch) count++;

            // else store it in the format it is required
            else{
                ans += ch;
                if(count != 1){
                    string countStr = to_string(count);  // storing the char

                    for(char i:countStr) ans += i;  // with its freq in string form 
                }
                
                // updation of 'ch' (coz we got a new character now ) and its 'count'
                ch = chars[i];
                count = 1;
            }
        }

        // when the loop breaks, the last char was not inserted in the ans, so do that
        ans += ch;
        if(count != 1){
            string countStr = to_string(count);  // storing the char

            for(char i:countStr) ans += i;  // with its freq in string form 
        }

        // it is mentioned that we need to store the ans string in our input itself 
        chars.clear();
        for(int i=0; i < ans.size(); i++) chars.push_back(ans[i]);

        return chars.size();
    }
};
