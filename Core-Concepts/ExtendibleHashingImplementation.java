import java.util.ArrayList;
import java.util.List;
import java.util.Optional;


/**
 * Utility class for hashing operations.
 * This class provides static methods to compute well-distributed hash codes for different types of keys.
 * By declaring all functions as static, they belong to the class itself, not an object instance.
 * This allows them to be called like {@code HashUtils.hashCode(key)} instead of {@code new HashUtils().hashCode(key)},
 * which is faster and more memory-efficient.
 */
class HashUtils {

    /**
     * A prime constant used in the polynomial rolling hash function for strings to ensure better hash distribution.
     */
    private static final int PRIME_CONSTANT = 31;

    /**
     * Hashes a String using a polynomial rolling hash function.
     * The final hash is XORed with a right-shifted version of itself to ensure that the
     * most significant bits (MSB) are not lost when the index is calculated using a bitwise AND with a mask.
     * This improves the distribution of hash values.
     *
     * @param key The string to be hashed.
     * @return The calculated 32-bit hash code.
     */
    private static int hashString(String key) {
        // polynomial rolling hash function for strings
        if (key == null) {
            return 0;
        }
        int hash = 0;
        for (char ch : key.toCharArray()) {
            hash = (hash * PRIME_CONSTANT) + (int) ch;
        }
        hash ^= (hash >>> 16); // Mix in the higher bits, XOR with right shifted value to reduce collisions (so that MSB bits are never lost), because & with mask for finding index will only consider the dth bits
        return hash;
    }

    /**
     * Hashes an integer. It performs an XOR operation with a right-shifted version of itself
     * to improve the distribution of the hash code, especially for keys that have patterns.
     *
     * @param key The integer to be hashed.
     * @return The calculated 32-bit hash code.
     */
    private static int hashInteger(int key) {
        return key ^ (key >>> 16); // XOR with right shifted value to reduce collisions
    }

    /**
     * Provides a fallback hash mechanism for object types that are not explicitly handled.
     * It defaults to using Java's built-in {@code hashCode()} method.
     *
     * @param key The object to be hashed.
     * @return The object's default hash code, or 0 if the key is null.
     */
    private static int hashFallback(Object key) {
        return key == null ? 0 : key.hashCode();
    }

    /**
     * since the function overloading is a compile-time feature, and out key is a generic type K, so at compile time
     * but since func overloading takes place at compile time, the compiler cannot determine which function to call for
     * type K, so we need to provide a single dispatcher method that can handle all types of keys.
     * @param key
     * @return
     */
    public static int hashCode(Object key) {
        if (key instanceof String) {
            return hashString((String) key);
        } else if (key instanceof Integer) {
            return hashInteger((Integer) key);
        } else {
            return hashFallback(key);
        }
    }
}

/**
 * A generic class representing a key-value pair.
 * This is used to store data within the buckets of the hash table.
 *
 * @param <K> The type of the key.
 * @param <V> The type of the value.
 */
class Entry<K, V> {
    private final K key;
    private V value;

    public Entry(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public K getKey() {
        return key;
    }

    public V getValue() {
        return value;
    }

    public void setValue(V value) {
        this.value = value;
    }

    @Override
    public String toString() {
        return "Entry{" +
                "key: " + key +
                ", value: " + value +
                "}";
    }
}

/**
 * Represents a data bucket in the extendible hash table.
 * Each bucket has a fixed capacity and a local depth.
 *
 * @param <K> The type of the keys stored in this bucket.
 * @param <V> The type of the values stored in this bucket.
 */
class Bucket<K, V> {
    private int localDepth;
    private final int capacity;
    private final List<Entry<K, V>> entries;

    public Bucket(int localDepth, int capacity) {
        this.localDepth = localDepth;
        this.capacity = capacity;
        this.entries = new ArrayList<>(capacity);
    }

    public List<Entry<K, V>> getEntries() {
        return entries;
    }

    public Optional<V> get(K key) {
        for (Entry<K, V> entry : entries) {
            if (entry.getKey().equals(key)) {
                return Optional.of(entry.getValue());
            }
        }
        return Optional.empty();
    }

    public boolean insert(K key, V value) {
        if (entries.size() < capacity) {
            entries.add(new Entry<>(key, value));
            return true;
        }
        return false;
    }

    public boolean isFull() {
        return entries.size() >= capacity;
    }

    public boolean isNotFull() {
        return !isFull();
    }

    public void incrementLocalDepth() {
        localDepth++;
    }

    public int getLocalDepth() {
        return localDepth;
    }

    @Override
    public String toString() {
        return "Bucket--[" +
                "localDepth=" + localDepth +
                ", entries=" + entries +
                "]";
    }
}

/**
 * Extendible Hashing implementation.
 * This class provides a way to store key-value pairs in a hash table that can grow dynamically.
 * Comprises of a 'directory' that maps keys(index) to buckets.
 * Each bucket can hold a limited number of entries, defined by the bucket capacity.
 * Its part of 'Dynamic Hashing' as compared to Open Addressing or Chaining (which are static).
 * When a bucket becomes full, it splits and the directory is updated accordingly.
 * There are 2 main types of splitting:
 * 1. Hard Split: When the bucket is full and its local depth is equal to the global depth, the directory size is doubled.
 * 2. Soft Split: When the bucket is full but its local depth is less than the global Depth, the bucket is split and the directory is updated to point to the new bucket.
 *
 * @param <K> Type of keys
 * @param <V> Type of values
 */

class ExtendibleHashing<K, V> {

    private final List<Bucket<K, V>> directory;
    private int globalDepth;
    private final int bucketCapacity;

    public ExtendibleHashing(int bucketCapacity) {
        this.globalDepth = 1;
        this.bucketCapacity = bucketCapacity;
        this.directory = new ArrayList<>((int) Math.pow(2, globalDepth));
        this.directory.add(new Bucket<>(globalDepth, bucketCapacity));
        this.directory.add(new Bucket<>(globalDepth, bucketCapacity));
    }


    /**
     * Calculates the index of the bucket in the directory for a given key.
     * The index is determined by the least significant 'd' bits of the key's hash code,
     * where 'd' is the current global depth. This is achieved efficiently using a bitwise AND
     * with a mask, ensuring the index is always within the directory's bounds.
     *
     * @param key The key whose bucket index is to be found.
     * @return The index in the directory.
     */
    private int getBucketIndex(K key) {
        int hash = HashUtils.hashCode(key);
        int mask = (1 << globalDepth) - 1; // these 2 steps are equivalent to doing (hash % 2^globalDepth) or hash % (size of directory) that we usually do in hashing to find index, bitwise & is more efficient then modulus operation
        return hash & mask;
    }

    public V get(K key) {
        int index = getBucketIndex(key);
        Optional<V> value = directory.get(index).get(key);
        return value.orElse(null);
    }

    /**
     * Inserts a key-value pair into the hash table.
     * If the target bucket is full, it triggers a split operation.
     *
     * @param key   The key to insert.
     * @param value The value to associate with the key.
     * @return {@code true} upon successful insertion.
     */
    public boolean insert(K key, V value) {
        int index = getBucketIndex(key);
        Bucket<K, V> bucket = directory.get(index);
        if (bucket.isNotFull()) {
            return bucket.insert(key, value);
        } else if (bucket.getLocalDepth() == globalDepth) {
            doubleDirectorySize();
            splitBucket(index, bucket);
            return insert(key, value); // recursive call to try to insert after splitting
        } else {
            splitBucket(index, bucket);
            return insert(key, value);
        }
    }

    /**
     * Doubles the size of the directory when a bucket splits and its local depth equals the global depth.
     * It increments the global depth and duplicates the existing pointers to fill the new half of the directory.
     */
    public void doubleDirectorySize() {
        int currentSize = directory.size();
        globalDepth++;
        for (int i = 0; i < currentSize; i++) { // duplicate existing buckets, to double the size
            directory.add(directory.get(i));
        }
    }

    /**
     * Splits an overflowed bucket and redistributes its entries.
     * It creates a new bucket and updates the directory pointers to correctly map to the old and new buckets.
     *
     * @param indexOfBucketToSplit The directory index that led to the bucket to be split.
     * @param bucketToSplit        The bucket that is full and needs to be split.
     */
    public void splitBucket(int indexOfBucketToSplit, Bucket<K, V> bucketToSplit) {
        int initialLocalDepth = bucketToSplit.getLocalDepth();
        Bucket<K, V> newBucket = new Bucket<>(initialLocalDepth + 1, bucketCapacity);
        List<Entry<K, V>> oldEntries = new ArrayList<>(bucketToSplit.getEntries());
        bucketToSplit.getEntries().clear();
        bucketToSplit.incrementLocalDepth();

        // Rewiring directory to point to the old bucket (to split) and new bucket
        for (int i = 0; i < directory.size(); i++) {
            if (directory.get(i) == bucketToSplit) { // from this we are clear that we need to split this bucket, but to make sure if old bucket to assign or new is below logic
                if ((i & (1 << initialLocalDepth)) != 0) {
                    directory.set(i, newBucket);
                }
            }
        }

        // re insert the old entries
        for (Entry<K, V> entry : oldEntries) {
            insert(entry.getKey(), entry.getValue());
        }
    }

    public List<Bucket<K, V>> getDirectory() {
        return directory;
    }

    public void display() {
        System.out.println("--------Directory--------");
        System.out.println("Global Depth: " + globalDepth);
        for (int i = 0; i < directory.size(); i++) {
            System.out.println("i[" + i + "] -> " + directory.get(i));
        }
        System.out.println("-------------------------");
    }
}

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class ExtendibleHashingImplementation {
    public static void main(String[] args) {

        ExtendibleHashing<Integer, String> addressBook = new ExtendibleHashing<>(2);

        addressBook.insert(4, "New York");
        addressBook.insert(2, "San Francisco");
        addressBook.insert(7, "Chicago");
        addressBook.insert(5, "Los Angeles");
        addressBook.insert(3, "Chandigarh, India");
        addressBook.insert(6, "Calcutta, India");

        addressBook.display();

        System.out.println(addressBook.get(6));
        System.out.println(addressBook.get(4));

        /*
        Expected Output:-

            --------Directory--------
            Global Depth: 2
            i[0] -> Bucket--[localDepth=2, entries=[Entry{key: 4, value: New York}]]
            i[1] -> Bucket--[localDepth=2, entries=[Entry{key: 5, value: Los Angeles}]]
            i[2] -> Bucket--[localDepth=2, entries=[Entry{key: 2, value: San Francisco}, Entry{key: 6, value: Calcutta, India}]]
            i[3] -> Bucket--[localDepth=2, entries=[Entry{key: 7, value: Chicago}, Entry{key: 3, value: Chandigarh, India}]]
            -------------------------
            Calcutta, India
            New York
         */

    }
}