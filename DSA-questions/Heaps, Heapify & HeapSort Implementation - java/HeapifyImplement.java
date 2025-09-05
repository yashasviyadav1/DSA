public class HeapifyImplement {
    
    // heapify for min heap

    public static void heapify(int arr[], int size, int i){

        int smallestIndex = i;

        int leftChildIndex = 2*i;
        int rightChildIndex = 2*i + 1;
        if(leftChildIndex < size && arr[smallestIndex] > arr[leftChildIndex]){
            smallestIndex = leftChildIndex;
        }
        if(rightChildIndex < size && arr[smallestIndex] > arr[rightChildIndex]){
            smallestIndex = rightChildIndex;
        }

        if(smallestIndex != i){
            int temp = arr[i];
            arr[i] = arr[smallestIndex];
            arr[smallestIndex] = temp;
            heapify(arr, size, smallestIndex);
        }
    }

    public static void main(String ... args){

        int arr[] = {1,6,4,3,7};
        int n = arr.length;
        for(int i=n/2; i > 0; i--){
            heapify(arr, n, i);
        }

        System.out.print("Min heap : ");
        for(int i=0; i < n; i++)
            System.out.print(arr[i] + " ");

        /*
            1
           / \
          3   4
         / \
        6   7

        */
    }

}
