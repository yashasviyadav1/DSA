/* ✔️⭐⭐Approach - 1 (purely recursive)

        T : O(n)
        S : O(n) - recursive 

    ☑️solved at leetcode : https://leetcode.com/problems/invert-binary-tree

*/

class Solution {
    
public:
    // main function
    TreeNode* invertTree(TreeNode* root) {

        // base case - if root is null, its inversion will be null 
        if(!root) return nullptr;

        // recursion will invert the left subtree and then return the 'invertedLeftRoot' similarly the 'invertedRightRoot'
        TreeNode* invertedLeftRoot = invertTree(root -> left);
        TreeNode* invertedRightRoot = invertTree(root -> right);

        // ones we have the left and right subtrees inverted, we need to join the leftInverted subtree to the right of BT, and rightinverted subtree to the left of BT
        root -> left = invertedRightRoot;
        root -> right = invertedLeftRoot;

        return root;
        
    }
};