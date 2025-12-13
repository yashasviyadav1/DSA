
import java.util.LinkedList;
import java.util.Queue;

class Node<T> {
    T value;
    Node<T> left;
    Node<T> right;

    Node(T value){
        this.value = value;
        this.left = this.right = null;
    }
}

class BinarySearchTree<T extends Comparable<T>> {

    public Node<T> root;

    public void insert(T data) {
        root = insertHelper(root, data);
    }

    private Node<T> insertHelper(Node<T> node, T data) {
        if (node == null) {
            return new Node<T>(data);
        }
        if (data.compareTo(node.value) > 0) { // compareTo returns +1 when data > node.value, -1 when data < node.value,
                                              // and 0 when equal
            node.right = insertHelper(node.right, data);
        } else {
            node.left = insertHelper(node.left, data);
        }
        return node;
    }

    public void delete(T key) {
        deleteHelper(root, key);
    }

    private Node<T> deleteHelper(Node<T> node, T key) {
        if (node == null)
            return node;

        if (key.compareTo(node.value) < 0) {
            node.left = deleteHelper(node.left, key);
        } else if (key.compareTo(node.value) > 0) {
            node.right = deleteHelper(node.right, key);
        } else {
            // 0 or 1 child node
            if (node.left == null) {
                return node.right;
            }
            if (node.right == null) {
                return node.left;
            }
            // double child
            // find the inorder successor (smallest in the right subtree) or inorder
            // predecessor (largest in the left subtree)
            Node<T> successor = inorderSuccessor(node.right); // we can alternatively use inorderPredecessor(node.left) as well, works the same
            node.value = successor.value;
            node.right = deleteHelper(node.right, successor.value);
        }
        return node;
    }

    private Node<T> inorderSuccessor(Node<T> node) {
        return node.left == null ? node : inorderSuccessor(node.left);
    }

    // alternatively, we can use inorderPredecessor while deleting a node with two children

    public boolean contains(T key) {
        return containsHelper(root, key);
    }

    private boolean containsHelper(Node<T> node, T key) {
        if (node == null) {
            return false;
        }
        if (key.compareTo(node.value) == 0) {
            return true;
        } else if (key.compareTo(key) < 0) {
            return containsHelper(node.left, key);
        } else {
            return containsHelper(node.right, key);
        }
    }

    public void levelOrderTraversal() {
        Queue<Node<T>> queue = new LinkedList<>();
        if (root == null) {
            return;
        }
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

    public void inorderTraversal() {
        inorderHelper(root);
    }

    private void inorderHelper(Node<T> node) {
        if (node == null) {
            return;
        }
        inorderHelper(node.left);
        System.out.print(node.value + " ");
        inorderHelper(node.right);
    }

    public void preorderTraversal() {
        preorderHelper(root);
    }

    private void preorderHelper(Node<T> node) {
        if (node == null) {
            return;
        }
        System.out.print(node.value + " ");
        preorderHelper(node.left);
        preorderHelper(node.right);
    }

    public void postorderTraversal() {
        postorderHelper(root);
    }

    private void postorderHelper(Node<T> node) {
        if (node == null) {
            return;
        }
        postorderHelper(node.left);
        postorderHelper(node.right);
        System.out.print(node.value + " ");
    }
}

public class BSTImplementation {
    public static void main(String[] args) {

        /*
                 3 
                / \
               1
                0 2 4 15 
                8 
                6 10 
                7 
         */

        BinarySearchTree<Integer> bst = new BinarySearchTree<>();

        // creating a tree like this:
        //          3
        //        /   \
        //       1    5
        //      / \   / \
        //     0  2  4  15
        //              /
        //             8
        //            / \
        //           6  10
        //            \
        //            7

        bst.insert(3);
        bst.insert(5);
        bst.insert(15);
        bst.insert(8);
        bst.insert(6);
        bst.insert(1);
        bst.insert(7);
        bst.insert(4);
        bst.insert(0);
        bst.insert(2);
        bst.insert(10);

        System.out.println("Contains 5: " + bst.contains(5)); // true
        System.out.println("Contains 20: " + bst.contains(20)); // false

        System.out.println("Level order Traversal:");
        bst.levelOrderTraversal();

        System.out.println("Inorder Traversal:");
        bst.inorderTraversal();
        System.out.println();

        System.out.println("Preorder Traversal:");
        bst.preorderTraversal();
        System.out.println();

        System.out.println("Postorder Traversal:");
        bst.postorderTraversal();
        System.out.println();

        bst.delete(5);
        System.out.println("After deleting 5, level Traversal:");
        bst.levelOrderTraversal();
        System.out.println();

        //       3
        //     /   \
        //    /     \
        //   1       6  <-- Node 5's key replaced by 6
        //  / \     / \
        // 0   2   4   15
        //            /
        //           8
        //          / \
        //         7  10 

        bst.delete(15);
        System.out.println("After deleting 15, level Traversal:");
        bst.levelOrderTraversal();
        System.out.println();

        
// final state
//         3
//       /   \
//      1     6  
//     / \   / \
//    0   2 4   8
//              / \
//             7  10

    }
}
