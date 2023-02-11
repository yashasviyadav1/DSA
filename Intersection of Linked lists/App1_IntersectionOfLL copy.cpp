
/* ✔️Approach - 1  (using 2 vectors<node*> )

        // slow solution

        ☑️solved at leetcode : https://leetcode.com/problems/intersection-of-two-linked-lists
        ⚠️TLE at gfg : https://practice.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article


        T : O(n*m)
        S : O(n+m) 

*/

class Solution {
    
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        
        // create 2 vector<Node*> and store both lists into the sets
        vector<ListNode*> list1;
        vector<ListNode*> list2;

        ListNode* temp1 = headA;
        ListNode* temp2 = headB;
        while(temp1){
            list1.push_back(temp1);
            temp1 = temp1 -> next;
        }

        while(temp2){
            list2.push_back(temp2);
            temp2 = temp2 -> next;
        }

        // traverse set1 , and check if its node is present in set2 , then we found the intersetion
        for(ListNode* node1:list1){
            for(ListNode* node2:list2){
                if(node1 == node2) return node1;
            }
        }   
        
        return nullptr;



    }

};



