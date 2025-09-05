# Failed Approach - 1

```cpp
class Solution {
    /* ⚠️Approach - 1 (brute force) 

            issue with code : ⚠️Int is getting out of range i.e when string '9999999999' (more than 2^10) is converted into integer by stoi() stl func then it is not able to store into a integer range, so throws error

    */
private:
    // fun. that converts '1' character to 1 int in O(1) time
    int chToInt(char ch){
        // to convert a character '2' to its int form 2 we will subtract it with 48 (asci of 0)
        return (ch - 48);
    }

public:
    // Main function
    vector<int> addToArrayForm(vector<int>& num, int k) {

        // convert all elements of 'num' into a string 'numStr'
        string numStr = "";
        for(int i = 0; i < num.size(); i++){
            numStr += to_string(num[i]);
        }

        // now convert this string into int, add k to it
        int numInt = stoi(numStr) + k;

        //  and convert it to string again 
        numStr = to_string(numInt);

        // novert numInt to new array form again 
        vector<int> ans;
        for(int i=0; i < numStr.length(); i++){
            // convert each char to int and then store it into ans vector
            int chInt = chToInt(numStr[i]);
            ans.push_back(chInt);
        }

        return ans;
    }
};
```

# Failed Approach - 2

```cpp
class Solution {
    /* ⚠️Approach - 1.1 modified (brute force) 

            modification :- here we used 'long long int' rather than int 
            issue: still getting out of range

    */
private:
    int chToInt(char ch){
        // to convert a character '2' to its int form 2 we will subtract it with 48 (asci of 0)
        return (ch - 48);
    }

    long long int stringToLongInt(string str){

        long long int num = 0;
        long long int place = 1;

        for(int i = str.length()-1; i >= 0; i--){
            int chInt = str[i] - 48;
            num += chInt*place;
            place *= 10;

        }

        return num;
    }

public:
    vector<int> addToArrayForm(vector<int>& num, int k) {

        // convert all elements of 'num' into a string 'numStr'
        string numStr = "";
        for(int i = 0; i < num.size(); i++){
            numStr += to_string(num[i]);
        }

        // now convert this string into int, add k to it
        long long int numInt = stringToLongInt(numStr) + k;

        //  and convert it to string again 
        numStr = to_string(numInt);

        // novert numInt to new array form again 
        vector<int> ans;
        for(int i=0; i < numStr.length(); i++){
            // convert each char to int and then store it into ans vector
            long long int chInt = chToInt(numStr[i]);
            ans.push_back(chInt);
        }

        return ans;
    }
};
```
