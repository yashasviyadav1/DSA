
// (Solved)✔️ - max depth of binary tree - (1 approach)

/* ✔️⭐Approach - 1 (using recursion) - improved code
        explanation - recursively traversing the tree and finding the maximum depth of the binary tree.

        ✅ T : O(n)
        ✅ S : O(n) - recursive stack 
*/

//code 
class Solution {
    
private:
    void maxHeightFinder(TreeNode* root, int &ans, int currHeight){

        // base case - when root is null,then save this height and return 
        if(!root){
            ans = max(ans, currHeight);
            return;
        }

        // recursively find height of the left ans right subtree 
        maxHeightFinder(root -> left, ans, currHeight + 1);
        maxHeightFinder(root -> right, ans, currHeight + 1);
 
    }
public:
    int maxDepth(TreeNode* root) {
        int ans = 0; // to return at the end 
        int currHeight = 0;
        maxHeightFinder(root, ans, currHeight);

        return (ans);
    }
};

