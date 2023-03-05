/* ✔️⭐Approach - 1 (using min heap)

        explanation : create min heap, insert all dig of 'num' into the it, then maintain 2 strings 'num1' and 'num2' and start to pop top of min and insert first in num1, then in num2, and at last when min heap is empty, convert 2 strings into integer and add them , return their sum

        T : O(nLogN)
        S : O(NLogN)

        ☑️solved at leetcode : https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/description/

*/

class Solution {
    
public:
    int minimumSum(int num) {
        int tempNum = num ;
        
        // creating min heap , inserting each dig of this 'num' into it 
        priority_queue<int,vector<int>, greater<int>> minHp;
        while(tempNum != 0){
            int ones = tempNum % 10;
            tempNum /= 10;
            
            minHp.push(ones);
        }
        
        // now create 2 strings 'num1' 'num2'
        string num1 = "", num2 = "";
        
        // now fetch dig from minHp one by one and insert it into num1,num2
        while(!minHp.empty()){
            
            int top = minHp.top();
            minHp.pop();
            num1 += to_string(top);
            
            if(minHp.empty()) break;
            
            top = minHp.top();
            minHp.pop();
            num2 += to_string(top);
        }
        
        // convert num1, num2 to int and add and return their sum
        int number1 = stoi(num1);
        int number2 = stoi(num2);
        
        return number1 + number2;
    }
};
