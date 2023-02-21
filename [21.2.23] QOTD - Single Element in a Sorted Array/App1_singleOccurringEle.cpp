
// ☑️leetcode link : https://leetcode.com/problems/single-element-in-a-sorted-array
/* ✔️ Approach - 1  - using unordered_map

            explanation :- storing all the elements of array and map them to their respective number of occurences in a unordered_map 
        T:O(N)
        S:O(N)
*/

class Solution {
public:
    
    
    int singleNonDuplicate(vector<int>& nums) {
        
        // saving all numbers with their occurrences into map 
        unordered_map<int,int> map;
        for(int i=0; i<nums.size(); i++)
            map[nums[i]]++;
        
        // lets return the element with only 1 occurence 
        for(pair<int,int> i:map) // same as for(auto i:map)  
            if(i.second == 1)
                return i.first;
        
        return -1;
    }
};