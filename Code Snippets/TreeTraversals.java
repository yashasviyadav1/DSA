import java.util.Stack;

class TreeNode {
    int data;
    TreeNode left, right;

    public TreeNode(int item) {
        data = item;
        left = right = null;
    }
}

public class TreeTraversals {
    TreeNode root;

    // --- RECURSIVE TRAVERSALS ---
    void printInorderRecursive(TreeNode node) {
        if (node == null) return;
        printInorderRecursive(node.left);
        System.out.print(node.data + " ");
        printInorderRecursive(node.right);
    }

    void printPreorderRecursive(TreeNode node) {
        if (node == null) return;
        System.out.print(node.data + " ");
        printPreorderRecursive(node.left);
        printPreorderRecursive(node.right);
    }

    void printPostorderRecursive(TreeNode node) {
        if (node == null) return;
        printPostorderRecursive(node.left);
        printPostorderRecursive(node.right);
        System.out.print(node.data + " ");
    }

    // --- NON-RECURSIVE (ITERATIVE) TRAVERSALS ---
    
    // Iterative Inorder
    void printInorderIterative(TreeNode node) {
        if (node == null) return;
        Stack<TreeNode> s = new Stack<>();
        TreeNode curr = node;

        while (curr != null || !s.isEmpty()) {
            while (curr != null) {
                s.push(curr);
                curr = curr.left;
            }
            curr = s.pop();
            System.out.print(curr.data + " ");
            curr = curr.right;
        }
    }

    // Iterative Preorder
    void printPreorderIterative(TreeNode node) {
        if (node == null) return;
        Stack<TreeNode> nodeStack = new Stack<>();
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            TreeNode mynode = nodeStack.peek();
            System.out.print(mynode.data + " ");
            nodeStack.pop();

            // Push right child first so that left is processed first
            if (mynode.right != null) {
                nodeStack.push(mynode.right);
            }
            if (mynode.left != null) {
                nodeStack.push(mynode.left);
            }
        }
    }

    // Iterative Postorder (Using 2 stacks)
    void printPostorderIterative(TreeNode node) {
        if (node == null) return;
        Stack<TreeNode> s1 = new Stack<>();
        Stack<TreeNode> s2 = new Stack<>();

        s1.push(node);
        while (!s1.isEmpty()) {
            TreeNode temp = s1.pop();
            s2.push(temp);

            if (temp.left != null) s1.push(temp.left);
            if (temp.right != null) s1.push(temp.right);
        }

        while (!s2.isEmpty()) {
            TreeNode temp = s2.pop();
            System.out.print(temp.data + " ");
        }
    }

    public static void main(String args[]) {
        TreeTraversals tree = new TreeTraversals();
        
        // Constructing the Tree
        //        1
        //      /   \
        //     2     3
        //    / \
        //   4   5
        
        tree.root = new TreeNode(1);
        tree.root.left = new TreeNode(2);
        tree.root.right = new TreeNode(3);
        tree.root.left.left = new TreeNode(4);
        tree.root.left.right = new TreeNode(5);

        System.out.println("--- RECURSIVE TRAVERSALS ---");
        System.out.print("Preorder: ");
        tree.printPreorderRecursive(tree.root);
        System.out.print("\nInorder:  ");
        tree.printInorderRecursive(tree.root);
        System.out.print("\nPostorder: ");
        tree.printPostorderRecursive(tree.root);

        System.out.println("\n\n--- NON-RECURSIVE TRAVERSALS ---");
        System.out.print("Preorder: ");
        tree.printPreorderIterative(tree.root);
        System.out.print("\nInorder:  ");
        tree.printInorderIterative(tree.root);
        System.out.print("\nPostorder: ");
        tree.printPostorderIterative(tree.root);
    }
}