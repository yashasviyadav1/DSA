# Formula Sheet for Mathematics Foundation of Computer Science 
### Unit-1
1. Random Variable
    - Discrete Random Variable
        - Probability Mass Function - $f_X(k) = P(X = k)$
    - Continuous Random Variable
        - Probability Density Function - $P(a \le X \le b) = \int_{a}^{b} f_X(x) dx$
2. Probability Mass Function - (PMF)
    1. Bernoulli Distribution - One simple event and 2 outcomes
        1. $P(X = k) = \begin{cases} p & \text{if } k = 1 \\ 1 - p & \text{if } k = 0 \end{cases}$
    2. Binomial Distribution - n events simultaneously - coin toss n times 
        1. $P(X = k) = \binom{n}{k} p^k (1-p)^{n-k}$
    3. Poisson Distribution - given average rate of events, whats prob of having k events 
        1.  $P(X = k) = \frac{\lambda^k e^{-\lambda}}{k!}$

1. Probability Density Function - (PDF)
    1. The Exponential Distribution - given average rate of event, whats time duration between events or how much time will take for next event to happen
        1.  PDF func: $f(x) = \lambda e^{-\lambda x}$
        2. Since PDF is just curve we need prob (are of curve from a to b) which is too hard to find with that formula so we use easier formula (pre calculated formulas)
            1. $P(X \le x) = 1 - e^{-\lambda x}$.  (this is also CDF)
            2. $P(X > x) = e^{-\lambda x}$
    2. Normal Distribution → bell shape → gaussian
        1.  Z score: $z = \frac{x - \mu}{\sigma}$
        2. 68-95-99.7 Rule
        3. Central Limit Theorm

1. Cumulative Distribution Function - master function for PMF and PDF
    1. prob of X being less then or equal to x - $F(x) = 1 - e^{-\lambda x}$
    2. CDF for discrete var is the sum
        1.  $F_k(x) = \sum_{k \le x} P(X=k)$
    3. CDF for continuous variable is integral
        1. $F(x) = \int_{-\infty}^{x} f(t) dt$
    4. most powerfull use of CMF: PDF(a ≤ x ≤ b) = CDF(b) - CDF(a)
        1. $P(a < X \le b) = F(b) - F(a)$

1. Expected Value $E[X]$ - It's a weighted average
    1. For discrete var:  $E[X] = \sum_{x} x \cdot P(X=x)$
    2. For Continuous var: $E[X] = \int_{-\infty}^{\infty} x \cdot f(x) dx$
    3. relation of $\lambda$ and Expected value: $E[X] = 1/λ$

1. Variance ($\sigma^2$) - Variance is "the expected value of the squared deviation from the mean.”
    1. $Var(X) = E[(X−μ)^2]$
    2. better computational formula:  $Var(X) = E[X^2] - (E[X])^2$
    3. **For Discrete:** $Var(X) = \sum_{x} (x - \mu)^2 \cdot P(X=x)$
    4. **For Continuous:** $Var(X) = \int_{-\infty}^{\infty} (x - \mu)^2 \cdot f(x) dx$

1. Variance connection with Sigma (Spread)
    1. $\sigma = \sqrt{Var(X)}$

1. Conditional Expectation $E[X∣Y ]$
    1. Discrete Case
        1. Normal Expected Value: $E[Y] = \sum_y y \cdot P(Y=y)$.
        2. Conditional Expectation: $E[Y | X=x] = \sum_y y \cdot P(Y=y | X=x)$
    2. Continuous Case:
        1. Normal EXpected value: $E[Y] = \int y \cdot f(y) dy$
        2. Conditional Expectation: $E[Y | X=x] = \int_{-\infty}^{\infty} y \cdot f_{Y|X}(y|x) dy$
        
2. Central Limit Theorem - CLT
    1. The Same Mean of sample distribution has same mean as actual mean of population: $E[\bar{X}] = \mu$
    2. *The variance of the sample mean is smaller than the variance of the population.
    $Var(\bar{X}) = \frac{\sigma^2}{n}$*
    3. standard error or standard deviation of our new bell curve : $\sigma_{\bar{X}} = \sqrt{Var(\bar{X})} = \frac{\sigma}{\sqrt{n}}$
    4. Z score : $\frac{\bar{x} - \mu_0}{\sigma/\sqrt{n}}$

1. Confidence Interval using CLT - univariate
    1. $\text{C.I.} = \bar{x} \pm z_{\alpha/2} \cdot \left(\frac{\sigma}{\sqrt{n}}\right)$

1. Multivariate Central Limit Theorm (CLT)
    1. The "Mean" is now a "Mean Vector” → $\boldsymbol{\mu} = \begin{bmatrix} \mu_{\text{height}} \\ \mu_{\text{weight}} \end{bmatrix} = \begin{bmatrix} 175 \\ 75 \end{bmatrix}$
    2. The "Variance" is now a "Covariance Matrix” → 
        
        $\boldsymbol{\Sigma} = \begin{bmatrix} \text{Var}(\text{Height}) & \text{Cov}(\text{Height, Weight}) \\ \text{Cov}(\text{Weight, Height}) & \text{Var}(\text{Weight}) \end{bmatrix}$
        

1. Probabilistic Inequalities: is used when we our sample is < 30 (not good for normal distribution) so we don’t know which distibution is our sample in. So these inequalities give higher bound or worst case possibility of something
    1. Markov's Inequality (uses Exp value) → whats prob of random value X being ≥ a
        1. $P(X \ge a) \le \frac{E[X]}{a}$
    2. Chebyshev's Inequality (uses mean & variance) → whats max prob of X being k standard daviations away from mean
        1. Form1: $P(|X - \mu| \ge k) \le \frac{\sigma^2}{k^2}$
        2. Form2: $P(|X - \mu| \ge k\sigma) \le \frac{1}{k^2}$

1. Markov Chains: model for system that moves between:
    1. A Set of States ($S$)
    2. A Transition Matrix ($P$)
    3. $v_n = v_0 \cdot P^n$
    4. Equilibrium: $π=πP$

### Unit-2

1. Method of Moments - equating estimates - A sample's properties should look like the population's properties
2. Maximum Likelihood Estimation (MLE) - choose the p that gives the highest probability of the observed data.

### Unit-3

1. Statistical Inference - using sample data to make conclusions about a population
    1. Null Hypothesis ($H_0$)
    2. Alternative Hypothesis ($H_a$ or $H_1$)
    3. Reasonable Doubt ($\alpha$)

1. multivariate statistical models: Regression and classification problems
2. Regression → predict house price (continuos)
    1. Simple Linear Regression (univariate) → $Y= β_0 +β_1 X + ϵ$
    2. Multiple Linear Regression (multivariate) → 
3. Classification → predict yes or no (discrete)
    1. Logistic Regression (using sigmoid function) → $P(Y=1) = \frac{1}{1 + e^{-(\beta_0 + \beta_1X_1 + \dots)}}$
    2. here sigmoid function → $P = \text{sigmoid}(z)$ = $\text{sigmoid}(z) = \frac{1}{1 + e^{-z}}$
    
4. Principal Components Analysis (PCA)
    1. Standardize the data
    2. compute the covariance matrix
    3. find eigen vectors and eigen values
    4. Select Top Components
    5. project

1. overfitting
    1. ways to tackle overfitting
        1. Data Splitting
        2. k-Fold Cross-Validation
        3. Regularization
            1. Ridge Regression (L2)
            2. Lasso Regression (L1)

### Unit-4

1. Isomorphism
2. Planar
- Euler formula for planar graph = V - E + R = 2
1. Non Planar
2. Coloring
3. Euler Cycle → cover each edge exactly onces and come back
    1. happens when all verticies have even degree
    
    Euler Path → cover each edge exactly once (not come back)
    
    - happens when there are 2 odd degree vertex
    
    Hamilton Circuits → cpver each vertex exactly once and come to start
    
4. Permutation - arrange, order matters
    1. Permutation without repetition →  $P(n, r) = \frac{n!}{(n-r)!}$
    2. Permutation with repetition → $n^r$
        - n is here the distinct things from which we can choose eg. (0,1 bit)
        - r is the no of places we need to place them on (eg. 8 bit string length)
    3. Indistinguishable Objects: $\frac{n!}{n_1! \cdot n_2! \cdot ...}$

1. Combination → selection, group, order does’nt matter
    1. Combination without repetition → $C(n, r) = \binom{n}{r} = \frac{n!}{r!(n-r)!}$
    2. Combination with repetition → $C(n + r - 1, r)$