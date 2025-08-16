
import java.util.LinkedList;
import java.util.Queue;

class Node<T> {
    int height;
    T value;
    Node<T> left, right;
    Node(T value) {
        this.height = 1;
        this.value = value;
        this.left = this.right = null;
    }
}

// AVL Tree are BST but with balance factor
class AVLTree<T extends Comparable<T>> {
    Node<T>root;
    public int height(Node<T>node){
        return node == null ? 0 : node.height;
    }

    public boolean contains(T key){
        return containsHelper(root, key);
    }
    private boolean containsHelper(Node<T> node, T key){
        if(node == null) { 
            return false;
        }
        if(key.compareTo(node.value) == 0) {
            return true;
        }
        else if(key.compareTo(node.value) > 0) {
            return containsHelper(node.right, key);
        }
        else{
            return containsHelper(node.left, key);
        }  
    }

    public Node<T> insert(T key){
        return root = insertHelper(root, key);
    }

    private Node<T> insertHelper(Node<T> node, T key){
        if(node == null) {
            return new Node<>(key);
        }
        if(key.compareTo(node.value) < 0) {
            node.left = insertHelper(node.left, key);
        }
        else if(key.compareTo(node.value) > 0) {
            node.right = insertHelper(node.right, key);
        }
        else{ // duplicate keys are not allowed
            return node;
        }

        // after insertion, update the height of the node, and balance if necessary
        node.height = 1 + Math.max(height(node.left), height(node.right));
        int balancingFactor = getBalancingFactor(node);

        // left heavy (LL, LR)
        if(balancingFactor > 1) {
            if(key.compareTo(node.left.value) < 0){
                node = rotateRight(node);
            }
            else{
                node.left = rotateLeft(node.left);
                node = rotateRight(node);
            }
        }
        
        // right heavy (RR, RL)
        if(balancingFactor < -1) {
            if(key.compareTo(node.right.value) > 0){
                node = rotateLeft(node);
            }
            else{
                node.right = rotateRight(node.right);
                node = rotateLeft(node);
            }
        }
        return node;
    }

    private int getBalancingFactor(Node<T> node){
        return height(node.left) - height(node.right);
    }

/*  This is the example for why we need to store T1 i.e right child of new root (so it never get lost)
       - the reason it is necessary to keep track of T1 is because when we create AVL from scratch, i.e each node 1 by 1 then 
         the balacing is taken care automatically,
         
       - but when we are inserting a node in an existing tree, we need to make sure that the right child of the new root is not lost.


       eg. insert 5 in this tree 

     30  <-- This is the node we will rotate
     /
    20
   /  \
  10   25
 /
5

*/

    private Node<T> rotateLeft(Node<T> y){
        Node<T> x = y.right;
        Node<T> T1 = x.left;
        x.left = y;
        y.right = T1;
        y.height = 1 + Math.max(height(y.left), height(y.right));
        x.height = 1 + Math.max(height(x.left), height(x.right));
        return x;
    }

    private Node<T> rotateRight(Node<T> y){
        Node<T> x = y.left;
        Node<T> T1 = x.right;
        x.right = y;
        y.left = T1;
        y.height = 1 + Math.max(height(y.left), height(y.right));
        x.height = 1 + Math.max(height(x.left), height(x.right));
        return x;
    }

    // delete node

    public void delete(T key) {
        root = deleteHelper(root, key);
    }

    private Node<T> deleteHelper(Node<T> node, T key) {
        if(node == null){
            return null;
        }
        if(key.compareTo(node.value) < 0){
            node.left = deleteHelper(node.left, key);
        }
        else if(key.compareTo(node.value) > 0){
            node.right = deleteHelper(node.right, key);
        }
        else {
            // node to be deleted found
            if(node.left == null){
                return node.right; 
            }
            if(node.right == null){
                return node.left;
            }
            Node<T> inorderSuccessor = getInorderSuccessor(node.right);
            node.value = inorderSuccessor.value;
            node.right = deleteHelper(node.right, inorderSuccessor.value);
        }

        node.height = 1 + Math.max(height(node.left), height(node.right));
        int balancingFactor = getBalancingFactor(node);

        // note : the balncing logic that we did in insertion was based on the key because when a key was inserted
        // a certain type of imbalance was created in the subtree where the key was inserted.
        // so that is the reason we used key to determine the direction of imbalance.
        // In 'DELETION' case, we can not use a key to determinne the imbalace is in which subtree because
        // when lets say key is deleted in right subtree, this will cause the left subtree to be heavier
        // since the key is already deleted, we can not use that in conditions to determine whether it is LL or LR
        // solution : so here we will check balancing of the node itself to determine its type
        if(balancingFactor > 1) {
            if(getBalancingFactor(node.left) >= 0){
                node = rotateRight(node);
            }
            else if(getBalancingFactor(node) < 0){
                node.left = rotateLeft(node.left);
                node = rotateRight(node);
            }
        }
        if(balancingFactor < -1) {
            if(getBalancingFactor(node.right) <= 0){
                node = rotateLeft(node);
            }
            else if(getBalancingFactor(node) > 0){
                node.right = rotateRight(node.right);
                node = rotateLeft(node);
            }
        }

        return node;
    }

    private Node<T> getInorderSuccessor(Node<T> node) {
        if(node == null){
            return null;
        }
        return (node.left == null) ? node : getInorderSuccessor(node.left);
    }

    public void printInOrder() {
        printInOrderHelper(root);
    }
    private void printInOrderHelper(Node<T> node) {
        if(node == null) {
            return;
        }
        printInOrderHelper(node.left);
        System.out.print(node.value + " ");
        printInOrderHelper(node.right);
    }

    public void printPreOrder() {
        printPreOrderHelper(root);
    }
    private void printPreOrderHelper(Node<T> node) {
        if(node == null) {
            return;
        }
        System.out.print(node.value + " ");
        printPreOrderHelper(node.left);
        printPreOrderHelper(node.right);
    }

    public void printPostOrder() {
        printPostOrderHelper(root);
    }
    private void printPostOrderHelper(Node<T> node) {
        if(node == null) {
            return;
        }
        printPostOrderHelper(node.left);
        printPostOrderHelper(node.right);
        System.out.print(node.value + " ");
    }

    public void printLevelOrder() {
        if (root == null) {
            return;
        }
        Queue<Node<T>> queue = new LinkedList<>();
        queue.add(root);
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                Node<T> current = queue.poll();
                System.out.print(current.value + " ");
                if (current.left != null) {
                    queue.add(current.left);
                }
                if (current.right != null) {
                    queue.add(current.right);
                }
            }
            System.out.println(); 
        }
    }

}


public class AVLImplementation {

    public static void main(String... args) {

        AVLTree<Integer> avlTree = new AVLTree<>();
    
        avlTree.insert(5);
        avlTree.insert(3);
        avlTree.insert(4);
        avlTree.insert(1);
        avlTree.insert(0);
        avlTree.insert(2);

        /*
                 3 
                / \ 
               1   4 
              / \   \
             0   2   5   
         */

        System.out.println("Level Order Traverssal : ");
        avlTree.printLevelOrder();


        // avlTree.delete(0);
        // avlTree.delete(5);
        avlTree.delete(4);

        /*
                 3 
                / \ 
               1   5 
              / \   
             0   2   
         */

        avlTree.delete(5);


        /*
                 3  (balancing factor = 2) -> balance the tree NOW !!!!!
                / 
               1  
              / \   
             0   2   
         */

        System.out.println("After deletion Level Order Traverssal : ");
        avlTree.printLevelOrder();
        
        /*
                 1 
                / \ 
               0   3
                  /
                 2  
         */

    }

}
