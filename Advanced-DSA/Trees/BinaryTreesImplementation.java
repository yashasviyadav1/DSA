
import java.util.Queue;
import java.util.LinkedList;

class Node<T> {
    T value;
    Node<T> left;
    Node<T> right;

    Node(T value){
        this.value = value;
        this.left = this.right = null;
    }
}

class BinaryTree<T> {
    Node<T> root;
    public void printInOrder(Node<T> root) {
        if(root == null) {
            return;
        }
        printInOrder(root.left);
        System.out.print(root.value + " ");
        printInOrder(root.right);
    }
    public void printPreOrder(Node<T> root) {
        if(root == null) {
            return;
        }
        System.out.print(root.value + " ");
        printPreOrder(root.left);
        printPreOrder(root.right);
    }
    public void printPostOrder(Node<T> root){
        if(root == null) {
            return;
        }
        printPostOrder(root.left);
        printPostOrder(root.right);
        System.out.print(root.value + " ");
    }
    public void printLevelOrder(Node<T> root) {
        Queue<Node<T>> queue = new LinkedList<>();
        queue.add(root);
        while(!queue.isEmpty()){
            int size = queue.size();
            for(int i=0; i < size; i++) {
                Node<T> current = queue.poll();
                System.out.print(current.value + " ");
                if(current.left != null) {
                    queue.add(current.left);
                }
                if(current.right != null) {
                    queue.add(current.right);
                }
            }
            System.out.println();
        }
    }
}

public class BinaryTreesImplementation {

    public static void main(String[] args) {

        BinaryTree<Integer> tree = new BinaryTree<>();
        tree.root = new Node<>(10);
        tree.root.left = new Node<>(5);
        tree.root.left.left = new Node<>(15);
        tree.root.left.right = new Node<>(20);
        tree.root.right = new Node<>(30);
        tree.root.right.left = new Node<>(6);
        tree.root.right.right = new Node<>(3);

        System.out.print("In-order traversal:");
        tree.printInOrder(tree.root);
        System.out.println();
        
        System.out.print("Pre-order traversal: ");
        tree.printPreOrder(tree.root);
        System.out.println();
        
        System.out.print("Post-order traversal: ");
        tree.printPostOrder(tree.root);
        System.out.println();
        
        System.out.println("Level-order traversal: ");
        tree.printLevelOrder(tree.root);
        System.out.println();
    }
    
}
