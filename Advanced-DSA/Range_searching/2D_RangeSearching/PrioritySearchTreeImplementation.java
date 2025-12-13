import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;
import java.util.Queue;

/**
 * A simple implementation of a Priority Search Tree (PST).
 * <p>
 * The PST is built as:
 * - A max-heap with respect to the y-coordinate.
 * - A binary search tree with respect to the x-coordinate (splitting value at
 * each node).
 * <p>
 * Supports range queries of the form:
 * [x1, x2] × [y1, ∞)
 *
 * Time Complexity:
 * - Build: O(n log n)
 * - Query: O(log n + k), where k = number of reported points
 *
 * Space Complexity:
 * - O(n) for nodes
 */

class Point {
    int x, y;

    /**
     * Constructs a Point with given x and y coordinates.
     *
     * @param x x-coordinate
     * @param y y-coordinate
     */
    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public String toString() {
        return "(" + this.x + "," + this.y + ")";
    }

    // why we override these methods has been alrady discussed in the 2D range Tree
    // implementation file, check it
    @Override
    public boolean equals(Object otherObject) {
        if (otherObject == null || !(otherObject instanceof Point)) {
            return false;
        }
        if (this == otherObject)
            return true;
        Point other = (Point) otherObject;
        return this.x == other.x && this.y == other.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.x, this.y);
    }
}

/**
 * A node in the Priority Search Tree.
 * Each node stores:
 * - A point
 * - Pointers to left and right children
 * - A splitting x-value (for BST property)
 * - A flag indicating if it has a splitting value
 */
class PSTNode {
    Point point;
    PSTNode left, right;
    int splittingX;// X-coordinate used for splitting (for BST property)
    boolean hasSplitting;

    /**
     * Creates a PST node with the given point.
     *
     * @param point point stored at this node
     */
    PSTNode(Point point) {
        this.point = point;
        this.left = null;
        this.right = null;
        this.splittingX = 0;
        this.hasSplitting = false;
    }

    @Override
    public String toString() {
        return "Node{" + point + "}";
    }
}

/**
 * The Priority Search Tree class.
 * Provides build and query operations.
 */
class MaxHeapPSTree {
    PSTNode root;

    /**
     * Constructs a Priority Search Tree from a 2D array of points.
     *
     * @param arr array of integer pairs representing points [x,y]
     */
    MaxHeapPSTree(int[][] arr) {
        List<Point> points = buildPointsList(arr);
        // sort the points by x-coordinate ascending
        points.sort(Comparator.comparingInt(point -> point.x));
        this.root = buildPrioritySearchTree(points);
    }

    /**
     * Converts a 2D integer array into a list of Point objects.
     *
     * @param arr input array of points
     * @return list of points
     */
    private List<Point> buildPointsList(int[][] arr) {
        List<Point> points = new ArrayList<>();
        for (int[] point : arr) {
            points.add(new Point(point[0], point[1]));
        }
        return points;
    }

    /**
     * Recursively builds the Priority Search Tree.
     * - Node stores point with maximum y.
     * - Splitting value chosen as median x.
     *
     * @param points list of points (sorted by x)
     * @return root of subtree
     */
    private PSTNode buildPrioritySearchTree(List<Point> points) {
        if (points.size() == 0) {
            return null;
        }
        // choose 1st node (max node acc to y)
        // note: our array is sorted in asc order based on x, so we need to find max
        // point based on y (for max heap root node)
        Point maxPoint = findMaxPointBasedOnYCoordinates(points);
        PSTNode curr = new PSTNode(maxPoint);
        points.remove(maxPoint);

        if (points.size() == 0) {
            curr.hasSplitting = false; // leaf node already inserted in above steps no more left so mark leaf as
                                       // undefined split (coz there is no node below this)
            return curr;
        }

        // find the splitXNode and based on it recrusively build the left and right tree
        // since array alrady sorted based on x we can directly find the median index
        // (no need to sort again)
        int medianIndex = calculateMedian(points);
        curr.splittingX = points.get(medianIndex).x; // (low, splitingX) (splitingX+1, high)
        curr.hasSplitting = true;
        curr.left = buildPrioritySearchTree(new ArrayList<>(points.subList(0, medianIndex + 1)));
        if (medianIndex + 1 >= points.size()) {
            curr.right = null;
            return curr;
        }
        curr.right = buildPrioritySearchTree(new ArrayList<>(points.subList(medianIndex + 1, points.size())));
        return curr;
    }

    /**
     * Find point with maximum y-coordinate, breaking ties by minimum x-coordinate
     * (we choose smaller x if y is same)
     *
     * @param points list of points
     * @return max-y point
     */
    private Point findMaxPointBasedOnYCoordinates(List<Point> points) {
        Point maxPoint = points.get(0);
        for (int i = 1; i < points.size(); i++) {
            if ((points.get(i).y > maxPoint.y) || (points.get(i).y == maxPoint.y && points.get(i).x < maxPoint.x)) {
                maxPoint = points.get(i);
            }
        }
        return maxPoint;
    }

    /**
     * Returns the median index of the list.
     *
     * @param points list of points
     * @return median index
     */
    private int calculateMedian(List<Point> points) {
        if (points.size() == 0)
            return 0;
        return (points.size() - 1) / 2;
    }

    /**
     * Query the PST for all points inside rectangle:
     * [x1, x2] × [y1, ∞)
     *
     * @param x1 min x
     * @param x2 max x
     * @param y1 min y
     * @return list of matching points
     */
    public List<Point> query(int x1, int x2, int y1) { // find all points in which are in [x1,x2] [y1, infinity]
        List<Point> result = new ArrayList<>();
        queryHelper(this.root, result, x1, x2, y1);
        return result;
    }

    /**
     * Recursive helper for range query.
     *
     * @param curr   current node
     * @param result accumulator for results
     * @param x1     min x
     * @param x2     max x
     * @param y1     min y
     */
    private void queryHelper(PSTNode curr, List<Point> result, int x1, int x2, int y1) {
        if (curr == null)
            return;
        if (curr.point.y < y1) { // curr nodes y is smaller then range required, we need larger y nodes value for
                                 // being in range (but in max heap top is is the larger if that is lower then y1
                                 // thne all nodes below are also lower then y1 so no need to continye formard)
            return;
        }

        if (x1 <= curr.point.x && curr.point.x <= x2 && curr.point.y >= y1) {
            result.add(curr.point);
        }

        if (!curr.hasSplitting)
            return;

        // not in range go left or right
        if (x1 <= curr.splittingX) {
            queryHelper(curr.left, result, x1, x2, y1);
        }
        if (x2 > curr.splittingX) {
            queryHelper(curr.right, result, x1, x2, y1);
        }
    }

    public void printTree() {
        printTreeLevelWise(this.root);
        return;
    }

    private void printTreeLevelWise(PSTNode curr) {
        if (curr == null) {
            return;
        }
        Queue<PSTNode> q = new LinkedList<>();
        q.add(curr);
        while (!q.isEmpty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                PSTNode front = q.poll();
                System.out.print("SplitXNodeValue: " + front.splittingX + " ");
                System.out.print(front + " ");
                if (!(front.left == null)) {
                    q.add(front.left);
                }
                if (!(front.right == null)) {
                    q.add(front.right);
                }
            }
            System.out.println();
        }
    }
}

public class PrioritySearchTreeImplementation {
    public static void main(String[] args) {
        int[][] arr = { { 5, 10 }, { 1, 6 }, { 3, 2 }, { 8, 5 }, { 4, 13 } };
        MaxHeapPSTree pst = new MaxHeapPSTree(arr);
        pst.printTree();

        List<Point> result1 = pst.query(2, 6, 7);

        // some bug in the query function
        System.out.println("Query [2,6] × [7,∞): " + result1);

        /*
         * output:
         * SplitXNodeValue: 3 Node{(4,13)}
         * SplitXNodeValue: 3 Node{(1,6)} SplitXNodeValue: 8 Node{(5,10)}
         * SplitXNodeValue: 0 Node{(3,2)} SplitXNodeValue: 0 Node{(8,5)}
         * Query [2,6] × [7,∞): [(4,13), (5,10)]
         */
    }
}
