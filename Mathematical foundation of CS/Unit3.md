# Unit 3

![unit 3 image](https://i.ibb.co/ZzR2K4kR/image.png)

### Statistical Inference

It is the formal name for the entire field of using sample data to make conclusions about a population

We've already learned one half of this:
1. **Estimation:** (e.g., creating a **Confidence Interval**). This is when we say, "I'm 95% confident the *true mean* $\mu$ is *between* 99.06 and 104.94." It's an "estimation" problem.

Now, we'll learn the second, and more famous, half:
2.  **Hypothesis Testing:** This is a formal procedure for making a **"yes/no" decision** based on data. (e.g., "Is this new server *faster* than the old one? Yes or No?", "Did this new drug *work*? Yes or No?").

**What is Hypothesis Testing?**
A hypothesis test is a formal "duel"(fight) between two competing claims about the population. We use our sample data to act as the "judge" and decide which claim is more likely to be true.

**1. The Two Hypotheses (The "Claims")**

1. **The Null Hypothesis ($H_0$) - current condition**
    1. This is the "boring" claim that *nothing interesting happened*. It's the default, the current belief, the "current condition"
        1. It *always* contains the equals sign: $=$, $\le$, or $\ge$.
        2. **In a trial:** "The defendant is **innocent**." ($H_0: \text{Defendant} = \text{Innocent}$)
2. **The Alternative Hypothesis ($H_A$ or $H_1$) - "The New Idea"**
    1. This is the "exciting" claim that the researcher *wants to prove*. It's the new idea, the "effect" they're looking for.
        1. It *never* contains an equals sign: $\ne$, $<$, or $>$.
        2. **In a trial:** "The defendant is **guilty**." ($H_A: \text{Defendant} \ne \text{Innocent}$)

**2. The Courtroom Logic (The "Innocent Until Proven Guilty" Rule)**
This is the absolute core of all hypothesis testing.We *assume* the Null Hypothesis ($H_0$) is TRUE from the start.

It is the job of the **data (the "evidence")** to convince us *beyond a reasonable doubt* that the $H_0$ is wrong and that we must switch to the $H_A$.

**3. The "Reasonable Doubt" Level ($\alpha$)**
How strong must the evidence be? We have to set a standard *before* the trial. This is the **Significance Level**, called **alpha ($\alpha$)**.
• $\alpha$ is the "reasonable doubt" threshold. It's the probability of a **Type I Error**.
• **Type I Error (False Positive):** We *reject $H_0$* even though $H_0$ was actually true.
• We usually set $\alpha = 0.05$ (or 5%).
• **Meaning:** "I am willing to accept a 5% risk of convicting an innocent person (a 5% risk of a Type I error) in order to run my test."

> In simple words, Reject H₀ (the currently known theory) when the evidence is so unlikely (p-value small) that it crosses our doubt threshold $α$.  i.e if p’s value < alpha (means this new result we have is very unlikely (very less chance of it happening) under $H_0$
> 

**Example of: How to run a Hypothesis Test**

***Example***: A server's average response time used to be $\mu = 120$ ms. We deploy a new update. We take a sample of $n=100$ requests and find our sample mean is $\bar{x} = 118$ ms. (We know $\sigma=10$).
So, question is that did the update actually make the server faster? Or was 118 just a "lucky" sample ? ($\alpha = 0.05$)

Firstly the lucky means - this 118ms sample mean had 5% or more chance ($\alpha$) of happing with the older setup without the update.

***Solution:***

**1.State the Hypotheses:**

$H_0: \mu \ge 120$ (The "boring" claim: the update did *not* make it faster; it's the same or worse).
$H_A: \mu < 120$ (The "exciting" claim: the update *did* make it faster. This is what we want to prove).

**2.Set the Significance Level ($\alpha$):**
$\alpha = 0.05$. (Our "reasonable doubt" threshold).

**3. Calculate the Test Statistic:**
We're asking: "If $H_0$ is true (if $\mu$ *is* 120), how *weird* is our sample mean of 118?"
We use the CLT (the Z-score) to calculate the probability of our 118 happening, because we *know* $\sigma$.

$Z = \frac{\bar{x} - \mu_0}{\sigma/\sqrt{n}} = \frac{118 - 120}{10/\sqrt{100}} = \frac{-2}{10/10} = \frac{-2}{1} = -2.0$
**Evidence:** Our sample is 2 standard deviations below the null hypothesis mean.

**4. Make the Decision (Two ways to do this):**

Method 1: **convert z-value to p-value:**

**p-value:** "The probability of getting our new value (or more extreme), *if the null hypothesis is true*."

$p = P(Z \le -2.0) = 0.0228$

remember The Rule: If $p < \alpha$, Reject $H_0$.
**Decision:** $0.0228 < 0.05$. 

Our p-value (2.3%) is *less than* our "reasonable doubt" level (5%). The evidence is strong enough.

> **Reject H₀ when the evidence is so unlikely (p-value small) that it crosses our doubt threshold α.**
> 

> 2.28% is **below** the “acceptable doubt limit” of $\alpha$ = 5%. The data  (118ms) is too unlikely to happen if H₀ were true. Therefore H₀ is probably false.” means our new theory $H_1$ is true, coz Evidence is strong enough
> 

Method 2: **The Critical Value:**

Instead of calculating a p-value, we directly check: Is our Z-score beyond the “rejection cutoff”?This cutoff is called the **critical value**. ($\alpha = 0.05$)

We want to check if the server became **faster** → mean decreased value. So this is a **left-tailed test**.

For a **left-tailed** test at 5% significance:

$z_{\alpha}$ $=$ $-1.645$ (z-value of 0.05 or 5% in z-table)

This is the **cutoff point**.

Meaning:

> If Z-score is less than –1.645, we reject H₀. (because fast server means less time) so lesser the z score is from the cutoff point we reject $H_0$
> 

**The Rule:** **If $Z_{\text{test}}$ is in the rejection region, Reject $H_0$.**

Our test statistic $Z = -2.0$ is *in the rejection region* (it's further out than -1.645).

So conclusion: “At a 0.05 significance level, we **reject the null hypothesis ($H_0$)**. The evidence is statistically significant ($p < .05$) to conclude that the ***new update is faster** than the old version ( $\mu < 120$ ms)."*

---

### Introduction to multivariate statistical models: Regression and classification problems

**Introduction to Multivariate Statistical Models**

- **Univariate** means *one* variable (e.g., just looking at "server latency").
- **Multivariate** means *many* variables.

The goal of multivariate models is to understand the **relationships between multiple variables at the same time**. We're no longer just *describing* one thing; we're trying to **build a model** that explains how a set of *input variables* (or "features") can predict an *output variable*.

For example, instead of just modeling "house price," you'd build a multivariate model to predict **house price (Y)** based on:

- **X1:** Square footage
- **X2:** Number of bedrooms
- **X3:** Location (e.g., ZIP code)
- **X4:** Age of the house

Almost all real-world problems (especially in machine learning) are multivariate.

> Instead of just $Y \rightarrow X$ (one variable) finding Y from X, we're doing $Y \rightarrow (X_1, X_2, X_3, \dots)$ (many variables i.e finding Y depends on multiple variables).
> 

The "multivariate models" you were just introduced to are almost all used for one of two main tasks: **regression** or **classification**.

| **Type of Problem** | **Regression** | **Classification** |
| --- | --- | --- |
| **What are you predicting?** | A **continuous number** | A **discrete category** or "class" |
| **The Question** | "How much?" or "How many?" | "Which one?" or "What kind?" |
| **Examples** | 1. Predict the **price** of a house.
2. Predict the **temperature** tomorrow.
3. Predict the **number of sales** next quarter. | 1. Predict if an email is **Spam** or **Not Spam**.
2. Predict if a customer will **Churn** or **Stay**.
3. Predict if a tumor is **Benign** or **Malignant**. |

### 1. Regression

**1. Regression Problems**
To model the relationship between one or more independent variables (features, $X$) and a single, continuous dependent variable (the target, $Y$).

The most famous and fundamental model is **Linear Regression**.

**A) Simple Linear Regression (1 variable)**

You start with one feature $X$ to predict $Y$. (e.g., Predict `Height` using `Weight`).

You assume the relationship is a straight line.

> **Model:** $Y = \beta_0 + \beta_1X + \epsilon$
> 

$Y$: The variable we want to predict (Height).

$X$: Our feature (Weight).

$\beta_0$: The "intercept" (where the line starts).

$\beta_1$: The "slope" (the coefficient). This is the *most important part*. It means "for a 1-unit increase

in X, we *expect* Y to increase by $\beta_1$."

$\epsilon$: The "error" term. This is the random, unpredictable part that our model *can't* capture (from the CLT).

![](https://i.ibb.co/4RQ2mgyz/image.png)

**B) Multiple Linear Regression**

This is the *multivariate* model. We use *multiple* features ($X_1, X_2, \dots, X_p$) to predict $Y$

**Example:** Predict `House Price (Y)` using `Square Footage (X1)`, `Number of Bedrooms (X2)`, and `Distance from City (X3)`.

Model: We're no longer fitting a "line." We're fitting a "plane" or a "hyperplane" in higher dimensions.

> Model:
$Y = \beta_0 + \beta_1X_1 + \beta_2X_2 + \beta_3X_3 + \epsilon$
> 

**Interpretation:**
• $\beta_1$: "Holding bedrooms and distance constant, a 1-unit increase in *square footage* is associated with a $\beta_1$ change in *price*."

**β₁, β₂, β₃** = Regression Coefficients

These tell you **how much Y changes when each X changes** (keeping others constant).

**Example:** Suppose the model calculates:

$Y = 50 + 0.03X_1 + 10X_2 - 5X_3$

Interpretation:

- Intercept = 50 lakhs (baseline)
- +0.03 per sq ft
    
    → 100 sq ft extra increases price by 3 lakhs (because $0.03*100 = 3$)
    
- +10 lakhs per bedroom
- −5 lakhs per km further from city

If a house is:

- 1200 sq ft
- 3 bedrooms
- 2 km from the city

Prediction:

$Y=50+0.03(1200)+10(3)−5(2)$

$= 106 lakhs$

![](https://i.ibb.co/zVn0Wr2R/image.png)

**Examples:**

- CS/Systems: Predicting a server's CPU load based on time of day and number of users.
- Business: Predicting a house's price based on its square footage and number of bedrooms.
- Science: Predicting a student's test score based on hours studied.

How do we "find" the best line/plane?

We need to find the "best" $\beta$ coefficients. The most common way is the ***Ordinary Least Squares (OLS)*** method.

- It's a "cost function" that finds the line that **minimizes the sum of the squared errors SSE**.
- This is a "calculus" problem, just like **Maximum Likelihood Estimation (MLE)**. In fact, for linear regression, the OLS and MLE solutions are *identical*!

We want to find the best coefficients:

$\beta_0, \ \beta_1, \ \beta_2, ..., \beta_k$

so that the predictions:

$\hat{Y} = \beta_0 + \beta_1 X_1 + \dots + \beta_k X_k$

are as close as possible to the real Y’s.

**Why do we use (SSE) sum of the squared errors?**

We measure **errors**.

For each data point:

> $\text{error} = Y_{\text{actual}} - Y_{\text{predicted}}$
> 
- *But errors can be positive or negative, so we **square** them.*

**OLS (Ordinary Least Squares)**

OLS is a method to find $β$ values that minimize the sum of squared errors.

OLS tries to minimize:

> $\text{SSE} = \sum_{i=1}^{n} (Y_i - \hat{Y_i})^2$
> 

This is called the **Sum of Squared Errors**.

This is our **cost function**.

We want the $β$ values that make $SSE$ as small as possible.

***Example:***  Say we try a line: $Y=10+5X$

We compute errors for all points → SSE = 1400.

Try another line:

$Y = 12 + 4X$

Compute errors → SSE = 700.

Try:

$Y=14+3.8X$

Compute errors → SSE = 690.

OLS finds the line with the **lowest** SSE.

---

### **2. Classification Problems**

**Goal:** To predict a *categorical* label for $Y$

The most famous and fundamental model here is **Logistic Regression**.

*Logistic Regression **is a multivariate statistical model** when it is used with multiple independent variables to predict a single dependent variable*

- **Warning (The Confusing Name):** Don't let the name fool you. Logistic **Regression** is a **Classification** algorithm.

The Solution: We use a new function, the logistic (or sigmoid) function, that "squashes" the output of a linear model into a valid probability (between 0 and 1).

> $P(Y=1) = \frac{1}{1 + e^{-(\beta_0 + \beta_1X_1 + \dots)}}$
> 

**The Model:**
1. The model first calculates a "score" just like linear regression: $z = \beta_0 + \beta_1X_1 + \dots$
2. It then feeds that score into the sigmoid function to get a probability: $P = \text{sigmoid}(z)$.
3. If $P > 0.5$, we "classify" it as **1 (Yes)**.
4. If $P < 0.5$, we "classify" it as **0 (No)**.**The Result:** The model doesn't just draw a line; it draws a **decision boundary** that separates the two classes.

**Why Linear Regression Doesn't Work for Yes/No Problems**

In mathematical theory, the line (or, more generally, hyperplane) produced by a linear regression model is **infinitely long** because it represents a function defined over all possible real numbers for the independent variables. The equation  $𝑌=𝛽_0+𝛽_1𝑋$ (for simple linear regression) is the equation of a straight line, which ***extends indefinitely in both directions*** of the X-axis in a theoretical, unbounded domain.

Imagine you're trying to predict: **"Will a student pass the exam?"** based on hours studied.

If you use **linear regression**, you're fitting a straight line through your data. The problem is:

- If someone studies 0 hours → the line might predict -0.3 (negative probability?)
- If someone studies 20 hours → the line might predict 1.8 (180% chance? )

**A straight line doesn't know when to stop!** It keeps going up and down forever, but probabilities **must** be between 0 and 1 (0% to 100%).

Think of it like this:

- You can't be "120% likely to pass"
- You can't be "-30% likely to pass"

That's what "the line reaches infinity" means — it doesn't have boundaries, but probabilities need boundaries.

**What is the Sigmoid Function and Why Does It Work?**

The **sigmoid function** is like a magic squasher. No matter what number you put in, it always spits out a number between 0 and 1.

Here's the formula again:

$\text{sigmoid}(z) = \frac{1}{1 + e^{-z}}$

**Where does it come from?**
It comes from something called the **logistic function**, which was originally used to model population growth (populations can't grow infinitely fast, they level off). Mathematicians noticed it's perfect for squashing any value into a 0-1 range.

**Why does it work?**

- When z is a big positive number (like +10) → $e^{-z}$ becomes tiny → sigmoid ≈ 1
- When z is a big negative number (like -10) → $e^{-z}$ becomes huge → sigmoid ≈ 0
- When $z=0$  → sigmoid = 0.5

It's shaped like an "S" curve that smoothly transitions from 0 to 1. Perfect for probabilities!

**Why Do We Use 0.5 as the Threshold?**

This is actually **arbitrary** (a choice we make), but it makes intuitive sense:

- If $P(Y=1)=0.7$ → There's a 70% chance it's "Yes" → Predict Y**es**
- If $P(Y=1)=0.3$ → There's only 30% chance it's "Yes" → Predict **No**
- If  $P(Y=1)=0.5$ → It's a coin flip, 50-50

**BUT** you can change this! Sometimes in real problems:

If you're predicting cancer (and missing cancer is really bad), you might use 0.3 as your threshold

Summary: 

- **Linear regression** draws a line that goes to infinity → bad for Yes/No because probabilities must be 0-1
- **Sigmoid function** squashes any number into 0-1 range → perfect for probabilities
- **0.5 threshold** is just a sensible default (we predict "Yes" when probability > 50%)

**Question: If linear regression is a infinite line then why does it work for example such as predicting house price from different betas (square foot, distance from city, rooms count)?**

House prices **can** theoretically go to very high or very low values. A house could be $100,000 or $10,000,000 or even higher. There's no strict upper limit (billionaires' mansions can cost $100M+). There's no strict lower limit either (though practically, houses don't cost $0)

**The infinite line is OKAY here** because, We're predicting a **continuous value** (any number). But

For Yes/No Problems (Logistic Regression), The answer **must** be a probability between 0 and 1.

---

### Principal Components Analysis (PCA)

**PCA** is a technique used for **Dimensionality Reduction**.

**The Problem**: Too Many Variables → the "Multivariate Models" we just discussed, you might have a dataset with **100 different input variables** ($X_1$ to $X_{100}$).
• It’s hard to visualize (you can't draw a 100-dimensional graph).
• It’s computationally heavy.
• Many variables might be redundant (e.g., if you have "age in years" and "age in months," they tell you the exact same thing).

**The Solution: PCA**

PCA takes your original set of messy, correlated variables and transforms them into a smaller set of **new** variables (called **Principal Components**) that are:

1. **Uncorrelated:** They don't repeat information.
2. **Ranked:** The first component (PC1) holds the *most* information, the second (PC2) holds the next most, and so on.

**The Intuition: "The Best Angle"**

Imagine you are holding a 3D object (like a teapot) and you want to take a **2D photograph** that captures as much detail as possible.

- If you take the photo from the top, it might just look like a circle (bad angle, lost information).
- If you take it from the side, you see the spout, handle, and body (good angle, high information).

PCA effectively rotates the dataset in high-dimensional space to find that "best angle" where the data is most spread out (has the highest variance).

> In PCA we **Standardize** the Data, so everyone is on the same page
> 

### **Working of Principal Component Analysis PCA**

1. **Standardize the Data:** Scale all variables so they have a mean of 0 and variance of 1. discussed above).
2. **Compute the Covariance Matrix:** This matrix describes how every variable relates to every other variable.
    1. 

The covariance matrix is a table that shows **how each variable relates to every other variable**.

1. **Calculate Eigenvectors and Eigenvalues:** This is the linear algebra magic.
2. **Eigenvectors:** These point in the *directions* of the new axes (the Principal Components).
3. **Eigenvalues:** These tell you the *magnitude* or **importance** of each direction. A high eigenvalue means that component explains a lot of variance.
4. **Select Top Components:** If you want to reduce your data to 2 dimensions, you pick the 2 eigenvectors with the highest eigenvalues.
5. **Project:** You "project" your original data onto these new axes.

**step1: Explained - Why do we Standardize?**

**The Problem:**  Because The Problem is that : Big Numbers Dominate

Imagine you're analyzing employees and you have two features:

```
Employee.  Age (years)  Salary (dollars)
----------------------------------------
Alice       25            50,000
Bob         30            60,000
Charlie     35            70,000
```

Now, when PCA tries to find patterns in this data, it looks at how much each variable varies.

The issue: Age varies from 25 to 35 → difference of 10 and Salary varies from 50,000 to 70,000 → difference of 20,000

Salary has **much bigger numbers**, so PCA thinks: *"Wow, salary is way more important! It varies SO much more than age!"*

But that's **not true**! The salary numbers are just bigger because we measured it in dollars instead of thousands of dollars. The actual **importance** of age vs salary shouldn't depend on the units we chose.

PCA is trying to find directions of **maximum variance** (maximum spread/variation) in the data.

So what we can do is we standardize i.e convert all of them to 1 single unit.

The solution: Standardization

**Standardization** means transforming each variable so that:

- **Mean = 0** (center it)
- **Variance = 1** (scale it)

The formula is:

$z = \frac{x - \text{mean}}{\text{standard deviation}}$

Converts everything to "how many standard deviations away from the mean”, Now both Age and Salary are measured on the **same scale**

*Before standardization:*

- Age: 25, 30, 35 → range of 10
- Salary: 50k, 60k, 70k → range of 20,000

*After standardization:*

- Age: -1, 0, 1 → range of 2
- Salary: -1, 0, 1 → range of 2

**step 2. Explained - Compute the Covariance Matrix**

**What is it?**
The covariance matrix is a table that shows **how each variable relates to every other variable**.
Imagine you have 3 variables: Height, Weight, and Age.

The covariance matrix looks like:

![](https://i.ibb.co/zWfJwGCL/image.png)

What does it tell you?

- **Diagonal elements (like var(H))**: How much that variable varies by itself
- **Off-diagonal elements (like cov(H,W)**): How two variables move together
    - Positive covariance: When Height increases, Weight tends to increase
    - Negative covariance: When Height increases, something else tends to decrease
    - Zero covariance: No relationship
    - Why we need this matrix? PCA needs to understand the relationships between all variables to find new directions that capture the most information.

**step 3. Explained - Calculate Eigenvectors and Eigenvalues**

**Eigenvectors: The New Directions**

Think of your data as a cloud of points in space. The eigenvectors are **the directions through this cloud that capture the most spread**.
Imagine a football (American football, oval-shaped):

- The **longest direction** (tip to tip) is the 1st eigenvector
- The **second longest direction** (side to side) is the 2nd eigenvector
- The **shortest direction** (thin edge) is the 3rd eigenvector

These are the **natural axes** of your data.

**Eigenvalues: The Importance**

The eigenvalue tells you **how much variance (spread) exists in that direction**.

- **High eigenvalue** = Lots of data spread in that direction = Important! we choose this as a principle component
- **Low eigenvalue** = Very little data spread = Not important

**step 4. Explained - Visualization of result**

If you plot the result, PC1 will be the x-axis and PC2 will be the y-axis.

- **PC1 (1st Principal Component):** The direction where the data varies the most. It captures the "main signal."
- **PC2 (2nd Principal Component):** The direction perpendicular (orthogonal) to PC1 that captures the next most variance.

PCA is the bridge between **Multivariate Models** and **Overfitting**

> If you try to run a regression on 1,000 variables, your model will likely fail or hallucinate patterns. By using PCA first, you can reduce those 1,000 variables down to maybe 10 Principal Components that contain 95% of the information, making your model faster and more robust.
> 

---

### **The problem of overfitting and model assessment**

If you build a model that works perfectly in the lab but fails miserably in the real world, the culprit is almost always **Overfitting**.

**1. The Core Problem: Overfitting vs. Underfitting**

Imagine you are studying for an exam.

- **Scenario A (Underfitting):** You barely study. You look at the book for 5 minutes. You miss the key concepts. You fail the exam.
- **Scenario B (Good Fit):** You understand the *logic* and *principles*. You can solve new problems you haven't seen before because you learned the underlying patterns.
- **Scenario C (Overfitting):** You memorize the *exact answers* to the practice test questions. You get 100% on the practice test. But when the real exam has slightly different numbers, you fail completely.

**Overfitting** is when your model **memorizes the noise** in the training data instead of learning the underlying signal.

**Underfitting (High Bias):** The model is too simple (e.g., fitting a straight line to curved data). It performs poorly on both training and testing data.

**Overfitting (High Variance):** The model is too complex. It performs *perfectly* on training data (low error) but *terribly* on new, unseen data (high error).

**2. Model Assessment: How do we catch this?**

we need a rigorous way to "assess" our model.

The Golden Rule of Machine Learning is **Data Splitting** i.e never train on all our data. We split it into:

1. **Training Set (~70-80%):** Used to teach the model.

2. **Testing Set (~20-30%):** Used to *assess* the model. The model is strictly forbidden from seeing this data during training.

**The "U-Shape" of Error:** If we plot the error rate as the model gets more complex:

**Training Error** always goes **DOWN**. (You can always memorize more). **Testing Error** goes down at first, but then **SHOOTS UP**. he point where the Testing Error starts rising is the exact moment **Overfitting** begins.

**3. Techniques for Assessment and Prevention**

***A. Cross-Validation (The Standard):*** 

Instead of just one Train/Test split, we do it multiple times.

- **k-Fold Cross-Validation:** Split data into $k$ parts (e.g., 5). Train on 4 parts, test on the 5th. then reset and erase whatever it learned from previous round and then with next round train on next 4 parts and use remaining part as testing data, rotate this 5 times so every part gets a turn being the "test" set. Average the success rate.
This gives a much more robust assessment of how the model will perform in the wild.
    - Why do we do this ? Once you've decided which model/parameters are best (using cross-validation), you then: **Train ONE final model on ALL your data** (all 5 folds combined)

***B. Regularization (The Fix)***

If a model is overfitting, we punish it for being too complex. We add a "penalty" term to our cost function.
• **Lasso (L1) and Ridge (L2) Regression:** These techniques force the coefficients ($\beta$) to stay small. This simplifies the model and prevents it from chasing wild noise in the data.

**Regularization**

Remember our house price example? A complex model might learn:

`Price = 50 + 3×Size + 200×Bedrooms - 150×Distance + 80×Age + ...`

But what if the model starts doing this:

`Price = 50 + 3×Size + 9847×Bedrooms - 8234×Distance + 7123×Age + ...`

Those **huge coefficients** (9847, 8234, 7123) mean the model is being **too sensitive** to small changes in the data. It's chasing noise!

**Regularization says:** "Hey model, keep those coefficients small and reasonable!"

- Normal cost function (what we're trying to minimize):
    
    `Cost = Prediction Errors only`
    
- Regularized cost function:
    
    `Cost = Prediction Errors + Penalty for Large Coefficients`
    

The Two Types of ***Regularization Regression*** : Ridge (L2) and Lasso (L1)

**Ridge Regression (L2)**

> $Penalty = λ × (β₁² + β₂² + β₃² + ... )$
> 
- Squares all the coefficients and adds them up
- **Shrinks** all coefficients toward zero
- But doesn't make them exactly zero
- use this when all features are important

**Example:**
Before regularization:

`Price = 50 + 3000×Size + 5000×Bedrooms - 4000×Distance`

After Ridge:

`Price = 50 + 30×Size + 50×Bedrooms - 40×Distance`

(All coefficients got smaller, but they're all still there)

**Lasso Regression (L1)**

Penalty formula:

> $Penalty = λ × (|β₁| + |β₂| + |β₃| + ... )$
> 

What it does:

- Takes absolute values of coefficients and adds them up
- ***Forces some coefficients to become exactly zero***
- Effectively does automatic feature selection
- Removes unimportant features completely
- use this when there are lot of features in the equation, and some of them are not important

Example:
Before regularization:

`Price = 50 + 3000×Size + 5000×Bedrooms - 4000×Distance + 100×Color`

After Lasso:

`Price = 50 + 30×Size + 50×Bedrooms - 40×Distance + 0×Color`

(Color got eliminated completely! Lasso decided it's not important)

**The λ (Lambda) Parameter**

Both methods have a parameter **λ** (lambda) that controls how much penalty you apply:

$λ = 0$ (No Regularization)

`Cost = Prediction Errors only`

- No penalty
- Model can do whatever it wants
- Risk of overfitting

$λ = Small$ (Gentle Regularization)

`Cost = Prediction Errors + Small Penalty`

- Slight pressure to keep coefficients small
- Model still has freedom

$λ = Large$ (Strong Regularization)

`Cost = Prediction Errors + Big Penalty`

- Heavy pressure to keep coefficients small
- Model becomes very simple
- Risk of underfitting

---
<i>next up: unit 4</i>