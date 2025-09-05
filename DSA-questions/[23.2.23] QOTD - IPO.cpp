#include<queue>
//☑️solved at leetcode :https://leetcode.com/problems/ipo/

/* ✔️⭐App-1 trying to build an approach using maxHp 

             explanation :- what we will do here is that we need to maximize our capital, so for that we will pick 'k' projects with maximum profits, and every time we pick a project, what we will do is we will add its profit to the 'capital' we already have, and we repeat this untill we have reached our project limit i.e k, and return the maximized final currProfit at the end.

        T : O(knlog(n)) - nlogn for inserting all n nodes into max heap, then while loop with run k times and for each time it will insert elements into max heap which makes time complexity -> O(NlogN) + O(k*NLogN) ==> O(K*N*LogN)

        S : O(N) - for max heap 
*/
// class to store the project 'index', project 'capitalReq', project 'profit' in node
class node{
    public:
        int projIndex;
        int capital;
        int profit;
        node(int projIndex, int capital, int profit){
            this -> projIndex = projIndex;
            this -> capital = capital;
            this -> profit = profit;
        }
};

// compare class to create a maxheap based on the order of 'profit' value of a node 
class compare{
    public:
    bool operator()(node* a, node* b){
        return a -> profit < b -> profit; // max heap 
    }
};

class Solution {

public:
    // Main function
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        
        // create a maxHeap<node*> and create nodes of all elements of the input and then insert these nodes into max heap in increasing order of their profits
        priority_queue<node*, vector<node*>, compare> maxHp;
        
        for(int i = 0; i < profits.size(); i++){
            node* newNode = new node(i, capital[i], profits[i]);
            maxHp.push(newNode);
        }

        int projectsFinished = 0; // to keep track that whether we have reached the project limit (k) or not

        // initially maximized profit is 'w' i.e initial capital, then whenever we get a profit, it will be added to this 
        int currCapital = w;

        // now run a loop while the projectsFinished are lesser then k
        while(!maxHp.empty() && projectsFinished < k){

            // if the top projects req capital is not more the curr Capital, then pick this project (i.e add this profit to the answer, remove it from the max heap's topm and update the currCapital now)
            if((maxHp.top() -> capital) <= currCapital){
                
                // fetch the top node (i.e unexplored project with the maximum profits)
                node* topProject = maxHp.top();

                maxHp.pop();

                // whenever a project is finished, add the profit received from it to the capital we had 
                currCapital += topProject -> profit; // updating currCapital in hand 

                projectsFinished++;

                delete topProject; // free up memory
            }

            // else if this top project is out of budgets of currCapital, then search for another node(proj) (make sure to store the ndoes, so taht we can insert them back)
            else{ 
                vector<node*> temp;  // to keep track of the nodes we need to enter again into the max heap 

                // temporarily removing the nodes of the max heap, to find a affordable,valid project 
                while((!maxHp.empty()) && (maxHp.top() -> capital > currCapital)){
                    temp.push_back(maxHp.top());
                    maxHp.pop();
                }

                // if no project was found under budget, then in that case return the 'currCapital' we have maximized till now
                if(maxHp.empty()) return currCapital;

                //ekse if another project is found under budget then 'pick it'
                node* topProject = maxHp.top();
                maxHp.pop();
                
                currCapital += topProject -> profit;

                delete topProject;
                projectsFinished++;

                // insert back the nodes that are stored in the temp vector into max heap again 
                for(node* i:temp) maxHp.push(i);
                temp.clear();
            }
        }

        return currCapital;

    }
};
