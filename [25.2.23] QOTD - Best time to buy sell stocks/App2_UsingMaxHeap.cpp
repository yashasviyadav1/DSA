// ☑️leetcode link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

/*✔️⭐ Approach - 2 (using max heap<node*>)

    explanation :- so in the prv approach (brute force), what we were doing was finding max profit by considering every node as buying price, and then considering every other node on the right as its respective selling price, but thats too much expensive , so to reduce the time, we here used extra space, and created a max heap of type 'node' and in this node(we have 'data' and 'index')  now create max heap based on the values, but why do we do this? because we will then traverse the whole 'prices' array and considering each element as buying price we will check if the we are on left of the maxEle of array or not, if we are on the left then that means our maxProfit can be updated, if we are on same index as maxHp.top()'s index, then taht means we need to go to the 2nd max element now, which, and so on.

    ✅T : O(N*logN + N*LogN) => O(N*LogN)
       S : O(N) - for max heap 

   🔍 note : we can use 'pair<int,int>' also instead of creating our on class 'node' but i prefer this way.

*/
 
// class : node with 'data' and 'index'
class node{
    public:
        int data;
        int index;
        node(int data, int index){
            this -> data = data;
            this -> index = index;
        }
};

// class compare : to create a max heap based on the 'data' of nodes.
class compare{
    public:
        bool operator()(node* a, node* b){
            return a -> data < b -> data;
        }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {

        // create a class node(with 2 data members data, index)and make sure the order of max heap depends on the data , now create nodes of all the element of 'prices' vector and then insert them into max heap 
        priority_queue<node*, vector<node*>, compare> maxHp;

        for(int i=0; i < prices.size(); i++){
            node* eachNode = new node(prices[i], i);
            maxHp.push(eachNode);
        }

        // now run a loop for all elements of 'prices'
        int maxProfit = INT_MIN;

        int topData;
        int topIndex;
        for(int i=0; i<prices.size(); i++){
            // now whenever the index iequals to the maxHp.top -> index, then this means that while moving from left to right we reached the maxPrice of the nums, so the maxPrice will change now, so pop it 
            node* topNode = maxHp.top();
            topData = maxHp.top() -> data;
            topIndex = maxHp.top() -> index;

            if(i >= topIndex){
                maxHp.pop();
                delete topNode; // freeing up memo
            }
                
            // else when our curr price (prices[i]) is on the left of the maxPrice on right then we need to update the 'maxProfit' if required 
            else if(i < topIndex)
                maxProfit = max(maxProfit, topData - prices[i]);
            
        }

        // if any profit is found then return it, else return 0 (no profit)
        return (maxProfit != INT_MIN)? maxProfit : 0;
        
    }
};