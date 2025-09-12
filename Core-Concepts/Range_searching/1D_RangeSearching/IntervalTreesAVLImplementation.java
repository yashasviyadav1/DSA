
import java.util.ArrayList;
import java.util.List;

// Interval Tree - self balanced using AVL Implementation
// prerequisite: AVL Tree

/**
 * Represents an interval with a low and high value.
 */
class Interval {
    int low, high;

    Interval(int low, int high) {
        this.low = low;
        this.high = high;
    }

    @Override
    public String toString() {
        return "[" + this.low + ", " + this.high + "]";
    }
}

/**
 * Node for the Interval Tree.
 * Each node stores:
 * - an interval [low, high]
 * - the maximum endpoint (maxEnd) in its subtree
 * - its height (for AVL balancing)
 * - left and right children
 */
class IntervalNode {
    Interval interval;
    int maxEnd;// max value present in whole tree starting from this node
    IntervalNode left, right;
    int height;

    IntervalNode(Interval interval) {
        this.interval = interval;
        this.maxEnd = Math.max(interval.low, interval.high);
        this.left = this.right = null;
        this.height = 1;
    }
}

/**
 * Self-balancing Interval Tree implemented using AVL rotations.
 * 
 * Supports:
 * - Insertion of intervals
 * - Deletion of intervals
 * - Searching for overlapping intervals
 * - Inorder traversal
 */
class IntervalTree {
    IntervalNode root;

    public IntervalTree() {
        this.root = null;
    }

    /**
     * Searches for all intervals overlapping with a given interval [low, high].
     *
     * @param low  lower bound of query interval
     * @param high upper bound of query interval
     * @return list of overlapping intervals
     */
    public List<Interval> searchOverlap(int low, int high) {
        List<Interval> result = new ArrayList<>();
        if (low > high)
            return new ArrayList<>();
        searchHelper(this.root, result, new Interval(low, high));
        return result;
    }

    /**
     * Recursive helper to find overlapping intervals.
     */
    private void searchHelper(IntervalNode curr, List<Interval> result, Interval key) {
        if (curr == null)
            return;
        // check if curr node is in range of key interval
        if (doesOverlap(curr.interval, key)) {
            result.add(curr.interval);
        }
        // go to left if max value of left subtree is larger then key interval (search
        // interval) low
        if (curr.left != null && curr.left.maxEnd >= key.low) {
            searchHelper(curr.left, result, key);
        }
        if (curr.right != null) {
            searchHelper(curr.right, result, key);
        }
    }

    /**
     * Checks whether two intervals overlap.
     */
    private boolean doesOverlap(Interval curr, Interval key) {
        return ((curr.low <= key.high) && (key.low <= curr.high));
    }

    /**
     * Inserts an interval [low, high] into the tree.
     *
     * @param low  lower bound
     * @param high upper bound
     */
    public void insert(int low, int high) {
        this.root = insertHelper(this.root, new Interval(low, high));
    }

    /**
     * Recursive helper for insertion.
     * Balances tree using AVL rotations if required.
     */
    private IntervalNode insertHelper(IntervalNode curr, Interval key) {
        if (curr == null) {
            return new IntervalNode(key);
        }
        // go to left to insert
        if (key.low < curr.interval.low) {
            curr.left = insertHelper(curr.left, key);
        } else {
            curr.right = insertHelper(curr.right, key);
        }

        // this is important: because after inserting recursively in left or right
        // subtree we have our height or maxEnd outddated
        // so we are updating it here because, we want to send our updated nodes maxEnd
        // and heights because, if we not update the values for curr node
        // then we would be doing rotations with wrong height and maxEnd values (note:
        // in rotation functions after rotation links are changed we are updating the
        // heights and maxEnds of those rotated nodes)
        // so we update the curr's maxEnd and height first before checking for balancing
        // factor, so we send the latest values of them before rotation
        updateHeightAndMaxEnd(curr);

        if (balancingFactor(curr) > 1) { // left heavy
            if (key.low < curr.left.interval.low) { // left left case
                curr = rightRotate(curr);
            } else { // left right case
                curr.left = leftRotate(curr.left);
                curr = rightRotate(curr);
            }
        }
        if (balancingFactor(curr) < -1) { // right heavy
            if (key.low > curr.right.interval.low) { // right right case
                curr = leftRotate(curr);
            } else { // right left case
                curr.right = rightRotate(curr.right);
                curr = leftRotate(curr);
            }
        }

        return curr;
    }

    /**
     * Deletes an interval [low, high] from the tree if present.
     *
     * @param low  lower bound
     * @param high upper bound
     */
    public void delete(int low, int high) {
        this.root = deleteHelper(this.root, new Interval(low, high));
    }

    /**
     * Recursive helper for deletion.
     * Balances tree using AVL rotations if required.
     */
    private IntervalNode deleteHelper(IntervalNode curr, Interval key) {
        if (curr == null)
            return null;
        if (key.low < curr.interval.low) {
            curr.left = deleteHelper(curr.left, key);
        } else if (key.low > curr.interval.low) {
            curr.right = deleteHelper(curr.right, key);
        } else if (key.low == curr.interval.low && key.high == curr.interval.high) {
            // delete this
            // case 1 : no child
            if (curr.left == null && curr.right == null) {
                return null;
            }
            // case2 : one child
            else if (curr.left == null || curr.right == null) {
                return curr.left != null ? curr.left : curr.right;
            }
            // case 3 : two child
            else {
                IntervalNode inorderSuccessor = findInorderSuccessor(curr.right);
                curr.interval = inorderSuccessor.interval;
                curr.right = deleteHelper(curr.right, inorderSuccessor.interval);
            }
        } else { // in above conditions 1 case is missed: when key is equal to key.low ==
                 // curr.low we go to right (coz during insertion if key is not less then curr we
                 // always go right to insert it)
            curr.right = deleteHelper(curr.right, key);
        }

        updateHeightAndMaxEnd(curr);

        int balancingFactor = balancingFactor(curr);
        if (balancingFactor > 1) { // left heavy
            if (balancingFactor(curr.left) >= 0) { // if either left tree is balanced or left left case -> rotate right curr
                curr = rightRotate(curr);
            } else { // left right -> rotate left the left subtree, rotate right the curr
                curr.left = leftRotate(curr.left);
                curr = rightRotate(curr);
            }
        }
        if (balancingFactor < -1) { // right heavy
            if (balancingFactor(curr.right) <= 0) { // if either right tree is balanced or RR case -> rotate left curr tree
                curr = leftRotate(curr);
            } else {// RL -> rotate right -> right subtree, rotate left -> curr tree
                curr.right = rightRotate(curr.right);
                curr = leftRotate(curr);
            }
        }
        return curr;
    }

    private IntervalNode findInorderSuccessor(IntervalNode curr) {
        while (curr.left != null) {
            curr = curr.left;
        }
        return curr;
    }

    private int balancingFactor(IntervalNode curr) {
        if (curr == null)
            return 0;
        return height(curr.left) - height(curr.right);
    }

    private int height(IntervalNode curr) {
        if (curr == null)
            return 0;
        return curr.height;
    }

    private IntervalNode leftRotate(IntervalNode y) {
        IntervalNode x = y.right;
        IntervalNode T1 = x.left;

        x.left = y;
        y.right = T1;

        updateHeightAndMaxEnd(y); // first update y as it is now child of x so the values of x depends on y(the
                                  // child)
        updateHeightAndMaxEnd(x);

        return x;
    }

    private IntervalNode rightRotate(IntervalNode y) {
        IntervalNode x = y.left;
        IntervalNode T1 = x.right;

        x.right = y;
        y.left = T1;

        updateHeightAndMaxEnd(y); // first update y as it is now child of x so the values of x depends on y(the
                                  // child)
        updateHeightAndMaxEnd(x);

        return x;
    }

    /**
     * Updates both height and maxEnd of a node based on its children.
     */
    private void updateHeightAndMaxEnd(IntervalNode curr) {
        if (curr == null)
            return;
        curr.height = 1 + Math.max(height(curr.left), height(curr.right));
        curr.maxEnd = Math.max(curr.interval.high, Math.max(getMax(curr.left), getMax(curr.right)));
    }

    private int getMax(IntervalNode curr) {
        if (curr == null)
            return Integer.MIN_VALUE;
        return curr.maxEnd;
    }

    public void inorderTraversal() {
        inorderTraversalHelper(this.root);
    }

    private void inorderTraversalHelper(IntervalNode curr) {
        // LNR
        if (curr == null)
            return;
        inorderTraversalHelper(curr.left);
        System.out.print(curr.interval + " ");
        inorderTraversalHelper(curr.right);
    }

    /**
     * Checks if an interval [low, high] exists in the tree.
     *
     * @param low  lower bound
     * @param high upper bound
     * @return true if present, false otherwise
     */
    public boolean isPresent(int low, int high) {
        return isPresentHelper(this.root, new Interval(low, high));
    }

    private boolean isPresentHelper(IntervalNode curr, Interval key) {
        if (curr == null)
            return false;
        if (curr.interval.low == key.low && curr.interval.high == key.high)
            return true;
        if (key.low < curr.interval.low) {
            return isPresentHelper(curr.left, key);
        } else {
            return isPresentHelper(curr.right, key);
        }
    }
}

// Interval Tree AVL Implementaiton
public class IntervalTreesAVLImplementation {

    public static void main(String[] args) {

        IntervalTree tree = new IntervalTree();
        int[][] intervals = { { 15, 20 }, { 10, 30 }, { 17, 19 }, { 5, 20 }, { 12, 15 }, { 30, 40 } };
        for (int[] interval : intervals) {
            tree.insert(interval[0], interval[1]);
        }

        System.out.println("\n" + "-".repeat(20));
        int low = 14, high = 16;
        List<Interval> result = tree.searchOverlap(14, 16);
        System.out.print("intervals overlapping with [" + low + ", " + high + "] are : ");
        for (Interval interval : result) {
            System.out.print(interval + " ");
        }
        System.out.println("\nInorder Traversal of tree: ");
        tree.inorderTraversal();

        System.out.println("\n" + "-".repeat(20));
        System.out.println("Deleting interval [10, 30]");
        tree.delete(10, 30);
        result = tree.searchOverlap(14, 16);
        System.out.print("intervals overlapping with [" + low + ", " + high + "] are : ");
        for (Interval interval : result) {
            System.out.print(interval + " ");
        }
        System.out.println("\nInorder Traversal of tree: ");
        tree.inorderTraversal();

        System.out.println("\n" + "-".repeat(20));
        System.out.println("Deleting interval [15, 20]");
        tree.delete(15, 20);
        result = tree.searchOverlap(14, 16);
        System.out.print("intervals overlapping with [" + low + ", " + high + "] are : ");
        for (Interval interval : result) {
            System.out.print(interval + " ");
        }
        System.out.println("\nInorder Traversal of tree: ");
        tree.inorderTraversal();

        System.out.println("\n" + "-".repeat(20));
        tree.insert(9, 14);
        tree.insert(4, 18);
        tree.insert(6, 8);
        System.out.println("\nInserted [9, 14] [4, 18] [6, 8]");

        System.out.println("\n" + "-".repeat(20));
        System.out.print("Searching for intervals overlapping with [7, 13]: ");
        result = tree.searchOverlap(7, 13);
        for (Interval interval : result) {
            System.out.print(interval + " ");
        }
        System.out.println("\nInorder Traversal of tree: ");
        tree.inorderTraversal();

        /*
            --------------------
            intervals overlapping with [14, 16] are : [15, 20] [10, 30] [5, 20] [12, 15] 
            Inorder Traversal of tree: 
            [5, 20] [10, 30] [12, 15] [15, 20] [17, 19] [30, 40] 
            --------------------
            Deleting interval [10, 30]
            intervals overlapping with [14, 16] are : [15, 20] [12, 15] [5, 20] 
            Inorder Traversal of tree: 
            [5, 20] [12, 15] [15, 20] [17, 19] [30, 40] 
            --------------------
            Deleting interval [15, 20]
            intervals overlapping with [14, 16] are : [12, 15] [5, 20] 
            Inorder Traversal of tree: 
            [5, 20] [12, 15] [17, 19] [30, 40] 
            --------------------

            Inserted [9, 14] [4, 18] [6, 8]

            --------------------
            Searching for intervals overlapping with [7, 13]: [9, 14] [5, 20] [4, 18] [6, 8] [12, 15] 
            Inorder Traversal of tree: 
            [4, 18] [5, 20] [6, 8] [9, 14] [12, 15] [17, 19] [30, 40] %  
         */

    }
}
