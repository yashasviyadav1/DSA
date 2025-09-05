// ☑️Leetcode link : https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/

/* ✔️⭐Approach - 1 (Recursion + backtracking)

    explanation :- Idea is to go till the end and while returning we will be incrementing the count and ones we reached the kth node from the end, we will be deleting it and connection the prv and next node of the 'head' so that they do not get lost in the operation, also we need to keep track of the prvNode as well, coz it will be connected to next node of 'head' ones the head gets deleted, also there are 2 imp cases to keep in mind :- 
        Case 1 ) if the node to be deleted is the first node of the linked list
                        -  then in that case we our prv is null, so runtime error will be thrown, so make sure that if there is no node on the left of head, so delete head and head's next node becomes the head of new linked list 
        Case 2 ) if the node to be deleted is in middle 
                        - then in that case, prvOfHead will become the new head ones the deletion has been taken place

        Time : O(n)
        Space : O(n) - recursive call stack
        
*/
class Solution {
private:
    // this fun delete the nth node from end, and returns head of the LL
    ListNode* solve(ListNode* head, ListNode* prvOfHead, int k, int &countFromEnd){

        if(!head) return nullptr; // if reached end then return

        solve(head -> next, head, k, countFromEnd); // recursion will delete the nth node if it is present in the right of head, and return new head

        // solving 1 case - if head is the nth node, then deleting it and making a new node 'head'
        if(++countFromEnd == k){

            if(prvOfHead == nullptr){ //edge case-1
                ListNode* temp = head;
                head = head -> next;  // new head 
                temp -> next = nullptr; // removing links for deletion
                delete temp;
            }
            else{ // prv is not null that means new head will be 'prv'
                prvOfHead -> next = head -> next;
                ListNode* temp = head;
                temp -> next = nullptr;  // removing links for deletion
                delete temp;
                head = prvOfHead; // new head  
            }
        }

        return head;// ones deletion is done retunr the new head
        
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int k) {

        if(!head || !(head -> next))// exception case - if linked list is empty or has only one node
            return nullptr;

        // we need to maintain 'k' 'countFromEnd' 'prvOfHead'
        ListNode* prvOfHead = nullptr;
        int countFromEnd = 0;

        head = solve(head, prvOfHead, k, countFromEnd); // deleting nth node and after that storing new 'head'
  
        return head;
        
    }
};
