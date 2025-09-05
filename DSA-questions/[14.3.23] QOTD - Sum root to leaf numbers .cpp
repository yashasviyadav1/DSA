
#include<string>
class Solution {
    /* ✔️⭐Approach - 1 (recursive approach)
         explanation : using recursion and backtracking, finding all the possible paths from the root to the leaf node's and adding them to 'answer' and returning it
         T : O(N) 
         S : O(N) - recursive stack 
    */
private:
    // fun.2 : to traverse the binary tree, and find all the paths.
    void inorder(TreeNode* root, int &ans, string &currPath){

        
        // base case - when reached leaf node, add this node to currPath, then add currPath to ans, and return 
        if(!root) return;
        if(root -> left == nullptr && root -> right == nullptr){ // leaf 
            currPath += to_string(root -> val);
            ans += stoi(currPath);
            currPath.pop_back();
            return;
        }

        // LNR - add curr root's value to the 'currPath' and recursively so it for left subtree
        currPath += to_string(root -> val); 
        
        inorder(root -> left, ans, currPath); // L
        
        inorder(root -> right, ans, currPath); //R 

        currPath.pop_back(); // backtrack

    }
public:
    int sumNumbers(TreeNode* root) {

        if(!root) return 0;

        int ans = 0; // to store the sum of all paths from root to leaf node
        string currPath = ""; // to store current path

        inorder(root, ans, currPath);

        return ans; 
        
    }
};
