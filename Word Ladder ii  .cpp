

class Solution {
    /* ✔️Approach - 2  - TLE at TC 32/26  (using modified BFS)

         explanaton - this is a modified version of BFS approach in 'word Ladder i' question so do check out that first, here in the queue we will be storing the 'list' (i.e currPath) 

         we will be storing not the words, but the whole paths into the queue so our queue will me 'queue<vector<string>>' and what we will do is we will traverse 1 level then just before moving to level 2 , we will mark all the 'newWords' occurred in the level 1 as visited, and then move to level 2 and so on so forth.

         IMP note : this approach works fine if u get this question in an interview, even this works fine on gfg : https://practice.geeksforgeeks.org/problems/word-ladder-ii/1

        ✅Time : O((n^2)*m*26)
        Space : O(n*m) - n is number of words, m is av length of a word

    */

private:
    int min(int a, int b){
        if(a < b) return a;
        return b;
    }

    void BFS(unordered_set<string> &wordSet, vector<vector<string>> &ans, string src, string endWord){

        wordSet.insert(src);

        queue<vector<string>> q;
        q.push({src});
        wordSet.insert(src); // since there is no prv level's new words so mark src as visited rn.

        bool shortestPathsFound = false;
        while(!q.empty()){

            // find the size of queue (and traverse current level)
            int size = q.size();

            vector<string> currLevelNewWords; // this will store all the newWords that were added during the 'currLevelNewWords' (and ones the currLevel is completely traversed, i.e the below for loop ends we will visit all the newWords present in the 'currLevelNewWords')

            for(int i=0; i < size; i++){

                vector<string> currPath = q.front();
                string currWord = q.front().back(); // last word of vector

                // if our currWord is the 'endWord' means all the shortest paths to reach 'endWord' are alrady in the q, so break this loop
                if(currWord == endWord){
                    shortestPathsFound = true;
                    break;
                }

                q.pop(); // do not put this before if cond (coz that will delete 1 path from q)


                // if currWord is not the 'endWord' then,
                // try all the possible combinations of characters on all indices of the 'currWord' (but 1 char at 1 index at a time), and try to find a new Word
                for(int i=0; i < currWord.length(); i++){
                    for(char ch='a'; ch<='z'; ch++){

                        string newWord = currWord;
                        newWord[i] = ch;

                        // if this newWord is not visited yet, and also it is present in the 'wordList' then store it into q (also store it into 'currLevelNewWords' vector)
                        if((wordSet.find(newWord) != wordSet.end()) && (newWord != currWord)){ // means word is unvisited and present in wordList as well
                            vector<string> newPath = currPath;
                            newPath.push_back(newWord);
                            q.push(newPath);
                            currLevelNewWords.push_back(newWord);

                            cout << "working" << endl;
                            
                        }
                    }
                }

            }

            if(shortestPathsFound) 
                break;

            // marking all 'currLevelNewWords' visited, so that the they do not gets added in the path again, (coz that will only make the path longer only )
            for(string word:currLevelNewWords)
                wordSet.erase(word);
        }

        // now shortest paths are present in the queue, so fetch only those whoes ending is 'endWord' 
        while(!q.empty()){
            if(q.front().back() == endWord)
                ans.push_back(q.front());
            q.pop();
        }
    }

public:
    // main func
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        
        unordered_set<string> wordSet(wordList.begin(), wordList.end());  // in this all the unvisited words of wordList will be stored, since initially all are unvisited, so store them

        string src = beginWord;
        vector<vector<string>> ans; // to return at the end

        // this fun will will the ans with all the shortest paths to reach 'endWord'
        BFS(wordSet, ans, src, endWord);

        return ans;

    }
};
