import java.util.List;
import java.util.Arrays;
import java.util.Collections;

/**
 * A utility class for performing one-dimensional range searching
 * on a sorted list of integers using binary search.
 *
 * <p>This class sorts the input list internally and provides methods
 * to efficiently find all elements that fall within a given inclusive range.
 * The range query is answered in O(log n + k), where n is the number of elements
 * and k is the number of results returned.</p>
 */
class BinarySortedRangeSearch{
    private List<Integer> elements;

    /**
     * Constructs a BinarySortedRangeSearch instance with the given elements.
     * The list is internally sorted for efficient range searching.
     *
     * @param elements the list of integers to be stored and queried
     */
    BinarySortedRangeSearch(List<Integer> elements){
        Collections.sort(elements);
        this.elements = elements;
    }
    
    /**
     * Returns all elements within the specified inclusive range [start, end].
     *
     * <p>If the input list is empty, the range is invalid (start > end),
     * or no elements fall within the range, an empty array is returned.</p>
     *
     * @param start the lower bound of the range (inclusive)
     * @param end   the upper bound of the range (inclusive)
     * @return an array containing all elements between start and end (inclusive),
     *         or an empty array if none exist
     */
    public int[] searchRange(int start, int end){
        // find lower bound elements index i (i.e element >= start ) and higher bound j (element <= end) using the binary search
        // loop from i to j and print all k elements
        if(this.elements.isEmpty() || start > end){ // empty array or reversed query like search(14, 10) 
            return new int[0];
        }
        
        int lowerBoundIndex = findLowerBound(start);
        int higherBoundIndex = findHigherBound(end);

        if(lowerBoundIndex == -1 || higherBoundIndex == -1 || lowerBoundIndex > higherBoundIndex){
            return new int[0];
        }

        int[] elementsInRange = new int[higherBoundIndex - lowerBoundIndex + 1]; 
        int index = 0;
        for(int i=lowerBoundIndex; i <= higherBoundIndex; i++){
            elementsInRange[index++] = elements.get(i);
        }
        return elementsInRange;
    }

    /**
     * Finds the index of the smallest element greater than or equal to the given key.
     *
     * @param key the value to search for
     * @return the index of the smallest element ≥ key, or -1 if no such element exists
     */
    private int findLowerBound(int key){
        int low=0, high = elements.size()-1, mid;
        int possibleAns = -1;
        while(low <= high){
            mid = low + (high - low)/2;
            if(elements.get(mid) == key){
                return mid;
            }
            else if(elements.get(mid) > key){
                possibleAns = mid;
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return possibleAns;
    }

    /**
     * Finds the index of the largest element less than or equal to the given key.
     *
     * @param key the value to search for
     * @return the index of the largest element ≤ key, or -1 if no such element exists
     */
    private int findHigherBound(int key){
        int low=0, high = elements.size()-1, mid;
        int possibleAns = -1;
        while(low <= high){
            mid = low + (high - low)/2;
            if(elements.get(mid) == key){
                return mid;
            }
            else if(elements.get(mid) > key){
                high = mid - 1;
            }
            else{
                possibleAns = mid;
                low = mid + 1;
            }
        }
        return possibleAns;
    }

}

/**
 * Demonstrates the usage of {@link BinarySortedRangeSearch}.
 */
public class SortedArrayBinarySearchRangeSearch {

    public static void main(String[] args) {
        
        List<Integer> arr = Arrays.asList(2, 1, 4, 3, 10, 6, 12);
        BinarySortedRangeSearch binarySortedSearch = new BinarySortedRangeSearch(arr);

        int[] rangeElements = binarySortedSearch.searchRange(3, 6);

        System.out.println("Elements in range are: " );
        for(int i=0; i < rangeElements.length; i++){
            System.out.print(rangeElements[i] + " ");
        }

        /* output : 
            3 4 6 
         */
        // int[] rangeElements = binarySortedSearch.searchRange(16, 23);// edge
        // int[] rangeElements = binarySortedSearch.searchRange(4, 14);// edge 2

    }
}
