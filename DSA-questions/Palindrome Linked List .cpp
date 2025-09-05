// ☑️leetcode link : https://leetcode.com/problems/palindrome-linked-list/description/

class Solution {

private:
    void isLLPalindromeRec(ListNode* head, ListNode* &leftNode, bool &isPalindrome){
        
        if(!head) return; // if linked list becomes empty, retrun 

        isLLPalindromeRec(head -> next, leftNode, isPalindrome); // rec go to the end of linked list

        if(head -> val != leftNode -> val)
            isPalindrome = false; 
        leftNode = leftNode -> next; // updating the leftNode to 1 step right 
    }
public:
    // main fun
    bool isPalindrome(ListNode* head) {
        
        ListNode* leftNode = head; // this ptr will go from left to right of ll
        bool isPalindrome = true;  
        isLLPalindromeRec(head, leftNode, isPalindrome); // this fun will update the 'isPalindrome' with the correct answer
        return isPalindrome; 
    }
};
