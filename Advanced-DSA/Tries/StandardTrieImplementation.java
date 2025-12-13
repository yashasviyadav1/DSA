/**
 * Node of a 'Standard Trie' (also known as prefix tree).
 * Each node contains an array of children (for 26 lowercase letters) and a flag
 * indicating the end of a word.
 */
class TrieNode {
    TrieNode[] children;
    boolean isEnd;

    TrieNode() {
        children = new TrieNode[26];
        isEnd = false;
    }
}

/**
 * Implementation of a Standard Trie (Prefix Tree).
 * Supports insertion, search, prefix checking, and deletion of words.
 */
class Trie {
    private final TrieNode root;

    /**
     * Initializes the Trie with an empty root node.
     */
    Trie() {
        this.root = new TrieNode();
    }

    /**
     * Checks whether there exists any word in the trie that starts with the given
     * prefix.
     *
     * @param word The prefix to check.
     * @return true if there is a word in the trie that starts with the given
     *         prefix, false otherwise.
     */
    public boolean startsWith(String word) {
        TrieNode curr = this.root;
        for (char ch : word.toCharArray()) {
            if (curr.children[ch - 'a'] == null) {
                return false;
            }
            curr = curr.children[ch - 'a'];
        }
        return true;
    }

    /**
     * Inserts a word into the trie.
     *
     * @param word The word to insert.
     */
    public void insert(String word) {
        TrieNode curr = this.root;
        for (char ch : word.toCharArray()) {
            if (curr.children[ch - 'a'] == null) {
                curr.children[ch - 'a'] = new TrieNode();
            }
            curr = curr.children[ch - 'a'];
        }
        curr.isEnd = true;
    }

    /**
     * Searches for an exact word in the trie.
     *
     * @param word The word to search for.
     * @return true if the word exists in the trie, false otherwise.
     */
    public boolean search(String word) {
        TrieNode curr = this.root;
        for (char ch : word.toCharArray()) {
            if (curr.children[ch - 'a'] == null) {
                return false;
            }
            curr = curr.children[ch - 'a'];
        }
        return curr.isEnd;
    }

    /**
     * Deletes a word from the trie if it exists.
     *
     * @param word The word to delete.
     * @return true if the word was successfully deleted, false if it was not found.
     */
    public boolean delete(String word) {
        if (Boolean.FALSE.equals(search(word))) {
            return false;
        }
        deleteHelper(this.root, word, 0);
        return true;
    }

    /**
     * Helper function for delete.
     * Traverses the trie recursively to unmark word endings and prune unused nodes.
     *
     * @param curr  The current TrieNode being traversed.
     * @param word  The word to delete.
     * @param index The current index of the word being processed.
     * @return true if the current node can be deleted (no children and not end of
     *         another word).
     */
    private boolean deleteHelper(TrieNode curr, String word, int index) {
        if (curr == null) {
            return false;
        }
        if (index == word.length()) { // note: we are comparing length with index directly (because we started i=0
                                      // from root node)
            if (curr.isEnd) {
                curr.isEnd = false;
                return true;
            }
            return false;
        }

        int i = word.charAt(index) - 'a';
        if (Boolean.TRUE.equals(deleteHelper(curr.children[i], word, index + 1))) { // returns true means word deleted
            curr.children[i] = null; // delink the deleted child node
            return !curr.isEnd && isEmpty(curr); // this curr is now empty (no childs left) and is not any other words
                                                 // endNode so return true, i.e telling its parent to unlink it
        } else
            return false;
    }

    /**
     * Utility function to check if a TrieNode has no children.
     *
     * @param curr The TrieNode to check.
     * @return true if the node has no children, false otherwise.
     */
    private boolean isEmpty(TrieNode curr) {
        for (TrieNode node : curr.children) {
            if (node != null) {
                return false;
            }
        }
        return true;
    }
}

public class StandardTrieImplementation {
    public static void main(String[] args) {

        Trie trie = new Trie();

        trie.insert("carl");
        trie.insert("cat");
        trie.insert("cab");

        System.out.println("Searching after inserting carl, cat, cab : ");
        System.out.println("-".repeat(20));
        System.out.println("is carl present : " + trie.search("carl"));
        System.out.println("is cat present : " + trie.search("cat"));
        System.out.println("is cab present : " + trie.search("cab"));
        System.out.println("is cabin present : " + trie.search("cabin"));

        System.out.println("-".repeat(20));
        trie.delete("carl");
        System.out.println("After deleting carl");
        System.out.println("is carl present : " + trie.search("carl"));
        System.out.println("is cat present : " + trie.search("cat"));
        System.out.println("is cab present : " + trie.search("cab"));

        /* console output : 

            Searching after inserting carl, cat, cab : 
            --------------------
            is carl present : true
            is cat present : true
            is cab present : true
            is cabin present : false
            --------------------
            After deleting carl
            is carl present : false
            is cat present : true
            is cab present : true
         */
    }
}