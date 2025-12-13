import java.util.HashMap;
import java.util.Map;


// prerequisite : In order to understand this go to CompressedTrieImplementation.java file and first understand that 
// suffix trie itself is nothing but a compressed trie in which we are inserting all suffixes of a string
// in order to search pattern in that string in pattern.length time 

/**
 * A node in the Suffix Trie (which is essentially a compressed trie storing all suffixes of a string).
 * 
 * Each node contains:
 * - {@code children}: a map from substring keys to child nodes. Using {@link HashMap} allows 
 *   dynamic branching for compressed segments.
 * - {@code isEnd}: a boolean that marks whether the node represents the end of a word/suffix.
 */
class TrieNode {
    Map<String, TrieNode> children;
    boolean isEnd;

    TrieNode() {
        isEnd = false;
        children = new HashMap<>();
    }
}

/**
 * Suffix Trie implementation using a compressed trie structure.
 * <p>
 * A Suffix Trie stores all suffixes of a given text. This allows efficient substring search 
 * in {@code O(m)} time, where {@code m} is the length of the pattern.
 * </p>
 * <p>
 * Design notes:
 * <ul>
 *   <li>This implementation compresses edges by storing substrings (not single characters) as keys.</li>
 *   <li>During insertion, edges are split based on the longest common prefix between 
 *       the word being inserted and existing keys.</li>
 *   <li>Instead of copying {@code children} (which would cause overhead), we carefully 
 *       separate iteration from modification to avoid {@link java.util.ConcurrentModificationException}.</li>
 * </ul>
 */
class SuffixTrie {
    TrieNode root;

    /**
     * Constructs a suffix trie for the given text by inserting all suffixes of the text.
     *
     * @param text the input string whose suffixes will be stored in the trie
     */
    SuffixTrie(String text) {
        this.root = new TrieNode();
        buildSuffixTrie(text); // processing text
    }

    /**
     * Builds the suffix trie by inserting all suffixes of the input string.
     *
     * @param text the input string
     */
    private void buildSuffixTrie(String text){
        for(int i=text.length()-1; i >= 0; i--){
            insert(text.substring(i));
        }
    }

    /**
     * Inserts a word into the suffix trie.
     *
     * @param word the word (or suffix) to insert
     */
    public void insert(String word) {
        insertHelper(this.root, word);
    }

    /**
     * Recursive helper for inserting a word into the compressed trie.
     * <p>
     * Handles three cases:
     * <ul>
     *   <li>Full match with an existing edge → recurse deeper.</li>
     *   <li>Partial match → split edge into prefix + suffixes.</li>
     *   <li>No match → create a new edge.</li>
     * </ul>
     *
     * @param curr current trie node
     * @param word remaining substring to insert
     */
    private void insertHelper(TrieNode curr, String word) {
        for (String child : curr.children.keySet()) {
            String longestCommonPrefix = getLongestCommonPrefix(word, child);
            // Case 1: Full match with existing edge
            if (longestCommonPrefix.length() == child.length()) {
                insertHelper(curr.children.get(child), word.substring(longestCommonPrefix.length()));
                return;
            }
            // Case 2: Partial match, split edge
            if (longestCommonPrefix.length() > 0) {
                String wordSuffix = word.substring(longestCommonPrefix.length());
                String childSuffix = child.substring(longestCommonPrefix.length());

                TrieNode oldNode = curr.children.get(child);
                curr.children.remove(child);

                TrieNode newNode = new TrieNode();
                curr.children.put(longestCommonPrefix, newNode); 

                newNode.children.put(childSuffix, oldNode); 

                if (!wordSuffix.isEmpty()) {
                    TrieNode wordNode = new TrieNode();
                    wordNode.isEnd = true;
                    newNode.children.put(wordSuffix, wordNode);
                } else {
                    newNode.isEnd = true;
                }
                return;
            }
        }
        // Case 3: No common prefix, create new child
        TrieNode newNode = new TrieNode();
        newNode.isEnd = true;
        curr.children.put(word, newNode);
    }

    /**
     * Finds the longest common prefix between two strings.
     *
     * @param str1 first string
     * @param str2 second string
     * @return longest common prefix
     */
    private String getLongestCommonPrefix(String str1, String str2) {
        int minLen = Math.min(str1.length(), str2.length());
        int i = 0;
        while (i < minLen && str1.charAt(i) == str2.charAt(i)) {
            i++;
        }
        return str1.substring(0, i);
    }

    /**
     * Searches for a substring in the suffix trie.
     * <p>
     * Since we inserted all suffixes, searching for a pattern corresponds to 
     * following compressed edges. The check ignores {@code isEnd} because we 
     * only need to know if the substring exists, not whether it ends at a suffix.
     *
     * @param word the pattern to search
     * @return {@code true} if the pattern exists in the text, otherwise {@code false}
     */
    public boolean search(String word){
        return searchHelper(this.root, word);
    }

    /**
     * Recursive helper for searching a word in the suffix trie.
     *
     * @param curr current trie node
     * @param word remaining substring to match
     * @return {@code true} if found, otherwise {@code false}
     */
    private boolean searchHelper(TrieNode curr, String word){
        if(word.isEmpty()){ // while searching a patter (i.e a subsrting) we do not care if node is end node or not we always return true
            return true;
        }
        for(String child:curr.children.keySet()){
            String longestCommonPrefix = getLongestCommonPrefix(word, child);
            if(longestCommonPrefix.length() > 0){
                return searchHelper(curr.children.get(child), word.substring(longestCommonPrefix.length()));
            }
        }

        return false;
    }

}


public class SuffixTrieImplementation{

    public static void main(String[] args){
        String text = "bananna";
        SuffixTrie trie = new SuffixTrie(text);
        System.out.format("is %s present in %s : %s \n", "ana", text, trie.search("ana"));
        System.out.format("is %s present in %s : %s \n", "nn", text, trie.search("nn"));
        System.out.format("is %s present in %s : %s \n", "ba", text, trie.search("ba"));
        System.out.format("is %s present in %s : %s \n", "nl", text, trie.search("nl"));
        /*
            s ana present in bananna : true 
            is nn present in bananna : true 
            is ba present in bananna : true 
            is nl present in bananna : false 
         */
    }
} 