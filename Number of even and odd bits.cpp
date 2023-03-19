//☑️ contest 19 march 23 - question 1 
// leetcode link : https://leetcode.com/contest/weekly-contest-337/problems/number-of-even-and-odd-bits

/*✔️⭐ Approach - 1 (T:O(n) S:O(1))
         
         explanation : find the binary representation of 'n' integer, then check number of set bits on odd index and even index and return answer resepectively.
         
         T : O(n)
         S : O(n) - recursive stack  
  */
class Solution {
    
private:
    void intToBinary(int n , string &binary){
        if(n==0) return;
        
        binary += to_string(n % 2);
        intToBinary(n/2, binary);
    }
    
public:
    vector<int> evenOddBit(int n) {
        
        // first convert n to binary string 
        string binary = "";
        intToBinary(n,binary);
        
        // now traverse the string 'binary' and maintain a oddIndexSetBitCount, evenIndexSetBitCount
        int oddIndexSetBitCount = 0, evenIndexSetBitCount = 0;
        for(int i=0; i < binary.length(); i++){
            
            if(i % 2 == 0 && binary[i] == '1') evenIndexSetBitCount++;
            else if(binary[i] == '1') oddIndexSetBitCount++;
        }
        
        return {evenIndexSetBitCount, oddIndexSetBitCount};
    }
};
