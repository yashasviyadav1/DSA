### MATHEMATICAL FOUNDATIONS OF COMPUTER SCIENCE: Paper–MT–CSE–20–11

gemini: https://gemini.google.com/app/6fd6b85454fbddba

GPT: https://chatgpt.com/c/6922f49a-a060-8321-83d4-92b146b374ff

![Maths-2024-PYQ-page-1](https://i.ibb.co/B5kk55L2/image.png)
![Maths-2024-PYQ-page-2](https://i.ibb.co/xkzxCLF/image.png)



### **Compulsory Question 1**

1. Answer the following questions in brief : 5×3=15
    
    (a) Define Markov Chain. What are some applications
    of Markov Chains?
    (b) What is a Probability mass function (PMF)?
    (c) What types of Random sampling exist?
    (d) What is the difference between a parameter and a
    statistic?
    (e) How do we determine if two Graphs are isomorphic?
    

**Answer:** 

**(a) Define Markov Chain. What are some applications of Markov Chains?**

A **Markov Chain** is a stochastic process that undergoes transitions from one state to another on a state space. It is defined by the **Markov Property**, which states that the probability of moving to the next state depends *only* on the present state and not on the previous states (history). This is often called the "memoryless" property.

It has 2 main components:

- Set of States $V_0$: represents all the states that a system can travel between
- transition matrix $P$ : is a matrix that represents the probability of moving to any state from current state

Formula: $V_n = V_0*P^n$

**Applications:**
• **Natural Language Processing:** Predicting the next word in a sentence (e.g., autocorrect).
• **PageRank Algorithm:** Used by Google to rank web pages based on transition probabilities.
• **Weather Forecasting:** Predicting tomorrow's weather based solely on today's weather conditions.

**(b) What is a Probability mass function (PMF)?**

A **Probability Mass Function (PMF)** is a function that gives the probability that a **discrete** random variable is exactly equal to some value. Unlike continuous variables (which use Probability Density Functions), a PMF assigns a specific probability to distinct outcomes.
For a discrete random variable $X$, the PMF is denoted as $f(k) = P(X = k)$.

It must satisfy two conditions:

1. $f(x) \geq 0$ for all $x$. probability of every x is always positive
2. The sum of probabilities for all possible values is 1: $\sum f(x) = 1$.

**(c) What types of Random sampling exist?**

Random sampling is a part of the sampling technique in which each sample has an equal probability of being chosen. The four primary types are:

1. **Simple Random Sampling:** Every member of the population has an equal chance of being selected (e.g., drawing names from a hat).

2. **Systematic Sampling:** Members are selected at regular intervals (e.g., every 10th person on a list) after a random starting point.

3. **Stratified Sampling:** The population is divided into subgroups (strata) based on shared characteristics (e.g., age, gender), and random samples are taken from each stratum.

4. **Cluster Sampling:** The population is divided into clusters (usually geographic); entire clusters are randomly selected to be surveyed.

**(d) What is the difference between a parameter and a statistic?**

| **Feature** | **Parameter** | **Statistic** |
| --- | --- | --- |
| **Definition** | A numerical value that describes a characteristic of an entire **population**. | A numerical value that describes a characteristic of a **sample** taken from the population. |
| **Notation (Mean)** | $\mu$ (Mu) | $\bar{x}$ (x-bar) |
| **Notation (Variance)** | $\sigma^2$ (Sigma squared) | $s^2$ |
| **Variability** | Fixed (usually unknown). | Variable (changes from sample to sample). |
| **Usage** | Used to define the true nature of a group. | Used to estimate the parameter. |

**(e) How do we determine if two Graphs are isomorphic?**

Two graphs, $G_1$ and $G_2$, are **isomorphic** if they have identical structures, even if they are drawn differently. This means there exists a one-to-one correspondence (bijection) between the vertex sets that preserves the adjacency relationship.
To check for isomorphism (necessary conditions):

1. They must have the same number of **vertices** ($n$).

2. They must have the same number of **edges** ($m$).

3. They must have the same **degree sequence** (the list of vertex degrees must match).
**Note:** Even if these three conditions are met, graphs might not be isomorphic. The sufficient condition is finding a mapping function $f$ such that if edge $(u, v)$ exists in $G_1$, then edge $(f(u), f(v))$ must exist in $G_2$.

---

### UNIT–I

**Question - 2**

1.  What are Probabilistic inequalities? What is the
significance of Probabilistic inequalities in statistical
theory, and how do they help in bounding probabilies?
2. Why is the Central Limit Theorem important for
understanding confidence intervals?

Answer: 

1. **Probabilistic Inequalities** are mathematical theorems that provide upper and lower bounds on the probability that a random variable deviates from a certain value (usually its mean), often without requiring the exact probability distribution of the variable to be known.
    
    **Significance in Statistical Theory:**
    
    - **Theoretical Foundation:** They are the building blocks for fundamental limit theorems, such as the [**Law of Large Numbers**](https://www.notion.so/PYQ-2024-Solved-2b42a3410ddc80a99aabfea01545bc2d?pvs=21) and the convergence of random variables.
    - **Robustness:** They allow statisticians to make statements about data even when the underlying distribution is unknown or complex.
    - **Error Estimation:** In estimation theory, they help quantify the "worst-case" probability of an error occurring.

*The law of large numbers states that as the number of trials of a random experiment increases, the average of the results will approach the expected value of the experiment.*

How they help in bounding probabilities:
They limit the probability mass in the "tails" of a distribution.

- **Markov’s Inequality:** Provides an upper bound for the probability that a non-negative random variable exceeds a specific value.  Formula: $P(X \ge a) \le \frac{E[X]}{a}$
- **Chebyshev’s Inequality:** Guarantees that a certain fraction of data must fall within $k$ standard deviations of the mean. For example, it proves that for *any* distribution, no more than $1/k^2$ of the values can be more than $k$ standard deviations away from the mean. Formula: $P(|X - \mu| \ge k\sigma) \le \frac{1}{k^2}$

b. The **Central Limit Theorem (CLT)** is the mathematical justification that allows us to construct confidence intervals for the mean, even when the population data is **not normally distributed**.

- **Normality of the Estimator:** The CLT states that the sampling distribution of the sample mean ($\bar{x}$) will approximate a **Normal Distribution** as the sample size increases ($n \ge 30$), regardless of the shape of the original population distribution.
- **Standardization:** Because the sampling distribution is normal, we can use standard **Z-scores** (or t-scores) to define the "confidence" (e.g., 95% of the area under the curve).
- **Predictability:** Without the CLT, we would not have a reliable formula (like $\bar{x} \pm Z \frac{\sigma}{\sqrt{n}}$) to create an interval that we trust contains the true population parameter.

Question 3: 

1. What is the variance of a discrete random variable,
and how is it computed? A discrete random variable
X takes the values x 1, 2,3, 4 with corresponding
probabilities : $P(X = 1) = 0.1, P(X = 2) = 0.3, P(X = 3) = 0.4, P(X = 4) = 0.2$
    
    Calculate the variance of X.
    
2. What is the cumulative distribution function (CDF),
and how does it relate to the PMF ?
3. Distinguish between specialization and generalization.
Draw an EER diagram to illustrate specialization

Answer: 

**(a) Variance of a Discrete Random Variable**

Definition:
The variance of a discrete random variable $X$ measures the spread, dispersion, or variability of the distribution. It represents the expected value of the squared deviation of the random variable from its mean ($\mu$).
How it is computed:
The variance, denoted as $\sigma^2$ or $Var(X)$, is calculated using the formula:
$Var(X) = E[(X - \mu)^2] = \sum (x - \mu)^2 \cdot P(X=x)$

Alternatively, for easier calculation, the standard computational formula is used:

$Var(X) = E[X^2] - (E[X])^2$

Where:

- $E[X]$ is the Mean (Expected Value).
- $E[X^2]$ is the Expected Value of the square of $X$.

**Numerical Solution:**
Given Data:

Values ($x$): 1, 2, 3, 4

Probabilities ($P(X=x)$): 0.1, 0.3, 0.4, 0.2

Step 1: Calculate the Mean, $E[X]$ (also called $\mu$)

$E[X] = \sum x \cdot P(x)$

$E[X] = 1(0.1) + 2(0.3) + 3(0.4) + 4(0.2)$

$E[X] = 0.1 + 0.6 + 1.2 + 0.8$

$E[X] = \mathbf{2.7}$

Step 2: Calculate $E[X^2]$

$E[X^2] = \sum x^2 \cdot P(x)$

$E[X^2] = 1^2(0.1) + 2^2(0.3) + 3^2(0.4) + 4^2(0.2)$

$E[X^2] = 1(0.1) + 4(0.3) + 9(0.4) + 16(0.2)$

$E[X^2] = 0.1 + 1.2 + 3.6 + 3.2$

$E[X^2] = \mathbf{8.1}$

Step 3: Calculate Variance

$Var(X) = E[X^2] - (E[X])^2$

$Var(X) = 8.1 - (2.7)^2$

$Var(X) = 8.1 - 7.29$

$Var(X) = \mathbf{0.81}$

**Answer:** The variance of X is **0.81**.

**(b) Cumulative Distribution Function (CDF)**

Definition:
The Cumulative Distribution Function (CDF), denoted by $F(x)$, specifies the probability that a

random variable $X$ will take a value less than or equal to a specific value $x$.

Formula:$F(x) = P(X \leq x)$

***Relation to PMF***: The CDF is related to the Probability Mass Function (PMF) through summation. For a discrete random variable, the CDF at value $x$ is the sum of the PMF values for all outcomes up to and including $x$.

1. From PMF to CDF:
$F(x) = \sum_{t \leq x} f(t)$

(Where $f(t)$ is the PMF)

2. From CDF to PMF:

You can recover the PMF from the CDF by taking the difference between consecutive CDF values:

$f(x) = F(x) - F(x-1)$

$PMF(x) = CMF(x) - CMF(x-1)$

**(c) Specialization vs. Generalization (EER Model)**

These concepts are used in the Extended Entity-Relationship (EER) model to define superclass/subclass relationships.

| **Feature** | **Specialization** | **Generalization** |
| --- | --- | --- |
| **Approach** | **Top-down** approach. | **Bottom-up** approach. |
| **Definition** | The process of breaking down a higher-level entity (superclass) into more specific lower-level entities (subclasses). | The process of combining multiple lower-level entities with shared characteristics into a single higher-level entity. |
| **Goal** | To identify distinct subsets of an entity set that have unique attributes. | To emphasize common attributes among different entity sets. |
| **Example** | An entity `Person` is specialized into `Student` and `Teacher`. | Entities `Car` and `Truck` are generalized into `Vehicle`. |

```
ERR DIAGRAM
            +----------------+
            |   Employee     |
            |----------------|
            | EmpID (PK)     |
            | Name           |
            | HireDate       |
            | Salary         |
            +----------------+
                   /|\
                    |
                 (ISA)
                  / \
                 /   \
+------------+  +---------+  +------------+
|  Engineer  |  |Secretary|  | Technician |
|------------|  |---------|  |------------|
| EmpID (FK) |  | EmpID   |  | EmpID (FK) |
| Discipline |  | Typing  |  | SkillLevel |
| Level      |  | Speed   |  | Certification |
+------------+  +---------+  +------------+
```

---

### Unit-2 Questions:

**Question-4.** 

1. What are the limitations of the Method of Moments,
and how might it lead to inefficient estimators?
2. What is the concept of a Random sample, and how
does it differ from a nonrandom sample in terms of
bias and representativeness?

Answer 4: 

**(a) Limitations of the Method of Moments and Inefficiency of Estimators**

The **Method of Moments (MoM)** is a technique for estimating population parameters by equating sample moments (like the sample mean or sample variance) to the corresponding theoretical population moments. While it is computationally simple and consistent, it has significant limitations compared to more robust methods like Maximum Likelihood Estimation (MLE).

**1. Limitations of the Method of Moments:**

- **Lack of Efficiency (High Variance):** The primary limitation is that MoM estimators are often **inefficient**. In statistics, efficiency refers to the variance of the estimator. MoM estimators typically have a larger variance (standard error) than Maximum Likelihood estimators, especially for small sample sizes. This means the estimates are more "spread out" from the true value.
- **Range Violation (Impossible Estimates):** MoM does not restrict estimates to the valid parameter space. For example, when estimating a probability parameter, MoM might produce a value greater than 1 or less than 0. Similarly, it might estimate a negative variance, which is mathematically impossible.
- **Dependence on Existence of Moments:** The method relies on the existence of population moments. For certain distributions (like the **Cauchy distribution**), the theoretical moments (mean, variance) are undefined or infinite. In such cases, the Method of Moments cannot be applied at all.
- **Ignoring Sufficient Statistics:** MoM estimators often do not utilize "sufficient statistics" (data summaries that contain all the information needed to estimate a parameter). By relying only on lower-order moments (like the mean), MoM might discard useful information contained in the data distribution, leading to less accurate results.

**How it leads to Inefficient Estimators:**
An estimator is considered "efficient" if it achieves the lowest possible variance (the Cramér-Rao lower bound).

- MoM estimators often fail to reach this lower bound.
- Because MoM focuses only on matching averages (moments) rather than maximizing the probability of the observed data (like MLE does), it does not extract as much information from the sample.
- **Result:** You would need a much larger sample size using the Method of Moments to achieve the same level of precision that a Maximum Likelihood Estimator could achieve with a smaller sample.

**(b) Concept of Random Sample vs. Nonrandom Sample**

Concept of a Random Sample:
A Random Sample is a subset of individuals chosen from a larger population in such a way that every individual in the population has a known, non-zero probability of being selected.

In its purest form (Simple Random Sampling), every possible sample of size $n$ has an **equal probability** of being chosen.

It ensures that the variables are **Independent and Identically Distributed (i.i.d)**.

Difference in terms of Bias and Representativeness:

| **Feature** | **Random Sample** | **Nonrandom Sample (e.g., Convenience, Quota)** |
| --- | --- | --- |
| **Bias** | **Minimizes Bias.** Because selection is left to chance, systematic favoritism is eliminated. The expected value of a statistic (like the sample mean) is usually equal to the true population parameter. | **High Risk of Bias.** Selection depends on human judgment or convenience. This introduces **Selection Bias** (e.g., interviewing only friends or people who volunteer), leading to results that skew away from the truth. |
| **Representativeness** | **Highly Representative.** By giving everyone a chance to be picked, the sample tends to reflect the diversity and characteristics of the entire population naturally (especially as sample size increases). | **Low Representativeness.** The sample usually reflects only a specific slice of the population (e.g., only internet users, only people in a specific city mall), making it a poor proxy for the whole group. |
| **Inference** | **Valid.** You can mathematically calculate sampling error and confidence intervals to generalize results to the whole population. | **Invalid.** You cannot objectively calculate error margins or confidently generalize findings to the broader population. |

**Summary:** Random sampling allows for scientific generalization, while nonrandom sampling is often descriptive only of the sample itself.

---

**Question-5.** What is a sampling distribution, and why is it important in understanding the properties of estimators? How does the sampling distribution of an estimator help us assess its bias and efficiency?

**Answer 5:**

***What is a sampling distribution?***

**A** **Sampling Distribution** is a probability distribution of a statistic (such as the mean, variance, or proportion) obtained from a large number of samples drawn from a specific population.
Key Concept:

Imagine you have a population of 1 million people. You cannot measure everyone, so you take a random sample of 100 people and calculate their average height ($\bar{x}$). If you repeat this process—taking 1,000 different samples of 100 people and calculating the average for each—you will have 1,000 different averages.

The **distribution (or plot)** of these 1,000 averages is the **Sampling Distribution of the Sample Mean**.
• It bridges the gap between the **Sample** (statistics) and the **Population** (parameters).
• It describes how a statistic varies from sample to sample.

***How does the sampling distribution of an estimator help us assess its bias?***

An **estimator** is a **rule or formula** used to estimate an unknown population parameter (like mean, variance, proportion) using sample data.

- **Estimator** = the formula (like sample mean). ex estimator for finding mean of a sample can be this: $\frac{1}{n}\sum_{i=1}^{n} X_i$
- **Estimate** = the value you get from applying the estimator to one sample.
- **Sampling distribution** = distribution of many such estimates (from repeated samples).

**Bias** refers to the tendency of a statistic to overestimate or underestimate a parameter. The sampling distribution is the primary tool used to check for bias.

- Definition of Unbiasedness: An estimator $\hat{\theta}$ is unbiased if the mean (expected value) of its sampling distribution equals the true population parameter $\theta$.
    - $E[\hat{\theta}] = \theta$ (unbiased)

If you plot the sampling distribution of the estimator:

- **Unbiased:** The "center of gravity" or the peak of the distribution sits exactly on top of the true population value.
- **Biased:** The center of the distribution is shifted to the left or right of the true value. The distance between the center of the distribution and the true value is the **Bias**.

***How does it help assess Efficiency?***

**Efficiency** refers to the precision or reliability of the estimator. It is determined by the **variance** (spread) of the sampling distribution.

- **Definition:** An efficient estimator is one that has the **smallest possible variance** among all unbiased estimators.
- **How the Sampling Distribution helps:**
By observing the "width" or spread of the sampling distribution, we can judge efficiency:
    - **High Efficiency:** The sampling distribution is **narrow** and tall. This means that if you take repeated samples, the calculated statistics will be very close to each other (and the true value).
    - **Low Efficiency:** The sampling distribution is **wide** and flat. This means the statistics vary wildly from sample to sample; one sample might give a very high value, and another might give a very low value.

---

### Unit-3 Questions:

**Question-6**: 

1. In multivariate analysis, how can you deal with missing data, and what techniques are available to handle missing values in high-dimensional datasets?
2. What are the steps involved in performing PCA on a dataset, and how do you interpret the results at each stage?

**Answer-6:** 

**(a) Dealing with Missing Data in Multivariate Analysis**

In multivariate analysis, missing data can severely bias results and reduce statistical power. Handling it effectively requires a two-step approach: diagnosing the **pattern** of missingness and then applying an appropriate **technique**.

**I. Diagnosing the Missing Data Mechanism**
Before applying a fix, you must understand *why* data is missing:

- **MCAR (Missing Completely at Random):** No pattern; missingness is unrelated to any variable (Safe to delete). eg. A lab machine randomly fails to record a measurement due to a temporary glitch.
- **MAR (Missing at Random):** Missingness is related to observed data (e.g., men are less likely to report depression, but gender is recorded). example: Older people skip online survey questions more often (age is known). Missingness is predictable using observed data. Missingness depends on age (observed), not on the actual answer they would have given.
- **MNAR (Missing Not at Random):** Missingness depends on the missing value itself (e.g., high-income earners not reporting income). This is the hardest to handle. example:  People with **very high income** skip the income question. Missingness depends on the true (missing) income value.

**II. Techniques to Handle Missing Values (including High-Dimensional Datasets)**

1. **Deletion Methods (Simplest):**

- **Listwise Deletion:** Removing entire rows with *any* missing value. (Good for MCAR, bad for high-dimensional data as you might lose most rows).
- **Pairwise Deletion:** Using all available data for specific calculations (e.g., correlation).

2. **Basic Imputation:**

- **Mean/Median/Mode Substitution:** Replacing missing values with the column average. (Simple, but underestimates variance and distorts correlations).

3. **Advanced Techniques for High-Dimensional Data:**

- **K-Nearest Neighbors (K-NN) Imputation:** Finds the $k$ samples most similar to the one with missing data (based on other features) and imputes the average of their values. Very effective for multivariate data.
- **Multiple Imputation (MICE):** Creates multiple different "filled-in" datasets by modeling each missing variable as a function of other variables. It accounts for the uncertainty of the missing data.
- **Matrix Completion / Factorization:** Uses techniques like Singular Value Decomposition (SVD) to approximate the data matrix and fill in gaps. Ideally suited for sparse, high-dimensional matrices (like Netflix recommendation systems).
- **Expectation-Maximization (EM) Algorithm:** An iterative method that estimates parameters in the presence of missing data by alternating between estimating the missing values (E-step) and optimizing the model parameters (M-step).

**(b) Steps Involved in Performing PCA and Interpreting Results**

Principal Component Analysis (PCA) is a dimensionality reduction technique used to transform a large set of variables into a smaller set that still contains most of the information.

**Step 1: Standardization (Scaling)**

- **Action:** Rescale data so that each variable has a mean of 0 and a standard deviation of 1 (Z-score normalization).
- Interpretation**:** This is crucial because PCA is sensitive to the scale of data. Without this, variables with large ranges (e.g., Salary) would dominate variables with small ranges (e.g., Age), biasing the results.

**Step 2: Compute the Covariance Matrix**

- **Action:** Calculate the covariance matrix (or correlation matrix) for the data.
- **Interpretation:** This matrix reveals how variables relate to one another. High positive covariance indicates variables vary together; zero implies independence. PCA aims to decorrelate these variables.

**Step 3: Compute Eigenvectors and Eigenvalues**

- **Action:** Decompose the covariance matrix into Eigenvectors and Eigenvalues.
- **Interpretation:**
    - **Eigenvectors:** Represent the **directions** (axes) of the new feature space (Principal Components).
    - **Eigenvalues:** Represent the **magnitude** (variance) of the data in that direction. A higher eigenvalue means that component carries more information.

**Step 4: Selection of Principal Components**

- If you want to reduce your data to 2 dimensions, you pick the 2 eigenvectors with the highest
eigenvalues

**Step 5: Projection (Transform Data)**

- **Action:** Multiply the original standardized data by the selected Eigenvectors to get the new dataset.

**Interpretation:** The data is now in a new coordinate system. The new variables (Principal Components) are uncorrelated. The first component captures the most pattern, the second captures the second most, and so on.

---

**Question 7:**

1. In the context of multivariate regression analysis, how do you interpret the coefficients of the model, especially when the predictors are correlated?
2. What is Principal Component Analysis (PCA), and what are its main objectives in data analysis?

**Answer 7:**

**(a) Interpretation of Multivariate Regression Coefficients (especially with correlated predictors)**

1. Standard Interpretation (The Ideal Scenario)

In a multivariate linear regression model represented by the equation:

$Y = \beta_0 + \beta_1X_1 + \beta_2X_2 + \dots + \beta_nX_n + \epsilon$

The coefficient $\beta_i$ represents the **partial regression coefficient**.

**Definition:** It indicates the expected change in the dependent variable $Y$ for a one-unit increase in the predictor $X_i$, **holding all other predictors ($X_j$) constant** (Ceteris Paribus).

**Example:** In a model predicting House Price based on Size ($X_1$) and Age ($X_2$), if $\beta_1 = 50$, it means that if the Size increases by 1 square foot *and the Age of the house remains exactly the same*, the price increases by $50.

2. The Problem with Correlated Predictors (Multicollinearity)
When predictors are highly correlated (a condition known as Multicollinearity), the standard interpretation breaks down.

- **Loss of Isolation:** If $X_1$ and $X_2$ are highly correlated (e.g., years of education and years of work experience), it becomes mathematically and practically impossible to change $X_1$ while holding $X_2$ constant. They move together.
- **Unstable Coefficients:** The estimates of the coefficients become highly sensitive to small changes in the data. Adding or removing a few data points can drastically change the value (and even the sign) of $\beta$.
- **Inflated Standard Errors:** Correlation increases the variance of the coefficient estimates. This leads to larger standard errors, which lowers the t-statistic.
    
    **Result:** You might find that the overall model is significant (high $R^2$), but individual variables appear statistically insignificant because their effects are "mixed up" or "shared."
    
- **Misleading Signs:** A variable that positively impacts $Y$ might show a negative coefficient simply because it is negatively correlated with another strong predictor in the model.

**Summary:** When predictors are correlated, you cannot interpret a coefficient as the *unique* effect of that variable. You must interpret them as a **joint effect**.

**(b) Principal Component Analysis (PCA) and its Main Objectives**

Definition: Principal Component Analysis (PCA) is an unsupervised statistical technique used for dimensionality reduction. It ***transforms a large set of potentially correlated variables into a smaller set of uncorrelated variables*** called Principal Components (PCs).

These new components are linear combinations of the original variables and are ordered so that the first few components retain most of the variation present in all of the original variables.

**Main Objectives in Data Analysis:**

1. **Dimensionality Reduction:**
The primary goal is to reduce the number of variables (features) in a dataset while losing as little information as possible. This overcomes the "Curse of Dimensionality" and makes algorithms run faster.
2. **Feature Extraction / Decorrelation:**
PCA converts correlated variables into uncorrelated (orthogonal) components. This solves the **Multicollinearity** problem mentioned in part (a), making the data suitable for algorithms that assume feature independence (like Naive Bayes or Linear Regression).
3. **Data Visualization:**
It is difficult to visualize data with more than 3 dimensions. PCA can project high-dimensional data down to 2D or 3D (using the first two or three PCs) to reveal clusters, outliers, or patterns visually.
4. **Noise Reduction:**
By keeping only the top principal components (which capture the signal/variance) and discarding the lower-ranked components (which often represent random noise), PCA helps in cleaning the data.
5. **Data Compression:**
It allows for storing and transmitting data more efficiently by representing complex datasets with fewer values.

---

### Unit - 4 Questions

**Question 8:** 

1. Discuss the relationship between graph colouring and the chromatic number in bipartite graphs
2. Can a graph with more than four vertices have fewer than four edges and still be planar?

**Answer-8:**

**(a)** Relationship between graph colouring and the chromatic number in bipartite graphs

- **Graph Coloring:** The assignment of labels (colors) to the vertices of a graph such that no two adjacent vertices (vertices connected by an edge) share the same color.
- **Chromatic Number ($\chi(G)$):** The minimum number of colors required to properly color a graph $G$.
- **Bipartite Graph:** A graph whose vertices can be divided into two disjoint and independent sets, $V_1$ and $V_2$, such that every edge connects a vertex in $V_1$ to one in $V_2$. No edge connects two vertices within the same set.

**2. The Relationship:**
The relationship is precise and fundamental: **A graph is bipartite if and only if its chromatic number is 2** (provided the graph has at least one edge).

**3. Explanation:**
Why 2 colors?

In a bipartite graph, since all vertices are partitioned into two sets ($V_1$ and $V_2$) with no internal edges:

- We can assign **Color A** to all vertices in set $V_1$.
- We can assign **Color B** to all vertices in set $V_2$.
- Since edges only travel between $V_1$ and $V_2$, no two adjacent vertices will have the same color.
    - This constitutes a valid 2-coloring.

**Conclusion:**

- If a bipartite graph has edges, its chromatic number $\chi(G) = 2$.
- If a bipartite graph has no edges (only isolated vertices), its chromatic number $\chi(G) = 1$
- Conversely, if a graph requires 3 or more colors (contains an odd cycle), it cannot be bipartite.

**(b) Can a graph with more than four vertices have fewer than four edges and still be planar?**

Yes, absolutely. In fact, every graph that fits this description is planar.

Explanation: To understand why, we look at what makes a graph non-planar. A graph is non-planar only if it is "dense" enough to contain complex crossing structures. 

Specifically, according to **Kuratowski's Theorem**, a graph is non-planar only ***if it contains a subgraph that is a subdivision of $K_5$ (complete graph with 5 vertices) or $K_{3,3}$ (complete bipartite graph)**.*
Let's analyze the constraints given:

- **Vertices ($V$):** More than 4 (e.g., $V = 5$).
- **Edges ($E$):** Fewer than 4 (e.g., $E = 3, 2, 1, \text{or } 0$).

**Reasoning: Lack of Edges:** A graph with fewer than 4 edges ($E \le 3$) is extremely sparse. With only 3 edges, the most complex structure you can form is a triangle (a cycle of 3). A triangle is trivially planar (can be drawn on paper without crossing lines).

- **Impossibility of Crossing:** To have edges that cross and cannot be untangled, you need a significant number of connections. $K_5$ requires 10 edges and $K_{3,3}$ requires 9 edges. It is physically impossible to form a non-planar structure with only 3 edges.
- **Forest Structure:** A graph with $V > 4$ and $E < 4$ will typically be a **Forest** (a collection of disjoint trees) or a set of isolated vertices and simple paths. All forests are planar.
- Example: Imagine 5 dots (Vertices) on a paper. You are allowed to draw only 3 lines (Edges) connecting them. No matter how you connect them, you can always draw the lines without them crossing each other.

---

**Question 9:** Define the concept of Combinations with repetition. Derive and explain the formula for selecting r objects from n distinct objects when repetition is allowed. Provide an example to demonstrate how this formula is applied.

**Answer 9:**

**Definition: Combinations with Repetition**

**Combinations with repetition** is a counting method used to determine the number of ways to select $r$ items from a set of $n$ distinct types of items, where:

1. **Order does not matter:** The arrangement of the selected items is irrelevant (e.g., choosing Chocolate then Vanilla is the same as choosing Vanilla then Chocolate).
2. **Repetition is allowed:** You can select the same type of item more than once (e.g., you can choose two scoops of Chocolate).
This differs from standard combinations ($^nC_r$), where once an item is picked, it cannot be picked again.

**2. The Formula and Derivation (The "Stars and Bars" Method)**
The Formula:
The number of ways to select $r$ objects from $n$ distinct types with repetition allowed is given by: $C(n+r-1, r) \quad \text{or} \quad \binom{n+r-1}{r}$
Derivation: To derive this formula, we use a combinatorial technique known as the Stars and Bars method.
The Setup:
Imagine we have $n$ distinct categories (or bins) and we want to select $r$ items total.

- We represent the **items** we select as **Stars** ($\star$). We need $r$ stars.
- We separate the distinct **categories** using **Bars** ($|$). To separate $n$ categories, we need exactly $n-1$ bars.

Total Positions:
The problem now shifts from "selecting items" to "arranging symbols." i.e arranging r items into n categories (so for arranging in 3 categories needs 2 bars thats why we used n-1 in formula) 

- Total symbols to arrange = (Number of Stars) + (Number of Bars)
- Total positions = $r + (n - 1)$
- The Calculation: We have $n + r - 1$ total positions available. We need to place $r$ stars into these positions (the remaining positions will automatically be filled by bars).
- Using the standard combination formula for choosing positions:
- $\text{Ways} = \binom{\text{Total Positions}}{\text{Number of Stars}}$
- $\text{Ways} = \binom{n + r - 1}{r}$
- This is equivalent to:$\frac{(n + r - 1)!}{r!(n - 1)!}$

**Example to demonstrate Combination with repetition:**

Problem: A bakery sells 3 types of donuts: Glazed, Chocolate, and Sprinkled. You want to buy a box of 2 donuts. How many different combinations of donuts can you buy?

**Solution:**
**1. Identify Variables:**

- $n = 3$ (The distinct types: Glazed, Chocolate, Sprinkled).
- $r = 2$ (The number of items to select).

$\text{Total Combinations} = \binom{n + r - 1}{r}$

$\text{Total Combinations} = \binom{3 + 2 - 1}{2}$

$\text{Total Combinations} = \binom{4}{2}$

$\binom{4}{2} = \frac{4!}{2!(4-2)!} = \frac{4 \times 3}{2 \times 1} = \frac{12}{2} = 6$

**Verification (Listing the options):**
To prove the formula works, let's list the possibilities (G=Glazed, C=Choc, S=Sprinkle):

1. **GG** (2 Glazed)
2. **CC** (2 Chocolate)
3. **SS** (2 Sprinkled)
4. **GC** (1 Glazed, 1 Chocolate)
5. **GS** (1 Glazed, 1 Sprinkled)
6. **CS** (1 Chocolate, 1 Sprinkled)

---

**Extra Que for Combinators**

**Q:** Unlimited supply of **4 types of stickers**, distribute **10 stickers** among **3 students**.

(Each sticker type can appear many times.)

We treat this as:

**Step 1 — Choose 10 stickers from 4 types (repetition allowed)**

So first:

$\binom{13}{10} = \binom{13}{3} = 286$

So there are **286 possible sets of 10 stickers** (like multiset selection).

**Step 2 — Distribute the chosen 10 stickers among 3 students**

Each sticker (regardless of type) can go to **any of 3 students**.

So for each of the 10 stickers → 3 choices →

$3^{10} = 59049$

**Total number of distributions:**

For each selection of stickers (286 possibilities), we have $3^{10}$ ways to distribute.

Total ways = $286 \times 59049$

Compute:

$286 \times 59049 = 168,892,014$ ways