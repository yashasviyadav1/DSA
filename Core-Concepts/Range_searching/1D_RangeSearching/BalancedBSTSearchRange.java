// This is implementation of Self Balancing BST i.e AVL Tree Range Search for 1D

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a node in an AVL tree.
 * @param <T> the type of value stored in the node (must implement Comparable)
 */
class Node<T> {
    int height;
    T value;
    Node<T> left, right;
    /**
     * Constructs a new node with given value.
     * Height is initialized as 1, left and right children as null.
     *
     * @param value the value to store in the node
     */
    Node(T value) {
        this.height = 1;
        this.value = value;
        this.left = this.right = null;
    }
}

// AVL Tree are BST but with balance factor
/**
 * Implementation of an AVL (self-balancing) Binary Search Tree.
 * Supports insertion, deletion, search, and one-dimensional range queries.
 *
 * <p>All operations run in O(log n) time on average. Range query runs in
 * O(log n + k) time, where k is the number of reported elements.</p>
 *
 * @param <T> the type of elements maintained by this tree (must implement Comparable)
 */
class AVLTree<T extends Comparable<T>> {
    Node<T> root;

    /**
     * Returns the height of a node.
     *
     * @param node the node
     * @return height of node, or 0 if node is null
     */
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

    /**
     * Inserts a key into the AVL tree.
     *
     * @param key the key to insert
     * @return the new root of the tree
     */
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

  /**
     * Performs a left rotation around the given node.
     *
     * @param y the node to rotate
     * @return new root after rotation
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

    
    /**
     * Performs a right rotation around the given node.
     *
     * @param y the node to rotate
     * @return new root after rotation
     */
    private Node<T> rotateRight(Node<T> y){
        Node<T> x = y.left;
        Node<T> T1 = x.right;
        x.right = y;
        y.left = T1;
        y.height = 1 + Math.max(height(y.left), height(y.right));
        x.height = 1 + Math.max(height(x.left), height(x.right));
        return x;
    }

     /**
     * Deletes a key from the AVL tree.
     *
     * @param key the key to delete
     */
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
            if(getBalancingFactor(node.left) >= 0){ // LL
                node = rotateRight(node);
            }
            else{
                node.left = rotateLeft(node.left); // LR
                node = rotateRight(node);
            }
        }
        if(balancingFactor < -1) {
            if(getBalancingFactor(node.right) <= 0){// RR
                node = rotateLeft(node);
            }
            else{
                node.right = rotateRight(node.right);// RL
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

    /**
     * Performs a one-dimensional range search on the tree.
     *
     * @param low lower bound of the range (inclusive)
     * @param high upper bound of the range (inclusive)
     * @return list of elements within [low, high]
     */
    public List<T> rangeSearch(T low, T high){
        List<T> elementsInRange = new ArrayList<>();
        rangeSearchHelper(this.root, elementsInRange, low, high);
        return elementsInRange;
    }

    private void rangeSearchHelper(Node<T> curr, List<T> elementsInRange, T low, T high){
        if(curr == null) return;
        int keyCompWithLow = curr.value.compareTo(low);
        int keyCompWithHigh = curr.value.compareTo(high);
        if(keyCompWithLow > 0){ // our curr node is larger then the lowbound of range, means this curr may or may not be in range, and since it is larger then low, there can be smaller elements on left that might be in range
            rangeSearchHelper(curr.left, elementsInRange, low, high);
        }
        if(keyCompWithLow >= 0 && keyCompWithHigh <= 0){ // curr is in range add this (means curr is >= low and curr <= high)
            elementsInRange.add(curr.value);
        }
        if(keyCompWithHigh < 0){ // out curr is < high means it meay or may not be in range, since its smaller then high on its right subtree there can be larger nodes that migth be in range
            rangeSearchHelper(curr.right, elementsInRange, low, high);
        }
    }

}

/**
 * Demonstrates usage of AVLTree for one-dimensional range searching.
 */
public class BalancedBSTSearchRange{
    public static void main(String[] args) {
        
        AVLTree<Integer> avlTree = new AVLTree<>();
        
        int[] randomElements = {2, 9, 7, 10, 8, 12 , 0, 1, 4, 3}; // output [3, 4, 7, 8, 9, 10]
        // int[] randomElements = {1, 10, 50, 9, 2}; // output [9, 10]
        // int[] randomElements = {12, 50, 19, 12}; // output []
        for(int ele:randomElements){
            avlTree.insert(ele);
        }

        int low = 3, high = 11;
        System.out.format("elements in range %s to %s are %s ", low, high, avlTree.rangeSearch(low, high));
    }
}