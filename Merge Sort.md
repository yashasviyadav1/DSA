
# Merge Sort (Algorithm)

```cpp
/* ✔️⭐Approach - 1 (Recursive) : Merge Sort 

    explanation :-  DIVIDE Function 
    
                    step 1 : base case - if start becomes equal to end i.e when array size is 1 then its already sorted, just return the function 
                    step 2 : find the mid element for the given start and end at an instance
                    step 3 : sort the left part of the array
                    step 4 : sort the right part of the array
                <-- step 5 : now since both the parts are sorted, just merge the 2 arrays
                |   //array sorted.
                |   
                |
                --> CONQUER Function
                
                   step 1 : create an array 'left' of length1 (mid-start+1)
                   step 2 : create an arary 'right' of length2 (end - mid)
                   step 3 : now push the first half elements of original array into array 'left'.
                   step 4 : now push the second half elements of original array into array 'right'.
                   step 5 : now using 2 pointer variables approach, push the 2 sorted arrays(left & right) into original array 
                   step 6 : when either one of left or right sorted array's all elements are pushed and others are still left then push all elements of non empty array into original array.
                   // now the 2 sorted arrays are merged.


    T : O( n*log(n) ) - best & worst case
    S : O(N) - recursive call stack

*/

#include <iostream>
using namespace std;

void printArray(int *arr, int size){
    for(int i=0; i<size; i++) cout << arr[i] << ' ';
    cout << endl;
}

void conquer(int *arr, int start, int mid, int end){
    
    int length1 = mid - start + 1;
    int length2 = end - mid;

    int *leftArray = new int[length1];
    int *rightArray = new int[length2];

    // adding elements to both arrays 
    int arrIterator = start;
    for(int i = 0; i<length1; i++){
        leftArray[i] = arr[arrIterator++];
    }

    for(int i=0; i<length2; i++){
        rightArray[i] = arr[arrIterator++];
    }

    // comparing both left and right arrays and finally sorting it (using 2 pointers)
    int originalArrIndex = start;
    int i = 0 , j = 0;
    while(i < length1 && j < length2){
        if(leftArray[i] <= rightArray[j] ) arr[originalArrIndex++] = leftArray[i++];
        else arr[originalArrIndex++] = rightArray[j++];
    }

    //if one out of left & right is large/smaller than other
    while(i < length1) arr[originalArrIndex++] = leftArray[i++];
    while(j < length2) arr[originalArrIndex++] = rightArray[j++];

    // cleaning up heap memory 
    delete[] leftArray;
    delete[] rightArray;

}

void divide(int *arr, int start , int end ){
    
    // base case 
    if(start >= end) return;

    int mid = start + (end-start)/2;

    divide(arr, start, mid);   //go to left part 
    divide(arr, mid+1, end);   //go to right part 
    conquer(arr, start, mid, end);  // sorting and merging both part at last

    return;
}

int main(){
    int arr[] = {10,4,2,43,8,0,88,43,21};
    int size = sizeof(arr)/sizeof(int);


    int start = 0 , end = size - 1;
    divide(arr, start, end);

    cout <<"Sorted Array : ";
    printArray(arr,size);

    return 0;


}

// Solved at CodeStudio's : https://www.codingninjas.com/codestudio/problems/merge-sort_920442?leftPanelTab=0&utm_source=youtube&utm_medium=affiliate&utm_campaign=love_babbar_14
// Solved at gfg : https://practice.geeksforgeeks.org/viewSol.php?subId=703ea23866286dc7eb2022df575c33ad&pid=700150&user=yashasvcb6y

/*

note : Merge Sort is a recursive algorithm based on divide and conquer 


*/

```
