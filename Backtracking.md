# Backtracking 

Backtracking is an algorithmic technique whose goal is to use brute force to find all solutions to a problem

----
Use cases :- 
- Finding all possible Permutations of array or string
- Finding Power set of a array
- Finding all possible subsets or combinations or sequences present in array whoose sum equals target

----
#### There are 2 ways to implement backtracking 
- 1. using pick and not pick
- 2. using looping with backtracking (more optimal)

lets see both ways with a question
```
Given array nums and target find all combinations of elements in array whoose sum equals target
note : can't pick an element more then ones
note: [2,6] and [6,2] are considered same here pick any of them in answer
```

-------
### Backtracking 1 -> using pick and not pick
```java
import java.util.*;
class Solution{
  // normal pick and not pick approach
    public void backtrack1(int[] nums, List<List<Integer>> ans, List<Integer> tempList, int target, int i){
        // count++;
        
        if(target == 0){
            ans.add(new ArrayList<>(tempList));
            return;
        }
        if(i == nums.length) return;
        backtrack1(nums, ans, tempList, target, i+1); // not pick
        if(nums[i] <= target){
            tempList.add(nums[i]);
            backtrack1(nums, ans, tempList, target - nums[i], i+1);
            tempList.remove(tempList.size()-1);
        }
    }
}

public class Backtracking {
    public static void main(String ... args){
        int[] nums = {6, 2, 8};
        int target = 8;
        Solution obj = new Solution();
        
        List<List<Integer>> ans = new ArrayList<>();
        obj.backtrack1(nums, ans, new ArrayList<>(), target, 0);

        System.out.println(ans);
    }
}
```

### Backtracking 2 - using loop with backtrack
```java
import java.util.*;
class Solution{

    // backtrack with loop - more efficient
    // we can pick every element as the first element 
    public void backtrack2(int[] nums, List<List<Integer>> ans, List<Integer> tempList, int target, int i){
        if(target == 0){
            ans.add(new ArrayList<>(tempList));
            return;
        }
        if(i == nums.length) return;
        for(int j=i; j < nums.length; j++){
            if(nums[j] > target) continue;
            tempList.add(nums[j]);
            backtrack2(nums, ans, tempList, target - nums[j], j+1);
            tempList.remove(tempList.size()-1);
        }
    }
}
public class Backtracking {
    public static void main(String ... args){
        int[] nums = {6, 2, 8};
        int target = 8;
        Solution obj = new Solution();

        List<List<Integer>> ans2 = new ArrayList<>();
        obj.backtrack2(nums, ans2, new ArrayList<>(), target, 0);

        System.out.println(ans2);
    }
}

```
