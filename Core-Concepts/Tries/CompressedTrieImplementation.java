import java.util.HashMap;
import java.util.Map;

/**
 * A node in the Compressed Trie (Radix Tree).
 * Each node contains a map of string edge labels to child nodes,
 * and a flag indicating if this node marks the end of a word.
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
 * Implementation of a Compressed Trie (Radix Tree).
 * Unlike a standard Trie where each edge represents a single character,
 * here edges are labeled with substrings to compress chains of nodes
 * with single children into one edge.
 */
class CompressedTrie {
    TrieNode root;

    CompressedTrie() {
        this.root = new TrieNode();
    }

    /**
     * Inserts a word into the compressed trie.
     *
     * <p>
     * Note: During insertion, the trie may restructure itself when
     * a partial match (longest common prefix) is found with an existing edge.
     * In such cases, we remove and replace children inside the iteration loop.
     *
     * <p>
     * This can potentially lead to {@code ConcurrentModificationException},
     * because Java's {@code HashMap.keySet()} iterator is fail-fast.
     * It detects any structural modifications (like put/remove) after the iterator
     * is created
     * and throws this runtime exception.
     *
     * <p>
     * In our implementation we are safely avoiding the exception since we are
     * returning as soon as we delete a key
     * immediately after modifying the map, so the iterator never advances further
     * i.e the control doesn't reach to the loop again after deletion which is
     * preventing the exception.
     *
     * <p>
     * Safer alternative (that we already implemented below) (future-proof): Iterate
     * over a copy of the keyset
     * using {@code new HashMap<>(curr.children).keySet()}.
     * This way, even if we modify {@code curr.children}, the iteration runs on the
     * copy
     * and no {@code ConcurrentModificationException} occurs.
     *
     * @param word the word to insert
     */
    public void insert(String word) {
        insertHelper(this.root, word);
    }

    private void insertHelper(TrieNode curr, String word) {
        for (String child : new HashMap<>(curr.children).keySet()) {
            String longestCommonPrefix = getLongestCommonPrefix(word, child);
            // case-1:
            // go deeper, to child node with shorter word(removing common prefix from it)
            if (longestCommonPrefix.length() == child.length()) {
                insertHelper(curr.children.get(child), word.substring(longestCommonPrefix.length()));
                return;
            }
            // case-2
            if (longestCommonPrefix.length() > 0) {
                String wordSuffix = word.substring(longestCommonPrefix.length());
                String childSuffix = child.substring(longestCommonPrefix.length());

                TrieNode oldNode = curr.children.get(child);
                curr.children.remove(child);

                TrieNode newNode = new TrieNode();
                curr.children.put(longestCommonPrefix, newNode); // not that this common prefix is not the end it can
                                                                 // have child

                newNode.children.put(childSuffix, oldNode); // we could have created a new node, but since we had a
                                                            // spare node already marked as endNode=true already, so we
                                                            // use this (as it is not linked to anything now)

                if (!wordSuffix.isEmpty()) {
                    TrieNode wordNode = new TrieNode();
                    wordNode.isEnd = true;
                    newNode.children.put(wordSuffix, wordNode);
                } else { // means our word was something like: word = "ca" and child="carpool" so common
                         // part was only ca so we created already 1 node ca and another node rpool, now
                         // for our word we only need to mark already created "ca" (LCP node) as end
                    newNode.isEnd = true;
                }
                return; // new word inserted, lets wrap up (also very imp: hashmaps are fail-first,eg.
                        // currentlly we are on curr node and we delete the curr node, then loop goes to
                        // next iterator there it will throw the 'ConcurrentModificationException' if we
                        // do not return after deleting, alternatively we could use line -> (String
                        // child: new HashMap<>(curr.children.keySet()) i.e iterating over copy of
                        // keyset and then removing element from real map curr.children
            }
        }
        // case-3
        // new node
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
     * Searches for an exact word in the trie.
     *
     * @param word the word to search
     * @return true if the word exists, false otherwise
     */
    public boolean search(String word) {
        return searchHelper(this.root, word);
    }

    private boolean searchHelper(TrieNode curr, String word) {
        if (word.isEmpty()) {
            return curr.isEnd;
        }
        for (String child : curr.children.keySet()) {
            if (word.startsWith(child)) { // go deeper this child
                return searchHelper(curr.children.get(child), word.substring(child.length()));
            }
        }
        return false;
    }

    /**
     * Checks if there exists any word in the trie that starts with the given prefix.
     *
     * @param prefix the prefix to check
     * @return true if at least one word starts with this prefix, false otherwise
     */
    public boolean startsWith(String word) {
        return startsWithHelper(this.root, word);
    }

    private boolean startsWithHelper(TrieNode curr, String word) {
        if (word.isEmpty()) {
            return true;
        }
        for (String child : curr.children.keySet()) {
            String longestCommonPrefix = getLongestCommonPrefix(word, child);
            if (longestCommonPrefix.length() > 0) {
                return startsWithHelper(curr.children.get(child), word.substring(longestCommonPrefix.length()));
            }
        }
        return false;
    }

    /**
     * Deletes a word from the trie if it exists.
     *
     * @param word the word to delete
     * @return true if the word was deleted, false otherwise
     */
    public boolean delete(String word) {
        if (!search(word)) {
            return false;
        }
        return deleteHelper(this.root, word);
    }

    private boolean deleteHelper(TrieNode curr, String word) {
        if (word.isEmpty()) { // word is empty and it is a end node then mark it as not end and return
                              // true(means telling parent to unlink this node) only when it has no children
                              // left
            if (curr.isEnd == true) {
                curr.isEnd = false;
                return curr.children.isEmpty();
            }
            return false;
        }
        for (String child : curr.children.keySet()) {
            String longestCommonPrefix = getLongestCommonPrefix(word, child);
            if (longestCommonPrefix.length() > 0) {
                if (deleteHelper(curr.children.get(child), word.substring(longestCommonPrefix.length())) == true) {
                    curr.children.remove(child); // unlink the child from 'curr' as its of no use
                    return !curr.isEnd && curr.children.isEmpty(); // return true means unlink this curr as well from
                                                                   // its parent (only when it is not an end node i.e
                                                                   // when it is not representing some other word && it
                                                                   // must not have any child)
                }
                return false;
            }
        }
        return false;
    }

}

public class CompressedTrieImplementation {

    public static void main(String[] args) {
        CompressedTrie trie = new CompressedTrie();
        trie.insert("time");
        trie.insert("timing");
        trie.insert("timedeaf");

        System.out.println("-".repeat(20));
        System.out.println("After inserting time, timing, timedeaf :");
        System.out.println("is time present: " + trie.search("time"));
        System.out.println("is timing present: " + trie.search("timing"));
        System.out.println("is timedeaf present: " + trie.search("timedeaf"));
        System.out.println("is timede present: " + trie.search("timede"));
        System.out.println("is abc present: " + trie.search("abc"));

        System.out.println("-".repeat(20));
        trie.delete("timedeaf");
        System.out.println("After deleting timedeaf: ");
        System.out.println("is time present: " + trie.search("time"));
        System.out.println("is timing present: " + trie.search("timing"));
        System.out.println("is timedeaf present: " + trie.search("timedeaf"));

        System.out.println("-".repeat(20));
        trie.delete("time");
        System.out.println("after deleting time: ");
        System.out.println("is time present: " + trie.search("time"));
        System.out.println("is timing present: " + trie.search("timing"));
        System.out.println("is timedeaf present: " + trie.search("timedeaf"));

        /*
         * CompressedTrieImplementation
         * --------------------
         * After inserting time, timing, timedeaf :
         * is time present: true
         * is timing present: true
         * is timedeaf present: true
         * is timede present: false
         * is abc present: false
         * --------------------
         * After deleting timedeaf:
         * is time present: true
         * is timing present: true
         * is timedeaf present: false
         * --------------------
         * after deleting time:
         * is time present: false
         * is timing present: true
         * is timedeaf present: false
         */
    }
}
