// leetcode link : https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal

/* ✔️⭐⭐ Approach - 2 ( using only queue(BFS) ) - Better approach 
        
        explanation :- this approach is better then the prv one, because here we are only using a queue , that too for level order traversal and no extra datastructure is used
        
        ✅T : O(N)
        ✅S : O(N)

  */

class Solution {
    
public:
    // Main function
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

        if(!root) return {};
        
        // step 1 : create a queue, and insert root into it.
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<int>> ans;// to return at the end

        // we need to also maintain a boolean 'leftToRight = true' which will tell us whether we need to insert elemetns from left to rigth or right to left
        bool leftToRight = true;

        // BFS
        while(!q.empty()){
            
            // now we need to traverse all the nodes of a level 'x'
            int size = q.size();

            vector<int> singleLevelEle(size); // stores the elements at a perticular level
            for(int i = 0; i < size; i++){

                TreeNode* front = q.front();
                q.pop();
                
                // if we are inserting right to left, then insert elements from the end of 'singleLevelEle' to its start, and if we are inserting from left to right, then insert from start to very end of 'singleLevelEle'
                int index = (leftToRight)? i : size - i - 1;
                singleLevelEle[index] = front -> val;

                // insert left and right (if exist) childs of front into queue 
                if(front -> left) q.push(front -> left);
                if(front -> right) q.push(front -> right);
            }

            // ones a level is completely traversed, negate/invert the value of 'leftToRight' boolean's value, and store all the elemnts of this current level into ans 
            leftToRight = !leftToRight;
            ans.push_back(singleLevelEle);
        }

        return ans;
    }
};
