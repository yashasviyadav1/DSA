## Unit-2: Distributed Database Design and Control

Let's dive deep into Unit 2, covering all topics comprehensively for M.Tech level understanding.

---

## 1. DISTRIBUTED DATABASE DESIGN

### 1.1 Top-Down Design Process

The **top-down approach** starts with a centralized schema and distributes it across multiple sites.

### Steps in Top-Down Design:

**Step 1: Requirements Analysis**

- Identify data requirements across all sites
- Analyze transaction patterns and frequencies
- Determine network topology and characteristics
- Identify user access patterns at each site

**Step 2: Conceptual Design**

- Create global conceptual schema using ER modeling
- Define entities, relationships, and constraints
- Independent of distribution considerations

**Step 3: Fragmentation**

- Divide relations into fragments
- Each fragment is a logical unit
- Types: Horizontal, Vertical, Mixed/Hybrid

**Step 4: Allocation**

- Assign fragments to specific sites
- Consider replication strategies
- Optimize based on access patterns and costs

**Step 5: Physical Design**

- Local schema design at each site
- Index structures, storage methods
- Site-specific optimizations

### Advantages of Top-Down Design:

- Better global optimization
- Consistency across the system
- Easier to maintain global integrity constraints
- Suitable for new system development

### Disadvantages:

- Requires complete redesign if system structure changes
- May not be feasible for integrating existing databases
- Complex for large-scale systems

---

### 1.2 Bottom-Up Design Process (Integration)

The **bottom-up approach** integrates existing local databases into a distributed system.

### Steps in Bottom-Up Design:

**Step 1: Local Schema Analysis**

- Analyze existing schemas at each site
- Identify data types, constraints, relationships
- Document local semantics

**Step 2: Schema Matching**

- Identify equivalent elements across schemas
- Handle naming conflicts (synonyms/homonyms)
- Resolve structural differences

**Step 3: Schema Integration**

- Merge local schemas into global schema
- Resolve conflicts and inconsistencies
- Create unified conceptual view

**Step 4: Schema Mapping**

- Define mappings between global and local schemas
- Establish transformation rules
- Handle semantic heterogeneity

### Challenges in Bottom-Up Design:

- [Semantic heterogeneity](https://www.notion.so/MT-CSE-18-14-ii-Distributed-Systems-27e2a3410ddc808a855cda0b9e08b577?pvs=21)
- Naming conflicts
- Structural conflicts
- Data type incompatibilities
- Constraint mismatches

> *Semantic heterogeneity occurs when different databases, often built independently within the same domain, represent or interpret the same data in different ways. This creates problems when trying to integrate or query such databases together, especially in distributed or federated database systems (FDBSs).*
> 

### Why Semantic Heterogeneity Occurs

It mainly arises due to design autonomy where each database has the freedom to define:

- **Universe of Discourse:** For example, customer databases in the US and China might store different sets of attributes for the same entity due to local accounting rules or currencies.
- **Representation and Naming:** Same data may be stored under different names (e.g., Customer_ID vs ClientNumber) or in different formats (e.g., date or currency formats).
- **Interpretation of Data:** A value like "priority customer" might be defined differently across systems.
- **Transaction Rules and Policies:** Local databases may have their own constraints, serializability rules, or compensating transactions.
- **Derived Data & Summaries:** Some databases might include computed fields or summaries which others do not.

### Challenges Caused by Semantic Heterogeneity

1. **Data integration:** Semantic heterogeneity can make it difficult to integrate data from multiple databases into a single system. This can result in data duplication, data inconsistencies, and reduced data quality.
2. **Query processing:** Semantic heterogeneity can make it difficult to process queries that involve data from multiple databases. This can result in slow query performance and increased processing time.
3. **Application development:** Semantic heterogeneity can make it difficult to develop applications that rely on data from multiple databases. This can result in increased development time and reduced application functionality.

### Solutions to Manage Semantic Heterogeneity

- **Data Mapping:** Map equivalent fields and values across different schemas.
- **Data Transformation:** Convert data formats and structures during integration.
- **Semantic Reconciliation:** Align the intended meaning of data fields across databases.
- **Metadata Management:** Use metadata to document how data is structured and what it means.

---

### Symbols - relational algebra

### 1. **σ (Sigma) — Selection Operator**

Selects *rows* (tuples) from a table that satisfy a given **condition (predicate)**.

> "Filter rows based on a WHERE condition."
> 

**Syntax:**

```
σ<condition>(Relation)
```

**Example:**

```
σ(Location = 'India')(EMPLOYEE)
```

means

“Select all employees whose location is India”

It’s equivalent to SQL:

```sql
SELECT * FROM EMPLOYEE WHERE Location = 'India';
```

**Used In:** Primary Horizontal Fragmentation (PHF)

### 2. **`π (Pi)`— Projection Operator**

**Meaning:**

Selects *columns* (attributes) from a relation.

> "Pick only these columns."
> 

**Syntax:**

```
π<columns>(Relation)
```

**Example:**

```
π(Name, Salary)(EMPLOYEE)
```

means

“Select only Name and Salary columns from EMPLOYEE.”

Equivalent SQL:

```sql
SELECT Name, Salary FROM EMPLOYEE;
```

**Used In:** Vertical Fragmentation

---

### 3. **`⨝`(Bowtie) — Natural Join Operator**

**Meaning:**

Combines two tables based on *common attributes* (usually a primary key = foreign key pair).

> “Merge two tables where they match on common columns.”
> 

**Syntax:**

```
Relation1 ⨝ Relation2
```

**Example:**

```
EMPLOYEE ⨝ DEPARTMENT
```

means

“Join EMPLOYEE and DEPARTMENT where their DeptID values match.”

Equivalent SQL:

```sql
SELECT * FROM EMPLOYEE NATURAL JOIN DEPARTMENT;
```

**Used In:**Reconstructing data after fragmentation

(e.g., combining vertically fragmented pieces)

---

### 4. **`⋉` (Left Semi-Join)**

**Meaning:**

Return **rows from the left relation** that have **matching rows in the right relation**, but **don’t include the right table’s columns**.

> “Filter left table using matches from the right table.”
> 

**Syntax:**

```
LeftRelation ⋉ RightRelation
```

**Example:**

```
ACCOUNT ⋉ CUSTOMER_INDIA
```

means

“Select all accounts whose customer is in CUSTOMER_INDIA.”

Equivalent SQL:

```sql
SELECT A.*
FROM ACCOUNT A
WHERE A.CustID IN (SELECT C.CustID FROM CUSTOMER WHERE Country = 'India');
```

**Used In:** Derived Horizontal Fragmentation (DHF)

---

### 5. **`∪` (Union)**

**Meaning:**

Combine tuples from two relations (like merging two result sets).

```
EMP_INDIA ∪ EMP_USA
```

means

“All employees either in India or USA.”

SQL equivalent:

```sql
SELECT * FROM EMP_INDIA
UNION
SELECT * FROM EMP_USA;
```

**Used In:** Reconstructing horizontally fragmented relations
| Symbol | Name | Meaning | SQL Equivalent | Common Use |
| --- | --- | --- | --- | --- |
| **σ** | Selection | Filter rows | `WHERE` | Horizontal fragmentation |
| **π** | Projection | Pick columns | `SELECT col1, col2` | Vertical fragmentation |
| **⨝** | Natural Join | Combine two relations | `NATURAL JOIN` | Reconstruct fragments |
| **⋉** | Semi-Join | Filter one relation using another | `WHERE ... IN (...)` | Derived fragmentation |
| **∪** | Union | Combine results | `UNION` | Combine fragments |

## 2. FRAGMENTATION

**Fragmentation** is the process of dividing a relation into smaller parts called fragments. Each fragment is stored at a different site.

### Why Fragmentation?

**Benefits:**

1. **Usage**: Data stored where it's used most frequently
2. **Efficiency**: Reduces irrelevant data access
3. **Parallelism**: Multiple fragments can be processed simultaneously.
4. **Security**: Sensitive data can be isolated.
5. **Reduced Network Traffic**: Local access reduces communication costs

### Fragmentation Correctness Rules

For fragmentation to be correct, it must satisfy three properties:

**1. Completeness**

- Every data item in the original relation must appear in at least one fragment
- No data loss during fragmentation
- Ensures: If R is fragmented into R₁, R₂, ..., Rₙ, then R = R₁ ∪ R₂ ∪ ... ∪ Rₙ

**2. Reconstruction**

- Must be possible to reconstruct the original relation from fragments
- Uses relational operations (JOIN for vertical, UNION for horizontal)
- Ensures reversibility of fragmentation

**3. Disjointness**

- For horizontal: Fragments should be disjoint (no duplicate tuples)
- For vertical: Non-key attributes shouldn't be duplicated (only primary key is replicated)
- Minimises redundancy and update anomalies

### [IMP] Why Fragmentation Reduces Network Overhead

**Network overhead** = time + cost + bandwidth used for data transfer between sites.

If all data is centralised (e.g., in the U.S.), a Delhi query must:

- Travel to U.S. node
- Process data there
- Return full results across the ocean 🌊

If data is **fragmented regionally (India data → Mumbai)**:

- Query runs **locally in India**
- Results sent to Delhi over a **short domestic path**

**Benefits:**

- Lower latency (shorter path)
- Reduced transcontinental bandwidth usage
- Computation done *where data lives* → smaller results transmitted

> If query truly needs all rows (no filters), data volume is same, but **path cost is much lower**.
> 

### Centralised vs Distributed Query Comparison

| Factor | Centralised DB (U.S.) | Distributed DB (India Fragment) |
| --- | --- | --- |
| Query execution | Remote (U.S.) | Local (Mumbai) |
| Data travel distance | ~13,000 km | ~1,400 km |
| Latency | High | Low |
| Load on central node | High | Distributed |
| Scalability | Limited | High |
| Fault tolerance | Low | Higher |
| Still sends 1M rows? | Yes |  Yes |
| But optimized? | No | Yes (local execution, faster transfer) |

> Fragmentation does not always reduce the number of rows sent,
> 
> 
> but it **reduces how far and how often** those rows must travel —
> 
> achieving better locality, speed, and scalability.
>

### 2.3 Types of Fragmentation

1. Horizontal Fragmentation
    1. Primary Horizontal Fragmentation (PHF)
    2. Derived Horizontal Fragmentation (DHF)
2. Vertical Fragmentation
3. Mixed / Hybrid Fragmentation

### A. Horizontal Fragmentation

1. **Primary Horizontal Fragmentation (PHF)**

Definition:

You divide (fragment) a relation **based on conditions (predicates)** that use **only the attributes of that same relation**.

So — the decision about which tuple goes to which fragment depends *only on that table itself.*

Example:

Let’s say you have a relation:

```
EMPLOYEE(EmpID, Name, Dept, Location)
```

You want to fragment this based on the `Location` attribute:

```
EMPLOYEE_INDIA = σ(Location = 'India')(EMPLOYEE)
EMPLOYEE_USA   = σ(Location = 'USA')(EMPLOYEE)
```

Here:

- The **predicate** is `Location = 'India'` or `Location = 'USA'`
- The **fragmentation** depends only on the **EMPLOYEE** relation’s own attributes
    
    → Hence this is **Primary Horizontal Fragmentation (PHF)**
    

**2. Derived Horizontal Fragmentation (DHF)**

Definition:

You divide (fragment) a relation **based on conditions (predicates) defined on another related relation**.

It’s **derived** because the fragmentation of one relation is *derived* from the fragmentation of another relation — usually using a **foreign key relationship**.

---

**Example:**

Suppose you have:

```
DEPARTMENT(DeptID, DeptName, Location)
EMPLOYEE(EmpID, Name, DeptID)
```

Now, if we first do PHF on `DEPARTMENT`:

```
DEPT_INDIA = σ(Location='India')(DEPARTMENT)
DEPT_USA   = σ(Location='USA')(DEPARTMENT)
```

Then we want to fragment `EMPLOYEE` **based on where their department is located** —

but that info (`Location`) is not in the EMPLOYEE table; it’s in DEPARTMENT.

So we use a **semi-join** to derive the employee fragments:

```
EMP_INDIA = EMPLOYEE ⋉ DEPT_INDIA
EMP_USA   = EMPLOYEE ⋉ DEPT_USA
```

→ This is **Derived Horizontal Fragmentation (DHF)**,

because the EMPLOYEE fragmentation depends on **predicates defined on another relation (DEPARTMENT)**.

 Quick Comparison Table

| Aspect | Primary Horizontal Fragmentation (PHF) | Derived Horizontal Fragmentation (DHF) |
| --- | --- | --- |
| **Predicate Based On** | Attributes of the *same relation* | Attributes of *another related relation* |
| **Relation Used** | Single relation | Two relations (uses foreign key relationship) |
| **Operation Used** | Selection (σ) | Semi-join (⋉) |
| **Example** | Split EMPLOYEE by its own Location | Split EMPLOYEE by DEPARTMENT’s Location |
| **Purpose** | Directly partition data for locality | Keep related tuples together across relation |

---

### B. VERTICAL FRAGMENTATION

Dividing a relation by columns (attributes). Each fragment contains a subset of attributes.

**Definition:** If R{A₁, A₂, ..., Aₙ} is a relation, vertical fragmentation produces:

- R₁{A₁, A₂, ..., Aᵢ, Key}
- R₂{Aᵢ₊₁, ..., Aⱼ, Key}
- Primary key appears in all fragments (for reconstruction)

**Example:**

Original Relation: **EMPLOYEE**

<a href="https://ibb.co/991hfPdz"><img src="https://i.ibb.co/3yjv8KPG/image.png" alt="image" border="0"></a>

**Vertical Fragmentation:**

**Fragment 1 (Public Info - All sites):**

`EMP_PUBLIC = π(EmpID, Name, Address, Phone)(EMPLOYEE)`

<a href="https://ibb.co/S4G1DBGD"><img src="https://i.ibb.co/39Q85cQ5/image.png" alt="image" border="0"></a>

**Fragment 2 (Financial Info - Restricted site):**

`EMP_FINANCE = π(EmpID, Salary, TaxInfo, BankAccount)(EMPLOYEE)`

<a href="https://imgbb.com/"><img src="https://i.ibb.co/s9QbKt26/image.png" alt="image" border="0"></a>
**Reconstruction:**

`EMPLOYEE = EMP_PUBLIC ⋈ EMP_FINANCE`

(Natural join on EmpID)

**Advantages of Vertical Fragmentation:**

- Better security (sensitive attributes isolated)
- Reduced I/O for queries needing few attributes
- Tuples are smaller, more fit in memory
- Parallel execution possible

### C. MIXED/HYBRID FRAGMENTATION

Combination of horizontal and vertical fragmentation applied successively.

**Example:**

**Step 1:** Vertical Fragmentation

`EMPLOYEE → EMP_PUBLIC, EMP_FINANCE`

**Step 2:** Horizontal Fragmentation on EMP_PUBLIC

`EMP_PUBLIC → EMP_PUBLIC_DELHI, EMP_PUBLIC_MUMBAI`

**Result:** Three fragments total

- EMP_PUBLIC_DELHI
- EMP_PUBLIC_MUMBAI
- EMP_FINANCE (centralized)

**Reconstruction:**

```java
EMP_PUBLIC = EMP_PUBLIC_DELHI ∪ EMP_PUBLIC_MUMBAI

EMPLOYEE = EMP_PUBLIC ⋈ EMP_FINANCE
```

---

### **Fragmentation Design Considerations**

When designing fragmentation in a distributed database system (DDBS), the goal is to **improve performance, availability, and locality of reference** while maintaining **data integrity and minimal redundancy**.

To achieve this, several **factors** must be analyzed carefully before deciding how to fragment data — whether horizontally or vertically.

### **1. Application Analysis**

Before deciding any fragmentation strategy, we must understand **how applications use the data**.

**a. Query Patterns and Frequencies**

- Analyze which queries are executed most often.
- Identify attributes used in `WHERE` clauses and `JOIN` conditions.
- Example: If 80% of queries on the `Employee` table use `WHERE region="north"`, horizontal fragmentation by `region` is beneficial.

**b. Update Patterns**

- Study how frequently data is inserted, updated, or deleted.
- High update frequency on a particular fragment can lead to higher communication costs if the fragment is distributed inefficiently.
- Example: If salary updates happen frequently across all regions, then vertical fragmentation (keeping salary attributes together) can optimize performance.

**c. Site Access Patterns**

- Determine **which sites (nodes)** access which parts of the database most frequently.
- Place fragments closer to the site that accesses them often (data locality).
- Example: Delhi branch accesses only North region employees → store that fragment at the Delhi site.

---

### **2. Predicate Selection (for Horizontal Fragmentation)**

Horizontal fragmentation divides a relation into **tuples (rows)** based on **predicates** applied to attributes.

**a. Based on Query Predicates**

- The predicates used in queries (especially in `WHERE` clauses) are ideal candidates for fragmentation.
- Example:
    
    `WHERE region = 'North'` → fragment by region.
    

**b. High Selectivity**

- Chosen predicates should divide data **evenly** and **selectively**, avoiding very small or very large fragments.
- Ensures load balancing across sites.

**c. Minimal Overlap**

- Fragments should be **mutually exclusive** to prevent redundant data storage.
- Each tuple should belong to exactly one fragment.

---

### **3. Attribute Grouping (for Vertical Fragmentation)**

Vertical fragmentation divides a relation by **columns (attributes)**, ensuring that each fragment contains the **primary key** to enable reconstruction.

> Affinity means: a natural liking for and understanding of someone or something.
> 

**a. Affinity Analysis**

- Identify which attributes are **accessed together** in the same queries or transactions.

**b. Affinity Matrix**

- Construct an **affinity matrix** showing the co-access frequency between attributes.
- Example:

| Attributes | Name | Dept | Salary | Address |
| --- | --- | --- | --- | --- |
| Name | — | 0.8 | 0.1 | 0.9 |
| Dept | 0.8 | — | 0.5 | 0.2 |
| Salary | 0.1 | 0.5 | — | 0.1 |
- From this matrix, group attributes with **high affinity values** (e.g., `{Name, Address}` together and `{Dept, Salary}` together).

**c. Group Highly Affiliated Attributes**

- Grouping attributes that are often used together reduces join costs and improves query response time.

---

### **4. Cost Model Considerations**

Fragmentation design must also be guided by a **cost model**, which estimates various system costs.

**a. Storage Cost**

- Cost to store fragments on different sites.
- Influenced by replication, indexing, and hardware capacity.

**b. Query Processing Cost**

- Depends on how much data needs to be transmitted and joined across fragments.
- Fragmentation should minimize inter-site joins.

**c. Update Cost**

- Frequent updates on distributed fragments can lead to synchronization overhead.
- Keep frequently updated data localised.

**d. Communication Cost**

- Includes cost of transferring data between sites for query execution or updates.
- Good fragmentation minimises remote data access.

---

## 3. ALLOCATION

After deciding **how to fragment** the data (horizontal or vertical), the next logical question is:

> “Where should each fragment be placed in the distributed system?”
> 

This step is called **Allocation** — it determines **which site (or sites)** will hold which fragment(s).

The main goal is to:

- **Reduce communication costs**
- **Improve locality and availability**, and
- **Balance load** across the network.

### 3.1 ALLOCATION ALTERNATIVES

There are three main allocation approaches depending on how redundancy (replication) is used.

**3.1.1 Non-Replicated Allocation**

- Each **fragment is stored at exactly one site.**
- **No duplication** (no replicas).

**Advantages**

- Minimal storage cost.
- No need to synchronize updates (only one copy).

**Disadvantages**

- Low availability → if that site fails, data becomes inaccessible.
- Users from other sites have to **fetch data remotely**, increasing communication cost.

### Example:

Employee data divided regionally:

- `Emp_North` → Delhi site
- `Emp_South` → Chennai site

Each fragment is **unique** to a single site.

---

**3.1.2 Replicated Allocation**

Some or all fragments are stored at multiple sites.

There are two types:

**a. Fully Replicated**

- Every site has **a complete copy** of the database.

Advantages:

- Very high availability — if one site fails, others can still serve requests.
- Reads are **local** and fast.

Disadvantages:

- Very high storage cost.
- Updates must propagate to all copies (expensive synchronization).

**b. Partially Replicated**

- Only some fragments are replicated — **strategically** based on access frequency.

Advantages:

- Balances availability and cost.
- Often used in real systems.

Example:

- Employee personal data replicated at all branches (frequently read).
- Payroll data stored only at HQ (less frequently read, often updated).

---

### 3.2 ALLOCATION STRATEGIES (Factors Influencing Placement)

When deciding **where** to place each fragment or replica, the following factors guide the decision:

**1. Locality of Reference**

- Place fragments where they are most frequently accessed.
- Reduces network latency and data transfer costs.

Example: If the Delhi branch queries only North-region employees → store `Emp_North` in Delhi.

**2. Reliability Requirements**

- Critical data (e.g., financial transactions, logs) should be **replicated**.
- Ensures **availability even if one site fails.**

Example: Transaction logs replicated across multiple servers for fault tolerance.

> If the transaction log is stored only on one server, and that server crashes →
you lose the entire record of recent transactions = data loss. So, we replicate the transaction log (e.g., to 2–3 servers).
> 

**3. Available Storage**

- Each site has limited storage.
- Ensure total size of allocated fragments ≤ site capacity.

Also: distribute data so no single site is overloaded.

**4. Communication Costs**

- Dependent on **network bandwidth** and **inter-site latency**.
- Place heavily accessed fragments closer to their frequent users.
- Avoid inter-site joins.

**5. Processing Capabilities**

- If some sites have stronger CPUs, assign them compute-heavy fragments.
- Load balancing ensures optimal query performance.

> Some nodes are used in **aggregations, joins, analytics** — requiring **high CPU** and **memory**
> 
> 
> These are called **compute-heavy fragments**.
> 

---

### 3.3 ALLOCATION MODELS

Allocation can be formulated mathematically as a **File Allocation Model (FAM)** — a kind of optimization problem.

<a href="https://ibb.co/B5bzWyYv"><img src="https://i.ibb.co/rRY78xXq/image.png" alt="image" border="0"></a>
<a href="https://ibb.co/SDf2k7db"><img src="https://i.ibb.co/9mZJx3V6/image.png" alt="image" border="0"></a><br /><a target='_blank' href='https://imgbb.com/'></a>



### **Interpretation:**

You choose the combination of fragments and sites that:

- Minimizes total cost
- Respects capacity limits
- Ensures each fragment is present somewhere

 In real systems, this is solved using **linear programming** or **heuristic algorithms** (since it’s NP-hard).

---

### 3.4 REPLICATION STRATEGIES

Replication increases availability, but creates **consistency management** challenges.

These strategies define **how reads and writes** are coordinated across replicas.

### **1.Read-One-Write-All (ROWA)**

- **Read:** any one replica (fast)
- **Write:** must update **all replicas** synchronously

Advantage:

- Strong consistency — all copies are identical.

Disadvantage:

- Low availability — if *any* site is down, writes fail.

**Use case:** banking, financial systems (strict consistency needed)

### **2. Majority Consensus (Quorum-Based)**

- To perform an operation:
    - **Read** requires majority of replicas (`R` votes)
    - **Write** requires majority (`W` votes)
    - Must ensure `R + W > N` (where `N` = total replicas)

 Advantage:

- Can still operate even if some sites fail.
- Consistency is guaranteed through quorum overlap.

Disadvantage:

- More complex coordination and latency.

```java
lets say we have, N = 5 nodes

acc to majority consensus approach we (R + W > N) must satisfy

let, R=1
		 W=2
3 > 5 (no, fail)

reading from 1 and writing to 2 will still....in this 3 of the nodes are pending and reading from any 1 of them results in failure

let, R=2
		 W=3

5 > 5 (no, fail)

reading from 2 and writing to 3 will still....in this 2 of the nodes are not updated and since we reading from 2 these 2 can be those so results are inconsistent

R=3
W=3

3 votes from nodes while reading a value and 3 votes from nodes while writing a value..

3 + 3 > 5
6 > 5 (correct)

here writing on 3 so only 2 nodes are left with old values, so we are reading from 3 nodes and even if 2 left nodes are with old data 1 is with new data
```

**how does system handles when different values are returned while reading from multiple nodes (for same value, as seen in above case ) ?**

 ***Explaination:*** 

You have 5 replicas of a data item:

S1, S2, S3, S4, S5

**Write Operation:**

- A write is successful only if **3 out of 5 replicas** acknowledge the write.
- Suppose you write new value `X = 50` to **S1, S2, S3**.

Now, S1–S3 = new value (50)

S4–S5 = old value (40)

**Read Operation:**

- A read must contact **3 replicas** (R = 3).
- Let’s say you randomly read from S3, S4, and S5.

You’ll receive:

- S3 → 50 (new)
- S4 → 40 (old)
- S5 → 40 (old)

So you have **mixed versions**.

In quorum-based systems:

- Each replica stores a **version number** (timestamp or logical clock).
- During read, the system picks the **most recent version** based on this timestamp.

So, in our case:

- The version from S3 (newer timestamp) is chosen as correct.
- The system may **asynchronously update** the stale replicas (S4, S5) afterward.

### 3. **Primary Copy**

- One site is designated as the **primary** for each fragment. (other sites are secondary)
- **All writes** go through the primary (i.e The primary updates its local copy → then propagates the update to other replicas asynchronously or synchronously.)
- **Reads** can go to any copy (local or primary).

Advantage:

- Simpler update management — only one site controls writes.

 Disadvantage:

- *If the primary fails, updates pause until a new primary is elected.*

---

## 4. DATABASE INTEGRATION

Integration combines multiple heterogeneous databases into a unified system.

### 4.1 Schema Matching

**Schema Matching** identifies semantically equivalent elements across different schemas.

**Types of Conflicts:**

**1. Naming Conflicts**

**a) Synonyms:** Different names, same meaning

- Example:
    - Schema1: `EmpNo`
    - Schema2: `EmployeeID`
    - **Resolution:** Choose standard name or create mapping

**b) Homonyms:** Same name, different meaning

- Example:
    - Schema1: `Date` (Date of birth)
    - Schema2: `Date` (Hire date)
    - **Resolution:** Rename with context: `BirthDate`, `HireDate`

**2. Structural Conflicts**

**a) Type Conflicts:** Same entity, different structures

- Example:
    - Schema1: `Address` as single attribute
    - Schema2: `Street`, `City`, `Zip` as separate attributes
    - **Resolution:** Decompose or compose as needed

**b) Dependency Conflicts:** Different integrity constraints

- Example:
    - Schema1: `Age` derived from birthdate
    - Schema2: `Age` stored explicitly
    - **Resolution:** Define derivation rules

**3. Semantic Conflicts**

**a) Domain Mismatches:** Different data types or ranges

- Example:
    - Schema1: `Salary` in USD
    - Schema2: `Salary` in INR
    - **Resolution:** Conversion functions

**b) Constraint Mismatches:** Different rules

- Example:
    - Schema1: Salary range 30000-100000
    - Schema2: Salary range 20000-80000
    - **Resolution:** Relax or reconcile constraints

### 4.2 Schema Integration Process — Deep Dive

Schema integration is the process of **merging multiple local schemas** (from different databases or departments) into a **single, unified global schema** that eliminates redundancy and resolves inconsistencies.

eg. 

```java
*Schema 1 (HR Database):*
EMPLOYEE(EmpID, Name, DeptCode, Salary)
DEPARTMENT(DeptCode, DeptName, Location)

*Schema 2 (Payroll Database):*
sqlWORKER(WorkerNo, FullName, Division, Pay)
DIVISION(DivCode, DivName)

these are the 2 dbs we need to created a mapping type integrated schema for these 2
```

**Step 1: Pre-Integration**

Goal: Prepare for schema integration by analyzing what needs to be merged and how.

Activities:

- Identify the **schemas** to integrate (e.g., HR, Payroll, Finance).
- Establish **correspondence assertions** — i.e., which attributes/tables are “the same” or “related.”
    - Example: `EmpID` in HR ↔ `WorkerNo` in Payroll
- Choose an **integration strategy**:
    - **Binary Integration:** Merge 2 schemas at a time.
    - **N-ary Integration:** Merge all at once.
    - **Iterative Integration:** Merge pair by pair gradually (common in large orgs).

**Example:**

> HR and Payroll databases both maintain employee info → we decide to integrate HR first with Payroll, then later with Finance.
> 

We’ll do **correspondence assertions** — i.e., we note which attributes/entities are equivalent.

| HR Schema Element | Payroll Schema Element | Relationship |
| --- | --- | --- |
| `EMPLOYEE` | `WORKER` | Same entity (Employee) |
| `EmpID` | `WorkerNo` | Same identifier |
| `Name` | `FullName` | Same concept |
| `DeptCode` | `Division` | Refers to department/division |
| `Salary` | `Pay` | Same concept (may need currency conversion) |
| `DEPARTMENT` | `DIVISION` | Same entity |
| `DeptCode` | `DivCode` | Same identifier |
| `DeptName` | `DivName` | Same concept |
| `Location` | — | Attribute only in HR schema |

***Step 2: Comparison***

Goal: Identify conflicts and relationships between schemas.

Types of conflicts:

1. **Naming conflicts**
    
    `EmpID vs WorkerNo`, `DeptCode vs DivCode` ,`Salary vs Pay`
    resolution: we can Standardize names to resolve this
    
2. **Structural conflicts**
    
    HR’s `DeptCode vs Payroll’s` Division (foreign key)
    resolution: Make both refer to `DepartmentCode`
    
3. **Semantic conflicts**
    
    `Pay` may be in different currency units
    resolution: Convert to standard format
    
4. **Attribute Presence**
    
    Location exists only in HR
    Keep it, mark as optional
    

***Step 3: Conformation (Align Structures)***

**Goal:** Resolve conflicts and align structures.

We now **align** the attributes, standardize names, and ensure the relationships match.

After conformation, we have these **aligned entities**:

EMPLOYEE (conceptual)

| Field | From | Notes |
| --- | --- | --- |
| EmployeeID | EmpID / WorkerNo | Unified name |
| EmployeeName | Name / FullName | Unified name |
| DepartmentCode | DeptCode / Division | Unified link |
| Salary | Salary / Pay | Unified name and units |

DEPARTMENT (conceptual)

| Field | From | Notes |
| --- | --- | --- |
| DepartmentCode | DeptCode / DivCode | Unified identifier |
| DepartmentName | DeptName / DivName | Unified name |
| Location | From HR | Optional attribute |

---

***Step 4: Merging & Restructuring → The Integrated Schema***

Now we merge them into the **final integrated schema** 👇

```sql
EMPLOYEE(EmployeeID, EmployeeName, DepartmentCode, Salary)
  -- Mapping:
  -- EmpID / WorkerNo → EmployeeID
  -- Name / FullName → EmployeeName
  -- Salary / Pay → Salary

DEPARTMENT(DepartmentCode, DepartmentName, Location)
  -- Mapping:
  -- DeptCode / DivCode → DepartmentCode
  -- DeptName / DivName → DepartmentName

```

Relationships:

```sql
FOREIGN KEY (DepartmentCode) REFERENCES DEPARTMENT(DepartmentCode)
```

> If Payroll had salaries in USD and HR in INR → the integrated schema includes a currency normalization rule.
> 

***Question: How this Integrated Schema will be used ? Is this only conceptual (only for mapping purpose stored in dictionary) or this integrated schema is what will be stored in db ?***

**The Truth About the “Integrated Schema”**

The integrated (global) schema does not necessarily replace the original local schemas.

- The **original local databases remain as they are,** and
- The **integrated schema acts as a “virtual global view”**

***Use Case of Integrated Schema*** 

- Each local database keeps its **own schema**, structure, and data (HR, Payroll, etc.).
- The integrated schema is **logical**, not physical — it’s defined in a **global data dictionary or catalog**.
- When a user queries the global schema, the system **translates** that query into sub-queries for the local schemas. (using this integrated schema)

A **Global Schema** is defined in the distributed DBMS catalog.

eg. when user does 

```java
SELECT EmployeeName, Salary FROM EMPLOYEE;
```

- The system automatically fetches data from **both the original data bases the `HR and Payroll`**,
- Translates it according to the mappings,
- Merges the results to return a **unified view**. and shows it to the user

> The **integrated (global) schema** is a **logical view** that provides users with a **single, unified interface** to query data that is actually stored across multiple autonomous local databases.
> 

---

---

### 4.3 Schema Mapping

We had:

- **HR DB:** `EMPLOYEE(EmpID, Name, DeptCode, Salary)`
- **Payroll DB:** `WORKER(WorkerNo, FullName, Division, Pay)`

After **schema integration**, we designed an **integrated (global)** schema:

```sql
EMPLOYEE(EmployeeID, EmployeeName, DepartmentCode, Salary)
```

and

```sql
DEPARTMENT(DepartmentCode, DepartmentName, Location)
```

Now, we’ll define **how this global schema is linked (mapped)** to the **local schemas** using **Schema Mapping techniques**.

---

**1. Global-as-View (GAV)**

In **GAV**, the *global schema* is defined as *a view over local schemas*.

So the global schema doesn’t have its own data — it just **derives** from local sources.

```sql
-- Global Schema
GLOBAL_EMPLOYEE(ID, Name, Dept, Salary)

-- Mapping (views defined over local sources)
CREATE VIEW GLOBAL_EMPLOYEE AS
SELECT EmpID AS ID, Name, DeptCode AS Dept, Salary
FROM HR.EMPLOYEE
UNION
SELECT WorkerNo AS ID, FullName AS Name, Division AS Dept, Pay AS Salary
FROM PAYROLL.WORKER;

```

Interpretation:

- `GLOBAL_EMPLOYEE` is a *virtual table* created by combining both databases.
- When the user queries `GLOBAL_EMPLOYEE`, the system fetches data from both `HR.EMPLOYEE` and `PAYROLL.WORKER`.

Advantages

- Easy for query processing (direct expansion).

Disadvantage

- Hard to add new data sources — you must change the view definition every time.

**2. Local-as-View (LAV)**

In **LAV**, *local schemas* are defined as *views over the global schema*.

Here, the **global schema is independent**, and local sources tell how their data relates to it.

Example:

```sql
-- Global Schema
GLOBAL_EMPLOYEE(ID, Name, Dept, Salary)

-- Local schema mappings (each as a view over the global schema)
CREATE VIEW HR.EMPLOYEE AS
SELECT ID AS EmpID, Name, Dept AS DeptCode, Salary
FROM GLOBAL_EMPLOYEE
WHERE Dept LIKE 'HR%';

CREATE VIEW PAYROLL.WORKER AS
SELECT ID AS WorkerNo, Name AS FullName, Dept AS Division, Salary AS Pay
FROM GLOBAL_EMPLOYEE
WHERE Dept LIKE 'PAY%';

```

Interpretation:

- Here the **global schema is the base truth**, and local schemas depend on it.
- To answer queries, the system needs to figure out **which local data contributes to which global data** — that’s why **query rewriting** is complex.

*Advantage*

- Adding new data sources is easy (just define a new view).

Disadvantage

- Query processing is more complex.

---

**3. GLAV (Hybrid)**

In **GLAV**, some parts are GAV-like, others LAV-like.

You can map global and local schemas flexibly — one-to-many or many-to-one.

Example rule:

```sql
GLOBAL_EMPLOYEE(ID, Name, Dept, Salary) ↔
   HR.EMPLOYEE(EmpID, Name, DeptCode, Salary)
   AND PAYROLL.WORKER(WorkerNo, FullName, Division, Pay)
```

This says:

Each `GLOBAL_EMPLOYEE` record corresponds to matching records in both HR and Payroll systems, but the exact mapping may use transformation rules or constraints.

---

## 5. DATA AND ACCESS CONTROL

**5.1 View Management in Distributed Databases**

What are Views in a Distributed DBMS?
A **view** is a *logical representation* of data — it doesn’t physically store the data (unless materialized).

In distributed systems, **views help hide data distribution** and control **what each site or user can see**.
**Types of Views**

- **1. Local Views**
• Defined **at each individual site** (node).
• They are based on **local fragments** of data stored at that site.
• Used for **site-specific access control** (e.g., a Delhi manager can see only Delhi employees).
Example:

```java
CREATE VIEW DELHI_EMP_VIEW AS
SELECT EmpID, Name, Salary
FROM EMP_DELHI
WHERE Dept = 'Sales';
```

Only uses data from **EMP_DELHI** (local fragment).
****

- **2. Global Views**
• Defined **over the entire distributed database** (across all sites).
• Provide a **unified interface** for users — they don’t need to know where data is stored.
• DBMS handles distributed query processing automatically.
Example:

```java
CREATE VIEW ALL_EMPLOYEES AS
SELECT * FROM EMP_DELHI
UNION
SELECT * FROM EMP_MUMBAI
```

 A global user can query `ALL_EMPLOYEES` without knowing about `EMP_DELHI` or `EMP_MUMBAI` tables.
****

**Why are Views Important?**

- **Logical Data Independence:** Physical location or fragmentation of data can change, but user queries on views don’t break.
- **Access Control:** Restrict user access to specific columns or rows via views.
- **Simplified Queries:** Provide pre-joined or filtered datasets.

**View Management Challenges**

**1.View Materialization**

There are **two strategies** for implementing views:

| Type | Definition | Advantage | Disadvantage |
| --- | --- | --- | --- |
| **Materialized View** | Data is **precomputed and stored** physically | Fast query response | Must be updated when base data changes |
| **Virtual View** | Data is **computed on demand** when queried | Always current | Slower due to recomputation |

```sql
-- Materialized (stored)
CREATE MATERIALIZED VIEW HIGH_SALARY AS
SELECT * FROM EMPLOYEE WHERE SALARY > 70000;

-- Virtual (computed on the fly)
CREATE VIEW HIGH_SALARY AS
SELECT * FROM EMPLOYEE WHERE SALARY > 70000;
```

**2. Distributed View Update Problem**
Updating data **through a view** in a distributed setup is complex —

because the **view may combine data from multiple fragments (sites).**
**Example:**

```sql
-- Global View
CREATE VIEW HIGH_EARNERS AS
SELECT EmpID, Name, Salary
FROM EMP_DELHI
UNION
SELECT EmpID, Name, Salary  
FROM EMP_MUMBAI
WHERE Salary > 70000;

-- Update through the view
UPDATE HIGH_EARNERS
SET Salary = Salary * 1.1
WHERE EmpID = 'E01';
```

**Problem:**

- Which site holds `EmpID = 'E01'`? Delhi or Mumbai?
- The system must:
    1. Locate the correct fragment.
    2. Apply the update there.
    3. Propagate changes if needed (e.g., materialized views).

This is known as the **distributed view update problem** —

maintaining **consistency across multiple sites** when data is updated through a global view. so in this case with searching with employee id the joins will be made and DBMS will search internally using joins and check where is this stored

## 5.2 DATA SECURITY IN DISTRIBUTED DATABASES

Security in DDBs is much more challenging than in centralized databases because:

- Data is **spread across multiple sites**
- Each site may use **different DBMSs or OSs**
- Data travels **over networks**
- **Different users** may access **different fragments**

So, we need to ensure **consistent, end-to-end security**.

**SECURITY REQUIREMENTS (what we must guarantee)**

| Security Goal | Meaning | Example |
| --- | --- | --- |
| **Authentication** | Verify that the user is who they claim to be | Login with valid credentials, Kerberos ticket, etc. |
| **Authorization** | Define what operations the user can do | User A can only `SELECT`, not `UPDATE` salary data |
| **Confidentiality** | Keep data secret from unauthorized users | Encrypt employee salary or transmit via TLS |
| **Integrity** | Ensure data is accurate and unaltered | No unauthorized user can modify records |
| **Auditability** | Keep a record of who accessed or changed data | Log all actions for later analysis or rollback |

**SECURITY CHALLENGES IN DISTRIBUTED DBs** 

### ***1. Distributed Authentication***

Since users may log in at any site, authentication must work **across the entire system**.

Example:

- You log in to the **Delhi site**.
- You should not be prompted again when querying data from **Mumbai**.

Solution:

- Use **Single Sign-On (SSO)**.
- Common protocols:
    - **Kerberos** (ticket-based trusted authentication)
    - **LDAP** (centralized directory for user identities)
    - **OAuth / JWT tokens** for modern APIs

**Analogy:**

Think of Kerberos as a “security passport” — you show it once, and you can visit all offices in the organization.

### **2. Authorization at Multiple Levels**

Once authenticated, the DBMS decides **what you are allowed to do**.

In distributed databases, access control can apply at **three levels** 

**(a) Global Level Authorization**

You define access rights for the entire distributed schema.

```sql
GRANT SELECT ON GLOBAL_EMPLOYEE TO user1;
```

Meaning:

- user1 can query from *any site* that contributes to the `GLOBAL_EMPLOYEE` view.

Use Case: System admin, auditor, etc.

**(b) Fragment-Level Authorization**

You restrict access to *specific sites or fragments*.

```sql
GRANT SELECT ON EMP_DELHI TO user2;
```

Meaning:

- user2 can only see data stored in the Delhi fragment.
- user2 cannot see employees in the Mumbai site.

Use Case: Regional HR manager only sees their region’s data.

**(c) Attribute-Level Authorization**

Sometimes even within a table, some columns are confidential.

```sql
CREATE VIEW EMP_PUBLIC AS
SELECT EmpID, Name FROM EMPLOYEE;
GRANT SELECT ON EMP_PUBLIC TO user3;
```

Meaning:

- user3 can see only `EmpID` and `Name`.
- They can’t view salary or department.

Use Case: Intern or external contractor.

### **3) Inference Control (Hidden Danger)**

Even if you restrict access, someone might **infer** private data indirectly.

**Example:**

You don’t allow users to view salaries.

But they can see **tax paid** — and by observing tax brackets, they can guess approximate salaries.

**Solution:**

- Statistical disclosure control (rounding, data suppression, noise addition)
- Query restriction (deny overly specific queries)
- Data generalization (show ranges instead of exact values)

---

### 4) Network Security (Data in Transit)

When nodes communicate across networks:

- Data (queries, results, updates) travels between sites
- Attackers could **intercept** or **modify** packets

**Solutions:**

- Use **SSL/TLS** for DB connections
- Use **VPNs** for site-to-site traffic
- Apply **end-to-end encryption** for sensitive payloads
- Use **digital signatures** to prevent tampering

**Analogy:**

Just like encrypting an email between two offices — no one in between can read it.

---

### 5) Multilevel Security (MLS)

Used in military or highly confidential databases — where users and data have **security levels**.

| Security Level | Example |
| --- | --- |
| Top Secret | Intelligence data |
| Secret | Employee details |
| Confidential | Sales reports |
| Unclassified | Public data |

**Rule:**

Users can *read down* but not *read up* (no access to higher security data).

Users can *write up* but not *write down* (to avoid data leaks).

---

### → Polyinstantiation:

This is a mechanism to prevent **covert channels** (sneaky data leaks).

If two users with different security levels query the same key (say EmpID = 101),

they might get **different tuples** depending on their clearance.

Example:

| EmpID | Name | Salary | Security Level |
| --- | --- | --- | --- |
| 101 | Alice | 120000 | Top Secret |
| 101 | Alice | 70000 | Confidential |

So:

- A **Confidential** user sees: `Alice earns 70k`
- A **Top Secret** user sees: `Alice earns 120k`

This avoids the system having to reveal that “there’s more data” at higher levels.

terminologies:  (read about them)

- **Kerberos**
- **SSL/TLS** for DB connections
- Apply **end-to-end encryption** for sensitive payloads
- Use **digital signatures** to prevent tampering

---

---

## 5.3 SEMANTIC INTEGRITY CONTROL

What It Means

**Semantic integrity** ensures that *data always obeys real-world rules or business logic* — even when it’s distributed across multiple sites.

In simpler words:

> “The database should never contain something that violates the organization’s policies.”
> 

Example business rule:

> Employee salary must be within a valid range,
> 
> 
> Each EmpID must be unique globally,
> 
> Each employee in WORKS_ON must exist in EMPLOYEE.
> 

### TYPES OF INTEGRITY CONSTRAINTS

### 1️⃣ Intra-Fragment Constraints

These apply **within a single fragment** (single site).

They’re just like constraints in a centralized DB — easy to enforce locally.

Example:

```sql
ALTER TABLE EMP_DELHI
ADD CONSTRAINT salary_range CHECK (Salary BETWEEN 30000 AND 150000);
```

- Enforced by **local DBMS** (Delhi site only)
- Doesn’t need communication with other sites
- Includes constraints like:
    - Domain constraints (`CHECK`, `NOT NULL`)
    - Primary keys / unique constraints *within the fragment*

 **Advantage:**

Local and efficient.

 **Limitation:**

Cannot ensure global correctness.

### 2️⃣ Inter-Fragment Constraints

These apply **across multiple fragments**, like EMP_DELHI and EMP_MUMBAI.

Example Rule:

> Each EmpID must be unique globally.
> 

Now, enforcing this means:

- When inserting into `EMP_DELHI`, you must check that the same EmpID doesn’t already exist in `EMP_MUMBAI` (remote site).
- This requires **communication** between sites before confirming the insert.

 Ensures **global correctness**

 Causes **network overhead** and **latency**

### 3️⃣ Referential Integrity

Deals with **relationships between tables** (foreign key constraints).

**(a) Co-located Fragments**

If related tables are on the **same site**, it’s simple.

```sql
ALTER TABLE WORKS_ON
ADD FOREIGN KEY (EmpID) REFERENCES EMPLOYEE(EmpID);
```

→ Enforced by local DBMS automatically.

**(b) Distributed Fragments**

Now, suppose:

| Table | Site | Description |
| --- | --- | --- |
| EMPLOYEE | Site 1 | Employee master |
| PROJECT | Site 2 | Project master |
| WORKS_ON | Site 3 | Relationship between EMPLOYEE and PROJECT |

Now when you insert a record into `WORKS_ON`:

```sql
INSERT INTO WORKS_ON VALUES ('E01', 'P01');
```

To enforce referential integrity:

1. Site 3 must check if `'E01'` exists in `EMPLOYEE` (Site 1)
2. Check if `'P01'` exists in `PROJECT` (Site 2)
3. Insert only if both exist.

This requires **distributed checks** before commit.

- Ensures correctness across DBs
- But is, Slow due to network round trips

**Your Job: Defining the Rule (The "What")**
You define the foreign key constraint using the exact same standard SQL command, regardless of where the tables are located. You would still run commands like:

SQL

```sql
-- This command is run once to define the relationship
-- defining relationship between the site1 Employee table and site 3 works_on table
ALTER TABLE WORKS_ON
ADD CONSTRAINT FK_WorksOn_Employee
FOREIGN KEY (EmpID) REFERENCES EMPLOYEE(EmpID);

-- defining relationship between the site2 Project table and site 3 works_on table
ALTER TABLE WORKS_ON
ADD CONSTRAINT FK_WorksOn_Project
FOREIGN KEY (ProjID) REFERENCES PROJECT(ProjID);
```

When you run this, you are telling the DDBMS's **global data dictionary** (or catalog) about the rule. The database now knows, "The `EmpID` in `WORKS_ON` *must* refer to an `EmpID` in `EMPLOYEE`." It stores this rule as part of the overall database schema.

---

## ENFORCEMENT STRATEGIES

these strategy defines how fast query will be resolved, in synchronous enforcement every check and processing is done 1 by 1 while in async enforcement the constraint checking may be delayed and lazy. (resulting in fast query results

### **1️⃣ Synchronous Enforcement**

- All constraint checks are performed **before transaction commit**
- Usually via **2-Phase Commit (2PC)** protocol

→ Strong consistency

→ Slower (blocking + network delay)

Example: Bank transfer validation between two branches before money moves.

Think of this as the **"do it right, right now"** approach. The database will not confirm your action until it has verified that the action follows all the rules, even if that means checking with other remote sites and making you wait.

***Example: Inter-Branch Bank Transfer***

Imagine you want to transfer ₹10,000 from your account at the **Mumbai** branch to a friend's account at the **Bengaluru** branch.

The critical constraint is that your account balance cannot go below zero. Here's how synchronous enforcement works using a 2-Phase Commit:

1. **Initiation:** You submit the transfer request at the Mumbai branch (or its app). The Mumbai site becomes the **Coordinator**.
2. **Phase 1: Prepare (Voting)**
    - The **Mumbai site** first checks your balance. It's ₹15,000. Good. It then *locks* your account, "prepares" to deduct ₹10,000, and votes **"YES"** to proceed.
    - It sends a "prepare" message over the network to the **Bengaluru site**. The **Bengaluru site** checks if your friend's account exists and is active. It is. It then *locks* that account, votes **"YES"** back to Mumbai.
3. **Phase 2: Commit**
    - The Mumbai coordinator has received "YES" votes from all participants (in this case, just Bengaluru). It makes the final decision: **COMMIT**.
    - It sends a "commit" command to both itself and the Bengaluru site. The Mumbai site permanently deducts the ₹10,000 and releases the lock. The Bengaluru site permanently adds the ₹10,000 and releases its lock.
4. **Confirmation:** Only after all this is done, you get the "Transfer Successful" message on your screen.
- **Result:** The transaction is perfectly consistent. It's impossible for the money to be deducted from your account but not credited to your friend's.
- **Downside:** You had to wait while the Mumbai and Bengaluru sites communicated and coordinated. This network delay and locking process made the operation **slower**.

### **2️⃣ Asynchronous Enforcement**

- Constraints are checked **after commit** (periodically or lazily)
- Temporary violations allowed, fixed later

→ Faster performance

→ Temporary inconsistency possible

Example: New employee added to Delhi site; global uniqueness check happens later overnight.

Think of this as the **"trust but verify later"** approach. The system processes your request immediately to give you a fast response and deals with any rule violations later.

***Example: Assigning a New Globally Unique Employee ID***

Imagine a large company where new employees are hired at local offices (**Delhi**, **Mumbai**, **Bengaluru**). The rule is that every employee ID must be unique across the entire global company.

1. **Initiation:** An HR manager in the **Delhi** office hires a new employee. The system needs to generate a new ID, say `EMP123`.
2. **Immediate Local Commit:**
    - The Delhi database checks for the uniqueness of `EMP123` *only against its own local records*.
    - Finding no conflict, it immediately **commits** the new employee to the Delhi database. The HR manager ***instantly gets*** a "Success! Employee EMP123 created." message and can proceed with their work.
3. **The "Later" Part (Reconciliation):**
    - The new record (`EMP123`) is added to a queue or log to be replicated to the other sites.
    - A few minutes later (or overnight during a batch process), this information is sent to the Mumbai and Bengaluru sites.
4. **Conflict Detection:** The **Mumbai** database receives the new record and checks it against its own data. It discovers that it *also* created an employee with the ID `EMP123` for a local hire that same day. This is a **constraint violation**.
5. **The "Fix" (Compensating Action):**
    - Since the violation is detected *after* the fact, an automated process must now fix it.
    - The system might automatically flag both `EMP123` records as "conflicted."
    - It could then send an email alert to the HR managers at both the Delhi and Mumbai offices, saying: "ID conflict for EMP123. Please resolve." One of the employees will need to be manually assigned a new ID.
- **Result:** The HR manager in Delhi received a fast response from the system.
- **Downside:** For a short period, the database was in an **inconsistent state**, with two employees having the same ID. This required a separate process to detect and a manual action to fix.

### 3️⃣ Trigger-Based Enforcement

Use triggers to automatically enforce rules (custom rules as per your buisness logic.

Think of this as the **"do it now, but follow my specific, custom rules"** approach. It's a form of synchronous enforcement, but instead of relying on a simple foreign key, you write your own program (the trigger) that runs automatically to check complex conditions before allowing a change.

Example:

```sql
-- A conceptual trigger definition set on site 3 (WORKS_ON) table
-- this trigger function will run before any insert happens in the table
CREATE TRIGGER check_assignment_rules
BEFORE INSERT ON WORKS_ON
FOR EACH ROW
EXECUTE PROCEDURE verify_employee_and_clearance(NEW.EmpID, NEW.ProjID);
```

Here `verify_employee_exists()` might:

- Send a remote query to check in `EMPLOYEE` (Site 1)
- Abort the transaction if employee not found

→ Fine-grained control

→ Still adds communication overhead

***Example: Project Assignment with Security Clearance***

Imagine your company has data spread across three sites:

- **Site 1:** `EMPLOYEE` table (includes `EmpID`, `Name`, and `Status` like 'Active' or 'On Leave').
- **Site 2:** `PROJECT` table (includes `ProjID`, `Name`, and `RequiredClearance` like 'Level 1' or 'Top Secret').
- **Site 3:** `WORKS_ON` table, which links employees to projects.

**The Business Rule:** You can only assign an employee to a project if the employee's status is **'Active'** AND they have the necessary **security clearance** (let's assume that's also stored in the `EMPLOYEE` table for simplicity). A simple foreign key can't check this complex, multi-table logic. So this is where our Trigger Based Enforcement comes into play

Here’s how a trigger handles it:

1. **Setup:** A developer writes a trigger, just like your example, on the `WORKS_ON` table at Site 3. 
2. **Initiation:** A manager tries to assign an employee to a new project by inserting a row into `WORKS_ON: ('E42', 'P07')`.
3. **Trigger Fires:** The database automatically stops the `INSERT` for a moment and executes the trigger's procedure (`verify_employee_and_clearance`).

```java
verify_employee_and_clearance(empId, projectID)
{
	- fetch status and clearance Level for this employee from the other sites
	- if (status = active && employee_clearance >= project_clearance) -> Yes
	- else false
}
```

1. **Remote Checks (Communication):** The procedure running at Site 3 now sends out queries over the network:
    - It asks **Site 1**: "What is the `Status` and `ClearanceLevel` for employee `E42`?" and It asks **Site 2**: "What is the `RequiredClearance` for project `P07`?"
2. **Logic Execution:** The procedure gets the answers back. Let's say Employee E42 is 'Active' with 'Top Secret' clearance, and Project P07 requires 'Top Secret' clearance. The custom logic inside the procedure checks the conditions.
3. **Confirmation or Rejection:**
    - **Success:** Since all custom rules passed, the procedure finishes successfully. The trigger is satisfied, and the original `INSERT` operation is allowed to complete.
    - **Failure:** If the employee was 'On Leave', the procedure would raise an error. The trigger would fail, which **aborts the entire transaction**. The manager would get a specific error message like, "Failed: Employee E42 is not currently active."
- **Result (Fine-grained control):** You enforced a complex business rule that a simple foreign key could never handle.
- **Downside (Communication overhead):** The user had to wait while the trigger performed two separate remote queries. The process is **synchronous and blocking**, adding network latency to the transaction.

## 5.4 SEMANTIC INTEGRITY CONTROL TECHNIQUES

These techniques aim to **enforce integrity efficiently** while minimizing distributed overhead.

---

### 1️⃣ Constraint Compilation

- Translate **global constraints** into **local constraints** wherever possible.
- So instead of checking globally each time, you enforce part of the constraint **locally**.

Example:

Global rule: Salary between 30k–150k for all employees

→ Compile into local rules for each fragment (Delhi, Mumbai).

Pros:

- Less communication
- Local enforcement possible

### 2️⃣ Timestamp Ordering

- Each update/constraint check has a **timestamp**
- The system enforces the order of operations based on timestamps to maintain serializability.

If two updates conflict (same EmpID):

- The one with **earlier timestamp** wins
- Later one must rollback

Pros: Ensures serializable consistency

Con: Adds coordination overhead

### 3️⃣ Snapshot Isolation

- Each transaction sees a **snapshot** of the database at a specific time.
- Constraint checks are done on this snapshot.

Pros:

- Non-blocking reads
- No distributed locks required

Con: May allow “write skew” anomalies (two valid local updates that break a global rule)

**What is “Write skew” ?**

- Both transactions *read old data (snapshot)*
- Both make *independent updates*
- Together they cause *inconsistency*

Example:

We have two accounts — `A` and `B`.

Business rule:

> “Total balance of A + B must always be ≥ 0.”
> 

```sql
-- Initial state:
A = 70
B = 50
(Total = 120)
```

**Two concurrent transactions start,** Both see the **same snapshot**: `A=70, B=50`

| Transaction | Operation | Intention |
| --- | --- | --- |
| **T1** | Withdraw 100 from `A` → sets A = -30 | (Thinks B=50, so total = 20, allowed) |
| **T2** | Withdraw 100 from `B` → sets B = -50 | (Thinks A=70, so total = 20, allowed) |

→ Each transaction checks its rule **based on the snapshot**, and individually both seem fine. But when both commit, Final state in DB:

```
A = -30
B = -50
Total = -80 (**violatation**)
```

This **violates the global constraint**,

even though **each transaction was correct in its own snapshot view**.

### 4️⃣ Escrow Method

Used when constraint involves **aggregate values** (like totals, sums, quotas).

**Example:**

> Total Salary (Delhi + Mumbai) ≤ 1,000,000
> 

You distribute “budget quotas” to sites:

```
Budget = 1,000,000
Delhi Quota = 600,000
Mumbai Quota = 400,000
```

- Delhi site can give raises or hire employees as long as it stays ≤ 600,000.
- No need to communicate with Mumbai for every update.

Reduces cross-site coordination

Pro: Great for performance

Con: Requires periodic rebalancing of quotas

## 6. PRACTICAL CONSIDERATIONS

### 6.1 Design Trade-offs

**Fragmentation Granularity:**

- **Fine-grained:** More fragments, better locality, higher overhead
- **Coarse-grained:** Fewer fragments, less overhead, less optimization

**Replication Degree:**

- **High replication:** Better availability, higher update costs
- **Low replication:** Lower storage, reduced availability

**Autonomy vs. Consistency:**

- **High autonomy:** Local control, potential inconsistency
- **Strong consistency:** Global coordination, reduced autonomy

### 6.2 Design Tools and Methodologies

**Automated Design Tools:**

- Fragment Analyzer: Analyzes access patterns
- Cost Estimator: Predicts query/update costs
- Optimization Algorithms: Genetic algorithms, simulated annealing

**Design Metrics:**

- Response time
- Throughput
- Availability
- Storage utilization
- Network usage