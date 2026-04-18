# Ford-Fulkerson Method: Flow Networks

## 1. Context Setting
Imagine a city's water supply system. You have a main water treatment plant (the **Source**) and a neighborhood that needs water (the **Sink**). Between them lies a network of pipes, junctions, and valves. 

Every pipe has a strict physical limit on how much water it can carry per second. If you randomly blast water through the network, you might accidentally fill up a wide pipe that leads to a narrow bottleneck, causing a jam and wasting the potential of other empty pipes. The Ford-Fulkerson method is a mathematical approach to perfectly route the water to ensure the absolute maximum volume reaches the destination without exceeding any pipe's limits.

## 2. Requirement (The Goal)
The objective is to find the **Absolute Maximum Flow**. You must calculate the highest possible total volume of flow that can be pushed from the Source (S) to the Sink (T) simultaneously, under the given network constraints.


## Why can't we use a random path for Flow Network ?
![](https://i.ibb.co/DmvqQbr/image.png)

<u>**Scenario 1: The "Dumb" Greedy Mistake (The Jam)**</u>

You are at the Source (S). You want to push water to T.
You look at your map and say, "Hey, S to A, then A to B, then B to T is a valid path! Let's blast water down that route."

You push 10 liters through: S -> A -> B -> T

The Result: The pipe S -> A is now completely full. The pipe B -> T is also completely full.

**Where is the wasted potential?**

Look at the pipes you didn't use:

You have an empty pipe from S to B (can hold 10 liters). But if you send water to B, it has nowhere to go because the B -> T exit pipe is already jammed full from your first move.

You have an empty pipe from A to T (can hold 10 liters). But you have no way to get water to A, because the S -> A entrance pipe is already jammed full.

Because of one greedy, bad choice, you created a bottleneck. You are delivering exactly 10 liters/sec, and the system is deadlocked.


<u>**Scenario 2: The Optimal Approach**</u>

If you step back and look at the whole system, the smarter routing is obvious:

Route 1: Send 10 liters straight through S -> A -> T.

Route 2: Send 10 liters straight through S -> B -> T.

Now you are delivering 20 liters/sec. Nothing is jammed. The cross-pipe (A -> B) is completely ignored, and that is perfectly fine.


## 3. Core Terminologies
* **Capacity Constraint:** The flow running through any edge cannot exceed that edge's maximum capacity.
* **Flow Conservation:** For every node (except Source and Sink), the total flow entering the node must exactly equal the total flow leaving it.
* **Residual Graph:** A dynamic, updated version of the network that tracks how much capacity is left on every path.
* **Augmenting Path:** Any valid path from Source to Sink in the residual graph where every edge has at least 1 unit of available capacity.
* **Bottleneck:** The smallest available capacity along a chosen augmenting path. This dictates the maximum flow you can push down that specific route.
* **Forward Edge:** The remaining capacity you can push in the normal direction of the pipe.
* **Backward Edge:** An imaginary pipe created by the algorithm in the opposite direction of the flow you just pushed. It acts as an "Undo" mechanism, allowing the algorithm to pull flow back later if it realizes it made a poor routing choice.

![](https://i.ibb.co/8nKCsBBw/image.png)
---

## 4. Step-by-Step Dry Run (4-Node Network)

![](https://i.ibb.co/rKmQtFFX/image.png)

**Initial Network Capacities:**
* S -> A: 12
* S -> B: 8
* A -> B: 6
* A -> T: 7
* B -> T: 11

*Initial Total Flow: 0*

### Step 1: The Greedy Path
* **Chosen Path:** `S -> A -> B -> T`
* **Available Capacities:** S->A (12), A->B (6), B->T (11)
* **Bottleneck:** 6 (from A->B)
* **Action:** Push 6 units of flow.
* **Residual Graph Updates:**
    * *Forward Edges (Decrease):* S->A has 6 left. A->B has 0 left. B->T has 5 left.
    * *Backward Edges (Increase):* A->S gets +6. B->A gets +6. T->B gets +6.
* **Total Max Flow:** 0 + 6 = 6
![](https://i.ibb.co/tTGFVw3V/Screenshot-2026-04-18-at-11-17-03-PM.png)


### Step 2: The Direct Path
* **Chosen Path:** S -> A -> T
* **Available Capacities:** S->A (6 left), A->T (7)
* **Bottleneck:** 6 (from S->A)
* **Action:** Push 6 units of flow.
* **Residual Graph Updates:**
    * *Forward Edges (Decrease):* S->A has 0 left. A->T has 1 left.
    * *Backward Edges (Increase):* A->S goes to 12 (6+6). T->A gets +6.
* **Total Max Flow:** 6 + 6 = 12
![](https://i.ibb.co/Psz9Sm4m/image.png)


### Step 3: The Alternate Direct Path
* **Chosen Path:** S -> B -> T
* **Available Capacities:** S->B (8), B->T (5 left from Step 1)
* **Bottleneck:** 5 (from B->T)
* **Action:** Push 5 units of flow.
* **Residual Graph Updates:**
    * *Forward Edges (Decrease):* S->B has 3 left. B->T has 0 left.
    * *Backward Edges (Increase):* B->S gets +5. T->B goes to 11 (6+5).
* **Total Max Flow:** 12 + 5 = 17
![](https://i.ibb.co/nsB3LwpL/image.png)


### Step 4: The "Undo" Move (Using the Backward Edge)
We still have 3 units of capacity left at S->B, and 1 unit left at A->T. But how do we get from B to A? We use the backward edge we created in Step 1!
* **Chosen Path:** S -> B -> A -> T
* **Available Capacities:** S->B (3 left), B->A (6 backward capacity), A->T (1 left)
* **Bottleneck:** 1 (from A->T)
* **Action:** Push 1 unit of flow. By pushing 1 unit "backward" from B to A, we are essentially cancelling 1 unit of flow that we sent from A to B in Step 1.
* **Residual Graph Updates:**
    * *Edge S->B:* Forward capacity decreases to 2. Backward B->S increases to 6.
    * *Edge B->A (The Undo):* Since we used a backward edge, its capacity decreases from 6 to 5. The forward edge A->B regains 1 unit of capacity (it goes from 0 back to 1).
    * *Edge A->T:* Forward capacity decreases to 0. Backward T->A increases to 7.
* **Total Max Flow:** 17 + 1 = 18
![](https://i.ibb.co/GQDZRRn0/image.png)

* This Back-Edge choosen means that originally in actual graph the edge was from `A---6-->B` then in step1 we choose `S->A->B->T` which used 6 units of that capacity, so that capacity now becomes 0 `A---0-->B` but since in last step we needed to go to A using backedge `B---6--->A` and our bottle neck is 1, so we need 1 unit from the backedge , so new backedge value is decremented by 1 so new backedge `B----5--->A` means we used the backward edge to "undo" 1 unit of that flow...

Final Residual Graph:



### 5. Termination
Looking at the residual graph, there are no more valid paths from S to T. S->A is at 0. S->B has 2, but from B, the path B->T is at 0, and the path B->A->T is blocked because A->T is at 0.

**Absolute Maximum Flow = 18**
