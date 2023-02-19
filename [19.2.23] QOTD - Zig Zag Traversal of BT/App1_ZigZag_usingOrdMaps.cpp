// ☑️leetcode link : https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal

/* ✔️⭐Approach - 1 (using ordered map(to store elements), and queue(for level order), and pair<TreeNode*,int>)
        
        explanation :- here our approach is simple, we will first find the level order traversal and store it into a ordered_map<int,vec<int>> where we will store 'levelNo' as the key and on that key we will push all the elements on that level eg. for level 0 elemets are {2,6,7,3} so here key will be 0, and value will be a vector of {2,6,7,3} , note here we can not use a unordered map because we need to preserve the order of insertion, which is need of this question....
        so but how will we store the elements at a level into the map ? ans : using 'pair<TreeNode*,int>' means we will make a queue<pair<TreeNode*,int> because we need to take care of the level so the pair.second means levelno of the node pair.first and in this way we will store the elements into the queue to do a level order traversal....At the end when we have all the elements at all their respective levels, in our map, we will traverse the map, and then from level 0 to last level whenever level is even (0,2,4) we will store elements into our 'ans' as it is, but when our level is odd (1,3,5..) we will reverse the elemnts ans then store that into ans (because we need to go right to left in odd levels) 

        ✅T : O(N) - n for level order, n for map
        ✅S : O(N) - for map, queue
  */

// main class
class Solution {
    
public:
    // Main function
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

        if(!root) return {};
        // step 1: create a ordered_map<int,vector<int>> which means(levelno., all the elments at that level), push the root node at level 0
        map<int,vector<int>> map;
        map[0].push_back(root -> val);

        // step 2 : we have to traverse level wise so create a queue<pair<node*,int>> q, (where pair.first is nodes address, and pair.second means level of that particular node) and then start level order traversal
        queue<pair<TreeNode*,int> > q;
        q.push({root, 0}); // created a pair of root with level 0

        while(!q.empty()){

            // fetch out the front pair and fetch the node and its level front it 
            pair<TreeNode*,int> frontPair = q.front();
            int frontLevel = frontPair.second;
            TreeNode* frontNode = frontPair.first;
            q.pop();

            // when frontNode's left child exists , then create pair for it (with level = frontLevel + 1, and child nodes addressand store it into map, and queue
            if(frontNode -> left){
                map[frontLevel + 1].push_back(frontNode -> left -> val);
                q.push({frontNode -> left, frontLevel + 1});
            }

            // similarly for right child 
            if(frontNode -> right){
                map[frontLevel + 1].push_back(frontNode -> right -> val);
                q.push({frontNode -> right, frontLevel + 1});
            }
        }

        
        //create a 2d vector<int> 'ans' , now traverse the map, and for each odd level elements reverse that level and store it into ans, for even levels dont reverse
        vector<vector<int>> ans;
        for(auto i:map){
            int level = i.first;
            vector<int> elements = i.second;

            if(level % 2 != 0){ // odd
                reverse(elements.begin(), elements.end());
                ans.push_back(elements);
            }
            else ans.push_back(elements); // even
        } 

        return ans;
    }
};
