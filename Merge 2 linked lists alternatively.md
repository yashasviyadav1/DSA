
# Merge linked list A to LinkedList B at alternate position

## ✔️Approach - 1 (using dummyList)
```java
import java.util.*;
// merge 2 lists at alternative positions 
// 1 2 3 4 5
// 7 6 4 2 
// out put : 1 7 2 6 3 4 4 2 5

class Node{
    int data;
    Node next;
    Node(int data){
        this.data = data;
        next = null;
    }
}

public class MergeListAlternatively {
    
    static void printList(Node head){
        Node temp = head;
        while(temp != null){
            System.out.print(temp.data + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    static Node buildList(int size){
        Scanner scn = new Scanner(System.in);
        Node head = null;
        Node tail = head;
        System.out.print("Enter elements : ");
        for(int i=0; i < size; i++){
            int ele = scn.nextInt();
            Node newNode = new Node(ele);
            if(head == null && tail == null){
                head = newNode;
                tail = newNode;
            }
            else{
                tail.next = newNode;
                tail = tail.next;
            }
        }
        return head;
    }

    public static void main(String[] args){
        // input 
        Scanner scn = new Scanner(System.in);

        System.out.println("Enter list1 size : ");
        int size1 = scn.nextInt();
        Node head1 = buildList(size1);

        System.out.println("Enter list2 size : ");
        int size2 = scn.nextInt();
        Node head2 = buildList(size2);

        System.out.print("list 1 : ");
        printList(head1);
        System.out.print("list 2 : ");
        printList(head2);

        // algo
        Node temp1 = head1, temp2 = head2;
        Node dummyHead = new Node(-1);
        Node dummyTail = dummyHead; // this will be ans list
        while(temp1 != null && temp2 != null){
            dummyTail.next = new Node(temp1.data);
            dummyTail = dummyTail.next;
            dummyTail.next = new Node(temp2.data);
            dummyTail = dummyTail.next;
            temp1 = temp1.next;
            temp2 = temp2.next;
        }
        while(temp1 != null){
            dummyTail.next = new Node(temp1.data);
            dummyTail = dummyTail.next;
            temp1 = temp1.next;
        }
        while(temp2 != null){
            dummyTail.next = new Node(temp2.data);
            dummyTail = dummyTail.next;
            temp2 = temp2.next;
        }

        // printing ans
        System.out.print("Result : ");
        printList(dummyHead.next);
    }   
}

```
