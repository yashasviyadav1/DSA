# First negative in every window of size k

#### [GFG](https://www.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k3345/1)

## ✔️Approach - 1 (fix sliding window + dq for negative elements)
```java
class Compute {
    
    public long[] printFirstNegativeInteger(long nums[], int N, int K)
    {
        Deque<Long> negatives = new ArrayDeque<>();
        long[] ans = new long[N-K+1];
        int index = 0;
        int left = 0;
        for(int right=0; right < N; right++){
            if(nums[right] < 0)
                negatives.addLast(nums[right]);
            if(right >= K-1){ // window of size k found
                if(negatives.size() == 0) ans[index++] = 0;
                else ans[index++] = negatives.getFirst();
                // shift window to right by 1 step
                if(!negatives.isEmpty() && nums[left] == negatives.getFirst())
                    negatives.removeFirst();
                left++;
            }
        }
        return ans;
    }
}
```
