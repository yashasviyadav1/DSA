import java.util.Scanner;

class BST {
    // Node structure
    class Node {
        int key;
        Node left, right;

        public Node(int item) {
            key = item;
            left = right = null;
        }
    }

    Node root;

    // Constructor
    BST() {
        root = null;
    }

    // A) CONSTRUCT / INSERT Operation
    void insert(int key) {
        root = insertRec(root, key);
    }

    // Recursive function to insert a new key
    Node insertRec(Node root, int key) {
        if (root == null) {
            root = new Node(key);
            return root;
        }
        if (key < root.key)
            root.left = insertRec(root.left, key);
        else if (key > root.key)
            root.right = insertRec(root.right, key);
        
        return root;
    }

    // B) SEARCH Operation
    boolean search(int key) {
        return searchRec(root, key);
    }

    boolean searchRec(Node root, int key) {
        if (root == null) return false;
        if (root.key == key) return true;
        
        if (root.key > key)
            return searchRec(root.left, key);
        
        return searchRec(root.right, key);
    }

    // C) DELETE Operation
    void deleteKey(int key) {
        root = deleteRec(root, key);
    }

    Node deleteRec(Node root, int key) {
        if (root == null) return root;

        // Traverse the tree
        if (key < root.key)
            root.left = deleteRec(root.left, key);
        else if (key > root.key)
            root.right = deleteRec(root.right, key);
        else {
            // Node found: Handle 3 cases
            
            // Case 1 & 2: Node with only one child or no child
            if (root.left == null) return root.right;
            else if (root.right == null) return root.left;

            // Case 3: Node with two children
            // Get the inorder successor (smallest in the right subtree)
            root.key = minValue(root.right);

            // Delete the inorder successor
            root.right = deleteRec(root.right, root.key);
        }
        return root;
    }

    int minValue(Node root) {
        int minv = root.key;
        while (root.left != null) {
            minv = root.left.key;
            root = root.left;
        }
        return minv;
    }

    // Utility to print Inorder Traversal
    void inorder() {
        inorderRec(root);
        System.out.println();
    }

    void inorderRec(Node root) {
        if (root != null) {
            inorderRec(root.left);
            System.out.print(root.key + " ");
            inorderRec(root.right);
        }
    }

    // Main Driver Code
    public static void main(String[] args) {
        BST tree = new BST();
        
        System.out.println("--- BINARY SEARCH TREE OPERATIONS ---");
        
        // 1. Construct/Insert
        tree.insert(50);
        tree.insert(30);
        tree.insert(20);
        tree.insert(40);
        tree.insert(70);
        tree.insert(60);
        tree.insert(80);
        
        System.out.print("Inorder traversal of created tree: ");
        tree.inorder();

        // 2. Search
        int keyToSearch = 40;
        System.out.println("Search for " + keyToSearch + ": " + 
                           (tree.search(keyToSearch) ? "Found" : "Not Found"));

        // 3. Delete
        System.out.println("\nDelete 20 (Leaf Node)");
        tree.deleteKey(20);
        System.out.print("Inorder traversal: ");
        tree.inorder();

        System.out.println("Delete 30 (Node with one child)");
        tree.deleteKey(30);
        System.out.print("Inorder traversal: ");
        tree.inorder();

        System.out.println("Delete 50 (Node with two children)");
        tree.deleteKey(50);
        System.out.print("Inorder traversal: ");
        tree.inorder();
    }
}