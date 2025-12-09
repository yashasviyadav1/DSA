# MT-CSE-18-13(iii): Introduction to Intelligent Systems

Full syllabus:- 
![backup image](https://i.ibb.co/BK7ydn1S/syllabus.webp)

### **Overview of all Units**

It covers the transition from traditional algorithms to systems that can handle ambiguity, learn from data, and mimic biological processes. In essence, this course teaches you **how to build software that "thinks" rather than just calculates.**
Here is a brief overview of the subject and a breakdown of each unit.

### **What is an "Intelligent System"?**

Traditional programming is rigid (if $X$, then $Y$). Intelligent Systems are designed to solve problems where the rules aren't clear-cut, the data is noisy, or the search space is too massive to check every possibility.
**This course focuses on three pillars of AI:**
1. **Biologically Inspired Computing:** Mimicking the human brain (Neural Networks) and evolution (Genetic Algorithms).
2. **Search & Logic:** How a computer explores options to find the best solution (like a chess bot looking for the best move).
3. **Uncertainty:** How computers make decisions when they are only 70% sure of the facts (Fuzzy Logic, Bayesian Probabilities).

### **Unit-by-Unit Breakdown**

**Unit 1: Biological Foundations & Soft Computing**

This unit focuses on methods inspired by nature. You will move away from "True/False" logic into "Partial Truths" and brain-like structures.

- **Neural Networks (ANNs):** You will learn about the basic building blocks of modern AI—perceptrons, back-propagation (how networks learn from mistakes), and Recurrent Networks (memory).
- **Fuzzy Logic:** Handling vague concepts. A standard computer thinks a temperature of $25^\circ\text{C}$ is precise. Fuzzy logic allows the computer to understand "It is warm."
- **Genetic Algorithms:** Solving optimization problems by simulating "survival of the fittest," where the best solutions "breed" to create better ones.

**Unit 2: Search Methods & Optimization**

This unit is the backbone of Classical AI. It asks: *How do we navigate from a starting state to a goal state?*

- **Blind Search:** Exploring every option (BFS, DFS).
    - **Heuristic Search:** Using "rules of thumb" to search smarter, not harder (Best-first, Hill-climbing).
- **Optimization:** Techniques like **Simulated Annealing** (inspired by metallurgy) to find the best global solution without getting stuck in local imperfections.

**Unit 3: Knowledge Representation**

AI is useless if it doesn't know anything. This unit covers how we structure information so a machine can use it.

- **Structured Representation:** Using **Frames** and **Scripts** (e.g., telling a computer what usually happens in a "Restaurant" so it understands the context of "ordering food").
- **Semantic Networks:** Mapping relationships (e.g., "Cat" *is-a* "Mammal").
- **Expert Systems:** Architectures like "Blackboard systems" where different AI agents collaborate to solve a problem.

**Unit 4: Reasoning Under Uncertainty & Learning**

Real-world data is messy. This unit teaches how to reason when you don't have all the facts.

- **Probabilistic Reasoning:** Using **Bayesian networks** to calculate the probability of an event based on prior knowledge.
    - **Evidence Theory:** Dempster-Shafer theory (handling ignorance vs. uncertainty).
- **Learning:** A brief introduction to how machines induce rules from data (Statistical learning), bridging the gap into modern Machine Learning.

---

# Unit 1

### **Biological Foundations & Artificial Neural Networks (ANN)**

The first topic of Unit 1 is **Biological Foundations**. This is the "Origin Story" of AI. The core idea is simple: *The most intelligent system we know is the human brain. If we want to build a smart machine, why not copy the brain's architecture?* This leads us to the **Artificial Neural Network (ANN)**.

**1. The Biological Inspiration**

Your brain is made of billions of cells called **Neurons**. They don't process information like a CPU (sequentially); they process it in parallel, sending electrochemical signals to each other.

An Artificial Neural Network is a simplified mathematical model of this biological system. Here is the direct mapping: 

| **Biological Neuron** | **Artificial Neuron (Node)** | **Function** |
| --- | --- | --- |
| **Dendrites** | **Inputs ($x$)** | Receives signals from other neurons/sources. |
| **Synapse** | **Weights ($w$)** | Determines the *strength* of the connection. |
| **Soma (Cell Body)** | **Summation Function** | Adds up all incoming signals. |
| **Axon** | **Output ($y$)** | Transmits the processed signal to the next neuron. |

**2. The Structure of an ANN**

An ANN is not just one neuron; it is a massive web of them connected in layers.

- **Input Layer:** The "eyes" of the network. It receives raw data (pixels of an image, rows from a database) and passes it forward. No processing happens here.
- **Hidden Layers:** The "brain" of the network. These layers sit between input and output. They perform the calculations and feature extraction. "Deep Learning" just means having many hidden layers.
- **Output Layer:** The "mouth" of the network. It gives you the final result (e.g., "Yes, this is a cat" or "Price: $500")

**3. How a Single Neuron "Thinks" (The Mathematical Model)**

It happens in two steps:

1. Weighted Sum: The neuron multiplies every input ($x$) by its weight ($w$) and adds them up, plus a "bias" ($b$) (which helps shift the activation function).
    
    $Z = (x_1 \cdot w_1) + (x_2 \cdot w_2) + \dots + b$
    

2. **Activation:** The neuron decides if this signal is strong enough to pass on. It applies an **Activation Function** (like a switch) to the result $Z$.

- *Example:* If $Z > 0.5$, output 1 (Fire). If $Z < 0.5$, output 0 (Don't fire).
- **Analogy:** Imagine you are deciding whether to study tonight.
    - **Input 1:** Is the exam tomorrow? (Weight: High importance)
    - **Input 2:** Are friends going out? (Weight: Medium importance)
    - **Activation:** If the weighted sum of "Exam Pressure" is higher than the "FOMO" (Fear Of Missing Out), the neuron fires "Study."


**Activation function:**

Activation Function is simply the **mathematical formula** that takes that weighted sum and calculates the final output.
that if (Z > 0.5) output 1 is example of activation formula

- The function looks at the weighted sum and checks: **"Is this number big enough to matter?"**
- **If YES (Important):** It keeps the number big (or makes it 1). The neuron "fires" and shouts the message to the next layer.
- **If NO (Not Important):** It turns the volume down to 0 (or a very small number). The neuron stays silent.

**Example:** If you are trying to recognize a **cat**, the neurons looking for "whiskers" should scream "YES!" (send signal). The neurons looking for "wheels" should be silent (ignore/output 0).

> "It decides if the signal is important enough to pass on, thereby introducing **non-linearity** to the network."
>

**ReLU - Rectified Linear Unit**

Modern networks use a function called ReLU (Rectified Linear Unit), which acts like a dimmer switch that can turn off completely but has no upper limit.

Rule: If the sum is negative, output 0. If the sum is positive, output the number itself.

Meaning: "If the signal is weak/negative, kill it completely (switch OFF). If it's positive, let it through exactly as is."

---

Example:
The "Intelligence" in these systems comes from the **Weights**.

- At first, the network is stupid; the weights are random.
- As it sees data (training), it adjusts the weights (e.g., "Pay more attention to Input 1, ignore Input 2").
- This process of adjusting weights to reduce errors is called **Learning** (specifically *Back-Propagation*, which is the next major topic).

---

### **Back-Propagation (The "Learning" Algorithm)**

If the Neural Network structure is the "Brain," then **Back-Propagation (Backprop)** is the "Education." Without it, the network is just a random guesser. It is the standard algorithm used to train neural networks.

**1. The Core Concept**

Back-Propagation is short for **"Backward Propagation of Errors."**
It works on a simple cycle:

1. **Forward Pass:** The network makes a guess.
2. **Calculate Error:** It checks how wrong the guess was.
3. **Backward Pass:** It goes back through the layers to find out **which weights contributed most to the error**.
4. **Update:** It adjusts those weights so the next guess is slightly better.
    
    **Analogy: Shooting a Basketball**
    
    - **Forward Pass:** You throw the ball (Input) and miss the hoop by 1 meter to the right (Output).
    - **Calculate Error:** The error is "1 meter right."
    - **Backward Pass:** Your brain analyzes what went wrong. Was it your wrist? Your elbow? Your stance? You realize your wrist flicked too hard.
    - **Update:** You adjust your wrist strength for the next shot.
    

**2. The Process: Step-by-Step**

**Step 1: The Forward Pass (Prediction)**

- Data enters the Input Layer.
- It flows through hidden layers (getting multiplied by weights and passing through activation functions).
- The Output Layer produces a prediction (e.g., $0.8$).

**Step 2: Error Calculation (Loss Function)**

- We compare the Predicted Output ($Y_{pred}$) with the Actual Target ($Y_{target}$).
- We calculate the Error (or Loss) using a formula (commonly Mean Squared Error):
$Error = \frac{1}{2}(Y_{target} - Y_{pred})^2$

**Step 3: The Backward Pass (Assigning Blame)**

- This is the magic part. The algorithm asks: *"Who is responsible for this error?"*
- It moves **backward** from Output $\rightarrow$ Hidden $\rightarrow$ Input.
- It uses **Calculus (The Chain Rule)** to calculate the **Gradient**. The Gradient tells us how much a change in a specific weight would change the total error.
    - *High Gradient:* This weight caused a lot of error. Change it a lot.
    - *Low Gradient:* This weight was mostly fine. Don't touch it much.

**Step 4: Weight Update (Optimization)**

- We adjust the weights using a technique called **Gradient Descent**.
- **Formula:** $W_{new} = W_{old} - (\text{Learning Rate} \times \text{Gradient})$
- **Learning Rate ($\eta$):** A small number (like 0.01) that controls how big the step is. If it's too big, you might overshoot the solution.

**3. Key Term: Gradient Descent**

To understand Backprop, you must mention **Gradient Descent.**

Gradient Descent is an iterative optimization algorithm used to minimize a Cost Function. It works by calculating the gradient (slope) of the error surface and updating the model parameters (weights) in the opposite direction to reach the Global Minima.

Imagine you are standing on top of a mountain (High Error) blindfolded, and you want to get to the bottom of the valley (Zero Error).

- You feel the slope of the ground under your feet (The Gradient).
- If the slope goes down to the left, you take a step left.
- You keep doing this until the slope is flat (you reached the bottom)
    - **Global Minima:** The absolute lowest point (The perfect model).
    - **Local Minima:** A small valley where you might get stuck thinking it's the bottom, but there is a deeper valley nearby.


**<u>The Analogy vs. Technical Reality</u>**

| **The Analogy (Mountain)** | **The Technical Term (Neural Network)** |
| --- | --- |
| **The Mountain** | The **Loss Function** (or Cost Function). This represents all possible errors. |
| **Your Height** | The **Error** (High altitude = High Error, Low altitude = Low Error). |
| **Blindfolded Person** | The **Algorithm** (It can't see the whole map; it only knows where it is right now). |
| **Feeling the Slope** | Calculating the **Gradient** (Derivative). This tells you which direction is "down." |
| **Taking a Step** | Updating the **Weights**. |
| **Size of the Step** | The **Learning Rate** (Big steps are faster but risky; small steps are safer but slower). |

---

These are two specialized types of Neural Networks designed to solve specific problems that the standard Back-Propagation network struggles with.

### Radial Basis Function Networks (RBFN)

A radial basis function (RBF) is a special type of mathematical function where the function's output depends solely on the distance from a fixed central point [1]

(describes something spreading out from a center, like rays, or relates to the forearm's radius bone)

While standard neural networks use lines and planes to separate data (like slicing a cake), RBFNs use **circles and spheres**.

**The Core Concept: "Distance" instead of "Sum"**

In the standard networks we just discussed, a neuron calculates a "Weighted Sum" ($Input \times Weight$).

But **RBFN is different:** The neurons in the hidden layer calculate the **Distance** between the input and a "Center Point."

- If the input is *close* to the center, the neuron fires strongly.
- If the input is *far* away, the neuron stops firing.

**2. The "Radial Basis" Function (The Bell Curve)**

The activation function used here is usually a **Gaussian Function** (looks like a Bell Curve).

- **Center:** The peak of the bell curve.
- **Radius:** How wide the bell curve is.
- **Intuition:** Imagine a map with several radio towers. If you are standing right next to a tower (Center), your signal is strong (1.0). As you walk away (Radial distance), the signal fades to 0

**3. Architecture (3 Layers Only)**

RBFNs typically have a very strict 3-layer structure:

- **Input Layer:** Passes data through.
- **Hidden Layer (RBF Layer):** Calculates the distance from the center. It uses the "Kernel Trick" to map data into higher dimensions,  Each hidden neuron contains a **radial basis function** like **Gaussian function**. The response depends on the **distance** between input and neuron's center.
- **Output Layer:** A simple linear combination (sum) of the hidden layer's signals.

![](https://i.ibb.co/GfHL27MW/image.png)

> RBFNs are Faster to train than Back-Propagation networks because the hidden layer often doesn't need to be "trained" iteratively; the centers can be fixed using clustering (like K-Means).
> 

**4. What is a Radial Basis Function?**

Most common RBF: **Gaussian Function**

> $\phi(x) = e^{-\frac{||x - c||^2}{2\sigma^2}}$
> 

Where:

- $x$ = input
- $c$ = center of Gaussian
- $\sigma$ = width/spread

**Key idea:** the neuron's output is **high** when input is close to its center, and low when far.

![](https://i.ibb.co/xt8M391G/image.png)

**Radial Basis Function Example: Fruit Classification System**

**Problem:** You run a fruit sorting machine. Based on **weight** and **color intensity** (0-10 scale), classify fruits as Apple, Orange, or Banana.

Your Training Data:

```sql
**Apples:** (150g, color=7), (160g, color=8), (155g, color=7)
**Oranges:** (180g, color=9), (175g, color=10), (182g, color=9)
**Bananas:** (120g, color=3), (118g, color=4), (125g, color=3)
```

Visualize this on a 2D graph:

```sql
Color
10 |              O O
 9 |              O
 8 |        A
 7 |        A A
 6 |
 5 |
 4 |    B
 3 |    B B
   |________________
     100  150  180  Weight
```

Now Build the RBF Network:

**Step 1: Place RBF Centers** (one for each fruit type)

- RBF₁ center at (155, 7.3) → "Apple detector"
- RBF₂ center at (179, 9.3) → "Orange detector"
- RBF₃ center at (121, 3.3) → "Banana detector"

**Step 2: Set the radius** (let's say σ = 15 for all)

Let's Test with a NEW fruit: (152g, color=7)

Calculate each RBF's response:

**RBF₁ (Apple detector):**

- Distance = √[(152-155)² + (7-7.3)²] = √[9 + 0.09] ≈ 3.01
- Output = exp(-3.01² / (2×15²)) = exp(-0.02) ≈ **0.98** ✅ Strong!

**RBF₂ (Orange detector):**

- Distance = √[(152-179)² + (7-9.3)²] = √[729 + 5.29] ≈ 27.1
- Output = exp(-27.1² / (2×15²)) = exp(-1.63) ≈ **0.20** ❌ Weak

**RBF₃ (Banana detector):**

- Distance = √[(152-121)² + (7-3.3)²] = √[961 + 13.69] ≈ 31.2
- Output = exp(-31.2² / (2×15²)) = exp(-2.16) ≈ **0.11** ❌ Weak

**Hidden layer outputs:** [0.98, 0.20, 0.11]

**Step 3: Output layer** (simple weighted sum)

- Apple output = $w₁×0.98 + w₂×0.20 + w₃×0.11$
- Orange output = ...
- Banana output = ...

**Result:** Highest output → **APPLE!** ✅

**How is RBFN model trained ?**

RBF training typically happens in **2 separate phases** (unlike backpropagation where everything trains together):

**PHASE 1: Find the Centers**

You need to decide where to place the RBF neurons. Three common methods:

**Method: K-Means Clustering** (Most Popular)

This is the best method!, k here means the number of clusters.

**How K-Means works for our fruit example:**

1. **Initialize:** Place 3 random centers (1 for each cluster)
2. **Assignment:** Assign each fruit to its nearest center
3. **Update:** after all the fruits are assigned to their nearest cluster, now calculate the average of each cluster. Move each center to the average of its assigned fruits.

**After K-Means on our data:**

```sql
Cluster 1 (Apples):     Center = (155, 7.3)
Cluster 2 (Oranges):    Center = (179, 9.3)
Cluster 3 (Bananas):    Center = (121, 3.3)
```

These become your RBF centers

> ***K mean simply means:** Firstly we randomly choose k fruits and make them the centre of the k clusters. now In each iteration, you go through ALL your data points one by one and assign each to its nearest cluster. AFTER you've assigned ALL the data points, THEN you calculate the new center for each cluster by taking the mean of all points in that particular cluster. Repeat this process until the centers stop moving.*
> 

---

### Recurrent Neural Networks (RNN)

Standard networks (and RBFNs) are **Feed-Forward**. Data moves in one direction: Input $\rightarrow$ Output. They have **No Memory**. 

If you show a Feed-Forward network a movie, it doesn't know that "Frame 2" is related to "Frame1." **RNNs are designed to remember.**

<!-- ![alternatve img url](https://i.ibb.co/CD11n5S/image.png) -->

![github url](https://private-user-images.githubusercontent.com/124666305/524393110-7a870c74-5c93-428c-8a7a-5c9efc5b388a.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjUyOTczODcsIm5iZiI6MTc2NTI5NzA4NywicGF0aCI6Ii8xMjQ2NjYzMDUvNTI0MzkzMTEwLTdhODcwYzc0LTVjOTMtNDI4Yy04YTdhLTVjOWVmYzViMzg4YS5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUxMjA5JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MTIwOVQxNjE4MDdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1jYTU1MmIxMGUyZjg1OGE3Y2RlOWUzYzI2ODUyNDE3MWVhOWE1OGE0MTYxNzJmYTdhMjUwNjhkODBhNzA3NmNlJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.vRTsNxxUoYDxsIBZX_aEl2XUcddWHMxPLPIpGg6q5oE)

**1. The Core Concept: Loops**

In an RNN, the output of a neuron is fed back into itself (or to the next time step) as an input.

**Equation:** `Current Output = Input + *Previous Output*`

This creates a "Short-term Memory." The network makes a decision based on what it sees *now* AND what it saw *a moment ago*.

**2. Unfolding the Network**

To understand how it learns, we often "unfold" the loop over time (as seen in diagrams).

- Time $t_1$: Network processes word "Hello".
- Time $t_2$: Network processes word "World", but it *also* receives the hidden state from $t_1$.
- This allows it to understand context (e.g., predicting the next word in a sentence).

**what does `unfold` the loop over time means in RNN?**

Unfolded (For Understanding/Training)

```sql
t₁: "I"           t₂: "love"        t₃: "AI"
┌─────┐          ┌─────┐          ┌─────┐
│ RNN │─ h₁ ────→│ RNN │─ h₂ ────→│ RNN │─ h₃
└─────┘          └─────┘          └─────┘
  ↓                ↓                ↓
  y₁               y₂               y₃
```

- $h₁, h₂, h₃$ = hidden states (memory being passed forward)
- $y₁, y₂, y₃$ = outputs at each time step
- Arrows between cells = hidden state flowing through time

> Key Insight: It's the SAME Cell!, Important: The "unfolded" diagram shows the same RNN cell multiple times, not different cells!
> 

**Confusion between hidden state $h$ and result $y$**

> Note: y₁ ≠ h₁, y₂ ≠ h₂, y₃ ≠ h₃ because $y_1$ means result from current state and $h_1$ means hidden state that we will pass on to next state.
> 

Lets say we recieved $h_0$ hidden state (memory of past events) from the previous state of neural network and $x_0$ is our new input we get in current state.

So we calculate: new hidden state (which will be passed to next state) from the previous hidden state $h_0$ and current input $h_0$ :

$h₁ = f(x₁, h₀)$

and our output of current state $y_1$ is calculated from $h_1$ :

$y₁ = g(h₁)$

*Therefore we can say that $y_1$ is not exactly equal to $h_1$, it is rather it is calculated using $h1$ that is $y_1$ is a function of h1*

So the final order is this:  `h₁ (from previous) + x₂ (current input) → h₂ → y₂`

**3. The Problem: Vanishing Gradient**

A common question regarding RNNs is their limitation.

- When you use Back-Propagation on a long sequence (Back-Propagation Through Time), the error signals get smaller and smaller until they vanish.
- This means basic RNNs have trouble remembering things from a long time ago (e.g., the start of a long paragraph). *Note: This led to the invention of [**LSTMs**](https://www.geeksforgeeks.org/deep-learning/deep-learning-introduction-to-long-short-term-memory/), though LSTMs are not explicitly named in this unit's list.*
- This problem is called Vanishing Gradient

**Short Intro to Long Short Memory mode (LSM)**

Long Short-Term Memory (LSTM) is an enhanced version of the [**Recurrent Neural Network (RNN)**](https://www.geeksforgeeks.org/machine-learning/introduction-to-recurrent-neural-network/)

LSTMs can capture long-term dependencies in sequential data making them ideal for tasks like language translation, speech recognition and time series forecasting, Music generation. Unlike traditional RNNs which use a single hidden state passed through time LSTMs introduce a memory cell that holds information over extended periods addressing the challenge of learning long-term dependencies.

<!-- ![alternative url](https://i.ibb.co/hxZHg1sr/image.png) -->
![github url img](https://private-user-images.githubusercontent.com/124666305/524419340-0863df95-6e48-4f14-a660-3b7fa0780432.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjUzMDA1NjcsIm5iZiI6MTc2NTMwMDI2NywicGF0aCI6Ii8xMjQ2NjYzMDUvNTI0NDE5MzQwLTA4NjNkZjk1LTZlNDgtNGYxNC1hNjYwLTNiN2ZhMDc4MDQzMi5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUxMjA5JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MTIwOVQxNzExMDdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT04NGQ3NzY0ZjQwZTIyODdhNWJhODMyN2IyMTBhOThjZjNiYTZmZGRiZjAxY2EzOTQ5ZTM0M2NkZGE5NGFhOGM5JlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.Edx8Ew5tLHbmH9HOKqc5RsScV2SmiE3ODYGsbVGRGHc)


<!-- ![alternative url](https://i.ibb.co/Y43pwCvb/image.png) -->
![github url](https://private-user-images.githubusercontent.com/124666305/524419514-a8f2773c-be59-4775-9b3f-c014dbd46932.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjUzMDA1NjcsIm5iZiI6MTc2NTMwMDI2NywicGF0aCI6Ii8xMjQ2NjYzMDUvNTI0NDE5NTE0LWE4ZjI3NzNjLWJlNTktNDc3NS05YjNmLWMwMTRkYmQ0NjkzMi5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUxMjA5JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MTIwOVQxNzExMDdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1lOTFlMzA0OGY0MzE3OWQ3NmJmOGNiOWY4OTQ1NWY1ZjgzMWIzMDhiZGIxNDAxNGY5MDk0NjJhMTM3Y2Q0NTFmJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.72XdtOld6eWVcPyfynSe9KexMDbY7OH8Lq35UopO8hY)


It mainly has 3 things at each state:

- $x$ : input of current state
- $h_{i-1}$ : working memory or short memory from previous step
- $C$ : Long-term memory from previous step

*So this long term memory is passed to current state in a memory unit attached. and this way the model never forgets the main points from the past, whereas keeping the previous steps memory (short memory)*


---

### **Fuzzy Logic**

This is one of the most interesting topics in Unit 1 because it bridges the gap between how computers think (Binary) and how humans think (Approximations).

Standard computers rely on **Boolean (Crisp) Logic**:

- Is the water hot? **Yes (1) or No (0).**
- If the temperature is $40^\circ\text{C}$, the computer says "Hot." If it is $39.9^\circ\text{C}$, it says "Not Hot." This is rigid and often useless in the real world.

**Fuzzy Logic** introduces "Degrees of Truth":

- Is the water hot? **0.8 (It is mostly hot).**
- It allows values *between* 0 and 1.

**1. Key Components of Fuzzy Logic**

To answer a question on this, you need to define these three core terms:

- **Linguistic Variables:** Variables whose values are words, not numbers.
    - *Example:* Instead of saying "Fan Speed = 500 RPM", we say "Fan Speed is **Medium**."
- **Membership Function ($\mu$):** A mathematical curve that defines *how much* an input belongs to a category.
    - *Example:* A temperature of $30^\circ\text{C}$ might belong **30%** to the "Warm" category and **70%** to the "Hot" category.
- **Fuzzy Rules (The Knowledge Base):** Simple IF-THEN statements used for decision making.
    - *Rule 1:* IF temperature is *Hot*, THEN fan speed is *Fast*.
    - *Rule 2:* IF temperature is *Warm*, THEN fan speed is *Medium*.

**2. The Fuzzy System Architecture (Process Flow)**

It has four distinct stages:

**1. Fuzzification (Input Stage):**

- Take the "Crisp" input (e.g., Temperature = $28^\circ\text{C}$) and convert it into fuzzy values using the membership function.
    ◦ *Result:* "Temperature is 0.6 Warm and 0.2 Hot."

2. **Knowledge Base (Rule Base):**

- Stores the "IF-THEN" rules defined by experts.

3. **Inference Engine (Processing Stage):**

- It looks at the fuzzy inputs and the rules to determine the fuzzy output.
- Since the input matches *two* rules (Warm and Hot), it combines the results.
- *Result:* "Fan speed should be mostly Medium, but slightly Fast."

4. **Defuzzification (Output Stage):**

- The machine cannot set the fan to "Mostly Medium." It needs a number.
- Defuzzification converts the fuzzy conclusion back into a "Crisp" value (e.g., **450 RPM**) using methods like **Centroid (Center of Gravity)**.

**3. Fuzzy Neural Networks (Neuro-Fuzzy Systems)**

This is a **Hybrid System**.

- **The Problem with Fuzzy Logic:** You have to manually write the rules ("If hot, then fast"). If you don't know the rules, you are stuck.
- **The Problem with Neural Networks:** They are "Black Boxes." They give you an answer, but can't explain *why* (no clear rules).
- The Solution: A Fuzzy Neural Network (often called ANFIS → Adaptive Neuro-Fuzzy Inference System) uses a Neural Network to learn the Fuzzy Rules from data.
    - It looks like a neural network, but the hidden neurons represent "Fuzzy Rules" instead of just mathematical weights.
    - **Benefit:** You get the learning power of an ANN with the explainability of Fuzzy Logic.

---

### **Genetic Algorithms (Evolutionary Computing)**

While Neural Networks mimic the **Brain** (Learning), Genetic Algorithms (GAs) mimic **Evolution** (Optimization).

Genetic Algorithm is NOT a neural network at all, It is an optimization algorithm that searches for best solution. Genetic Algorithm is used to **optimize** neural networks:

> ***Evolution: selection, crossover, mutation***
> 

The core philosophy is Darwin’s **"Survival of the Fittest."**

- Instead of trying to *calculate* the perfect solution mathematically, we generate a bunch of random solutions and let them "compete."
- The bad solutions die. The good solutions "breed" to create even better solutions.

**1. The Biological Metaphor**
biological terms to computer science terms:

| **Biological Term** | **Computer Science Term** | **Meaning** |
| --- | --- | --- |
| **Individual** | **Solution** | One possible answer to the problem (e.g., one specific route for a delivery truck). |
| **Chromosome** | **String/Array** | The data structure holding the solution (usually a string of 1s and 0s). |
| **Gene** | **Variable** | A specific part of the solution (e.g., the 3rd bit in the string). |
| **Population** | **Set of Solutions** | All the current guesses the computer is considering. |
| **Fitness** | **Score/Objective Function** | How "good" a solution is (e.g., "Distance traveled" – lower is better). |

**2. The Genetic Algorithm Cycle (Process Flow)**

The algorithm runs in a continuous loop called a **Generation**. 

**Step 1: Initialization**

- We create a random population of solutions (e.g., 100 random binary strings).

**Step 2: Fitness Evaluation**

- We test every solution.
- *Example:* If the problem is "Maximize $x^2$", and we have individuals $x=3$ and $x=5$, their fitness scores are 9 and 25.

**Step 3: Selection (Survival of the Fittest)**

- We pick the best individuals to be "parents" for the next generation.
- **Roulette Wheel Selection:** A popular method where better solutions have a larger "slice" of the wheel, so they are more likely to be picked, but weaker ones still have a small chance (to maintain diversity).

**Step 4: Crossover (Reproduction)**

- This is the most critical step. Two parents swap parts of their genetic code to create a child (offspring).
- *Single-Point Crossover:*
    - Parent A: `11111` | `00000`
    - Parent B: `00000` | `11111`
    - **Child:** `11111` `11111` (Inherits the first half of A and second half of B).
    - *Goal:* Hopefully, the child inherits the *good* traits from both parents.

**Step 5: Mutation**

- Occasionally (with low probability, e.g., 1%), we flip a random bit in the child.
    - Child: `1111111` $\rightarrow$ `1110111`
- *Why?* To introduce new traits that didn't exist in the parents. This prevents the algorithm from getting stuck in a local optimum (a good solution, but not the best one).

**Step 6: Termination**

- The loop repeats until we find a perfect solution OR we run out of time (e.g., 1000 generations).

 **Example for Genetic Algorithm - *Crack the Password "HELLO"***

Problem:  **Goal:** Find the 5-letter password "HELLO"

**Our tools:** Random letters A-Z

Let's see how Genetic Algorithm solves this!

**STEP 0: Setup**

Target Password: `HELLO`

Population Size: 6 individuals

Fitness Function: How many letters match the target position?

Example:

```sql
Guess: "HELPS" vs Target: "HELLO"
       H E L P S
       H E L L O
       ✓ ✓ ✓ ✗ ✗
Fitness = 3/5 = 60%
```

**GENERATION 1:** Random Start

Create Random Population:

```sql
Individual 1: "ABCDE"  → Compare with "HELLO"
              A B C D E
              H E L L O
              ✗ ✗ ✗ ✗ ✗  → Fitness = 0/5 = 0%

Individual 2: "HEFGH"  → Compare with "HELLO"
              H E F G H
              H E L L O
              ✓ ✓ ✗ ✗ ✗  → Fitness = 2/5 = 40% ✅

Individual 3: "XYZWQ"  → Fitness = 0/5 = 0%
              
Individual 4 : "HELPO"  → Compare with "HELLO"
              H E L P O
              H E L L O
              ✓ ✓ ✓ ✗ ✓  → Fitness = 4/5 = 80% ✅✅

Individual 5: "QRSTU"  → Fitness = 0/5 = 0%

Individual 6: "HAAAA"  → Compare with "HELLO"
              H A A A A
              H E L L O
              ✓ ✗ ✗ ✗ ✗  → Fitness = 1/5 = 20%
```

Fitness Summary:

```sql
Individual 1: "ABCDE"  → 0%
Individual 2: "HEFGH"  → 40%  ✅ Good
Individual 3: "XYZWQ"  → 0%
Individual 4: "HELPO"  → 80%  ✅✅ Best!
Individual 5: "QRSTU"  → 0%
Individual 6: "HAAAA"  → 20%
```

***Selection (Roulette Wheel)***

Build the Wheel: sum all the fitness score’s and the amount of contribution they do in the total sum, assign each of them that much % of slice in the wheel (circle) 

```sql
Total Fitness = 0 + 40 + 0 + 80 + 0 + 20 = 140

Individual 1: 0/140   = 0%   (no slice)
Individual 2: 40/140  = 29%  (medium slice)
Individual 3: 0/140   = 0%   (no slice)
Individual 4: 80/140  = 57%  (HUGE slice) 🎯
Individual 5: 0/140   = 0%   (no slice)
Individual 6: 20/140  = 14%  (small slice)
```

### **The Wheel:**

<!-- ![alt url](https://i.ibb.co/N6HKtzL5/image.png) -->

![img](https://private-user-images.githubusercontent.com/124666305/524453250-bdf8ed29-ed4b-4831-9531-93988349abd5.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjUzMDQ1NDUsIm5iZiI6MTc2NTMwNDI0NSwicGF0aCI6Ii8xMjQ2NjYzMDUvNTI0NDUzMjUwLWJkZjhlZDI5LWVkNGItNDgzMS05NTMxLTkzOTg4MzQ5YWJkNS5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUxMjA5JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MTIwOVQxODE3MjVaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT0yOGJiOTYxMTY3NTg4MWZkOTQ2NGVhOTZiYmVmNjhhOThhMGNiZjUyOTMyNTg5NTg5NWIyOGY0Y2ZlOTAwN2NkJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.XpjUGURSy0edEp0nsvwS3EN7-8kbHacI-LnxtgyUx_A)



**Spin Twice to Select 2 Parents:**

Spin 1:  Pointer lands on... Individual 4: "HELPO" ✅
Spin 2:  Pointer lands on... Individual 2: "HEFGH" ✅

Selected Parents:

- Parent 1: "HELPO" (fitness 80%)
- Parent 2: "HEFGH" (fitness 40%)

**STEP 2: Crossover (Make Babies)**

Single-Point Crossover:

Choose random crossover point: Let's say after position 3

```sql
Parent 1: HEL | PO
Parent 2: HEF | GH
          ↑
    crossover point
```

Swap Parts:

```sql
Child 1: HEL | GH  = "HELGH"
         ↑     ↑
      from P1  from P2

Child 2: HEF | PO  = "HEFPO"
         ↑     ↑
      from P2  from P1
```

Check Fitness:

```sql
Child 1: "HELGH" vs "HELLO"
         H E L G H
         H E L L O
         ✓ ✓ ✓ ✗ ✗  → Fitness = 3/5 = 60%

Child 2: "HEFPO" vs "HELLO"
         H E F P O
         H E L L O
         ✓ ✓ ✗ ✗ ✓  → Fitness = 3/5 = 60%
```

Not better than Parent 1, but that's okay! Evolution needs variety.

**STEP 3: Mutation**

**Mutation Rate:** 10% (simply means: Each gene (each position in the string) has a 10% chance of mutating)

- Roll a random number between 0–100
- If the roll ≤ 10 → **mutation happens**
- If the roll > 10 → **no mutation**

Child 1: "HELGH"

Roll dice for each position:

```sql
Position 1 (H): 🎲 Roll = 19%  → No mutation
Position 2 (E): 🎲 Roll = 15% → No mutation
Position 3 (L): 🎲 Roll = 13%  → No mutation
Position 4 (G): 🎲 Roll = 4% → MUTATE! Change to random letter
Position 5 (H): 🎲 Roll = 8%  → MUTATE! Change to random letter
```

After mutation: "HELGH" → "HELRO"

```sql
Check fitness: "HELRO" vs "HELLO"
               H E L R O
               H E L L O
               ✓ ✓ ✓ ✗ ✓  → Fitness = 4/5 = 80% 🎉 Better!
```

Child 2: "HEFPO"

```sql
All positions: No mutation (got lucky, less then 10% rolls)
Stays: "HEFPO"
```

**Create Full Generation 2**

We selected 2 parents and made 2 children. Repeat this process 2 more times to get 6 individuals:

Note: <i>1 Generation = One complete cycle of the entire population</i>

---

**GENERATION 2: Results**

```sql
Individual 1: "HELRO"  → 80%  ✅✅ (from crossover + mutation)
Individual 2: "HEFPO"  → 60%  ✅
Individual 3: "HELLO"  → 100% 🎉🎉🎉 (got lucky in crossover!)
Individual 4: "HELGO"  → 60%
Individual 5: "HELAO"  → 60%
Individual 6: "HELPO"  → 80%  ✅✅ (kept from Gen 1)
```

Found It! "HELLO"

**Individual 3 achieved 100% fitness!**

**Algorithm stops.** Password cracked! 🔓

---

## Unit 2

### **Search Methods**

In Classical AI, we treat intelligence as a **Search Problem**.

- **The Goal:** You are at a "Start State" and want to reach a "Goal State."
- **The Challenge:** You don't know the path. You have to explore the map (State Space) to find it.
- **Real-world examples:** A GPS finding a route, a chess bot finding a winning move, or a robot solving a maze.

Key Terms: 

1. **State:** A snapshot of the problem at any moment.
    
    Example: arrangement of tiles in 8-Puzzle.
    
2. **State Space:** All possible states reachable from the start.
3. **Initial State:** Where the search begins.
4. **Goal State:** The desired solution condition.
5. **Operators (Actions):** Operations that move from one state to another.
6. **Path:** Sequence of states leading from start → goal.
7. **Cost:** Cost of moving along a path (e.g., distance, time).

The first topic is **Simple Search Methods** (also called **Uninformed** or **Blind Search**). They are called "Blind" because the AI has no clue how close the goal is—it just blindly checks every path until it hits the target.

### **BLIND SEARCH**

Here are the three methods listed: BFS, DFS, IDS (Iterative Deepening Search)  ****

### **1. Breadth-First Search (BFS)**

**"The Cautious Explorer"**

- **Strategy:** Explore level-by-level. It checks all immediate neighbors (Depth 1) before moving to Depth 2.
- **Data Structure:** Uses a **Queue (FIFO - First In, First Out)**. "First node seen is the first node processed."
- **Pros:** It is **Complete** (will always find a solution if one exists) and **Optimal** (finds the shortest path if all step costs are equal).
- **Cons:** It requires massive memory because it has to store every single node at the current level before moving deeper.

> Visual: Imagine dropping a stone in a pond. The ripples expand equally in all directions. That is BFS.
> 

**Time Complexity:** $O(n^m)$

Where:

- n = branching factor
- m = depth of solution

**Space Complexity: $O(n^m)$**

Stores all nodes 

![](https://i.ibb.co/pv496Htd/Screenshot-2025-11-27-at-3-08-57-PM.png)

---

### **2. Depth-First Search (DFS)**

**"The Bold Adventurer"**

- **Strategy:** Pick one path and go as deep as possible until you hit a dead end. Only then do you backtrack and try the next path.
- **Data Structure:** Uses a **Stack (LIFO - Last In, First Out)**. "Last node seen is the first one processed."
- **Pros:** Very memory efficient. It only needs to store the current path.
- **Cons:** It is **Not Optimal** (might find a long, winding path first) and can get stuck in infinite loops if the search space is infinite.

> Visual: Imagine solving a maze by keeping your hand on the left wall and walking until you hit a dead end, then turning back. That is DFS.
> 

**Time Complexity:** $O(n^m)$

Where:

- n = branching factor
- m = depth of solution

**Space Complexity: $O(n*m)$**

DFS needs only the current path + siblings.

---

### **3. Iterative Deepening Search (IDS)**

**"The Best of Both Worlds"**

This method fixes the problems of BFS (too much memory) and DFS (getting lost in infinite depths).

- **Strategy:** It runs DFS, but with a **Limit**.
    1. Run DFS with depth limit = 1. (Check immediate neighbors).
    2. If goal not found, discard everything.
    3. Run DFS with depth limit = 2 (i.e from start node `A` do DFS to each neighbours of A but only till depth limit 2)
    4. Repeat, increasing the limit by 1 each time.
- **Why do this?**
    - It looks like BFS (explores level by level), so it finds the shortest path.
    - It uses the memory of DFS (very low), because at any moment it is only running a stack-based search.
- **Exam Note:** It feels wasteful to restart from scratch every time, but because the bottom level of a tree contains the vast majority of nodes, reprocessing the top levels is actually very cheap computationally.

First, search only depth 0
Then, search depth 0 and 1
Then, search depth 0, 1, and 2
Keep increasing until you find the goal

**CONCRETE EXAMPLE for IDS : Finding a City H starting from A**

```sql
The Map:
                    A (Start)
                   / \
                  /   \
                 B     C
                / \     \
               /   \     \
              D     E     F
             /       \
            /         \
           G           H (Goal!)

Goal: Find city H starting from city A
```

**IDS Step-by-Step**

*ITERATION 1*: `Depth Limit = 0`

- Rule: Only explore depth 0 (just the starting node)
Search Tree:
    `A` ← Check this (depth 0)
- Process: Check `A` → Is it `H`? No
- Depth limit reached (0), `stop`
- Result: Goal not found
Nodes visited: 1 (just `A`)

*ITERATION 2*: `Depth Limit = 1`

- Rule: Explore depth 0 and depth 1
Search Tree:

```sql
        A (depth 0)
       / \
     B   C (depth 1)
```

- Process:
Check `A` → Is it `H`? No
Expand A, go to children (depth 1):
    - Check `B` → Is it `H`? No
    - Check `C` → Is it `H`? No
    - Depth limit reached (1), `stop`
    
    Result: Goal not found 
    Nodes visited: 3 (`A, B, C`)
    

*ITERATION 3*: `Depth Limit = 2`

- Rule: Explore depth `0, 1, and 2`
Search Tree:

```sql
        A (depth 0)
       / \
      B   C (depth 1)
     / \   \
    D   E   F (depth 2)
```

- Check `A` → Is it `H`? No
Expand `A`:
    - Check `B` → Is it `H`? No
        - Expand `B`:
            
            Check `D` → Is it `H`? No
            Check `E` → Is it `H` ?No
            
        - Check `C` → Is it `H`? No
        Expand `C`:
        Check `F` → Is it `H`? No
        `Depth limit reached (2)`, stop
    
    Result: Goal not found
    Nodes visited: 6 (`A, B, D, E, C, F`)
    

*ITERATION 4*: `Depth Limit = 3`
Rule: Explore depth 0, 1, 2, and 3

```sql
Search Tree:
        A (depth 0)
       / \
      B   C (depth 1)
     / \   \
    D   E   F (depth 2)
   /     \
  G       H (depth 3)
```

Process:
Check `A` → Is it `H`? No
Expand A:

- Check `B` → Is it `H`? No
Expand `B`:
    - Check `D` → Is it `H`? No
        
        Expand `D`:
        
        - Check `G` → Is it `H`? No
    - Check `E` → Is it `H`? No
    Expand `E`:
        - Check `H` → Is it `H`? `YES`!

Result: Goal FOUND! 🎉
Path: `A → B → E → H`
Nodes visited: 8 (`A, B, D, G, E, H, C, F`)

**Comparision Table BFS vs DFS vs IDS**

| **Feature** | **Breadth-First (BFS)** | **Depth-First (DFS)** | **Iterative Deepening (IDS)** |
| --- | --- | --- | --- |
| **Strategy** | Level by Level | Deepest Node First | DFS with increasing limits |
| **Data Structure** | **Queue** (FIFO) | **Stack** (LIFO) | Stack |
| **Memory Use** | **High** (Exponential) | **Low** (Linear) | **Low** (Linear) |
| **Optimal?** | **Yes** (Finds shortest path) | **No** (Might find long path) | **Yes** |
| **Complete?** | Yes | No (can get stuck in loops) | Yes |

---

### Informed search (Not Blind)

1. Hill Climb Search
2. Best First Search
    1. A* - Admissible Search

### Heuristic Search (Informed Search)

We just covered "Blind Search" (BFS/DFS), where the AI stumbles around until it finds the goal.
Heuristic Search is "Informed." The AI has a map or a compass. It doesn't know the exact path, but it has a Heuristic Function ($h(n)$) that estimates: "How close am I to the goal?"

- **$h(n)$:** Estimated cost from current node $n$ to the Goal.
- *Example:* If you are driving to a city, the "Blind" search checks every road. The "Heuristic" search looks at a sign saying "City: 50km straight ahead" and chooses the road pointing that way.

Here are the specific methods from Heuristic Search :

### **1. Hill-Climbing Search**

**"The Mountaineer in the Fog"**

Basic functionality: just take the most optimal next step (not thinking too far)

This is the simplest heuristic method. It is often used for optimization problems (like finding the maximum profit).

- **Strategy:** You are standing on a landscape. You look at your immediate neighbors. You always take a step **uphill** (towards a better state). You stop when no neighbor is higher than where you are.
- **Key Characteristic:** It is a "Local Search." It doesn't care about the past or the future, only the immediate next step. It does not maintain a search tree (saves memory).

**The 3 Major Problems (Important):**
Hill Climbing is fast, but it often fails. You must know these three failure states:

1. **Local Maximum:** You reach a peak that is higher than everything around you, but it's not the highest peak (Global Maximum). You get stuck because every step is "down."
    - Example: Imagine you're blindfolded, standing on a small hill in a valley. There's a huge mountain nearby, but you can't see it. Here every next step in all directions are Lower then current place So we end up thinking that "I'm at the top!".
    - But you're NOT at the HIGHEST point!
    - You're STUCK!
    
    ```java
                         HUGE MOUNTAIN - Global Maxima
       (You're here!)      (Goal!)          
        Local maxima.        /\
                            /  \
           /\              /    \
          /  \            /      \
    _____/    \__________/        \____________
    
    example:-
    Height:   3  4  5  4  3  2  1  2  3  4  7  10  9  8  7
    Position: 0  1  2  3  4  5  6  7  8  9 10  11 12 13 14
                    ↑                           ↑
               Local Max (5)                 Global Max (10)
               You're here!                  Real goal!
               
               
     // Since we are on local maxima and our previous is 4, current is 5 and next is 4 which is smaller then current so we end up thinking this is the best place (highest) but in reallity we are stuck 
     // global maxima is the best solution
    ```
    
2. **Plateau:** A ***flat area*** where all neighbors have the same value. The algorithm doesn't know which way to go and wanders aimlessly.

```java
example: 

              Goal (far away)
               *
              /|\
             / | \
____________/  |  \___________________
FLAT FLAT FLAT FLAT FLAT FLAT FLAT
👤
You're 
here

// You feel around → Everything is the SAME height North = 5, South = 5, East = 5, West = 5 Which way to go? 🤷
// You wander randomly
// making NO PROGRESS!
```

1. **Ridge:** A ***narrow peak*** where any single step (North, South, East, West) goes down, even though the ridge itself goes up ***diagonally***.

```java
Goal (higher, further along ridge)
          *
         /
        /
       / ← Ridge goes diagonally UP
      /
     
     *  ← You're here
    /|\
   ↙ | ↘ All these directions go DOWN!
  ↙  |  ↘
 ↙   |   ↘
 
 
**Numeric Example :-**

     X →
Y    0   1   2   3   4
↓  ┌───┬───┬───┬───┬───┐
0  │ 3 │ 2 │ 1 │ 1 │ 1 │
   ├───┼───┼───┼───┼───┤
1  │ 2 │ 4 │ 3 │ 2 │ 1 │
   ├───┼───┼───┼───┼───┤
2  │ 1 │ 3 │ ***5*** │ 4 │ 2 │  ← Ridge runs diagonally!
   ├───┼───┼───┼───┼───┤
3  │ 1 │ 2 │ 4 │ 6 │ 3 │  ← 5 → 6 = uphill along diagonal
   ├───┼───┼───┼───┼───┤
4  │ 1 │ 1 │ 2 │ 3 │ 7 │ ← Goal: 7 (bottom-right)
   └───┴───┴───┴───┴───┘
   
   
You're at position (2,2) = 5
Check neighbors:

North (1,2): 3  ← DOWN! ❌
South (3,2): 4  ← DOWN! ❌
East (2,3):  4  ← DOWN! ❌
West (2,1):  3  ← DOWN! ❌
All single steps go DOWN!

But if you could move diagonally (Southeast): Diagonal (3,3): 6 ← UP! ✅

***But Hill-Climbing only moves in 4 directions (N,S,E,W)!
Can't move diagonally!***
```

---

### Best-First Search (Greedy Search)

Best-First Search is an **informed search algorithm** that uses a heuristic function to guide its exploration toward the most promising nodes. It's called "best-first" because it always expands the node that appears best according to the heuristic.

This uses a proper search tree (like BFS), but with a priority system.

- **Strategy:** At every step, look at **all** the nodes you have discovered (the "Open List"). Pick the one with the **lowest $h(n)$** (the one that *looks* closest to the goal).
- **Difference from Hill Climbing:** Hill Climbing only looks at immediate neighbors and forgets the rest. Best-First keeps a list of all unexplored options. If the current path gets bad, it can jump back to an earlier promising node.
- **Drawback:** It is "Greedy." It might run towards a city that looks close straight-line distance, but is actually blocked by a river, forcing it to take a huge detour. It is **not guaranteed to be optimal**.

**Key Components**

1. **Heuristic Function $h(n)$**

- Estimates the cost/distance from node $n$ to the goal node
- Domain-specific knowledge encoded as a function
- Example: In navigation, $h(n$) = straight-line distance to destination
- in this case : Lower $h(n)$ values = closer to goal

2. **Priority Queue (Open List)**

- Stores all discovered but *unexplored nodes*
- Orders nodes by their heuristic value since this a priority queue (min or max heap)
- Node with lowest $h(n)$ gets explored first (means smallest route to reach goal)

3. **Closed List**

- Tracks already explored nodes are stored in this
- Prevents revisiting the same node

**Algorithm Steps**

1. Start with initial node in priority queue
2. While priority queue is not empty:
    1. Remove node with best (lowest) heuristic value
    2. If it's the goal → SUCCESS, return path
    3. Mark node as explored (add to closed list)
    4. For each neighbor of current node:
        1. If not explored and not in queue → add to queue
        2. Calculate $h(n)$ for each neighbor
3. If queue becomes empty → FAILURE (no solution)

**Example for Best-First Search**

Goal: Find path from A to Z

```java
				A (start)
       / \
      B   D
      |   |
      C   E
       \ /
        Z (goal)
```

Heuristic Values (estimated distance to Z):

```java
h(A) = 6
h(B) = 5
h(C) = 2
h(D) = 4
h(E) = 3
h(Z) = 0
```

Step-by-Step Execution

Step 1: Initialize

- Queue: [A(6)]
- Explored: []
- Action: Start at A

Step 2: Expand A

- Current Node: A
- Neighbors: B(5), D(4)
- Queue: [D(4), B(5)] ← D has lower h-value
- Explored: [A]

Step 3: Expand D

- Current Node: D ← Best node (lowest h-value)
- Neighbors: E(3)
- Queue: [E(3), B(5)]
- Explored: [A, D]

Step 4: Expand E

- Current Node: E ← Best node
- Neighbors: Z(0)
- Queue: [Z(0), B(5)]
- Explored: [A, D, E]

Step 5: Expand Z

- Current Node: Z ← Best node
- Goal Found! ✓
- Path: `A → D → E → Z`

**Characteristics**

Advantages: 

- **Informed:** Uses domain knowledge via heuristics
- **Efficient:** Explores promising paths first
- **Complete:** Finds solution if one exists (in finite spaces)
- **Flexible:** Works with various heuristic functions

Disadvantages:

- **Not optimal:** May not find shortest/cheapest path
- **Memory intensive:** Stores all discovered nodes
- **Heuristic dependent:** Bad heuristic = poor performance
- **Can be misled:** Might explore wrong path if heuristic is inaccurate

**Time Complexity:** $O(b^m)$ - worst case

**Space Complexity:** $O(b^m)$

*where b = branching factor, m = maximum depth*
****

**Variants**

- Greedy Best-First Search
    - Uses only $h(n)$ to evaluate nodes
    - Fast but not optimal
    - Can get stuck in loops
- *A Search**
    - Uses $f(n) = g(n) + h(n)$
    - $g(n)$ = actual cost from start to n
    - $h(n)$ = estimated cost from n to goal
    - **Optimal** if heuristic is admissible
    - Best-First Search + path cost consideration

---

### Best-First Search vs Hill Climbing: A Comparision

In **Hill Climbing Search:** 

- Starts at a random point
- Looks at only the immediate neighbors
- Moves to the neighbor with the best value
- Never looks back - can't undo moves
- Stops when no neighbor is better (local maximum)

In **Best First Search:** 

- Keeps track of all promising paths it has seen
- Evaluates nodes using a heuristic function (estimated distance to goal)
- Always expands the most promising unexplored node from **anywhere** in the search space
- Can "backtrack" by exploring nodes from earlier in the search
- Uses a priority queue to organize nodes by their heuristic value

---

### 3. Admissible Evaluation Functions

This topic usually relates to the *A (A-Star) Algorithm**, which is the gold standard of search.

To fix the problems of Greedy search, we use a smarter evaluation function:

$f(n) = g(n) + h(n)$

- **$g(n)$:** The actual cost you have already paid to get here (History).
- **$h(n)$:** The estimated cost to get to the goal (Future).
- **$f(n)$:** The estimated *total* cost of the path.

**What is an "Admissible" Heuristic?**

For the algorithm to guarantee finding the shortest path (Optimal), the heuristic $h(n)$ must be Admissible.

- **Definition:** A heuristic is admissible if it **never overestimates** the cost to reach the goal. It must be optimistic.
- *Example:* If the true distance to the goal is 10km, your heuristic can say 5km, 8km, or 10km. But if it says 11km, it is **not admissible**, and the algorithm might miss the best path.

---

### Optimization

Now we will optimize the searching algorithm that we used such as `Hill Climb searching` which was a ***deterministic algorithm***  ******(Same input → always same output, no randomness) with new the ***probabilistic  Algorithm*** (Same input → *may* give different outputs, has randomness) such as `Simulated Annealing` 

### Simulated Annealing (Stochastic Annealing)

**Simulated Annealing** is a probabilistic optimization algorithm inspired by the metallurgical process of annealing (heating and slowly cooling metal to remove defects).

**Key Idea:** Unlike Hill Climbing which gets stuck at local maxima, Simulated Annealing occasionally accepts **worse moves** to escape local optima and find the global optimum.

**The Annealing Metaphor**

**Physical Process:**

1. Heat metal to high temperature (atoms move freely)
2. Slowly cool it down (atoms settle into low-energy state)
3. Result: Strong, stable structure (global minimum energy)

**Algorithm Analogy:**

1. Start with high "temperature" (accept bad moves frequently)
2. Gradually decrease temperature (become more selective)
3. Result: Converge to optimal or near-optimal solution

**Basic Concept**

- **At high temperature:** Accepts both good AND bad moves (explores widely)
- **At low temperature:** Accepts mostly good moves (exploits best area)
- **Probability of accepting worse moves decreases over time**

**Algorithm Steps**

```java
1. Start with random initial state
2. Set initial temperature T (high value)
3. Repeat until T reaches minimum:
a. Pick a random neighbor
b. Calculate ΔE = (neighbor_value - current_value)
    
    c. If ΔE > 0 (better solution):
    → Accept the move
    
    d. If ΔE < 0 (worse solution):
    → Accept with probability P = e^(ΔE/T)
    → Generate random number r (0 to 1)
    → If r < P: accept the move
    → Otherwise: stay at current state
    
    e. Decrease temperature: T = T × cooling_rate
    
4. Return best solution found
```

**Key Components**

1. **Temperature (T)**

- Controls probability of accepting bad moves
- **High T** → Accept bad moves easily (exploration)
- **Low T** → Rarely accept bad moves (exploitation)

2. **Cooling Schedule**

- How temperature decreases over time
- Common: `T = T × α` (where α = 0.95 to 0.99)
- **Too fast:** May miss global optimum
- **Too slow:** Wastes computation time

3. **Acceptance Probability**

- Formula: **`P = e^(ΔE/T)`**
- ΔE = change in objective function
- At high T: P is higher (accept bad moves)
- At low T: P is lower (reject bad moves)

**Simple Example for simulated anneling: Traveling Salesman Problem (TSP)**

Problem: Visit 4 cities and return to start with minimum distance

```java
Cities: A, B, C, D

Initial route: A → B → C → D → A (distance = 100)
Execution: 
Temperature = 100 (High)

**Iteration 1:**
Current: A→B→C→D→A (100)
Try: A→C→B→D→A (110) ← Worse by 10
ΔE = 100 - 110 = -10
P = e^(-10/100) = e^(-0.1) ≈ 0.90 (90% chance)
Random: 0.75 < 0.90 → Accept worse move!

Temperature = 50 (Medium)

**Iteration 2:**
Current: A→C→B→D→A (110)
Try: A→D→B→C→A (120) ← Worse by 10
ΔE = 110 - 120 = -10
P = e^(-10/50) = e^(-0.2) ≈ 0.82 (82% chance)
Random: 0.88 > 0.82 → Reject

Temperature = 10 (Low)

**Iteration 3:**
Current: A→C→B→D→A (110)
Try: A→B→D→C→A (95) ← Better by 15
ΔE = 110 - 95 = 15 (positive)
Always accept better moves!

Temperature = 1 (Very Low)

**Iteration 4:**

Current: A→B→D→C→A (95)
Try: A→D→C→B→A (105) ← Worse by 10
ΔE = 95 - 105 = -10
P = e^(-10/1) = e^(-10) ≈ 0.00005 (0.005% chance)
Random: 0.5 > 0.00005 → Reject (almost no bad moves accepted)

**Final Solution: A→B→D→C→A (distance = 95)**
```

**Comparison: Hill Climbing vs Simulated Annealing**

| Feature | Hill Climbing | Simulated Annealing |
| --- | --- | --- |
| Bad moves | Never accepted | Sometimes accepted |
| Local optima | Gets stuck | Can escape |
| Exploration | Limited | Extensive (early on) |
| Deterministic? | Yes | No (probabilistic) |
| Global optimum | Not guaranteed | Better chance |
| Speed | Fast | Slower |

---

### Genetic Algorithms (GA)

Although already covered in unit 1 lets understand this from unit 2 perspective (search optimization)

**The Problem: Why do we need GA here?**

In Hill Climb Algo It is like **one single hiker** climbing a mountain in the fog. If they reach a small peak (Local Maximum), they stop, thinking they are at the top, even if Mount Everest is a mile away.

**Genetic Algorithms** solve this by being a **Global Search** method.

- Instead of one hiker, imagine dropping **100 paratroopers** (the Population) all over the map at once.
- They communicate, swap coordinates, and jump around.
- Even if 50 get stuck on a small peak, the other 50 might land near the real summit. This is how it solved local maxima problem of hill climb.

Genetic Algorithms provide an **alternative search technique** that uses **population-based random search + heuristics**.

**GA is a global search method.**

It searches **many points at once** instead of following one path.

Key idea:

> Instead of searching node-by-node (like BFS/DFS/A*), GA searches in parallel using a population of candidate solutions.
> 

This makes GA useful for: Optimization problems, NP-hard problems, Problems without clear structure, Problems with many local minima.

Genetic Algorithm searches by **evolving solutions** using operators: **Selection, Crossover, Mutation**

1. **Fitness Function (The Evaluation):** This is your "Heuristic." It assigns a score to every solution.
2. **Selection:** Pick good solutions → explore promising regions.
3. **Crossover:** Combine solutions → discover new regions.
4. **Mutation:** Add randomness → escape local minima.

*This is exploration + exploitation, like advanced versions of hill climbing.*

**Important Characteristics for Genetic Algorithm**

1. GA is **NOT deterministic:** Every run can produce different results.
2. **GA is NOT complete:** Does not guarantee finding a solution.
3. **GA is NOT optimal:** May not give the best possible solution — only a “good enough” solution.
4. **GA is robust:** Works even with noisy or incomplete data.
5. **GA is parallel:** Population evolves simultaneously → more exploration.

**Comparision: Hill Climb vs Genetic Algorithm**

| **Feature** | **Hill Climbing** | **Genetic Algorithm** |
| --- | --- | --- |
| **Search Agents** | Single Point (1 solution) | Population (Many solutions) |
| **Strategy** | Greedy (Always go up) | Stochastic (Probabilistic) |
| **Memory** | None (Forgets past steps) | Implicit (Good traits survive in population) |
| **Local Maxima** | **Gets Stuck** | **Can Escape** (via Mutation/Crossover) |
| **Speed** | Very Fast | Slower (Computationally heavy) |

---

## Unit 3

### Knowledge Representation

Before a computer can solve a problem, it needs to "know" the facts. **Knowledge Representation (KR)** is the art of translating real-world information into a code format (symbols) that an AI can understand and use to reason.

However, this is not easy. There are **"Issues"** which are the trade-offs and difficulties we face when designing these systems.

Here are the **4 Key Issues:**

**1. Expressive Adequacy (Can we say it all?)**

- **The Issue:** Can the system represent *every* distinction needed?
- *Example:* If your system only understands "Integers," it cannot represent "Temperature is 98.6". If it only understands "Facts," it cannot represent "Beliefs" (e.g., "John *thinks* it is raining").
- **Goal:** The language must be rich enough to capture vague, incomplete, or complex ideas.

> *It's the issue of the KNOWLEDGE REPRESENTATION SYSTEM we choose/design!*
> 

**2. Reasoning Efficiency (Is it fast?)**

- **The Issue:** The more detailed your knowledge, the slower the computer becomes.
- **The Trade-off:** There is a direct conflict between **Expressiveness** and **Efficiency**.
    - **Expressiveness** = how detailed, rich, and complex the representation is.
    - *Simple Logic:* fast to process, but dumb. (eg. “A is true”, “B is false”)
    - *Complex Logic:* smart, but takes forever to calculate. (eg. “If it rains, the ground becomes wet”)
- **Goal:** To structure data so the AI can access the *right* facts quickly without checking the entire database.

**3. Acquisition Efficiency (Is it easy to teach?)**

- **The Issue:** How hard is it to put new info into the system?
- *Example:* In the 1980s, "Expert Systems" failed because humans had to manually type in thousands of "If-Then" rules. It was too hard to maintain. (eg. IF fever AND body-ache THEN flu
)
- But Modern Approaches have:
    - **Machine Learning (ML):** AI **learns rules automatically from data**. (eg. spam mail filters, recommendation systems)
- **Goal:** The system should allow for easy updates or (ideally) learn automatically from data.

**4. Granularity (How much detail?)**

Granularity means **the level of detail** at which knowledge is represented. AI also has to choose the **right level of detail** when storing or using knowledge.

- **The Issue:** At what level of detail should we store knowledge?
- *High Level:* "John ate dinner." (Good for planning).
- *Low Level:* "John moved his hand to the fork, grasped it, lifted it..." (Good for robotics).
- **Goal:** The system must pick the right level of detail for the specific task, or risk getting overwhelmed by useless data.

If the system stores **too much detail**, it becomes: Slow, Hard to reason, Cluttered with useless facts.

If it stores **too little detail**, it becomes: Unable to solve tasks requiring precision, Blind to important differences, Too vague for correct decisions

So the AI must find the **correct balance**.

---

### Structured Representation

Now that we know the *problems*, let's look at the *solutions*. These are the specific data structures used to store knowledge.

The syllabus lists four specific types. We will cover **Semantic Networks** and **Frames** first, as they are the most common.

### **1. Semantic Networks**

This is a graph-based representation.

- **Structure:**
    - **Nodes:** Objects or concepts (e.g., "Bird", "Wings", "Canary").
    - **Arcs (Links):** Relationships (e.g., "Has-Part", "Is-A").
- **Key Concept: Inheritance.**
    - If "Bird" has "Wings", and "Canary" *is-a* "Bird", then the computer automatically knows "Canary" has "Wings." It doesn't need to be told explicitly.

```java
         Animal
           |
        is-a
           |
         Bird
           |
        is-a
           |
        Sparrow
```

### **2. Frames**

Think of a **Frame** as an "Object" in Object-Oriented Programming (like a Java Class). It bundles specific details about an object.

- **Structure:**
    - **Frame Name:** e.g., "Hotel Room".
    - **Slots:** Properties (e.g., "Bed", "Wifi", "Price").
    - **Fillers:** Values for those properties (e.g., "King Size", "Yes", "$100").
- **Why use it?** It groups related knowledge together. When you trigger the "Hotel Room" frame, the AI immediately expects a Bed and Wifi to exist.

```yaml
Frame: Dog
   Slots: 
      Color: Brown
      Sound: Bark
      Legs: 4
      Type: Mammal
```

### **3. Scripts**

If **Frames** represent *Objects* (like a "Car" or "Hotel"), **Scripts** represent sequence of events or *scenarios*.

Developed by researchers Schank and Abelson, a Script tells the AI "what normally happens" in a specific situation. This allows the AI to fill in missing details.

- **The Classic Example: The "Restaurant" Script**
If I tell an AI: *"John went to a restaurant. He left a tip."*
The AI knows, without being told, that John likely **sat down**, **looked at a menu**, **ordered food**, and **ate**. It infers this from the script.

**Components of a Script (Exam Checklist):**

1. **Entry Conditions:** What must be true to start? (User is hungry, has money).
2. **Roles:** Who is involved? (Customer, Waiter, Chef).
3. **Props:** What objects are used? (Table, Menu, Food, Money).
4. **Scenes:** The sequence of events (Entering $\rightarrow$ Ordering $\rightarrow$ Eating $\rightarrow$ Exiting).
5. **Results:** The final state (User is full, has less money).

### **4. Conceptual Graphs**

A Conceptual Graph (CG) is a more formal, rigorous version of a Semantic Network. It connects logic with a graphical structure.

**Structure:** It has two types of nodes.

- **Concept Nodes (Boxes):** Represents entities, objects, events (e.g., [Cat], [Mat]).
- **Relation Nodes (Circles/Ovals):** Represents the relationship (e.g., (On), (Color),(agent), (object), (recipient), (part-of)).
    - Example: "The cat is on the mat." $[\text{Cat}] \rightarrow (\text{On}) \rightarrow [\text{Mat}]$
    - **Why use it?** Unlike Semantic Networks, which can be vague, Conceptual Graphs map directly to **Predicate Logic**, making them precise enough for mathematical reasoning.

```yaml
Conceptual Graph:
[John] —(agent)→ [Give]
[Give] —(object)→ [Book]
[Give] —(recipient)→ [Mary]

This represents:

John is the giver
Book is the object
Mary is the receiver
```

---

### Formal Logic & Inference

This is the "Math" side of Knowledge Representation. Instead of drawing graphs, we write formulas.

### **1. Propositional Logic (Boolean Logic)**

The simplest form. It deals with facts that are either True or False.

- **Symbols:** $P, Q, R$
- **Connectives:** $\wedge$ (AND), $\vee$ (OR), $\neg$ (NOT), $\rightarrow$ (Implication).
- *Example:* If $P$ (It rains) $\rightarrow$ $Q$ (Ground is wet).

### **2. First-Order Logic (Predicate Logic)**

Propositional logic is too weak because it can't handle variables. It can say "Socrates is mortal," but it can't say "All men are mortal."

Predicate Logic fixes this by adding:

- **Predicates:** $Man(x)$ means "$x$ is a man."
- **Quantifiers:**
    - $\forall$ (**For All**): $\forall x (Man(x) \rightarrow Mortal(x))$ ("For all $x$, if $x$ is a man, then $x$ is mortal.")
    - $\exists$ (**There Exists**): $\exists x (Bird(x) \wedge CannotFly(x))$ ("There exists some bird that cannot fly.")

### **3. Inference (How the AI thinks)**

Inference is the process of deriving new facts from old ones.

- **Modus Ponens:** The golden rule of AI logic.
    - Rule: If $P \rightarrow Q$ is true, and $P$ is true..
    - Inference: ...then $Q$ **must** be true.

---

### Knowledge-Based Systems (KBS)

Knowledge-Based Systems (often called Expert Systems) and **Blackboard Architectures.**

**1. Knowledge-Based System Structure**

A **Knowledge-Based System** is an AI system that uses **stored knowledge** and a **reasoning mechanism** to solve problems like a human expert.. It has two main parts separating "What it knows" from "How it thinks":

1. **Knowledge Base (KB):** The library of facts and rules (e.g., "If fever > 102, suspect infection").
    
    It comprises of:
    
    - **Facts**
    - **Rules** (IF–THEN)
    - **Relationships**
2. **Inference Engine:** The processor that applies the rules to the data to solve problems.
    1. *Note:* This separation is crucial. You can update the medical knowledge (KB) without rewriting the code (Inference Engine).

Disadvantages:

- Hard to acquire knowledge (knowledge acquisition bottleneck)
- Rule explosion (thousands of rules)
- Cannot learn automatically (unless extended)
- Struggle with uncertain or incomplete data

**2. Blackboard Architecture**

This is a specific design for complex problems (like speech recognition) where one "Expert" isn't enough.

- **The Metaphor:** Imagine a group of experts standing around a **Blackboard**.
    - **The Blackboard:** A shared memory space containing the current problem.
    - **Knowledge Sources (KS):** Independent experts (agents). One is good at grammar, one at acoustics, one at vocabulary.
- **The Process:**
    1. The "Acoustic Expert" writes phonetic sounds on the board.
    2. The "Vocabulary Expert" sees the sounds and writes possible words.
    3. The "Grammar Expert" sees the words and corrects the sentence structure.
- **Key Benefit:** The experts don't talk to each other directly; they only look at the global "Blackboard." This allows many different AIs to collaborate.

---

## Unit 4:

### Reasoning Under Uncertainty and Learning

Earlier in unit 3, we assumed the world is perfect: "If A, then B."

But In the real world, data is noisy, sensors fail, and rules are only "usually" true. Unit 4 teaches AI how to guess when it isn't 100% sure.
The first major method is **Bayesian Reasoning**.

### **1. Bayesian Reasoning (Probability Theory)**

This is the mathematical standard for handling uncertainty. It is based on **Bayes' Theorem**, which tells us how to update our beliefs when we see new evidence.

**The Formula**

> $P(H|E) = \frac{P(E|H) \cdot P(H)}{P(E)}$
> 

Where:

- **$P(H|E)$ (Posterior):** The probability that the Hypothesis ($H$) is true *given* the Evidence ($E$). (This is what we want to find).
- **$P(H)$ (Prior):** The probability of the Hypothesis being true *before* seeing any evidence. (Our initial belief).
- **$P(E|H)$ (Likelihood):** If the Hypothesis were true, how likely is it that we would see this Evidence?
- **$P(E)$ (Marginal):** The total probability of seeing the Evidence under all circumstances.

**Example: The Medical Diagnosis**

Imagine a patient has a **Cough ($E$)**. We want to know if they have **Flu ($H$)**.

- **Prior ($P(H)$):** 10% of people currently have the Flu.
- **Likelihood ($P(E|H)$):** 80% of people with Flu have a Cough.
- **Marginal ($P(E)$):** 20% of everyone has a Cough (from flu, allergies, smoking, etc.).
- $P(\text{Flu}|\text{Cough}) = \frac{0.80 \times 0.10}{0.20} = \frac{0.08}{0.20} = 0.4$

**Result:** Even though the patient has a cough, there is only a **40% chance** they have the Flu. This prevents the AI from jumping to conclusions.

### **2. Certainty Factors (CF)**

While Bayes is mathematically perfect, it is hard to get all those exact numbers ($0.80, 0.10$, etc.) from doctors.

Certainty Factors were invented for Expert Systems (like MYCIN) to make this easier.

- **Definition:** A number between **-1 and +1** that represents an expert's confidence.
    - **+1.0:** Definitely True.
    - **-1.0:** Definitely False.
    - **0:** No clue (Ignorance).

**Key Difference:** Unlike probability, CFs don't have to add up to 1. An expert can say: "I am 0.7 sure it's Flu" without caring about the other 0.3.

### **3. Dempster-Shafer Theory (Theory of Evidence)**

This is a more advanced theory that fixes a flaw in Bayesian Logic: **Distinguishing "Uncertainty" from "Ignorance."**

**The Flaw in Bayesian probability:** 

Both scenarios give the SAME answer (0.5), but they mean DIFFERENT things!

```yaml
Prob of Head        Probability of bomb inside
Coin Toss:           Mystery Box:
P = 0.5              P = 0.5
   ↓                    ↓
"I KNOW it's         "I have NO IDEA,
50-50"              so I guess 50-50"
   ↓                    ↓
KNOWLEDGE            IGNORANCE

Bayesian probability treats these the SAME! That's wrong
```

- Problem: It treats "Randomness" and "Total Ignorance" the same way.

**The Dempster-Shafer Solution:** 

Use an INTERVAL instead of a single number!

It uses an Interval $[Belief, Plausibility]$ instead of a single number.

```yaml
Instead of:  P = 0.5

Use:  [Belief, Plausibility]
       ↑            ↑
    Lower bound  Upper bound
```

- **Belief ($Bel$):** How much evidence I have *supporting* the claim.
- **Plausibility ($Pl$):** How much evidence I have that *does not contradict* the claim.
- **Ignorance:** Represented by the gap between Belief and Plausibility.

**Key Concepts**

**1. Belief (Bel) - Lower Bound**

"How much evidence DO I have that supports this?"

```yaml
Belief = Evidence FOR something
       = Minimum probability
       
# What you KNOW supports rain (for rain example)
# There is at least 50% probability of raining, given the evidence we have
*Think: "I'm AT LEAST this confident"*
```

**2. Plausibility (Pl) - Upper Bound**

"How much is it possible/plausible (not contradicted)?"

```yaml
**Plausibility = 1 - (Evidence AGAINST something)**
             = Maximum probability 
             
# What you DON'T know might still allow rain
# there is at most 80% probability of rain happening
# eg. 1 - (evidence that rain not heppening)
*Think: "I'm AT MOST this confident"*
```

**3. Ignorance/Uncertainty - The Gap**

```yaml
Ignorance = Plausibility - Belief
          = The gap between upper and lower bounds
          
**Think:** "This is how much I DON'T KNOW"
```

***Example 1 : (Mystery box)*** 

```yaml
Question: "Is there a bomb inside?"

Evidence:
❌ I've never seen the box
❌ I don't know who made it
❌ I have NO information

Belief(Bomb) = 0.0
   ↑
"I have ZERO evidence there IS a bomb"

Plausibility(Bomb) = (1 - evidence that there is no bomb) => 1 - 0 (0 becoz "I have no evidence there ISN'T a bomb either")
									 = 1.0

Interval: [0.0, 1.0]
            ↑    ↑
         HUGE GAP = Total ignorance!
         
         
0.0 ─────[●●●●●●●●●●●●●●●●●●●●●]─────── 1.0
        0.0                    1.0
        
The interval spans EVERYTHING! We know nothing!
```

***Example 2: (Rainy season)***

```yaml
Scenario: "Will it rain tomorrow?"

Evidence:
✅ Dark clouds gathering (supports rain)
✅ Barometer dropping (supports rain)
❌ But no guarantee (weather is complex)

- 40% chance of rain from the evidence we got
- 20% chance of not ranining (from the evidence that says no rain) 

Belief(Rain) = 0.4
   ↑
"I have evidence supporting 40% confidence"

Plausibility(Rain) = 1 - probabiliy of not raining from evidence => 0.8
   ↑
"Nothing contradicts up to 80% chance"

Interval: [0.4, 0.8]
           ↑    ↑
        MEDIUM GAP = Some uncertainty
        
        
 0.0 ────────────[●●●●●●●●●]──────────── 1.0
              0.4       0.8
              
We know something, but not everything!
```

> **Belief** = confirmed support for the event (eg rain), **Plausibility** = support for event thinking the evidence that we do not know (missing evidence) also support our event (eg rain)
> 

eg. if there is 

- 20% = confirmed support *for rain from the evidence*
- *30% = confirmed support of not rain*
- The remaining 50 **%** = **unknown / we have no evidence** (eg. we were not able to record the wind speed and other parameter)
- ***belif(rain)** = 20%*
- so ***plausibility*** will be 20% (confirmed) + 50% (no evidence) = 70%

***Example 3: Rainy 2*** 

```yaml
Weather: 60% evidence for rain, 10% evidence against rain
				Find Dempster-Shafer interval?

Answer: [0.6, 0.9]

Solution: Belief = 0.6 
					Plausibility = 1 - 0.1 = 0.9
		      Gap = 0.3 (uncertainty)
```

---

### **Learning Techniques**

The syllabus then moves to **Learning**. This overlaps slightly with Unit 1 (Neural Networks) but focuses on statistical and symbolic learning.

**1. Statistical Learning**

This is the basis of modern Machine Learning. Instead of being told rules, the system looks at data distributions to approximate a function. It learns patterns from data using statistics and probability. So we don’t have to explicitly define rules. It understands data by itself

- **Goal:** To find the most probable hypothesis $H$ given the data $D$.
- **Method:** It often uses **Maximum Likelihood Estimation (MLE)**—tuning the parameters of a model until the data fits well.

```yaml
YOU PROVIDE EXAMPLES:

Data:
Temperature | Weather Label
     35     |    "hot"
     28     |   "warm"
     15     |   "cold"
     32     |    "hot"
     22     |   "warm"
     ...

Computer learns the pattern:
"Temperatures above ~30 are usually 'hot'"
"Temperatures 20-30 are usually 'warm'"
"Temperatures below ~20 are usually 'cold'"
```

### **2. Induction Learning (Decision Trees)**

This is "Symbolic Learning." The AI builds a logic tree from a table of examples.

**Induction Learning = Learning general rules from specific examples In Decision Trees:**

- You show the computer a table of examples
- It builds a tree of IF-THEN rules automatically
- The tree can then classify new examples

**Why "Induction"?**

```yaml
INDUCTION = Specific → General

Examples (Specific):
- "This apple is red and sweet"
- "That apple is red and sweet"
- "Another red apple is sweet"

Rule (General):
→ "Red apples are usually sweet"

Computer induces (learns) the general rule from specific cases
```

**What is a Decision Tree?**

A tree of questions that leads to a decision!

Simple Example: Should I Play Tennis?

```yaml
            Weather?
           /        \
       Sunny      Rainy
        /            \
    Humidity?      Wind?
     /    \        /    \
  High  Normal Strong  Weak
   /      \      /       \
  NO     YES    NO      YES

Read it:
"If Sunny AND Humidity is Normal → Play Tennis (YES)"
"If Rainy AND Wind is Weak → Play Tennis (YES)"
"If Sunny AND Humidity is High → Don't Play (NO)"
```

Training Data:

| Day | Weather | Temperature | Humidity | Wind | Play Tennis? |
| --- | --- | --- | --- | --- | --- |
| 1 | Sunny | Hot | High | Weak | No |
| 2 | Sunny | Hot | High | Strong | No |
| 3 | Cloudy | Hot | High | Weak | Yes |
| 4 | Rainy | Mild | High | Weak | Yes |
| 5 | Rainy | Cool | Normal | Weak | Yes |
| 6 | Rainy | Cool | Normal | Strong | No |
| 7 | Cloudy | Cool | Normal | Strong | Yes |
| 8 | Sunny | Mild | High | Weak | No |
| 9 | Sunny | Cool | Normal | Weak | Yes |
| 10 | Rainy | Mild | Normal | Weak | Yes |
| 11 | Sunny | Mild | Normal | Strong | Yes |
| 12 | Cloudy | Mild | High | Strong | Yes |
| 13 | Cloudy | Hot | Normal | Weak | Yes |
| 14 | Rainy | Mild | High | Strong | No |

**Goal:** Build a tree that can predict "Play Tennis?" for new days!

**The ID3 Algorithm (Building the Tree)**

1. Look at the dataset.
2. Find the attribute that best splits the data (e.g., "weather in prev example"). This is calculated using **Information Gain (Entropy)**.
3. Create a branch for "Yes" and "No".
4. Repeat until all data is classified.

**Entropy**

- **Entropy** measures "messiness."
- If a bucket has 50 Red balls and 50 Blue balls, Entropy is **High** (1.0).
- If a bucket has 100 Red balls, Entropy is **Low** (0.0).
- The algorithm always chooses the question that reduces Entropy the most.

---

### **Recent Trends**

The syllabus ends with **"Recent trends in Fuzzy Logic & Knowledge Representation."**
This is usually a general theory section.

1. **Hybrid Systems:** Combining Neural Networks with Fuzzy Logic (Neuro-Fuzzy) to get the best of both worlds (Accuracy + Explainability).
2. **Ontologies (Web 3.0):** Standardizing Knowledge Representation so different systems on the internet can share data (e.g., how Google understands that "Jaguar" can be a car or an animal based on context).
3. **Deep Learning:** Moving from simple "Shallow" neural networks (Unit 1) to massive, multi-layered networks that perform "Feature Extraction" automatically.

---

END