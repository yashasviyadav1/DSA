// (✔️)Solved - create BT from inorder postorder - 1 approach 
// QOTD - 17 Mar 23
// ☑️leetcode link : https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/


/* ✔️⭐Approach - 1 (using recursrion and unordered_map)
    
    explanation : we are given inorder(LNR) and postorder(LRN) so observe that we can find root node of tree from the right end of postorder every time, ones we know the root node we will search at what index it is present in the inorder vector, ones we know the index 'foundAtInIndex' we know that inorder is [Left Root Right] so the right array of that 'foundAtInIndex' will can be used to make the right subtree of BT and left part will be used to create left subtree of BT using recursion, but the most imp question is should we create the left subtree first or the right subtree first (recursively), so to answer this observe that the postorder is (left Right Root ) so we are traversing the postorder array from the end of it to the start, so going this way the right part comes first, so first create right part then create left part recursively.
 
    ✅T : O(N)
    ✅S : O(N) - for map, and recursive stack 
*/

#include<unordered_map>
class Solution {
    
private:
    //fun.2 
    TreeNode* BTfromInPost(vector<int>& inorder, vector<int>& postorder, unordered_map<int,int> &eleToInorderIndex, int inStart, int inEnd, int &postEnd){

        // base case - if the InStart > InEnd means we can not form a BT with it 
        if(inStart > inEnd) return nullptr;

        // create rootData from the postorder[postEnd] , now create root from this data, and search at which index this 'rootData' is found in inorder array
        int rootData = postorder[postEnd];
        TreeNode* root = new TreeNode(rootData);
        
        int foundAtInIndex = eleToInorderIndex[rootData];

        // decrement the 'postEnd' and recursively create 'right' subtree first , then 'left subtree'
        postEnd--;
        root -> right = BTfromInPost(inorder, postorder, eleToInorderIndex, foundAtInIndex + 1, inEnd, postEnd);
        root -> left = BTfromInPost(inorder, postorder, eleToInorderIndex, inStart, foundAtInIndex -1, postEnd);

        return root; // tree created
    }

public:
    // main function
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {

        // in our approach we need to search for 'index' of an 'element' in inorder array, so to reduce time complexiy we can map element (key) to inorderIndex (value) 'eleToInorderIndex'  
        unordered_map<int,int> eleToInorderIndex;
        for(int i=0; i < inorder.size(); i++)
            eleToInorderIndex[inorder[i]] = i;

        // we need to maintain the range of elements using 2 pointers of inorder 'inStart' and 'inEnd', also we need to find root node from the end of postorder, so maintain 'postEnd'
        int inStart = 0;
        int inEnd = inorder.size() - 1;
        int postEnd = postorder.size() - 1;

        // now call a fun.2 to create the BST and return its root
        return BTfromInPost(inorder, postorder, eleToInorderIndex, inStart, inEnd, postEnd);

        
    }
};
