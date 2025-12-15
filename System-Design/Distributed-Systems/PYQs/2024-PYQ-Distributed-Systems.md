# [PYQ 2024] **MT-CSE-18-14(ii): Distributed Systems**

![question paper 2024](https://i.ibb.co/wfdHwqT/image.png)

**Question 1(i) What is distributed data processing and how does it differ from centralized data processing? (4 Marks)**

**Distributed Data Processing (DDP)** refers to a system where data storage and processing tasks are shared across multiple interconnected computers (nodes) over a network, rather than being handled by a single machine. These nodes work together to appear as a single system to the user.

**Differences:**

| **Feature** | **Centralized Data Processing** | **Distributed Data Processing** |
| --- | --- | --- |
| **Architecture** | All data and processing logic reside on a single central computer (e.g., a mainframe). | Processing and data are spread across multiple distinct sites (nodes) connected via a network. |
| **Reliability** | **Low:** It has a "Single Point of Failure." If the central server crashes, the entire system stops. | **High:** If one node fails, the system can continue to function using the remaining nodes. |
| **Scalability** | **Vertical:** You must upgrade the hardware of the main server (more RAM/CPU), which has a limit. | **Horizontal:** You can simply add more cheap computers (nodes) to the network to increase power. |
| **Control** | Easier to manage security and updates because everything is in one place. | More complex to manage due to data synchronization, replication, and network security issues. |

**1(ii) What is the role of view management in ensuring controlled access to data in distributed databases? (4 Marks)**

In a Distributed Database System (DDBS), a **View** is a virtual table derived from the actual base tables. It plays a critical role in security and abstraction:

1. **Access Control (Security):** Views act as a filter. You can create a view that reveals only specific columns or rows to a user.
    - *Example:* A view for an HR intern might show employee names but exclude the `Salary` column. This restricts access to sensitive data without changing the underlying database.
2. **Location Transparency:** The most important role in a distributed system. The user queries the view as if it were a local table. The view definition handles the complexity of fetching data that might be fragmented or replicated across New York, London, and Tokyo. The user doesn't need to know *where* the data is.
3. **Logical Data Independence:** If the database administrator changes the physical schema (e.g., splits a table into two fragments), they only need to update the view definition. The user's queries on that view remain unchanged.

---

**1(iii) What is the role of data localization in distributed query processing? (4 Marks)**

**Data Localization** is the phase in query processing where a query written on global relations is translated into a query on specific data fragments.

**Key Roles:**

1. **Mapping Global to Local:** It replaces the global table names (e.g., `Employee`) with their actual fragments (e.g., `Employee_North`, `Employee_South`) based on the fragmentation schema.
2. **Fragment Pruning (Optimization):** This is its most critical role. It analyzes the query conditions to eliminate fragments that contribute no data.
    - *Example:* If a query asks for `SELECT * FROM Employee WHERE City = 'Delhi'`, and the system knows that `Fragment_2` only contains employees from 'Mumbai', the Data Localization step will **prune** (discard) `Fragment_2` immediately.
3. **Reducing Network Traffic:** By identifying exactly which sites hold the relevant data (and ignoring the rest), it prevents the system from sending useless queries to every node in the network.

---

**1(iv) What is concurrency control and why is it important in centralized database systems? (3 Marks)**

**Concurrency Control** is the mechanism that manages simultaneous access to a database to ensure that transactions do not interfere with each other.

**Why it is important (The ACID properties):**

1. **Preventing the "Lost Update" Problem:** Without it, if two users try to update the same record at the same time (e.g., both withdrawing money), the last write might overwrite the first one, leading to incorrect balances.
2. **Preventing "Dirty Reads":** It ensures a user doesn't read data that is currently being modified by someone else but hasn't been saved (committed) yet.
3. **Ensuring Consistency:** It guarantees that even if multiple transactions run in parallel, the final database state is consistent, as if the transactions had run one after the other (Serializability).

---

### **UNIT-I**

**Q2. (a) What are the primary features of distributed databases and why are they significant? Explain. (6 Marks)**

A **Distributed Database (DDB)** is a collection of multiple, logically interrelated databases distributed over a computer network.

**Primary Features:**

1. **Distribution:** The most obvious feature. Data is strictly not resident at a single site; it is spread across multiple nodes (sites) connected via a communication network.
2. **Logical Correlation:** Unlike a set of loose files, the data across these sites is logically related. It forms a single "system" in the eyes of the user.
3. **Site Autonomy:** Each site has some degree of control over its local data. It can often process local transactions independently of the global system.
4. **Transparency:** The system hides the complexities of the network. The user feels like they are querying a single local machine, even if data is coming from three different continents.

**Significance (Why we use them):**

- **Organizational Fit:** Most big organizations are decentralized (branches in Delhi, Mumbai, Bangalore). Distributed databases fit this structure naturally.
- **Reliability & Availability:** If one site crashes, the system doesn't die. Users can still access data from other surviving sites.
- **Performance:** Data is stored close to where it is used most frequently (Data Localization). This reduces network traffic and speeds up queries.
- **Scalability:** It is easier to add a new small server to the network than to upgrade a massive central mainframe.

**Q2. (b) Discuss various types of distributed database systems. (9 Marks)**

Distributed Database Systems are primarily classified based on **Homogeneity** (are the sites the same?) and **Autonomy** (how independent are they?).

**1. Homogeneous Distributed Database Systems**

In these systems, all sites use the **same DBMS product** (e.g., all sites use Oracle, or all use MySQL).

- **Features:** They share the same data model and query language.
- **Pros:** Much easier to design and manage. Query optimization is straightforward because the system knows exactly how every node behaves.
- **Cons:** Less flexible; you are locked into one vendor.
- **Types:**
    - **Autonomous:** Sites are independent but share a schema.
    - **Non-Autonomous:** Sites are just "dumb" storage nodes managed by a central master.

**2. Heterogeneous Distributed Database Systems**

In these systems, different sites run **different DBMS products** (e.g., Site A runs Oracle, Site B runs SQL Server, Site C runs PostgreSQL).

- **Features:** They may use different data models (relational vs. object-oriented) and transaction managers.
- **Pros:** Allows an organization to integrate legacy systems that already exist.
- **Cons:** Extremely complex. Requires a "Translator" or "Wrapper" layer to convert queries between different formats.

**3. Federated Database Systems (FDBS)**

A special type of heterogeneous system where the local sites are highly autonomous.

- They participate in the federation only for specific shared data but function as completely independent databases for local users.
- There is no single "Global Schema" that enforces strict rules on everyone.

---

**Q3. (a) What are the main functions of a distributed DBMS and how do they contribute to its objectives? (7 Marks)**

A **Distributed DBMS (DDBMS)** is the software that manages the distributed database. Its functions extend standard DBMS functions to a network environment.

| **Main Function** | **Contribution to Objectives** |
| --- | --- |
| **Distributed Query Processing** | **Performance:** It breaks a high-level query into sub-queries for different sites, ensuring data is fetched efficiently with minimal network delay. |
| **Distributed Concurrency Control** | **Consistency:** Uses locking or timestamping to ensure that simultaneous users (at different sites) don't corrupt the data. |
| **Reliability & Recovery (Commit Protocols)** | **Reliability:** Uses protocols like **2-Phase Commit (2PC)** to ensure atomicity—either all sites save the data, or none do. It handles site crashes gracefully. |
| **Replication Management** | **Availability:** Keeps copies of data at multiple sites. If the primary site fails, the DDBMS automatically redirects users to the backup copy. |
| **Security & Authorization** | **Protection:** Manages user permissions across the network, ensuring a user in New York can't delete restricted data in London. |
| **Catalog Management** | **Transparency:** Maintains a "Global Directory" so the system knows exactly where every piece of data is located, hiding this detail from the user. |

**Q3. (b) Discuss the Multi-database System Architecture. How is it different from a distributed DBMS? (8 Marks)**

A **Multi-database System (MDBS)** supports operations on multiple autonomous databases that effectively "don't know" they are part of a larger system. They are often "loosely coupled."

**The Architecture (5-Level Schema)**

MDBS (specifically Federated systems) often uses a 5-level schema architecture to bridge the gap between local independence and global access:

1. **Local Schema:** The conceptual schema of the individual component database (e.g., the original Oracle schema).
2. **Component Schema:** A translation of the local schema into a "canonical" (common) data model so the central system can understand it.
3. **Export Schema:** A subset of the component schema. The local database decides, "I will only share *these* tables with the federation, the rest is private."
4. **Federated Schema:** The integration of all Export Schemas. This is the "global view" available to the MDBS users.
5. **External Schema:** Custom views for specific users or applications built on top of the Federated Schema.

| **Feature** | **Distributed DBMS (DDBMS)** | **Multi-Database System (MDBS)** |
| --- | --- | --- |
| **Coupling** | **Tightly Coupled:** The sites are designed to work together from the start. | **Loosely Coupled:** Independent databases are "glued" together later. |
| **Global Schema** | Has a single, unified Global Conceptual Schema that covers all data. | Usually lacks a strict global schema; creates a "federated" view instead. |
| **Autonomy** | **Low:** The central system has significant control over local sites. | **High:** Local sites retain full control and can shut down or change without asking the central system. |
| **User Experience** | Users see it as **one** large database. | Users are often aware they are querying multiple distinct sources. |
| **Analogy** | A single company with branches in different cities. | A consortium of different companies agreeing to share some files. |

---

### Unit-2

**Q4. Discuss the top-down design process and the design issues in distributed databases. (15 Marks)**

This question asks for the methodology of building a distributed database from scratch.

**Part 1: The Top-Down Design Process**

The Top-Down approach is used when we are designing a completely new system. We start with the high-level requirements and work our way down to the physical implementation on specific nodes.

**The Phases:**

1. **Requirements Analysis:**
    - Understanding the organization's needs. What data do they have? Who needs to access it? What is the expected transaction volume?
    - *Output:* User requirement documents.
2. **Conceptual Design (Global Schema):**
    - We design the database as if it were a centralized system. We define entities, relationships, and constraints (ER Diagrams).
    - *Output:* **Global Conceptual Schema** (e.g., a massive diagram containing all tables like `Employee`, `Department`, `Project`).
3. **View Design:**
    - Defining the specific views (subsets of data) required by different user groups (e.g., HR needs "Salary" data, Engineering needs "Project" data).
4. **Distribution Design (The Core Step):**
    - This is where the system becomes "distributed." We do not just copy the Global Schema to every site. Instead, we perform two critical activities:
        - **Fragmentation:** Breaking the global relations (tables) into smaller logical units (fragments).
        - **Allocation:** Deciding which site (computer) stores which fragment.
5. **Physical Design:**
    - Mapping the allocated fragments to the physical storage devices (disks) at each local site. This involves setting up indexes and local access paths.

**Part 2: Design Issues in Distributed Databases**

When performing the "Distribution Design" phase mentioned above, we face three major challenges (Design Issues):

**1. Fragmentation (How do we split the data?)**
We cannot just store the whole `Employee` table in New York if 90% of the employees work in London. We must split the table.

- **Horizontal Fragmentation:** Splitting rows. (e.g., `Employee_NY` gets rows where `City='NY'`, `Employee_LDN` gets rows where `City='London'`).
- **Vertical Fragmentation:** Splitting columns. (e.g., Storing `Salary` info on the secure Finance server and `Names` on the public HR server).
- **Mixed Fragmentation:** A combination of both.

**2. Allocation (Where do we put the data?)**
Once we have fragments, where do we place them?

- **Information:** We need to know network topology, link speeds, and site capacities.
- **Goal:** Place the data closest to the applications that use it most frequently to minimize network traffic (Data Localization).

**3. Replication (How many copies do we keep?)**
Should we keep just one copy of a fragment, or copy it to multiple sites?

- **No Replication:** Fast updates (only one place to write), but low availability (if that site crashes, data is gone).
- **Full Replication:** High availability and fast reads (everyone has a local copy), but very slow updates (you must update every single copy across the network).
- **Partial Replication:** The balance—keeping copies only at key sites.

---

**Q5. What is allocation problem? Discuss an allocation model that attempts to minimise the total cost of processing and storage while trying to meet certain response time restrictions. (15 Marks)**

**1. The Allocation Problem**
The allocation problem is the mathematical challenge of finding the "optimal" distribution of data fragments ($F_1, F_2, ... F_n$) across a network of sites ($S_1, S_2, ... S_m$).
It is essentially a decision-making problem: **"For every fragment $F_i$, which site(s) $S_j$ should store it?"**
The decision is difficult because there is a trade-off:

- Placing data everywhere (Replication) makes **Reading** fast (local access).
- But it makes **Writing** expensive (network traffic to update all copies) and increases **Storage** costs.

**2. The Cost-Minimization Allocation Model**

A standard allocation model aims to minimize the **Total Cost** while ensuring the system isn't too slow (Constraints).
The Objective Function (Minimize Total Cost)
The Total Cost ($TC$) generally consists of three components:
$TC = \text{Query Cost} + \text{Update Cost} + \text{Storage Cost}$

1. **Query Processing Cost ($C_{query}$):**
- The cost of sending read requests from a user at Site A to the data at Site B.
- This includes the cost of transmitting the request and transmitting the result back.
- *Goal:* We want to place fragments closer to the users who query them the most.

1.  **Update Cost ($C_{update}$):**
    - The cost of propagating changes. If we replicate a fragment to 5 sites, every `UPDATE` command must send messages to all 5 sites.
    - *Goal:* Do not replicate data that is updated frequently.
2. **Storage Cost ($C_{storage}$):**
    - The literal cost of disk space at each site. Storing a copy of a massive database at every branch office is expensive.
    The Constraints (Rules we must follow)
    We cannot just pick the cheapest option if it makes the system unusable. The model must respect:
    - 1. **Response Time Constraint:**
        - The execution time of critical queries must be less than a threshold $T$.
        - *Equation:* $\text{Time}(\text{Query}_k) \le T_{limit}$
        - This forces us to replicate data (to improve speed) even if it costs more.
    - 2. **Storage Capacity Constraint:**
        - A specific site $S_j$ (e.g., a small branch server) only has a fixed amount of disk space.
        - *Equation:* $\sum (\text{Size of fragments at } S_j) \le \text{Capacity}(S_j)$

---

### Unit-3

**Question 6: Discuss the important characteristics of query processors
that can be used as a basis for comparison.**

A Distributed Query Processor (DQP) is responsible for translating a high-level query (like SQL) into an efficient execution plan that runs across multiple sites. Since different systems use different approaches, we compare them based on several key characteristics.

Here are the main characteristics used for comparison:

**1. Optimization Timing (When is the plan made?)**

- **Static Optimization:** The query is analyzed and compiled into an execution plan **before** execution starts (at compile time).
    - *Pros:* No runtime overhead; thorough optimization possible.
    - *Cons:* Cannot adapt to changes in the system (e.g., if a site fails or data size changes drastically after compilation).
- **Dynamic Optimization:** The optimization happens **during** execution (at run time).
    - *Pros:* Can make decisions based on the exact state of the system at that moment.
    - *Cons:* The optimization process itself slows down the query execution.
- **Hybrid:** Uses static optimization for standard parts and dynamic for variable parts.

**2. Type of Information (What info does it use?)**

- **Rule-Based (Heuristic):** Uses general "rules of thumb" to optimize.
    - *Example:* "Always perform selection (filtering) before joining tables."
    - *Pros:* Fast to generate a plan.
    - *Cons:* May pick a bad plan if the data distribution is unusual.
- **Cost-Based:** Estimates the "cost" (CPU, I/O, Network) of different strategies and picks the cheapest one.
    - *Pros:* Usually finds the best plan.
    - *Cons:* Requires maintaining accurate statistics (histograms) about the data, which is hard in distributed systems.

**3. Decision Site (Who decides the plan?)**

- **Centralized Approach:** A single site (the coordinator) creates the global plan for the entire query.
    - *Pros:* Easy to implement; the optimizer sees the "big picture."
    - *Cons:* The coordinator becomes a bottleneck.
- **Distributed Approach:** All participating sites cooperate to decide the plan.
    - *Pros:* Robust; no single point of failure.
    - *Cons:* Very complex coordination required.
- **Hybrid Approach:** A coordinator makes the major decisions, while local sites optimize their own sub-queries.

**4. Network Topology Assumptions**

- **Wide Area Network (WAN):** Assumes sites are far apart.
    - *Focus:* **Minimizing Communication Cost** (data transfer) is the #1 priority.
- **Local Area Network (LAN):** Assumes fast connections.
    - *Focus:* **Minimizing Processing Cost** (CPU/Disk I/O) is the priority, as network transfer is cheap.

**5. Join Strategy**

- **Semijoin-based:** Sends only the joining column (not the whole row) to the other site to filter matches, then requests the full data. Best for WANs.
- **Join-based:** Sends the entire table to the other site to perform the join. Best for LANs.

---

**Q7. (a) Discuss the primary objectives of database security in distributed environments. How do they address confidentiality, integrity and availability? (8 Marks)**

Database security aims to protect the database against unauthorized access, malicious destruction, and accidental data loss. In a distributed environment, this is harder because data travels over a network.

The primary objectives are defined by the **CIA Triad**:

**1. Confidentiality (Secrecy)**

- **Objective:** Ensuring that information is accessible *only* to those authorized to have access.
- **Addressed by:**
    - **Authentication:** Verifying user identity (passwords, 2FA) across all sites.
    - **Authorization (Views):** Creating specific "Views" for users so they only see the data they need (e.g., hiding the `Salary` column).
    - **Encryption:** Since data travels over public networks between sites, it must be encrypted in transit to prevent "sniffing" or wiretapping.

**2. Integrity**

- **Objective:** Ensuring the data remains accurate, consistent, and trustworthy.
- **Addressed by:**
    - **Access Controls:** Preventing unauthorized users from `UPDATE` or `DELETE` commands.
    - **Semantic Integrity Constraints:** Rules enforced by the DBMS (e.g., "Age cannot be negative").
    - **Concurrency Control:** Preventing two users from modifying the same record simultaneously, which would corrupt the data.

**3. Availability**

- **Objective:** Ensuring authorized users have reliable access to data whenever they need it.
- **Addressed by:**
    - **Replication:** The unique strength of Distributed Databases. If Site A goes down, the system automatically redirects the user to Site B, which holds a copy of the data.
    - **Recovery Protocols:** Ensuring the system can restart and recover a consistent state after a crash.

**Q7. (b) Discuss distributed catalog management. (7 Marks)**

The **Catalog** (or Data Dictionary) is a system database that stores "metadata"—data about data. It contains schema definitions, user permissions, fragmentation rules, and allocation details.

In a Distributed DBMS, managing the catalog is tricky because we must decide **where** to store it.

**Storage Strategies:**

1. **Centralized Catalog:**
    - The entire catalog is stored at exactly **one** central site.
    - *Pros:* Easy to maintain.
    - *Cons:* If that site crashes, the entire distributed system halts because no one knows where data is located. It is a major bottleneck.
2. **Fully Replicated Catalog:**
    - A complete copy of the catalog is stored at **every** site.
    - *Pros:* Extremely fast reads (every site knows everything instantly). High availability.
    - *Cons:* Very slow updates. If you add a new table, you must update the catalog at *every single site* simultaneously.
3. **Partitioned Catalog:**
    - Each site maintains its **own** local catalog for data stored at that site.
    - *Pros:* Easy updates (local only).
    - *Cons:* Querying global data is slow. If Site A needs data from Site B, it must first send a message to Site B just to ask, "Do you have this table?"
4. **Hybrid Catalog (The Standard):**
    - Each site keeps a local catalog for its own data.
    - A central site (or a few key sites) keeps a global index of where everything is.
    - *Balance:* Offers a good trade-off between lookup speed and update cost.

---

### Unit-4

**Q8. Discuss the (a) Centralised, (b) Distributed and (c) Hierarchical approaches of detecting distributed deadlocks. (15 Marks)**

This question deals with how a distributed system finds out that a "cycle" of waiting processes exists across multiple nodes.

**(a) Centralized Approach**

In this approach, a single designated site (the **Coordinator**) is responsible for detecting deadlocks for the entire system.

- **Mechanism:**
    1. Every local site maintains its own local Wait-For Graph (WFG).
    2. Whenever a local WFG changes (e.g., a transaction waits for a lock), the site sends this update to the Central Coordinator.
    3. The Coordinator merges all these local graphs into one massive **Global Wait-For Graph**.
    4. The Coordinator runs a cycle detection algorithm on this global graph. If a cycle is found, it declares a deadlock and selects a victim transaction to abort.
- **Pros:**
    - Simple to implement (logic is similar to a single-computer database).
    - The Coordinator has a complete view of the system.
- **Cons:**
    - **Single Point of Failure:** If the Coordinator crashes, deadlock detection stops completely.
    - **Bottleneck:** The Coordinator can get overwhelmed by status messages from all other sites.
    - **False Deadlocks:** Due to network delays, the Coordinator might see a cycle that no longer exists (because one transaction finished while the message was traveling).

**(b) Distributed Approach**
In this approach, there is no single leader. All sites cooperate to detect deadlocks.

- **Mechanism (Edge Chasing / Probe-Based):**
    - There is no global graph built anywhere.
    - If Transaction $T_1$ (at Site A) is waiting for Transaction $T_2$ (at Site B), Site A sends a special message called a **PROBE** to Site B.
        - The probe contains the ID of the transaction that started the check.
        - If the probe is passed along a chain of waiting transactions and eventually returns to the sender (Site A), a cycle is confirmed.
        - **Pros:**
            - **Robust:** No single point of failure. If one site dies, the rest can still detect deadlocks among themselves.
            - **Scalable:** No single node is overwhelmed with traffic.
        - **Cons:**
            - **High Traffic:** Generating probes for every wait condition creates a lot of network "chatter."
            - **Complexity:** Difficult to implement correctly (need to handle lost messages, etc.).

**(c) Hierarchical Approach**
This is a hybrid approach that organizes sites into a tree-like structure to balance the load.

- **Mechanism:**
Sites are grouped into **clusters**.
    - **Level 0 (Leaves):** These are the actual database sites. They detect local deadlocks.
    - **Level 1 Coordinators:** These manage a specific cluster. If a deadlock involves multiple sites within the *same* cluster, this coordinator resolves it.
    - **Global Coordinator:** If a deadlock spans across different clusters, the Level 1 coordinators send the relevant dependency information up to the Global Coordinator to resolve it.
    - **Pros:**
        - Reduces the bottleneck problem of the Centralized approach (work is shared).
        - Reduces the communication traffic of the Distributed approach (local stuff stays local).
    - **Cons:**
        - Complex to manage the hierarchy dynamically (e.g., what if a Level 1 coordinator crashes?).

---

**Q9. (a) Explain the presumed abort and presumed commit 2PC protocols. (8 Marks)**

The standard Two-Phase Commit (2PC) protocol is "chatty" and requires writing to the disk (logging) frequently. These two variations optimize 2PC by reducing the number of log writes and messages.

**1. Presumed Abort (PA) Protocol**

This protocol optimizes for the case where a transaction fails (aborts), or when the system crashes and forgets status.

- **The Rule:** If a coordinator recovers from a crash and searches its log for a transaction but finds **no information**, it assumes the transaction was **Aborted**.
- **Optimization (Savings):**
    - The Coordinator does **not** need to force-write a "Start" record to disk before beginning.
    - If the decision is to **Abort**, the Coordinator does not need to force-write the "Abort" record to disk. It can just send "Abort" messages. If it crashes, it will wake up, find nothing, and "Presume Abort"—which is the correct outcome.
    - *Benefit:* Saves disk I/O when transactions fail.

**2. Presumed Commit (PC) Protocol**

This protocol optimizes for the common case where transactions succeed (commit).

- **The Rule:** If a coordinator recovers and finds no information about a transaction, it assumes the transaction was **Committed**.
- **Optimization (Savings):**
    - The Coordinator does **not** need to force-write the "End" record after a commit is finished.
    - More importantly, the Coordinator does not need to wait for "Acknowledgments" (ACKs) from participants after sending a Commit command. It assumes they will finish successfully.
- **The Cost:** To make this safe, the Coordinator *must* force-write a "Collecting" record at the very start (so it knows it is active) and *must* force-write any "Abort" decisions.
- *Benefit:* Since most transactions commit, this saves writes and messages in the normal, successful flow.

---

**Q9. (b) Discuss the recovery protocols for 2PC. (7 Marks)**

This section answers: *"What happens if a computer crashes in the middle of a 2-Phase Commit?"*

**1. Coordinator Failure & Recovery**

The Coordinator restarts and reads its log:

- **Case 1: Log contains "Commit".**
    - The Coordinator knows it already decided to commit. It re-sends the **COMMIT** message to all participants (just in case they didn't get it before the crash).
- **Case 2: Log contains "Abort".**
    - It re-sends the **ABORT** message to all participants.
- **Case 3: Log contains "Prepare" (but no decision).**
    - The Coordinator started the process but crashed before deciding. It effectively aborted (since it never sent a Commit). It sends **ABORT** to everyone.
    

**2. Participant Failure & Recovery**

A participant (a local site) restarts and reads its log:

- **Case 1: Log contains "Commit" or "Abort".**
    - The participant knows the final outcome. It simply applies the changes (Redo/Undo) locally.
- **Case 2: Log contains NO record of the transaction.**
    - The participant crashed *before* voting. It unilaterally **ABORTS** the transaction (votes No).
- **Case 3: Log contains "Ready" (The Critical Case).**
    - The participant voted "Yes" and was waiting for the Coordinator's decision when it crashed.
    - It is now blocked. It does not know if the group decided to Commit or Abort.
    - **Action:** It must initiate a **Termination Protocol** (ask the Coordinator or other participants: *"Hey, what happened to transaction T1 while I was asleep?"*) to synchronize its state.

---

END