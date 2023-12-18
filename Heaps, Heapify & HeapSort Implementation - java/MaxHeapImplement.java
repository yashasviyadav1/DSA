import java.util.*;

// implementation of Max Heap  

class MaxHeap{ // Max Heap

    int arr[];
    int size;

    MaxHeap(){ // constructor
        arr = new int[99999];
        size = 0;
        arr[0] = -99999;
    }

    void push(int data){// insersion
        size++;
        int index = size;
        arr[index] = data;

        while(index > 1){ // placing newly inserted node at its correct position

            int parentIndex = index/2;
            if(arr[parentIndex] < arr[index]){ // parent < child, swap them both

                int temp = arr[parentIndex]; // swap values
                arr[parentIndex] = arr[index];
                arr[index] = temp;

                index = parentIndex; //update the childs index, coz it has shifted to above now 
            }
            else return; // node placed at its correct position
        }
    }

    void pop(){

        int deletedElement = arr[1]; 
        arr[1] = arr[size];
        size--;
        int index = 1 ; // lets place this top element at its coorect position
        System.out.println("popped " + deletedElement + " from top");

        while(index < size){

            int leftChildIndex = 2*index;
            int rightChildIndex = 2*index + 1;

            // in max heap largest value is on top
            int smallestChildIndex = index;

            if(leftChildIndex <= size && arr[leftChildIndex] > arr[index])
                smallestChildIndex = leftChildIndex;

            if(rightChildIndex <= size && arr[rightChildIndex] > arr[smallestChildIndex])
                smallestChildIndex = rightChildIndex;
            
            // if we found that at least 1 child has smaller value then swap
            if(smallestChildIndex != index){ // swap parent and smaller child
                int temp = arr[index]; // swap values
                arr[index] = arr[smallestChildIndex];
                arr[smallestChildIndex] = temp;

                index = smallestChildIndex;// updated index of parent
            }
            else break;//node placed at its correct position

            // System.out.println("index " + index + " is " + arr[index] + " and size of heap : " + size);
        }

    }

    void print(){
        if(size == 0){
            System.out.println("Can't print empty heap");
        }

        for(int i=1; i <= size; i++)
            System.out.print(arr[i] + " ");
        System.out.println();
    }

    
}

class MaxHeapImplement{

    public static void main(String ... args){
        
        MaxHeap maxHp = new MaxHeap();

        maxHp.push(10);        
        maxHp.push(20);
        maxHp.push(8);
        maxHp.push(9);       
        maxHp.push(2);

        System.out.println("max heap : ");
        maxHp.print();
        /*
         
            20
           /  \
          10   8
         /  \
        9    2 

        20, 10, 8, 9, 2
         
         */

         maxHp.pop();

         
        /*
         
            10
           /  \
          9   8
         /  
        2     

        10, 9, 8, 2
         
         */

        System.out.println("max heap : ");
        maxHp.print();

        maxHp.pop();        
        maxHp.pop();
        maxHp.pop();

        

        System.out.println("max heap : ");
        maxHp.print();



    }
}