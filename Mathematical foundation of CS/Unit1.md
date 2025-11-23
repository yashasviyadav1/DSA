# Unit 1
![unit-1 syllabus](https://i.ibb.co/qMQ9tQvC/image.png)

Unit1 Topics:

1. **Probability mass... functions (PMF)**
2. **density functions (PDF)**
3. **cumulative distribution functions (CDF)**
4. **parametric families of distributions** Binomial, Poisson, Exponential, Normal (like $\lambda$, $\mu$, and $\sigma$).
5. **Central Limit Theorem**

6. **Expected Value (or Expectation)**

7. **Variance**
8. **Conditional Expectation**

9. **Central Limit Theorm**
10. **Probabilistic Inequalities**
11. **Markov Chains**

### **Total Units: 4**

1. **Probability & Random Processes**
2. **Sampling & Estimation Theory**
3. **Statistical Inference & Multivariate Models**
4. **Graph Theory & Combinatorics**

Unit 1 – Probability & Distribution Functions

## What is Probability? (The Basics)

**Simple Definition:** Probability is just a way to measure "How likely is something to happen?"

**Scale:** Always between 0 and 1

- 0 = Impossible (never happens)
- 1 = Certain (always happens)
- 0.5 = 50-50 chance

**Example:**

- Probability of getting heads in a coin toss = 0.5
- Probability of sun rising tomorrow = 1 (certain)
- Probability of rolling a 7 on a standard die = 0 (impossible)

---

## Random Variables (The Foundation)

### What is a Random Variable?

Think of it as a **variable whose value depends on chance**.

**Example:**

- X = number you get when rolling a die
- X can be 1, 2, 3, 4, 5, or 6 (all random!)

### Two Types:

**1. Discrete Random Variables**

- Can only take specific, separate values
- Example: Number of students in class (can't be 25.5!)
- You can COUNT them

**2. Continuous Random Variables**

- Can take ANY value in a range
- Example: Height of a person (can be 5.7123... feet)
- You MEASURE them

In simple terms, a **random variable** is a variable whose value is a number that represents the outcome of a random process.
That's it. It's not a variable like `x` in the equation `x + 5 = 10.` It's a **function** that maps the messy, real-world outcomes of an experiment to a clean, simple number.
Let's use a classic computer science example: a packet transmission.
• **The Random Experiment:** You send a data packet over a network.
• **The Sample Space (Possible Outcomes):**
    ◦ `{Success}` (The packet arrives correctly)
    ◦ `{Failure}` (The packet is lost or corrupted)
• **The Random Variable (let's call it $X$):** We need to map these outcomes to numbers. We could define a variable $X$ as:
    ◦ `X = 1` if the outcome is `{Success}`
    ◦ `X = 0` if the outcome is `{Failure}`
Now, instead of talking about "the probability of success," we can talk about `P(X = 1)` This variable `X`is a random variable. It's a special type called an **Indicator Random Variable**, which is used *all the time* in algorithm analysis.

**The Two Main Types of Random Variables**

You'll encounter two types, and the distinction between them is critical. It determines the exact mathematical tools you can use.

**1. Discrete Random Variable (DRV)**

This is a variable that can only take on a **countable** number of distinct values. Think of things you can *count*.
• **What it is:** The values are separate and distinct, often integers (e.g., 0, 1, 2, 3, ...).
• **The Tool You Use:** **Probability Mass Function (PMF)**. This is what we just discussed. The PMF gives you the exact probability `P(X = k)` for each specific value `k`.
**Examples for an M.Tech CSE Student:**
• **Algorithm Analysis:** Let `X` = the number of **comparisons** your randomized Quicksort algorithm performs. `X` could be 1000, 1015, or 1000000, but it can't be 1000.5.
• **Networking:** Let `Y` = the number of **packet retransmissions** required for a message (part of the TCP protocol). `Y` can be 0, 1, 2, 3, ...
• **Data Structures:** Let `Z` = the **number of nodes** in a specific level of a randomly built binary search tree.
• **The variable we just made:** `X`= 1 if a packet arrives, 0 if it fails.

**2. Continuous Random Variable (CRV)**

This is a variable that can take on an **infinite** number of possible values within an interval. Think of things you *measure*.
• **What it is:** The variable can be *any* real value in a range (e.g., any value between 0.0 and 1.0).
• **The Problem:** The probability of a continuous variable being *exactly* one specific value is zero. For example, what's the probability that a server response time is *exactly* 0.034987123... seconds? It's zero, because there are infinite other possibilities.
• **The Tool You Use:** **Probability Density Function (PDF)**. Instead of giving the probability of a single point, the PDF gives you a curve where the **area under the curve** between two points gives you the probability of the variable falling *within that range*.
**Examples for an M.Tech CSE Student:**
• **Distributed Systems:** Let `T` = the **time between** user requests arriving at your web server (the "interarrival time"). `T` could be 0.5s, 0.51s, 0.51123s, etc.
• **Machine Learning:** Let `E` = the **error** of your regression model's prediction. Your model might be off by 1.2, 3.4, or 0.005. This error is a continuous variable.
• **Networking:** Let `L` = the **latency** (ping time) to a server. This is a measurement, like 24.3 milliseconds.

**Summary: PMF vs. PDF**

| **Feature** | **Discrete Random Variable (DRV)** | **Continuous Random Variable (CRV)** |
| --- | --- | --- |
| **Values** | Countable (e.g., 0, 1, 2,...) | Uncountable (e.g., $0 \le x \le 1$) |
| **Examples** | Number of packet losses, comparisons in an algorithm | Time between arrivals, server latency |
| **Probability Tool** | **Probability Mass Function (PMF)** | **Probability Density Function (PDF)** |
| **Key Question** | What is `P(X = 5)`? | What is `P(4 < X < 5)`? |

---

## **Probability Mass Function - (PMF)**

Now that we know what a discrete random variable is (a variable that can take on countable values, like 0, 1, 2, ...), the PMF is our primary tool for working with it.

**The Core Definition of PMF**

A **Probability Mass Function**, or PMF, is a function that gives the probability that a discrete random variable ($X$) is *exactly equal* to some specific value ($k$).

> In simple terms: You ask, "What's the probability of getting exactly 3 packet losses?" The PMF is the formula that gives you the answer.
> 

It's written as:

$f_X(k) = P(X = k)$

A function is only a valid PMF if it satisfies two non-negotiable rules:

1. **Non-negative:** $f_X(k) \ge 0$ for all possible values of $k$. (A probability can't be negative).
2. **Sums to 1:** The sum of the probabilities for *all possible outcomes* must equal 1. $\sum_{k} f_X(k) = 1$.

The best way to understand PMFs is to see them in action. Your syllabus's "parametric families" are the most famous PMFs used in computer science. Let's look at the three most important ones.

---

### Case Study 1: The Bernoulli Distribution (The "Single Coin Flip")

This is the simplest possible PMF. It models a **single trial** with only **two possible outcomes**: success or failure.

- **The "Story":** A single yes/no question.
- **Random Variable ($X$):**
    - $X = 1$ (for "success")
    - $X = 0$ (for "failure")
- **Parameter:** $p$, the probability of success. (The probability of failure is $1-p$).
- **CS Example:**
    - A single network packet arrives ($X=1$) or is lost ($X=0$).
    - A user clicks on an ad ($X=1$) or does not ($X=0$).
    - A disk write succeeds ($X=1$) or fails ($X=0$).

**The PMF Formula**

The PMF for a Bernoulli distribution is:

 $P(X = k) = \begin{cases} p & \text{if } k = 1 \\ 1 - p & \text{if } k = 0 \end{cases}$ 

You'll also see this written in a single, clever line: $P(X=k) = p^k (1-p)^{1-k}$ for $k \in \{0, 1\}$.

---

### Case Study 2: The Binomial Distribution (The "N Coin Flips")

This is what you get when you **repeat a Bernoulli trial $n$ times** and count the total number of successes.

- **The "Story":** What is the probability of getting *k* successes in *n* independent trials?
- **Random Variable ($X$):** The total number of successes. $X$ can be any integer from $0$ to $n$.
- **Parameters:**
    - $n$: The total number of trials.
    - $p$: The probability of success *in each individual trial*.
- **CS Example:**
    - You send **100 packets** ($n=100$). Each has a **95%** chance of success ($p=0.95$). What's the probability that *exactly 98* packets arrive? ($k=98$).
    - You have a batch of **50** hard drives ($n=50$). The probability of any *one* drive being defective is **1%** ($p=0.01$). What's the probability of finding *exactly 2* defective drives? ($k=2$).

**The PMF Formula**

This formula has three parts:

$P(X = k) = \binom{n}{k} p^k (1-p)^{n-k}$

- $\binom{n}{k}$: The "binomial coefficient," read as "**n choose k**". It's the number of *ways* you can arrange $k$ successes within $n$ trials. ($\binom{n}{k} = \frac{n!}{k!(n-k)!}$).
- $p^k$: The probability of getting $k$ successes.
- $(1-p)^{n-k}$: The probability of getting $(n-k)$ failures.

---

### The Binomial PMF Explained with examples

The formula you're asking about is the **Probability Mass Function (PMF) for the Binomial Distribution**.

It's a powerful formula used to model the probability of getting a specific number of successes in a set number of independent trials.

![](https://i.ibb.co/HpL8QyYS/image.png)

$P(X = k) = \binom{n}{k} p^k (1-p)^{n-k}$

**The Ingredients**

- $n$: The total number of independent trials (e.g., you flip a coin **10** times).
- $k$: The specific number of successes you want to find the probability for (e.g., you want exactly **7** heads).
- $p$: The probability of success on a *single* trial (e.g., the probability of getting heads, **0.5**).
- $(1-p)$: The probability of failure on a *single* trial (e.g., the probability of getting tails, $1 - 0.5 = 0.5$).
- $P(X = k)$ : The final answer. This is read as "The probability that the random variable $X$ (our count of successes) is equal to *exactly* $k$."

**Breaking Down the Formula into Its Three Parts**

Let's analyze the formula $P(X = k) = \binom{n}{k} p^k (1-p)^{n-k}$ by looking at each of its three main components.

**Part 1: $p^k$ (The Probability of Your Successes)**

- **What it is:** This is $p$ multiplied by itself $k$ times.
- **Why it's here:** If you want $k$ successes, and the probability of *one* success is $p$, you need to string $k$ of these events together. Since all trials are independent, we multiply their probabilities.
- **Example:** The probability of getting 3 heads in a row is $p \times p \times p = p^3$.

**Part 2: $(1-p)^{n-k}$ (The Probability of Your Failures)**

- **What it is:** This is the probability of failure, $(1-p)$, multiplied by itself $(n-k)$ times.
- **Why it's here:** If you have $n$ total trials and $k$ of them are successes, the *rest* of them must be failures. The number of failures is simply the total minus the successes, or $(n-k)$.
- **Example:** If you flip a coin 5 times ($n=5$) and want 3 successes ($k=3$), you must have $5 - 3 = 2$ failures. The probability of 2 failures in a row is $(1-p) \times (1-p) = (1-p)^2$.

> Putting Parts 1 & 2 Together:
The term $p^k (1-p)^{n-k}$ represents the probability of one specific sequence of $k$ successes and $(n-k)$ failures.
> 
> 
> For example, if $n=5$ and $k=3$, this is the probability of getting:
> **Success-Success-Success-Failure-Failure**
> $p \times p \times p \times (1-p) \times (1-p) = p^3(1-p)^2$
> 
> But this is also the probability of:
> **Success-Failure-Success-Failure-Success**
> $p \times (1-p) \times p \times (1-p) \times p = p^3(1-p)^2$
> 
> This brings us to the crucial third part.
> 

**Part 3: $\binom{n}{k}$ (The Number of Ways)**

- **What it is:** This is the **binomial coefficient**, read as "$n$ choose $k$." It's calculated as $\frac{n!}{k!(n-k)!}$.
- **Why it's here:** This formula calculates the total number of different ways you can arrange $k$ successes within $n$ trials. As shown above, there are many different *orders* in which you can get your $k$ successes (e.g., `HHT, HTH, THH`).
- Since each of these unique sequences has the *exact same probability* (which we found in Parts 1 & 2), we just multiply that probability by the total number of ways it can happen.

**A Concrete Example**

Let's find the probability of getting **exactly 2 heads (**$k=2$**)** when flipping a fair coin **3 times (**$n=3$**)**.

- $n = 3$ (total flips)
- $k = 2$ (desired number of heads)
- $p = 0.5$ (probability of heads)
- $(1-p) = 0.5$ (probability of tails)

Let's plug this into the formula: $P(X = 2) = \binom{3}{2} (0.5)^2 (0.5)^{3-2}$

1. **Part 1:** $p^k \rightarrow (0.5)^2 = 0.25$
This is the probability of our 2 heads.
2. **Part 2:** $(1-p)^{n-k} \rightarrow (0.5)^1 = 0.5$
This is the probability of our 1 tail.
3. **Part 3:** $\binom{n}{k} \rightarrow \binom{3}{2}$
This means "how many ways can we arrange 2 heads in 3 flips?" Let's list them:
    - **H-H-T**
    - **H-T-H**
    - **T-H-H**
    There are **3** ways. (The formula $\frac{3!}{2!(3-2)!}$ also gives us 3).

**Putting it all together:**

$P(X = 2) = \text{(Number of ways)} \times \text{(Prob. of successes)} \times \text{(Prob. of failures)}$

$P(X = 2) = 3 \times 0.25 \times 0.5$

$P(X = 2) = 0.375$

So, there is a 37.5% chance of getting exactly 2 heads on 3 coin flips.

---

### Case Study 3: The Poisson Distribution (The "Event Rate")

This one is different and extremely important for systems modeling. It does **not** have a fixed number of trials ($n$). Instead, it models the number of events that occur in a **fixed interval of time or space**.

- **The "Story":** We know the *average rate* of an event. What's the probability of *k* events happening in that interval?
- **Random Variable ($X$):** The number of events that occur. $X$ can be 0, 1, 2, 3, ... (with no upper limit).
- **Parameter:** $\lambda$ (lambda), the **average number of events** in the interval.
- **CS Example:**
    - A web server receives an **average of 10 requests per second** ($\lambda=10$). What is the probability it receives *exactly 15* requests in a given second? ($k=15$).
    - A block of code has an **average of 2.5 bugs per 1000 lines** ($\lambda=2.5$). What is the probability of finding *zero* bugs in a 1000-line block? ($k=0$).
    - Customers arrive at a queue at an **average rate of 3 per minute** ($\lambda=3$). What is the probability that *5 or more* customers arrive in the next minute? (You'd calculate $1 - [P(X=0) + ... + P(X=4)]$).
    
    ![](https://i.ibb.co/6j0yRv5/image.png)
    

**The PMF Formula**

$P(X = k) = \frac{\lambda^k e^{-\lambda}}{k!}$

- $\lambda^k$: The average rate, scaled by the number of events you're asking about.
- $e^{-\lambda}$: A scaling factor that ensures the total probability sums to 1. ($e$ is Euler's number, $\approx 2.718$).
- $k!$: The factorial of $k$. This normalizes the probability.

---

### The **Poisson Distribution Explained with example**

We are no longer counting "successes" out of a *fixed number* of trials ($n$).
Instead, we're measuring **how many times an event happens** in a *fixed interval* of time or space, given that we know the **average rate** at which it happens.

**The Ingredients**
First, let's look at the "ingredients" for the formula:

$P(X = k) = \frac{\lambda^k e^{-\lambda}}{k!}$

• **$\lambda$ (lambda):** This is the single most important number. It's the **average number of events** that occur in your specific interval. (e.g., average 10 requests/sec, average 2.5 bugs/1000 lines).
• **$k$:** This is the **specific number of events** you want to find the probability for. (e.g., what's the probability of *exactly* 15 requests? $k=15$).
• **$e$:** This is Euler's number ($\approx 2.718...$). It's a fundamental mathematical constant, like pi ($\pi$), that shows up in all kinds of natural growth and rate-based processes.
• **$k!$ (k-factorial):** This is $k \times (k-1) \times (k-2) \times ... \times 1$. (e.g., $4! = 4 \times 3 \times 2 \times 1 = 24$).
• **$P(X = k)$:** The final answer. "The probability that the number of events $X$ is equal to *exactly* $k$."

**Breaking Down the Formula into Its Three Parts**
The formula is a single fraction, but we can analyze its three main components:

**1. The Numerator (Part 1): `$\lambda^k$` (The "Event" Term)**

• **What it is:** This is the average rate ($\lambda$) raised to the power of the number of events ($k$) you're looking for.
• **Why it's here:** This part of the formula scales the probability based on the *average*. If the average $\lambda$ is high, you'd naturally expect a higher probability of seeing many events. This term is the main "engine" of the probability, connecting the average rate to the specific outcome $k$ you're testing.

**2. The Numerator (Part 2): $e^{-\lambda}$ (The "Scaling" or "Zero-Event" Term)**

• **What it is:** This is $e$ raised to the power of the *negative* average.
• **Why it's here:** This is a crucial scaling factor that "anchors" the whole distribution. It's actually the probability of **zero** events occurring ($P(X=0)$). In a way, the Poisson formula calculates the probability of $k$ events by starting with the probability of *zero* events ($e^{-\lambda}$) and then scaling it up by the "event term" ($\lambda^k$). This component ensures that all the probabilities for $k=0, 1, 2, ...$ add up to 1.

**3. The Denominator: $k!$ (The "Normalization" Term)**

• **What it is:** The factorial of the number of events, $k$.
• **Why it's here:** As you noted, this normalizes the probability. Why? Because the events are *indistinguishable*. If 3 customers arrive in one minute, we don't care about the *order* in which they arrived. The $\lambda^k$ term overcounts the possibilities, and dividing by $k!$ (which is the number of ways to arrange $k$ items) corrects for this overcounting. It scales the probability back down to the correct value.

**A Concrete Example (Using Yours)**

Let's use your bug example: A block of code has an average of **2.5 bugs per 1000 lines ($\lambda=2.5$)**. What is the probability of finding **zero bugs ($k=0$)** in a 1000-line block?
• $\lambda = 2.5$
• $k = 0$
Let's plug this into the formula: $P(X = 0) = \frac{2.5^0 \times e^{-2.5}}{0!}$
1. $\lambda^k \rightarrow 2.5^0 = 1$
(Anything to the power of 0 is 1)
2. $e^{-\lambda} \rightarrow e^{-2.5} \approx 0.082$
(This is the "scaling factor")
3. $k! \rightarrow 0! = 1$
(By mathematical definition, 0-factorial is 1)

**Putting it all together:**

$P(X = 0) = \frac{1 \times 0.082}{1}$

$P(X = 0) = 0.082$

So, there is an **8.2% chance** of finding zero bugs in that block of code, even though the average is 2.5.

---

### Summary: Which PMF to Use?

| **Model** | **Bernoulli** | **Binomial** | **Poisson** |
| --- | --- | --- | --- |
| **Question** | 1 trial, success/fail? | $k$ successes in $n$ trials? | $k$ events in an interval? |
| **Random Variable** | $X \in \{0, 1\}$ | $X \in \{0, 1, ..., n\}$ | $X \in \{0, 1, 2, ...\}$ |
| **Parameters** | $p$ (prob. of success) | $n$ (num. of trials), $p$ | $\lambda$ (average rate) |
| **CS Example** | Click / No Click | 5/10 packets succeed | 20 requests/second |

This is how the PMF moves from a simple definition to a powerful toolkit for modeling real-world systems.

---

## **Probability Density Function - (PDF)**

We're now moving from *counting* (discrete) to *measuring* (continuous). This is the key difference, and it changes how we think about probability.
This is where the **Probability Density Function (PDF)** comes in.

**The Big Problem with Continuous Variables**
A **continuous random variable** is one that can take on an *infinite* number of values in a range. Think about a server's response time.
• It could be 0.5 seconds.
• It could be 0.51 seconds.
• It could be 0.5112345 seconds.
If I ask, "What's the probability the response time is *exactly* 0.5112345... seconds?" The answer is **zero**. Why? Because there are infinitely many other possibilities it could have been.
This means a PMF, which gives $P(X=k)$, is useless for continuous variables.

**The Solution: The Probability Density Function (PDF)**
A PDF is a function where the **area under the curve** gives you the probability.
We *never* ask for the probability of a single point. We *always* ask for the probability of a **range**.In simple terms: You don't ask, "What's the probability of the response time being 0.5s?"
You ask, "What's the probability of the response time being between 0.5s and 0.6s?"
The PDF, $f_X(x)$, is the curve. The probability is the area under that curve from 0.5 to 0.6.

$P(a \le X \le b) = \text{Area under the PDF curve from } a \text{ to } b$

This is calculated using an integral: 

$P(a \le X \le b) = \int_{a}^{b} f_X(x) dx$.

**Two Key Rules for a PDF:**

1. **Non-negative:** $f_X(x) \ge 0$ for all $x$. (The curve can't dip below the x-axis).
2. **Total Area is 1:** The total area under the *entire* curve (from $-\infty$ to $+\infty$) must equal 1. This is the same as the PMF's rule that all probabilities must sum to 1.

**What is $f_X(x)$? (The PDF)**

Since $P(X=k)$ doesn't work, we can't use a PMF. Instead, we use a Probability Density Function (PDF), which is $f_X(x)$.
• $f_X(x)$ is NOT a probability.
• It's a function that describes the *relative likelihood* (or *density*) of the variable being around the value $x$.
• Where the $f_X(x)$ curve is **high**, the values of $X$ are more likely to occur.
• Where the $f_X(x)$ curve is **low**, the values are less likely

![](https://i.ibb.co/Y7qdkG14/image.png)

**What is the Integral $\int_{a}^{b} ... dx$? (The "Area Under the Curve")**

This is the key. The integral is just a calculus tool for finding the **area under a curve**.
In probability, this area *is* the probability.
So, your formula:
$P(a \le X \le b) = \int_{a}^{b} f_X(x) dx$
...is just a formal way of saying:"The probability that $X$ falls somewhere between $a$ and $b$ is equal to the **total area under the density curve** $f_X(x)$, measured from $a$ to $b$

| **Feature** | **PMF (like Binomial, Poisson)** | **PDF (like Normal Distribution)** |
| --- | --- | --- |
| **Variable Type** | Discrete (you count it: 0, 1, 2...) | Continuous (you measure it: 1.5, 1.51...) |
| **The Formula Gives** | The exact probability at one point, $P(X=k)$ | The *density* at a point. It's **not** probability. |
| **How to get Probability** | You just use the PMF formula. | You must find the **area under the curve** using an integral, $\int_{a}^{b} f_X(x) dx$. |

---

### **Case Study 1: The Exponential Distribution (The "Waiting Time" Model)**

This is one of the most important distributions in computer science and is directly related to the Poisson PMF.

- **Poisson PMF (Discrete):** Counts the *number of events* in an interval (e.g., 10 requests/sec) or "How many events happen in one minute?" (e.g., 3 customers)
- **Exponential PDF (Continuous):** Measures the *time between* those events (e.g., 0.1 seconds between requests) or How long do we have to wait *for the next* customer?" (e.g., 0.45 minutes)

The graph of the exponential distribution always has this "decay" shape. It shows that very short wait times are the most likely, and very long wait times are very unlikely (but still possible).

**Examples:**

- The time between requests arriving at your web server.
- The time until a component (like a hard drive) fails.
- The time between one customer arriving at a queue and the next customer arriving.

**Key Characteristic: "*Memorylessness*"**
This is the most famous and important property of the exponential distribution.
It means **the process "forgets" what has happened in the past.**

The "Dumb" Toaster

Imagine you have a very basic, "dumb" toaster. This toaster isn't well-made. It has a **constant 1% chance of breaking *forever*** every single time you use it.

- The probability it *survives* one use is 99%.
- The probability it *breaks* on one use is 1%.

**Scenario 1: The Brand New Toaster**
You buy a brand-new toaster. You want to toast some bread.

- What's the probability it breaks on this very first use? **1%**.

**Scenario 2: The "Old" Toaster**
Now, imagine you've successfully used this *same toaster* **500 times in a row**. You are a very lucky person.

- It's time for your 501st use. You put in your bread.
- **Question:** What's the probability it breaks *this time*?

**The "Memoryless" Answer:** The probability is **still 1%**.

**Why?**
The toaster is "dumb." It doesn't know it has survived 500 uses. It hasn't "worn out" like a normal toaster. It hasn't "aged." It's still the same simple machine with a 1% chance of failure *every single time you press the button*.

The 500 successful uses in the past **tell you nothing** about what will happen on the 501st use. The toaster has no "memory" of its past success.

**The Opposite: What *Isn't* Memoryless?**

To make this clearer, let's think of something that ISN'T memoryless.

Waiting for a Bus

- The bus is scheduled to arrive at 10:00 AM.
- At 9:50 AM: The probability of the bus arriving in the next 5 minutes (by 9:55) is very low (maybe 0%).
- At 9:59 AM: You have "waited" 9 minutes. The probability of the bus arriving in the next 5 minutes (by 10:04) is now very high (maybe 99%).

In this case, the time you've already waited *dramatically* changes the probability of what will happen in the future. The system has a memory (it's called a "schedule").

"Memorylessness" means the past has no effect on the future. The process is as "fresh" at every single moment as it was at the very beginning.

The "story" of the Poisson and Exponential distributions are two sides of the same coin:

- **Poisson** counts *how many* events happen in a fixed time. (e.g., "3 customers arrived *in one minute*.")
- **Exponential** measures the *time between* those events. (e.g., "The wait *for the next customer* was 0.45 minutes.")

**The Shared Partner: $\lambda$ (Lambda)**
The "magic" is that they use the exact same parameter, $\lambda$.
• In the Poisson distribution, $\lambda$ is the average rate of events. Example: $\lambda = 3$ customers per minute.
• In the Exponential distribution, this *same* $\lambda$ is the average rate of events. Example: $\lambda = 3$ is the rate you plug into the formula.

This creates a beautiful inverse relationship:
If your average rate is $\lambda = 3$ customers per minute...
...then your average time between customers is $1/3$ of a minute.
For the Exponential distribution, the **mean (average) wait time is $1/\lambda$**. This is the key connection.

**The PDF Formula for the Exponential Distribution**

Here is the formula for the Probability Density Function (PDF):

$f(x) = \lambda e^{-\lambda x}$

• **$f(x)$:** The Probability Density. Remember, this isn't a probability itself. It's the *height* of the "decay" curve.
• **$\lambda$ (**lambda)**:** The average *rate* of events (the same $\lambda$ from Poisson).
• **$e$:** Euler's number ($\approx 2.718$), the base of natural growth and decay.
• **$x$:** The variable. It represents the *time* you are waiting (e.g., $x=0.5$ minutes, $x=10$ seconds).
This formula $f(x) = \lambda e^{-\lambda x}$ is what *draws* that classic decay curve.

**How We *Actually Use* the Formula**
we know, that we need to find the **area under the curve (integrate)** to get a real probability.
This sounds hard, but for the Exponential distribution, the integrals are already solved for us and give two very simple, powerful formulas:

- 1. Probability of it happening before time $x$ :
(e.g., "What's the probability the server fails within 2 years?")
$P(X \le x) = 1 - e^{-\lambda x}$

- 2. Probability of it happening after time $x$ :
(e.g., "What's the probability the server survives more than 2 years?")
$P(X > x) = e^{-\lambda x}$
- (Notice that these two formulas add up to 1, which makes sense!)

**A Concrete Example for Exponential PMF**

Let's use our server example:

- Poisson Story: A web server receives an average of λ=10 requests per second.
- Exponential Question: What is the probability that the *next request* arrives in less than 0.1 seconds?
- λ=10 (the rate)
- x=0.1 (the time)
- We want the probability of the wait time being *less than* x, so we use the first formula: $P(X \le x) = 1 - e^{-\lambda x}$

**Calculation:**

$P(X \le 0.1) = 1 - e^{-(10)(0.1)}$

$P(X \le 0.1) = 1 - e^{-1}$

$e^{-1}$ is approximately $0.368$ 

$P(X \le 0.1) = 1 - 0.368$

$P(X \le 0.1) = 0.632$

**Answer:** There is a **63.2% chance** that the next request will arrive in less than 0.1 seconds.

**Doubt: Since the if Exponential PDF is memoryless (i.e waiting time does’nt matter) then why we using waiting time $x$  in its formula ?** 

> Because the *length of the future window you're asking about* matters. A 30-second window ($x=30$) will have a different probability than a 0.1-second window ($x=0.1$).
> 

You are confusing two different things:
1. Time that has *already passed* (the "past," which is the "memory").
2. A *future time window* we are making a prediction about (the "$x$" in the formula).
The "Memoryless" property means #1 (the past) has no effect on the probability of #2 (the future).
The variable $x$ is in the formula because the size of the future window *absolutely* matters.
Let's break this down.

The "Memoryless" Part vs. The "Future Window" ($x$)

The "Memoryless" Property says:
It doesn't matter if you started waiting 1 second ago or 1 hour ago. The probability of the next event happening within the next 0.1 seconds is always the same.
The "Future Window" ($x$) in the formula says:
The probability of an event happening within the next 0.1 seconds is DIFFERENT from the probability of it happening within the next 30 seconds.
Of course, a longer future window ($x=30$) has a higher probability of containing the event than a short future window ($x=0.1$).
The formula $P(X \le x) = 1 - e^{-\lambda x}$ is **only** telling you the probability for that *future window* of length $x$.

**A Concrete Example**

Let's use our server again: $\lambda = 10$ requests per second.
The formula for the probability of a request arriving in the next $x$ seconds is:
$P(X \le x) = 1 - e^{-10x}$

Scenario A: "Fresh Start"
• You start your clock at $t=0$.
• **Question:** What's the probability the next request arrives **within 0.1 seconds** (i.e., before $t=0.1$)?
• **$x = 0.1$**
• **Answer:** $P(X \le 0.1) = 1 - e^{-10(0.1)} = 1 - e^{-1} \approx 0.632$ (or 63.2%)

Scenario B: "The Memoryless Test"
• You start your clock. You wait... and wait... 5 whole seconds go by... and no request has come.
• You are now at $t=5$.
• Question: *Starting from this new point*, what's the probability the next request arrives within the next 0.1 seconds (i.e., before $t=5.1$)?
• The "Memory" Fallacy: You might *think*, "Well, I've already waited 5 seconds, and the average is 10 per second, so one must be *really* overdue. The probability should be super high, like 99%!" This is false.
• The "Memoryless" Truth: The system has no "memory" of the past 5 seconds. It doesn't feel "overdue." The 5 seconds of waiting are irrelevant.
• We are *still* just asking about the probability of an event happening in a future window of length $x = 0.1$ seconds.
• $x = 0.1$
• Answer: The probability is exactly the same as Scenario A.
$P(\text{event between 5.0 and 5.1}) = 1 - e^{-10(0.1)} = 1 - e^{-1} \approx 0.632$ (or 63.2%)

---

### **Case Study 2: The Normal Distribution (The "Bell Curve")’**

The **Normal Distribution** (or "Gaussian Distribution") is a continuous probability distribution (a PDF) that is famous for its symmetric, *bell-like shape.*

It's the single most important distribution because it describes an incredible number of real-world phenomena.

**The "Story":** We are measuring a natural phenomenon (like human height, exam scores, or measurement errors). Most of the values will be clustered around a central **average**, and values farther away from the average become progressively rarer.

**The Two Ingredients (Parameters)**
Everything about the bell curve is defined by just two numbers:
1. **The Mean ($\mu$ - "mu")**: This is the **center** of the bell. It's the average, median, and mode all in one. It tells you where the peak of the curve is.
2. **The Standard Deviation ($\sigma$ - "sigma")**: This is the **spread** of the bell. It tells you how "wide" or "narrow" the data is.
    ◦ A **small $\sigma$** means the data is tightly clustered around the mean (a **tall, skinny** bell).
    ◦ A **large $\sigma$** means the data is very spread out (a **short, wide** bell).

**what is this $\sigma$ - "sigma" actually?**

Imagine a city. The average (mean) house price is $100,000 ($\mu = 100,000$).The "standard block length" (standard deviation) in this city is $15,000 ($\sigma = 15,000$).

A Z-score of $z = 1$ means 'you are exactly 1 standard deviation above the mean.'" means you are "1 block east (above) of Home."
• **In our example:** "Home" is $100,000. One "block" is $15,000.
• So, you are at $100,000 + $15,000 = **$115,000**.

so in basic terms sigma or standard deviation is just a unit for describing how far or near is our value from the mean

**The Empirical Rule (The "68-95-99.7" Rule)**

This is the most famous and useful rule of thumb for the Normal Distribution. It's the reason it's so powerful for making predictions.
It states that for *any* normal distribution, a predictable percentage of the data will fall within a certain number of standard deviations from the mean:
• **~68%** of all data falls within **1 standard deviation** of the mean (i.e.,between $\mu - \sigma$ and $\mu + \sigma$).
• **~95%** of all data falls within **2 standard deviations** of the mean(between $\mu - 2\sigma$ and $\mu + 2\sigma$).
• **~99.7%** of all data falls within **3 standard deviations** of mean(between $\mu - 3\sigma$ and $\mu + 3\sigma$).

note: 2 standard deviations" is just a rounded number that's easy to remember.

The number **1.96** is the **exact, precise Z-score** required for 95%.

**Example:**
• The average IQ is 100 ($\mu=100$) and the standard deviation is 15 ($\sigma=15$).
• This rule tells us that 68% of people have an IQ between 85 (100 - 15) and 115 (100 + 15).
• It also tells us that 95% of people have an IQ between 70 (100 - 30) and 130 (100 + 30).

**The PDF Formula (The "Scary" Part)**

Here is the formula for the PDF. It looks intimidating, but you *almost never use* it directly.

$f(x) = \frac{1}{\sigma \sqrt{2\pi}} e^{-\frac{1}{2}\left(\frac{x-\mu}{\sigma}\right)^2}$
The only reason I'm showing you this is to point out two things:
1. The only variables you plug in to define the curve's shape are the **mean ($\mu$)** and **standard deviation ($\sigma$)**.
2. The rest ($e$, $\pi$) are just constants to make sure the total area under the curve (our total probability) equals exactly 1.

**How We *Actually* Use It: The Z-Score**

Since it's a PDF, finding a probability (like $P(90 \le \text{IQ} \le 110)$) would mean integrating that scary formula. Nobody wants to do that.
So, we use a "cheat." We **standardize** any normal distribution into a special one called the **Standard Normal Distribution**.
• *Standard Normal Distribution: A special bell curve with a Mean ($\mu$) of 0 and a Standard Deviation ($\sigma$) of 1.*
We do this using a **Z-Score**.

> The Z-Score formula for a single observation is:
**$z = \frac{x - \mu}{\sigma}$**
> 

> Z-score for a sample mean (used in statistical inference in unit 3): 
$z = \frac{\bar{x} - \mu}{\sigma / \sqrt{n}}$
>

This simple formula translates your specific value ($x$) into a "Z-score." The Z-score simply tells you:
"How many standard deviations is $x$ away from the mean?"
• A Z-score of $z = 1$ means "you are exactly 1 standard deviation *above* the mean."
• A Z-score of $z = -2$ means "you are exactly 2 standard deviations *below* the mean."
Once we have a Z-score, we just look up the probability in a "Z-table" or use a calculator. This is how *all* normal distribution problems are solved.

**The "Secret Weapon": The Central Limit Theorem**

You might be wondering: "This bell type is a great shape, but why is it *everywhere*?"

The answer is the Central Limit Theorem (CLT). The CLT is one of the most powerful ideas in all of math. It states:

> "If you take a bunch of random samples, and find the average of each sample, the distribution of those averages will always end up looking like a perfect Normal Distribution (a bell curve), no matter what the original distribution looked like!"
> 

**Normal Distribution explained with Example**

**The Problem:** the scores for a final exam are normally distributed (this is the key phrase that tells us to use the bell curve).
• The mean (average) score is $\mu = 75$.
• The standard deviation is $\sigma = 10$.
Question: What percentage of students scored above 90?

**Solution:** 
From the problem, we know:
• Mean ($\mu$) = 75
• Standard Deviation ($\sigma$) = 10
• Our value of interest ($x$) = 90
• Our Goal: Find $P(X > 90)$

**Step 1:** Standardize with the Z-Score

We can't use the raw score of 90. We must first convert it to a "standardized" Z-score. This tells us how many "blocks" (standard deviations) 90 is away from "home" (the mean).
• **Formula:** $z = \frac{x - \mu}{\sigma}$
• Calculation:
$z = \frac{90 - 75}{10}$

$z = \frac{15}{10}$

$z = 1.5$

**Step 2:** Interpret the Z-Score

• A Z-score of **1.5** means that a score of 90 is exactly 1.5 standard deviations above the mean.
• Our original question $P(X > 90)$ is now the *exact same* as $P(Z > 1.5)$. We are now just using the "standard map" where the mean is 0 and the S.D. is 1.

**Step 3:** Find the Probability (The "Lookup")

![](https://i.ibb.co/6000FdVN/image.png)

We now need to find the probability associated with $z = 1.5$. We do this by looking up the Z-score in a **Standard Normal (Z) Table**. 

Important note**:** Standard Z-tables almost always tell you the probability **to the LEFT** of your Z-score (i.e., the total area *below* that score).
When we look up $z = 1.5$ in a table, it gives us a value of **0.9332**.
• This means that **93.32%** of the data is *BELOW* a Z-score of 1.5.
• In our problem, this means 93.32% of students scored **less than 90**.
But our question asked for the area *to the right* (percentage of students who scored **ABOVE** 90).
Since the total area under the entire curve is 1 (or 100%), we just subtract:
• **Formula:** $P(Z > 1.5) = 1 - P(Z < 1.5)$
• Calculation:
$P(Z > 1.5) = 1 - 0.9332$

$P(Z > 1.5) = 0.0668$

The probability of a student scoring above 90 is **0.0668**.
To express this as a percentage, we multiply by 100.
**Answer:** **`6.68%`** of students scored above 90 on the exam.

| **Feature** | **PMF (Probability Mass Function)** | **PDF (Probability Density Function)** |
| --- | --- | --- |
| **Variable Type** | **Discrete** (Countable) | **Continuous** (Measurable) |
| **Examples** | No. of packet losses, No. of clicks | Server response time, Latency |
| **How it works** | Gives **exact probability** at a point. | Gives probability over a **range**. |
| **Key Formula** | $f(k) = P(X = k)$ | $P(a \le X \le b) = \int_{a}^{b} f(x) dx$ |
| **Y-axis Value** | Is a probability (from 0 to 1). | Is a *density*, not a probability. Can be > 1. |
| **"Sum to 1" Rule** | $\sum_{k} f(k) = 1$ | $\int_{-\infty}^{\infty} f(x) dx = 1$ (Total area is 1) |

---

### **Cumulative Distribution Function - (CDF)**

The **Cumulative Distribution Function (CDF)** is the "master" function for any probability distribution. The PMF and PDF are great, but the CDF is the one function that can describe *any* kind of random variable (discrete, continuous, or a mix).

**The One Definition to Remember**

The CDF, written as $F(x)$, is a function that gives you the total probability of all outcomes **less than or equal to** a specific value $x$.
The formula is:
$F(x) = P(X \le x)$
Think of it as the "total-so-far" function or the "accumulator." It always answers the question: "What's the probability we've landed at or below this number?"
Let's see how this one definition applies to the two types of variables we've discussed.

**CMF for  Discrete Variables (like Binomial, Poisson)**

For a discrete variable, the CDF is a **sum**. To find $F(x)$, you just add up the individual probabilities (PMF) for all outcomes $k$ that are less than or equal to $x$.

$F(x) = \sum_{k \le x} P(X=k)$

**Example: A Fair 6-Sided Die**
• $P(X=1) = 1/6$
• $P(X=2) = 1/6$
• ...etc.
Let's find the CDF, $F(x)$, for a few values:
• **$F(1)$**: $P(X \le 1) = P(X=1) = 1/6$
• **$F(2)$**: $P(X \le 2) = P(X=1) + P(X=2) = 1/6 + 1/6 = 2/6$
• **$F(2.5)$**: $P(X \le 2.5) = P(X=1) + P(X=2) = 2/6$
    ◦ *(This is a key insight! The value doesn't change until we hit the next actual outcome.)*
• **$F(3)$**: $P(X \le 3) = P(X=1) + P(X=2) + P(X=3) = 3/6$
• **$F(6)$**: $P(X \le 6) = 1/6 + 1/6 + 1/6 + 1/6 + 1/6 + 1/6 = 1$
• **$F(100)$**: $P(X \le 100) = 1$ (The probability is 100% that the die roll is $\le 100$)

**CMF For Continuous Variables (like Exponential, Normal)**

For a continuous variable, we can't "sum" individual points (since their probability is zero). So, the CDF is an **integral** (an area).
To find $F(x)$, you find the total area under the PDF curve from the very beginning ( $-\infty$ ) all the way up to $x$.

$F(x) = \int_{-\infty}^{x} f(t) dt$
***You've already been using this!***
• **Exponential Example:** We said the formula for "probability *before* time $x$" (eg. probability of getting another request in next 5 seconds) was $P(X \le x) = 1 - e^{-\lambda x}$.
    ◦ That's it! That *is* the CDF. 

> $F(x) = 1 - e^{-\lambda x}$.
> 

It's the *result* of solving that integral for the exponential PDF.
• **Normal Distribution Example:** When we used the Z-table:
    ◦ We had $z = 1.5$.
    ◦ We looked it up and found the value **0.9332**.
    ◦ This value was the *total area to the left* of 1.5.
    ◦ What we *really* found was the CDF: $F(1.5) = P(Z \le 1.5) = 0.9332$.
    ◦ The Z-table is just a giant lookup table for the **C**umulative **D**istribution **F**unction of the Standard Normal Distribution.
The graph of a continuous CDF is a **smooth, S-shaped, increasing curve**.

![](https://i.ibb.co/DgLYHPMz/image.png)

**Key Properties of ALL CDFs**

1. **Starts at 0, Ends at 1:** The function $F(x)$ is always between 0 and 1.
    ◦ $F(-\infty) = 0$ (The probability of getting a number $\le$ negative infinity is 0).
    ◦ $F(+\infty) = 1$ (The probability of getting a number $\le$ positive infinity is 1).
2. **It Never Decreases:** A CDF can only go up or stay flat. It can never go down (because you're only ever *adding* more probability as you move to the right).

**The Most Powerful Use of the CDF**

This is the best part. Once you have the CDF, $F(x)$, you can find the probability of *any range* just by subtracting:**$P(a < X \le b) = F(b) - F(a)$**
Example: "What's the probability of an IQ between 90 ($a$) and 110 ($b$)?
You would find:
1. $F(110)$ (the total probability of being $\le 110$)
2. $F(90)$ (the total probability of being $\le 90$)
3. ...and just subtract: $P = F(110) - F(90)$
This single formula works for *both* discrete and continuous distributions.

---

### Expected Value

The **Expected Value** is the formal, mathematical name for the **average outcome of an experiment if you ran it an infinite number of times.**
We've been using the word "average" or "mean ($\mu$)" a lot. Expected Value is the *calculation* behind that. It's the most important number to describe a distribution's "center" or "location."

The Notation:
It's written as $E[X]$.
• $X$ is your random variable (e.g., the outcome of a die roll).
• $E[X]$ is "the expected value of X.”

**The Core Idea: A Weighted Average**

The key insight is that the expected value is not just a simple average of the outcomes. It's a weighted average, where each outcome is weighted by its probability.

A simple average would just be $(1 + 2 + 3 + 4 + 5 + 6) / 6 = 3.5$.
The expected value calculation *proves* why this is true.

1. **Expected value For Discrete Variables (like a Die Roll)**

You calculate $E[X]$ by taking each possible outcome ($x$), multiplying it by its probability ($P(X=x)$), and then summing all those products together.

> Formula:
$E[X] = \sum_{x} x \cdot P(X=x)$
> 

**Example 1:** A Fair 6-Sided Die

• $E[X] = (1 \cdot P(X=1)) + (2 \cdot P(X=2)) + ... + (6 \cdot P(X=6))$
• $E[X] = (1 \cdot \frac{1}{6}) + (2 \cdot \frac{1}{6}) + (3 \cdot \frac{1}{6}) + (4 \cdot \frac{1}{6}) + (5 \cdot \frac{1}{6}) + (6 \cdot \frac{1}{6})$
• $E[X] = \frac{1 + 2 + 3 + 4 + 5 + 6}{6} = \frac{21}{6} = 3.5$

So If you roll this die thousands of times, the average of all your rolls will get closer and closer to 3.5. (Even though 3.5 isn't a possible outcome!)

***Example 2:** A Casino Game (The real power of E[X]*

You pay $5 to play.

You roll a fair die.

if you roll a 1-5, you win nothing ($0).

If you roll a 6, you win $20.

What is the *expected value of your winnings*?
• Outcomes ($x$): $0 or $20
• Probabilities: $P(X=0) = 5/6$, $P(X=20) = 1/6$
• $E[X] = (0 \cdot P(X=0)) + (20 \cdot P(X=20))$
• $E[X] = (0 \cdot \frac{5}{6}) + (20 \cdot \frac{1}{6})$
• $E[X] = 0 + \frac{20}{6} \approx \$3.33$

**Interpretation:** On average, you *win* $3.33 every time you play. But you *paid* $5 to play.
• **Your Net E[X] on each throw :** $3.33 - $5.00 = -$1.67
• This means every time you play this game, you are *expected to lose* $1.67. This is how casinos make money.

**2. Expected Value For Continuous Variables (like Height)**
We can't use a sum (since there are infinite values and any value has probability of 0), so we use its continuous equivalent: the **integral**. You "sum" each value ($x$) multiplied by its *density* ($f(x)$) over the entire range.
The idea is identical, but we replace the "sum" ($\sum$) with an "integral" ($\int$) and the PMF ($P(X=x)$) with the PDF ($f(x)$).

> Formula:
$E[X] = \int_{-\infty}^{\infty} x \cdot f(x) dx$
> 

Example: An Exponential Distribution
(Used to model waiting times, $f(x) = \lambda e^{-\lambda x}$)
If you solve the integral $E[X] = \int_{0}^{\infty} x \cdot \lambda e^{-\lambda x} dx$, you find that the average waiting time is $E[X] = \mathbf{1/\lambda}$.
• **This is a key CS insight:** If a server gets **10 requests/sec** (so $\lambda=10$), the *average time between requests* is $E[T] = 1/10 = \mathbf{0.1}$ seconds.

**Why Expected Value is Critical in Computer Science**

Expected Value is the single most important tool for analyzing the performance of algorithms and systems.**Key Idea:** It gives us the **Average-Case Analysis**.
• **Randomized Algorithms:** What is the *average-case running time* of Quicksort? You can't give a single number, as it depends on the random pivots. But you *can* calculate its **expected running time**, which turns out to be $E[\text{Time}] = O(n \log n)$.
• **Distributed Systems & Networking:** What is the *average load* on a server? What is the *average queue length*? What is the *expected throughput* of a network? These are all calculated using $E[X]$.

---

Expected Value ($E[X]$) is the "average" outcome. The natural next question is, "How far from the average do the outcomes tend to be?"

### Variance ($Var(X)$)

**Variance** is the formal, mathematical way to measure **how spread out a distribution is**.
An "Expected Value" ($E[X]$) tells you the average, but it doesn't tell you anything about the risk or uncertainty.
**Example:** Imagine two different investment options.
• **Investment A (Low Variance):** You are *expected* to make $50. The outcomes are always between $45 and $55. It's a very "tight" and predictable distribution.
• **Investment B (High Variance):** You are also *expected* to make $50. But the outcomes can be anywhere from -$1000 to +$1100. It's an extremely "wide" and unpredictable distribution.
Both have the same $E[X] = 50$, but their **Variance** is completely different. Variance is the number that quantifies this "spread."

**How to Calculate "Spread" or Variance**

1. The "center" is the mean, $\mu = E[X]$.
2. For any single outcome $x$, its "distance" (or "deviation") from the center is $(x - \mu)$.
3. We want to find the *average* of all these distances. But if we just take the average, all the negative distances (outcomes below the mean) will cancel out all the positive distances (outcomes above the mean). Our answer would just be 0, which is useless.
4. **The Solution:** We **square** the distances first! This makes every distance positive: $(x - \mu)^2$
5. Now, we take the "expected value" (the weighted average) of all these **squared distances**.
$E[ (X - \mu)^2 ]$
****
Variance is **"the expected value of the squared deviation from the mean."**
• **Notation:** $Var(X)$ or (even more famous) **$\sigma^2$** ("sigma-squared").

> $Var(X) = E[ (X - \mu)^2 ]$
> 

where $\mu = E[X]$
This single formula works for all distribution types.
• **For Discrete:** $Var(X) = \sum_{x} (x - \mu)^2 \cdot P(X=x)$
• **For Continuous:** $Var(X) = \int_{-\infty}^{\infty} (x - \mu)^2 \cdot f(x) dx$

**Connecting Variance to Standard Deviation  
$(\sigma)$**

"$\sigma^2$? That sounds familiar!"
We've been using $\sigma$ (Standard Deviation) this whole time.
The variance we just calculated is in "squared units" (e.g., "squared dollars" or "squared IQ points"). That's not very intuitive to talk about.
So, to get the "spread" back into its *original units*, we just take the **square root** of the variance.
That is the **Standard Deviation ($\sigma$)**.

**$\sigma = \sqrt{Var(X)}$**
The **Standard Deviation ($\sigma$)** that we used in the Normal Distribution is simply the square root of the Variance.

**The "Computational Formula" for Variance (The Better Way to Calculate It)**

The "definition" formula $Var(X) = E[ (X - \mu)^2 ]$ is great for theory but terrible for computation. You'd have to pass through your data *twice*: once to find the mean ($\mu$), and a second time to find the squared differences.
The **computational formula** (also called the "shortcut") is much better. You can calculate $E[X^2]$ and $E[X]$ at the same time in a single pass.

we know that mean is $\mu = E[X]$ so replace that in previous formula and we get this: 

> **$Var(X) = E[X^2] - (E[X])^2$**
> 

**In words:** "The variance is the **Expected Value of X-Squared** minus the **Square of the Expected Value of X**."
• **$E[X^2]$** is the "Expected Value of X-Squared."
    ◦ For discrete: $\sum x^2 \cdot P(X=x)$
    ◦ For continuous: $\int x^2 \cdot f(x) dx$
• **$(E[X])^2$** is just the mean ($\mu$) squared.

note: **A Very Special Property:** Look at the **Poisson** distribution. Its **Expected Value is $\lambda$** and its **Variance is *also* $\lambda$**. This is a unique and defining feature of the Poisson distribution.

---

### Conditional Expectation **$E[X|Y]$**

**Conditional Expectation** is a bit abstract at first, but it's one of the most powerful tools in statistics, especially for machine learning and data science.
Let's build it up.
• **Expected Value $E[Y]$** is your *best guess* for the value of $Y$ when you have *no information*.
• **Conditional Expectation $E[Y | X=x]$** is your *new, updated best guess* for $Y$ *after you learn a piece of new information* (that $X$ is equal to $x$).

> **$E[X|Y]$ is spelled as ‘expected value of X given Y**
> 

**A Simple Analogy**

• **$E[\text{Height}]$**: What's the expected (average) height of a random adult? Maybe 5' 9" (175 cm).
• **$E[\text{Height} | \text{Person is an NBA player}]$**: What's the expected height *given* you know the person is an NBA player? Maybe 6' 6" (198 cm).
The "condition" (knowing they are an NBA player) *dramatically* changes your expectation.

**Why Conditional Expectation Matters in CS**
This concept is used *everywhere* in system analysis and machine learning. We rarely care about the single, overall average; we care about the average in specific scenarios.
**Example: Cache Performance**
• Let $T$ be the time to retrieve a piece of data from db.
• Let $E[T]$ be the *overall* average retrieval time. This number is a blend of fast cache hits and slow disk lookups, so it's not very descriptive.
It's far more useful to use conditional expectation:
• **$E[T | \text{Cache Hit}]$**: The expected time *given* the data is in the cache. (e.g., **5 ns**).
• **$E[T | \text{Cache Miss}]$**: The expected time *given* the data is *not* in the cache. (e.g., **10,000,000 ns** or 10 ms).

**The Law of Total Expectation**

This is the most important "trick" that uses conditional expectation. It's a way to calculate the overall $E[X]$ by breaking it down into its conditional parts.**The overall average is the weighted average of the scenario-averages.**
Using our cache example:
$E[T] = E[T | \text{Hit}] \cdot P(\text{Hit}) + E[T | \text{Miss}] \cdot P(\text{Miss})$
If your cache hit rate $P(\text{Hit})$ is 99%, then:
$E[T] = (5 \text{ ns} \cdot 0.99) + (10,000,000 \text{ ns} \cdot 0.01)$
$E[T] = 4.95 \text{ ns} + 100,000 \text{ ns} = 100,004.95 \text{ ns}$

This formula is a key technique for analyzing systems and algorithms. You calculate the expected value for each possible "case" (like a cache hit/miss or an `if`/`else` branch) and then combine them, weighted by the probability of each case.

**The Formal Formulas for Conditional Expectation**

The logic is just like the regular Expected Value, but we swap all the "probabilities" with "conditional probabilities."
***Discrete Case:***
The normal formula is $E[Y] = \sum_y y \cdot P(Y=y)$.

> The conditional formula is:
$E[Y | X=x] = \sum_y y \cdot P(Y=y | X=x)$
> 

***Continuous Case:***
The normal formula is $E[Y] = \int y \cdot f(y) dy$.

> The conditional formula is:
$E[Y | X=x] = \int_{-\infty}^{\infty} y \cdot f_{Y|X}(y|x) dy$
> 

**Another example for LAW of Total Expectation The "Average of Averages" Analogy**

Imagine you want to find the average grade ($Y$) for *all students in a large university*. This is our goal, $E[Y]$.
It's a huge task. But, we have a way to break it down. We can get the data for each department ($X$).

**step1: *The "Inner" Expectation: $E[Y | X]$***

First, we go to each department and find the average grade *just for that department*. This is $E[Y | X=x]$.
• We go to the **Computer Science** department. They have a 50% of the student population. and their average grade ($Y$) is **90**.
$E[Y | X = \text{"CS"}] = 90$
 $P(X = \text{"CS"}) = 0.5$
• We go to the **History** department. They have 30% of the students.  their average grade ($Y$) is **80**.
$E[Y | X = \text{"History"}] = 80$
$P(X = \text{"History"}) = 0.3$
• **Physics** department have 20% of the students. and  average grade ($Y$) is **70**.
$E[Y | X = \text{"Physics"}] = 70$
$P(X = \text{"Physics"}) = 0.2$
This "inner" part, $E[Y | X]$, is *not* a single number. It's a **function** that gives you a different average (90, 80, or 70) depending on which department you look at.

**step2: The "Outer" Expectation: $E[ \dots ]$**

Now we have our list of "department averages" (90, 80, 70). How do we combine them to get the one final average for the *entire* university?
We can't just do $(90 + 80 + 70) / 3 = 80$. That would be wrong, because the departments have different sizes.
Logically, we have to take a **weighted average**, using the *size (probability)* of each department as the weight.
• The CS average of 90 should count for 50% of the final grade.
• The History average of 80 should count for 30%.
• The Physics average of 70 should count for 20%.
**This "weighted average of the inner averages" IS the "outer" expectation.**$E[Y] = (90 \cdot 0.5) + (80 \cdot 0.3) + (70 \cdot 0.2)$

$E[Y] = 45 + 24 + 14$

$E[Y] = 83$

The overall average grade for the entire university ($E[Y]$) is **83**.

The Law of Total Expectation: $E[Y] = E[ E[Y | X] ]$
• $E[Y]$ is the **one final number** we want (the university average, 83).
• $E[Y | X]$ is the **list of "inner" averages** (90, 80, 70) that depend on the department ($X$).
• $E[ \dots ]$ is the **"outer" average**, which tells you to take a *weighted average* of that inner list to get your final answer.
So, the law is just a formal way of saying:

> The overall average ($E[Y]$) is probability-weighted average ($E[...]$) of the individual group averages ($E[Y|X]$)."
> 
> 
> ---
> 

**Central Limit Theorem (CLT)**.

The [Central Limit Theorem (CLT)](https://www.google.com/search?sca_esv=b51b2d73c9f7d5a8&sxsrf=AE3TifPoGN5SbPN7Si8fLxHDH7Nm1pLkBg%3A1762940864584&q=Central+Limit+Theorem+%28CLT%29&sa=X&ved=2ahUKEwjnhfm_quyQAxUmzjgGHW88MW4QxccNegQINRAB&mstk=AUtExfBWRn8KUP29Vm6AHbzrPHGsZxGbys2Yu11mnGnVd2JRgX7AgywFGM81PG3-DGwbzSvoa-t8GhoD0ARckaszU6vweBVoph9akUHJbKukyuCeAsKyK3Py3uBzTrhFoMTFhWo80hbFKpZPqi99ETJn5jF5NcOG8g8jQrEErg9cH8JERbSXXV4I-PS-eU1fBiIRvDGZHULEB6v7B5oLsED3O7TypztuHUPuCOEMsIlh5aZ4IOKKlozzwNRjWEkdEi61sqKh-TI3BAYr9mWVs5Fjm9W2&csui=3) states that the distribution of sample means will be approximately a normal distribution (***a bell curve***) as the sample size gets large enough, regardless of the shape of the original population's distribution

**The Parameters of that Normal Distribution (The "So What?")**
This is the most crucial part for calculations. The CLT doesn't just say "it becomes normal"; it tells us *exactly which* normal distribution.
The new bell curve for the sample means ($\bar{X}$) will have:

> a) The Same Mean:
$E[\bar{X}] = \mu$
> 

 **Meaning:** The average of all the "sample averages" will be the *same* as the true population average. This makes sense; our samples are unbiased.

> b) A Much Smaller Variance (This is the key insight!):
$Var(\bar{X}) = \frac{\sigma^2}{n}$
> 

As $n$ gets bigger, this variance gets *tiny*. This means the sample means are all tightly clustered around the true mean $\mu$.

It's the mathematical way of saying:"Averages are *less variable* (less spread out) than individuals. The 'canceling-out' power of your average is equal to your sample size $n$."

> c) The Standard Error:
$\sigma_{\bar{X}} = \sqrt{Var(\bar{X})} = \frac{\sigma}{\sqrt{n}}$
> 

This is just the standard deviation of our new bell curve. It's the square root of the variance:
This is called the **Standard Error**, and it's the most important number in A/B testing and confidence intervals.

**The Application of the *univariate* CLT (Univariate = 1 variable)**

• **The Problem:** We want to know the *true mean* $\mu$ of a giant data (e.g., "What's the true average response time of our servers?"). We can't possibly test *all* requests.
• **The "Old" Problem:** We don't even know if the original response times are normally distributed! They are probably *exponentially* distributed (as we discussed). We can't use a Z-score... or can we?
• **The CLT Solution:**
    1. We don't care about the original distribution. We just take *one* large sample, say of $n=100$ requests.
    2. We calculate *our* sample mean, $\bar{x}$.
    3. The CLT guarantees that the *sampling distribution* (the imaginary distribution of *all possible* $\bar{X}$'s) is a **Normal Distribution** centered at the true mean $\mu$, with a standard error of $\frac{\sigma}{\sqrt{n}}$.
    4. Because we now have a **Normal Distribution**, we can use Z-scores!
    5. This allows us to take our *one* sample mean $\bar{x}$ and make an inference, like: "We are 95% confident that the *true* server response time $\mu$ is in the interval $\bar{x} \pm 1.96 \cdot (\frac{\sigma}{\sqrt{100}})$."

**The Confidence Interval Formula for Univariate**

It is the formula to *estimate* the true, unknown population mean ($\mu$) using your sample data.
****The Formula to Memorize:

> $\text{C.I.} = \bar{x} \pm z_{\alpha/2} \cdot \left(\frac{\sigma}{\sqrt{n}}\right)$
> 

eg. we used above $\bar{x} \pm 1.96 \cdot (\frac{\sigma}{\sqrt{100}})$.
• **What each part means:**
    ◦ $\bar{x}$: This is your **Sample Mean** (the average you calculated from your one sample).
    ◦ $z_{\alpha/2}$: This is your **Critical Value** (the "magic number" from step 2, like 1.96 for 95% confidence).
    ◦ $\sigma$: This is the **Population Standard Deviation**.
    ◦ $n$: This is your **Sample Size**.
    ◦ $\left(\frac{\sigma}{\sqrt{n}}\right)$: This is the **Standard Error** (from the CLT).
The second half of the formula, $z_{\alpha/2} \cdot \left(\frac{\sigma}{\sqrt{n}}\right)$, is called the **Margin of Error**.
What it means:
→ You are "95% confident" that the true population mean $\mu$ lives somewhere inside the interval you just calculated.

→ or we can say So, if we *pick up our dart* ($\bar{x}$) and build a net of the **exact same size** ($\pm 1.96 \cdot \frac{\sigma}{\sqrt{n}}$) *around it*, there is a 95% chance that we "captured" the true post $\mu$ inside our net. 

**where does this 1.96 comes from ?**

The "Magic Numbers" (Z-scores)
It comes from the "[68-95-99.7](https://www.notion.so/MT-CSE-18-11-Mathematical-Foundations-of-Computer-Science-2a32a3410ddc8069a705d7381da40fee?pvs=21)" rule is just an approximation. 
The 95% value of **1.96** comes from this logic:
• We want the middle 95% (0.95) of the data. This leaves 5% (0.05) for the "tails." Symmetry means we put 2.5 (0.025) in the left tail and 2.5% (0.025) in the right tail.
• The Z-score that leaves 0.025 in the right tail (and 0.975 to its left) is **1.96**. from the Z-table
**Memorize these Z-scores (they are called "critical values"):**
• For **90%** confidence: $z = 1.645$
• For **95%** confidence: $z = 1.96$
• For **99%** confidence: $z = 2.576$

### **Multivariate Central Limit Theorm (CLT)**

**The Setup: Univariate CLT vs. Multivariate CLT**
• **Univariate:** We measure *one* thing.
    ◦ e.g., We sample 100 students and measure their **Height**.
    ◦ Our data is a list of numbers: $[170, 165, 180, ...]$
• **Multivariate:** We measure *two or more* things on the *same* student.
    ◦ e.g., We sample 100 students and measure their **[Height, Weight]**.
    ◦ Our data is a list of **vectors**: $[[170, 70], [165, 65], [180, 80], ...]$

> *A **vector is an ordered list of numbers that represent multiple measurements of a single item,*** It has **multiple values**. Those values are **connected** because they describe **one entity**. and order matters. A vector is simply a **point in space.** With coordinates that specify its position.
> 

**1. The "Mean" is now a "Mean Vector"**
• Univariate**:** The population mean is one number: $\mu$    e.g., $\mu_{\text{height}} = 175\text{cm}$
• Multivariate**:** The population mean is a **vector ($\boldsymbol{\mu}$)** of the means for each variable.
    ◦ e.g., $\boldsymbol{\mu} = \begin{bmatrix} \mu_{\text{height}} \\ \mu_{\text{weight}} \end{bmatrix} = \begin{bmatrix} 175 \\ 75 \end{bmatrix}$

**2. The "Variance" is now a "Covariance Matrix"**
• **Univariate:** The spread is one number, the variance: $\sigma^2$
    ◦ e.g., $\sigma_{\text{height}}^2 = 25$ (This tells us the spread of *heights*).
• **Multivariate:** The spread is a **Covariance Matrix ($\boldsymbol{\Sigma}$)**. This matrix tells us *two* things:
    1. The spread of *each* variable (on the diagonal).
    2. How the variables *move together* (on the off-diagonal) and also these variables are connected and effect the variance or spread.

> For our [Height, Weight] example, the 2x2 Covariance Matrix $\boldsymbol{\Sigma}$ would be:
$\boldsymbol{\Sigma} = \begin{bmatrix} Var(\text{Height}) & Cov(\text{Height, Weight}) \\ Cov(\text{Weight, Height}) & Var(\text{Weight}) \end{bmatrix}$
> 

• **$Var(\text{Height})$:** The spread of heights (e.g., 25).
• **$Var(\text{Weight})$:** The spread of weights (e.g., 100).
• **$Cov(\text{Height, Weight})$:** This is new. The **Covariance**. It's a positive number (e.g., 40) because as Height increases, Weight tends to increase. This "link" is now formally part of our math.

**The Multivariate Central Limit Theorem (MCLT)**
Now we just plug our new vector and matrix into the CLT.
• Univariate CLT: The sample mean $\bar{X}$ becomes normal: 

> $N(\mu, \frac{\sigma^2}{n})$
> 

This means that For one variable: the sample mean $\bar{X}$ becomes normal (bell-shaped) as sample size increases. and 

- Centered at true mean $μ$
- Spread shrinks as n increases $(σ²/n)$

For Multivariate CLT: The sample mean vector $\boldsymbol{\bar{X}}$ becomes "multivariate normal":

> $N_k(\boldsymbol{\mu}, \frac{\boldsymbol{\Sigma}}{n})$
> 

where 

- $\boldsymbol{\bar{X}}$ = sample mean vector
- $\mu$ = true mean vector
- $\Sigma$ = true covariance matrix
- divided by n because means have less variability
- $k$ is the number of variables, e.g., $k=2$ height and width)
This just means:
1. The mean of our sample mean vectors ($\boldsymbol{\bar{X}}$) is the true mean vector ($\boldsymbol{\mu}$).
2. The covariance matrix of our sample mean vectors is the true covariance matrix *shrunk by $n$* ($\frac{\boldsymbol{\Sigma}}{n}$).

When we write:

$N_k(\boldsymbol{\mu}, \Sigma)$

it means: A k-dimensional bell-shaped distribution with center at mean vector  $μ$ and shape defined by covariance matrix $Σ$.

**4. The Application: The "Confidence Region"**

This is the direct answer to your question.
• **Univariate Application:** We used the CLT to build a 95% **Confidence *Interval***.
    ◦ $\bar{x} \pm 1.96 \cdot (\frac{\sigma}{\sqrt{n}})$
    ◦ This creates a **line segment** [A, B] on a 1D number line. We are 95% confident the true $\mu$ is *on this line*.
• **Multivariate Application:** We use the MCLT to build a 95% **Confidence *Region***.
    ◦ For our 2D [Height, Weight] problem, our region is **not a square**.
    ◦ Because the variables are *correlated* (e.g., $Cov(\text{Height, Weight}) > 0$), the region is a **tilted ellipse**.
. The points of the scatter plot are clustered around this ellipse.]

Covariance tells you:

> Covariance tells you: How two variables move together.`Covariance > 0` means, When one variable increases, the other also tends to increase. Or equivalently: When one decreases, the other also tends to decrease.
> 

**[imp] Why is Confidence Region an ellipse?**
A square would treat height and weight as independent. The ellipse "tilts" along the same direction as the covariance. It correctly shows that a person who is "above average height" is *also* likely to be "above average weight."

---

### Probabilistic Inequalities

The Central Limit Theorem tells you what happens with a *large* sample ($n \ge 30$), but what if your sample is small, or you don't even know the *type* of distribution you're dealing with?

That's where these inequalities come in. They give you a **"bound"** or a **"worst-case guarantee"** on a probability, using only the mean or variance.

**1. Markov's Inequality**

This is the most basic inequality. It gives you a *loose* upper bound ,this on the probability that a non-negative random variable $X$ is much larger than its average.

It *only* works for non-negative random variables (e.g., $X$ = time, distance, number of requests. It *cannot* be $X$ = profit/loss).
• **What you need to know:** Only the expected value, $E[X] = \mu$. (And $X$ must be non-negative).
• **The "Common Sense" Idea:** If the average salary in a room is $50,000, it's impossible for *more than 10%* of the people to earn $500,000 or more (because if 11% did, their salaries *alone* would bust the average).

> The Formula: For any $a > 0$:
$P(X \ge a) \le \frac{E[X]}{a}$
> 
> - here E[X] is the average mean
> - a is the value that we want to find the probability for

**example 1:** You have a web server with an *average* queue length of 20 requests ($E[X]=20$). What's the *worst case* probability that the queue length hits 100?
    ◦ $P(X \ge 100) \le \frac{20}{100} = 0.2$
    ◦ You can guarantee (with no other information!) that there's at most a 20% chance of the queue being 100 or more.

**example 2**: The average grade on a final exam ($E[X]$) is **20** (out of 100).**Question:** What's the absolute maximum probability that a student got a grade of **80** or more ($a=80$)?

solution: $P(X \ge 80) \le \frac{E[X]}{a} = \frac{20}{80} = 0.25$

**Conclusion:** At most, 25% of the class could have scored an 80 or higher. If it were more than 25%, the average *must* be higher than 20.

**Limitation:** This is a very "loose" bound. In reality, the probability is probably *much* lower than 25%, but Markov *guarantees* it's not higher.

**2. Chebyshev's Inequality (The "Mean-and-Variance" Tool)**

This one is *much* more famous and useful. It uses *both* the **Mean ($\mu$)** and the **Variance ($\sigma^2$)**.
• **Condition:** Works for *any* distribution, as long as the mean and variance are defined.
• **The "Story":** "If I know the mean and the spread, what's the worst-case probability of a value falling 'far away' from the mean?"
• **The Formula:** (There are two identical ways to write it)

> ***Form 1*** (in terms of distance $k$): For any $k > 0$:
$P(|X - \mu| \ge k) \le \frac{\sigma^2}{k^2}$
> 

(This says: "The probability of being $k$ units away from the mean is at most $σ²/k²$.")

| Symbol | Meaning |
| --- | --- |
| $X$ | A random variable (your data) |
| $\mu$ | The mean (average) of (X) |
| $\sigma^2$ | The variance of (X) |
| $\sigma$ | Standard deviation (square root of variance) |
| $k$ | A **distance** measured in raw units of X |
| $|X - \mu| \ge k$ | means X is away from mean u by k steps |

**Why this formula is sometimes inconvenient?**

Because k is in raw units, not standard deviations. For example, you might not know what “20,000 units” really means relative to the variability. So we rewrite it in terms of standard deviations in form 2

***Form 2*** (in terms of standard deviations $k$): 

> For any $k > 0$:
$P(|X - \mu| \ge k\sigma) \le \frac{1}{k^2}$
> 

This says: "The probability of a random variable X being $k$ standard deviations ($\sigma$)  i,e ($k$$\sigma$) away from the mean $\mu$ is at most. $1/(k^2)$
This second form is the powerful one.

| Symbol | Meaning |
| --- | --- |
| ($k$) | Number of **standard deviations** |
| ($k\sigma$) | A distance equal to “k standard deviations” |
| $X - \mu$ | gives the distance of X being away from mean $\mu$ |
| RHS = ($1/k^2$) | Bound on probability |

**example**: what's the probability of being 2 or more standard deviations away ($k=2$)

If you know your distribution is NORMAL (our old rule):
• The "95%" rule tells you that 95% is *inside* 2 S.D.
• This means the probability of being *outside* is **exactly 5%**.

**But If you know *nothing* about the distribution (we use the Chebyshev's rule):**
• We use the formula: $P(|X - \mu| \ge 2\sigma) \le \frac{1}{k^2}$
• We plug in $k=2$: $... \le \frac{1}{2^2} = \frac{1}{4} = 0.25$
• Conclusion**:** The probability of being *outside* 2 S.D. is **at most 25%**.

| **Rule** | **Condition** | **Probability of being > 2 S.D. away** |
| --- | --- | --- |
| **Normal Distribution** | Must be a **bell-shaped** (normal) distribution | **Exactly 5%** (tight, precise) |
| **Chebyshev’s Inequality** | **Any** distribution (no shape assumptions) | **At most 25%** (loose, worst-case bound) |

Application in CS:When you're designing a system, you often don't know the true distribution of (for example) network latency. You can't assume it's Normal. But you can measure its mean and variance. Chebyshev allows you to use that $\mu$ and $\sigma^2$ to create a guaranteed bound for your "Service Level Agreement" (SLA).

**Example:**
Let's say the average runtime of your algorithm is 50 ms ($\mu=50$), and the standard deviation is 5 ms ($\sigma=5$). What's the probability the runtime is more than 3 standard deviations away (i.e., $< 35$ ms or $> 65$ ms)?
• Here, $k=3$.
• $P(|X - 50| \ge 3 \cdot 5) \le \frac{1}{3^2} = \frac{1}{9}$
• Result**:** You can guarantee that at least $1 - 1/9 = 8/9$ (or $\approx 89\%$) of your runtimes will *always* fall between 35 ms and 65 ms, regardless of what the distribution looks like.

---

### **Markov Chains**

**1. The Core Idea: What is a Markov Chain?**
A Markov Chain is a mathematical model for a **system that moves between different "states."**
It's a "stochastic process," meaning it's random, but its randomness follows specific rules.
**The "Story":**

- Imagine a system that can be in one of several states. (e.g., A server is `[Up]`, `[Down]`, or `[Busy]`).
- At each "tick" of time (e.g., every second), the system can *transition* to another state or *stay* in its current state.
• There's a *probability* associated with each transition. (e.g., "If the server is `[Up]`, there's a 1% chance it goes `[Down]`, a 20% chance it becomes `[Busy]`, and a 79% chance it just stays `[Up]`).
- **Examples:**
    - Weather: The states are `[Sunny]`, `[Cloudy]`, `[Rainy]`.
    - Web User: The states are `[Homepage]`, `[About Page]`, `[Contact Page]`.
    - NLP: The states are words. What's the probability the *next* word is "cheese" *given* the current word is "macaroni"?
    

**2. The "Markov Property" (The Key to Everything)**

This is the most important rule, and it should sound familiar to you. The Markov Property is **Memorylessness**.**"The future depends *only* on the *present* state, not the past."**
means:  To predict the weather for tomorrow, a Markov Chain *only* cares about what the weather is *today*. It doesn't care that it was sunny for the past 30 days. All the information about the past is "baked into" the present state.

**3. The Components**
To build a Markov Chain, you need two things:

**a) A Set of States ($S$)**

- A finite list of all possible states. e.g., $S = \{\text{State 1, State 2}\}$

**b) A Transition Matrix ($P$)**

This is the "engine" of the chain. It's a matrix that holds all the "transition probabilities."

$P_{ij}$ = The probability of moving from **State *i*** to **State *j*** in one step.

**Example: A Simple 2-State Weather Model**

**States ($S$):** $S = \{1: \text{Sunny}, 2: \text{Rainy}\}$

**Transition Rules:**

- If it's Sunny (State 1) today, there's a 90% chance it's Sunny (1) tomorrow and a 10% chance it's Rainy (2).
- If it's Rainy (State 2) today, there's a 50% chance it's Sunny (1) tomorrow and a 50% chance it stays Rainy (2).
- Transition Matrix ($P$):
We build a matrix where row i represents today's state and column j represents tomorrow's state.

$P = \begin{matrix} & \text{Sunny (j=1)} & \text{Rainy (j=2)} \\ \text{Sunny (i=1)} & 0.9 & 0.1 \\ \text{Rainy (i=2)} & 0.5 & 0.5 \end{matrix}$

Notice: **Each row must sum to 1.** (From any given state, *something* has to happen).

This matrix and set of states *is* the Markov Chain.

**4. The Application: Predicting Future States**

How do we find the probability of the weather in 3 days?

Let's say our **Initial State** is a vector, $v_0$. It's Day 0, and it's `100%` Sunny.

$v_0 = \begin{bmatrix} 1 & 0 \end{bmatrix}$ (100% in State 1, 0% in State 2)

**After 1 Day ($v_1$):** We just multiply our vector by the matrix $P$.

$v_1 = v_0 \cdot P = \begin{bmatrix} 1 & 0 \end{bmatrix} \begin{bmatrix} 0.9 & 0.1 \\ 0.5 & 0.5 \end{bmatrix} = \begin{bmatrix} 0.9 & 0.1 \end{bmatrix}$
Result:  90% chance of Sun, 10% chance of Rain. (This matches our rules).

**After 2 Days ($v_2$):** We multiply *again*.

$v_2 = v_1 \cdot P = \begin{bmatrix} 0.9 & 0.1 \end{bmatrix} \begin{bmatrix} 0.9 & 0.1 \\ 0.5 & 0.5 \end{bmatrix} = \begin{bmatrix} (0.9\cdot0.9 + 0.1\cdot0.5) & (0.9\cdot0.1 + 0.1\cdot0.5) \end{bmatrix} = \begin{bmatrix} 0.86 & 0.14 \end{bmatrix}$

**Result:** 86% chance of Sun, 14% chance of Rain.

**After *n* Days ($v_n$):** This is the magic. We just use matrix exponentiation.

**$v_n = v_0 \cdot P^n$**

**5. The "Big Goal of markov chain": The Stationary Distribution ($\pi$)**

So what happens after a long time like 1000 days ?

After many transitions (like 100 or 1000 days), the system “forgets” where it started. It settles into a **steady long-run pattern**. That long-run pattern is the **stationary distribution**. It is the long-run probability of being in each state.
It does not change even if you apply the transition matrix again.

Mathematically, we write:

> $π=πP$
> 

Which means: “If the system is already at equilibrium, applying the transition rules keeps it in equilibrium.”

**Question:** If this weather model runs for 1,000 days, what's the probability it's Sunny?

**Answer:** We are looking for the **Stationary Distribution ($\pi$)**. This is a special probability vector that **does not change** when you multiply it by $P$.

> **The Formula:** $\pi = \pi \cdot P$
> 

**In English:** "The probability of being in a state *tomorrow* ($\pi \cdot P$) is the *exact same* as the

probability of being in a state *today* ($\pi$)." This is the "steady state" or "equilibrium."

For our weather example, if you solve $\pi = \pi P$

you find: $\pi = \begin{bmatrix} 0.833 & 0.167 \end{bmatrix}$

**Interpretation:** In the long run, it will be Sunny **83.3%** of the time and Rainy **16.7%** of the time, *regardless* of whether you started on a Sunny or Rainy day.

**Proof: how did we get this $\pi = \begin{bmatrix} 0.833 & 0.167 \end{bmatrix}$ ?**

**Stationary Distribution Calculation (Short Version)**

Given transition matrix:

$P = \begin{bmatrix} 0.9 & 0.1 \\ 0.5 & 0.5 \end{bmatrix}$

Let the stationary distribution be: $\pi = [\pi_S, \pi_R]$

The stationary condition: $\pi = \pi P$

ignore the 2nd equation coz its redundant

gives the equation: $\pi_S = 0.9\pi_S + 0.5\pi_R$

Solve: $\begin{aligned} \pi_S - 0.9\pi_S &= 0.5\pi_R \\ 0.1\pi_S &= 0.5\pi_R \\ \pi_S &= 5\pi_R \end{aligned}$

Use normalization:

$\begin{aligned} \pi_S + \pi_R &= 1 \\ 5\pi_R + \pi_R &= 1 \\ 6\pi_R = 1 &\Rightarrow \pi_R = \frac{1}{6} \\ \pi_S = 5 \cdot \frac{1}{6} &= \frac{5}{6} \end{aligned}$

Final stationary distribution:

$\pi = \begin{bmatrix} 0.833 \\ 0.167 \end{bmatrix}$

**6. CS Application of Marcov chain**

1. **Google's PageRank Algorithm:** The *entire web* is a massive Markov Chain.
    - **States:** Web pages.
    - **Transitions:** Links. (A 10% chance you click a link, a 90% chance you stay).
    - The **Stationary Distribution ($\pi$)** of this chain tells you the long-run probability of a user "landing" on a page
    - This probability *is* the PageRank. **PageRank = Stationary Distribution.**
2. **Queuing Theory:** (Like your Poisson/Exponential). The number of people in a queue `[0, 1, 2, 3...]` is a state. The Markov Chain models the flow of customers.
3. **NLP (n-gram models):** What's the probability the next word is "Chain" given the current state is "Markov"?
4. **Reinforcement Learning:** (Markov Decision Processes are an advanced version of this, forming the basis of AI in games and robotics).

---

next: unit 2