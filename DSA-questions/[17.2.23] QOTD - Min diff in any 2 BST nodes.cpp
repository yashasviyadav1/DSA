
// QOTD 17 Feb 23 
// ☑️leetcode link : https://leetcode.com/problems/minimum-distance-between-bst-nodes/

/*✔️⭐ Approach - 1 (find inorder and traverse it)

    basic idea :- lets say we have inorder now, so what we can do is we can check difference of every node with every other node in the inorder which will take time of O(n^2) but if we try to analyse we know that inorder is always sorted so (lets say inorder = {3,6,8,10,18,45} so if we find differece of 0th and 1st index element we get 6-3 => 3 now if we subtract 3(0th index) with any other elemnet then we know difference will be always larger or equal to 3, not less then that, so we dont need to compare an element with every other element, instead compare adj elements difference only which will reduce time from n^2 to n only)

        ✅T : O(N) - n for finding inorder, and then n for traversing the inorder vector
        S : O(N)- for storing inorder and for, recursive stack (inorder func)
        
*/

class Solution{

    // func.2 : to find inorder recursively 
    void findInorder(TreeNode* root, vector<int> &inorder){

        // base case
        if(!root) return;

        // LNR - inorder
        findInorder(root -> left, inorder);
        inorder.push_back(root -> val);
        findInorder(root -> right, inorder);
    }

    // fun.3 : finds mod of difference of 2 numbers
    int positiveDifference(int num1, int num2){
        return (num1 > num2)? num1-num2 : num2-num1;
    }
    
public:
    int minDiffInBST(TreeNode* root) {

        // step 1 : find inorder of BST and store it in vector<int> inorder
        vector<int> inorder;
        findInorder(root, inorder);

        // step 2 : compare adj nodes of inorder and find the min diff node, return it at the end 
        int ans = INT_MAX; // coz we want minimum ans 
        for(int i=0; i < inorder.size()-1 ; i++){
            int diff = positiveDifference(inorder[i],inorder[i+1]) ;
            ans = min(ans, diff);
        }
        
        // return ans
        return ans;
    }
};
