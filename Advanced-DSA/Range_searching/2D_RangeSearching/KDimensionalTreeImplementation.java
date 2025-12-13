import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Queue;
import java.util.LinkedList;

/**
 * Represents a point in k-dimensional space.
 * <p>
 * This class encapsulates coordinates in any number of dimensions and provides
 * utility methods for comparison and string representation.
 * </p>
 */
class Point {
    /**
     * Array storing the coordinates of this point because coordinate can have any
     * number of points basically k dimensions means k coordinates for representing
     * each point
     */
    int[] coordinates;

    /** Number of dimensions of this point */
    int dimension;

    /**
     * Constructs a Point with the given coordinates.
     * 
     * @param coordinates variable-length array of integers representing the point's
     *                    coordinates
     * @throws IllegalArgumentException if coordinates is null or empty
     */
    Point(int... coordinates) {
        if (coordinates == null || coordinates.length == 0) {
            throw new IllegalArgumentException("Coordinates cannot be null or empty");
        }
        this.coordinates = coordinates.clone();
        this.dimension = coordinates.length;
    }

    /**
     * Compares this point to another object for equality.
     * Two points are equal if they have the same coordinates in all dimensions.
     * 
     * @param other the object to compare with
     * @return true if the objects are equal, false otherwise
     */
    @Override
    public boolean equals(Object other) {
        if (other == null || !(other instanceof Point)) {
            return false;
        }
        if (other == this) {
            return true;
        }
        Point otherPoint = (Point) other;
        return Arrays.equals(otherPoint.coordinates, this.coordinates);
    }

    /**
     * Returns a hash code value for this point.
     * 
     * @return hash code based on the coordinates array
     */
    @Override
    public int hashCode() {
        return Arrays.hashCode(this.coordinates);
    }

    /**
     * Returns a string representation of this point.
     * Format: "[x, y, z, ...]" for a point with coordinates x, y, z, etc.
     * 
     * @return string representation of the point's coordinates
     */
    @Override
    public String toString() {
        // return "" + Arrays.toString(coordinates) + ""; // alternative way
        return "" + Arrays.stream(coordinates).boxed().toList() + ""; // converting int[] to List<Integer> using stream
                                                                      // api
    }
}

/**
 * Represents a node in a k-D tree.
 * <p>
 * Each node contains a point and references to left and right child nodes.
 * The left child contains points with smaller coordinate values in the
 * splitting dimension,
 * while the right child contains points with larger coordinate values.
 * </p>
 */
class KDTreeNode {
    Point point;
    KDTreeNode left, right;

    KDTreeNode(Point point) {
        this.point = point;
        this.left = null;
        this.right = null;
    }
}

/**
 * Implementation of a k-Dimensional tree (k-D tree) for efficient spatial
 * queries.
 * <p>
 * A k-D tree is a space-partitioning data structure for organizing points in
 * k-dimensional space.
 * It supports efficient range searching and nearest neighbor queries.
 * </p>
 * 
 * <h2>Construction Complexity:</h2>
 * <ul>
 * <li>Time: O(n log n) using QuickSelect for median finding</li>
 * <li>Space: O(log n) for recursion stack</li>
 * </ul>
 * 
 * <h2>Query Complexity:</h2>
 * <ul>
 * <li>Range Search: O(n^(1-1/k) + m) where m is the number of reported
 * points</li>
 * <li>For 2D: O(√n + m)</li>
 * <li>For 3D: O(n^(2/3) + m)</li>
 * </ul>
 */
class KDTree {
    /** Root node of the k-D tree */
    KDTreeNode root;

    /** Number of dimensions (k value) for this tree */
    int dimension;

    /**
     * Constructs a k-D tree from a 2D array of coordinates.
     * 
     * @param dimension the number of dimensions (k value) for the tree
     * @param arr       2D array where each row represents a point's coordinates
     * @throws IllegalArgumentException if any point doesn't have the expected
     *                                  number of dimensions
     */
    KDTree(int dimension, int[][] arr) {
        this.dimension = dimension;
        List<Point> points = buildPointsArray(arr);
        buildKDTree(points);
    }

    /**
     * Converts a 2D array of coordinates into a list of Point objects.
     * 
     * @param arr 2D array of coordinates
     * @return list of Point objects
     */
    private List<Point> buildPointsArray(int[][] arr) {
        List<Point> points = new ArrayList<>();
        for (int[] point : arr) {
            points.add(new Point(point));
        }
        return points;
    }

    /**
     * Builds the k-D tree from a list of points.
     * <p>
     * Validates that all points have the correct dimensionality before
     * construction.
     * </p>
     * 
     * @param points list of points to build the tree from
     * @throws IllegalArgumentException if any point has incorrect dimensionality
     */
    private void buildKDTree(List<Point> points) {
        if (points == null || points.size() == 0) {
            return;
        }
        // validate all points have same dim
        for (Point point : points) {
            if (point.dimension != this.dimension) {
                throw new IllegalArgumentException("Point " + point + " has dimension " + point.dimension +
                        " but tree expects dimension " + this.dimension);
            }
        }

        this.root = buildKDTreeHelper(points, 0, 0, points.size() - 1);
    }

    /**
     * Recursively builds the k-D tree using the median-finding approach.
     * <p>
     * At each level, the algorithm:
     * <ol>
     * <li>Determines the splitting dimension using (depth % k)</li>
     * <li>Uses QuickSelect to find the median point along that dimension</li>
     * <li>Creates a node with the median point</li>
     * <li>Recursively builds left subtree with points having smaller
     * coordinates</li>
     * <li>Recursively builds right subtree with points having larger
     * coordinates</li>
     * </ol>
     * </p>
     * 
     * @param points list of points to build the tree/subtree from
     * @param depth  current depth in the tree (used to determine splitting
     *               dimension)
     * @param start  starting index in the points list
     * @param end    ending index in the points list
     * @return root node of the constructed subtree
     */
    private KDTreeNode buildKDTreeHelper(List<Point> points, int depth, int start, int end) {
        if (start > end)
            return null;
        if (start == end) {
            return new KDTreeNode(points.get(start));
        }

        // Cycle through dimensions: depth % k determines the splitting axis
        // For 3D (k=3): depth 0→X, 1→Y, 2→Z, 3→X, 4→Y, 5→Z, ...
        int axis = depth % this.dimension;
        int medianIndex = start + (end - start) / 2;

        // QuickSelect finds the median and partitions the array:
        // - Elements with smaller coordinates on the left
        // - Median element at medianIndex
        // - Elements with larger coordinates on the right
        // - this is done in O(n) time on average, removing the need for full sorting
        // which is O(n log n)
        quickSelect(points, axis, medianIndex, start, end);

        Point medianPoint = points.get(medianIndex);
        KDTreeNode curr = new KDTreeNode(medianPoint);

        curr.left = buildKDTreeHelper(points, depth + 1, start, medianIndex - 1);
        curr.right = buildKDTreeHelper(points, depth + 1, medianIndex + 1, end);

        return curr;
    }

    /**
     * QuickSelect algorithm to find the k-th smallest element and partition the
     * array.
     * <p>
     * This is a selection algorithm that finds the k-th smallest element in linear
     * time
     * on average. It works similarly to QuickSort but only recurses on one side of
     * the partition.
     * </p>
     * 
     * <h3>Algorithm:</h3>
     * <ol>
     * <li>Choose a pivot element (last element in range)</li>
     * <li>Partition array: elements ≤ pivot on left, elements > pivot on right</li>
     * <li>If pivot is at position k, done</li>
     * <li>If k < pivot position, recurse on left side</li>
     * <li>If k > pivot position, recurse on right side</li>
     * </ol>
     * 
     * <h3>Complexity:</h3>
     * <ul>
     * <li>Time: O(n) average case, O(n²) worst case</li>
     * <li>Space: O(log n) recursion stack on average</li>
     * </ul>
     * 
     * @param points list of points to partition
     * @param axis   the dimension/coordinate to compare (0 for x, 1 for y, 2 for z,
     *               etc.)
     * @param kth    the index where the k-th smallest element should be placed
     * @param start  starting index of the range to partition
     * @param end    ending index of the range to partition
     */
    private void quickSelect(List<Point> points, int axis, int kth, int start, int end) {
        if (start >= end) {
            return;
        }

        // Partitioning phase: arrange elements so that
        // [elements ≤ pivot] [pivot] [elements > pivot]
        int pivotIndex = end;
        int pivotElement = points.get(pivotIndex).coordinates[axis];
        int i = start - 1;

        // Scan through array, moving elements ≤ pivot to the left
        for (int j = start; j < end; j++) { // not vising the pivot element, coz we will swap it at the end of loop and
                                            // after swapping update the pivot index
            if (points.get(j).coordinates[axis] <= pivotElement) { // jth element <= pivot
                                                                   // swap them
                i++;
                Collections.swap(points, i, j);
            }
        }

        // Place pivot in its correct position
        i++;
        Collections.swap(points, i, pivotIndex); // place pivot element at its correct position
        pivotIndex = i; // update the pivot index, coz its position has changed after swapping

        // k-th element is on the left side of the pivot index
        if (kth < pivotIndex) {
            quickSelect(points, axis, kth, start, pivotIndex - 1);
        } else { // k-th element is on the right side
            quickSelect(points, axis, kth, pivotIndex + 1, end);
        }
    }

    /**
     * Performs a range search to find all points within a rectangular region.
     * <p>
     * A range search finds all points that fall within the hyper-rectangle defined
     * by
     * two corner points p1 (minimum bounds) and p2 (maximum bounds).
     * </p>
     * 
     * <h3>Example for 2D:</h3>
     * 
     * <pre>
     * p1 = (2, 3), p2 = (8, 9)
     * Finds all points where: 2 ≤ x ≤ 8 AND 3 ≤ y ≤ 9
     * </pre>
     * 
     * <h3>Complexity:</h3>
     * <ul>
     * <li>Time: O(n^(1-1/k) + m) where m is the number of points found</li>
     * <li>For 2D: O(√n + m)</li>
     * </ul>
     * 
     * @param p1 point defining the minimum bounds of the range
     * @param p2 point defining the maximum bounds of the range
     * @return list of all points within the range [p1, p2]
     * @throws IllegalArgumentException if p1 has larger coordinates than p2 in any
     *                                  dimension
     */
    public List<Point> rangeSearch(Point p1, Point p2) {
        List<Point> result = new ArrayList<>();
        if (p1 == null
                || p2 == null
                || p1.coordinates == null
                || p2.coordinates == null
                || p1.coordinates.length != this.dimension
                || p2.coordinates.length != this.dimension) {
            return result;
        }
        // validation for checking p1 has smaller coordinates than p2 in all dimensions
        for (int i = 0; i < this.dimension; i++) {
            if (p1.coordinates[i] > p2.coordinates[i]) {
                throw new IllegalArgumentException(
                        "p1 must have smaller coordinates than p2 in all dimensions");
            }
        }

        rangeSearchHelper(this.root, p1, p2, result, 0);
        return result;
    }

    /**
     * Helper method for recursive range search traversal.
     * <p>
     * This method efficiently prunes the search space by:
     * <ul>
     * <li>Only checking if current point is in range</li>
     * <li>Only exploring left subtree if range minimum is ≤ current point's
     * coordinate</li>
     * <li>Only exploring right subtree if range maximum is ≥ current point's
     * coordinate</li>
     * </ul>
     * This pruning strategy can eliminate large portions of the tree from
     * consideration.
     * </p>
     * 
     * @param curr   current node being examined
     * @param p1     minimum bounds of the range
     * @param p2     maximum bounds of the range
     * @param result list to accumulate points found within range
     * @param depth  current depth in the tree (determines splitting axis)
     */
    private void rangeSearchHelper(KDTreeNode curr, Point p1, Point p2, List<Point> result, int depth) {

        if (curr == null)
            return;

        int axis = depth % this.dimension;

        // Check if current point falls within the range in ALL dimensions
        boolean allCoordinatesInRange = true;
        for (int i = 0; i < curr.point.coordinates.length; i++) {
            if ((curr.point.coordinates[i] < p1.coordinates[i] || curr.point.coordinates[i] > p2.coordinates[i])) {
                allCoordinatesInRange = false;
                break;
            }
        }
        if (allCoordinatesInRange) {
            result.add(curr.point);
        }

        // Prune search space by only exploring relevant subtrees:

        // Explore left subtree if the range's minimum bound is ≤ current node's
        // coordinate
        // (smaller values exist in left subtree)
        if (p1.coordinates[axis] <= curr.point.coordinates[axis]) {
            rangeSearchHelper(curr.left, p1, p2, result, depth + 1);
        }

        // Explore right subtree if the range's maximum bound is ≥ current node's
        // coordinate
        // (larger values exist in right subtree)
        if (p2.coordinates[axis] >= curr.point.coordinates[axis]) {
            rangeSearchHelper(curr.right, p1, p2, result, depth + 1);
        }
    }

    /**
     * Prints the k-D tree structure in level-order (breadth-first) traversal.
     * <p>
     * Output format shows each level of the tree with depth information,
     * useful for debugging and visualizing the tree structure.
     * </p>
     * 
     * <h3>Example Output:</h3>
     * 
     * <pre>
     * Dimension: 3
     * Depth: 0 [9, 1, 25]
     * Depth: 1 [6, 12, 1] [13, 15, 10]
     * Depth: 2 [2, 7, 3] [3, 6, 1] [10, 19, 5] [17, 15, 20]
     * </pre>
     */
    public void printTree() {
        Queue<KDTreeNode> queue = new LinkedList<>();
        queue.add(root);
        System.out.println("Dimension: " + this.dimension);
        int depth = 0;
        while (!queue.isEmpty()) {
            int size = queue.size();
            System.out.print("Depth: " + depth++ + " ");
            for (int i = 0; i < size; i++) {
                KDTreeNode curr = queue.poll();
                System.out.print(curr.point + " ");
                if (curr.left != null)
                    queue.add(curr.left);
                if (curr.right != null)
                    queue.add(curr.right);
            }
            System.out.println();
        }
    }
}

public class KDimensionalTreeImplementation {
    public static void main(String[] args) {

        int[][] coordinates = { { 3, 6, 1 }, { 17, 15, 20 }, { 13, 15, 10 }, { 6, 12, 1 }, { 9, 1, 25 }, { 2, 7, 3 },
                { 10, 19, 5 } };
        KDTree kDimTree = new KDTree(3, coordinates);

        kDimTree.printTree();

        Point rangeStart = new Point(2, 5, 0);
        Point rangeEnd = new Point(10, 15, 10);
        List<Point> result = kDimTree.rangeSearch(rangeStart, rangeEnd);
        System.out.println(
                "Points that are in between range result " + rangeStart + " to " + rangeEnd + " are: " + result);
        /*
         * Dimension: 3
         * Depth: 0 [9, 1, 25]
         * Depth: 1 [2, 7, 3] [13, 15, 10]
         * Depth: 2 [3, 6, 1] [6, 12, 1] [17, 15, 20] [10, 19, 5]
         * Points that are in between range result [2, 5, 0] to [10, 15, 10] are: [[2,
         * 7, 3], [3, 6, 1], [6, 12, 1]]
         */
    }
}
