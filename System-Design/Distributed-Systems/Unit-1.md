### Unit-1: Introduction to distributed Systems

Great! Let's begin with **Unit 1: Introduction to Distributed Systems**. This unit covers the foundational concepts of distributed data processing and distributed database systems.

## Overview of Unit 1

Unit 1 focuses on:

- Introduction to distributed data processing and distributed database systems
- Advantages and disadvantages of DDBS
- Types of DDBS
- Promises and Complications in a distributed DBMS
- Distributed DBMS architecture

---

## 1. Introduction to Distributed Systems

### What is a Distributed Database System (DDBS)?

A **Distributed Database System** is a collection of multiple, logically interrelated databases distributed over a computer network. The data is physically stored across multiple sites (nodes), but appears as a single, unified database to users.

**Key Characteristics:**

- Data is distributed across multiple geographic locations
- Each site has its own local database and DBMS
- Sites are connected through a communication network
- Users can access data from any site transparently

### Distributed Data Processing

This involves processing data that is stored at multiple locations. The processing itself can also be distributed across multiple processors or systems.

---

## 2. Advantages of Distributed Database Systems

1. **Improved Performance**: Queries can be processed at local sites, reducing network traffic and response time
2. **Increased Reliability and Availability**: Failure of one site doesn't bring down the entire system
3. **Data Sharing**: Users at different locations can access shared data
4. **Easier Expansion**: New sites can be added without major system redesign
5. **Local Autonomy**: Each site maintains control over local data
6. **Reduced Communication Costs**: Data can be stored closer to where it's used most frequently

---

## 3. Disadvantages of Distributed Database Systems

1. **Complexity**: More complex to design, implement, and maintain
2. **Cost**: Higher initial investment in hardware, software, and network infrastructure
3. **Security Concerns**: Data transmission over networks creates security vulnerabilities
4. **Integrity Control**: Maintaining data consistency across sites is challenging
5. **Concurrency Control**: More complex than centralized systems
6. **Lack of Experience**: Requires specialized knowledge and skills
7. **Database Design Complexity**: Deciding how to fragment and distribute data is difficult

---

## 4. Types of Distributed Database Systems

We can differentiate DDS based on:- 

1. Based on Homogeneity
2. Based on Autonomy

### Based on Homogeneity:

**a) Homogeneous DDBS**

- All sites use the same DBMS software
- Easier to manage and maintain
- Sites appear identical to each other
- Example: All sites running Oracle or all running PostgreSQL

**b) Heterogeneous DDBS**

- Different sites may use different DBMS software
- More complex to integrate
- Requires translation mechanisms
- Example: Some sites running Oracle, others MySQL, others SQL Server

## Homogeneous and Heterogeneous DDBS explained

### Homogeneous DDBS

In a homogeneous distributed database system, it's not just about using the same software (like Oracle on all servers), but also about having a consistent **database schema**.

There are two layers to the "sameness":

- **1. The Same DBMS Software:** Every server or node runs the exact same database program (e.g., MySQL 8.0). This ensures that they all understand the same commands, have the same features, and can communicate without a "translator."
- **2. The Same Database Schema:** For any given table that is distributed across the system, the structure of that table—the columns (`id`, `name`, `firstname`), their data types (integer, var char), and their relationships—is the same on every server that holds a piece of that table.
- Since there are Same Data Base System used on all nodes, so they any query done will directly hit the DB and retriev e results. (no translation needed)

### Heterogeneous DDBS

In a heterogeneous DDBS, different sites may use different DBMS software.

heterogeneous system, you can't just send a single query and expect it to work everywhere. The system needs a "translator" to manage the complexity. This is typically handled by a special layer of software called **middleware.**

- **The Different DBMS Softwares:** Different server or node runs on different database program (e.g., MySQL 8.0, SQL server, Oracle). So they do not understand the same commands, have the different features, and can not communicate without a "translator."
- **Different Database Schema:** In this, the **database schemas at each site are typically different**. This is the fundamental challenge that the system is designed to overcome.
- The entire system is built around managing and reconciling these differences to present the user with what looks like a single, unified database. This is achieved through a two-level schema architecture: **Local Schemas** and a **Global Schema**.

**1. Local Schema**

Each individual database in the distributed system has its own pre-existing structure. This is its **local schema**. These schemas were often designed in isolation, long before there was any plan to connect them.

This results in differences like:

- **Different Naming:** One database might have a `customer_id` column, while another has `cust_no`.
- **Different Data Types:** A product price might be a `DECIMAL` in one database and a `FLOAT` in another.
- **Different Structures:** One system might store a customer's full name in a single `FullName` field, while another splits it into `FirstName` and `LastName`.

**2. The Global Query**

A user or application sends a single query. This query is written using a common, standardised language (like standard SQL) that doesn't target any specific database. This is called a **global query**.

For example, a user wants to find the name and location of a product with ID `123`. The product's name is stored in a modern `PostgreSQL` database, while its warehouse location is in an old `mainframe` system.

**User's Query:** 

```java
SELECT product_name, location FROM products WHERE product_id = 123;
```

**3. The Middleware "Translator"**

This global query is intercepted by the middleware, which acts as the system's brain. The middleware has a crucial component called a **global schema**. This is a map that understands how the data is distributed and how to reconcile the differences between the local databases.

The middleware does two things:

- **Schema Mapping:** It looks at the query and consults its global schema. It knows that `product_name` is in the PostgreSQL database in a column called `p_name`, and `location` is in the mainframe system in a field called `wh_loc`.
- **Query Translation:** It breaks the global query into smaller sub-queries and translates each one into the specific language or SQL dialect that the target database understands.

**Translated Sub-query for PostgreSQL:** `SELECT p_name FROM inventory WHERE p_id = 123;`**Translated Sub-query for Mainframe:** `GET wh_loc FROM stock WHERE item_code = 123;`

**4. Executing the Sub-Queries**

The middleware sends each translated sub-query to its respective database. Each database processes its query locally, completely unaware of the larger distributed system, and sends its result back to the middleware.

- PostgreSQL returns: `{"p_name": "Ultra-Widget"}`
- Mainframe returns: `{"wh_loc": "Warehouse B"}`

---

**5. Integrating the Results**

The middleware's final job is to receive all the partial results from the different databases. It then **integrates** them into a single, consistent result set that matches the format the user originally requested. This might involve changing data types, column names, or formatting.

The middleware combines the two results into a single record.

**Final Result to User:**

```java
| product_name | location |
|--------------|------------|
| Ultra-Widget | Warehouse B|
```

### Based on Autonomy:

Autonomy refers to the degree of independence that individual database sites have within a distributed system. It dictates how much control a local site has over its own data and operations versus how much it is controlled by the central distributed system.

---

### a) Tightly Integrated (No Autonomy)

This is a top-down approach where the entire distributed system is designed and controlled as a single entity. The individual sites have **no independence**.

- **Detailed Explanation:**
In a tightly integrated system, there is one central Database Management System (DBMS) that has absolute authority over all the nodes. The nodes are essentially just "workers" that execute commands given by the central controller. The database is conceived as a single logical unit from the start, and it is then physically distributed across various locations for performance or capacity reasons. There is no concept of a "local" database versus a "global" one—there is only one database.
- **Analogy: A Centrally Controlled Drone Swarm**
Imagine a swarm of drones flying in a perfectly synchronised formation to create a light show. A single operator with a central computer controls every drone's position, speed, and light color. An individual drone has **no autonomy**; it cannot decide to fly on its own or change its color. It only does what the central controller commands. This is a tightly integrated system.
- **How It Works:**
    - **Single Global Schema:** There is only one schema for the entire database. This schema is designed centrally and then parts of it are distributed (or fragmented) across the different sites.
    - **Centralised Control:** All queries, transaction management, and concurrency control are handled by the central authority.
    - **Complete Transparency:** From a user's perspective, they are interacting with a single database. They are completely unaware that the data is physically stored in different locations.
- example: The idea that "some part of the schema is in 1 node... and other in the other node" is exactly how tightly integrated (non-autonomous) systems are designed. This process is formally called **data fragmentation**. Data fragmentation is a broad term that refers to **data being split into smaller, dispersed parts, either within a single database (logical data fragmentation) or across different systems and locations (physical data fragmentation)**

### Horizontal Fragmentation (Splitting by Rows)

Here, a table is split row by row. Think of it like slicing a cake horizontally. Each node gets a full set of columns but only a subset of the rows, usually based on a condition.

- **Example:** Imagine a `Students` table for the entire college.
    - **Node A (in the Engineering building)** stores the rows `WHERE Department = 'Computer Science'` or `'Mechanical'`.
    - **Node B (in the Arts building)** stores the rows `WHERE Department = 'History'` or `'Fine Arts'`.

Both nodes have the exact same table structure (`StudentID`, `Name`, `Department`), but they contain different sets of students.

### Vertical Fragmentation (Splitting by Columns)

This is precisely the scenario you described. A table is split column by column. Think of it like cutting a cake into vertical slices. Each fragment contains all the rows but only a subset of the columns. A common key (like `StudentID`) is kept in all fragments to link the data back together.

- **Example:** Using the `Students` table again.
    - **Node A (Registrar's Office Server)** stores general information: `StudentID`, `Name`, `Address`, `Department`.
    - **Node B (Finance Office Server)** stores financial information: `StudentID`, `Tuition_Due`, `Fees_Paid`, `Scholarship_Status`.

So, if a user runs a query to get a student's name and their tuition balance (`SELECT Name, Tuition_Due FROM Students WHERE StudentID = 123;`), the DDBMS knows it needs to fetch the `Name` from Node A and the `Tuition_Due` from Node B and then combine them.

To the user, it still looks and feels like a single, unified `Students` table. The DDBMS handles all the complexity of fragmenting the data and reassembling it behind the scenes.

---

### b) Semi-autonomous

This is a hybrid model that tries to balance the benefits of centralized coordination with the need for local control. Sites have a degree of independence but must still cooperate within the larger system.

- **Detailed Explanation:**
In a semi-autonomous system, each site has its own local database with its own local users and applications. However, each site also agrees to participate in the distributed system. This means it follows certain rules and makes its data available to global users through a coordinated effort. The local site can manage its own affairs, but it can't make unilateral decisions that would disrupt the global system (e.g. changing the schema of shared data without permission).
- **Analogy: A University with Different Departments**
Think of a university. The Physics department, the History department, and the Arts department are all semi-autonomous. Each department manages its own budget, hires its own faculty, and sets its own curriculum (**local autonomy**). However, they are all part of the same university. They must follow the university's overall rules, use the central student registration system, and coordinate on course schedules (**global coordination**).
- **How It Works:**
    - **Local and Global Schemas:** Each site has its own complete local schema. A portion of this schema, called an "export schema," is shared with the distributed system. The global schema is then built by combining the export schemas from all participating sites.
    - **Shared Control:** Local operations are managed by the local site. Global operations (queries or transactions involving multiple sites) are managed by a coordinating layer of software.

---

### How Semi-Autonomous Systems Work

In this hybrid model, each node operates its own database but agrees to cooperate with the larger system under a set of shared rules.

- **Schema Management:** This is the key difference. There isn't just one global schema. Instead, there's a multi-level structure:
    1. **Local Schema:** Each node has its own complete, private database schema that it uses for its local users and applications. It has full control over this.
    2. **Export Schema:** Each node administrator decides which parts of their local schema they are willing to share with the distributed system. This public-facing portion is the "export schema."
    3. **Global Schema:** The central coordinating software builds the global schema by integrating the various export schemas from all the participating nodes.
- **How a Query Works:**
Let's use the analogy of a university with different departments. 🎓
    1. A student (the user) goes to the central university registrar's website (the global system) to find all 3rd-year courses that have no prerequisites.
    2. The registrar's software (the global coordinator) consults its **global schema**, which is a combination of course catalogs (**export schemas**) from all departments.
    3. It determines it needs information from the Physics, History, and Arts departments. It sends a request to each department's local database.
    4. Each department's database runs the query on its own course data (**local schema**) and sends the results back.
    5. The registrar's software combines the results into a single list and presents it to the student.

The History department maintains full control over its own database but has agreed to share its course catalog in a standardized way.

---

### c) Loosely Integrated / Federated (High Autonomy)

This is a bottom-up approach where pre-existing, fully independent databases are brought together to cooperate. The emphasis is on preserving local independence at all costs.

- **Detailed Explanation:**
A federated system is a collection of independent databases that agree to work together. Each site is a "sovereign" entity. It owns its data, controls its schema, and manages its own operations. It can choose what data (if any) to share with the federation. The distributed system is a software layer built *on top* of these existing databases to provide a unified view. The local sites have the power to refuse requests from the federation if they conflict with local priorities.
- **Analogy: A Group of Independent Freelancers**
Imagine a group of independent freelancers—a graphic designer, a writer, and a web developer. Each one is their own boss, uses their own tools, and manages their own clients (**high autonomy**). They decide to form a collective or "federation" to bid on larger projects together. When a big project comes in, they cooperate, but the designer still has full control over the design process, and the writer controls the content. The client interacts with the collective as a single team, but behind the scenes, it's a partnership of equals.
- **How It Works:**
    - **Federated Schema:** Each site shares an export schema, and the federated (global) schema is a combination of these. The system must handle all the heterogeneity between the different local schemas.
    - **Local Control is Supreme:** The local DBMS has the final say. It processes requests from the federation just as it would from any other external user. The local administrator can revoke access or even take the site out of the federation at any time.

### How Loosely Integrated (Federated) Systems Work

This model is for connecting databases that were never intended to work together. Preserving **local autonomy** is the absolute highest priority.

- **Schema Management:** This is the most complex scenario. The system is built "bottom-up" using powerful middleware to stitch everything together.
    1. **Local Schema:** Each node has its own pre-existing, independent, and often completely different schema. Think of a MySQL database, an old mainframe system, and a modern cloud database.
    2. **Export Schema:** The local administrator agrees to share some data. The middleware must be configured to understand the structure of this shared data.
    3. **Federated Schema (Global Schema):** This is a virtual schema created in the middleware that provides a unified view of all the connected, heterogeneous databases. The middleware's most important job is to maintain the complex **map** between this clean, unified view and the messy, different local schemas.
- **How a Query Works:**
Let's use the analogy of a travel booking website.
    1. A user (the traveler) searches for a flight and a hotel in Paris for the same dates.
    2. The website's middleware receives this single request. It consults its **federated schema**.
    3. It performs **query translation**. It sends a specific, correctly-formatted query to the American Airlines database (a local system) for flights and a completely different query to the Marriott database (another local system) for hotels.
    4. Each system (the airline, the hotel) processes the request independently, having no idea it's part of a larger federated query. They each have full control and are just responding to an external request.
    5. The middleware gets the results back—flight times from one, room availability from the other—**integrates** them, and presents them on a single page to the user.

In this case, the airline and hotel databases are fully autonomous. They have simply agreed to allow the booking website to query their data via a public API.

### Very Important Point about semi Autonomous and Highly Autonomous DDS

- Semi-autonomous and Highly Autonomous DDS (federated systems) **generally don't use fragmentation**.

Why? Because fragmentation is a process of *breaking up a single, unified database*.

Semi-autonomous systems are built the other way around: by **joining together whole, pre-existing databases**. Each node brings its own complete, independent database to the partnership. It doesn't receive a "fragment" from a central authority; it *shares* its own data.

### Promises of Distributed DBMS

1. **Transparent Management**: Users shouldn't need to know where data is located
2. **Improved Performance**: Through parallel processing and local data access
3. **Improved Reliability**: Through replication and redundancy
4. **Easier Expansion**: Modular growth capability
5. **Shareable**: Data can be shared across organization

Explained:

**1. Transparent Management of Data**

From a graduate-level perspective, **transparency** is not a single feature but a multi-faceted concept. The ultimate goal of a DDBMS is to provide the illusion of a single, centralized database. This is known as the "golden rule" of DDBMS. A sophisticated system aims to provide several types of transparency:

- **Location, Fragmentation, and Replication Transparency:** This is the most crucial aspect. A user writes a simple query like `SELECT * FROM Employees WHERE salary > 50000;` without needing to know:
    - **Location:** That the `Employees` table is stored across servers in Delhi and Mumbai.
    - **Fragmentation:** That the table is horizontally fragmented (Delhi employees on one server, Mumbai on another) and vertically fragmented (salary details are on a separate, more secure server).
    - **Replication:** That the Delhi server has a live replica in Chandigarh for disaster recovery.
    
    **How it's achieved:** This magic is handled by the **DDBMS query processor** and the **global data dictionary (or catalog)**. When a query is submitted, the processor consults the global catalog to find the location, fragmentation rules, and replication status of the required data. It then rewrites the user's simple query into a complex execution plan of sub-queries targeted at the specific fragments on the correct nodes, and then assembles the results.
    
- **Failure Transparency:** This ensures that in the event of a node failure, the system can continue to operate without the user even noticing (or with minimal disruption).
**How it's achieved:** This relies on **transaction management protocols** like the **Two-Phase Commit (2PC)** or **Three-Phase Commit (3PC)** protocol. When a transaction spans multiple nodes, these protocols ensure that the transaction is either committed on *all* participating nodes or aborted on *all* of them (atomicity). If a node fails, the recovery manager and concurrency control mechanisms work to resolve the transaction's state, often using replicated data from another available node.

**2. Improved Performance**

Performance enhancement in a DDBMS is achieved through two primary strategies: data localization and parallel processing.

- **Data Localization (Reducing Latency):** The cost of sending data over a network is orders of magnitude higher than accessing it from a local disk. By storing data closer to where it's most frequently used (e.g., storing European customer data on a server in Frankfurt), a DDBMS dramatically reduces network latency, leading to faster query response times. The query optimizer in a DDBMS is designed to be "communication-cost-aware," meaning it will try to minimize data transfer between sites, even if it means sending a more complex query to a remote node to process data locally and only send back the small final result.
- **Parallelism:** A DDBMS can execute operations in parallel to speed up processing.
    - **Inter-query Parallelism:** Different queries from multiple users can be executed simultaneously on different nodes. This increases the system's overall throughput.
    - **Intra-query Parallelism:** A single, complex query (e.g., a large join and aggregation) can be broken down into sub-queries that are executed in parallel on different nodes. For example, if you're joining a `Sales` table (on Node A) with a `Products` table (on Node B), the system might execute parts of the join on both nodes simultaneously and then merge the results. This can drastically reduce the time taken for complex analytical queries.

**3. Improved Reliability and Availability**

These are often the primary business drivers for adopting a DDBMS.

- **Reliability through Redundancy:** A system is reliable if it doesn't lose data. By **replicating** data across multiple nodes, the DDBMS ensures that if one node is destroyed (e.g., in a fire or flood), a complete copy of the data is safe on another node.
- **Availability through Replication:** A system is available if it can continue to answer queries. If a node goes offline due to a hardware failure, the system can automatically redirect all queries to a replica of that data on another node. This process, known as **failover**, ensures high availability.
    
    **The CAP Theorem:** As an M.Tech student, you must consider the **CAP Theorem**. It states that a distributed system can only provide two out of three guarantees: **C**onsistency, **A**vailability, and **P**artition Tolerance. In the real world, network partitions are a given, so you are forced to trade off between perfect consistency and high availability. For example, a banking system might choose Consistency over Availability (halting transactions if nodes can't sync), while a social media feed would choose Availability over Consistency (showing you slightly stale data is better than showing nothing at all).
    

---

**4. Easier Expansion (Scalability)**

Scalability is the ability of a system to handle a growing amount of work. DDBMS provides excellent **horizontal scalability** (or scaling out).

- **Horizontal vs. Vertical Scaling:**
    - **Vertical Scaling (Scaling Up):** In a centralized system, when you run out of power, you have to replace your server with a bigger, more expensive one. This is costly and has a physical limit.
    - **Horizontal Scaling (Scaling Out):** In a DDBMS, you simply add another commodity server (node) to the distributed system. This **modular growth** is far more cost-effective and has virtually no upper limit.
    
    **Technical Challenge:** While adding a new node is physically easy, the DDBMS has the complex job of **data rebalancing**. It needs to automatically redistribute the data and query load across the new, larger cluster without significant downtime. Sophisticated algorithms are required to move fragments of data to the new node while the system is still live.
    

---

**5. Data Sharing**

This goes back to the fundamental promise of databases: to be a single source of truth.

- **Organisational Integration:** A DDBMS provides a mechanism to integrate data from different departments or geographical locations into a single, logical database. The sales department's database in the US and the manufacturing department's database in China can be integrated into a single global schema. This allows high-level management to run queries that provide a holistic view of the entire company's operations, which is impossible if the data is locked away in isolated "silos."
- **Local Autonomy:** This integration can be achieved without sacrificing local control. Using a semi-autonomous or federated architecture, each department can continue to manage its own database for its own needs, while also sharing relevant data with the broader organization under a set of agreed-upon rules. This provides the best of both worlds: global data sharing and local control.

### Complications in Distributed DBMS

1. **Distributed Database Design**: How to fragment and allocate data?
2. **Query Processing**: How to execute queries across multiple sites efficiently?
3. **Concurrency Control**: How to coordinate concurrent transactions across sites?
4. **Reliability**: How to handle site failures and network failures?
5. **Catalog Management**: Where to store metadata about distributed data?
6. **Deadlock Handling**: Detection and resolution across distributed sites

### 1. Distributed Database Design

This is a strategic, NP-hard optimization problem that occurs before the system is even built. The core question is: How do you partition and place data to optimize for performance, availability, and cost?

- **Fragmentation Strategy:**
    - **Horizontal Fragmentation (Splitting rows):** The decision of *how* to split is critical. A `Customers` table could be split by `Region`. This is perfect for regional queries, but a query that needs to aggregate data across all regions becomes very expensive.
    - **Vertical Fragmentation (Splitting columns):** This is done to improve performance by separating frequently accessed columns from large, infrequently accessed ones (like `BLOB` or `TEXT` fields). However, any query that needs columns from different fragments will require an expensive join operation on the same primary key across different nodes.
    - **Derived Fragmentation:** A more advanced technique where one table is fragmented based on the fragmentation of another. For example, the `Orders` table might be horizontally fragmented based on `CustomerID`, ensuring that an order is always stored on the same node as the customer who placed it. This is done to optimize join performance, a key consideration.
- **Allocation Strategy:**
Once data is fragmented, where do you store the fragments?
    - **Non-Replicated:** Each fragment resides at exactly one site. This is simple and good for write-heavy workloads (no replication overhead), but it creates a single point of failure for that data.
    - **Replicated:** Copies of fragments are stored at multiple sites. This offers excellent read performance (reads can be load-balanced) and high availability, but at a significant cost to write performance. Every `UPDATE`, `INSERT`, or `DELETE` must be coordinated and applied to all replicas, a process known as the **write-all protocol**, which introduces significant network overhead and complexity.

### Horizontal Fragmentation

Rows of a table are **partitioned** across different nodes, usually based on some attribute value.

Example: **Customers table**

```sql
CustomerID | Name    | City     | Region
----------------------------------------
1          | Rajesh  | Mumbai   | West
2          | Priya   | Pune     | West
3          | Rohan   | Delhi    | North
4          | Simran  | Chandigarh | North
5          | Arjun   | Chennai  | South
```

**Fragmentation rule:**

- All rows with `Region = West` go to **Mumbai Node**
- All rows with `Region = North` go to **Delhi Node**
- All rows with `Region = South` go to **Chennai Node**

So yes, you understood correctly: **customers belonging to Mumbai region are stored on the Mumbai node (or West region node)**.

**Advantage:**

- Local queries (like “Get all customers in Mumbai region”) are very fast, because the data is already local.

**Disadvantage:**

- Global queries (like “Total customers across all regions”) require contacting multiple nodes and aggregating results (expensive).

### Vertical Fragmentation

Split columns of a table into groups (fragments), and distribute them.

Example: **Employee table**

```sql
EmployeeID | Name   | Phone      | Salary  | Resume (BLOB) | ProfilePic (BLOB)
```

- **Frequently accessed:** `EmployeeID, Name, Phone, Salary` (needed in most queries, like payroll, attendance, HR queries).
- **Rarely accessed:** `Resume, ProfilePic` (only needed when HR reviews profiles).

So we split like this:

**Fragment F1 (Core Info):**

```sql
EmployeeID | Name   | Phone | Salary
```

Stored on **fast nodes**, queried often.

**Fragment F2 (Heavy/rare data):**

```sql
EmployeeID | Resume | ProfilePic
```

Stored on **separate storage**, maybe on cheaper/slower nodes.

Whenever HR wants to see the full profile, the system does a **join on EmployeeID** between F1 and F2.

So vertical fragmentation = separate “hot” (frequent) vs “cold” (rare/large) data.

### Derived Fragmentation

A table is fragmented **based on how another table was fragmented**.

The classic use case = **Orders vs Customers**.

Example:

- Suppose **Customers** are horizontally fragmented by Region (as in #1).
- Now, every **Order** should ideally be stored on the same node as the Customer who placed it.

Why? Because queries like:

```sql
SELECT *
FROM Customers C JOIN Orders O ON C.CustomerID = O.CustomerID
WHERE C.Region = 'West';
```

are **extremely common**.

If Orders were stored separately (not aligned with Customers), every such query would become a **distributed join** across multiple nodes (very expensive).

**So Derived Fragmentation rule:**

- Partition `Orders` **by CustomerID**, in alignment with where the `CustomerID` resides.

Example:

```
Customer Rajesh (Mumbai, Region=West) → stored in Mumbai Node
All Orders placed by Rajesh → also stored in Mumbai Node
```

It’s not about the physical location of where the customer clicked "Place Order" (like from Mumbai city), but about **data locality** → Orders are co-located with the Customer record for optimisation.

### 2. Distributed Query Processing

The goal is to resolve a user's declarative SQL query into an optimal execution plan in a distributed environment. The definition of "optimal" is minimizing a cost function where **network communication cost is the most dominant factor**.

- **Phases of Processing:**
    1. **Query Decomposition:** The SQL query is parsed and transformed into a standardized relational algebra query tree.
    2. **Data Localization:** The query tree is mapped against the fragmentation schema. The system determines which fragments on which nodes are needed to answer the query.
    3. **Global Optimization:** This is the most complex phase. The optimizer generates multiple possible execution plans (e.g., "Join A and B at site 1, then send the result to site 3" vs. "Send A to site 2 and B to site 2 and join there"). It estimates the cost of each plan, considering data size, network speed, and processing power, and selects the cheapest one.
- **Key Optimization Technique: Semijoin**
Instead of shipping an entire large table across the network for a join, a semijoin is used to filter data first.
    - **Scenario:** Join `Employees` (1 million rows, at Site A) with `Projects` (100 rows, at Site B).
    - **Naive Plan:** Ship the entire `Employees` table to Site B. Cost: Transferring 1 million rows.
    - **Semijoin Plan:**
        1. Ship only the joining column (`ProjectID`) from `Projects` at Site B to Site A. (Cost: 100 values).
        2. Site A performs the join locally, finding the `Employees` who match those 100 `ProjectID`s (maybe 500 employees).
        3. Ship only those 500 matching `Employee` rows to Site B.
        4. Site B performs the final join.
        The semijoin reduces the data transferred across the network from 1 million rows to 100 values + 500 rows.

**Step 1: How Joins Work in a Centralised Database**

Say we want to compute:

```sql
SELECT *
FROM Employees E
JOIN Projects P
ON E.ProjectID = P.ProjectID;
```

- **Employees** = 1,000,000 rows
- **Projects** = 100 rows

Internally, the DBMS tries to find all pairs `(E, P)` where `E.ProjectID = P.ProjectID`.

Depending on the join algorithm (nested loop, hash join, merge join), the DBMS may:

- Scan Employees, and look up matching Projects rows.
- Or build a hash table of Projects and probe with Employees.

But this is all *inside one database*, no network cost. Only CPU and disk I/O.

---

**Step 2: What Changes in a Distributed Database?**

Now assume:

- **Employees** table is stored at **Site A**.
- **Projects** table is stored at **Site B**.

But the query was submitted at **Site B**.

So Site B must produce the final result.

Now, Site B has two choices:

**Option 1: Ship Employees → Site B**

- Send all **1 million rows** of Employees from Site A to Site B.
- Join locally at Site B with Projects (100 rows).
- Correct, but **network cost = 1M rows** (very expensive).

**Option 2: Ship Projects → Site A**

- Send the 100 Project rows to Site A.
- Perform the join at Site A (1M scan + match).
- Send the **500 matched employees** back to Site B.
- Much cheaper: **network cost = 100 rows + 500 rows**.

---

**Step 3: Where the `Semijoin` Comes In**

The optimiser wants to **minimize network transfer**.

Semijoin idea =

Instead of sending *all* Project rows or *all* Employee rows, first **filter what’s really needed**.

**How?**

- At Site B (Projects), extract only the **join key column** (ProjectID).
    - That’s just 100 IDs.
- Send these 100 ProjectIDs to Site A.
- At Site A, scan Employees (yes, you still need to scan the 1M rows, but scanning locally is fine, there’s no network cost).
- Select only Employees where `Employee.ProjectID ∈ {those 100 IDs}`.
    - Suppose that’s 500 Employees.
- Send those 500 Employee rows back to Site B.
- Site B now joins them with its local Projects table.

Total network transfer = 100 IDs + **500 Employee rows**, instead of **1 million rows**.

semijoin = “send only what is *minimally necessary* for the join (the key values), not the whole table.” The optimization is about r**educing network transfer** by sending only the *join attributes i*nstead of all attributes.

---

### 3. Distributed Concurrency Control

How do you maintain the ACID properties (especially Isolation) when transactions are accessing data across multiple sites without a shared memory or a global clock?

- **Locking Protocols:** Standard Two-Phase Locking (2PL) is extended to a distributed environment. This requires a **Distributed Lock Manager**.
    - **Centralized Lock Manager:** A single site manages all locks for the entire system. Simple to implement but becomes a severe performance bottleneck and a single point of failure.
    - **Distributed Lock Manager:** Each site manages locks for its own data. This is more robust, but now deadlock detection becomes a major distributed problem (covered next).
- **Timestamp Ordering Protocols:** Since there's no global clock, the system must create a total ordering of transactions. This is often done using a **Lamport Timestamp**, which combines a local counter with the site ID to generate a globally unique and monotonically increasing timestamp. Transactions are then processed in the order of their timestamps to ensure serializability. The challenge here is handling out-of-order requests without causing excessive transaction rollbacks.

### **Two Phase Locking Protocol (2PL)**

The Two-Phase Locking (2PL) Protocol is a key technique used in DBMS to manage how multiple concurrent transactions access and modify data. When many users or processes interact with a database, it’s important to ensure that data remains consistent and error-free. Without proper management, issues like data conflicts or corruption can occur

The Two-Phase Locking Protocol resolves this issue by defining clear rules for managing data locks. It divides a transaction into two phases:

1. **Growing Phase**: In this step, the transaction gathers all the locks it needs to access the required data. During this phase, it cannot release any locks.
2. **Shrinking Phase**: Once a transaction starts releasing locks, it cannot acquire any new ones. This ensures that no other transaction interferes with the ongoing process.

Types of Lock:

- **Shared Lock (S):** Shared Lock is also called a read-only lock, allows multiple transactions to access the same data item for reading at the same time. However, transactions with this lock cannot make changes to the data. A shared lock is requested using the lock-S instruction.
- **Exclusive Lock (X):** An Exclusive Lock allows a transaction to both read and modify a data item. This lock is exclusive, meaning no other transaction can access the same data item while this lock is held. An exclusive lock is requested using the lock-X instruction.

**Lock Conversions**

In the Two-Phase Locking Protocol, lock conversion means changing the type of lock on data while a transaction is happening. This process is carefully controlled to maintain consistency in the database.

1. **Upgrading a Lock**: This means changing a shared lock (S) to an exclusive lock (X). For example, if a transaction initially only needs to read data (S) but later decides it needs to update the same data, it can request an upgrade to an exclusive lock (X). However, this can only happen during the Growing Phase, where the transaction is still acquiring locks.**Example:** A transaction reads a value (S lock) but then realizes it needs to modify the value. It upgrades to an X lock during the Growing Phase.
2. **Downgrading a Lock**: This means changing an exclusive lock (X) to a shared lock (S). For instance, if a transaction initially planned to modify data (X lock) but later decides it only needs to read it, it can downgrade the lock. However, this must happen during the Shrinking Phase, where the transaction is releasing locks.**Example**: A transaction modifies a value (X lock) but later only needs to read the value, so it downgrades to an S lock during the Shrinking Phase.

<a href="https://ibb.co/JLBYLwG"><img src="https://i.ibb.co/W9xr94M/image.png" alt="image" border="0"></a>

These rules ensure that the Two-Phase Locking Protocol maintains consistency and avoids conflicts between transactions. By limiting when upgrades and downgrades can occur, the system prevents situations where multiple transactions interfere with each other’s operations.

### **Cascading Rollbacks in 2-PL (An issue) - `Uncommitted Reads`**
<a href="https://ibb.co/HLPmWQM5"><img src="https://i.ibb.co/1YXHDxpF/image.png" alt="image" border="0"></a>

**1. Transaction T1:**

- T1 acquires an exclusive lock (X) on data item A, performs a write operation on A and then acquires a shared lock (S) on B.
- T1 reaches its lock point (LP) after acquiring all locks.
- Eventually, T1 fails and a rollback is triggered, undoing its changes.

**2. Transaction T2:**

- T2 reads A after T1 writes A. This is called a [**dirty read**](https://www.geeksforgeeks.org/sql/dbms-dirty-read-in-sql/) because T1's write is not committed yet.
- When T1 rolls back, T2's operations become invalid, and it is also forced to rollback.

**3. Transaction T3:**

- T3 reads A after T2 reads A. Since T2 depends on the uncommitted changes of T1, T3 indirectly relies on T1's changes.
- When T1 rolls back, T3 is also forced to rollback even though it was not directly interacting with T1's operations.

**Cascading Rollback Problem:**

- Here, T2 and T3 both depend on *uncommitted data* from T1 (either directly or indirectly). When T1 fails and rolls back all dependent transactions (T2 and T3) must also rollback because their operations were based on invalid data.
- Cascading rollbacks waste system resources, reduce concurrency and lead to inefficiency, In large systems, this can significantly affect performance and make recovery more complex.

### How to avoid Cascading Rollbacks and Uncommitted Reads ?

There are 3 types of 2 phase locking i.e `Basic 2PL` , `Strict 2PL` , `Rigorous 2PL` .

- **Strict 2PL**: Ensure that transactions release their X-locks (exclusive locks) only after they commit, preventing dirty reads (solved dirty reads but can still cause unrepeatable reads problem)
- **Rigorous 2PL**: Ensure that transactions release both S-locks (Shared locks) and X-locks (Exclusive locks) only after they commit the changes (solves both dirty reads and unrepeatable reads problem, may increase latency in transactions coz locks are now holds for longer times)

*A `dirty read` occurs when one transaction reads data that has been modified by another, ongoing transaction that has not yet been committed or rolled back*

### Major Drawback of `Strict 2PL` that we can overcome using `Rigorous 2PL`

- Strict 2PL in some situations breaks **repeatable read** condition.
- ***Repeatable Read:** This isolation level guarantees that a transaction will see the same data throughout its duration, even if other transactions commit changes to the data. However, phantom reads are still possible.*

**1. Strict 2PL**

Rule:

- **X-locks are held until commit**.
- **S-locks can be released earlier (after read)**.

**T1:**

```
S-lock(A)
Read(A)
Unlock(A)   <-- Strict 2PL allows this
```

**T2:**

```
X-lock(A)   <-- succeeds because T1 released S-lock
Write(A)
Commit
Unlock(A)
```

Now suppose **T1 again needs to read A**:

**T1:**

```
S-lock(A)   <-- has to reacquire
Read(A)     <-- but now it reads updated value from T2
```

---

**⚠️ The issue here:**

- T1 has **read two different versions of A** in the same transaction:
    - First, the old version (before T2’s write).
    - Later, the new version (after T2’s write).
- This breaks **repeatable read** (and can cause anomalies in serializability).

So Strict 2PL prevents **dirty reads** (no one reads uncommitted X-lock data), but still allows **non-repeatable reads** because S-locks can be released early.

---

**2. Rigorous 2PL**

Rule: **Both S-locks and X-locks are held until commit.**

**T1:**

```
S-lock(A)
Read(A)
... (T1 keeps holding S-lock, not released)
```

**T2:**

```
X-lock(A)   <-- blocked, because T1 still holds S-lock
```

So T2 must **wait until T1 commits**.

Thus, T1 cannot see multiple versions of A. Its read of A is guaranteed to be the same throughout the transaction.

This guarantees **serializability** and avoids non-repeatable reads.

- *Serializability ensures that when multiple database transactions run concurrently, the outcome is the same as if they had executed one after another in a serial order, maintaining data consistency and ACID properties*

### 4. Reliability (Atomic Commitment)

How do you ensure a transaction that spans multiple sites is **atomic**—that is, it either commits everywhere or aborts everywhere, even if sites crash or networks fail during the transaction?

- **The Two-Phase Commit (2PC) Protocol:** This is the classic solution.
    1. **Phase 1 (Voting Phase):** A central **Coordinator** node sends a `PREPARE` message to all participating nodes ("cohorts"). Each cohort checks if it can commit the transaction, writes its changes to a durable log, and replies `YES` or `NO`.
    2. **Phase 2 (Commit/Abort Phase):**
        - If the Coordinator receives `YES` from **all** cohorts, it sends a `COMMIT` message to all of them.
        - If it receives even one `NO` (or a cohort times out), it sends an `ABORT` message to all of them.
- **The Problem with 2PC: Blocking.** If the Coordinator crashes after the voting phase begins but before it sends the final decision, all cohorts that voted `YES` are **blocked**. They cannot unilaterally commit or abort; they must wait for the Coordinator to recover, potentially holding critical locks for an indefinite amount of time. The **Three-Phase Commit (3PC)** protocol was designed to solve this but is rarely used in practice due to its own complexities.

### **Two-Phase Commit Protocol (2PC)**

What is 2PC?

The **Two-Phase Commit Protocol (2PC)** is a widely used approach to ensure atomic transactions in distributed systems. In 2PC, a coordinator oversees multiple participants and ensures that either all participants agree to commit the transaction, or if any participant fails to commit, all participants rollback.

2PC operates in two phases: the **Prepare Phase** and the **Commit Phase**.

1. **Preparation Phase:**
- The coordinator sends a **Prepare** request to all participants.
- Each participant checks if it can complete the transaction and responds with either a **Yes** (prepared) or **No** (abort).
- If any participant responds with a No, the process halts, and the transaction is rolled back.

**2. Commit Phase:**

- If all participants respond with Yes, the coordinator sends a **Commit** command, and all participants commit the transaction.
- If any participant responds with No, the coordinator sends an **Abort** command to rollback the transaction across all participants.

**Example Scenario for 2PC**

Imagine an e-commerce website handling an order transaction:

- When a customer places an order, the e-commerce system needs to check the **inventory** (whether items are in stock), **payment processing** (funds availability), and **delivery system** (delivery partner availability).
- The coordinator (order system) sends a Prepare request to each component.
- If all components confirm they are ready, the coordinator proceeds with Commit. If any component indicates an issue (e.g., insufficient stock), the coordinator aborts the transaction to maintain consistency.

**Limitations of 2PC**

2PC does not handle network failures very well:

- If the coordinator fails during the Commit Phase, some participants may not receive the final decision.
- It can result in **blocking** (participants waiting indefinitely), especially if the coordinator fails to send a response.

### **Three-Phase Commit Protocol (3PC)**

**What is 3PC?**

The **Three-Phase Commit Protocol (3PC)** is an enhanced version of 2PC designed to address the limitations of 2PC, specifically the risk of blocking. 3PC introduces an additional phase between Prepare and Commit, known as the **Pre-Commit** phase, to ensure participants have enough time to respond, reducing the risk of indefinite blocking.

3PC operates in three phases: **Prepare Phase**, **Pre-Commit Phase**, and **Commit Phase**.

1. **Prepare Phase:**
- Similar to 2PC, the coordinator sends a **Prepare** request to participants, asking if they can commit the transaction.
- Each participant responds with Yes or No.

**2. Pre-Commit Phase:**

- If all participants respond Yes, the coordinator sends a **Pre-Commit** message, indicating the transaction is likely to be committed.
- Participants acknowledge the Pre-Commit, preparing to commit the transaction but not yet completing it.

**3. Commit Phase:**

- If all participants acknowledge the Pre-Commit, the coordinator sends the **Commit** command.
- If any participant fails to acknowledge the Pre-Commit, the transaction is **Aborted**.

***3PC mitigates blocking issues by adding a timeout mechanism,*** allowing participants to autonomously decide to commit or abort if they don’t receive further messages from the coordinator.

**Example Scenario for 3PC**

Imagine a financial application processing a transaction across multiple bank accounts:

- A transaction coordinator oversees several bank databases to transfer funds between accounts.
- The coordinator sends a Prepare request to all databases.
- If all respond positively, the coordinator sends a Pre-Commit message to ensure all are ready.
- After receiving acknowledgments, the coordinator finally sends the Commit request to finalize the transaction. If any bank fails to acknowledge, the transaction is aborted.

**Advantages of 3PC**

3PC reduces the likelihood of indefinite blocking, particularly helpful in situations with unreliable networks:

- **Timeout Mechanism**: Allows participants to make autonomous decisions if they don’t hear back from the coordinator.
- **Improved Fault Tolerance**: Reduces the risk of hanging transactions.

**Choosing Between 2PC and 3PC**

Use 2PC if your system prioritizes consistency over availability and has reliable network connectivity. Examples include:

- Banking systems where each transaction’s atomicity is paramount.
- Inventory management systems where resource locking ensures stock levels remain accurate.

Use 3PC if your system requires high availability and must handle network unreliability gracefully. Examples include:

- Distributed databases where transactions are spread across regions.
- Microservices in cloud environments with potential network interruptions.

<a href="https://ibb.co/Psn106yP"><img src="https://i.ibb.co/kVfqvSTw/image.png" alt="image" border="0"></a>

### 5. Catalog Management

The catalog (or data dictionary) contains the metadata: information about schemas, fragments, allocation sites, and statistics. It is the brain of the DDBMS. Where do you store this brain?

- **Centralized Catalog:** Stored at one site. Easy to manage but suffers from the classic problems of a single point of failure and a performance bottleneck.
- **Fully Replicated Catalog:** A copy is stored at every site. This offers excellent performance for query optimization (all metadata is local) and high availability. However, any change to the database schema (e.g., `ALTER TABLE`) becomes incredibly expensive, as the change must be synchronously propagated to all sites.
- **Partitioned Catalog:** Each site maintains the catalog for its own local data. This scales well and supports site autonomy, but resolving a global query requires the coordinator to query multiple catalog sites just to build an execution plan.

Most modern systems use a hybrid approach, such as a master catalog with extensive local caching at each node.

### 6. Distributed Deadlock Handling

A **global deadlock** can occur when a chain of waiting transactions spans multiple sites, forming a cycle that no single site can see on its own.

- **Global Wait-For Graph (GWFG):** Conceptually, a deadlock is a cycle in a graph where nodes are transactions and an edge T1 -> T2 means T1 is waiting for a lock held by T2. The GWFG is the union of all local wait-for graphs.
- **Detection Strategies:**
    - **Centralized Coordinator ("Deadlock Czar"):** Periodically, each site sends its local wait-for graph to a central coordinator. The coordinator combines them into a GWFG and checks for cycles. This is simple but, again, creates a bottleneck and a single point of failure.
    - **Distributed Detection (e.g., Chandy-Misra-Haas algorithm):** A more robust approach. When a transaction T1 starts waiting for T2, a special "probe" message is generated and sent to the site where T2 is. This probe message is then forwarded along the wait-for chain. If the probe message eventually returns to its originator (T1), it means a cycle has been found, and a deadlock is detected. The system must then choose a victim transaction to abort and break the cycle.

### Key Components & Schema Levels

The architecture is often described as a multi-level structure, where each level deals with a different aspect of data distribution.

### **1. Global Schema (Conceptual Schema)**

This is the **highest level of abstraction**. It provides a unified, logical view of the entire distributed database as if it were a single, centralized database.

- **Purpose:** To define all the data items, their relationships, and constraints for the entire system.
- **Analogy:** Think of it as the complete, unabridged catalog for a massive library system. It lists every book available across all branches, but it doesn't tell you which specific branch a book is in.

### **2. Fragmentation Schema**

This level describes how the global data is broken down into smaller pieces called **fragments**. This process is called data fragmentation.

- **Purpose:** To define how relations (tables) are logically divided. The goal is to improve performance, reliability, and availability by storing data where it's most frequently used.
- **Types of Fragmentation:**
    - **Horizontal Fragmentation:** The table is split by rows. For example, a `Customers` table could be split by city, with all Chandigarh customers in one fragment and all Delhi customers in another.
    - **Vertical Fragmentation:** The table is split by columns. For example, an `Employee` table might be split to store `EmployeeID`, `Name`, and `Department` in one fragment and the less frequently accessed `Salary` and `PerformanceReview` in another. The primary key (`EmployeeID`) is usually kept in all vertical fragments to allow reconstruction of the original table.
    - **Mixed (Hybrid) Fragmentation:** A combination of both horizontal and vertical fragmentation.

### **3. Allocation Schema**

This level specifies **where each fragment is physically stored**.

- **Purpose:** To map the logical fragments to the actual physical sites (computers/servers) in the network.
- **Key Considerations:**
    - **Replication:** The system might store identical copies of a fragment at multiple sites. This increases data availability (if one site fails, the data is still accessible) and improves read performance, but makes updates more complex.
    - **No Replication:** Each fragment is stored at exactly one site.

### **4. Local Schema**

This is the **lowest level**, representing the physical database implementation at each individual site.

- **Purpose:** To define how the allocated fragments are stored on the physical storage devices at a specific location. It translates the fragments into the data model and storage format of the local DBMS (e.g., Oracle, MySQL, etc.).
- **Analogy:** This is the specific shelving system and organization used within a single library branch to store its assigned books.

---

### Communication Architecture Models

This describes how the different sites in the distributed system communicate with each other to process queries and transactions.

### **Client-Server Model**

This is a traditional model where multiple clients connect to a central server or a set of servers. The clients request data, and the server processes the request and returns the result. In a distributed context, one site might act as a server for a query initiated by another site (the client).

### **Peer-to-Peer (P2P) Model**

In this model, every site is an equal partner or "peer." Each site has full DBMS functionality and can communicate directly with any other site. They can act as both a client and a server. This architecture is more decentralized and resilient, as there is no single point of failure.

### **Multi-DBMS (Federated Database System)**

This architecture is used to integrate several pre-existing, autonomous database systems into a single, unified DDBMS. A software layer sits on top of the different local DBMSs to provide a global schema and coordinate query processing, effectively acting as a translator between them. This is useful for large organisations that want to integrate legacy systems.

***