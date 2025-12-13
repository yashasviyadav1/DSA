import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.Objects;

/**
 * Simple immutable 2D point used in the range tree.
 */
class Point {
    int x, y;

    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public String toString(){
        return "(" + this.x + "," + this.y + ")";
    }

    /** [IMP] why we have to override this ?  
     * Logical equality: two points are equal if both x and y are equal.
     * We impelemented Because we using HashSet in our code, now by default equals method checks equality using == operator and for eg. Point p1 = new Point(2,3) and Point p2 = new Point(2,4), default will return false i.e not equal for p1 and p2, but in our case we consider them as duplicates durign traversal coz for us in this implementation any point which has same coordinates is duplicate, so we override equals method to check logical equality not the reference equality. 
     * @param o candidate object
     * @return true if o is a Point with same coordinates
     */
    @Override
    public boolean equals(Object o){
        if(o == null || !(o instanceof Point)) return false;
        if(this == o) return true;
        Point point = (Point)o;
        return this.x == point.x && this.y == point.y;
    }

    /**
     * Hash code consistent with equals — used by HashSet/HashMap buckets.
     * now why did we override this?
     * coz by default the hashCode of java will return hash based on the reference i.e  Point p1 = new Point(2,3) and Point p2 = new Point(2,4) java's default hashCode will return 2 different hash code for these 2 points, so Hash Set uses hash code to find which bucket we need to put this data in, so there will be 2 different bucket for these 2 points, but for us 2 points are equal when their x and y coordinates are same, so we are here overiding func to generating hash code based on coordinates and not the reference, so the p1 nad p2 will now have same hash code  
     * @return hash combining x and y
     */
    @Override
    public int hashCode(){
        return Objects.hash(this.x, this.y);
    }
}

/**
 * Node of the Y-subtree (secondary tree). The BST ordering is by point.y.
 */
class YTreeNode {
    Point point;
    YTreeNode left, right;

    YTreeNode(Point point) {
        this.point = point;
    }
}

/**
 * Node of the X-tree (primary tree). Each node holds a single point and a
 * Y-subtree containing all points in the X-node's subtree.
 */
class XTreeNode {
    Point point;
    XTreeNode left, right;
    YTreeNode ySubTree;

    XTreeNode(Point point) {
        this.point = point;
    }
}

/**
 * Two-dimensional range tree.
 *
 * <p>Properties:
 * <ul>
 *   <li>Query time: O(log^2 n + k) using canonical-subtree + split-node Y queries,
 *       where k is number of reported points.</li>
 *   <li>Space: O(n log n) because each X-node stores a Y-structure for its subtree.</li>
 *   <li>Build: current implementation copies + sorts subarrays at each X-node;
 *       that is simpler but leads to higher build time (≈ O(n log^2 n)). This
 *       is acceptable for moderate n; for large n consider build by merging
 *       presorted Y-lists to get O(n log n) build time.</li>
 * </ul>
 */
class TwoDimensionalRangeTree{
    XTreeNode root;
    
    /**
     * Build a 2D range tree from an array of integer pairs.
     * The array format is int[][] where each entry is {x, y}.
     *
     * @param arr input points as int[][] (each row = {x, y})
     */
    TwoDimensionalRangeTree(int[][] arr){
        List<Point> points = convertToPointsArray(arr);
        points.sort(Comparator.comparingInt(point -> point.x)); // sorting points on based on x cordinates
        this.root = buildXTree(points, 0, points.size()-1); // creating BST
    }

    /**
     * Convert an int[][] to a List<Point>.
     *
     * @param arr input points
     * @return list of Point objects
     */
    private List<Point> convertToPointsArray(int[][] arr){
        List<Point> points = new ArrayList<>();
        for(int[] point:arr){
            points.add(new Point(point[0], point[1]));
        }
        return points;
    }

    /**
     * Build the X-tree recursively using median-of-range (balanced BST).
     * For each created X-node we also build the Y-subtree containing all
     * points from this node's X-subtree. IMPORTANT: we copy the subList before
     * sorting by y to avoid corrupting the master x-sorted list.
     *
     * @param points x-sorted list of points
     * @param low left index (inclusive)
     * @param high right index (inclusive)
     * @return root of the constructed X-subtree
     */
    private XTreeNode buildXTree(List<Point> points, int low, int high){
        if(low > high){
            return null;
        }

        int mid = low + (high - low)/2;
        XTreeNode curr = new XTreeNode(points.get(mid));

        curr.left = buildXTree(points, low, mid-1);
        curr.right = buildXTree(points, mid + 1, high);

        // building y subtree of curr x tree node -> sort the curr tree nodes by ascending y nodes (for creating y subtree bst)
        List<Point> pointsForYSubtree = new ArrayList<>(points.subList(low, high+1)); // imp: In Java, list.subList() does not create a new, independent list. It returns a view of the original points list. When you call .sort() on this pointsForYSubtree view, you are actually re-sorting that portion of the original points list only, so inorder to fix that we create a new arraylist from that sublist because otherwise sorting the sublist by y coordinates will mess up the original points list which is sorted by x coordinates
        pointsForYSubtree.sort(Comparator.comparingInt(point -> point.y)); 
        curr.ySubTree = buildYSubTree(pointsForYSubtree, 0, pointsForYSubtree.size()-1);

        return curr;
    }

    /**
     * Build a balanced BST (Y-tree) from a list of points sorted by y.
     *
     * @param points list sorted by y
     * @param low left index inclusive
     * @param high right index inclusive
     * @return root of Y-tree
     */
    private YTreeNode buildYSubTree(List<Point> points, int low, int high){
        if(low > high){
            return null;
        }
        int mid = low + (high - low)/2;
        YTreeNode curr = new YTreeNode(points.get(mid));
        curr.left = buildYSubTree(points, low, mid-1);
        curr.right = buildYSubTree(points, mid+1, high);
        return curr;
    }

    /**
     * Public wrapper for 2D range query.
     *
     * @param x1 left x-bound (inclusive)
     * @param x2 right x-bound (inclusive)
     * @param y1 lower y-bound (inclusive)
     * @param y2 upper y-bound (inclusive)
     * @return list of points inside the rectangle [x1,x2] × [y1,y2]
     */
    public List<Point> query(int x1, int x2, int y1, int y2){
        Set<Point> result = queryXTree(x1, x2, y1, y2);
        return new ArrayList<>(result);
    }

    /**
     * Core X-tree query that finds the split node and then traverses left & right
     * paths. Uses canonical subtree queries on Y-subtrees for fully-contained X-subtrees
     * and checks individual X-nodes on the path (non-canonical).
     *
     * @param x1 left x-bound
     * @param x2 right x-bound
     * @param y1 lower y-bound
     * @param y2 upper y-bound
     * @return set of points (deduplicated) in the query rectangle
     */
    public Set<Point> queryXTree(int x1, int x2, int y1, int y2){
        Set<Point> result = new HashSet<>();
        XTreeNode splitNode = findXSplitNode(this.root, x1, x2);
        if (splitNode == null) {
            return result;
        }
        // split node is already in range of x (checked in findsplitnode func), since it is not a canonical node, we only check its y coordinates and add it to list if it is in range of y
        else if (splitNode.point.y >= y1 && splitNode.point.y <= y2) {
            result.add(splitNode.point);
        }

        // Explore canonical subtrees along the two search paths
        followXNodeLeftPath(splitNode.left, result, x1, x2, y1, y2);
        followXNodeRightPath(splitNode.right, result, x1, x2, y1, y2);

        return result;
    }

    /**
     * Find the split node in the X-tree (node where paths to x1 and x2 diverge).
     *
     * @param curr starting node (usually root)
     * @param x1 left bound
     * @param x2 right bound
     * @return split node or null if none intersects the x-range
     */
    private XTreeNode findXSplitNode(XTreeNode curr, int x1, int x2){
        if(curr == null) return null;
        if(x1 <= curr.point.x && curr.point.x <= x2){ // split node
            return curr;
        }
        if (curr.point.x < x1){
            return findXSplitNode(curr.right, x1, x2);
        }
        else {//curr.point.x > x2
            return findXSplitNode(curr.left, x1, x2);
        }
    }

    /**
     * Traverse the left search path from the split node towards x1.
     * For a node v on this path:
     * - if v.x >= x1 then v.right subtree is canonical (entirely inside x-range)
     *   so we query its Y-subtree; we also test v.point individually (non-canonical).
     * - otherwise (v.x < x1) we move right to find x1.
     *
     * @param curr current X-node (initially split.left)
     * @param result set to add results to (deduplicated)
     * @param x1 left x-bound
     * @param x2 right x-bound
     * @param y1 lower y-bound
     * @param y2 upper y-bound
     */
    private void followXNodeLeftPath(XTreeNode curr, Set<Point> result, int x1, int x2, int y1, int y2){
        if(curr == null) return;
        // if curr node is == LB that means curr node is in range and the whole right tree is in range
        if(curr.point.x == x1){
            if(curr.point.y >= y1 && curr.point.y <= y2){ // non canonical node, check y range and add if in range
                result.add(curr.point);
            }
            if(curr.right != null){
                queryYSubtree(curr.right.ySubTree, y1, y2, result); // since curr's whole right tree is in range so curr.right is a  canonical node, explore all its y subtree
            }
        }
        // if curr node > LB that means curr node (non canonical) and whole right tree (canonical) is in range, go to left rec
        else if(curr.point.x > x1){
            if(curr.point.y >= y1 && curr.point.y <= y2){ // non canonical node, check y range and add if in range
                result.add(curr.point);
            }
            if(curr.right != null){
                queryYSubtree(curr.right.ySubTree, y1, y2, result);
            }
            followXNodeLeftPath(curr.left, result, x1, x2, y1, y2);
        }
        // curr node < LB go right
        else{
            followXNodeLeftPath(curr.right, result, x1, x2, y1, y2);
        }
    }

    /**
     * Traverse the right search path from the split node towards x2.
     * For a node v on this path:
     * - if v.x <= x2 then v.left subtree is canonical (entirely inside x-range)
     *   so we query its Y-subtree; we also test v.point individually.
     * - otherwise (v.x > x2) we move left to find x2.
     *
     * @param curr current X-node (initially split.right)
     * @param result set to add results to
     * @param x1 left x-bound
     * @param x2 right x-bound
     * @param y1 lower y-bound
     * @param y2 upper y-bound
     */
    private void followXNodeRightPath(XTreeNode curr, Set<Point> result, int x1, int x2, int y1, int y2){
        if(curr == null) return;
        // if curr node is == HB that means curr node (non canonical) is in range and the whole left tree is in range (canonical)
        if(curr.point.x == x2){
            if(curr.point.y >= y1 && curr.point.y <= y2){ // non canonical node, check y range and add if in range
                result.add(curr.point);
            }
            if(curr.left != null){
                queryYSubtree(curr.left.ySubTree, y1, y2, result);
            }
        }
        // if curr node < HB that means curr node and whole left tree is in range, go to right rec
        else if(curr.point.x < x2){
            if(curr.point.y >= y1 && curr.point.y <= y2){ // non canonical node, check y range and add if in range
                result.add(curr.point);
            }
            if(curr.left != null){
                queryYSubtree(curr.left.ySubTree, y1, y2, result);
            }
            followXNodeRightPath(curr.right, result, x1, x2, y1, y2);
        }
        // curr node > HB (out of range)  go left, to find smaller nodes, that might be in range
        else{
            followXNodeRightPath(curr.left, result, x1, x2, y1, y2);
        }
    }

    /**
     * Query a Y-subtree (which belongs to a canonical X-subtree) for the y-range
     * [y1, y2] using the split-node method in the Y-tree.
     *
     * @param curr root of the Y-subtree (a BST by y)
     * @param y1 lower y-bound
     * @param y2 upper y-bound
     * @param result set to add qualifying points to
     */
    private void queryYSubtree(YTreeNode curr, int y1, int y2, Set<Point> result){
        if(curr == null){
            return;
        }
        YTreeNode splitNode = findYSplitNode(curr, y1, y2);
        if(splitNode == null){
            return;
        }
        else{
            result.add(splitNode.point);
        }

        followYNodeLeftPath(splitNode.left, y1, y2, result);
        followYNodeRightPath(splitNode.right, y1, y2, result);
    }

    /**
     * Find split node in Y-tree where y1 <= node.y <= y2.
     *
     * @param curr starting node
     * @param y1 lower bound
     * @param y2 upper bound
     * @return split node or null
     */
    private YTreeNode findYSplitNode(YTreeNode curr, int y1, int y2){
        if(curr == null){
            return null;
        }
        if(curr.point.y >= y1 && curr.point.y <= y2){
            return curr;
        }
        else if(curr.point.y < y1){
            return findYSplitNode(curr.right, y1, y2);
        }
        else{ // curr.point.y > y2
            return findYSplitNode(curr.left, y1, y2);
        }
    }

    /**
     * On the left side of a Y split, traverse towards y1. For a node v on this path:
     * if v.y >= y1 then v.right subtree is canonical (all values between v.y and split.y).
     *
     * @param curr node on left path
     * @param y1 lower y-bound
     * @param y2 upper y-bound
     * @param result set to add points to
     */
    private void followYNodeLeftPath(YTreeNode curr, int y1, int y2, Set<Point> result){
        if(curr == null) return;

        // if curr node == LB (of y) means curr node and its whole right subtree is in y range (and x range is already checked for these nodes, so directly add all nodes of right y subtree into result)
        if(curr.point.y == y1){
            result.add(curr.point);
            addAllNodesOfYSubtreeTreeToList(curr.right, result);
        }
        // if curr node > LB  means curr node and its whole right subtree is in y range (and x range is already checked for these nodes, so directly add all nodes of right y subtree into result)
        else if(curr.point.y > y1){
            result.add(curr.point);
            addAllNodesOfYSubtreeTreeToList(curr.right, result);
            followYNodeLeftPath(curr.left, y1, y2, result);
        }
        // curr node < LB, go right find some in range
        else{
            followYNodeLeftPath(curr.right, y1, y2, result);
        }
    }

    /**
     * On the right side of a Y split, traverse towards y2. For a node v on this path:
     * if v.y <= y2 then v.left subtree is canonical.
     *
     * @param curr node on right path
     * @param y1 lower y-bound
     * @param y2 upper y-bound
     * @param result set to add points to
     */
    private void followYNodeRightPath(YTreeNode curr, int y1, int y2, Set<Point> result){
        if(curr == null) return;

        // if curr node == HB (of y) means curr node and its whole left subtree is in y range (and x range is already checked for these nodes, so directly add all nodes of right y subtree into result)
        if(curr.point.y == y2){
            result.add(curr.point);
            addAllNodesOfYSubtreeTreeToList(curr.left, result);
        }
        // if curr node < HB  means curr node and its whole left subtree is in y range, add them and go right to explore more in range
        else if(curr.point.y < y2){
            result.add(curr.point);
            addAllNodesOfYSubtreeTreeToList(curr.left, result);
            followYNodeRightPath(curr.right, y1, y2, result);
        }
        // curr node > HB, go left find some in range
        else{
            followYNodeRightPath(curr.left, y1, y2, result);
        }
    }

    /**
     * Add all nodes in a Y-subtree to the result set (preorder traversal).
     * This is used when a subtree is canonical (we know every point there lies in [y1,y2]).
     *
     * @param curr root of subtree to add
     * @param result set to add to
     */
    private void addAllNodesOfYSubtreeTreeToList(YTreeNode curr, Set<Point> result){
        if(curr == null) return;
        result.add(curr.point);
        addAllNodesOfYSubtreeTreeToList(curr.left, result);
        addAllNodesOfYSubtreeTreeToList(curr.right, result);
    }

    public void printRangeTree(){
        printXTreeHelper(this.root);
    }
    public static void printXTreeHelper(XTreeNode node) {
        if(node == null) return;
        System.out.println("XNode: " + node.point); // NLR
        System.out.print("YSubTree: ");
        printYTree(node.ySubTree);
        System.out.println("\n" + "-".repeat(20));
        System.out.println();
        printXTreeHelper(node.left);
        printXTreeHelper(node.right);
    }

    private static void printYTree(YTreeNode node) {
        if (node == null) return;
        System.out.print(node.point + " ");//NLR
        printYTree(node.left);
        printYTree(node.right);
    }
}

public class TwoDimensionalRangeTreeImplementation {

    public static void main(String[] args) {

        // int[][] arr = {{1,4},{2,2},{3,6},{5,3},{6,7},{7,1}};
        int[][] arr = {{2,3},{4,7},{5,1},{7,2},{8,6},{9,4}};

        TwoDimensionalRangeTree rangeTree2D = new TwoDimensionalRangeTree(arr);

        // rangeTree2D.printRangeTree();
        List<Point> result = rangeTree2D.query(3, 8, 3, 6);
        System.out.println("Points in range (3,8) and (3,6) are: ");
        for(Point p: result){
            System.out.print(p + ", ");
        }

        System.out.println("-".repeat(20));

        List<Point> result2 = rangeTree2D.query(2, 8, 3, 6);
        System.out.println("Points in range (2,8) and (3,6) are: ");
        for(Point p: result2){
            System.out.print(p + ", ");
        }

        /*
            Points in range (3,8) and (3,6) are: 
            (8,6), --------------------
            Points in range (2,8) and (3,6) are: 
            (2,3), (8,6), %       

            visualize 2D range tree build : https://i.ibb.co/CXh8LLL/image.png
            visualize the first query:  : https://i.ibb.co/QBMFHVm/image.png 

        */
        
    }

}
