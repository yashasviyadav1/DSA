// ⭐HEAP SORT IMPLEMENTATION - using max heap (for sorting array in asc order)

// practice at : https://www.geeksforgeeks.org/problems/heap-sort/1

/* ⭐✔️Approach - 1  (using heapify and heapSort functions) - JAVA
    
        explanation :- 
        
                // Fun.3 : this function converts a random array into max heap
            
                    step 1 : store the i into a integer 'largerChildIndex' , also find the left and right childs indexea of index
                    step 3 : now condition check if (leftChildIndex < size && (arr[leftChildIndex] > arr[largerChildIndex])) if yes then, update largerChildIndex = leftChildIndex
                    step 4 : now condition check if (rightChildIndex < size && (arr[rightChildIndex] > arr[largerChildIndex])) if yes then, update largerChildIndex = rightChildIndex
                    step 5 : check if (i != index) if yes then swap(arr[largerChildIndex], arr[i]) and then recursion will build the rest i.e heapify(arr, size, largerChildIndex)
            
            
                // Fun.2 : to build the heap
             
                    step 1 : run a loop for non leaf nodes (i.e n/2-1 to 0th index [for 0 based indexing]) and call function heapify that will convert this array into a max heap
              
                
                
                // Main function : this function will take heap array as input and sorts this array as output
            
                    step 1 : call function 2 buildHeap(arr,size) to convert array into heap
                    step 1 : store the size into a variable tempSize 
                    step 2 : run a loop while this tempSize is greater than 1 
                        step 3 : swap the 1st index(if 1bases indexing) and tempSize index element
                        step 4 : decrement the tempSize-- (as the right part will be sorted part of the array)
                        step 5 : now to place the 1st index node(if doing 1 bases indexing) at its correct position in the remaining heap, call function heapify(arr, tempSize, 1)
            
                    Done
    
      ✅T : O(NlogN + NLogN) => O(nLogn) 
      S : O(1) - no extra space used, (only recursive stack)
    
        [note : above code is for 1-bases indexing]

*/

public class HeapSortImplement{

    private static void heapify(int arr[], int size, int i){

        // we got a nodes index and we need to place it at its correct position
        // in a max heap, root is the largest node
        while(i < size){

            int leftChildIndex = 2*i + 1;
            int rightChildIndex = 2*i + 2;
            int largestNodeIndex = i;
            
            // find which node is largest among both child (which is greater then the ith node)
            if(leftChildIndex < size && arr[leftChildIndex] > arr[largestNodeIndex])
                largestNodeIndex = leftChildIndex;
            if(rightChildIndex < size &&  arr[rightChildIndex] > arr[largestNodeIndex])
                largestNodeIndex = rightChildIndex;
                
            // if we found a child greater then i then child and parent nodes
            if(largestNodeIndex != i){

                int temp = arr[i];
                arr[i] = arr[largestNodeIndex];
                arr[largestNodeIndex] = temp;
                i = largestNodeIndex; // after the swap, then ith node is the swapped child node
            } 
            else return; // means no need to swap, i is already at its correct position
        }

        // reached here means ith node is placed at its correct position in the max heap
        return;
    }

    private static void buildMaxHeap(int arr[]){

        int n = arr.length;
        for(int i=n/2-1; i >= 0; i--)
            heapify(arr, n, i);
    }

    private static void heapSort(int arr[]){

        int n = arr.length;
        // in asc heap sort, we loop the max heap array, and swap the 1st (0th) node with last node, then reduce size and heapify it
        while(n > 0){
            
            // swap the 0th and n-1th node to place 0th node at its correct position
            int temp = arr[0];
            arr[0] = arr[n-1];
            arr[n-1] = temp;

            n--; // reduce size by 1 because the nth node is just placed at its correct position (for sorted array)
            heapify(arr, n, 0); // lets place the 0th node at its correct position
        }
    }

    public static void main(String ... args){

        int arr[] = {10,15,14,13,12,18,16};

        // build max heap
        buildMaxHeap(arr);
        
        // for(int i=0; i < arr.length; i++)
        //     System.out.print(arr[i] + " ");

        // heapSort the max Heap in asc order
        heapSort(arr);

        // System.out.println("reached line 65");

        // print the array
        System.out.println("Sorted array : ");
        for(int i=0; i < arr.length; i++)
            System.out.print(arr[i] + " ");
    }
}
