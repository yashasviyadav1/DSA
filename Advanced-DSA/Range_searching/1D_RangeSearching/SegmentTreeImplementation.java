/**
 * Segment Tree implementation for range sum queries and point updates.
 * 
 * Time Complexity:
 * - Build: O(N)
 * - Query: O(log N)
 * - Update: O(log N)
 * 
 * Space Complexity: O(4N)
 */
class SegmentTree {
    private int[] tree;
    private int N;

    /**
     * Constructs a Segment Tree from the given array.
     * 
     * @param arr input array used to build the segment tree
     */
    SegmentTree(int[] arr) {
        this.N = arr.length;
        this.tree = new int[4 * this.N];
        buildTree(arr, 0, N - 1, 0);
    }

    /**
     * Builds the segment tree recursively.
     * 
     * @param arr           input array
     * @param low           starting index of the current segment
     * @param high          ending index of the current segment
     * @param currNodeIndex index in the segment tree array
     */
    private void buildTree(int[] arr, int low, int high, int currNodeIndex) {
        if (low == high) {
            tree[currNodeIndex] = arr[low];
            return;
        }

        int mid = low + (high - low) / 2;
        buildTree(arr, low, mid, 2 * currNodeIndex + 1); // left child of index i will have index = 2*i + 1
        buildTree(arr, mid + 1, high, 2 * currNodeIndex + 2); // right child of index i will have index = 2*i + 2
        tree[currNodeIndex] = tree[2 * currNodeIndex + 1] + tree[2 * currNodeIndex + 2]; // for min value just change
                                                                                         // this operation
    }

    /**
     * Queries the sum of elements in the range [queryLow, queryHigh].
     * 
     * @param queryLow  left bound of query (inclusive)
     * @param queryHigh right bound of query (inclusive)
     * @return sum of elements in the given range
     */
    public int query(int queryLow, int queryHigh) {
        if(queryLow > queryHigh){ // invalid query
            return 0;
        }
        return queryHelper(0, N - 1, queryLow, queryHigh, 0);
    }

    /**
     * Recursive helper for range query.
     * 
     * @param nodeLow        left bound of current node segment
     * @param nodeHigh       right bound of current node segment
     * @param queryLow       left bound of query range
     * @param queryHigh      right bound of query range
     * @param currNodeIndex  current index in the segment tree
     * @return sum of elements within the query range
     */
    private int queryHelper(int nodeLow, int nodeHigh, int queryLow, int queryHigh, int currNodeIndex) {
        
        // no overlap in curr node and query
        if (queryHigh < nodeLow || queryLow > nodeHigh) {
            return 0;
        }

        // reached here means there is overlap (it can be partial or complete)
        // complete overlap -> return value of curr node
        if (queryLow <= nodeLow && queryHigh >= nodeHigh) { // complete overlap
            return this.tree[currNodeIndex];
        }

        // reached here means there is only partial overlap left, so expore both childs
        int midNode = nodeLow + (nodeHigh - nodeLow) / 2;
        return queryHelper(nodeLow, midNode, queryLow, queryHigh, currNodeIndex * 2 + 1)
                + queryHelper(midNode + 1, nodeHigh, queryLow, queryHigh, currNodeIndex * 2 + 2);

    }

    /**
     * Updates the element at the given index with the new value.
     * 
     * @param indexToBeUpdate index of element to update
     * @param value           new value to set
     */
    public void updateAtIndex(int indexToBeUpdate, int value) {
        if(indexToBeUpdate < 0 || indexToBeUpdate >= N){
            return;
        }
        updateHelper(0, N - 1, 0, indexToBeUpdate, value);
    }

    /**
     * Recursive helper for updating the segment tree.
     * 
     * @param nodeLow            left bound of current node segment
     * @param nodeHigh           right bound of current node segment
     * @param currNodeTreeIndex  current index in segment tree
     * @param indexToUpdate      index to update in original array
     * @param newValue           new value to set
     */
    private void updateHelper(int nodeLow, int nodeHigh, int currNodeTreeIndex, int indexToUpdate, int newValue) {
        if (nodeLow == nodeHigh && nodeLow == indexToUpdate) {
            this.tree[currNodeTreeIndex] = newValue;
            return;
        }

        int mid = nodeLow + (nodeHigh - nodeLow) / 2;
        if (indexToUpdate <= mid) {
            updateHelper(nodeLow, mid, currNodeTreeIndex * 2 + 1, indexToUpdate, newValue);
        } else {
            updateHelper(mid + 1, nodeHigh, currNodeTreeIndex * 2 + 2, indexToUpdate, newValue);
        }

        // updating the new value
        tree[currNodeTreeIndex] = tree[currNodeTreeIndex * 2 + 1] + tree[currNodeTreeIndex * 2 + 2];
        return;
    }

    public void printSegmentTree() {
        for (int ele : this.tree) {
            System.out.print(ele + ", ");
        }
        System.out.println();
    }
}

public class SegmentTreeImplementation {

    public static void main(String[] args) {

        // building segment tree for finding sum of elements in ranges
        int[] arr = { 2, 5, 1, 4, 9, 3 };
        SegmentTree segmentTree = new SegmentTree(arr);

        segmentTree.printSegmentTree();
        System.out.println("Sum of elements from index 1, 4: " + segmentTree.query(1, 4));// 19
        System.out.println("Sum of elements from index 0, 1: " + segmentTree.query(0, 1));// 7
        System.out.println("Sum of elements from index 0, 1: " + segmentTree.query(1, 3));// 10
        System.out.println("Sum of elements from index 4, 5: " + segmentTree.query(4, 5)); // 12

        segmentTree.updateAtIndex(3, 7);

        segmentTree.printSegmentTree();

        System.out.println("Sum of elements from index 1, 4: " + segmentTree.query(1, 4));// 22
        System.out.println("Sum of elements from index 0, 1: " + segmentTree.query(0, 1));// 7
        System.out.println("Sum of elements from index 0, 1: " + segmentTree.query(1, 3));// 13
        System.out.println("Sum of elements from index 4, 5: " + segmentTree.query(4, 5)); // 12


        /*
            24, 8, 16, 7, 1, 13, 3, 2, 5, 0, 0, 4, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            Sum of elements from index 1, 4: 19
            Sum of elements from index 0, 1: 7
            Sum of elements from index 0, 1: 10
            Sum of elements from index 4, 5: 12
            27, 8, 19, 7, 1, 16, 3, 2, 5, 0, 0, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            Sum of elements from index 1, 4: 22
            Sum of elements from index 0, 1: 7
            Sum of elements from index 0, 1: 13
            Sum of elements from index 4, 5: 12
         */
    }
}
