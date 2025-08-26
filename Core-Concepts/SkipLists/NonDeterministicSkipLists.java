package SkipLists;

import java.util.Random;

/**
 * A node in the Skip List that stores data and references to next nodes at
 * various levels.
 * 
 * @param <T> the type of data stored in the node, must be Comparable
 */
class Node<T> {
    T data;
    Node<T>[] next;

    /**
     * Constructs a new Node with the specified data and level.
     * 
     * @param data  the data to be stored in the node
     * @param level the maximum level (height) of the node, determines the size of
     *              the next array
     * 
     *              * Suppresses the "unchecked" warning caused by creating a
     *              generic array.
     *
     *              Explanation:
     *              - Java does not allow direct creation of generic arrays (e.g.,
     *              new Node<String>[...])
     *              because arrays are covariant and reified at runtime, while
     *              generics use type erasure.
     *              Mixing the two would break type safety.
     *
     *              - As a workaround, we first create a raw Node[] array (new
     *              Node[...]) and then cast it
     *              to Node<T>[]. This cast is unchecked because the JVM cannot
     *              verify that the array
     *              will only contain Node<T> elements.
     *
     *              - The @SuppressWarnings("unchecked") annotation silences the
     *              compiler warning that
     *              results from this cast. It is safe as long as we only ever
     *              insert Node<T> objects
     *              into this array.
     *
     *              In short: This is a standard workaround to create arrays of
     *              generic types in Java,
     *              but it relies on developer discipline to maintain type safety.
     */
    @SuppressWarnings("unchecked")
    public Node(T data, int level) {
        this.data = data;
        next = (Node<T>[]) new Node[level + 1]; // if for a node level is 11 i.e from 0 to 11 then we need to have 12
                                                // size
    }
}

/**
 * A probabilistic/Non deterministic skip list implementation that provides
 * average O(log n) time complexity
 * for search, insertion, and deletion operations.
 * 
 * <p>
 * The skip list maintains multiple levels of linked lists, with higher levels
 * containing
 * fewer elements and acting as "express lanes" for faster searching.
 * </p>
 * 
 * @param <T> the type of elements maintained by this skip list, must be
 *            Comparable
 */
class SkipList<T extends Comparable<T>> {

    private final Node<T> head;
    private int currentLevel;
    private final Random random;

    private static final int MAX_LEVEL = 16;
    private static final Float P_FACTOR = 0.5f;

    public SkipList() {
        this.head = new Node<T>(null, MAX_LEVEL);
        this.currentLevel = 0;
        this.random = new Random();
    }

    /**
     * Inserts the specified element into the skip list.
     * Duplicate elements are not allowed and will be ignored.
     * 
     * @param key the element to be inserted into the skip list
     */
    public void insert(T key) {
        @SuppressWarnings("unchecked")
        Node<T>[] predecessors = (Node<T>[]) new Node[MAX_LEVEL + 1];
        Node<T> curr = head;
        for (int i = currentLevel; i >= 0; i--) {
            while (curr != null && curr.next[i] != null && curr.next[i].data.compareTo(key) < 0) {
                curr = curr.next[i];
            }
            predecessors[i] = curr;
        }

        // we have alrady stored the predecessors in array, are are on level 0, so move
        // curr to the next element to make sure it is not a duplicate key case
        curr = curr.next[0];
        if (curr == null || !curr.data.equals(key)) {
            // if this new height h is more then the longest node of the alrady existing
            // list with height (h-y), then for the remaining y levels, we need to assign
            // head node as predecessor for the new node
            int levelForNewNode = getRandomHeight();
            if (levelForNewNode > currentLevel) { // this new nodes height is more then current maxumum height of a
                                                  // node, add head as predecessors for this node
                for (int i = currentLevel + 1; i <= levelForNewNode; i++) {
                    predecessors[i] = head;
                }
                currentLevel = levelForNewNode;
            }

            Node<T> newNode = new Node<>(key, levelForNewNode);

            for (int i = 0; i <= levelForNewNode; i++) {
                newNode.next[i] = predecessors[i].next[i];
                predecessors[i].next[i] = newNode;
            }
        }
    }

    /**
     * Generates a random height for a new node using the probability factor.
     * The height follows a geometric distribution.
     * 
     * @return a random level between 0 and MAX_LEVEL
     */
    private int getRandomHeight() {
        int level = 0;
        while (random.nextFloat() < P_FACTOR && level < MAX_LEVEL) {
            level++;
        }
        return level;
    }

    /**
     * Searches for the specified element in the skip list.
     * 
     * @param key the element to search for
     * @return true if the element is found, false otherwise
     */
    public boolean search(T key) {
        Node<T> curr = head;
        for (int i = currentLevel; i >= 0; i--) {
            while (curr != null && curr.next[i] != null && curr.next[i].data.compareTo(key) < 0) {
                curr = curr.next[i];
            }
        }
        curr = curr.next[0];
        return curr != null && curr.data.equals(key);
    }

    /**
     * Removes the specified element from the skip list if it exists.
     * If the element is not found, the method does nothing.
     * 
     * @param key the element to be removed from the skip list
     */
    public void delete(T key) {
        @SuppressWarnings("unchecked")
        Node<T>[] predecessors = (Node<T>[]) new Node[MAX_LEVEL + 1];
        Node<T> curr = head;
        for (int i = currentLevel; i >= 0; i--) {
            while (curr != null && curr.next[i] != null && curr.next[i].data.compareTo(key) < 0) {
                curr = curr.next[i];
            }
            predecessors[i] = curr;
        }
        curr = curr.next[0];

        if (curr != null && curr.data.equals(key)) {
            // time to change some pointers to remove the node completely
            // going 0 to h level 1 by 1 and for each level of predecessor when predecessor
            // point to curr, change it
            // the moment we find a predesesor that doesnpt point to curr, then no need to
            // go above, as we consumed comlete height
            for (int i = 0; i <= currentLevel; i++) {
                if (predecessors[i].next[i] != curr) {
                    break;
                }
                predecessors[i].next[i] = curr.next[i];
            }
        }

        // if after deletion of nodes at multiple level if somehow the max height has
        // been now reduced, just decrease the list's level
        while (currentLevel > 0 && head.next[currentLevel] == null) {
            currentLevel--;
        }
    }

    /**
     * Displays the current state of the skip list in a formatted manner.
     * Shows each level from highest to lowest with all elements at that level.
     */
    public void display() {
        System.out.println("\n--- Skip List ---");
        for (int i = currentLevel; i >= 0; i--) {
            System.out.print("Level " + i + ": " + "head -> ");
            Node<T> node = head.next[i];
            while (node != null) {
                System.out.print(node.data + " -> ");
                node = node.next[i];
            }
            System.out.println("NIL");
        }
        System.out.println("-----------------\n");
    }
}

public class NonDeterministicSkipLists {

    public static void main(String[] args) {

        SkipList<Integer> skipList = new SkipList<>();

        skipList.insert(10);
        skipList.insert(30);
        skipList.insert(50);
        skipList.insert(20);
        skipList.insert(40);
        skipList.insert(60);

        skipList.display();

        // Search for elements
        System.out.println("Search for 20: " + skipList.search(20));
        System.out.println("Search for 25: " + skipList.search(25));

        // Delete an element
        skipList.delete(30);
        // Delete a non-existent element
        skipList.delete(100);

        // Display the list again
        skipList.display();

        /*
         * - since this is a undeterministic implementation of skip lists i.e structure
         * is different of the skip list even if we insert nodes in same order
         * - so their can be many outputs, one of them is :
         * 
         * --- Skip List ---
         * Level 2: head -------------> 30 -------------> 60 -> NIL
         * Level 1: head -------------> 30 -------> 50 -> 60 -> NIL
         * Level 0: head -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> NIL
         * -----------------
         * 
         * Search for 20: true
         * Search for 25: false
         * 
         * --- Skip List ---
         * Level 2: head -------------------------> 60 -> NIL
         * Level 1: head -------------------> 50 -> 60 -> NIL
         * Level 0: head -> 10 -> 20 -> 40 -> 50 -> 60 -> NIL
         */
    }
}