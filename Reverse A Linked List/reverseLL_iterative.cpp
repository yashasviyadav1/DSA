
class Solution {
    
/*✔️⭐ approach - 1 (iterative approach)

       T : O(N)
     ✅S : O(1)

*/
public:
    ListNode* reverseList(ListNode* head) {
        
        /* (case - 1 & 2) when Linked List is empty or LL has only 1 node present in it */
        if(head == nullptr) return head;
        if(head -> next == nullptr) return head;
    
        ListNode* previous = head;
        ListNode* current = previous -> next;
        ListNode* last = current -> next;
    
        // setting 1st node to null (to make it last node)
        previous -> next = NULL;
    
        /* (case - 3) when linked list is having 2 or more nodes */
        //reversal will run untill last pointer reaches null i.e out of loop 
        while(last != NULL){
            current -> next = previous;
            previous = current;
            current = last;
            last = last -> next;
        }
        current -> next = previous;
        head = current;
        
        return head;
    }
};