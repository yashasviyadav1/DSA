/* ✔️⭐Approach - 2 ( creating a optimised solution, using a doubly ended queue) 
        
        explanation :- here what we will do is we will traverse both the k and nums from the back side of them and then add each of the characters (after converting it to int) + power , and then whatever sum we get here, we will fetch only its ones place and then store it at the front of the queue, (we cant do this in num coz in vector their is no push and pop at front() operations, so we used a deque, at the end fetch the queue and store it into a vector 'ans' and return it)


        ✅T : O(2*max(N+M)) where n is length of 'num' and m is length of k (when converted to a string), and then fetching the whole queue into vector
        S : O(N) - using dobly ended queue 

        ☑️solved at leetcode : https://leetcode.com/problems/add-to-array-form-of-integer/description/

*/

class Solution {

private:/// function that converts '1' to 1 (int) 
    int charToInt(char ch){
        return ch - 48;
    }

public:
    // Main function
    vector<int> addToArrayForm(vector<int>& num, int k) {
        
        // convert k to string and store it in 'kStr' 
        string kStr = to_string(k);
        
        // now traverse both the kStr, num ,from the end 
        int i = num.size() - 1, j = kStr.length() - 1;

        deque<int> dq;

        int power = 0;
        while( i >= 0 || j >= 0){
            
            int num1 = 0, num2 = 0; // by default
            if(i >= 0) num1 = num[i];
            if(j >= 0) num2 = charToInt(kStr[j]);

            int sum = num1 + num2 + power;

            int onesPlace;
            if(sum >= 10) onesPlace = sum % 10;
            else onesPlace = sum;

            power = sum/10;

            // store ones dig into the dq
            dq.push_front(onesPlace);

            if(i >= 0) i--;
            if(j >= 0) j--;
        }

        // lets say if the array is consumed and power is still left, then ?
        if(power){
            dq.push_front(power);
        }

        // create vector from dq;
        vector<int> ans;
        while(!dq.empty()){
            ans.push_back(dq.front());
            dq.pop_front();
        }

        return ans;

    }
};