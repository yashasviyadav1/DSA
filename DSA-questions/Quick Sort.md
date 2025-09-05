
# Quick Sort 
### Solved at : [GFG](https://practice.geeksforgeeks.org/problems/quick-sort/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article)

### Explaination :- 
```md
explanation :-   Quick Sort Function 

                    step 1 : base case - when there is single elemnt left than array is already sorted
               |--- step 2 : find the pivot index using function 'pivotIndexFinder'
               |    step 3 : now do recursive call for left part of array
               |    step 4 : do recursive call for right part of the array
               |
               |-->   PIVOT INDEX Finder

                   step 1 : take starting index as the pivot of the array 
                   step 2 : count number of elements smaller or equal to the pivot element
                   step 3 : swap the pivotElement and (pivotElement + count)th element.
                   step 4 : declare 2 variables i = start and j = end, and run a loop untill i becomes equal to pivotIndex or j becomes equal to pivotIndex.
                        step 5 : run a loop untill ith element is equal or smaller than the pivotIndex element
                        step 6 : run a loop untill jth element is greater than the pivotIndex element
                        step 7 : swap the ith and jth element if index i is smaller than the pivotIndex and index j is greater than the pivot index.
                   step 8 : return pivot Index.



```
### Dry Run 
![Quick Sort ](https://github.com/yashasviyadav1/DSA-Questions/assets/124666305/250d33a1-ec0e-43fe-8425-fdf8462396b2)

```java

// J A V A

class Solution
{
/*  ⭐✔️QUICK SORT 

        idea : consider 1st element of array as the pivot element, then place it at a position from where all element on its left 
                are smaller and all elements on its right are larger then pivot element, after that divide the array into subarrays (consider pivot as mid element, divide into 2 parts left & right)
            
                🪄 the base case here is that an empty array or single elemnt array is alredy sorted

    Time : N*logN
    Space : O(N) - recursive stack 
 */

    //Function to sort an array using quick sort algorithm.
    static void quickSort(int arr[], int start, int end)
    {
         if(start >= end) return; // array is now sorted

        // now lets find the pivot Index, and place all smaller ele on its left, and larger on right
        int pivotIndex = partition(arr, start, end);

        // split the array into subarrays 
        quickSort(arr, start, pivotIndex-1);
        quickSort(arr, pivotIndex + 1, end);
    }
    
    static int partition(int arr[], int start, int end)
    {
        // count the number of elements smaller/equal to pivot element
        int pivotIndex = start; 
        int smallerEleCount = 0;
        for(int i=start+1; i <= end; i++)
            if(arr[i] <= arr[pivotIndex])
                smallerEleCount++;
        
        // swap -> place pivot element at its right position
        int temp = arr[pivotIndex];
        arr[pivotIndex] = arr[pivotIndex + smallerEleCount];
        arr[pivotIndex + smallerEleCount] = temp;
        pivotIndex = pivotIndex + smallerEleCount; // new value of pivot element is updated now

        // now place all smaller ele on left of pivot, larger on right
        int i = start;
        int j = end;
        while(i < pivotIndex && j > pivotIndex){

            while(i < pivotIndex && arr[i] <= arr[pivotIndex]) i++; // place i and j at their right positions where we can swap them 
            while(j > pivotIndex && arr[j] > arr[pivotIndex]) j--; 

            if(i < pivotIndex && j > pivotIndex){
                // swap
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }
        
        return pivotIndex;
    } 
}
```

```cpp
// C P P 

class Solution
{
    /*✔️⭐(Approach 1 - Recursive) - QUICK SORT 

    explanation :-   Quick Sort Function 

                    step 1 : base case - when there is single elemnt left than array is already sorted
               |--- step 2 : find the pivot index using function 'pivotIndexFinder'
               |    step 3 : now do recursive call for left part of array
               |    step 4 : do recursive call for right part of the array
               |
               |-->   PIVOT INDEX Finder

                   step 1 : take starting index as the pivot of the array 
                   step 2 : count number of elements smaller or equal to the pivot element
                   step 3 : swap the pivotElement and (pivotElement + count)th element.
                   step 4 : declare 2 variables i = start and j = end, and run a loop untill i becomes equal to pivotIndex or j becomes equal to pivotIndex.
                        step 5 : run a loop untill ith element is equal or smaller than the pivotIndex element
                        step 6 : run a loop untill jth element is greater than the pivotIndex element
                        step 7 : swap the ith and jth element if index i is smaller than the pivotIndex and index j is greater than the pivot index.
                   step 8 : return pivot Index.


    T :  O(n^2) - worst case, O(n*log(n)) - best case
    S :  O(n) - recursive call stack in worst case and o(log(n)) in normal case
    
    
    */
    public:
    //Function to sort an array using quick sort algorithm.
    void quickSort(int arr[], int start, int end)
    {
        // step 1 : base case - when there is single elemnt left than array is already sorted
        if(start >= end) return;
        
        // step 2 : find the pivot index using function 'pivotIndexFinder'
        int pivotIndex = partition(arr, start, end);
    
        // step 3 : now do recursive call for left part of array
        quickSort(arr, start, pivotIndex-1);
    
        // step 4 : do recursive call for right part of the array
        quickSort(arr, pivotIndex+1, end);
    
    }
    
    public:
    int partition (int arr[], int start, int end)
    {
       
        // step 1 : take starting index as the pivot of the array 
        int pivotIndex = start;
    
        // step 2 : count number of elements smaller or equal to the pivot element
        int count = 0;
        for(int i = start+1; i < end +1; i++){
            if(arr[i] <= arr[pivotIndex]) count++;
        }
    
        // step 3 : swap the pivotElement and (pivotElement + count)th element.
        swap(arr[pivotIndex], arr[pivotIndex + count]);
        pivotIndex = start + count;
    
        // step 4 : declare 2 variables i = start and j = end, and run a loop untill i becomes equal to pivotIndex or j becomes equal to pivotIndex.
        int i = start, j = end;
        while(i < pivotIndex && j > pivotIndex){
    
            // step 5 : run a loop untill ith element is equal or smaller than the pivotIndex element
            while(arr[i] <= arr[pivotIndex]) i++;
            // step 6 : run a loop untill jth element is greater than the pivotIndex element
            while(arr[j] > arr[pivotIndex]) j--;
    
            // step 7 : swap the ith and jth element if index i is smaller than the pivotIndex and index j is greater than the pivot index.
            if(i < pivotIndex && j > pivotIndex) swap(arr[i++], arr[j--]);
            
        }
    
        // step 8 : return pivot Index.
        return pivotIndex;
    }
};


```
