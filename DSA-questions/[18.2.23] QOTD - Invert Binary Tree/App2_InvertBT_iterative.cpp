
/* ✔️⭐Approach - 2 (iterative approach, using queuee)

    T : O(N) 
    S : O(N) - queue
    
    ☑️solved at leetcode : https://leetcode.com/problems/invert-binary-tree

*/
class Solution {
public:
    // Main fucntion
    TreeNode* invertTree(TreeNode* root) {
        
        // exception case - when root is null it cant be inverted 
        if(root == nullptr) return nullptr;

        // creating queue and inserting root into it
        queue<TreeNode*> q;
        q.push(root);

        // traverse each node, while the queue is not emppty 
        while(!q.empty()){
            TreeNode* front = q.front();
            q.pop();

            // inserting left and right childs of front node into queue (only if they are non null)
            if(front -> left) q.push(front -> left);
            if(front -> right) q.push(front -> right);

            // inverting the left and right parts of front node
            TreeNode* temp = front -> left;
            front -> left = front -> right;
            front -> right = temp;
        }

        return root;
    }
};