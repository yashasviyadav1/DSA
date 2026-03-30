import java.util.LinkedList;
import java.util.Scanner;

// Generic Hash Table class
class HashTable<K, V> {
    // Inner class to store Key-Value pairs
    private class Entry {
        K key;
        V value;
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }

    private LinkedList<Entry>[] table;
    private int capacity;

    // Constructor to initialize the table
    public HashTable(int capacity) {
        this.capacity = capacity;
        table = new LinkedList[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = new LinkedList<>();
        }
    }

    // Hash Function
    private int getHash(K key) {
        return Math.abs(key.hashCode()) % capacity;
    }

    // INSERT Operation
    public void insert(K key, V value) {
        int index = getHash(key);
        // Check if key already exists, update if so
        for (Entry entry : table[index]) {
            if (entry.key.equals(key)) {
                entry.value = value;
                System.out.println("Updated: " + key + " -> " + value);
                return;
            }
        }
        // If not found, add new entry
        table[index].add(new Entry(key, value));
        System.out.println("Inserted: " + key + " -> " + value);
    }

    // SEARCH Operation
    public V search(K key) {
        int index = getHash(key);
        for (Entry entry : table[index]) {
            if (entry.key.equals(key)) {
                return entry.value;
            }
        }
        return null;
    }

    // DELETE Operation
    public void delete(K key) {
        int index = getHash(key);
        Entry toRemove = null;
        for (Entry entry : table[index]) {
            if (entry.key.equals(key)) {
                toRemove = entry;
                break;
            }
        }
        if (toRemove != null) {
            table[index].remove(toRemove);
            System.out.println("Deleted key: " + key);
        } else {
            System.out.println("Key not found.");
        }
    }
}

// Main class to test the Dictionary
public class DictionaryApp {
    public static void main(String[] args) {
        HashTable<String, Integer> dictionary = new HashTable<>(10);
        Scanner sc = new Scanner(System.in);
        
        System.out.println("--- DICTIONARY IMPLEMENTATION ---");
        
        // 1. Insert Data
        dictionary.insert("Apple", 100);
        dictionary.insert("Banana", 200);
        dictionary.insert("Orange", 300);
        
        // 2. Search Data
        System.out.println("\nSearching for 'Banana': " + dictionary.search("Banana"));
        System.out.println("Searching for 'Grapes': " + dictionary.search("Grapes"));
        
        // 3. Delete Data
        System.out.println();
        dictionary.delete("Apple");
        System.out.println("Searching for 'Apple' after delete: " + dictionary.search("Apple"));
    }
}