// (✔️)Solved - Sorted LL to BST - 1 approach 
// QOTD 11 March 23 
// ☑️leetcode link : https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/description/

/* ✔️⭐ Approach - 1 (recursion + fastslow logic of LL)
        
    explanation : since the linked list is sorted, so we will find the mid node, then make it as 'root' of BST with its data and split it into 2 parts 'leftPart' and 'rightPart' , then recursively we will create BST's left and right parts using the 'leftPart' and 'RightPart' of linked list 

       ☑️T : O(N)
       ☑️S : O(N)
*/

class Solution {
    
private:
    // fun.2 : this func uses the slow-fast pointer approach to find the mid node in O(n/2) time - where n is number of nodes in linked list
    pair<ListNode*,ListNode*> midPrvOfLLFinder(ListNode* head){

        ListNode* prvOfMid = nullptr;
        ListNode* slow = head, *fast = head;

        while(fast && (fast -> next)){

            prvOfMid = slow;
            slow = slow -> next;
            fast = fast -> next -> next;
        }

        // mid is slow
        return {slow, prvOfMid};
    }

public:
    // main func - to creating balanced BST from sorted LL
    TreeNode* sortedListToBST(ListNode* head) {

        // base case - if linked list has single node then create BST node of it and return ,else if head is null then simply retunr 
        if(!head || !(head -> next)){
            if(head == nullptr) return nullptr;
            return (new TreeNode(head -> val));
        } 

        // finding the mid, and mid-1(prv) node of linked list, then spliting it into 2 parts
        pair<ListNode*,ListNode*> midAndPrvNode = midPrvOfLLFinder(head);
        ListNode* mid = midAndPrvNode.first;
        ListNode* prvOfMid = midAndPrvNode.second;

        prvOfMid -> next = nullptr; // splitting


        // now creating root node of bst from the 'mid' 's data and then retursively creating left and right subtree of the BST, from the left and rigth parts of the splitted sorted linked list 
        TreeNode* root = new TreeNode(mid -> val);
        root -> left = sortedListToBST(head); // left part
        root -> right = sortedListToBST(mid -> next); // right part

        return root;
    }
};
