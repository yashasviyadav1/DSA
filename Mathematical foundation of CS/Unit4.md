# Unit-4

![](https://i.ibb.co/CCGMRw5/image.png)

[topic wise gemini](https://gemini.google.com/app/1f08b8b9f0ed4aa4) 

[deep dive gemini](https://gemini.google.com/app/487440a5222567fc) 

[deep dive in smaller parts - GPT](https://chatgpt.com/c/69199fe8-7808-8321-b2eb-2299235d8a5f)

[deep dive in smaller parts - claude](https://claude.ai/chat/50450ace-ec71-482c-b277-0bcc1f394226)

- **Graph Theory:**
    - **Isomorphism** (Determining if two graphs are structurally the same).
    - **Planar graphs** (Drawing graphs without edges crossing).
    - **Graph coloring** (The famous map coloring problems).
    - **Hamilton circuits & Euler cycles** (Pathfinding problems).
- **Combinatorics (Counting):**
    - **Permutations and Combinations** (Basic counting rules).
    - **With and Without Repetition** (The tricky variations).
    - **Specialized Techniques** for combinatorial enumeration.

**What is a Graph? (The Basics)**

Before diving into the complex stuff, just remember:
• A **Graph ($G$)** consists of **Vertices ($V$)** (points/nodes) and **Edges ($E$)** (lines connecting them).
• That's it. It’s a way to model connections (like friends on Facebook or cities on a map).

**Graph Isomorphism (Are they twins?)**

The word "Isomorphism" comes from Greek: *isos* (equal) + *morphe* (shape).
The Concept: Two graphs might look completely different on paper (one is drawn as a square, the other as a twisted star), but if they have the exact same connectivity structure, they are Isomorphic.

> Formal Definition: Two graphs $G_1$ and $G_2$ are isomorphic if there is a one-to-one mapping (bijection) between their vertices such that:"If vertex A is connected to vertex B in $G_1$, then the 'partner' of A must be connected to the 'partner' of B in $G_2$."
> 

example:

```sql
  A
 / \.     G1
B---C

   X
  / \       G2
 Y---Z

A and X are called partneres in G1 and G2
similarly 
B and Y
C and Z
```

If any of these don't match, they are NOT isomorphic:
1. Same number of Vertices?
2. Same number of Edges?
3. Same "Degree Sequence"? (e.g., if Graph A has two vertices with 3 connections, Graph B must also have exactly two vertices with 3 connections).

4. Cycles**:** If Graph A has a "triangle" (a cycle of length 3), Graph B must also have a triangle.

**Example** Let's look at two graphs that **are** isomorphic or not.
• **Graph 1 (The Square):** Vertices $\{1, 2, 3, 4\}$ connected in a cycle $1-2-3-4-1$.
• **Graph 2 (The Bowtie):** It looks like an hourglass shape. Vertices $\{A, B, C, D\}$.
    ◦ $A$ connected to $B$.
    ◦ $B$ connected to $C$.
    ◦ $C$ connected to $D$.
    ◦ $D$ connected to $A$.
    ◦ (But drawn with the lines $A-D$ and $B-C$ crossing in the middle). But there is no vertex in the middle where diagonal meet

**Solution:** 

Graph 1 (The Square):

```sql
1 --- 2
|     |
|     |
4 --- 3
```

Edges: 1-2, 2-3, 3-4, 4-1

**Graph 2** (The Bowtie/Hourglass):

```sql
A ─── B
 \   /
  \ /
   X  (crossing point - not a vertex!)
  / \
 /   \
D ─── C
```

Edges: A-B, B-C, C-D, D-A

Step 1: Check Basic Properties

| Property | Graph 1 | Graph 2 |
| --- | --- | --- |
| Number of vertices | 4 | 4 |
| Number of edges | 4 | 4 |
| Degree of each vertex | 2 | 2 |

Step 2: Try to Find a Mapping

Let's try to map vertices from Graph 1 to Graph 2:

**Attempt 1:**

`1 → A
2 → B
3 → C
4 → D`

**Check connections:**

- In G1: 1 connects to 2 ✅ → In G2: A connects to B ✅
- In G1: 2 connects to 3 ✅ → In G2: B connects to C ✅
- In G1: 3 connects to 4 ✅ → In G2: C connects to D ✅
- In G1: 4 connects to 1 ✅ → In G2: D connects to A ✅

Both are **4-cycles** (a cycle with 4 vertices). The "bowtie" shape is just a different way of drawing the same graph.

*yes, so they are **isomorphic**.*

> important note: The crossing point in the bowtie drawing is **NOT a vertex** - it's just where the edges cross when drawn on paper
> 

**Example 2**
Consider these two graphs with 6 vertices and 5 edges:
1. **Graph X:** A straight line of 6 vertices ($1-2-3-4-5-6$).
2. **Graph Y:** A "star" shape (one center vertex connected to 5 others).
**Check the invariants:**
• Vertices: Both have 6. (Pass)
• Edges: Both have 5. (Pass)
• **Degree Sequence:**
    ◦ Graph X (Line): Degrees are `1, 2, 2, 2, 2, 1`. (Endpoints have 1 neighbor, middle ones have 2).
    ◦ Graph Y (Star): Degrees are `1, 1, 1, 1, 1, 5`. (Center has 5 neighbors!).
**Conclusion:** Since the degrees don't match (Graph Y has a degree-5 vertex, Graph X doesn't), they are **NOT** isomorphic.

next topic: Planar Graph in depth right now we only did basic part

---

### **Planar Graph**

A graph is **Planar** if you can draw it on a piece of paper such that ***no two edges cross each other***

A triangle or a square. You can draw them without crossing lines.

**Euler's Formula for Planar Graphs** :If a connected graph is planar, then:

> $V - E + R = 2$
> 
- **V:** Number of Vertices
- **E:** Number of Edges
- **R (or F):** Number of Regions (Faces) enclosed by the edges (plus the infinite "outside" region).

example of Planar Graph: $K_4$

![](https://i.ibb.co/7t77kKsx/image.png)

proving Euler’s formula for Planar Graph

Edges = 6, Vertices = 4, Regions = 4 (including outer region also)

V - E + R = 2 (Formula)

4 - 6 + 4 = 2

2 = 2 (Hence Proved)

### **Non-Planar Graphs**

There are exactly **two basic non-planar graphs** (Kuratowski’s Theorem):

1. Complete graph with 5 vertices: **$K_5$**
    
    Every vertex connected to every other.
    
    Try drawing this — impossible without crossing. No matter how you redraw it → edges cross.
    
    ```
      1----2
      |\  /|
      | \/ |
      | /\ |
      |/  \|
      3----4
       \  /
         5
    ```
    
2. Complete bipartite graph K₃,₃
    
    Two sets of 3 vertices, every left connects to every right.
    
    ```
    A1   B1
    A2   B2
    A3   B3
    ```
    

**Kuratowski's Theorem:** A graph is non-planar if and only if it "contains" a $K_5$ or a $K_{3,3}$ hidden inside it (as a subgraph or subdivision).

### **Graph Coloring (The Map Problem)**

The Concept:This deals with assigning a "color" to every vertex so that no two connected vertices have the same color.
Key Term: Chromatic Number ($\chi(G)$)
This is the minimum number of colors needed to color the graph.
• **Example:** A Triangle needs **3 colors** (since all 3 corners touch each other).
• **Example:** A Square needs only **2 colors** (Top-Left is Red, Top-Right is Blue, Bottom-Right is Red, Bottom-Left is Blue).
Application:
This is used in Compilers (Register Allocation) and Scheduling (if two classes share students, they are "connected" and cannot be scheduled at the same "color"/time slot).

**The Four Color Theorem**

This is the most famous theorem in this field. It applies specifically to **Planar Graphs** (maps).

> Theorem: Any planar graph (any map you can draw on a piece of paper) requires at most 4 colors such that no two sharing borders have the same color.
> 

### **Traversals:**

**Traversals** This is one of the most famous topics in computer science history because it highlights the difference between a problem that is "easy" to solve and one that is "impossible" (or NP-hard) to solve efficiently.

We are looking at two types of paths that cover the entire graph. **Euler Cycles** and **Hamilton Circuits**

| Feature | Euler Cycle | Hamilton Circuit |
| --- | --- | --- |
| **Goal** | Visit every **EDGE** exactly once | Visit every **VERTEX** exactly once |
| **Return to start?** | Yes | Yes |
| **Easy to check?** | Yes (just check degrees) | No (have to try many paths) |

### **1. Euler Cycles (The Edge Problem)**

example of euler cycle:

- Mail delivery: Walk every street exactly once
- Drawing puzzles: "Draw this shape without lifting your pen"

**The Story: Bridges of Königsberg (1736)**

![](https://i.ibb.co/mV5bPnQB/image.png)

The city of Königsberg had 

- 7 bridges connecting 4 land areas
- each land has a odd degree (degree = no of edges/bridges connected to that land)

**The question:** Can you walk through the city, crossing each bridge **exactly once**, and return to where you started?

**Euler proved:** NO, it's impossible! And he explained exactly why.

The 4 land areas had degrees: 3, 3, 3, 5 (all odd!)

Since no vertex has even degree, **it's impossible** to walk all bridges exactly once and return.

The Rule: Even Degrees

**A graph has an Euler Cycle if and only if:**

1. The graph is connected (you can reach any vertex from any other)
2. Every vertex has an EVEN degree

**Why Must Degrees Be Even?**

Think about walking through a vertex:

**Every time you ENTER a vertex, you must LEAVE it.**

- Enter through edge 1 → Leave through edge 2 (used 2 edges)
- Enter through edge 3 → Leave through edge 4 (used 2 more edges)
- ...

Edges are always used in **pairs** at each vertex (one in, one out).

If a vertex has ODD degree (say, 3 edges):

- Enter through edge 1
- Leave through edge 2
- Enter through edge 3
- **Now you're STUCK!** No edge left to leave!

**If a vertex has EVEN degree (say, 4 edges):**

- Enter through edge 1
- Leave through edge 2
- Enter through edge 3
- Leave through edge 4
- **Perfect!** You can always escape.

**Example 1: Has Euler Cycle ? YES**

```sql
    A---B
    |   |
    D---C
```

Check degrees:

- A: connected to B and D → degree = 2  (even)
- B: connected to A and C → degree = 2  (even)
- C: connected to B and D → degree = 2  (even)
- D: connected to A and C → degree = 2  (even)

All even! Euler Cycle exists!

**One possible path:** A → B → C → D → A (visited all 4 edges exactly once, returned to start)

**Example 2:** No Euler Cycle 

```sql
    A---B
    |\ /|
    | X |
    |/ \|
    D---C
```

Edges: A-B, A-C, A-D, B-C, B-D, D-C

**Check degrees:**

- A: connected to B, C, D → degree = 3  (odd!)
- B: connected to A, C, D → degree = 3  (odd!)
- C: connected to A, B, D → degree = 3  (odd!)
- D: connected to A, B, C → degree = 3  (odd!)

All odd! No Euler Cycle possible!

---

### 2. Hamilton Circuits (The Vertex Problem)

The Goal: Visit every VERTEX exactly once and return to start. (You don't need to use every edge, just visit every vertex and return to start)

Real Life examples:

- **Traveling Salesman Problem:** Visit every city exactly once
- **Delivery routes:** Visit every customer exactly once

**Example 1: Has Hamilton Circuit ? YES**

```sql
    A---B
    |   |
    D---C
```

Find a path that visits each vertex once and returns:

A → B → C → D → A 

Visited**:** A, B, C, D (all vertices exactly once), returned to A.

**Example 2: Has Hamilton Circuit ? YES**

```sql
    A---B---C
    |       |
    F---E---D
```

**Path:** A → B → C → D → E → F → A 

All 6 vertices visited exactly once, returned to start.

**Example 3: has Hamilton Circuit ? YES**

```sql
      A
     /|\
    B-C-D
```

Vertices: A, B, C, D
Edges: A-B, A-C, A-D, B-C, C-D

Try to find a Hamilton Circuit:

A → B → C → D → A

All 4 vertex visited and returned to start

**Example 4: has Hamilton Circuit ? NO**

```sql
    A---B---C---D---E
```

A straight line of 5 vertices.

- Start at A → B → C → D → E
- Now need to return to A
- But E only connects to D (already visited!)
- Stuck! No Hamilton Circuit!

**The BIG Difference: Difficulty**

**Euler Cycle: EASY** 

```sql
Algorithm:
1. Check if graph is connected
2. Count degree of each vertex
3. If ALL degrees are even → Euler Cycle exists!

Time: Very fast (polynomial time)
```

You don't even need to find the path - just count degrees!

**Hamilton Circuit: HARD** 

```sql
Algorithm:
1. Try path starting from vertex 1...
2. Try another path...
3. Try another path...
4. Keep trying until you find one or exhaust all possibilities

Time: Extremely slow (exponential time)
```

No simple rule exists! You basically have to try many possible paths.

---

### Combinatorics (Counting)

**Permutations** and **Combinations**. 

The difference between them comes down to a single question: **Does the order matter?**

**1. Permutations ($P$) — "Order Matters"**

A permutation is an **arrangement** of items in a specific order.

**Keywords:** Arrange, Order, Rank, Schedule, Sequence.

**The Logic:** "AB" is different from "BA". (Like a password: `1234` is different from `4321`).

Formula (Without Repetition):

Number of ways to arrange $r$ items from a set of $n$:

> $P(n, r) = \frac{n!}{(n-r)!}$
> 

Example: You have 5 students ($n=5$) and 3 chairs ($r=3$). How many ways can they sit?

Student A, B, C is different from C, B, A.

$P(5, 3) = \frac{5!}{2!} = 5 \times 4 \times 3 = 60$ ways.

****

**2. Combinations ($C$) — "Order Doesn't Matter"**

A combination is a **selection** of items where order is irrelevant.

**Keywords:** Select, Choose, Pick, Group, Team.

**The Logic:** "AB" is the same as "BA". (Like a fruit salad: "Apple & Banana" is the same as "Banana & Apple").

Formula (Without Repetition):

Number of ways to choose $r$ items from a set of $n$:

> $C(n, r) = \binom{n}{r} = \frac{n!}{r!(n-r)!}$
> 

Example: You have 5 students ($n=5$) and you need to pick a team of 3 ($r=3$).
• Team {A, B, C} is the exact same team as {C, B, A}.
• $C(5, 3) = \frac{5!}{3!2!} = \frac{60}{6} = 10$ ways.

****

**3. Handling Repetition**

**A. Permutations WITH Repetition**

Scenario A:

You are arranging items, but you can reuse them.
• **Formula:** 

> $n^r$
> 
- n is here the distinct things from which we can choose eg. (0,1 bit)
- r is the no of places we need to place them on (eg. 8 bit string length)

**Example:** A byte has 8 bits. Each bit can be 0 or 1 ($n=2$).
• Total arrangements: $2^8 = 256$.

Scenario B**: The "MISSISSIPPI" Rule** (Indistinguishable Objects)

You have a set of items, but some are identical (indistinguishable). How many unique ways can

you arrange them?

**Formula:** 

> $\frac{n!}{n_1! \cdot n_2! \cdot ...}$
> 

**Example:** Arrange the letters in APPLE.

Total letters $n=5$.

P repeats 2 times.

$\frac{5!}{2!} = \frac{120}{2} = 60$.

****

**B. Combinations WITH Repetition (The Hard One)**

You are selecting items, but you can pick the same type multiple times. (Often called "Stars and Bars").

> **Formula:** $C(n + r - 1, r)$
> 

**Example:** You are at an ice cream shop with 5 flavors ($n=5$). You want 3 scoops ($r=3$). You can pick {Chocolate, Chocolate, Vanilla}.
• Calculation: $C(5+3-1, 3) = C(7, 3)$.

**Combinatorics Practice Problems**

***Problem 1***: You have 6 books and want to arrange 4 of them on a shelf. How many different arrangements are possible?

**Type:** Permutation without repetition

*solution : arrange → order matters → permutation* 

 **$P(6,4) = \frac{6!}{(6-4)!} = \frac{6!}{2!} = 6 \times 5 \times 4 \times 3 = 360$

***Problem 2***: 

A pizza shop offers 8 toppings. You can choose 3 toppings for your pizza. How many different pizzas can you make?

**Type:** order of toppings does’t matter and we can’t repeat a toping → Combination without repetition

Solution: $C(8,3) = \frac{8!}{3! \times 5!} = \frac{8 \times 7 \times 6}{3 \times 2 \times 1} = 56$

***Problem 3***: Permutation with Repetition

A 4-digit PIN code uses digits 0-9. Each digit can be repeated. How many different PIN codes are possible?

**Type:** Permutation with repetition

Solution: 

$10^4 = 10,000$

***Problem 4:*** Seating Arrangement

7 friends go to a movie theater. They find a row with exactly 7 seats. How many ways can they sit in the row?

**Type:** Permutation without repetition

Solution: $7! = 5,040$

***Problem 5***: Committee Selection

A class has 12 students. The teacher needs to select a committee of 5 students. How many different committees are possible?

**Type:** Combination without repetition

Solution: $C(12,5) = \frac{12!}{5! \times 7!} = \frac{12 \times 11 \times 10 \times 9 \times 8}{5 \times 4 \times 3 \times 2 \times 1} = 792$

***Problem 6:*** Password Creation

A password must be exactly 3 characters long. Each character can be any lowercase letter (a-z, 26 letters). Repetition is allowed. How many passwords are possible?

**Type:** Permutation with repetition

Solution: $26^3 = 17,576$

***Problem 7:*** Combination with Repetition (Stars and Bars)

A candy store has 4 types of candy. You want to buy 6 pieces total (you can buy multiple of the same type). How many different selections are possible?

**Type:** Combination with repetition

Solution: $C(n+r-1, r) = C(4+6-1, 6) = C(9,6) = \frac{9!}{6! \times 3!} = 84$

***Problem 8:*** Mixed Problem

A club has 10 members. They need to elect a President, Vice-President, and Secretary. How many ways can they do this?

**Hint:** Think about whether order matters here!

Solution: **Order matters!** (President ≠ Vice-President)
$P(10,3) = 10 \times 9 \times 8 = 720$

***Problem 9:*** Combination with Repetition

You're distributing 5 identical balls into 3 different boxes. How many ways can you do this?

**Hint:** This is "Stars and Bars"

Solution: Using Stars and Bars: n = 3 boxes, r = 5 balls
$C(n+r-1, r) = C(3+5-1, 5) = C(7,5) = 21$

***Problem 10:*** Multi-Part Problem

A bag contains 5 red balls, 4 blue balls, and 3 green balls (12 balls total, all distinguishable).

**(a)** How many ways can you select 4 balls from the bag?

**(b)** How many ways can you arrange 4 balls from the bag in a row?

Solution:

**(a)** Selection (order doesn't matter):
$C(12,4) = \frac{12!}{4! \times 8!} = 495$

**(b)** Arrangement (order matters):
$P(12,4) = 12 \times 11 \times 10 \times 9 = 11,880$

---

Summary:

| **Type** | **Order Matters?** | **Repetition Allowed?** | **Formula** |
| --- | --- | --- | --- |
| **Permutation** | Yes | No | $\frac{n!}{(n-r)!}$ |
| **Combination** | No | No | $\frac{n!}{r!(n-r)!}$ |
| **Permutation** | Yes | Yes | $n^r$ |
| **Combination** | No | Yes | $\binom{n+r-1}{r}$ |

---

### Specialized Techniques

**1. The Pigeonhole Principle (PHP)**

This is a technique for proving **existence**. It doesn't give you a number (enumeration), but it proves that a certain configuration *must* exist.
• **The Concept:** If you have $n$ pigeonholes and $n+1$ pigeons, at least one pigeonhole must contain **more than one** pigeon.
• **M.Tech Application (Hashing):**
    ◦ If you have a Hash Table with 100 slots (buckets) and you try to store 101 keys, the Pigeonhole Principle guarantees a **collision** (two keys hashing to the same slot). You don't need to check the keys; the math proves the collision is unavoidable.
• **Generalized Version:** If $N$ objects are placed into $k$ boxes, then there is at least one box containing at least $\lceil N/k \rceil$ objects.

**2. The Principle of Inclusion-Exclusion (PIE)**

This technique is used to solve combinatorial problems where sets **overlap**. Simple addition counts the overlaps twice; PIE corrects this.
• The Formula (for 3 sets):
$|A \cup B \cup C| = |A| + |B| + |C| - (|A \cap B| + |A \cap C| + |B \cap C|) + |A \cap B \cap C|$
• **The Logic:** Add the singles, subtract the doubles (to remove double-counting), add the triples (because you subtracted them too many times).
• **CS Application:**
    ◦ **Database Query Optimization:** Estimating the number of records that satisfy "Condition A OR Condition B OR Condition C".
    ◦ **Derangements:** Counting how many ways you can arrange a list so that *no* item stays in its original spot (e.g., shuffling a list where index `i` never contains value `i`).

**3. Generating Functions**

This is the most "specialized" and powerful technique in the unit. It transforms a counting problem into an **algebraic problem**.
• **The Concept:** Instead of counting sequences directly, we represent them as coefficients of a polynomial (or power series).
    ◦ To find the number of ways to select items with complex constraints (e.g., "pick between 2 and 5 apples, and an odd number of oranges"), you simply **multiply polynomials**.
• **Why it's "Specialized":** It solves problems that are impossible with standard $nCr$ formulas, specifically **Partitions of Integers** (e.g., "How many ways can 100 be written as a sum of 1s, 2s, and 3s?").

**4. Recurrence Relations**

This technique counts things by finding a pattern or relationship between the "current" term and "previous" terms.
• **The Concept:** You define the count for size $n$ ($a_n$) based on the count for size $n-1$.
• **CS Application:**
    ◦ **Algorithm Complexity:** The Master Theorem ($T(n) = 2T(n/2) + n$) is a recurrence relation used to count operations in Merge Sort.
    ◦ **Dynamic Programming:** The entire field of DP is based on solving recurrence relations (e.g., Fibonacci, Tower of Hanoi).

---
END