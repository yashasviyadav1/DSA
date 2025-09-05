// Solved (✔️) - Min Valid Capacity of ship to deliver all weights - 1 approach 

// ☑️leetcode link : https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/description/

// QOTD 22 Feb 23

/* Approach - 1 (binary search)
    
         ✅T : O(NlogN) 
         ✅S : O(1)
*/

// code 
class Solution {
    

private:
    // fun.2  - this fun will return false if the 'mid' can not be a valid capacity for the ship, else returns true if mid can be a valid capacity for the ship
    bool isValidCapacity(vector<int> &weights, int maxDaysToDeliver, int mid){

        int days = 1; // to keep track of the delivery 
        int sum = 0; // to maintain if the sum does'nt go above capacity(mid)
        int i=0;
        while(i < weights.size()){
            
            int element = weights[i];

            // if the curr weight doesnt make the sum go above the capacity for single day (Mid) then deliver it 
            if(element + sum <= mid){
                sum += element;
                i++;
            }

            // ekse if curr weight can'nt be delivered on curr day then deliver it the next day , make sure if the days limit is crossed, then we cant deliver all the weights on the current capacity (mid)
            else{
                sum = element;
                if(days > maxDaysToDeliver) return false;
                days++;
                i++;
            }
        }

        // if we delivered in the required days, then return true, else false
        return days <= maxDaysToDeliver;
    }
public:
    // main function
    int shipWithinDays(vector<int>& weights, int maxDaysToDeliver) {
        
        // lowest capacity of a ship can be max element of the 'weights' (not considering 'maxDaysToDeliver') , and highest capacity will be the sum of all the weights 
        int low = INT_MIN;
        int high = 0;
        for(int i=0; i < weights.size(); i++){
            low = max(low, weights[i]);
            high += weights[i];
        }

        // now lets do a binary search on the low and high
        int mid;
        int minValidCapacity = INT_MAX;
        while(low <= high){
            mid = low + (high-low)/2;

            // call fun.2 and if 'mid' is a valid capacity then update the ans, if it is the min valid capacity , and then to minimise the capacity search for a lower capacity 
            if(isValidCapacity(weights, maxDaysToDeliver, mid)){
                minValidCapacity = min(minValidCapacity, mid);
                high = mid - 1;
            }

            // else if it is not a valid capacity , then search on the right (coz on right we will have heigher values)
            else low = mid + 1;
        }

        if(minValidCapacity != INT_MAX)
            return minValidCapacity;
        else return -1;
    }
};

