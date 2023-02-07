/* ✔️⭐Approach - 1 (recursively)

        T : O(N)
        S : O(N) - rec call stack

*/

class Solution {
    
public:
    ListNode* reverseList(ListNode* head) {

        // base case - if the head is null or its next is null, then return head
        if(head == nullptr || head -> next == nullptr)
            return head;

        // recursion will reverse the right part of the linked list, and will return the head of reversed linked list
        ListNode* reversedLLHead = reverseList(head -> next);

        // now we need to solve 1 case 
        head -> next -> next = head;
        head -> next = nullptr;

        return reversedLLHead;
        
    }
};