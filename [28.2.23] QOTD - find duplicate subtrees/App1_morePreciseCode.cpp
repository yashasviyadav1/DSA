
class Solution {
    /*✔️⭐ Approach - 1 (using string representation concept + unordered_map) - more precise code 

            explanation :- lets take a graph 

                            10
                           /  \
                          2    3 
                         /
                        4   
                        
                        string representation of this graph (with LNR) is :- ( (4) 2) ) 10 (3)) , so we can store each and every node's string representaiton into a map with its occurrence, and whenever occurrence becomes 2, means a diuplicate root is found so, store it into the map

        ☑️T : O(N) - for recursively finding the stringReq 
           S : O(N) - recursive stack, map
    */  
private:
    // fun.2
    string stringRepWithFreq(TreeNode* root, vector<TreeNode*> &dupliSubtrRoots, unordered_map<string, int> &stringToFreq){
        // base case - if root is null, its string rep is nothing 
        if(!root) return "";

        // LNR - start the bracket, recursively find the left 'stringRep' then close bracket, then add roots data to it, then start bracket, recursively find 'stringRep' of right subtree and close the bracket 
        string strRepresentation = "";

        strRepresentation += '(' + stringRepWithFreq(root -> left, dupliSubtrRoots, stringToFreq) + ')' + to_string(root -> val) + '(' + stringRepWithFreq(root -> right, dupliSubtrRoots, stringToFreq) + ')';
        // note : do not do ( strRep += int ) this will store the asci of int into string.
        
        // now increment this string's freq in the map, and if it becomes 2, then store the currRoots address into 'dupliSubtrRoots' vector
        stringToFreq[strRepresentation]++;
        if(stringToFreq[strRepresentation] == 2) dupliSubtrRoots.push_back(root);

        // at the end return the string 
        return strRepresentation;
    }
public:
    // main function
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {

        // we need a unordered_map<string,int> unmap(string representation, number of times it occurs in tree)
        unordered_map<string,int> stringToFreq;

        // we need to find the string representation (LNR) and maintain its freq, and also we need to fill up the 'dupliSubtrRoots'
        vector<TreeNode*> dupliSubtrRoots;
        stringRepWithFreq(root, dupliSubtrRoots, stringToFreq);

        /* DEBUG - printing map
        */
        for(auto i:stringToFreq){
            cout << i.first << " -> " << i.second << endl; 
        }
        return dupliSubtrRoots;
        
    }
};