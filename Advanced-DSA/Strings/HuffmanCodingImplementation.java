
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Map;

/**
 * Represents a node in the Huffman Tree.
 * Each node can either be:
 * - A leaf node (stores a character and its frequency)
 * - An internal node (stores combined frequency and links to left/right children)
 */
class Node implements Comparable<Node>{
    char ch;
    int freq;
    Node left, right;
    Node(char ch, int freq){
        this.ch = ch;
        this.freq = freq;
        this.left = this.right = null;
    }

    // < 0 → this node is “smaller” (higher priority).
    // = 0 → equal.
    // > 0 → this node is “bigger” (lower priority).
    // compareTo in priorityQueue works like this :- 
        // if value is negative it does opposite (gives highest proiority -> sends it to top)
        // if value +ve it gives lowest priority
    @Override
    public int compareTo(Node other){
        return this.freq - other.freq;
    }
}

/**
 * Implements the Huffman Coding algorithm for text compression and decompression.
 * 
 * Steps:
 * 1. Build frequency map of characters.
 * 2. Construct Huffman Tree using a min-heap (priority queue).
 * 3. Generate Huffman codes (0 = left, 1 = right).
 * 4. Encode string into compressed binary string.
 * 5. Decode binary string back into original text.
 * 
 * Handles special edge case: input string with only one unique character.
 */
class HuffmanCoding{    
    Node root;
    Map<Character, String> charToHuffmanCode;

    HuffmanCoding(){
        this.root = null;// Root of the Huffman Tree
        this.charToHuffmanCode = new HashMap<>();// Mapping of characters to Huffman codes
    }

    /**
     * Compresses a given text string into its Huffman-encoded binary representation.
     *
     * @param text the original text to compress
     * @return Huffman-encoded binary string
     */
    public String compress(String text){
        this.root = buildHuffmanTree(text); // building the tree - phase 1 
        if(root.left == null && root.right == null){ // edge case handling: in a str like 'AAAA' which has only single char only, the huff code will be empty, which will result in wrong decompression, so we are inserting 0 here to avoid that (we already have base case as leaf node in the decompression so no need to worry)
            this.charToHuffmanCode.put(root.ch, "0");
        }else{
            generateHuffmapCode(this.root, "");// mapping original string's alphabets to the huffmap code)
        }
        String encodedString = encodeString(text);
        return encodedString;
    }

    /**
     * Builds the Huffman Tree based on character frequencies.
     *
     * @param text the input text
     * @return root of the Huffman Tree
     */

    private Node buildHuffmanTree(String text){
        HashMap<Character, Integer> charToFreq = new HashMap<>();
        PriorityQueue<Node> minHeap = new PriorityQueue<>();;
        // creating freq array
        for(char ch:text.toCharArray()){
            charToFreq.put(ch, charToFreq.getOrDefault(ch, 0) + 1);
        }
        // adding nodes to tree to initilize it
        for(char ch:charToFreq.keySet()){
            minHeap.add(new Node(ch, charToFreq.get(ch)));
        }
        // lets create the actual huffman tree
        while(minHeap.size() > 1){
            Node left = minHeap.poll();
            Node right = minHeap.poll();
            Node newNode = new Node('\0', left.freq + right.freq);
            newNode.left = left;
            newNode.right = right;
            minHeap.add(newNode);
        }
        return minHeap.peek(); // now the minheap has only 1 node left the root, so return it (note: removing it from heap will not dislocate anything sice the tree is preserved in the root itself)
    }

    /**
     * Recursively generates Huffman codes from the tree.
     *
     * @param curr current node
     * @param code the binary code built so far
     */
    private void generateHuffmapCode(Node curr, String code){
        if(curr == null) return;
        if(curr.left == null && curr.right == null){
            this.charToHuffmanCode.put(curr.ch, code);
            return;
        }
        generateHuffmapCode(curr.left, code + "0");
        generateHuffmapCode(curr.right, code + "1");
    }

    /**
     * Encodes the input string into Huffman-encoded binary string.
     *
     * @param text original input text
     * @return encoded binary string
     */
    private String encodeString(String text){
        StringBuilder encodedString = new StringBuilder();
        for(char ch:text.toCharArray()){
            encodedString.append(charToHuffmanCode.get(ch));
        }
        return encodedString.toString();
    }

    /**
     * Decompresses a Huffman-encoded binary string back to original text.
     *
     * @param compressedString encoded binary string
     * @return decoded original text
     */
    public String decompress(String compressedString){
        StringBuilder decoded = new StringBuilder();
        Node curr = this.root;
        // Edge case: single unique character eg. AAAA -> 0000 -> AAAA (in response to handling done at line 64)
        if(curr.left == null && curr.right == null){
            for (int i=0; i < compressedString.length(); i++) {
                decoded.append(root.ch);
            }
            return decoded.toString();
        }
        // normal cases: eg. BANANA 
        for(char ch:compressedString.toCharArray()){
            if(ch == '0'){
                curr = curr.left;
            }
            else{
                curr = curr.right;
            }
            if(curr.left == null && curr.right == null){ // reached leaf, add this to decoded and reset curr
                decoded.append(curr.ch);
                curr = this.root;
            }
            
        }
        return decoded.toString();
    }

}

public class HuffmanCodingImplementation{
    public static void main(String[] args){

        HuffmanCoding huffman = new HuffmanCoding();
        String original = "YASHASVIYADAV";
        original = "YYYY";
        String compressed = huffman.compress(original);
        String decoded = huffman.decompress(compressed);

        System.out.println("-".repeat(20));
        System.out.println("Original: " + original);
        System.out.println("Compressed: " + compressed);
        System.out.println("Decompressed: " + decoded);
        System.out.println("Was it successfully decoded: " + original.equals(decoded));

        /*
            Original: YASHASVIYADAV
            Compressed: 00101110111101111100100010011010110
            Decompressed: YASHASVIYADAV
            Was it successfully decoded: true
 
            Original: YYYY
            Compressed: 0000
            Decompressed: YYYY
            Was it successfully decoded: true
         */
        System.out.println("-".repeat(20));

    }
}