// Solved(✔️) - Check if binary tree is complete BT or not  - 1 approach 

// QOTD 15 Mar 23
// ☑️leetcode link :  https://leetcode.com/problems/check-completeness-of-a-binary-tree/description

/* ✔️⭐Approach - 1 (recursive approach)
            
            explanation : we will calculate the number of nodes in the binary tree we will check the index of each node if we reached a node whose index is more then the number of nodes that means that we must have came across a 'null' node in the left subtree previously, so it can not be a complete Binary Tree, else it is complete, also note that we are here starting indexing for nodes from 1 so for any parent node (left child's index = 2*ParentIndex) and (right child's index = 2*ParentIndex + 1) 
        ✅T : O(N)
        ✅S : O(N) - recursive
*/

class Solution {

    
private:
    // fun.2  : counts number of nodes, and returns the count 
    int countTotalNodesInBT(TreeNode* root){

        if(!root) return 0; // when root is null, there is no node in BT 
        // recursively finding the count of nodes from left and right BT, then add curr root into that count and return it 
        return countTotalNodesInBT(root -> left) + countTotalNodesInBT(root -> right) + 1; 
    }

    // fun.3 : to check if BT is complete or not 
    bool isBTComplete(TreeNode* root, int &totalNodesCount, int index){

        // base case - if root is null, it is a complete BT
        if(!root) return true;

        if(index > totalNodesCount) return false; // VIP : read explanation at top

        // recursively find if left and right subtrees are complete, and if atleast 1 of them is not complete (use && ) return false
        return (isBTComplete(root -> left,totalNodesCount, index*2) && isBTComplete(root -> right,totalNodesCount, index*2+1)); 
    }

public:
    // main function
    bool isCompleteTree(TreeNode* root) {
        
        // calculate the number of nodes in BT 
        int totalNodesCount = countTotalNodesInBT(root); 
  
        // now we will use a variable 'index' and 'totalNodes' to find if BT is complete (1 based indexing)
        return isBTComplete(root, totalNodesCount, 1); 
        
    }
};

