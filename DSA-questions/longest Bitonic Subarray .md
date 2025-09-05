
```java
public class MyClass {
    
    // find bitonic subarray 
    static void subarray(int arr[]){
        
        int n = arr.length;
        
        int maxLen = 0;
        int start = 0;
        int end = 0;
        for(int i=1; i < arr.length-1; i++){ // we can also run loop from 0 >= to <= n-1 (it will also work)
            
            int element = arr[i];
            int left = i;
            int right = i;
            
            while(left > 0){
                if(arr[left-1] <= arr[left])
                    left--;
                else break;
            }
            
            while(right < n-1){
                if(arr[right+1] <= arr[right])
                    right++;
                else break;
            }
            
            // if ans found 
            if((right - left + 1) > maxLen){
                start = left;
                end = right;
                maxLen = (right-left+1);
            }
        }
        
        for(int i=start; i <= end; i++){
            System.out.print(arr[i] + " ");
        }
    }
    
    public static void main(String args[]) {
        
        int arr[] = {3,5,8,4,5,9,10,8,5,3,4};   // ans = 4 5 9 10 8 5 3 
        // int arr[] = {12, 4, 78, 90, 45, 23};  // ans = {4, 78, 90, 45, 23} 
        //int arr[] = {20, 4, 1, 2, 3, 4, 2, 10}; //  ans = {1, 2, 3, 4, 2} 
        
        subarray(arr);
    }
}
```
