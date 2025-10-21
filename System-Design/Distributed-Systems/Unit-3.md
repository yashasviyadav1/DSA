## Unit 3: Query Processing

## Query Processing in Distributed Databases

**1. OBJECTIVES OF QUERY PROCESSING**

Query processing = converting a **high-level SQL query** (like `SELECT * FROM EMPLOYEE WHERE SALARY > 50000`)

into an **efficient execution strategy** that can be run **across multiple distributed sites**.

### **1.1 Goals of Distributed Query Processing**

Let’s unpack the **three major goals** with **M.Tech-level clarity and examples**

**1️⃣ Minimize Response Time**

- Definition:
    
    Time between user submitting query → and receiving result.
    
- Includes:
    - Local computation time
    - Data transfer time (network)
    - Result assembly time
- Why important?
    
    Critical for *interactive systems* (e.g., OLTP, dashboards).
    
- Example:
    
    Suppose a query joins tables `EMPLOYEE` (in Delhi) and `DEPARTMENT` (in Mumbai).
    
    Sending the full EMPLOYEE table (10 GB) to Mumbai is slow.
    
    Instead, you may **send only relevant tuples** or perform **semi-joins** to minimize transmission time.
    

**2️⃣ Minimize Total Cost**

- Definition:
    
    Total system resources consumed by the query.
    
    (Important for *batch or analytical workloads* where many queries run together.)
    
- Formula:Total Cost=CPU Cost+I/O Cost+Communication Cost+Storage Cost
    
    Total Cost=CPU Cost+I/O Cost+Communication Cost+Storage Cost\text{Total Cost} = \text{CPU Cost} + \text{I/O Cost} + \text{Communication Cost} + \text{Storage Cost}
    
- Example:
    
    Two execution plans might give same result, but:
    
    - Plan A uses more CPU
    - Plan B transmits less data
        
        Optimizer chooses the one with lower total cost.
        

**3️⃣ Maximize Throughput**

- **Definition:**
    
    Number of queries executed per unit time.
    
- Focus:
    
    Efficient load balancing and resource scheduling across all sites.
    
- Example:
    
    Distribute heavy queries among multiple servers → avoids overloading one site → system serves more users simultaneously.
    

Cost Components in Distributed Systems

| Cost Type | Description | Example |
| --- | --- | --- |
| **CPU Cost** | Computations at each site | Joins, projections, selections |
| **I/O Cost** | Disk operations (read/write) | Reading 1 million tuples |
| **Communication Cost** | Data transfer between nodes | Sending 10 MB join data from Site A → Site B |
| **Storage Cost** | Temporary or intermediate data | Materialized join result on disk |

> Note: Communication cost is usually dominant in distributed environments.
> 
> 
> Because: network I/O (milliseconds) ≫ disk I/O (microseconds).
> 

**Example: Comparing Two Plans**

Let’s say query:

```sql
SELECT *
FROM EMPLOYEE E, DEPARTMENT D
WHERE E.dept_id = D.dept_id AND D.city = 'Delhi';
```

- **Plan 1:** Send DEPARTMENT (Delhi) subset from Mumbai → Delhi and join locally.
- **Plan 2:** Send EMPLOYEE data (10 GB) from Delhi → Mumbai and join there.

**Optimizer chooses Plan 1** because **communication cost** (sending small department subset) is much smaller.

### 1.2 Differences from Centralized Query Processing

| Aspect | Centralized | Distributed |
| --- | --- | --- |
| **Cost Model** | CPU + I/O | CPU + I/O + Communication |
| **Data Location** | One site | Multiple sites |
| **Parallelism** | Limited (within one site) | Inter-site + intra-site |
| **Optimization** | Local | Global + local |
| **Complexity** | Simple | High (site selection, data transfer, fragmentation) |
| **Network Involvement** | None | Key factor |

**Takeaway:**

Distributed query optimization = **multi-objective problem** (minimize response time & total cost while balancing load).

### 2. CHARACTERIZATION OF QUERY PROCESSORS

Query processing pipeline is same conceptually as centralized systems — but each stage must handle **distribution awareness** (data at multiple sites, network delays, etc.).

### **2.1 Query Processor Architecture**

The stages are:

```
SQL Query
   ↓
1️⃣ PARSER
   ↓
2️⃣ QUERY OPTIMIZER
   ↓
3️⃣ CODE GENERATOR
   ↓
4️⃣ RUNTIME PROCESSOR
   ↓
RESULT
```

**1️⃣ Parser**

Goal:

Convert SQL into an internal representation — a query tree or query graph.

Responsibilities:

- Syntax & semantic checking
- Expand views into base tables
- Generate initial logical query tree

Example:

```sql
SELECT name
FROM EMPLOYEE
WHERE salary > 50000;

becomes a **tree:**

 σ(salary>50000)
        |
     EMPLOYEE
```

**Distributed Role:**

Parser also checks **where data fragments are stored** and annotates nodes with **site info**.

**2️⃣ Query Optimizer**

Goal:

Find best execution plan (ordering of operations, data shipping strategy) to minimize total cost.

Key Tasks:

1. Logical Optimization
    - Transform query using algebraic laws (e.g., push selections, combine projections)
2. Site Selection
    - Decide where to execute each operation
3. Data Transfer Minimization
    - Choose whether to move data or move computation (ship whole table vs ship partial results)
4. Join Order Optimization
    - Decide which joins first → least cost intermediate results

Example:

Optimizer may convert:

```
σ(city='Delhi')(EMP ⋈ DEPT)
```

into:

```
(σ(city='Delhi')(DEPT)) ⋈ EMP
```

and perform the selection *before* join → smaller data → cheaper network transfer.

**3️⃣ Code Generator**

Goal:

Translate optimized query plan → executable code or query execution strategy.

Tasks:

- Generate subqueries for each site.
- Insert data transfer instructions (e.g., “Send result from Site A → Site B”).
- Coordinate multi-site transactions.

Example Output:

```bash
-- Site Mumbai
SELECT * FROM DEPT WHERE city='Delhi';

-- Send result to Delhi
-- Site Delhi
JOIN local EMP with received DEPT result
```

**4️⃣ Runtime Processor**

**Goal:**

Actually execute the plan → manage **data transfer, communication, intermediate results**.

**Tasks:**

- Execute subqueries at each site.
- Coordinate communication among sites.
- Assemble final result and return to user.

**Characteristics:**

- Uses **parallel execution** (inter-site and intra-site).
- Handles **network failures** and **site unavailability**.
- Monitors runtime stats for adaptive optimization (in advanced systems).

---

### 2.2 Detailed Component Analysis

### **Component 1: PARSER**

Functions:

- Lexical analysis (tokenization)
- Syntax checking
- Semantic analysis
- Transform SQL into internal representation (query tree/graph)

Example:

sql

```sql
*-- Input SQL Query*
SELECT E.Name, D.DeptName
FROM Employee E, Department D
WHERE E.DeptID = D.DeptID AND E.Salary > 50000 AND D.Location = 'Delhi';
```

**Parse Tree Output:** 

```sql
           PROJECT (Name, DeptName)
                    |
                  JOIN (E.DeptID = D.DeptID)
                    |
        +-----------+-----------+
        |                       |
    SELECT                  SELECT
(Salary > 50000)      (Location = 'Delhi')
        |                       |
    Employee(E)            Department(D)
```

### **Component 2: QUERY OPTIMIZER**

**Most Critical Component** - Transforms parsed query into efficient execution plan.
Optimization Steps:

Step 1: Query Decomposition

- normalisation
- analysis
- simplification
- restructuring

Step 2: Data Localization

Step 3: Global Optimization

Step 4: Local Optimization

***“Brain of Query Processing”***

The query optimizer decides *how* to execute a query most efficiently.

In a distributed database, this becomes complex because:

- Data is fragmented (horizontally/vertically)
- Stored at different sites
- Network communication is expensive

So the optimizer must choose:

- Which sites to access
- Which fragments to use
- Which operations to perform where
- In what order

### **Step 1: Query Decomposition**

Once the SQL query is parsed into a **query tree**, the optimizer first simplifies and restructures it into an *algebraically correct and minimal form*.

Think of this as **"cleaning and rewriting"** the query before any cost-based analysis.

**🧩 1. Normalization**

Goal: Convert query into a canonical (standardized) logical form, typically relational algebra.

Why?

- To handle queries uniformly
- To simplify further optimization

```sql
SELECT * FROM EMP WHERE NOT (city <> 'Delhi');

-- After **normalization**:
SELECT * FROM EMP WHERE city = 'Delhi';
```

**🧩 2. Analysis**

Goal:

Verify semantic correctness — ensure all relations, attributes, and operations mentioned in the query make sense and actually exists .

Tasks:

- Check schema consistency
- Identify which relations and fragments are used
- Validate attribute references

```sql
SELECT name FROM EMP, DEPT WHERE EMP.deptno = DEPT.id;
```

Optimizer verifies that `deptno` and `id` exist, are comparable, and belong to compatible types.

**🧩 3. Simplification**

Goal:

Eliminate unnecessary parts of query and reduce size of the query tree.

Techniques:

- Remove redundant predicates
- Replace complex expressions with equivalent simpler ones
- Use constant propagation

Example:

```sql
SELECT * FROM EMP WHERE (salary > 5000 AND salary > 3000);

-- Simplified to:
SELECT * FROM EMP WHERE salary > 5000;
```

**🧩 4. Restructuring (Logical Optimization)**

Goal:

Use relational algebraic laws to reorder and combine operations for efficiency.

Common Transformations:

- Selection Pushdown: Apply `WHERE` before joins to reduce intermediate results
- Join Reordering: Choose join order that reduces data movement
- Projection Pushdown: Eliminate unnecessary attributes early

Example:

```sql
-- Original:
σ(city='Delhi')(EMP ⋈ DEPT)

-- Restructured:
(σ(city='Delhi')(DEPT)) ⋈ EMP
```

this reduces the network overhead, so we have to send less data while transffering over the network to other site which eventually reduces cost as well as response time

---

### Step 2: Data Localization

Once the logical query is clean, optimizer now maps global relations → actual physical fragments/sites. Because In a distributed DB, tables are **fragmented (horizontally/vertically)** and **replicated** across multiple sites.

Key Tasks:

1. **Consider Data Fragmentation**
    - Identify which fragments store required data. Example: `EMPLOYEE` may be **horizontally fragmented** by region: `EMP_North at Site1` and `EMP_South at Site2`
2. **Replace Global Relations with Fragments**
    
    Replace logical relations in query tree with physical fragments.
    
    Example:
    
    ```
    EMPLOYEE → EMP_North ∪ EMP_South ∪ EMP_West
    ```
    
3. **Eliminate Irrelevant Fragments**
    
    Remove fragments that **cannot** satisfy the query condition.
    
    ```
    SELECT * FROM EMPLOYEE WHERE region='North'
    ```
    
    ➡ Only EMP_North fragment is relevant; other fragments (South, West) are **discarded**.
    
    So After Data Localization, query is **converted into subqueries per site**, Final merge step at coordinator site
    

### Step 3: Global Optimization

This is where the real optimization intelligence works. Now that the optimizer knows which sites/fragments are involved, it must find the best global execution plan.

Objectives:

- Minimize communication cost
- Exploit parallelism between sites
- Reduce total response time

Key Activities:

1. **Generate Alternative Execution Plans**
    - Different join orders
    - Different data transfer strategies
        
        (Ship data A → B or B → A?)
        
2. **Estimate Cost of Each Plan**
    - Based on:
        - Data size at each site
        - Network bandwidth
        - Selectivity factors
        - CPU and I/O cost
3. **Choose Optimal Plan**
    - The one with minimum total cost (or response time).

Query:

```sql
SELECT *
FROM EMP E, DEPT D
WHERE E.dept_id = D.dept_id;
```

Assume:

- EMP in **Delhi**
- DEPT in **Mumbai**

Possible Plans:

| Plan | Description | Communication Cost |
| --- | --- | --- |
| P1 | Send EMP → Mumbai, join at Mumbai | 10 GB transfer |
| P2 | Send DEPT → Delhi, join at Delhi | 1 GB transfer |
| P3 | Send both partial results to 3rd site and join | 5 GB total |

→ Optimizer chooses **P2** (minimum 1 GB transfer).

### **Optimization Strategies:**

1. **Exhaustive Search**
2. **Heuristic-Based**
3. **Cost-Based**

### 1. Exhaustive Search

Idea: Generate all possible execution plans and choose the one with minimum cost.

- Enumerate all join orders, access paths, and site combinations.
- Compute cost for each plan (CPU, I/O, communication).
- Pick the lowest-cost one.

**Example:**

```sql
For three relations A, B, C —
possible join orders = (A ⋈ B) ⋈ C, (A ⋈ C) ⋈ B, (B ⋈ A) ⋈ C, etc. → **n! combinations**.
```

**Pros:** Guarantees the *optimal* plan.

**Cons:** Exponential complexity: `O(n!)` Impractical for queries with more than ~5–6 relations.

**Used in:** Research prototypes or small queries where plan space is small.

### 2. Heuristic-Based

The heuristic (rule of thumb) used here is: **"Push selections down"** or **"Do the filtering first."**  means using common-sense rules (like "filter early" or "drop columns you don't need") to quickly find a *good enough* plan for running a database query.

Use transformation rules and heuristics (common-sense rules) instead of exploring every plan. Some Common Heuristics:

1. Push selections down to reduce intermediate results early. (i.e filter first and combine after)
2. Perform projections early to eliminate unnecessary columns.
3. Combine operations whenever possible.

Example: Instead of joining first and then filtering:

```sql
-- natural joining employee and department tables first and then filtering the rows based on delhi city
σ(city='Delhi')(EMP ⋈ DEPT)
```

Heuristic optimizer does:

```sql
-- filtering delhi rows from department table first and then natural join those filtered result with employee table
(σ(city='Delhi')(DEPT)) ⋈ EMP
```

→ reduces transmitted tuples → less cost.

**Pros:**

- Polynomial time
- Efficient for large queries

**Cons:**

- May miss the globally optimal plan (approximation)

**Used in:** Commercial systems when query complexity is large.

### 3. Cost-Based (most commonly used)

- Estimate cost of operations
- Use statistics (cardinality, selectivity)
- Choose minimum estimated cost

***How Cost-Based Optimization Works***

The optimizer becomes a super-detailed trip planner. It doesn't just guess; it *estimates* the "cost" (usually meaning time, CPU work, and disk reads) for every step of every possible plan.

To do this, it needs two things from its "statistics" database:

1. **Cardinality (How many items?)**
    - It knows: The **Bank** table has 10 million customers. and The **Post Office** table has 5 million packages. then tells the optimizer how "big" each table is.
2. **Selectivity (How specific is my filter?)**
    - It knows: The filter `city='Delhi'` will only match 0.01% of the packages in the **Post Office** (this is called "low selectivity" - it's very specific).
    - It knows: A filter like `status='open'` might match 50% of the **Bank** accounts (this is "high selectivity").
    
    > *note: This selectivity statistic is taken from the histogram of the tables, in modern databases the database keeps a "dirty" counter for each table. Every time you `INSERT`, `UPDATE`, or `DELETE` a row, the counter goes up. Low-priority background process will automatically run to create a new histogram snapshot.The histogram 📊 is created periodically. The query optimizer uses the most recent snapshot it has.*
    > 

**Comparing Plans with Costs**

Now, the optimizer calculates the *total cost* for all the different plans it can think of.

**→ Plan A: Filter First (The Heuristic Plan)**

`(σ(city='Delhi')(Post Office)) ⋈ Bank`

1. Cost to filter Post Office: (Scan 5 million packages) x (0.01% match) = Cost: 500 units (This finds ~500 packages for Delhi).
2. Cost to join 500 packages with 10 million bank accounts: This is a small thing joining a big thing. Cost: 20,000 units.
3. TOTAL ESTIMATED COST: 20,500 units

**→ Plan B: Join First (The "Bad" Plan)**

`σ(city='Delhi')(Bank ⋈ Post Office)`

1. Cost to join 10 million accounts with 5 million packages: This is a *massive* operation. The intermediate result is gigantic. Cost: 90,000,000,000 units.
2. Cost to filter that giant result for 'Delhi': Cost: 1,000,000 units.
3. TOTAL ESTIMATED COST: 91,000,000,000 units

**The Decision**

Choose minimum estimated cost

- **Plan A Cost:** 20,500
- **Plan B Cost:** 91,000,000,000

looking at numbers, optimizer looks at the numbers. It picks **Plan A** because its estimated cost is dramatically lower.

### Step 4: Local Optimization

Once the global plan is finalized, each site performs local optimization — i.e. optimizing how to execute its own subquery using the local DBMS optimizer.

1. **Apply Local DBMS Optimizer**
    - Choose best index, access path, and join method (nested loop, hash join, etc.)
2. **Use Local Statistics**
    - Cardinality, selectivity, local cost models.
3. **Perform Intra-site Parallel Execution**
    - Query plan executed using local resources efficiently.

If Site Delhi receives subquery:

```sql
SELECT * FROM EMP WHERE city='Delhi';
```

Its local optimizer may:

- Use **B+ Tree index** on `city`
- Apply **index scan** instead of full table scan
- Cache frequently accessed pages

## Summary

```
                +-----------------------------+
                |        QUERY OPTIMIZER      |
                +-----------------------------+
                        │
                        ▼
        ┌────────────────────────────────────────────┐
        │           STEP 1: Query Decomposition       │
        │  → Normalize → Analyze → Simplify → Restructure │
        └────────────────────────────────────────────┘
                        │
                        ▼
        ┌────────────────────────────────────────────┐
        │           STEP 2: Data Localization         │
        │  → Replace global relations with fragments  │
        │  → Remove irrelevant fragments              │
        └────────────────────────────────────────────┘
                        │
                        ▼
        ┌────────────────────────────────────────────┐
        │           STEP 3: Global Optimization       │
        │  → Generate alternative plans               │
        │  → Minimize communication cost              │
        │  → Parallelize execution                    │
        └────────────────────────────────────────────┘
                        │
                        ▼
        ┌────────────────────────────────────────────┐
        │           STEP 4: Local Optimization        │
        │  → Use local indexes & DBMS optimizers      │
        └────────────────────────────────────────────┘

```
