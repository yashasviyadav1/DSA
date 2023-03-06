// Solved(✔️) - Kth Missing Ele in Sorted Array - 1 approach 
// QOTD - 6th Mar 23 
// ☑️leetcode link : https://leetcode.com/problems/kth-missing-positive-number/description/

/*✔️⭐ Approach - 1 

            📝note : this is not the best approach, this is the first approach that came to my mind.

        explanation : there is one observation to make, see we can store the elements missing between 0 till lastEle of arr, but what if the missing ele they asked for is lets say '9' and the arr = {1,3,4,6} then in that case note that our kthmissing ele is greater the the last element of array and in this case our mising elements between 0 and 6 are missing = [2,5] so using a formula kth missing will be = (last ele of arr + k - elements in 'missing' array ) i.e => 6 + 9 - 2 => 13 (ANS) 

        T : O(n)
        S : O(n) 

*/

// Code 
class Solution {
   
public:
    int findKthPositive(vector<int>& arr, int k) {
        int size = arr.size();

        vector<int> missingEles;
        int prv = 0;

        for(int i=0; i < arr.size(); i++){

            int curr = arr[i];
            // insert all elements from (prv+1 to curr-1) into the 'missing' vector
            for(int ele = prv+1; ele < curr; ele++)
                missingEles.push_back(ele);
            
            prv = curr; // updation
        }
        
        // now return the kth missing ele
        if(missingEles.size() >= k)
            return missingEles[k-1];

        else{ // reached here means, missing ele is not in the missing ele's array
            int kthMissingEle = arr[size-1] + (k - missingEles.size());
            return kthMissingEle;
        }
    }
};

