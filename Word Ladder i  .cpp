class Solution {
/* ✔️⭐Approach - 1 (Using BFS)

        algo :- suppose we have word 'how' we need to reach wordEnd = 'gew' now whats the brute force that comes to ur mind, it is that we will try all cominations of characters on indexes of word 'how' and try to make in 'gew' with a sequence which is already present in the array 'wordList' and as we store the new version of word how into the queue make sure to visit it. now lets say word is 'how' now we need to place all char from a to z on each of the index of this word 'how' and we will check every time if the new word which is formed is 'not yet visited' then push it into q and visit it (because in BFS we find a node by  default with its shortest possible distace, so if we found a already found a word, then that means that in case we find it again, we can not find it with a shorter distace anywhere else)

        for test case 1 BFS will go like this 
   
            hit     --level1 
            |
            hot     --level2 
            / \ 
          dot  lot  -- level3
          /    / 
        dog   log   -- level4
        /
      cog          --level5 (found our endWord = cog on level 5 - shortest distance)


      ✅Time : O(26*n*m) - where n is number of words, m is length of av word, 26 is characters   
      ✅Space : O(n*m) - for maps 
      
      ☑️leetcode link : https://leetcode.com/problems/word-ladder/
    
*/
  
public:
    // Main func
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        // we need to maintain what 'strings' are present in the wordList, and also which strings are visited 
        unordered_map<string,bool> isStringVisited;
        unordered_map<string,bool> isStringPresentInWordList;

        for(int i=0; i < wordList.size(); i++){
            isStringVisited[wordList[i]] = false; // by default all strings are unvisited
            isStringPresentInWordList[wordList[i]] = true; // set all wordList strings as visited
        }

        // lets start bfs (algo)
        queue<pair<string,int>> q; // pair(string, level on which it was found during BFS)
        q.push({beginWord,1});
        isStringVisited[beginWord] = true;

        while(!q.empty()){

            string word = q.front().first;
            int level = q.front().second;
            q.pop();

            if(word == endWord) return level; // we reached the 'endWord' already

            // now lets say word is 'how' now we need to place all char from a to z on each of the index of this word 'how' and we will check every time if the new word which is formed is 'not yet visited' then push it into q and visit it (because in BFS we find a node by  default with its shortest possible distace, so if we found a already found a word, then that means that in case we find it again, we can not find it with a shorter distace anywhere else)
            for(int i=0; i < word.length(); i++){
                
                for(char ch='a'; ch <= 'z'; ch++){
                    string newWord = word;
                    newWord[i] = ch;  // inserting new character into word

                    if( isStringPresentInWordList[newWord] && !isStringVisited[newWord] ){ // when new word is present in 'wordList' and its also not visited, then we should go by this path , else ignore this newWord.
                        isStringVisited[newWord] = true;
                        
                        //we reached endWord
                        if(newWord == endWord) return level+1;

                        q.push({newWord,level+1});

                    }
                }
            }
        }


        // if q becomes empty that means no way to reach the endWord
        return 0;
    }
};
