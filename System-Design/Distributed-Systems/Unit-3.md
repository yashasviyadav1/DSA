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

### **Component 3: CODE GENERATOR**

Once the **Query Optimizer** decides *what* the best plan is, the **Code Generator** decides *how to execute it*.

**Purpose**

Convert the **logical execution plan** (which is abstract and optimizer-friendly) into a **physical executable form** — something the DBMS runtime can actually execute.

Think of it like:

> Optimizer gives a recipe, and the Code Generator turns it into cooking steps a chef can follow.
> 

Steps:

- *Translate Execution Plan to Executable Code*
- *Generate Calls to Runtime Routines*
- *Handle Data Format Conversions*
- *Prepare for Distributed Execution*

### Responsibilities

### 1️⃣ Translate Execution Plan to Executable Code

- The optimizer’s plan (query tree or DAG) is **converted into procedural code**.
- Each node (JOIN, SELECT, PROJECT) becomes a **routine** or **function call**.
- These routines will later be executed by the runtime processor.

**Example:**

```
JOIN (E.DeptID = D.DeptID)
→ generate_join(E, D, "DeptID", "DeptID")
```

The code generator produces a low-level sequence like:

```c
scan(Employee)
filter(Salary > 50000)
send_to(DeptNode)
receive_from(EmployeeNode)
join_on(DeptID)
project(Name, DeptName)
```

### 2️⃣ Generate Calls to Runtime Routines

- The DBMS already has **built-in modules** (for scan, join, sort, filter, etc.).
- The code generator links these routines appropriately.
- This allows **reusability** and consistency.

Example:

- Use built-in routine `local_join()` instead of re-implementing it.
- Each operator in the plan is associated with a corresponding runtime function.

### 3️⃣ Handle Data Format Conversions

- Different sites may have different **data representations**, e.g.,
    - Different endian formats (Big-endian vs Little-endian)
    - Different character encodings (UTF-8, ASCII, etc.)
- The code generator **inserts conversion operations** so that data sent across sites can be understood correctly.

Example:

If Site A uses UTF-8 and Site B uses Latin-1, it generates conversion routines before sending data.

### 4️⃣ Prepare for Distributed Execution

- Identify **which operation runs where** (site assignment).
- Insert **data transfer instructions** (like SEND, RECEIVE, SHIP).
- Insert **synchronization points** for inter-site coordination.

Example:

If `Employee` is at Site 1 and `Department` is at Site 2,

the code generator may produce:

```
AT Site 1: scan(Employee), filter(Salary > 50000), send_to(Site2)
AT Site 2: receive_from(Site1), join(Department), project(Name, DeptName)
```

**Final Output:**

An **Executable Query Execution Plan (QEP)** that includes:

- Sequence of physical operations
- Site assignments
- Data transfer details
- Synchronization & communication routines

---

### **Component 4: RUNTIME PROCESSOR**

Once the **code generator** produces the executable plan, the **runtime processor** is responsible for **executing** it across the distributed system.

**Purpose**

To actually *run* the distributed query — fetching data, performing joins, coordinating between sites, and returning results to the user.

Think of it like:

> The runtime processor is the “executor” that follows the instructions from the code generator.
> 

functions: 

- *Execute Generated Code*
- *Manage Data Transfers Between Sites*
- *Coordinate Distributed Operations*
- *Handle Failures and Recovery*
- *Return Results to User*

### Functions of Runtime Processor

### 1️⃣ Execute Generated Code

- It reads and executes the code produced by the code generator.
- Executes local and remote operations using site DBMS APIs.

Example:

```
Run local SELECT on Employee
Send result tuples to Site 2
Receive joined tuples from Site 2
```

### 2️⃣ Manage Data Transfers Between Sites

- Handles **shipping of intermediate results**.
- Uses efficient communication protocols (e.g., pipelining, buffering).
- Ensures **minimal data transfer** using network cost estimation.

Example:

If intermediate data is large, the runtime processor may apply projection before sending it to reduce data size.

### 3️⃣ Coordinate Distributed Operations

- Ensures all sites **synchronize correctly**.
- Maintains operation order and timing.
- May use **two-phase commit (2PC)** for distributed transactions.

Example:

Site A cannot perform join until it receives data from Site B.

### 4️⃣ Handle Failures and Recovery

- Detects failures (node crash, network failure).
- Uses logs and checkpoints to recover partial results.
- Re-executes subplans if necessary.

Example:

If Site 2 fails, the runtime processor can re-send data or restart that subquery.

### 5️⃣ Return Results to User

- Combines partial results.
- Applies final ordering, grouping, or formatting.
- Sends the final result to the user or client application.
---
### Execution Modes in Query Processing

When the **runtime processor** executes a query plan, it can do so in **two modes** — *interpreted* or *compiled*.

These differ in how the query plan is **executed** and **optimized** for performance.

- 1️⃣ **Interpreted Mode**
    
    Idea:
    
    The query plan (tree or graph) is *interpreted* step-by-step during execution — like reading and executing instructions line by line.
    
    How it works:
    
    - The plan nodes (e.g., selection, join, projection) are not converted into machine code.
    - Instead, a query interpreter reads each operator at runtime and executes it.
    - Each operation calls the respective function dynamically.
    
    Example:
    
    - Suppose a plan says:
        
        `SELECT → JOIN → SCAN(Employee)`
        
    - The interpreter reads:
        - “Ok, first do SCAN(Employee)”
        - “Now apply JOIN condition”
        - “Now PROJECT Name and DeptName”
    
    Advantages:
    
    - Flexible — can adapt at runtime (e.g., dynamic query optimization)
    
    - Easy to debug and modify
    
    Disadvantages:
    
    - Slower — because every operator incurs interpretation overhead at runtime
    - More CPU instructions are needed per operation
    
    Analogy:
    
    Like running a Python script — interpreted line by line.
    
- 2️⃣ **Compiled Mode**
    
    Idea:
    
    The query plan is compiled into machine code (or low-level code) *before* execution.
    
    How it works:
    
    - The entire execution plan is translated into optimized executable code.
    - The DBMS can even generate C/C++ code or bytecode for faster execution.
    - This code directly interacts with the storage engine and memory.
    
    Example:
    
    - The DBMS compiles the same query plan into executable instructions:
        
        ```
        Load Employee table
        Filter Salary > 50000
        Join with Department
        Project Name, DeptName
        ```
        
        → then executes this compiled binary.
        
    
    Advantages:
    
    - Much faster — no interpretation overhead
    - Can exploit CPU-level optimizations and caching
    
    Disadvantages:
    
    - Less flexible — if data distribution or plan changes, recompilation is needed
    - Slower to start (compilation takes time)
    
    Analogy:
    
    Like running a C program — compiled once, executed very fast.


---

important note to remove confusions :- 

> Topics overlap between “Characterization of Query Processors” and “Layers of Query Processing”.
The 4 layers are a reorganized, distributed view of the same 4–5 stages that happen internally in a query processor. (which we studies initially)
> 

## 3. LAYERS OF QUERY PROCESSING

Distributed query processing can be understood as a **four-layer pipeline** — each layer adds structure, optimization, and physical meaning to the query.

### **3.1 Four-Layer Architecture Overview**

```
┌─────────────────────────────────────┐
│   Layer 4: Query Result Assembly    │  ← Collect and merge results
├─────────────────────────────────────┤
│   Layer 3: Distributed Execution    │  ← Execute at multiple sites
├─────────────────────────────────────┤
│   Layer 2: Global Query Optimization│  ← Optimize across sites
├─────────────────────────────────────┤
│   Layer 1: Query Decomposition      │  ← Parse and transform
└─────────────────────────────────────┘
```

Each layer progressively **refines** the query — from logical representation to physical execution.

### **3.2 Layer 1: Query Decomposition**

Goal:

Convert the user’s **SQL query on global schema** into an **optimized algebraic expression** that can later be localized to fragments and executed efficiently.

**Input → Output**

| Input | Output |
| --- | --- |
| SQL query (on global schema) | Canonical relational algebra expression |

**Major Phases of Query Decomposition**

### **1️⃣ Normalization**

Convert the SQL query into a **standardized form** — removing redundancies and ambiguities.

**Purpose:**

- Ensure consistent internal representation
- Simplify downstream transformations

**Example:**

```sql
-- Original Query
SELECT * FROM Employee
WHERE Salary > 50000 OR Salary > 60000;

-- Normalized (simplified condition)
SELECT * FROM Employee
WHERE Salary > 50000;
```

Redundant OR is eliminated since 60000 ⊂ 50000 condition.

### **2️⃣ Analysis**

This phase ensures **query correctness**.

**Tasks:**

- Type checking (ensure attributes are comparable)
- Semantic validation (ensure attributes/tables exist)
- Integrity constraint checks

Example:

If the query references `E.DeptCode` but the schema has `DeptID`, the parser/analysis layer will raise an error.

### **3️⃣ Simplification**

Transform the algebraic form of the query by **applying equivalence rules** to remove unnecessary operations and reduce cost.

Below are key **transformation rules** used in relational algebra simplification 👇

**[Imp] Transformation Rules**

| Rule | Name | Expression | Meaning |
| --- | --- | --- | --- |
| **R1** | Cascade of Selections | σp1(σp2(R)) = σ(p1 ∧ p2)(R) | Combine multiple selections into one |
| **R2** | Commutativity of Selections | σp1(σp2(R)) = σp2(σp1(R)) | Selection order doesn’t matter |
| **R3** | Cascade of Projections | πA1(πA2(R)) = πA1(R) (if A1 ⊆ A2) | Drop unnecessary projections |
| **R4** | Commuting σ with π | πA(σp(R)) = σp(πA(R)) if predicate uses only attributes in A | Filter can be applied before projection |
| **R5** | Commutativity of Join | R ⋈ S = S ⋈ R | Order of join doesn’t affect result |
| **R6** | Associativity of Join | (R ⋈ S) ⋈ T = R ⋈ (S ⋈ T) | Grouping of joins can change |
| **R7** | Commuting σ with Join | σp(R ⋈ S) = σp(R) ⋈ S (if p on R only) | Apply selection early before join |
| **R8** | Commuting π with Join | πA(R ⋈p S) = πA(πA1(R) ⋈p πA2(S)) | Push projections down before join |

***Transformation Rules Explained***

You're looking at the core building blocks of **heuristic query optimization**, which is a key part of the "decomposition" layer you mentioned.
Don't worry about the complex math symbols. Let's think of this like **making a salad for a huge party** where your ingredients are in different warehouses.
• **Tables (`R`, `S`)**: Two giant warehouses. `R` (Employees) has 1 million boxes of info. `S` (Departments) has 100 boxes.
• **Join (`⋈`)**: A very slow, expensive truck that has to go between *both* warehouses to match items (e.g., match `Employee.DeptID` to `Department.DeptID`).
• **Selection (`σ`)**: A filter. "I only want boxes marked 'Sales'." (`σ(Dept = 'Sales')`)
• **Projection (`π`)**: A trimmer. "I only need the 'Name' and 'Salary' from each box, throw the rest away." (`π(Name, Salary)`)
The **Goal:** Make the salad as fast as possible. The *slowest* part is the Join (the truck).
**The main strategy is: Do not send useless boxes or useless parts of boxes to the slow truck.**

**The Big Idea: Do Less Work**

The whole point of these rules is to **push Selections (σ) and Projections (π) down** the query plan (do them *earlier*).
• **Bad Plan:** Join *all* 1 million Employee boxes with *all* 100 Department boxes... *then* filter for "Sales" employees... *then* trim to just their names.
• **Good Plan:**
    1. Go to the Employee warehouse and *first* filter for "Sales" (maybe you only have 5,000 left).
    2. Trim those 5,000 boxes to just "Name" and "DeptID".
    3. Go to the Department warehouse and trim all 100 boxes to just "DeptName" and "DeptID".
    4. *Now* use the slow truck to join your small list of 5,000 items with your small list of 100 items.
This is *thousands* of times faster. The rules you listed are the formal way to justify this "push-down" logic.

**Explaining the Rules in Plain English**

Let's group them by what they do.

**Group 1: Rules for Filtering (Selection (σ))**

These rules just say you can combine your filters efficiently.
• **R1: Cascade of Selections**
    ◦ `σp1(σp2(R)) = σ(p1 ∧ p2)(R)`
    ◦ **Meaning:** Instead of filtering for `(salary > 50000)` and *then* filtering the result for `(dept = 'Sales')`...
    ◦ ...just filter *once* for `(salary > 50000 AND dept = 'Sales')`. It's one pass, not two.
• **R2: Commutativity of Selections**
    ◦ `σp1(σp2(R)) = σp2(σp1(R))`
    ◦ **Meaning:** It doesn't matter if you find "Sales" people first and *then* check their salary, or check salaries first and *then* find "Sales" people. The final list is the same.

**Group 2: Rules for Trimming (Projection (𝜋))**

This rule says "don't trim things twice."
• **R3: Cascade of Projections**
    ◦ `πA1(πA2(R)) = πA1(R) (if A1 ⊆ A2)`
    ◦ **Meaning:** If you have a table and first trim it to get `(Name, Salary, DeptID)`...
    ◦ ...and *then* trim *that* result to just get `(Name, Salary)`...
    ◦ ...you could have just trimmed the original table to `(Name, Salary)` from the start. Just keep the *final* columns you need.

**Group 3: Rules for Combining (Join [(⋈))**](https://wumbo.net/symbols/bow-tie/)

These rules give you flexibility in *how* you join.
• **R5: Commutativity of Join**
    ◦ `R ⋈ S = S ⋈ R`
    ◦ **Meaning:** Joining `Employees` to `Departments` gives the same result as joining `Departments` to `Employees`.
• **R6: Associativity of Join**
    ◦ `(R ⋈ S) ⋈ T = R ⋈ (S ⋈ T)`
    ◦ **Meaning:** If you have to join three tables (e.g., `Employees`, `Departments`, `Projects`), you can either join `(Employees + Departments)` first and then join `Projects`...
    ◦ ...or you can join `(Departments + Projects)` first and then join `Employees`. This is *crucial* because joining two small tables first is much smarter.

**Group 4: The Most Important Rules (Mixing Operations)**

These are the "push-down" rules and the whole reason for decomposition!
• **R7: Commuting (σ) with Join (THE MOST IMPORTANT RULE)** 🥇
    ◦ `σp(R ⋈ S) = σp(R) ⋈ S` (if p is only about R)
    ◦ **Meaning:** This is the core of optimization!
    ◦ *Bad way:* `σ(Employees.Salary > 100k) (Employees ⋈ Departments)`
    ◦ *Good way:* `( σ(Employees.Salary > 100k) (Employees) ) ⋈ Departments`
    ◦ **In English:** Instead of joining *all* employees to departments and *then* filtering for high salaries...
    ◦ ...**Filter the employees for high salaries *first*** (getting a much smaller table), and *then* join that small table to departments. This saves a massive amount of work.
• **R8: Commuting (π) with Join (THE SECOND MOST IMPORTANT RULE)** 🥈
    ◦ `πA(R ⋈p S) = πA(πA1(R) ⋈p πA2(S))`
    ◦ **Meaning:** This is the "trim early" rule.
    ◦ **In English:** Instead of joining the *entire* `Employees` table (20 columns) with the *entire* `Departments` table (15 columns)...
    ◦ ...if you only need `Employee.Name` and `Department.Location` in the end, just trim `Employees` down to `(Name, DeptID)` and trim `Departments` down to `(Location, DeptID)` *first*.
    ◦ Then, join those two small, skinny tables. This saves memory and I/O.
• **R4: Commuting (σ) with (π)**
    ◦ `πA(σp(R)) = σp(πA(R))`
    ◦ **Meaning:** You can usually filter rows first and then trim columns, or vice-versa. (You just have to be careful not to trim a column that your filter needs!)

### **4️⃣ Restructuring**

Now that redundant operations are removed, the algebraic expression is **restructured** into an efficient logical form.

This step applies **heuristics** (rule-of-thumb strategies) for improved performance.

**Heuristics for Query Restructuring**

| Heuristic | Rule | Benefit |
| --- | --- | --- |
| **H1** | Push selections down | Reduces tuple count early |
| **H2** | Push projections down | Reduces attribute count early |
| **H3** | Perform most restrictive selections first | Eliminates largest irrelevant data quickly |
| **H4** | Replace Cartesian product + selection with join | Prevents huge intermediate results |

***Example Transformation***

**Original SQL Query:**

```sql
SELECT E.Name, D.DeptName
FROM Employee E, Department D
WHERE E.DeptID = D.DeptID
  AND E.Salary > 50000
  AND D.Location = 'Delhi';
```

**Initial (Naive) Algebraic Form:**

```
πName,DeptName(σE.DeptID=D.DeptID ∧ Salary>50000 ∧ Location='Delhi'(E × D)
```

→ This is inefficient because it first performs a **Cartesian product (E × D)** before applying filters.

**After Applying Heuristics:**

```
πName,DeptName(
  σSalary>50000(E)
  ⋈DeptID
  σLocation='Delhi'(D)
)
```

Here:

- **Selections** are pushed closer to base relations (H1).
- **Join** replaces the expensive Cartesian product (H4).
- Only **necessary attributes** are projected (H2).

**Restructured Query Tree**

```
            πName,DeptName
                |
             ⋈DeptID
              /   \
             /     \
    σSalary>50000  σLocation='Delhi'
          |              |
      Employee       Department
```

Now, the tree is **optimized logically** — smaller intermediate results, better performance.

---

### **3.3 Layer 2: Global Query Optimization**

Once the query has been **decomposed** (Layer 1), the optimizer must decide:

- **Where** to execute each operation,
- **In what order**, and
- **How** to minimize total cost (especially communication cost).

> Essentially, it transforms a logical query tree into a distributed execution plan.
> 

**Input → Output**

| **Input** | **Output** |
| --- | --- |
| Canonical (optimized logical) query | Global execution plan specifying site assignments and operation order |

**Key Tasks in Global Query Optimization**

### **1️⃣ Data Localization**

Since data in a distributed database is **fragmented** or **replicated**, we must map global relations to actual **physical fragments** at different sites.

**Steps:**

- Replace each **global relation** with its **fragments**.
- Eliminate irrelevant fragments (those that don’t satisfy query conditions).

**Example:**

```
Employee → Employee_Delhi ∪ Employee_Mumbai
Department → Department_Delhi ∪ Department_Bangalore
```

Query Condition:

```
WHERE D.Location = 'Delhi'
```

So, only `Employee_Delhi` and `Department_Delhi` fragments are used.

This process converts:

```
πName,DeptName(σSalary>50000(E) ⋈DeptID σLocation='Delhi'(D))
```

into

```sql
πName,DeptName(
  σSalary>50000(Employee_Delhi)
  ⋈DeptID
  σLocation='Delhi'(Department_Delhi)
)

-- **Output:** Fragmented Query Tree — i.e., now we know *which fragments* to access and *where* they are located.
```

### **2️⃣ Generation of Alternative Query Plans**

There are **many possible ways** to execute a distributed query.

Each plan differs by:

- The **order of operations** (e.g., join order),
- The **sites** chosen for execution,
- The **data movement pattern**.

**Example:**

To join `Employee_Delhi` (at Site 1) and `Department_Delhi` (at Site 2), possible plans include:

1. Ship `Employee_Delhi` to Site 2 and join there.
2. Ship `Department_Delhi` to Site 1 and join there.
3. Perform partial joins at both sites and merge results.

→ Each plan has **different costs** (due to network and processing).

### **3️⃣ Cost Estimation**

For every candidate plan, the optimizer estimates **total cost** using a cost model.

**Total Cost Formula:**

```
Total Cost = CPU_Cost + I/O_Cost + Communication_Cost
```

But in distributed systems: ***Communication cost dominates***.

### **Communication Cost Estimation**

| Component | Description |
| --- | --- |
| **Startup Cost (Cstart)** | Cost of initiating a data transfer (connection setup) |
| **Transfer Cost (Ctrans)** | Cost of transmitting data over the network |
| **Total Communication Cost** | `Cstart + (Message_Size × Ctrans)` |

**Example:**

If 1 MB data is transferred at 10 ms setup + 1 ms per KB:

```
C = 10 + (1024 × 1) = 1034 ms
```

So the optimizer will prefer plans that *reduce the data size sent across sites.*

### **4️⃣ Optimization Strategies**

There are **three broad strategies** for global optimization:

🔹**A. Exhaustive (Search-Based) Optimization**

- Enumerate **all possible plans**. then Compute cost for each. Choose plan with **minimum total cost**.

**Pros:** Finds the optimal plan.

**Cons:** Exponential complexity → `O(n!)` (only feasible for small queries).

🔹**B. Heuristic-Based Optimization**

- Use **rules of thumb** (heuristics) to generate a good (not necessarily best) plan.
- Faster and scalable.

**Common Heuristics:**

1. **Perform selection and projection early** → reduce data size.
2. **Perform joins at the site where most data resides.**
3. **Avoid unnecessary data transfer**.
4. **Use semijoins to minimize communication.**

***Semijoin Strategy Example***

Instead of transferring full relations, transfer **only join attribute values** to filter data remotely.

**Scenario:**

```
Site A: Employee(EmpID, Name, DeptID)
Site B: Department(DeptID, DeptName)
```

Goal: `Employee ⋈ Department`

**Naive Join (High Cost):**

- Send full `Employee` to Site B.
- Communication = large.

**Semijoin Approach:**

1. Send only `DeptID` values from `Department` → Site A.
2. Filter Employee records using these DeptIDs at Site A.
3. Send filtered employees to Site B and join.

→ Less data transfer → reduced communication cost.

🔹 **C. Cost-Based Optimization**

- Combines **heuristics** with **quantitative cost estimates**.
- Uses **statistics** such as:
    - Relation cardinality
    - Selectivity of predicates
    - Size of tuples/fragments
    - Network bandwidth

Example:

```
Cost(Join at Site1) = Local cost (E1) + Comm cost (D2 → Site1)
Cost(Join at Site2) = Local cost (D2) + Comm cost (E1 → Site2)
```

Choose the one with **minimum total cost**.

*As Result of Global Optimization.* After this layer, we get a **global execution plan** that specifies:

- Which fragments to access,
- Which operations to perform locally,
- Which data to ship where,
- The order of operations.

*Example Final Plan (Simplified) :*

```
Site 1: σSalary>50000(Employee_Delhi)
Send result to Site 2
Site 2: σLocation='Delhi'(Department_Delhi)
Join received Employee tuples with Department
Project Name, DeptName
Return results to client
```

---

### **Layer 3: Distributed Execution**

Goal: To **execute the global query plan** by running subqueries at the appropriate sites, coordinating their execution, and collecting intermediate results efficiently.

***Input and Output***

| Step | Description |
| --- | --- |
| **Input** | Optimized global query plan (from Layer 2) |
| **Output** | Partial query results from each site (sent to Layer 4 for assembly) |

**Main Responsibilities**

1. **Fragment Query into Subqueries**
    - The global query is divided based on **data distribution** (horizontal / vertical fragments).
    - Each subquery is sent to the site containing that fragment.
    
    *Example:*
    
    ```
    SELECT * FROM EMPLOYEE
    WHERE LOCATION = 'Delhi';
    ```
    
    If `EMPLOYEE` is horizontally fragmented:
    
    - Fragment 1 (Delhi data) at Site A
    - Fragment 2 (Mumbai data) at Site B
    
    Then → Only Site A needs to execute the subquery.
    
2. **Local Query Execution**
    - Each site’s **local DBMS** executes its assigned subquery (in its own query processor).
    - Local optimization (e.g., index usage, join ordering within that site) happens here.
    
    *→ Local operations are just like centralized DBMS processing.*
    

**Inter-Site Communication**

- Sites exchange data **when needed** (e.g., for distributed joins or unions).
- Communication is **expensive**, so minimizing data transfer is key.

🧠 *Example:*

```
πName(σDID=EID (EMPLOYEE ⋈ DEPARTMENT))
```

If `EMPLOYEE` is at Site A and `DEPARTMENT` at Site B:

- Either A sends relevant EMPLOYEE tuples to B, or
- B sends DEPARTMENT tuples to A.

→ The optimizer decides which direction is cheaper (based on cost model).

**Synchronization & Parallel Execution**

- Subqueries can often be executed **in parallel** at multiple sites.
- The coordinator manages **start**, **dependency**, and **result collection**.

🔁 Example:

- Site A executes filter on EMPLOYEE
- Site B executes filter on DEPARTMENT
- Coordinator waits for both → then performs join.

**Techniques for Efficient Distributed Execution**

| Technique | Purpose |
| --- | --- |
| **Query Shipping** | Send the *query* to the site with the data (preferred, less data movement). |
| **Data Shipping** | Send *data* to where the query is executed (used if query is small or site lacks capability). |
| **Hybrid Shipping** | Combination of both based on cost or resource constraints. |
| **Semi-Join Strategy** | Send only *join attributes* first to reduce transferred data size. |

---

### **Layer 4: Query Result Assembly**

Goal: To collect, merge, and present the results obtained from different sites after distributed execution — forming the final answer for the user.

| Step | Description |
| --- | --- |
| **Input** | Partial or intermediate results from multiple sites (Layer 3 output) |
| **Output** | Final, unified query result (presented to user or application) |

Main Responsibilities

1. **Collect Results from All Sites**
    - The *coordinator site* (usually where the query originated) gathers outputs from every participating site.
    - Communication control ensures that all partial results are received and no duplicates are missed.
    
    If `SELECT * FROM EMPLOYEE;` runs across 3 sites (each with fragments), The coordinator waits for partial results from all 3 before combining them.
    
2. **Merge & Combine Results**
    - For **UNION** type queries (like retrieving fragments), results are concatenated.
    - For **JOIN** or **AGGREGATE** queries, results may need to be merged or computed globally.
    
    *Example:*
    
    ```
    SELECT COUNT(*) FROM EMPLOYEE;
    ```
    
    - Each site computes local count (say 50, 70, 30)
    - Coordinator adds them → Final result = 150
3. **Sort / Group / Aggregate (if required)**
    - If the query includes **ORDER BY**, **GROUP BY**, or **aggregate functions**, these may need to be **finalized** at the coordinator site.
    - Partial aggregates (like `SUM`, `COUNT`, `AVG`) are combined efficiently.
    
    *Example:*
    
    ```
    SELECT DeptID, AVG(Salary)
    FROM EMPLOYEE
    GROUP BY DeptID;
    ```
    
    - Each site sends (DeptID, partial_sum, partial_count), Coordinator combines to compute final averages.
4. **Eliminate Duplicates**
    - Needed for **UNION**, **DISTINCT**, etc.
    - If fragments overlap, the coordinator ensures no duplicates appear in the final result.
5. **Present Final Output**
    - Once all merging, aggregating, and sorting is done,
        
        the final query result is **returned to the user/application**.
        

*Execution Flow Example*

Let’s take a simple example query:

```sql
SELECT Name, Salary
FROM Employee
WHERE Salary > 50000;
```

Suppose `Employee` is horizontally fragmented:

| Site | Data |
| --- | --- |
| Site A | Employees in Delhi |
| Site B | Employees in Mumbai |

**Step-by-Step Flow:**

| Layer | Description |
| --- | --- |
| **Layer 1 (Decomposition)** | SQL parsed → relational algebra form |
| **Layer 2 (Global Optimization)** | Query split across fragments (Site A, Site B) |
| **Layer 3 (Distributed Execution)** | Each site executes locally and sends results |
| **Layer 4 (Result Assembly)** | Coordinator merges both result sets → final table |

---


## 1) Localization of Distributed Data

**Fragmentation types**

- **Horizontal fragmentation**: subset of rows (predicate-based); preserves schema. Good for locality (regional data).
- **Vertical fragmentation**: subset of columns (must keep primary key across fragments); used when different attributes used by different sites.
- **Hybrid fragmentation**: first vertical then horizontal (or vice versa).
- **Derived fragmentation**: fragments of one relation based on fragmentation of related relation to improve locality for joins.

**Catalog / Fragment mapping**

- The global catalog stores metadata: fragment definitions, site locations, replication status.
- **Fragment selection**: optimizer consults the catalog to replace global relation with appropriate fragments (use predicates to prune irrelevant fragments).

**Replication**

- Full or partial replication speeds reads but introduces consistency and update propagation costs (replica selection problem).
- Must handle update propagation (synchronous vs asynchronous) and choose site for writes.

**Exam tips**

- Draw examples: Employee split by region (horizontal), Employee attributes split into public vs payroll (vertical).
- Explain how a WHERE clause can allow pruning fragments (localization).

## Centralized Query Optimization

**Access paths**

- Table scan, index scan (clustered/unclustered), covering index.
- Choose access path using statistics (pages, tuples, selectivity).

**Join algorithms**

- Nested loop join (simple, good if one side small or indexed)
- Block nested loop join (I/O optimized)
- Sort-merge join (good for large, sorted inputs)
- Hash join (good for equality joins if memory available)

Let's assume we have two tables, `Students` and `Majors`, and we want to find the name of each student and their corresponding major.

```sql
Students (The "outer" table)
| StudentID | Name | MajorID |
| :--- | :---    | :--- |
| 1    | Alice   | 10   |
| 2    | Bob     | 20   |
| 3    | Charlie | 10   |

Majors (The "inner" table)
| MajorID | MajorName |
| :---    | :---      |
| 10      | CS        |
| 20      | Physics   |
| 30      | Math      |

-- The Goal Query: 
SELECT Students.Name, Majors.MajorName 
FROM Students 
JOIN Majors 
ON Students.MajorID = Majors.MajorID;
```

There are 4 types of JOINs:

**1. Nested Loop Join (NLJ)**

This is the most straightforward, "brute-force" method. It uses two nested loops. For every single row in the outer table (`Students`), it scans the entire inner table (`Majors`) looking for matches.
• Analogy: Finding matching pairs of socks. You pick one sock from the "outer" pile (Students) and compare it to *every single sock* in the "inner" pile (Majors). When you find a match, you set them aside. Then you grab the *next* sock from the outer pile and repeat the *entire* process.

****Example Walkthrough:

1. Outer Loop (Students): Get `(1, 'Alice', 10)`.
    ◦ Inner Loop (Majors):
        ▪ Compare `10 == 10` (Match!). **Result:** `('Alice', 'CS')`.
        ▪ Compare `10 == 20` (No match).
        ▪ Compare `10 == 30` (No match).
2. Outer Loop (Students): Get `(2, 'Bob', 20)`.
    ◦ Inner Loop (Majors):
        ▪ Compare `20 == 10` (No match).
        ▪ Compare `20 == 20` (Match!). **Result:** `('Bob', 'Physics')`.
        ▪ Compare `20 == 30` (No match).
3. Outer Loop (Students): Get `(3, 'Charlie', 10)`.
    ◦ Inner Loop (Majors):
        ▪ Compare `10 == 10` (Match!). **Result:** `('Charlie', 'CS')`.
        ▪ Compare `10 == 20` (No match).
        ▪ Compare `10 == 30` (No match).

**2. Block Nested Loop Join (BNLJ)**

This is an optimization of the Nested Loop Join, designed to reduce a major bottleneck: disk I/O. Reading row-by-row from disk is very slow.
• How it works: Instead of processing row-by-row, it reads a block (or "page") of rows from the outer table into memory. Then, it scans the *entire* inner table (or a block of it) and compares all rows in its in-memory block against the inner table's rows.
• Analogy: Instead of picking up *one* sock from the outer pile, you grab a whole *armful* (a block). Then you compare that entire armful against each sock in the inner pile. This is much more efficient because you're "going to the pile" (accessing the disk) far fewer times.

Example Walkthrough:

1. Read a **block** of `Students` into memory. Let's say the block size is 2.
    ◦ In-Memory Block: `[(1, 'Alice', 10), (2, 'Bob', 20)]`
2. Scan the `Majors` table.
    ◦ Get `(10, 'CS')`. Compare it against the *whole block* in memory.
        ▪ `10 == 10` (Match `Alice`). **Result:** `('Alice', 'CS')`.
        ▪ `10 == 20` (No match `Bob`).
    ◦ Get `(20, 'Physics')`. Compare it against the *whole block* in memory.
        ▪ `20 == 10` (No match `Alice`).
        ▪ `20 == 20` (Match `Bob`). **Result:** `('Bob', 'Physics')`.
    ◦ Get `(30, 'Math')`. (No matches in the block).
3. Read the next block of `Students` into memory.
    ◦ In-Memory Block: `[(3, 'Charlie', 10)]`
4. Scan the `Majors` table *again from the beginning*.
    ◦ Get `(10, 'CS')`. Compare it against the block.
        ▪ `10 == 10` (Match `Charlie`). **Result:** `('Charlie', 'CS')`.
    ◦ ...and so on.
• When it's good**:** This is better than NLJ when tables are large and not indexed, as it drastically reduces disk I/O.

**3. Sort-Merge Join (SMJ)**

This algorithm is based on a simple "divide and conquer" idea: joining two sorted lists is extremely fast.
    1. **Sort Phase:** Sort *both* tables on the join key (`MajorID`).
    2. **Merge Phase:** Scan down both sorted tables simultaneously, like two zippers merging.
• **Analogy:** You have two decks of cards, both already sorted by number. You want to find all matching pairs.
    ◦ You flip the top card of each deck: iIt's a match! Record it. Advance *both* pointers.
    ◦ if it is not a match then increment the smaller one 

Example Walkthrough:
1. Sort Phase:
    ◦ `Students` sorted by `MajorID`:
        ▪ `(1, 'Alice', 10)`
        ▪ `(3, 'Charlie', 10)`
        ▪ `(2, 'Bob', 20)`
    ◦ `Majors` sorted by `MajorID` (it's already sorted):
        ▪ `(10, 'CS')`
        ▪ `(20, 'Physics')`
        ▪ `(30, 'Math')`
2. Merge Phase:
    ◦ Ptr_S (Students) → `(1, 'Alice', 10)`
    ◦ Ptr_M (Majors) ->`(10, 'CS')`
    ◦ `10 == 10`? Yes. Result: `('Alice', 'CS')`. Advance Ptr_S. (To handle duplicates, you'd advance Ptr_S but *not* Ptr_M yet).
    ◦ Ptr_S ->`(3, 'Charlie', 10)`
    ◦ Ptr_M ->`(10, 'CS')`
    ◦ `10 == 10`? Yes. Result: `('Charlie', 'CS')`. Advance Ptr_S.
    ◦ Ptr_S ->`(2, 'Bob', 20)`
    ◦ Ptr_M ->`(10, 'CS')`
    ◦ `20 > 10`? Yes. `Ptr_M` is too small. Advance Ptr_M.
    ◦ Ptr_S ->`(2, 'Bob', 20)`
    ◦ Ptr_M ->`(20, 'Physics')`
    ◦ `20 == 20`? Yes. Result: `('Bob', 'Physics')`. Advance Ptr_S.
    ◦ Ptr_S ->(End of table). Stop.
• When it's good**:** Excellent for large tables, especially if they are *already sorted* (e.g., from an index scan), which lets it skip the expensive sort phase. It's also one of the few joins that works efficiently on non-equality conditions (like `>` or `<`).

**4. Hash Join (HJ)**

This is typically the fastest algorithm for equality joins when you have enough memory.
    1. Build Phase: Scan the *smaller* table (`Majors`) and build a hash table (or "hash map") in memory, using the join key (`MajorID`) as the hash key.
    2. Probe Phase: Scan the *larger* table (`Students`) one row at a time. For each row, hash its join key (`MajorID`) and "probe" (look up) that key in the hash table. If a match is found, return the result.

Example Walkthrough:
1. Build Phase (on smaller table, `Majors`):
    ◦ Create a hash table in memory.
    ◦ Read `(10, 'CS')`. Hash `10`. Store: `(10) \rightarrow ('CS')`
    ◦ Read `(20, 'Physics')`. Hash `20`. Store: `(20) \rightarrow ('Physics')`
    ◦ Read `(30, 'Math')`. Hash `30`. Store: `(30) \rightarrow ('Math')`
    ◦ In-Memory Hash Table:

```sql
| Key | Value |
| :--- | :--- |
| 10 | 'CS' |
| 20 | 'Physics' |
| 30 | 'Math' |
```

2. Probe Phase (on larger table, Students):
    ◦ Read (1, 'Alice', 10). Hash 10. Look up 10 in the hash table.
    ◦ Found! ('CS'). Result: ('Alice', 'CS').
    ◦ Read (2, 'Bob', 20). Hash 20. Look up 20.
    ◦ Found! ('Physics'). Result: ('Bob', 'Physics').
    ◦ Read (3, 'Charlie', 10). Hash 10. Look up 10.
    ◦ Found! ('CS'). Result: ('Charlie', 'CS').
• When it's good: The "go-to" join for large datasets *if* the join is on equality (=) and the *entire* hash table for the smaller table can fit in available RAM.

## Distributed Query Optimization

**Core difference**: communication cost usually dominates — so strategies aim to reduce bytes moved.

**Key Techniques**

- **Semijoin**: exchange only join key values to prefilter tuples at remote site. Steps: send projection of join attribute → filter local tuples → transfer filtered set → final join.
    - Variants: two-phase semijoin, cascade semijoin.
- **Bloom filters**: probabilistic compact filters sent to other site to filter tuples with small message size (small false positives).
- **Anti-semijoin**: used for difference operations (R − S).
- **Shipping strategies**:
    - **Query shipping**: move query to data (good when data large, computation small).
    - **Data shipping**: move data to query processor (good when data small).
    - **Hybrid**: combine using cost model.
- **Replication awareness**:
    - If relation R is replicated at many sites, choose the replica that minimizes data transfer/job latency.
- **Adaptive Query Processing**:
    - Reoptimize at runtime when statistics differ or network conditions change.
    - Techniques: eddies, runtime reordering, dynamic filters.
- **Multi-Query Optimization (MQO)**:
    - Share results/subplans among concurrent queries to save cost (materialize once, reuse).
- **Plan enumeration algorithms**:
    - Top-down vs bottom-up; greedy heuristics; use of dynamic programming for small join sets; search space pruning.
- **Failure handling & transactions**:
    - Distributed transactions often use 2-phase commit (2PC) for atomicity; optimizer must consider overhead.
- **Practical additions**:
    - Use of parallelism (pipelining, inter-site parallel execution), pipelined transfers to reduce latency.

**Exam tips**

- Be able to **sketch the semijoin sequence** and explain when semijoin outperforms direct shipping.
- Explain Bloom filter benefits and false positive tradeoffs.
- Show a small cost comparison (numbers) between shipping full table vs semijoin for clarity.
- Mention why adaptive runtime reoptimization is important in WAN environments.

---