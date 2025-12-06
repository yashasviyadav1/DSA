## **Dictionaries**

- Implementations of Dictionary
    - Unsorted List
    - Sorted List
    - Balanced BST
    - Hash Table
        - Collision, Hash Function
        - Collision Handling using `Separate Chaining`, `Open Addressing`
            - Separate Chaining
            - Open Addressing
                - linear probing
                    - primary clustering
                - quadratic probing
                    - secondary clustering
    - Rehashing
    - Extendible Hashing

### **Dictionary ADT: Study Notes**

This document provides a concise overview of the different ways to implement a Dictionary (or Map) Abstract Data Type.

### **1. The Four Implementations: At a Glance**

| **Implementation** | **Get / Lookup** | **Set / Insert** | **Remove** | **Keeps Keys Sorted?** | **Best For (in Java)** |
| --- | --- | --- | --- | --- | --- |
| Unsorted List | O(n) | O(n) | O(n) | No | Education only |
| Sorted List | O(logn) | O(n) | O(n) | Yes | Read-heavy, write-rare scenarios |
| **Balanced BST** | O(logn) | O(logn) | O(logn) | **Yes** | **TreeMap**: Reliable performance + sorted order |
| **Hash Table** | O(1) | O(1) | O(1) | **No** | **HashMap**: Maximum speed when order is irrelevant |

### **2. Implementation Details**

### **Method 1: Unsorted List**

- **Core Idea:** Store (key, value) pairs in a list.
- **How it Works:** Every operation requires a full linear scan of the list.
- **Verdict:** Simple to understand, but too slow for practical use.

### **Method 2: Sorted List**

- **Core Idea:** Store pairs sorted by key in an ArrayList.
- **How it Works:**
- **Get:** Use fast O(log n) Binary Search.
- **Set/Remove:** Finding the spot is fast, but inserting/deleting requires an O(n) shift of elements.
- **Verdict:** A good trade-off if you need sorted keys and do many more reads than writes.

### **Method 3: Balanced Binary Search Tree (BST)**

- **Core Idea:** A tree where left children are smaller and right children are larger. It **self-balances** after changes to keep its height at O(log n).
- **How it Works:** All operations are a traversal from the root down a path of the tree.
- **Verdict:** The best choice for great, predictable performance **and** sorted keys. Embodied by java.util.TreeMap.

### **Method 4: Hash Table**

- **Core Idea:** Use a **hash function** to map a key to an array index ("bucket").
- **How it Works:**
1. Calculate an index from the key.
2. Go to that bucket.
3. If multiple items are in the bucket (a "collision"), search the short LinkedList there.
- **Verdict:** The fastest general-purpose dictionary. Embodied by java.util.HashMap.

### **Topic: The Hash Function**

- **Goal:** To convert a key into an array index. Must be fast and distribute keys evenly.
- **Standard Algorithm:** Polynomial Hashing.
- hash = 0;
- for each char c: `hash = (hash * P) + character_value`_asci;
- **Example Dry Run: Polynomial Hashing for the key "cat"**

  Here's how the hash code for the string `"cat"` is calculated using the standard polynomial hash function.

  **Setup:**

    - **Key:** `"cat"`
    - **Prime Multiplier (`P`):** `31`
    - **ASCII Values:** `c` = 99, `a` = 97, `t` = 116

  **Calculation:**

    1. **Initial State:**
        - `hash = 0`
    2. **Process the first character: 'c'**
        - `hash = (current_hash * 31) + ascii('c')`
        - `hash = (0 * 31) + 99`
        - **Result:** `hash = 99`
    3. **Process the second character: 'a'**
        - `hash = (current_hash * 31) + ascii('a')`
        - `hash = (99 * 31) + 97`
        - `hash = 3069 + 97`
        - **Result:** `hash = 3166`
    4. **Process the third character: 't'**
        - `hash = (current_hash * 31) + ascii('t')`
        - `hash = (3166 * 31) + 116`
        - `hash = 98146 + 116`
        - **Result:** `hash = 98262`

  The final hash code for `"cat"` before any modulo operation is **98,262**.


### **Topic: Why use a Prime Number P as the multiplier?**

- **The Core Reason:** A prime P is very likely to be **coprime** with the table size M.
- **What this means:**
- **Prime P (Good):** The * P operation acts like a **perfect shuffle** of hash values. It preserves the information from all parts of the key.
- **Non-Prime P (Bad):** The * P operation **collapses** hash values. It destroys information from the start of the key, leading to many avoidable collisions.

### **Topic: Integer Overflow in Hashing**

- **Is it a problem?** No, it is an **expected and essential feature**, not a bug.
- **Why?** The wrap-around behavior of a fixed-size int provides a very fast, implicit form of modulo arithmetic that helps mix the bits of the key thoroughly.
- eg. `Integer.MAX_VALUE + 1` equals to `Integer.MIN_VALUE`  think of it like a circle the integer stores values from `Integer.MIN_VALUE TO Integer.MAX_VALUE`  so adding 1 to max value makes it min value so it never really overflows

### **Topic: Handling Negative Hash Codes**

- **Why do they happen?** They are a direct result of the integer overflow wrap-around.
- **How to fix it?** An array index cannot be negative. You must make the hash code non-negative *before* you take the modulo % M.
- **The Best Method:** Use a bitwise AND to force the sign bit to zero. This is robust and handles all edge cases.
- `int index = (hashCode & 0x7fffffff) % arraySize`;

**And with `0x7fffffff` explained:-**

In 32-bit signed integers, the first bit (left most) is the sign bit.
If it is 0 → the number is positive.
If it is 1 → the number is negative.
So in order to convert its sign to +ve (keeping all digits same) we and it with `Integer.MAX_VALUE` i.e `0x7fffffff` (in decimal form)

**Why do we use `Int.MAX` or `0x7fffffff` for AND operation:-**

Because `Integer.MAX_VALUE` or `0x7fffffff` is `01111111 11111111 11111111 11111111` in binary. 
Note that only first bit is 0.
So if we have any negative number eg. 
```
-5:         11111111 11111111 11111111 11111011  
 &
0x7fffffff: 01111111 11111111 11111111 11111111  

result:     01111111 11111111 11111111 11111011   -> 5
```

So This way we can change the sign of any value (which is necessary because we need to find index from teh hash so we need +ve hash value)



### **4.1 Core Architecture**

A hash table consists of three main components:

1. **An Array:** The underlying storage, where each slot is called a **bucket**.
2. **A Hash Function:** A function that maps a key to an array index.
3. **A Collision Handling Strategy:** A plan for what to do when two keys map to the same index.

### **4.2 The Hash Function: A Deep Dive**

The quality of the hash function determines the performance of the entire table.

- **Goal:** To be deterministic and to distribute keys uniformly (like a random scatter-shot).
- **Standard Algorithm (Polynomial Hashing):**`hash = (hash * P) + character_value`, iterated over the key's components.
- **Why use a prime number `P`?**
    - **The Core Reason:** A prime `P` is very likely to be **coprime** with the table size `M`. This mathematical property is critical.
    - **Prime `P` (Good):** The `P` operation acts like a **perfect shuffle** of the hash's bits. It preserves information from all parts of the key.
    - **Non-Prime `P` (Bad):** The `P` operation **collapses** the hash's bits. It destroys information from earlier parts of the key, leading to avoidable collisions.
- **Integer Overflow:**
    - Overflow is an **expected feature**, not a bug. The wrap-around behavior of a fixed-size `int` provides a fast, implicit form of modulo arithmetic that is excellent for mixing bits.
- **Handling Negative Hashes:**
    - Overflow is the cause of negative hash codes. An array index cannot be negative.
    - **Solution:** Make the hash code non-negative before the final modulo. The most robust method is `(hashCode & 0x7fffffff) % M`.

### **4.3 Collision Handling Strategy 1: Separate Chaining**

- **Method:** Each bucket in the array holds a pointer to a **`LinkedList`**. When a collision occurs, the new key-value pair is simply added to the list at that index.
- **Load Factor (λ):** A crucial metric defined as `λ = (number of items) / (table size)`. It represents the average number of items per bucket. A `λ > 1.0` indicates collisions have occurred.
- Cons : Uses extra memory for pointers; can lead to poor cache performance because list nodes may be scattered in memory.

### **4.4 Collision Handling Strategy 2: Open Addressing (Probing)**

- **Method:** All key-value pairs are stored directly in the array. If a collision occurs, you **probe** for the next available empty slot.
- **Deletion:** Requires a special "tombstone" marker to indicate a slot was once occupied, so searches don't stop prematurely.
- **Types of Probing:**
    1. **Linear Probing:**
        - **How:** If index `k` is taken, you probe sequentially. The formula for the i-th probe is:
          `index_i = (h(key) + i) % M`
        - **Problem:** Suffers from **Primary Clustering**, where long contiguous blocks form, degrading performance.
        - **Detailed Example:** Insert `[25, 47, 14]` into a table of size 11. `h(key) = key % 11`.
            1. **Insert `25`**: `h(25) = 3`. Slot 3 is empty. Place `25` there.
                - `Table: [ , , , 25, , , , , , , ]`
            2. **Insert `47`**: `h(47) = 3`. **Collision!**
                - Probe 1 (i=1): Check index `(3 + 1) % 11 = 4`. It's empty. Place `47` there.
                - `Table: [ , , , 25, 47, , , , , , ]`
            3. **Insert `14`**: `h(14) = 3`. **Collision!**
                - Probe 1 (i=1): Check index `(3 + 1) % 11 = 4`. Occupied.
                - Probe 2 (i=2): Check index `(3 + 2) % 11 = 5`. It's empty. Place `14` there.
                - `Table: [ , , , 25, 47, 14, , , , , ]`*This creates a "cluster" from index 3 to 5.*
    2. **Quadratic Probing:**
        - **How:** The probe jumps by quadratic steps. The formula for the i-th probe is:
          `index_i = (h(key) + i²) % M`
        - **Benefit:** "Jumps" over occupied slots, eliminating primary clustering.
        - **Problem:** Suffers from milder **Secondary Clustering**, where keys that share the same initial hash follow the same probe sequence.
        - **Detailed Example:** Insert `[25, 47, 14]` into a table of size 11. All hash to 3.
            1. **Insert `25`**: `h(25) = 3`. Slot 3 is empty. Place `25` there.
                - `Table: [ , , , 25, , , , , , , ]`
            2. **Insert `47`**: `h(47) = 3`. **Collision!**
                - Probe 1 (i=1): Check index `(3 + 1²) % 11 = 4`. It's empty. Place `47` there.
                - `Table: [ , , , 25, 47, , , , , , ]`
            3. **Insert `14`**: `h(14) = 3`. **Collision!**
                - Probe 1 (i=1): Check index `(3 + 1²) % 11 = 4`. Occupied.
                - Probe 2 (i=2): Check index `(3 + 2²) % 11 = 7`. It's empty. Place `14` there.
                - `Table: [ , , , 25, 47, , , 14, , , ]`*Notice how `14` "jumped" over the occupied slot 4 to land at 7.*
    3. **Double Hashing:**
        - **How:** Uses a second hash function, `h2(key)`, to determine a unique step size. The formula for the i-th probe is:
          `index_i = (h1(key) + i * h2(key)) % M`
        - **Benefit:** The most effective probing method for eliminating all forms of clustering.
        - **Detailed Example:** Insert `[25, 47, 14]`. All have `h1=3`. Let `h2(key) = 7 - (key % 7)`.
            1. **Insert `25`**: `h1(25) = 3`. Slot 3 is empty. Place `25` there.
                - `Table: [ , , , 25, , , , , , , ]`
            2. **Insert `47`**: `h1(47) = 3`. **Collision!**
                - Calculate step size: `h2(47) = 7 - (47 % 7) = 2`.
                - Probe 1: Check index `(3 + 1*2) % 11 = 5`. It's empty. Place `47` there.
                - `Table: [ , , , 25, , 47, , , , , ]`
            3. **Insert `14`**: `h1(14) = 3`. **Collision!**
                - Calculate step size: `h2(14) = 7 - (14 % 7) = 7`.
                - Probe 1: Check index `(3 + 1*7) % 11 = 10`. It's empty. Place `14` there.
                - `Table: [ , , , 25, , 47, , , , , 14]`*Even though all keys started at index 3, their unique step sizes (2 and 7) sent them to completely different locations.*

### **Part 5: Final Recommendations**

- **For Maximum Speed (Order Doesn't Matter):** Use a **Hash Table**. In Java, this is `java.util.HashMap`. This should be your default choice for a general-purpose dictionary.
- **For High Performance AND Sorted Order:** Use a **Balanced Binary Search Tree**. In Java, this is `java.util.TreeMap`.

### What is Rehashing?

Rehashing is the process of creating a new, larger hash table and re-inserting all the existing key-value pairs into this new table. This is done to maintain the performance of the hash table as the number of elements grows. It's a necessary "maintenance" operation.

---

### Why is Rehashing Necessary? The Load Factor

The efficiency of a hash table depends on keeping collisions to a minimum. As you add more and more elements to a fixed-size table, the number of collisions inevitably increases, and the performance starts to degrade. In the worst case, the lookup time can approach O(n).

To prevent this, we monitor the **load factor (λ)**.

- **Load Factor (λ) = (Total number of items) / (Size of the hash table array)**

Every hash table implementation has a **load factor threshold**, which is a predefined limit (commonly 0.75 for separate chaining).

**The Trigger:** When you perform an insertion that causes the load factor to **exceed** this threshold, the rehashing process is triggered.

Think of it like a filing cabinet 🗄️. If you have a 10-drawer cabinet (the array size) and you've filled 7 or 8 drawers with files (the items), finding any specific file starts to get slow. Instead of letting it get completely full, you decide it's time to upgrade to a bigger 20-drawer cabinet and reorganize everything. That reorganization is rehashing.

---

### The Rehashing Process: A Step-by-Step Guide

Let's say our current table has a size of 11 and our load factor threshold is 0.75. We have 8 items in it. When we try to insert the 9th item, the load factor becomes `9/11 ≈ 0.82`, which is greater than 0.75. Rehashing begins.

1. **Create a New, Larger Array:** A new array is created, typically double the size of the old one. To keep our math good (for prime number properties), let's say we double it and find the next prime number. So, we create a new, empty array of size, say, 23.
2. **Iterate Through the Old Table:** The system goes through every bucket of the **old** table (size 11).
3. **Recalculate Hashes and Re-insert:** For every single key-value pair found in the old table, it performs a **brand new hash calculation**. This is the most critical step.
    - The hash code of the key itself doesn't change.
    - However, the final index is calculated using the **new array size**: `index = hashCode % 23`.
    - The key-value pair is then inserted into its correct new position in the new, larger table.
4. **Replace the Old Table:** Once all the items have been moved from the old table to the new one, the old table is discarded by the garbage collector. The hash table object now points to the new, larger array.

### The Crucial Insight: Why You Can't Just Copy

You might wonder, "Why not just copy the contents of the old array into the new, larger one?"

The reason is that the array size (`M`) is a fundamental part of the index calculation (`index = hashCode % M`). If you change `M`, the index for almost every key will change.

- In the old table: `h("cat") % 11 = 1`
- In the new table: `h("cat") % 23 = 8` (using a hypothetical hash code)

Simply copying would put "cat" at index 1 in the new table, but its correct location is now index 8. Rehashing ensures every element is placed in its proper new home according to the new table size.

---

### Performance Implications: Amortized O(1)

A single rehashing operation is **expensive**. You have to touch every single item in the table, so the cost of that one insertion that triggers the rehash is **O(n)**, where `n` is the number of items.

This sounds bad, but it happens very infrequently. Because we double the table size each time, the gap between rehashing events gets wider and wider.

- Rehash at 8 items.
- Next rehash at 16 items.
- Next rehash at 32 items... and so on.

When we average the cost of all insertions over time, the expensive O(n) operations are "spread out" over many cheap O(1) operations. This gives us an **amortized time complexity of O(1)** for insertion. It's a powerful concept that guarantees hash tables remain fast on average, despite these occasional expensive maintenance steps.

### **Extendible Hashing: A Detailed Explanation**

Extendible Hashing is a dynamic hashing technique designed for large, disk-based databases. Its primary goal is to allow a hash table to grow gracefully without the massive performance hit of a full "stop-the-world" rehashing operation.

### **1. Core Components**

Extendible Hashing separates the hash table into two main structures:

- **The Directory:** A small array of pointers that usually fits in memory. It acts as an index or a quick-reference guide.
- **The Buckets (or Pages):** The actual data containers that are stored on disk. Each bucket can hold a fixed number of records.

To manage these structures, we use two crucial integer values:

### **Global Depth (d)**

- **Belongs to:** The entire **Directory**.
- **What it is:** A single number that defines the size of the directory. The directory will always have **2<sup>d</sup>** entries.
- **What it does:** It tells the system how many bits from the beginning of a key's hash to look at to find the correct pointer in the directory.

### **Local Depth (d')**

- **Belongs to:** Each individual **Bucket**.
- **What it is:** A number that specifies how many bits were used to group all the keys currently inside *that specific bucket*.
- **The Golden Rule:** A bucket's local depth `d'` can never be greater than the directory's global depth `d`. (`d' <= d`).

### **2. The Hashing and Lookup Process**

1. A key is converted into a binary hash string (e.g., `101101...`).
2. The system looks at the first **`d`** bits of this hash string, where `d` is the current **Global Depth**.
3. These `d` bits are treated as a number, which corresponds to an index in the Directory (e.g., if `d=3` and the bits are `101`, the index is 5).
4. The system follows the pointer at this directory index to the correct Bucket on disk.
5. The record is then inserted into or searched for within that bucket.

### **3. Handling Overflows: The "Extendible" Logic**

The magic happens when a bucket becomes full. The system checks the bucket's **local depth (`d'`)** against the directory's **global depth (`d`)** to decide what to do.

### **Case 1: Simple Split (when `d' < d`)**

This is the common, "easy" case. It occurs when the directory is already more detailed than the bucket that needs to be split. This means multiple directory entries are already pointing to the same overflowing bucket.

1. **Create a New Bucket:** A new, empty bucket is allocated.
2. **Increment Local Depths:** The local depth `d'` of *both* the old bucket and the new bucket is incremented by 1.
3. **Redistribute Records:** All records from the original, overflowing bucket are re-examined using the new, deeper `d'` number of bits. Based on this extra bit, each record is either kept in the old bucket or moved to the new one.
4. **Update Directory Pointer:** One of the "spare" directory pointers that used to point to the old bucket is updated to point to the new bucket.

**Key takeaway:** The Directory size does **not** change. This is a very fast and localized operation.

### **Case 2: Directory Doubling (when `d' == d`)**

This is the less frequent, "hard" case. It means the directory is not detailed enough to distinguish between the keys in the overflowing bucket. There are no spare pointers to use.

1. **Increase Global Depth:** First, the directory's **Global Depth `d`** is incremented by 1.
2. **Double the Directory:** The directory array doubles in size (from `2^d` to `2^(d+1)`). The new half of the directory is created by mirroring the pointers from the first half.
3. **Perform the Split:** Now that the directory has been expanded, the condition has changed to `d' < d`. The system can now proceed with the **Simple Split** logic described in Case 1. It creates a new bucket, increments the local depths of the two split buckets, redistributes the records, and updates the newly available directory pointer.

**Key takeaway:** Even in this more expensive case, we only redistribute the records from the *one* overflowing bucket. We never touch the entire dataset.

### **4. A Detailed Step-by-Step Example**

Let's build a table from scratch.

- **Bucket Size:** Can hold 2 records.
- **Hash Function:** Provides a binary string for each key.

### **Initial State**

- **Global Depth (d) = 1**. Directory has `2^1 = 2` entries ('0', '1').
- We have two **Buckets (A, B)**, each with **Local Depth (d') = 1**.

| **Directory (d=1)** | **Buckets** |
| --- | --- |
| `0` -> | **Bucket A** [ ] (d'=1) |
| `1` -> | **Bucket B** [ ] (d'=1) |

### **Step 1: Causing an Overflow (The Hard Case)**

Let's insert three keys whose hashes all start with `0`:

- Insert `K1` (hash `0101...`) -> Goes to Bucket A.
- Insert `K2` (hash `0011...`) -> Goes to Bucket A. Bucket A is now full.
- Insert `K3` (hash `0110...`) -> Tries to go to Bucket A, causing an **overflow**.

**Decision:** Check the overflowing bucket (A). Is `d' == d`? Yes, `1 == 1`. We must double the directory.

**Action:**

1. **Global Depth `d` becomes 2**.
2. **Directory doubles** to `2^2 = 4` entries ('00', '01', '10', '11'). Pointers are mirrored.
3. **Split Bucket A:**
    - Create a new **Bucket C**.
    - The local depth `d'` of Bucket A and Bucket C becomes **2**.
    - Redistribute `K1`, `K2`, `K3` using their first **2** hash bits:
        - `K1` (hash `01...`) -> Moves to new Bucket C.
        - `K2` (hash `00...`) -> Stays in Bucket A.
        - `K3` (hash `01...`) -> Moves to new Bucket C.
    - Update the directory pointer for `01` to point to the new Bucket C.

**State after Directory Doubling:**

| **Directory (d=2)** | **Buckets** |
| --- | --- |
| `00` -> | **Bucket A** [`K2`] (d'=2) |
| `01` -> | **Bucket C** [`K1`, `K3`] (d'=2) |
| `10` -> | **Bucket B** [ ] (d'=1) |
| `11` -> |  |

*Notice that two pointers now point to Bucket B, whose local depth is still 1.*

### **Step 2: Causing an Overflow (The Easy Case)**

Now let's insert three keys whose hashes start with `1`:

- Insert `K4` (hash `1010...`) -> Goes to Bucket B.
- Insert `K5` (hash `1100...`) -> Goes to Bucket B. Bucket B is now full.
- Insert `K6` (hash `1001...`) -> Tries to go to Bucket B, causing an **overflow**.

**Decision:** Check the overflowing bucket (B). Is `d' == d`? No, `1 < 2`. We do a simple split.

**Action:**

1. **Create a new Bucket D**.
2. The local depth `d'` of Bucket B and Bucket D becomes **2**.
3. Redistribute `K4`, `K5`, `K6` using their first **2** hash bits:
    - `K4` (hash `10...`) -> Stays in Bucket B.
    - `K5` (hash `11...`) -> Moves to new Bucket D.
    - `K6` (hash `10...`) -> Stays in Bucket B.
4. Update the directory pointer for `11` to point to the new Bucket D.

**Final State:**

| **Directory (d=2)** | **Buckets** |
| --- | --- |
| `00` -> | **Bucket A** [`K2`] (d'=2) |
| `01` -> | **Bucket C** [`K1`, `K3`] (d'=2) |
| `10` -> | **Bucket B** [`K4`, `K6`] (d'=2) |
| `11` -> | **Bucket D** [`K5`] (d'=2) |

### **5. Advantages and Disadvantages**

- **Advantages:**
    - **Graceful Growth:** Avoids massive, full rehashing operations.
    - **Efficient Lookups:** Performance remains stable, typically requiring only two disk reads (one for the directory, one for the bucket).
- **Disadvantages:**
    - **Complexity:** Significantly harder to implement than standard hashing.
    - **Directory Overhead:** The directory adds a layer of indirection and can become large if the data is poorly distributed.
    - **Data Skew Sensitivity:** A non-uniform hash function can lead to frequent directory doublings even if the table is mostly empty.

note : above section did use MSB most significant bits (prefix) from the binary string for the purpose of indexing, below section is GFG guide for extendible hashing with example that uses the suffix binary string.

# Extendible Hashing (Dynamic approach to DBMS)

**Extendible Hashing** is a dynamic hashing method wherein directories, and buckets are used to hash data. It is an aggressively flexible method in which the hash function also experiences dynamic changes.

**Main features of Extendible Hashing:** The main features in this hashing technique are:

- **Directories:** The directories store addresses of the buckets in pointers. An id is assigned to each directory which may change each time when Directory Expansion takes place.
- **Buckets:** The buckets are used to hash the actual data.

**Basic Structure of Extendible Hashing:**

![](https://media.geeksforgeeks.org/wp-content/uploads/20190806160015/Basic-Structure-of-Extendible-Hashing.png)

**Frequently used terms in Extendible Hashing:**

- **Directories:** These containers store pointers to buckets. Each directory is given a unique id which may change each time when expansion takes place. The hash function returns this directory id which is used to navigate to the appropriate bucket. Number of Directories = 2^Global Depth.
- **Buckets:** They store the hashed keys. Directories point to buckets. A bucket may contain more than one pointers to it if its local depth is less than the global depth.
- **Global Depth:** It is associated with the Directories. They denote the number of bits which are used by the hash function to categorize the keys. Global Depth = Number of bits in directory id.
- **Local Depth:** It is the same as that of Global Depth except for the fact that Local Depth is associated with the buckets and not the directories. Local depth in accordance with the global depth is used to decide the action that to be performed in case an overflow occurs. Local Depth is always less than or equal to the Global Depth.
- **Bucket Splitting:** When the number of elements in a bucket exceeds a particular size, then the bucket is split into two parts.
- **Directory Expansion:** Directory Expansion Takes place when a bucket overflows. Directory Expansion is performed when the local depth of the overflowing bucket is equal to the global depth.

**Basic Working of Extendible Hashing:**

![](https://media.geeksforgeeks.org/wp-content/uploads/20190806160342/Basic-Working-of-Extendible-Hashing.png)

- **Step 1 - Analyze Data Elements:** Data elements may exist in various forms eg. Integer, String, Float, etc.. Currently, let us consider data elements of type integer. eg: 49.
- **Step 2 - Convert into binary format:** Convert the data element in Binary form. For string elements, consider the ASCII equivalent integer of the starting character and then convert the integer into binary form. Since we have 49 as our data element, its binary form is 110001.
- **Step 3 - Check Global Depth of the directory.** Suppose the global depth of the Hash-directory is 3.
- **Step 4 - Identify the Directory:** Consider the 'Global-Depth' number of LSBs in the binary number and match it to the directory id. Eg. The binary obtained is: 110001 and the global-depth is 3. So, the hash function will return 3 LSBs of 110**001** viz. 001.
- **Step 5 - Navigation:** Now, navigate to the bucket pointed by the directory with directory-id 001.
- **Step 6 - Insertion and Overflow Check:** Insert the element and check if the bucket overflows. If an overflow is encountered, go to **step 7** followed by **Step 8**, otherwise, go to **step 9**.
- **Step 7 - Tackling Over Flow Condition during Data Insertion:** Many times, while inserting data in the buckets, it might happen that the Bucket overflows. In such cases, we need to follow an appropriate procedure to avoid mishandling of data. First, Check if the local depth is less than or equal to the global depth. Then choose one of the cases below.
    - **Case1:** If the local depth of the overflowing Bucket is equal to the global depth, then Directory Expansion, as well as Bucket Split, needs to be performed. Then increment the global depth and the local depth value by 1. And, assign appropriate pointers. Directory expansion will double the number of directories present in the hash structure.
    - **Case2:** In case the local depth is less than the global depth, then only Bucket Split takes place. Then increment only the local depth value by 1. And, assign appropriate pointers.

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803103752/OverFlow3.png)

- **Step 8 - Rehashing of Split Bucket Elements:** The Elements present in the overflowing bucket that is split are rehashed w.r.t the new global depth of the directory.
- **Step 9 -** The element is successfully hashed.

**Example based on Extendible Hashing:** Now, let us consider a prominent example of hashing the following elements: **16,4,6,22,24,10,31,7,9,20,26.**

**Bucket Size:** 3 (Assume)

**Hash Function:** Suppose the global depth is X. Then the Hash Function returns X LSBs.

- **Solution:** First, calculate the binary forms of each of the given numbers. 16- 10000 4- 00100 6- 00110 22- 10110 24- 11000 10- 01010 31- 11111 7- 00111 9- 01001 20- 10100 26- 11010
- Initially, the global-depth and local-depth is always 1. Thus, the hashing frame looks like this:

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803103835/hash11.png)

- **Inserting 16:** The binary format of 16 is 10000 and global-depth is 1. The hash function returns 1 LSB of 1000**0** which is 0. Hence, 16 is mapped to the directory with id=0.

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803221035/hash23.png)

- **Inserting 4 and 6:** Both 4(10**0**) and 6(11**0**)have 0 in their LSB. Hence, they are hashed as follows:

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803221037/hash32.png)

- **Inserting 22:** The binary form of 22 is 1011**0**. Its LSB is 0. The bucket pointed by directory 0 is already full. Hence, Over Flow occurs.

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803221039/hash42.png)

- As directed by **Step 7-Case 1**, Since Local Depth = Global Depth, the bucket splits and directory expansion takes place. Also, rehashing of numbers present in the overflowing bucket takes place after the split. And, since the global depth is incremented by 1, now,the global depth is 2. Hence, 16,4,6,22 are now rehashed w.r.t 2 LSBs.[ 16(100**00**),4(1**00**),6(1**10**),22(101**10**) ]

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803221040/hash52.png)

-

> *Notice that the bucket which was underflow has remained untouched. But, since the number of directories has doubled, we now have 2 directories 01 and 11 pointing to the same bucket. This is because the local-depth of the bucket has remained 1. And, any bucket having a local depth less than the global depth is pointed-to by more than one directories.
>
- **Inserting 24 and 10:** 24(110**00**) and 10 (10**10**) can be hashed based on directories with id 00 and 10. Here, we encounter no overflow condition.

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803221042/hash62.png)

- **Inserting 31,7,9:** All of these elements[ 31(111**11**), 7(1**11**), 9(10**01**) ] have either 01 or 11 in their LSBs. Hence, they are mapped on the bucket pointed out by 01 and 11. We do not encounter any overflow condition here.

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803222615/hash73.png)

- **Inserting 20:** Insertion of data element 20 (101**00**) will again cause the overflow problem.

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803221043/hash7.12.png)

- 20 is inserted in bucket pointed out by 00. As directed by **Step 7-Case 1**, since the **local depth of the bucket = global-depth**, directory expansion (doubling) takes place along with bucket splitting. Elements present in overflowing bucket are rehashed with the new global depth. Now, the new Hash table looks like this:

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803104120/hash81.png)

- **Inserting 26:** Global depth is 3. Hence, 3 LSBs of 26(11**010**) are considered. Therefore 26 best fits in the bucket pointed out by directory 010.

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803222301/hash93.png)

- The bucket overflows, and, as directed by **Step 7-Case 2,** since the **local depth of bucket < Global depth (2<3)**, directories are not doubled but, only the bucket is split and elements are rehashed. Finally, the output of hashing the given list of numbers is obtained.

![](https://media.geeksforgeeks.org/wp-content/uploads/20190803104123/hash101.png)

- **Hashing of 11 Numbers is Thus Completed.**

**Key Observations:**

1. A Bucket will have more than one pointers pointing to it if its local depth is less than the global depth.
2. When overflow condition occurs in a bucket, all the entries in the bucket are rehashed with a new local depth.
3. If Local Depth of the overflowing bucket
4. The size of a bucket cannot be changed after the data insertion process begins.