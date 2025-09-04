# Tries

A trie is a tree-like information retrieval data structure whose nodes store the letters of an alphabet. It is also known as a digital tree or a radix tree or prefix tree. Tries are classified into three categories:

1. [**Standard Trie**](https://www.geeksforgeeks.org/dsa/trie-insert-and-search/) (also known as Prefix Trie)
2. Compressed Trie
3. [**Suffix Trie**](https://www.geeksforgeeks.org/dsa/pattern-searching-using-suffix-tree/) (also known as compressed trie of suffixes)

## **1. Standard Trie**

The Trie **data structure** is used to store a set of keys represented as strings. It allows for efficient **retrieval** and **storage** of keys, making it highly effective in handling large datasets. Trie supports operations such as **insertion**, **search**, **deletion** of keys, and **prefix** searches.

![image.png](https://i.ibb.co/gb1XBg7b/image.png)

In a standard trie : Each `TrieNode` consists of : 

- `children` array of 26 `TrieNode` , size 26 represents 26 alphabets of english language i.e each node can be connected to 26 alphabets
- boolean `isLeaf` , represents weather this forms a complete word

![image.png](https://i.ibb.co/ZRG3dMLm/image.png)

*usually have 4 functionalities :* 

- insert
- delete
- search
- startsWith

*Time Complexities ➖*

- search : `O(n)`
- insert : `O(n)`

---

## 2. **Compressed Trie**

A Compressed Trie is an advanced version of the standard trie made for better space management.

*Properties* : - 

- Each nodes(except the **leaf** nodes) have atleast 2 children.
- To derive a Compressed Trie from a Standard Trie, compression of chains of redundant nodes is performed.
- It consists of *grouping, re-grouping and un-grouping* of keys of characters.
- While performing the insertion operation, it may be required to un-group the already grouped characters.
- While performing the deletion operation, it may be required to re-group the already grouped characters.

*In compressed Trie each TrieNode consists of :-* 

- `children` array storing 26 `TrieNodes` representing each alphabet
- `edgeLabel` string of size 26 representing lable of the edge eg. id is one of the edge lable in the trie.
- boolean `isEnd` to mark the end of word or node.

example : 

![image.png](https://i.ibb.co/8n5x27f8/image.png)

example of before grouping : 

![image.png](https://i.ibb.co/2YS8gZPw/image.png)

after grouping : 

![image.png](https://i.ibb.co/27hKzc1p/image.png)

### **Implementing Compressed Trie**

**Insertion**

there are 3 main cases while inserting a word into compressed trie

- **CASE-1** : `child` itself is the Longest Common Prefix(`word` and `child`) i.e LCP’s length = `child.length` . in this case we go deeper for inserting the new word

- **CASE-2** : length of longest common prefix of (`word` and `child`) is < `child.length` i.e some part of `child` does not come in longest common prefix ➖ eg. `word = "Sample"`  and `child = "Sampoo"`  here `LCP = "Samp"` and `word’s remaining suffix = "le"` and `child’s remaining suffix = oo` , now in this case we need to do 3 things ➖
    - we remove the child of x whose value was `Sampoo`
    - as child of x insert new node with value as common Longest common prefix = `Samp` as the child of x
    - now we create 2 new nodes with the `word_remaining_suffix = "le"`   and `child_remaining_suffix = "oo"` and insert them as the child of the node that we created in step2 with value `Samp`
    
    ```java
    // case 2 
    
    before :      new word = "Sample", LCA = "Samp"
    			 (x)
    			  | "Sampoo"
    			  |
    			 ( ) <--child of x
    	 
    	 
    after : 
    			 (x)
    			  | "Samp"
    			  |
    			 ( )       <--child of x
    	"oo" / \ "le"
    			/   \ 
    		( )  ( )
    ```
    

- **CASE-3** : No common prefix → insert as new edge right here


## 3. Suffix Tree

A **suffix trie** is a trie that stores all **suffixes of a string**.

Useful for substring queries.

→ used for fast pattern searching in a string

- ***How is suffix tree approach different from the Boyer Moree Algo and KMP Algo ?***
    - suppose we have `text` of length `n` and a `pattern` of length `m` now in Boyer Moree and KMP we used to preprocess the pattern string and then we search the pattern in the text. The best case time we could achieve was `O(n)`  for searching.
    - In `Suffix Tree Approach` we preprocess the `text` string and make a suffix tree (compressed trie comprising of all the suffixes of the `text` ) , and this is how we can achieve best case `O(m)` time complexity for searching.

***Why does suffix tree searches really fast ?***

- Because any `pattern` (if present) in the string `text` is nothing but a prefix of one of the suffixes of the `text` .
- eg. `text="CARTOON"` and `pattern=”RTO”`  now lets list all the suffixes of the text below :
    - suffixes of text = `CARTOON, ARTOON, RTOON, TOON, OON, ON, N` .
    - as we can see our pattern `RTO` is prefix of the suffix `RTOON`  so since we already have the suffix tree made compressed form so we can search the pattern really fast in `T:O(m)`

***How to build a Suffix Tree for a given text?*** 

As discussed above, Suffix Tree is compressed trie of all suffixes, so following are very abstract steps to build a suffix tree from given text. 1) Generate all suffixes of given text. 2) Consider all suffixes as individual words and build a compressed trie. Let us consider an example text `banana\0` where `\0` is string termination character. Following are all suffixes of `banana\0`

```
banana\0
anana\0
nana\0
ana\0
na\0
a\0
\0
```

If we consider all of the above suffixes as individual words and build a trie, we get following. 

`standard Trie`

![image.png](https://i.ibb.co/VFGG7jm/image.png)

If we join chains of single nodes, we get the following compressed trie, which is the Suffix Tree for given text `banana\0`

lets make it a `compressed Trie` 

![image.png](https://i.ibb.co/HD4dNrjQ/image.png)

***How to search a pattern in the built suffix tree?*** 

Following are abstract steps to search a pattern in the built Suffix Tree.

**1)** Starting from the first character of the pattern and root of Suffix Tree, do following for every character. .....

**a)** For the current character of pattern, if there is an edge from the current node of suffix tree, follow the edge. .....

**b)** If there is no edge, print "pattern doesn't exist in text" and return.

**2)** If all characters of pattern have been processed, i.e., there is a path from root for characters of the given pattern, then print "Pattern found". Let us consider the example pattern as "nan" to see the searching process. Following diagram shows the path followed for searching "nan" or "nana".

![image.png](https://i.ibb.co/01mdtkt/image.png)

***How does this work?***

Every pattern that is present in text (or we can say every substring of text) must be a prefix of one of all possible suffixes. The statement seems complicated, but it is a simple statement, we just need to take an example to check validity of it.