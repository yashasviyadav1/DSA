## Unit-4

![](https://i.ibb.co/xqck1Mp3/image.png)

### What is Concurrency Control?

Concurrency Control is the process of managing simultaneous operations (transactions) on a database without letting them interfere with each other and ensuring data consistency and isolation.

### 1. CONCURRENCY CONTROL IN CENTRALIZED DATABASE SYSTEMS

Before understanding distributed concurrency control, we must understand the fundamentals from centralized systems.

### 1.1 Why Concurrency Control?

**Problem:** Multiple transactions executing concurrently can lead to inconsistencies.

Example of Anomaly:

**Initial State:** `Account A = $1000`, `Account B = $500`

**Transaction T1:** Transfer $100 from A to B

```sql
T1: Read(A)           *-- Reads 1000*
T1: A = A - 100       *-- A = 900*
T1: Write(A)          *-- Writes 900*
T1: Read(B)           *-- Reads 500*
T1: B = B + 100       *-- B = 600*
T1: Write(B)          *-- Writes 600*
```

**Transaction T2:** Add 10% interest to both accounts

```sql
T2: Read(A)           *-- Reads value*
T2: A = A * 1.1       *-- Increase by 10%*
T2: Write(A)
T2: Read(B)
T2: B = B * 1.1       
T2: Write(B)

-- t2 first 
A = 1100 ,B = 550
-- then t1
A = 1000 B = 660
```

```sql
***-- Correct Final State***
A = $990, B = $660 (if T1 first, then T2) 
OR
A = $1000, B = $660 (if T2 first, then T1)
```

**Interleaved Execution (Incorrect, without concurrency controll)**

```sql
T1: Read(A)      [1000]
T2: Read(A)      [1000]
T1: A = A - 100  [900]
T2: A = A * 1.1  [1100]
T1: Write(A)     [900]   *-- Lost Update! -> this update is overritten by the T2's write in next step*
T2: Write(A)     [1100]  *-- Overwrites T1's change*
T1: Read(B)      [500]
T1: B = B + 100  [600]
T1: Write(B)     [600]
T2: Read(B)      [600]
T2: B = B * 1.1  [660]
T2: Write(B)     [660]
```

```sql
Final: A = 1100, B = 660 (INCORRECT! Lost T1's debit)

**Total should be $1500**, but is $1760 Money created from nowhere!
```

### 1.2 Transaction Properties (ACID)

defined on the data (like balances ≥ 0, totals must match, etc.) should always hold true.

When we say a database supports **transactions**, it means it ensures these four essential properties — **A, C, I, D** — so that even in the presence of failures, concurrent access, or errors, **data remains correct and consistent**.

**Atomicity**
- A transaction is treated as a single, indivisible unit of work. Either all of its operations are executed successfully, or none are executed at all.
- "All or nothing" ideology

**Consistency**
- A transaction must take the database from one valid (consistent) state to another valid state.
- The integrity constraints defined on the data (like balances ≥ 0, totals must match, etc.) should always hold true.- Example: Total money remains constant

**Isolation**

- Even if multiple transactions run concurrently, each should behave as if it were the only one running.
- Their intermediate steps should not be visible to others.

**Durability**

Once a transaction **commits**, its changes are **permanent**, even if:

- System crashes
- Power fails
- Database restarts
- Written to non-volatile storage

### With Concurrency Control:

The system ensures that:

- Only **one transaction** updates the balance at a time.
- Others **wait** or **are serialized** (like a queue).

### **1.3 Serializability**

When multiple transactions execute concurrently, we want the **final result** to be **as if** the transactions were executed **one after another** (serially).

So, **Serializability** is the **gold standard** for correctness in concurrency.

**Serial Schedule vs Serializable Schedule**

| Type | Meaning | Example |
| --- | --- | --- |
| **Serial Schedule** | Transactions run **one by one**, no overlap | T1 → T2 or T2 → T1 |
| **Serializable Schedule** | Transactions run **concurrently**, but **final result = some serial order** | T1 and T2 interleave but produce same result as serial execution |

Even with concurrency, database state should be identical to one produced by a serial schedule. **serializability** guarantees that the result of running multiple transactions concurrently (at the same time) is the same as if they had run one after another (serially) in some order.

**The "Race Condition" (A Non-Serializable Schedule)**

A "schedule" is the order in which the database executes the individual steps (read, write) of the transactions.

Consider this **bad** interleaved schedule:

1. **A reads balance:** A sees $100.
2. **B reads balance:** B *also* sees $100 (because A hasn't written its result yet).
3. **A calculates:** A calculates $100 + $50 = $150.
4. **B calculates:** B calculates $100 - $20 = $80.
5. **A writes balance:** A saves **$150** to the database.
6. **B writes balance:** B saves **$80** to the database, overwriting A's work.

**Final Balance: $80**. This is wrong! This is called a "lost update" problem. This schedule is **not serializable** because its result ($80) does not match *any* of the possible correct serial executions (which both resulted in $130).

### The Solution: A Serializable Schedule

A system that enforces serializability would prevent this bad interleaving. It uses mechanisms like **locking** to force a correct outcome, even though the transactions are *trying* to run concurrently.

Here's how a serializable system might handle it:

1. **A reads balance:** A sees $100. (The system places a "lock" on the balance).
2. **B tries to read balance:** B has to *wait* because A has it locked.
3. **A calculates:** A calculates $100 + $50 = $150.
4. **A writes balance:** A saves **$150** to the database. (A's transaction commits and releases the lock).
5. **B reads balance:** B is now allowed to read. B sees **$150**.
6. **B calculates:** B calculates $150 - $20 = $130.
7. **B writes balance:** B saves **$130** to the database.

**Final Balance: $130**. This outcome is correct. It is equivalent to the serial order (A, then B). The system allowed concurrency but ensured the result was logically correct. This is a **serializable** schedule.

- **Serial:** Running transactions one by one. This is simple, correct, but slow.
- **Serializable:** Running transactions concurrently, but with safeguards (like locks) that make the final result **identical** to *some* serial execution. It gives you the performance of concurrency with the correctness of serial execution.

### Types of Serializability

There are **two major types**:

1. **Conflict Serializability**
2. **View Serializability**

In practice, when people just say "serializability," they are almost always referring to conflict serializability because it's the one systems actually implement.

### **Conflict Serializability (The Practical One)**

This is the most common and important type.  It focuses on the *order of conflicting operations*.
• **What's a "Conflict"?** An operation conflicts with another if:
    1. They belong to different transactions.
    2. They access the same data item
    3. At least one of them is a **write** operation.

**Types of Conflicts**

| Type | Meaning | Example Problem |
| --- | --- | --- |
| **Read–Write (RW)** | One reads, another writes the same item | **Unrepeatable Read** |
| **Write–Read (WR)** | One writes, another reads the same item | **Dirty Read** |
| **Write–Write (WW)** | Both write same item | **Lost Update** |

**How it's checked:** 

The most common way is by building a **precedence graph** (or serializability graph).

1. Create a node for each transaction (e.g., T1, T2).
2. Draw a directed edge from T1 to T2 if an operation in T1 conflicts with and *comes before* an operation in T2.
3. **If the graph has no cycles, the schedule is conflict serializable.** A cycle means you have an impossible ordering, like "T1 must come before T2" and "T2 must come before T1."
(Note: A Read-Read (R-R) is never a conflict, as it doesn't change any data.)

example of **Conflict Serializability**.
Let's analyze an interleaved schedule **S** with two transactions, **T1** and **T2**, operating on two data items, **A** and **B**.

| **Time** | **Transaction T1** | **Transaction T2** |
| --- | --- | --- |
| 1 | `Read(A)` |  |
| 2 |  | `Read(A)` |
| 3 | `Read(B)` |  |
| 4 |  | `Write(A)` |
| 5 | `Write(B)` |  |
| 6 |  | `Read(B)` |
| 7 |  | `Write(B)` |

This schedule of operations is:
`S: R1(A); R2(A); R1(B); W2(A); W1(B); R2(B); W2(B);`

We will check if this schedule is **conflict serializable** by building a precedence graph.

**Step 1: Identify All Conflicts**
Remember, a conflict occurs if two operations from *different* transactions access the *same* data item, and *at least one* is a `Write`.
1. **`R1(A)`** vs. **`W2(A)`**: **Conflict.**
    ◦ T1 reads A, and later T2 writes A.
    ◦ This creates a dependency: **T1 -> T2** (T1's operation came first).
2. **`R2(A)`** vs. **`W1(B)`**: No conflict (different data items, A and B).
3. **`R1(B)`** vs. **`R2(B)`**: No conflict (both are `Read`).
4. **`R1(B)`** vs. **`W2(B)`**: **Conflict.**
    ◦ T1 reads B, and later T2 writes B.
    ◦ This creates a dependency: **T1 -> T2**.
5. **`W1(B)`** vs. **`R2(B)`**: **Conflict.**
    ◦ T1 writes B, and later T2 reads B.
    ◦ This creates a dependency: **T1 -> T2**.
6. **`W1(B)`** vs. **`W2(B)`**: **Conflict.**
    ◦ T1 writes B, and later T2 writes B.
    ◦ This creates a dependency: **T1 -> T2**.

**Step 2: Build the Precedence Graph**
We create a node for each transaction and draw an edge for each dependency we found.
• Nodes: T1, T2
• Edges: We found three types of conflicts, but all of them create the same dependency: an arrow from T1 to T2.

**Step 3: Check for Cycles**
Look at the graph. Is there a cycle? (A path that starts and ends at the same node).
• No. There are no cycles. The graph is a simple arrow from T1 to T2.

**Conclusion**
Because the precedence graph is **acyclic** (it has no cycles), the schedule **S** is **Conflict Serializable**.
This also tells us that this interleaved schedule (S) is equivalent to the serial schedule **(T1, then T2)**. If the database ran all of T1 first, and then all of T2, the final result would be identical. 

Even though the operations from T1 and T2 are interleaved, the final state of the database will be **identical** to what it would be if you had just run all of T1 first and then all of T2 second.

**Note: In the Schedule `S` the `T1` reads value of `A` and `T2` also reads value of `A` but then `T2` changes the value of `A` so is’nt this a problem (repeatable reads problem)?**

This is’nt a problem in this schedule because, T1 reads A *once* at the very beginning and then **never looks at A again**. Because T1 is "done" with data item A before T2 changes it, it doesn't matter that A's value is updated in the database. T1 already has the value it needs (the "older" value) and uses it for whatever calculation it needs to perform its `W1(B)` operation.

---

### **2. View Serializability**.

A schedule **S** is **view serializable** if it is **view equivalent** to some serial schedule (like T1, then T2).
For a schedule to be "view equivalent" to a serial schedule, it must satisfy three conditions:
1. **Initial Read:** If a transaction `T1` reads the initial value of a data item `A` in the serial schedule, it must also read the initial value of `A` in the interleaved schedule.
2. **Reads-From:** If a transaction `T1` reads a value of `A` that was written by `T2` in the serial schedule, it must also read the value of `A` written by `T2` in the interleaved schedule.
3. **Final Write:** The transaction that performs the *final* write on a data item `A` in the serial schedule must also perform the *final* write on `A` in the interleaved schedule.

**The Key Difference: "Blind Writes"**

Here's the most important relationship:
All conflict-serializable schedules are also view-serializable. But not all view-serializable schedules are conflict-serializable.
Why? Because view serializability allows for a special case that conflict serializability forbids. This case involves a **"blind write"**—a transaction that writes a value *without* reading it first.
Let's look at the classic example that shows this difference.

**Example: A Schedule that is View-Serializable (but NOT Conflict-Serializable)**

Consider this schedule **S** with three transactions (T1, T2, T3) and one data item, **A**.
• `T2`'s write is a **blind write**; it writes to `A` without ever reading it.
• `T3`'s write is also a **blind write**.
**TimeTransaction T1Transaction T2Transaction T3**
- `T1: Read(A)`
- `T2: Write(A)`
- `T1: Write(A)`
- `T3: Write(A)`

The schedule of operations is: `S: R1(A); W2(A); W1(A); W3(A);`

**Analysis Step 1: Is it Conflict Serializable?**

Let's build the precedence graph by finding all conflicts:
1. **`R1(A)`** vs. **`W2(A)`**: Conflict. `T1`'s operation came first.
    ◦ Edge: **T1 -> T2**
2. **`W2(A)`** vs. **`W1(A)`**: Conflict. `T2`'s operation came first.
    ◦ Edge: **T2 -> T1**
3. **`W1(A)`** vs. **`W3(A)`**: Conflict. `T1`'s operation came first.
    ◦ Edge: **T1 -> T3**
4. **`W2(A)`** vs. **`W3(A)`**: Conflict. `T2`'s operation came first.
    ◦ Edge: **T2 -> T3**
**The Graph:**
• We have an edge `T1 -> T2` and an edge `T2 -> T1`.
• This creates a **CYCLE**!
**Conclusion:** Because the precedence graph has a cycle, this schedule **S** is **NOT conflict serializable.**

**Analysis Step 2: Is it View Serializable?**

Now, let's check if **S** is *view equivalent* to any serial schedule. Let's try the serial schedule **<T1, T2, T3>**.**Schedule S (Interleaved)Serial Schedule <T1, T2, T3>**`R1(A)R1(A)W2(A)W1(A)W1(A)W2(A)W3(A)W3(A)`
Let's check our three rules:
1. **Initial Read:**
    ◦ In **S**: `T1` performs the initial read of `A`.
    ◦ In **<T1, T2, T3>**: `T1` also performs the initial read of `A`.
    ◦ **Result: Match!** 👍
2. **Reads-From:**
    ◦ `T1` reads the initial value in both schedules. No other transactions read anything. This condition is satisfied.
    ◦ **Result: Match!** 👍
3. **Final Write:**
    ◦ In **S**: The very last write to `A` is `W3(A)`.
    ◦ In **<T1, T2, T3>**: The very last write to `A` is also `W3(A)`.
    ◦ **Result: Match!** 👍
**Conclusion:** Because schedule **S** satisfies all three conditions of view equivalence with the serial schedule **<T1, T2, T3>**, it **IS view serializable.**

**Summary: Why?**

• Conflict serializability failed because it saw the `T1 -> T2` and `T2 -> T1` conflicts and created a cycle. It's too "strict."
• View serializability passed because it was "smart" enough to see that `T2`'s "blind write" was immediately overwritten by `T1` *before* anyone else could read it. Therefore, `T2`'s write had no effect on the final outcome, making the schedule safe.
**Key Takeaway:** In practice, checking for view serializability is computationally very difficult (NP-complete), so systems don't bother. They enforce **conflict serializability**, which is much easier to check (using the graph) and covers almost all practical cases.

---

### **Annomalies in Concurrency Explained**

1. Dirty Read (Write-Read Conflict)
2. Lost Update (Write-Write Conflict)
3. Unrepeatable Read (Read-Write Conflict)

Let's assume a bank account `Account_X` has a balance of **$100**.

### 1. Dirty Read (Write-Read Conflict)

This happens when **Transaction 2 reads uncommitted data** written by Transaction 1. It's "dirty" because the data might be rolled back, meaning T2 will have read data that never officially existed.

```sql
The Schedule (T1 Writes, T2 Reads):

1. T1 (Withdrawal): Reads balance ($100).
2. T1 (Withdrawal): Calculates new balance: $100 - $20 = $80.
3. T1 (Withdrawal): `Write(Account_X, $80)`. (This is *not yet committed*).
4. T2 (Interest): `Read(Account_X)`. It sees $80.
5. T2 (Interest): Calculates 10% interest: $80 * 0.10 = $8.
6. T1 (Withdrawal): The withdrawal fails for some reason (e.g., fraud alert) and ROLLS BACK. The database reverts the balance to the original $100.
7. T2 (Interest): `Write(Account_X, $88)`.
8. T2 (Interest): Commits.
```

Result: The final balance is $88.
Correct Result Should Be: The withdrawal (T1) failed, so the balance should be $100. The interest (T2) should have been calculated on $100, for a final balance of **$110**.

Problem: T2 made a decision based on "dirty" data that was later erased.

### 2. Lost Update (Write-Write Conflict)

This happens when **two transactions both update the same data**, and one update overwrites the other, "losing" the first transaction's work.

```sql
The Schedule (T1 Writes, T2 Writes):

1. T1 (Deposit): Read(Account_X). T1 sees $100.
2. T2 (Withdrawal): Read(Account_X). T2 also sees $100.
3. T1 (Deposit): Calculates new balance: $100 + $50 = $150.
4. T2 (Withdrawal): Calculates new balance: $100 - $20 = $80.
5. T1 (Deposit): Write(Account_X, $150).
6. T2 (Withdrawal): Write(Account_X, $80). (This overwrites T1's write).
7. T1 (Deposit): Commits.
8. T2 (Withdrawal): Commits.
```

Result: The final balance is $80.
Correct Result Should Be: $100 + $50 - $20 = $130.

Problem: T1's deposit of $50 was "lost" because T2 wrote its own value *after* T1, based on the same old data.

### 3. Unrepeatable Read (Read-Write Conflict)

This happens when a transaction **reads the same data item twice but gets different values** because another transaction modified it in between. The first read becomes "unrepeatable."

The Schedule (T1 Reads, T2 Writes, T1 Reads again):

1. T1 (Audit): `Read(Account_X)`. T1 sees $100. (The start of an audit process).
2. T2 (Deposit): `Read(Account_X)`. T2 sees $100.
3. T2 (Deposit): Calculates new balance: $100 + $50 = $150.
4. T2 (Deposit): `Write(Account_X, $150)`.
5. T2 (Deposit): Commits.
6. T1 (Audit): To verify, the audit process `Read(Account_X)` *again*. It now sees $150.
7. T1 (Audit): Commits.

Result: The audit transaction (T1) sees two different values ($100 and $150) for the *same data item* within its *own single execution*.
Correct Result Should Be: An "isolated" audit should see a consistent snapshot of the data. It should have seen $100 both times or $150 both times, but not both.

Problem: T1 is operating on inconsistent data, which could cause it to fail an integrity check (e.g., "Error! Balance changed from $100 to $150 mid-audit!").

---

### 1.4 Concurrency Control Protocols

**A. BASIC LOCKING**

Locking ensures that **only safe transactions** access data concurrently.

There are **two lock types:**

| Lock Type | Purpose | Can coexist with |
| --- | --- | --- |
| **Shared (S-lock)** | For reading only | Other S-locks ✅ |
| **Exclusive (X-lock)** | For writing (and reading) | No other lock ❌ |

**Compatibility Matrix**

|  | S | X |
| --- | --- | --- |
| **S** | ✓ | ✗ |
| **X** | ✗ | ✗ |

So, multiple transactions can **read the same item**, but **only one can write** at a time.

### ⚠️ **Problem — Not Serializable!**

Even though locks are used, **releasing too early** (before transaction ends) breaks serializability.

### Example:

```
T1: Lock-S(A)
T1: Read(A)
T1: Unlock(A)
                  T2: Lock-S(A)
                  T2: Read(A)
                  T2: Write(A)
                  T2: Unlock(A)
                  T2: Lock-X(B)
                  T2: Write(B)
                  T2: Unlock(B)
T1: Lock-X(B)
T1: Write(B)
T1: Unlock(B)
```

Here:

- `T1: Read(A)` comes before `T2: Write(A)`
- But `T2: Write(B)` comes before `T1: Write(B)`
- This creates a `T1 -> T2` and a `T2 -> T1` dependency, which is a **deadlock** and a **cycle**. The final result is inconsistent.

**The Problem: Releasing a Lock Too Soon**

The *exact* problem in your schedule is this line: `T1: Unlock(A)`.The moment T1 released its lock on `A`, it told the system, "I'm done with `A`." T2 then acquired its own locks. *However*, T1 *wasn't* truly "done." Its transaction was still running! It went on to acquire *another* lock on `B`. This violates the core principle of isolation. By releasing a lock (`A`) and then later acquiring a new lock (`B`), T1 created a window where another transaction (T2) could sneak in and break the serializable order.

**The Solution: Two-Phase Locking (2PL)**

### B. TWO-PHASE LOCKING (2PL)

2PL is the **standard protocol** used to guarantee **conflict serializability.**

- **Phase1: Growing Phase:**
    
    Transaction acquires locks (S or X) but releases none.
    
- **Lock Point:**
    
    The point where the **last lock** is acquired (boundary between growing and shrinking).
    
- **Phase2: Shrinking Phase:**
    
    Transaction releases locks but cannot acquire new ones.
    

By ensuring all locks are taken before any release, **circular dependencies** are avoided, ensuring **serializable order** of transactions.

**How 2PL Fixes Your Previous Example**

Let's re-run your schedule, but this time, T1 and T2 **must follow the 2PL rules**. 

| **Time** | **Transaction T1 (follows 2PL)** | **Transaction T2 (follows 2PL)** | **2PL Rule Check** |
| --- | --- | --- | --- |
| 1 | `Lock-S(A)` |  | (T1 is in its **Growing Phase**) |
| 2 | `Read(A)` |  |  |
| 3 |  | `Lock-S(A)` | (T2 requests, but T1 holds a lock. T2 must **WAIT**.) |
| 4 | `Lock-X(B)` | `...WAITING...` | (T1 is still in its **Growing Phase**. This is allowed.) |
| 5 | `Write(B)` | `...WAITING...` |  |
| 6 | **`Unlock(A)`** | `...WAITING...` | (T1 just released a lock. It is now in its **Shrinking Phase**.) |
| 7 | **`Unlock(B)`** | `...WAITING...` | (T1 is in its Shrinking Phase. Releasing is allowed.) |
| 8 | *(T1 Commits)* | `Lock-S(A)` | (T1's locks are gone. T2's request is **GRANTED**.) |
| 9 |  | `Read(A)` | (T2 is in its **Growing Phase**) |
| 10 |  | `Unlock(A)` | (T2 enters its **Shrinking Phase**) |
| 11 |  | `Lock-X(B)` | **❌ 2PL VIOLATION!** T2 tried to acquire a *new lock* after entering its shrinking phase. |

This schedule is impossible under 2PL.

**How it *Would* Work with 2PL**

For T2 to be valid, it would have to acquire all its locks *before* releasing any. The correct flow would be:

1. **T1:** `Lock-S(A)`
2. **T1:** `Read(A)`
3. **T1:** `Lock-X(B)`
4. **T1:** `Write(B)`
5. **T1:** *(T1 is done working, enters Shrinking Phase)*
6. **T1:** `Unlock(A)`
7. **T1:** `Unlock(B)`
8. *(T1 Commits)*
9. **T2:** `Lock-S(A)` (Now T2 can start)
10. **T2:** `Read(A)`
11. **T2:** `Lock-X(B)`
12. **T2:** `Write(B)`
13. **T2:** `Unlock(A)`
14. **T2:** `Unlock(B)`
15. *(T2 Commits)*

**Result:** This forces the serializable order **<T1, T2>**. The simple (but powerful) rule of 2PL completely prevents the cycle from ever happening.

### Why Cycle detection is important ?

(what were the consequences)

The cycle isn't just a theoretical graph, it represents a real-world, system-freezing issue called a **Deadlock**. Let's use a classic bank transfer example to show *exactly* what problem that cycle causes.

**The Real-World Problem: Deadlock**
Imagine two bank accounts:
• Account A: Has `$1000`
• Account B: Has `$500`
Now, two transactions start at the *exact same time*:
1. **Transaction T1:** Wants to transfer `$100` from **A to B**.
    ◦ *Logic:* It must lock A, subtract `$100`, then lock B, add $100.
2. **Transaction T2:** Wants to transfer `$50` from **B to A**.
    ◦ *Logic:* It must lock B, subtract $50, then lock A, add $50.
Now, let's watch the disastrous, non-2PL schedule unfold (this is the "cycle" you're asking about):

| **Time** | **Transaction T1 (A → B)** | **Transaction T2 (B → A)** | **State of the World** |
| --- | --- | --- | --- |
| 1 | `Lock-X(A)` |  | **Success.** T1 locks Account A. |
| 2 |  | `Lock-X(B)` | **Success.** T2 locks Account B. (No conflict yet). |
| 3 | `Subtract $100 from A` |  | T1 does its first step. (A=$900) |
| 4 |  | `Subtract $50 from B` | T2 does its first step. (B=$450) |
| 5 | `Lock-X(B)` |  | T1 now needs to lock Account B to add the $100... **But T2 is holding the lock!** T1 must **WAIT**. |
| 6 |  | `Lock-X(A)` | T2 now needs to lock Account A to add the $50... **But T1 is holding the lock!** T2 must **WAIT**. |

**The Catastrophe (The Cycle)**

Now, look at the state of the system at Time 6:

- **T1 is waiting** for T2 to release the lock on Account B.
- **T2 is waiting** for T1 to release the lock on Account A.

They will wait **forever**. Neither transaction can ever finish. This is a **deadlock**. The system is completely frozen, and no new transactions involving A or B can be processed.

This is the real-world problem a cycle in the precedence graph represents. The system has "locked itself" into an impossible-to-resolve waiting loop.

**How is this fixed?**

This is where a Deadlock Detection mechanism comes in. The database system has a background process that builds this "waits-for" graph (T1 is waiting for T2, T2 is waiting for T1).

1. Detect: It sees the cycle.
2. Kill: It chooses one transaction as a "victim" (e.g., T2).
3. Rollback: It kills T2 and rolls back all its work (the subtraction from B is undone, so B goes back to $500).
4. Release: Killing T2 releases its lock on B.
5. Proceed: T1's wait is over! It gets the lock on B, adds $100, and commits.
6. Retry: The banking application would then automatically restart T2 from the beginning.

So, while 2PL is essential to guarantee serializability *if transactions complete*, it doesn't prevent them from getting into a deadlock.

### **Variants of Two-Phase Locking**

| Variant | Description | Advantage | Disadvantage |
| --- | --- | --- | --- |
| **Strict 2PL** | Hold all **X-locks** until commit/abort | Prevents cascading aborts | Slower (locks held longer) |
| **Rigorous 2PL** | Hold **all (S + X) locks** until commit/abort | Simplest, guarantees serial + strict schedule | Reduces concurrency |
| **Conservative (Static) 2PL** | Acquire **all locks before** starting | Avoids deadlocks completely | Needs full data knowledge in advance |

**Example: Strict 2PL**

Transaction T1

```
BEGIN
  Lock-S(A)
  Read(A)
  Lock-X(B)
  Write(B)
  -- hold locks until commit
COMMIT
  Unlock(A)
  Unlock(B)
```

Transaction T2

```
BEGIN
  Lock-X(A)  ← waits if T1 holds S(A)
  Write(A)
  Lock-S(B)
  Read(B)
COMMIT
  Unlock(A)
  Unlock(B)
```

This ensures:

✅ Serializability

✅ No cascading aborts

✅ Consistent recovery

---

### **C. TIMESTAMP ORDERING (TO) PROTOCOL)**

Concept:

Instead of locking data items, each transaction is given a **timestamp (TS)** when it starts. That timestamp defines its **position in the serial order**.

> Rule:
> 
> 
> Transactions must appear to execute **in timestamp order.**
> 
> (Older timestamps → higher priority)
> 

**Metadata Maintained for Each Data Item X:**

| Field | Meaning |
| --- | --- |
| **Read_TS(X)** | The largest timestamp of any transaction that **successfully read X** |
| **Write_TS(X)** | The largest timestamp of any transaction that **successfully wrote X** |

**Read Rule**

When transaction **Ti** wants to read X:

```
If TS(Ti) < Write_TS(X):
   → Ti is too old (trying to read a value that was already overwritten)
   → ABORT Ti
Else:
   → Allow Ti to read X
   → Update Read_TS(X) = max(Read_TS(X), TS(Ti))
```

Meaning: if a newer transaction has already written X, the old one can’t read it — that would break the timestamp order.

**Write Rule**

When transaction **Ti** wants to write X:

```
If TS(Ti) < Read_TS(X):
   → A newer transaction has already read X
   → ABORT Ti (to prevent inconsistency)

Else If TS(Ti) < Write_TS(X):
   → A newer transaction already wrote X
   → Ignore write (Thomas Write Rule) OR Abort Ti

Else:
   → Execute Write(X)
   → Write_TS(X) = TS(Ti)
```

**Meaning:** If your write would “travel backward in time” (overwrite newer values), it’s not allowed.

Example Walkthrough

Transactions:

- T1 → TS = 10
- T2 → TS = 20
- T3 → TS = 30

Schedule:

```
T1: R(A)   → Read_TS(A) = 10
T2: W(A)   → Write_TS(A) = 20
T3: R(A)   → Read_TS(A) = 30
T1: W(A)   → TS(T1)=10 < Read_TS(A)=30 → ABORT T1
```

**Why aborted?**

Because T1 (older) is trying to write after a newer transaction (T3) already read the item.

That would break the serial order (T3 depends on older version of A).

### ⚙️ **Thomas Write Rule (Optimization)**

If an old transaction tries to **write a value that has already been overwritten by a newer one**,

we can **ignore** the old write instead of aborting it.

```
If TS(Ti) < Write_TS(X):
   → Ignore write (safe to skip)
```

This reduces unnecessary aborts — improves concurrency.

---

### **Deadlock in a Distributed System**

In a distributed system, a **deadlock** is a state where a set of processes are blocked because each process is holding a resource and waiting for another resource acquired by some other process in the set.

The critical difference in a *distributed* context is that these processes and resources are spread across different **sites** (nodes) in a network.

> Simple Analogy: Imagine two people, Alice (in Delhi) and Bob (in Mumbai).
> 
> - Alice locks the **"Database A"** file and needs **"Database B"** to finish.
> - Bob locks the **"Database B"** file and needs **"Database A"** to finish.
> - Neither can proceed, and because they are in different cities, they might not immediately know the other is waiting.

---

### **1. The Four Necessary Conditions (Coffman Conditions)**

Just like in centralized systems, a deadlock can only occur if these four conditions happen simultaneously:

1. **Mutual Exclusion:** Resources cannot be shared (only one process uses it at a time).
2. **Hold and Wait:** A process holding at least one resource is waiting to acquire additional resources held by others.
3. **No Preemption:** Resources cannot be forcibly taken away from a process; they must be released voluntarily.
4. **Circular Wait:** There is a closed chain of processes (P1 → P2 → ... → Pn → P1), where each is waiting for the next.

### **2. Why is it harder in Distributed Systems?**

Handling deadlock in a single computer is relatively easy because the OS knows everything. In a distributed system, it is much harder due to:

- **No Global State:** No single site has a complete, up-to-date view of the entire system.
- **Communication Delays:** Message passing takes time. By the time Site A learns that Site B has released a lock, Site A might have already decided a deadlock exists.
- **Phantom Deadlocks:** Due to network delays, the system might detect a deadlock that doesn't actually exist (e.g., a "release" message was lagging in the network).

### **3. How to Handle It: Detection & Resolution**

Since "preventing" deadlock is very expensive in distributed systems (it hurts performance too much), we usually allow deadlocks to happen and then **detect** and **resolve** them.

### **A. Centralized Deadlock Detection**

- **How it works:** One specific node is designated as the **Control Site**. All other sites send their "Wait-For Graphs" (who is waiting for whom) to this central site.
- **Pros:** Simple to implement.
- **Cons:** The control site becomes a bottleneck and a **Single Point of Failure**. If it crashes, detection stops.

### **B. Distributed Deadlock Detection**

- **How it works:** All sites cooperate to detect cycles without a single leader.
- **Common Method (Edge Chasing / Chandy-Misra-Haas):**
    - If Process A is waiting for Process B, it sends a special "Probe" message.
    - If that Probe message gets passed around and eventually comes back to Process A, it knows there is a cycle.
- **Pros:** Robust; no single point of failure.
- **Cons:** High message traffic overhead.

### **C. Hierarchical Deadlock Detection**

- **How it works:** Sites are grouped into clusters. A local coordinator manages deadlocks within a cluster, and a global coordinator manages deadlocks *between* clusters.
- **Pros:** Balances the load better than the centralized approach.

we already studied centralized (Wait-For Graph) and chandy misra algo

### **Hierarchical Deadlock Detection**

You can think of **Hierarchical Deadlock Detection** as the "middle ground" between the Centralized approach (one boss for everyone) and the Distributed approach (everyone is their own boss).

In this method, sites are organized into **clusters** or groups (like departments in a company).

1. **Local Coordinator:** Each cluster has a "manager" that detects deadlocks *inside* that cluster.
2. **Global Coordinator:** Above these local managers, there are higher-level managers that detect deadlocks *between* clusters.

**1. How It Works (The Hierarchy)**

Instead of one giant Wait-For Graph (WFG) for the whole world (which is slow) or thousands of tiny fragments (which is chatty), we build a **Tree of Coordinators**.

- **Leaf Nodes (Level 0):** These are the actual database sites where transactions happen. They manage their own local locks.
- **Level 1 Coordinators:** Several sites report to a Level 1 coordinator. This coordinator builds a WFG just for its children. If it finds a cycle, it resolves it.
- **Level 2 (and up) Coordinators:** If a transaction in *Cluster A* is waiting for a transaction in *Cluster B*, the Level 1 coordinators won't see the full cycle. They pass this "dependency info" up to the Level 2 coordinator, who sees the bigger picture.

**Cons of Hierarchical Deadlock Detection**

**In the Hierarchical Deadlock Detection if the level 1 cluster node fail then ? who sees the deadlock for that cluster?**

If a **Level 1 coordinator** (the "manager" of a local cluster) fails in a Hierarchical Deadlock Detection system, it creates a **Single Point of Failure** for that specific group.
Here is exactly what happens, broken down by immediate impact and how the system fixes it:

**1. The Immediate Impact (The "Blackout")**
When the Level 1 coordinator crashes, two major things go wrong:

- **Local Deadlocks go undetected:** If Transaction A and Transaction B are both inside this cluster and deadlock with each other, no one notices. They will wait indefinitely.
- **Global Deadlocks break:** The "chain" of reporting is broken. If a global deadlock cycle passes *through* this cluster (e.g., Cluster A $\to$ **Cluster B (Failed)** $\to$ Cluster C $\to$ Cluster A), the Level 2 (parent) coordinator will never receive the report from Cluster B. The global deadlock remains undetected.
- **Visual:** Imagine a corporate team where the Manager is sick. The CEO (Level 2) doesn't know what's happening inside the team, and the team members (Level 0) have no one to report their problems to.

**Recovery strategies for scenario where a cluster node goes down**

**A. Election Algorithms (The most common solution)**

The remaining active sites in the cluster realize their coordinator is dead (usually because it stops sending "heartbeat" signals). They immediately hold an **Election** to pick a new coordinator.

- **Bully Algorithm:** The site with the highest process ID "bullies" the others and declares itself the new coordinator.
- **Ring Algorithm:** Sites pass a message around in a circle to decide who becomes the new leader.
- *Once elected, all sites send their wait-for graphs to the new leader, and detection resumes.*

**B. Backup Coordinator (Hot Standby)**

In mission-critical systems, a **Backup Coordinator** is maintained.

- It receives copies of all the Wait-For Graphs that the main coordinator gets.
- If the main coordinator crashes, the backup instantly takes over without needing an election.

### 

<!-- gemini chat: https://gemini.google.com/app/6d93fbfb2bc0912a  -->

<!-- gpt: https://chatgpt.com/c/68f0c431-6dcc-8323-ab10-fe69eebe39ef -->

<!-- claude: https://claude.ai/chat/0ce03217-ce5d-435b-b8e9-4033b1236ef2 -->