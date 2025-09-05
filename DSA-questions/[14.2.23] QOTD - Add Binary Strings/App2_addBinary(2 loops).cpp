
// QOTD - 14 Feb 23 
// leetcode link : https://leetcode.com/problems/add-binary/description/

/* ✔️⭐Approach - 2 (improved - extra loops removed) (using 2 normal while loops) - more readable code 

        note : to understand how i made these improvements, make sure to check out both the approaches of the question '2 Sum Linked List' it is a similar question. 

        explanation :- 
            we need to take care of few things for this question

            see 'short' sum can be either 0,1,2,3 ( it cant be more than that, how) ?
                1) when short sum is 3 (let 2 bits be 1, 1, power = 1)
                    sum => a[i] + b[j] + power => (1+1+1) => 3 ( 11 in binary)
                        in this case we need to add 1 to our 'sum' and set 1 to the power
                2) when short sum is 2 (let 2 bits be 1, 0, power = 1) 
                    in this case short sum = 2 (10 in binary) so 0 is added to the sum string and 1 is set as the new power
                3) when short sum is 1 
                    in that case 1 is simply added to the sumstring and power becomes 0

                imp1 : when both strings are consumed, there can be a case when power is still left, so for that case, make sure to insert the power also to the sumstring 

                imp2 : power will always be 1 at max (not more than that)
                

        ✅T : O(N+M) - N + M for traversing both strings, then N for reversing sumstring
        ✅S : O(1) - no extra space 

        ☑️solved at leetcode : leetcode link : https://leetcode.com/problems/add-binary/description/


    */


// code :- 

class Solution {

private:
// Creating a function to convert character into int (not asci value) implicitely 
    int charToInt(char ch){

        // for eg. we have ch = '2' now we know asci of '0' is 48, so if we do (ch - 48) this will calcluate (50 - 48)(since asci of '2' is 50) give us output => 2 
        int ans = ch - '0'; 
        return ans;
    }

public: // main function
    string addBinary(string a, string b) {
        string sum = "";
        int power = 0;

        int i = a.length() - 1, j = b.length() - 1;

        // this loop will run while any 1 string is not completely consumed
        while(i >= 0 || j >= 0){

            // int shortSum = (int)a[i] + (int)b[j] + power; // dont use this, coz this will convert characters into asci values and then add those values

            int bit1 = 0;
            int bit2 = 0;
            if(i >= 0) bit1 = charToInt(a[i]);
            if(j >= 0) bit2 = charToInt(b[j]);

            int shortSum = bit1 + bit2 + power;
            
            if(shortSum == 2){
                sum += '0';
                power = 1;
            }
            else if(shortSum == 3){
                sum += '1';
                power = 1;
            }
            else{
                sum += to_string(shortSum);
                power = 0;
            }

            // updating pointers to characters
            if(i >= 0) i--;
            if(j >= 0) j--;
        }


        // when both strings are consumed but some power is left
        if(power){
            sum += to_string(power);
            power = 0; 
        } 
    
        // reverse the sum string and return it 
        i = 0, j = sum.length()-1;
        while(i < j){
            swap(sum[i],sum[j]);
            i++;
            j--;
        }

        return sum;
    }

};