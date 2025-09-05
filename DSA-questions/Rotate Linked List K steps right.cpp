//(✔️)Solved - Rotate LL by k steps to the right  - 1 approach 
// leetcode link : https://leetcode.com/problems/rotate-list/description/

/*✔️⭐ Approach - 1 (creating a 4 step algo to solve this)

            explanation :- 
                        step 1 : find the total count of nodes of LL
                        step 2 : calculate the new head's position in the linked list using 'totalCount' and 'k'
                        step 3 : now arrange the LL by placing 'newHead' at the start of LL and the left part at the end of LL
                        step 4 : return the new Head formed.

        ✅ Time : O(n)
        ✅ Space : O(1)

        🔍note : this is the first approach that comes to my mind.
*/

class Solution {
    
private:
    // fun.2  - to calculate total nodes of LL
    int countNodesLL(ListNode* head){
        
        if(head == nullptr) return 0; // null node does'nt count 
        return 1 + countNodesLL(head -> next); // recursively count right part's nodes then add curr node and return
    }

public:
    ListNode* rotateRight(ListNode* head, int k) {

        // step 1 : , count the number of nodes in LL, then find the position of the node which will be the new head of the rotated linked list
        int totalNodes = countNodesLL(head);
        int newHeadPos = 0;

        // exception case :- 
        // when k == totalNodeeCount OR k == 0 OR head is null OR head is only node of LL, then no need to rotate
        if(!(head) || !(head -> next) || k == 0 || totalNodes == k ) return head;

        if(k > totalNodes){
            // exception case - when k % totalNodes = 0, that means newHead is 'head' only (i.e org list is the rotated list itself, so no need to calculate further)
            if(k % totalNodes == 0) return head;

            newHeadPos = totalNodes - (k % totalNodes) + 1;
        }
            
        else 
            newHeadPos = totalNodes - k + 1;
        
        // step 2 : now go to the new head node and also track just prv node of 'newHead'
        ListNode* newHead;
        ListNode* newHeadPrv;

        ListNode* temp = head;
        int tempCount = 1;
        while(tempCount != newHeadPos){
            newHeadPrv = temp;
            temp = temp -> next;
            tempCount++;
        }  
        newHead = temp;

        // step 3 : now set the prvOfNewHead to null, and then go to the end of the 'newHead's' linked list
        newHeadPrv -> next = nullptr;
        ListNode* newLLTail = newHead;
        while(newLLTail -> next != nullptr) 
            newLLTail = newLLTail -> next;

        // step 4 : finally attach tail's next of newLL to head and set newHead as head, and return 
        newLLTail -> next = head;
        head = newHead;

        return head;

    


        
    }
};
