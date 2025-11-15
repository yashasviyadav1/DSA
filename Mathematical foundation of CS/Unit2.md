![unit 2 topics](https://i.ibb.co/mVyHprK8/image.png)

### 1. Random Samples

A **random sample** is a subset of data collected from a larger group (called a **population**) in such a way that every member of the population has an equal chance of being included.

- **Population:** The *entire* group you care about (e.g., **all** server requests in a day, **all** users of your app).
- **Sample:** The small, manageable subset of data you *actually collect* (e.g., 1000 server requests, 500 users).

We use samples because it's almost always impossible or too expensive to get data from the entire population.

### **2. Parameters vs. Statistics/Estimate**

This is a critical definition:
**Parameter:** A number that describes the **population**. It's the "true" value, but it's usually **unknown**.

*Example:* The *true* average latency of **all** server requests ($\mu$) or the *true* failure rate of **all** hard drives ($p$).
• **Statistic/Estimate:** A number you calculate from your **sample**. It's a "best guess" or an **estimate** of the population parameter.
    ◦ *Example:* The *sample average* latency from your 1000 requests ($\bar{x}$) or the *sample failure rate* from your 50 tested drives ($\hat{p}$).
The whole goal of Unit 2 is to use a **statistic** (known) to make an intelligent guess about a **parameter** (unknown). The statistic $\bar{x}$ is an **estimator** for the parameter $\mu$.

**Estimator:** This is the *formula* or *rule* you use to guess the parameter. The sample mean ($\bar{x}$) is an estimator.

**Estimate:** This is the *actual number* you get after plugging your data into the estimator. (e.g., $\bar{x} = 120.5$ ms).

 ****

### **3. Sampling Distributions of Estimators**

Imagine we want to know the *true* average latency ($\mu$) of our server.
1. **You** take a sample of 100 requests and calculate the average. You get $\bar{x}_1 = 120.5$ ms.
2. **I** take a *different* sample of 100 requests. My average is $\bar{x}_2 = 118.7$ ms.
3. We do this 10,000 more times. We get 10,000 different sample averages: $\{\bar{x}_1, \bar{x}2, \dots, \bar{x}{10000}\}$
**Plot:** If you plot a histogram of all 10,000 of these sample means, you get a new distribution.
**This new distribution is the "Sampling Distribution of the Estimator $\bar{x}$".**
A **sampling distribution** is the probability distribution (the histogram) of all these *sample statistics*. It's not the distribution of the original data; it's the distribution of the *averages* you get from sampling.

The **CLT (Central Limit Theorm)** 

tells us *exactly* what this sampling distribution (of the sample mean $\bar{x}$) will look like, without us having to draw 10,000 samples:
1. **Shape:** It will be a **Normal Distribution** (a bell curve), even if the original population *wasn't* normal.
2. **Center:** The mean of this bell curve will be the *true population mean* $\mu$. (This is great! It means our estimator is "unbiased" and centered on the right target).
3. **Spread:** The standard deviation of this bell curve will be $\frac{\sigma}{\sqrt{n}}$, where $\sigma$ is the original population's standard deviation and $n$ is our sample size.
This third point is crucial. It gives us a way to measure the *precision* of our estimator. This spread ($\frac{\sigma}{\sqrt{n}}$) has a special name: the **Standard Error**.

**Standard Error (SE)**
• The **Standard Error** is the standard deviation of a sampling distribution.
• It tells you, on average, how far any given sample estimate ($\bar{x}$) is likely to be from the true population parameter ($\mu$).
• Look at the formula: $\frac{\sigma}{\sqrt{n}}$. As your sample size $n$ gets **bigger**, the denominator gets bigger, so the Standard Error gets **smaller**.
• This makes perfect sense: A **larger sample** gives you a **more precise estimate** (less spread, a narrower bell curve), so you can be more confident that your $\bar{x}$ is very close to the true $\mu$.

### Method of Moments

This is the first of two major techniques you'll learn for estimating population parameters. The Method of Moments is the older, more intuitive of the two.

**The Core Idea**

The logic behind MoM is incredibly simple:

> "A sample's properties should look like the population's properties."
> 

Specifically, the **moments** of the *sample* (which you can calculate from your data) should be set equal to the corresponding **moments** of the *population* (which are formulas with the unknown parameters).

**What's a "Moment"?**
"Moment" is just a mathematical term for a specific measure of a distribution's shape.
• **The 1st moment** is the **Mean** ($E[X]$). The "Average”
• **The 2nd moment** is $E[X^2]$ i.e  "Average of the Squares” (which we use to find the variance).
• **The k-th sample moment** is calculated as $m_k = \frac{1}{n} \sum_{i=1}^{n} x_i^k$. (The 1st sample moment $m_1$ is just the sample mean $\bar{x}$).

**The 4-Step "How-To" for MoM**
Here’s the recipe you follow:
1. **Population Moment:** Write down the formula for the population moment(s) in terms of the unknown parameter(s). (e.g., $\lambda$, $\mu$, $\sigma^2$).
2. **Sample Moment:** Calculate the equivalent sample moment(s) from your data.
3. **Equate:** Set the population formula (Step 1) equal to the sample calculation (Step 2).
4. **Solve:** Solve the resulting equation(s) for the unknown parameter(s).

**A Clear Example: Estimating $\lambda$ for an Exponential Distribution**
Let's say you have a bunch of data (e.g., waiting times) $x_1, x_2, ..., x_n$ and you believe it comes from an **Exponential distribution**. We need to estimate the unknown parameter, the rate $\lambda$.
We only have one parameter, so we only need to use the 1st moment.
1. Population Moment (1st): From Unit 1, we know the mean (1st moment) of an Exponential distribution is:
$E[X] = \frac{1}{\lambda}$
2. Sample Moment (1st): We calculate the sample mean from our data:
$\bar{x} = \frac{1}{n} \sum_{i=1}^{n} x_i$
3. Equate: Now, we just set them equal to each other:
$E[X] = \bar{x}$

$\frac{1}{\lambda} = \bar{x}$
4. Solve: We solve for our parameter $\lambda$:
$\hat{\lambda} = \frac{1}{\bar{x}}$
(We put a "hat" on $\lambda$ to show it's our *estimate*, not the true, unknown value).
And that's it! If your average sample waiting time ($\bar{x}$) was 5 seconds, your MoM estimate for the rate $\hat{\lambda}$ would be 1/5 or 0.2 arrivals per second.

***example1 for MoM (method of moments)***

Problem: You are monitoring a web server. You believe the time between incoming user requests follows an Exponential distribution. You need to estimate the rate parameter, $\lambda$, of this distribution.
Data: You collect a random sample of $n=5$ waiting times (in seconds):
$\text{Sample} = \{2.5, 3.1, 1.9, 2.8, 3.7\}$

***solution:*
Step 1:** Find the Population Moment formula

We have one unknown parameter ($\lambda$), so we only need the 1st moment (the mean). From Unit 1, we know the formula for the theoretical mean of an Exponential distribution is:
$E[X] = \frac{1}{\lambda}$

**Step 2:** Calculate the Sample Moment from data

We calculate the 1st sample moment (the sample mean, $\bar{x}$) from our actual data:
$\bar{x} = \frac{1}{n} \sum_{i=1}^{n} x_i$

$\bar{x} = \frac{2.5 + 3.1 + 1.9 + 2.8 + 3.7}{5}$

$\bar{x} = \frac{14.0}{5}$

$\bar{x} = 2.8 \text{ seconds}$
So, our sample average waiting time is 2.8 seconds.

**Step 3:** Equate the moments

Now we set the population formula from Step 1 equal to the sample value from Step 2:
$E[X] = \bar{x}$

$\frac{1}{\lambda} = 2.8$

**Step 4:** Solve for the unknown parameter

We solve the equation for $\lambda$. We'll call our estimate $\hat{\lambda}$ ("lambda-hat").
$\hat{\lambda} = \frac{1}{2.8}$

$\hat{\lambda} \approx 0.357$
Conclusion: Based on our data, the Method of Moments estimate for the rate is $\hat{\lambda} \approx 0.357$.
This means we estimate that requests are arriving at a rate of approximately **0.357 requests per second**.

---

### Maximum Likelihood Estimation

**Maximum Likelihood Estimation (MLE)** is a method to estimate unknown parameters of a model by choosing the value that makes the observed data **most likely**.

**MLE says: choose the p that gives the highest probability of the observed data.**

> *We have already observed our data. What set of parameters ($\mu, \sigma^2, \lambda$, etc.) would make the data we already saw the **most probable** (most likely) to have happened?*
> 

Imagine you have a coin and you don't know if it's fair. The unknown **parameter** is $p$, the probability of getting Heads. You flip it 10 times and get this exact result:

**{H, H, T, H, H, T, H, H, H, H}**

(That's 8 Heads and 2 Tails)

Now, you ask a simple question: "Which value of $p$ would make this outcome *most likely*?"
• What if $p = 0.5$ (a fair coin)?
The probability of getting 8H, 2T would be $\binom{10}{8} \times (0.5)^8 \times (0.5)^2 \approx 0.044$.
• What if $p = 0.1$ (a coin very biased to Tails)?
The probability would be $\binom{10}{8} \times (0.1)^8 \times (0.9)^2 \approx 0.0000036$. This is extremely unlikely. Our data just doesn't support this $p$.
• What if $p = 0.8$ (a coin biased to Heads)?
The probability would be $\binom{10}{8} \times (0.8)^8 \times (0.2)^2 \approx 0.302$. ***(HIGHEST)***

• What if $p = 0.9$  (a coin highly biased to Heads)?
The probability would be $\binom{10}{8} \times (0.9)^8 \times (0.1)^2 \approx 0.194$.

> It seems that $p=0.8$ is the *best* explanation for the data we saw.
**This is the entire philosophy of MLE.** You find the one value for the parameter (we call it $\hat{p}$, or "p-hat") that *maximizes the probability* of having observed your exact data.
> 

**The "Likelihood Function" $L(\theta)$**

This brings us to the main tool: the **Likelihood Function**.
• A **Probability Function** $P(x | \theta)$ asks: "Given a parameter $\theta$, what's the chance of getting data $x$?"
• A **Likelihood Function** $L(\theta | x)$ flips this. It asks: "Given the data $x$ that I *already have*, what is the 'likelihood' of various parameters $\theta$?"

It's the *same formula*, but we treat the data ($x$) as fixed and the parameter ($\theta$) as the variable we want to change.

**Crucial Difference:** We treat the data ($x_i$) as *fixed* (we already saw it) and the parameter ($\theta$) as the *variable* we want to change.

The goal is to find the $\theta$ that maximizes $L(\theta | x)$.

**The 4-Step Process for finding Likelihood function** 

Calculating this by hand (as we did above, plugging in 0.5, 0.1, 0.8) is too slow. We use calculus to find the *exact* peak of the likelihood function.

**Step 1:** Write the Likelihood Function $L(\theta)$

If your data points $x_1, \dots, x_n$ are independent (which they usually are), the total probability is just the product of the individual probabilities.

> formula:
$L(\theta) = \prod_{i=1}^{n} P(x_i | \theta)$
> 

**Step 2:** Use the Log-Likelihood $l(\theta)$

Multiplying things is hard. Adding things is easy.
Calculus on products is hard (product rule). Calculus on sums is easy. Since $\log(x)$ is a monotonically increasing function, the value of $\theta$ that maximizes $L(\theta)$ is the exact same value that maximizes $\log(L(\theta))$. We call this the ***log-likelihood.***

> ***log-likelihood function:***
$l(\theta) = \log(L(\theta)) = \sum_{i=1}^{n} \log(P(x_i | \theta))$
> 

**Why does this work ?** Because $\ln(a \cdot b) = \ln(a) + \ln(b)$. This turns a horrible **product** into a simple **sum**.**Is this legal?** Yes. The $\ln(x)$ function is *monotonically increasing*. This means that the $\theta$ that maximizes $L(\theta)$ is the *exact same* $\theta$ that maximizes $\ln(L(\theta))$.

**Step 3:** Differentiate
Take the derivative of the log-likelihood $l(\theta)$ with respect to the parameter $\theta$.
$\frac{d}{d\theta} l(\theta)$

**Step 4:** Set to Zero and Solve
To find the peak (the maximum) of a function, you set its derivative to 0 and solve for the parameter. The solution is your MLE, $\hat{\theta}$.

**Working Example for Maximum Likelihood Estimation (MLE)**
Lets solve the same Problem that we did earlier using HIT and trial: 

We flip a coin $n=10$ times. The parameter $p$ (probability of heads) is unknown.
Data: We observe $k=8$ heads.
Step 1: Write the Likelihood Function $L(p)$
The probability of getting $k$ heads in $n$ trials is given by the Binomial PMF:
$L(p) = P(k=8 | p, n=10) = \binom{10}{8} p^8 (1-p)^{10-8}$

$L(p) = \binom{10}{8} p^8 (1-p)^2$

Step 2: Use the Log-Likelihood $l(p)$

We take the natural log ($\log$) of $L(p)$:
$l(p) = \log\left(\binom{10}{8} p^8 (1-p)^2\right)$

Using log rules ($\log(ab) = \log a + \log b$ and $\log(x^k) = k \log x$):

$l(p) = \log\left(\binom{10}{8}\right) + \log(p^8) + \log((1-p)^2)$

$l(p) = \log\left(\binom{10}{8}\right) + 8 \log(p) + 2 \log(1-p)$

Step 3: Differentiate $l(p)$ with respect to $p$

The $\log(\binom{10}{8})$ is just a constant, so its derivative is 0.

$\frac{d}{dp} l(p) = 0 + 8 \left(\frac{1}{p}\right) + 2 \left(\frac{1}{1-p} \cdot (-1)\right)$

$\frac{d}{dp} l(p) = \frac{8}{p} - \frac{2}{1-p}$

Step 4: Set to Zero and Solve for $p$
$\frac{8}{p} - \frac{2}{1-p} = 0$

$\frac{8}{p} = \frac{2}{1-p}$

Cross-multiply:
$8(1-p) = 2p$

$8 - 8p = 2p$

$8 = 10p$

$\hat{p} = \frac{8}{10} = 0.8$

Conclusion:
The Maximum Likelihood Estimate is $\hat{p} = 0.8$. The parameter value that best explains seeing 8 heads in 10 flips is $p=0.8$.

Therefor the 8 heads and 2 tails in 10 tosses we get when the coin we have has the P=0.8 i.e probability of getting head is 0.8

---

### Recent Trends in various distribution functions in computer science

It's about connecting all the theory we've just learned (PMFs, PDFs, MoM, MLE) to how it's *actually used* in modern, 
The main "trend" is this: We're moving **beyond simple, clean distributions** (like the fair coin or the perfect bell curve) and using powerful computers to model **messy, complex, real-world data**.

**1. Trend: Probabilistic Machine Learning (ML)**

This is the biggest and most important trend. Many advanced ML models are not deterministic; they are *probabilistic*. They use distributions to represent *uncertainty*.
• **Bayesian Inference:** Instead of finding *one single* "best" parameter (like MLE does), Bayesian methods treat the parameter itself as a random variable.
    ◦ *Old Way (MLE):* "My estimate for the click-through rate is exactly $p = 0.7$."
    ◦ *New Way (Bayesian):* "I'm 95% confident the click-through rate $p$ is *between 0.65 and 0.75*." This is much more useful, as it explicitly states the model's uncertainty.
• **Generative Models (AI):** Models like **Generative Adversarial Networks (GANs)** or **DALL-E** are essentially *learning* the entire, incredibly complex probability distribution of data (e.g., $P(\text{image | text})$). They learn the "distribution of all human faces" so they can then **sample** from it to create a new, realistic face that has never existed.

**2. Trend: Modeling Network Traffic & Systems**

For a long time, networking theory used simple **Poisson/Exponential distributions** to model server requests or packet arrivals. We've learned this is often wrong.
• **Heavy-Tailed Distributions (e.g., Pareto):** Real-world data (like file sizes on the internet, or the duration of web sessions) doesn't follow a bell curve. It follows distributions with "heavy tails."
• **What this means:** In a Normal distribution, an event 10x the average is almost impossible. In a **heavy-tailed distribution**, it's rare but *very possible*. This means your system must be designed to handle rare, *extremely* large events (like a single file transfer 10,000 times the average size), which simple Poisson models would miss.

**3. Trend: Bioinformatics**

This field relies heavily on advanced probability models to find patterns in massive amounts of biological data.
• **Hidden Markov Models (HMMs):** This is a more advanced version of the Markov Chains from Unit 1. A HMM is used when you can't see the "state" directly, only an "observation" that depends on the state.
• **Application (Gene Finding):** You scan a long DNA sequence (A, T, C, G...). The "hidden state" might be {"inside a gene", "outside a gene"}. The sequence of A, T, C, G's you *observe* has a different probability distribution depending on which hidden state you're in. HMMs are the mathematical tool used to find the most likely "path" of hidden states, thus identifying where genes likely begin and end.Shutterstock

**4. Trend: Simulation (Monte Carlo Methods)**

Sometimes, the probability math is just too hard. The integrals are impossible to solve by hand.
• **The Trend:** Just use the computer's speed to run the experiment! If you can't *calculate* the expected value of a complex algorithm, just *run a simulation* of the algorithm 1,000,000 times with random inputs and take the average of the results. This is the **Monte Carlo method**. It uses random sampling to approximate complex calculations.
**In summary:** The "recent trend" is about moving from simple math to **computation-heavy statistics**. We use code (like in Python) to fit complex distributions, model uncertainty, and simulate systems that are too difficult to solve on paper.