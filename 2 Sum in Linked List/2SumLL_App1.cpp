
class Solution {
    /* ✔️Approach - 1 (did using 3 loops)
       
       T : O(N)
       S : O(1)

    */

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
        int power = 0;
        ListNode* temp1 = l1;
        ListNode* temp2 = l2;

        ListNode* dummyHead = new ListNode(-1);
        ListNode* dummyTail = dummyHead;

        // while both temp1, temp2 are non null
        while(temp1 && temp2){

            int onesDigit;
            int sum = temp1-> val + temp2 -> val + power;
            if(sum >= 10) onesDigit = sum % 10;
            else onesDigit = sum;
            ListNode* newNode = new ListNode(onesDigit);
            dummyTail -> next = newNode;
            dummyTail = newNode;

            power = sum/10;
            temp1 = temp1 -> next;
            temp2 = temp2 -> next;

        }

        // while temp1 is non null i.e when list2 is completely traversed, but list1 is still left
        while(temp1){
            int sum = temp1 -> val + power;
            int onesDigit;
            if(sum >= 10) onesDigit = sum % 10;
            else onesDigit = sum;
            ListNode* newNode = new ListNode(onesDigit);
            dummyTail -> next = newNode;
            dummyTail = newNode;
            power = sum/10;
            temp1 = temp1 -> next;
        }

        // while only temp2 is not null i.e when list1 is completely traversed, but list2 is still left
        while(temp2){
            int sum = temp2 -> val + power;
            int onesDigit;
            if(sum >= 10) onesDigit = sum % 10;
            else onesDigit = sum;
            ListNode* newNode = new ListNode(onesDigit);
            dummyTail -> next = newNode;
            dummyTail = newNode;
            power = sum/10;
            temp2 = temp2 -> next;
        }

        // there can be a case where both lists gets consumed but there is some power left
        if(power != 0){
            ListNode* newNode = new ListNode(power);
            dummyTail -> next = newNode;
            dummyTail = newNode;

        }

        
        return dummyHead -> next;
        





        
    }
};