
/*✔️⭐Approach - 2 (best code) done in 1 loop 
    
    T : O(n)
    S : O(1)

*/
class Solution {
    

public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        /* 2 4 3 
          +5 6 4  (from left to right)
          -------
           7 0 1 

           ansLinkedList : -1 (dummyNode)

           initially power = 0

           2 + 5 + (power = 0) => 7     ansLL : -1 -> 7
           now power is 0

           6 + 4 + (power = 0) => 10     ansLL : -1 -> 7 -> 0
           now power is 1 

           4 + 3 + (power = 1) => 8          ansLL : -1 -> 7 -> 0 -> 8
           now power is 0                (8)node

           final linked list : 7 -> 0 -> 8 ☑️

        */

        // now lets add the 2 lists
        ListNode* temp1 = l1;
        ListNode* temp2 = l2;

        ListNode* dummyHead = new ListNode(-1);
        ListNode* dummyTail = dummyHead;

        // lets handle 3 cases in this 1 loop
        // case 1 : when both lists are non consumed, 
        // case 2 : when list1 is consumed and list2 is still left
        // case 3 : when list2 is consumed and list1 is still left
        
        // this loop will break only when both the lists are consumed
        int power = 0;
        while(temp1 || temp2){

            int data1 = 0;
            int data2 = 0;
            if(temp1) data1 = temp1 -> val;
            if(temp2) data2 = temp2 -> val;

            int sum = data1 + data2 + power;

            int onesDig;
            if(sum < 10) onesDig = sum;
            else onesDig = sum % 10;

            // creating a node and then adding it at the end
            ListNode* newNode = new ListNode(onesDig);
            dummyTail -> next = newNode;

            // updating power, t1, t2, dummyTail
            power = sum/10;
            if(temp1) temp1 = temp1 -> next;
            if(temp2) temp2 = temp2 -> next;
            dummyTail = newNode;

        }

        // there can be a case where both lists gets consumed but there is some power left
        if(power != 0){
            ListNode* newNode = new ListNode(power);
            dummyTail -> next = newNode;
            dummyTail = newNode;

        }


        return dummyHead -> next;
        
