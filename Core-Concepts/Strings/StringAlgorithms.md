
# **String Algorithms**:- 

For Pattern Searching :
- Bruteforce pattenr searching
- Boyer Moree Algorithm (BM)
- Knuth-Morris-Pratt Algo  (KMP)

---
---
---
## **Bruteforce pattern searching**

takes n*m time where n is length of text and m is length of pattern
iterate 1 by 1 every char and go to m length to match it

```java
public int strStr(String haystack, String needle) {
    int n = haystack.length(), m = needle.length();
    if(m > n) return -1;
    for(int i=0; i <= n - m; i++){
        int j = 0;
        while(j < m && haystack.charAt(i+j) == needle.charAt(j)){
            j++;
        }
        if(j == m){
            return i;
        }
    }
    return -1;
}

```

---
---
---

## **Boyer Moree Algorithm**

The **Boyer–Moore algorithm** is one of the most efficient string-searching algorithms in practice. Its time complexity depends on the case:

1. **Best Case Complexity**

- **O(n/m)**
    - Here `n` is the length of the text and `m` is the length of the pattern.
    - This happens when the alphabet is large, and mismatches occur quickly (because the pattern shifts by large jumps using the **bad character** or **good suffix** heuristics).
    - Example: searching for `"abcd"` in `"zzzzzzzzzzabcd"`.

---

2. **Worst Case Complexity**

- **O(n·m)**
    - Occurs rarely, when the heuristics don’t help much (e.g., when the text and pattern consist of repeated characters like `"aaaaaaaaaaa"` and `"aaaaa"`).
    - In such cases, the algorithm may check almost every character multiple times.

---

3. **Average Case Complexity**

- **O(n/m + m)** ≈ **O(n)**
    - This is why Boyer–Moore is considered very efficient in practice.
    - On average, it skips many characters instead of checking them one by one, outperforming algorithms like **Naïve** (O(n·m)) and **KMP** (O(n+m)) in most practical scenarios.

**Text:** `HEXALXAIMALXAMAHE` (length = 17)

**Pattern:** `MALXA` (length = 5)

### *Step 1: Bad Character Table Computation*

The bad character table stores the rightmost occurrence of each character in the pattern (excluding the last position).

For pattern `MALXA`:

- Position indices: M(0), A(1), L(2), X(3), A(4)
- We ignore the last character A(4) for bad character table

| Character | Last Occurrence Index | Bad Character Value |
| --- | --- | --- |
| M | 0 | 0 |
| A | 1 | 1 |
| L | 2 | 2 |
| X | 3 | 3 |
| Others | -1 | -1 |

**Bad Character Rule:** When a mismatch occurs at pattern[j] with text[i], we can shift the pattern so that the rightmost occurrence of text[i] in the pattern aligns with text[i].

in below eg. A != G (so A is bad character) so search for rightmost occurance of A in pattern (ignoring last index), another occurance is found at index 1 (in pattern), index of bad char is 3 (in text) so shift -> 3 - 1 = 2 steps to right 
<img width="1000" height="504" alt="image" src="https://github.com/user-attachments/assets/7341451a-ccd6-4236-8d37-6829a7379ff7" />


### *Step 2: Good Suffix Table Computation (Complete Implementation)*

The good suffix table has ***TWO rules:***

note :  good suffix is the suffix of the text which is common in both text and string as suffix. eg. AB is common in both the Text and Pattern window (green)

```java
Rule 1: Find the rightmost occurrence of the suffix elsewhere in the pattern
				-> once found that align this new occurrence of the suffix present in text with the suffix of the pattern (basically shifting)
				-> eg. in the below image good suffix T[3,4] = AB is found again in the pattern at P[1,2] = AB so we will align this new Ab
					 with the text by shifting 2 positions to right (because in text suffix AB start at index 3 and in pattern suffix AB start at
					 index 1 so shift = 3 - 1 => 2 steps
```

![image.png](https://i.ibb.co/0VGZcQS4/image.png)

*I→ MP : Good suffix found : eg. above A ≠ B but there is good suffix AB, and it is again found from index P[1:2] so we shift it*

```java

Rule 2: If Rule 1 fails, find the longest prefix of the pattern that matches a suffix of the good suffix
				-> eg. since in picture 2 the : A of Text != B of Pattern so we search good suffix (BAB) in pattern but could not found,
					 so other suffix of good suffix BAB are : BAB, AB, B......now in pattern there are prefixes : A, AB, ABB, ABBA, ABBAB
					 so in the good suffix there is smaller suffix AB which is common as prefix of pattern, so we align AB of pattern with
					 good suffix of the text so index of AB : 3 (in text) and index of AB: 0 (in pattern) i.e steps : 3 - 0 : **3 steps**
```

![image.png](https://i.ibb.co/GvFszrVL/image.png)

*|→ Good suffix fallback : A ≠ B but in good suffix (BAB) a part of good sufix is found i.e AB is found as prefix of pattern* 

so we shift it to align it 

For pattern `MALXA`:

**Detailed Good Suffix Analysis:**

**Position 4 (j=4):** Suffix = "" (empty)

- Empty suffix → shift = 1

**Position 3 (j=3):** Suffix = "A"

- Rule 1: "A" appears at position 1 in pattern → shift = 4-1 = 3 ✓

**Position 2 (j=2):** Suffix = "XA"

- Rule 1: "XA" doesn't appear elsewhere in pattern
- Rule 2: Check if any prefix of pattern matches suffix of "XA":
    - Does "M" match suffix "A"? No
    - Does "MA" match suffix "XA"? No
- No fallback found → shift = 5 (pattern length)

**Position 1 (j=1):** Suffix = "LXA"

- Rule 1: "LXA" doesn't appear elsewhere in pattern
- Rule 2: Check prefixes against suffixes of "LXA":
    - Does "M" match "A"? No
    - Does "MA" match "XA"? No
    - Does "MAL" match "LXA"? No
- No fallback found → shift = 5

**Position 0 (j=0):** Suffix = "ALXA"

- Rule 1: "ALXA" doesn't appear elsewhere in pattern
- Rule 2: Check prefixes against suffixes of "ALXA":
    - Does "M" match "A"? No
    - Does "MA" match "XA"? No
    - Does "MAL" match "LXA"? No
    - Does "MALX" match "ALXA"? No
- No fallback found → shift = 5

### Good Suffix Table:

| Position j | Suffix | Rule Applied | Good Suffix Shift |
| --- | --- | --- | --- |
| 4 | "" | Default | 1 |
| 3 | "A" | Rule 1 | 3 |
| 2 | "XA" | Rule 2 (fail) | 5 |
| 1 | "LXA" | Rule 2 (fail) | 5 |
| 0 | "ALXA" | Rule 2 (fail) | 5 |

### *Example Where Rule 2 Would Apply:*

If pattern was `ABCAB` and we had suffix "AB":

- Rule 1: "AB" at end doesn't appear elsewhere
- Rule 2: Prefix "AB" matches suffix "AB" of the good suffix → smaller shift

Step 3: Dry Run - Pattern Matching

### Initial Setup:

```
Text:    H E X A L X A I M A L X A M A H E
Index:   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
Pattern:         M A L X A
Pattern Index:   0 1 2 3 4
Text Index:      4 5 6 7 8

```

Step 1: First Alignment (Text index 4-8)

**Comparison:** Start from rightmost character of pattern

- Pattern[4] = 'A' vs Text[8] = 'I' → **MISMATCH**
- Character 'I' is not in our bad character table → Bad char shift = 5
- No good suffix (first comparison) → Good suffix shift = 1
- **Take maximum shift = max(5, 1) = 5**

```
After shift by 5:
Text:    H E X A L X A I M A L X A M A H E
Index:   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
Pattern:                     M A L X A
Pattern Index:               0 1 2 3 4
Text Index:                  9 10 11 12 13

```

**Step 2: Second Alignment (Text index 9-13)**

**Comparison from right:**

- Pattern[4] = 'A' vs Text[13] = 'M' → **MISMATCH**
- Character 'M' is in bad character table at position 0
- Bad char shift = 4 - 0 = 4
- No good suffix → Good suffix shift = 1
- **Take maximum shift = max(4, 1) = 4**

```
After shift by 4:
Text:    H E X A L X A I M A L X A M A H E
Index:   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
Pattern:                         M A L X A
Pattern Index:                   0 1 2 3 4
Text Index:                      13 14 15 16 17(out of bounds)

```

**Step 3: Third Alignment (Text index 13-17)**

**Text index 17 is out of bounds, so we stop here.**

Let me also show what would happen if we had a match:

Alternative Example - If we had a match at position 9:

```
Text:    H E X A L X A I M A L X A M A H E
                         M A L X A

```

**Comparison from right:**

- Pattern[4] = 'A' vs Text[13] = 'M' → MISMATCH (as shown above)

**But let's say the text was different and we had:**

```
Text:    H E X A L X A I M A L X A A L X A
Pattern:                     M A L X A

```

Then we'd have:

- Pattern[4] = 'A' vs Text[13] = 'A' → **MATCH**
- Pattern[3] = 'X' vs Text[12] = 'X' → **MATCH**
- Pattern[2] = 'L' vs Text[11] = 'L' → **MATCH**
- Pattern[1] = 'A' vs Text[10] = 'A' → **MATCH**
- Pattern[0] = 'M' vs Text[9] = 'M' → **MATCH**

**PATTERN FOUND at position 9!**

Summary of Boyer-Moore Efficiency

The algorithm's power comes from:

1. **Right-to-left scanning** - Often eliminates many characters with single comparison
2. **Bad character rule** - Skips positions where pattern characters can't possibly match
3. **Good suffix rule** - Uses information from partial matches to skip more positions

In our example, instead of checking every position (naive approach would need 13 comparisons), Boyer-Moore eliminated large chunks of text with just 2 mismatches, demonstrating its efficiency especially for longer patterns and texts.

Key Points:

- Always compare from right to left within each alignment
- Take the maximum of bad character and good suffix shifts
- Bad character shift can be negative (when character appears to the right), so we use max(1, bad_char_shift)
- The algorithm excels when the alphabet is large and pattern is long

---
---
---



## **Knuth Morris Pratt (KMP) Algorithm**

We want to find all occurrences of a pattern `P` (length *m*) inside a text `T` (length *n*).

The simplest approach is **brute force pattern matching**:

- Start aligning pattern at every position in text.
- Compare characters one by one until either mismatch or full match.
- Worst-case: **O(n·m)** (e.g., text = `aaaaaaa…`, pattern = `aaaab`).

This is too slow for large inputs.

**Trade-off that KMP Overcomes**

KMP was designed to **eliminate unnecessary re-checking of characters**.

- In brute force, if a mismatch happens, you might restart matching from the next character in text, even though some prefix of the pattern was already matched (wasted effort).
- KMP avoids this waste by remembering how much of the pattern has already matched using a **failure function (LPS = Longest Prefix Suffix array)**.

So the **trade-off** is:

- Extra preprocessing time **O(m)** and memory **O(m)** for building the LPS array.
- But searching becomes **O(n)** instead of **O(n·m)**.

Essentially, KMP trades **preprocessing cost** for **faster searching**.

### What is LPS (Longest prefix suffix) ?

For each position `i` in the pattern, **LPS[i]** = length of the **longest proper prefix** of `pattern[0..i]` which is also a suffix of `pattern[0..i]`.

- **Prefix**: substring that starts from the beginning.
- **Suffix**: substring that ends at the end.
- **Proper** means we don’t take the whole string itself.

LPS tells us: *“If a mismatch happens at position i, how far back can we shift while reusing already matched characters?”*

---

### Algorithm to Build LPS

We maintain:

- `len` = length of the longest prefix-suffix found so far.
- `i` = current index in the pattern.

Steps:

1. Start with `LPS[0] = 0` (a single char has no proper prefix/suffix).
2. For each `i` from 1 to m-1:
    - If `pattern[i] == pattern[len]` → extend current prefix → `len++`, set `LPS[i] = len`.
    - Else:
        - If `len > 0` → shrink length → `len = LPS[len-1]` (try shorter prefix).
        - If `len == 0` → no match → `LPS[i] = 0`.

---

## 🔹 Example Walkthrough

Pattern = `A B A B C A B A B`

Initialize:

- LPS[0] = 0
- `len = 0`, `i = 1`

---

### Step-by-step:

1. **i=1, P[1]=B, P[len=0]=A** → mismatch, len=0 → LPS[1]=0
2. **i=2, P[2]=A, P[len=0]=A** → match → len=1 → LPS[2]=1
3. **i=3, P[3]=B, P[len=1]=B** → match → len=2 → LPS[3]=2
4. **i=4, P[4]=C, P[len=2]=A** → mismatch
    - len>0 → len=LPS[len-1]=LPS[1]=0
    - now len=0, mismatch again → LPS[4]=0
5. **i=5, P[5]=A, P[len=0]=A** → match → len=1 → LPS[5]=1
6. **i=6, P[6]=B, P[len=1]=B** → match → len=2 → LPS[6]=2
7. **i=7, P[7]=A, P[len=2]=A** → match → len=3 → LPS[7]=3
8. **i=8, P[8]=B, P[len=3]=B** → match → len=4 → LPS[8]=4

Final LPS = `[0, 0, 1, 2, 0, 1, 2, 3, 4]`

### Idea Behind KMP

The key observation:

When a mismatch occurs at `pattern[j]`, we don’t need to start from scratch.

- Some prefix of the pattern has already matched the suffix of what we’ve just seen.
- Use the **LPS array** (longest proper prefix that is also a suffix) to decide where to continue in the pattern, without rechecking characters in text.

Example:

Text = `ABABABC`

Pattern = `ABABC`

While matching, if mismatch occurs after matching `ABAB`, KMP says:

➡️ “You don’t need to restart from beginning; you already know the first two chars match, so shift pattern intelligently.”

***Question*** [IMP] - when 2 chars mismatch, why do we shift 1 some steps back ? Should’t we just place the leftmost pointer to the 0th index when there is mismatch ?

Answer : Why simply setting `len=0` is wrong? If you do `len=0` directly, you are **throwing away useful information** about possible shorter prefix-suffixes.

The `lps[len-1]` step says: 

> “Okay, the prefix of length `len` didn’t work, but maybe a shorter prefix (captured in `lps[len-1]`) still works.”
> 

This recursive fallback is what finds *all* valid prefix-suffix lengths.

If you just zero it, you’ll miss these cases.

computing the LPS - longest prefix suffix table for KMP

Counterexample (where your method fails) : 

Take pattern:

```
P = AAACAAAA
```

We’ll compute LPS manually.

---

### Using Correct Method (with fallback `len = lps[len-1]`)

1. i=0 → lps[0]=0
2. i=1 (`A==A`) → lps[1]=1, len=1
3. i=2 (`A==A`) → lps[2]=2, len=2
4. i=3 (`C != A`):
    - mismatch, len=2 → fallback `len=lps[1]=1`
    - still mismatch (`C != A`), fallback again `len=lps[0]=0`
    - finally lps[3]=0

... continue → at the end we get:

LPS = `[0,1,2,0,1,2,3,4]`

---

### Using Your Method (direct `len=0` on mismatch)

At i=3 (`C != A`), you’d **immediately reset len=0** without fallback.

Now when continuing further, you’d lose the information about overlapping `"AAA"` at the end.

You’d eventually compute:

LPS (wrong) = `[0,1,2,0,1,0,1,0]`

Notice the last entries are **all wrong**.

---

Why this matters ? 

Later, in the **search phase**, the wrong LPS will cause you to restart from scratch too often → O(n·m) instead of O(n+m).

In our example:

- Correct LPS says `"AAAA"` is both prefix and suffix.
- Wrong LPS (with len=0) says “nah, nothing matches”, so you throw away the `"AAAA"` info.

That’s exactly the efficiency loss.

---

### Dry Run KMP with example :-

**Step 1: Compute the LPS table** for Pattern `P = ABABCABAB`

We build LPS (longest prefix which is also a suffix).

Pattern:

```
Index:   0 1 2 3 4 5 6 7 8
Char:    A B A B C A B A B
```

We initialize:

- `lps[0] = 0` always
- Variables: `len = 0`, `i = 1`

Now compute:

1. `i=1, P[1]=B, P[len=0]=A` → mismatch → `lps[1]=0`, `i=2`
2. `i=2, P[2]=A, P[len=0]=A` → match → `len=1`, `lps[2]=1`, `i=3`
3. `i=3, P[3]=B, P[len=1]=B` → match → `len=2`, `lps[3]=2`, `i=4`
4. `i=4, P[4]=C, P[len=2]=A` → mismatch → fallback `len=lps[1]=0` → mismatch again → `lps[4]=0`, `i=5`
5. `i=5, P[5]=A, P[len=0]=A` → match → `len=1`, `lps[5]=1`, `i=6`
6. `i=6, P[6]=B, P[len=1]=B` → match → `len=2`, `lps[6]=2`, `i=7`
7. `i=7, P[7]=A, P[len=2]=A` → match → `len=3`, `lps[7]=3`, `i=8`
8. `i=8, P[8]=B, P[len=3]=B` → match → `len=4`, `lps[8]=4`, `i=9` (done)

✅ LPS Table:

```
Index:   0 1 2 3 4 5 6 7 8
Char:    A B A B C A B A B
LPS:     0 0 1 2 0 1 2 3 4
```

---

**Step 2: KMP Search**

Text `T = ABABDABACDABABCABAB` (length 19)

Pattern `P = ABABCABAB` (length 9)

We maintain:

- `i` → index in Text
- `j` → index in Pattern

---

**Iteration dry run**

1. `i=0, j=0`: `T[0]=A`, `P[0]=A` → match → `i=1, j=1`
2. `i=1, j=1`: `T[1]=B`, `P[1]=B` → match → `i=2, j=2`
3. `i=2, j=2`: `T[2]=A`, `P[2]=A` → match → `i=3, j=3`
4. `i=3, j=3`: `T[3]=B`, `P[3]=B` → match → `i=4, j=4`
5. `i=4, j=4`: `T[4]=D`, `P[4]=C` → mismatch → fallback → `j=lps[3]=2` (don’t move `i`)
6. `i=4, j=2`: `T[4]=D`, `P[2]=A` → mismatch → fallback → `j=lps[1]=0`
7. `i=4, j=0`: mismatch → move `i=5`
8. `i=5, j=0`: `T[5]=A`, `P[0]=A` → match → `i=6, j=1`
9. `i=6, j=1`: `T[6]=B`, `P[1]=B` → match → `i=7, j=2`
10. `i=7, j=2`: `T[7]=A`, `P[2]=A` → match → `i=8, j=3`
11. `i=8, j=3`: `T[8]=C`, `P[3]=B` → mismatch → fallback `j=lps[2]=1`
12. `i=8, j=1`: `T[8]=C`, `P[1]=B` → mismatch → fallback `j=lps[0]=0`
13. `i=8, j=0`: mismatch → move `i=9`
14. `i=9, j=0`: `T[9]=D`, `P[0]=A` → mismatch → move `i=10`
15. `i=10, j=0`: `T[10]=A`, `P[0]=A` → match → `i=11, j=1`
16. `i=11, j=1`: `T[11]=B`, `P[1]=B` → match → `i=12, j=2`
17. `i=12, j=2`: `T[12]=A`, `P[2]=A` → match → `i=13, j=3`
18. `i=13, j=3`: `T[13]=B`, `P[3]=B` → match → `i=14, j=4`
19. `i=14, j=4`: `T[14]=C`, `P[4]=C` → match → `i=15, j=5`
20. `i=15, j=5`: `T[15]=A`, `P[5]=A` → match → `i=16, j=6`
21. `i=16, j=6`: `T[16]=B`, `P[6]=B` → match → `i=17, j=7`
22. `i=17, j=7`: `T[17]=A`, `P[7]=A` → match → `i=18, j=8`
23. `i=18, j=8`: `T[18]=B`, `P[8]=B` → match → `i=19, j=9`

`j == 9` → Pattern found at `i - j = 19 - 9 = 10`

**Final Answer**

Pattern `P = ABABCABAB` is found in Text `T` at ***index 10**.*

**Final Answer**:

- LPS table computation = **14 iterations**
- Pattern searching = **22 comparisons**
- **Total iterations ≈ 36**

This shows the efficiency: instead of 171 brute-force steps, *KMP solved it in 36 steps.* (text.len = 19, pattern.len = 9 almost took n+m time)

### Time comparision of Boyer Moore and KMP

**KMP - Knuth Morris Pratt Algo**

- **Worst-case time complexity:** `O(n+m)`
    - Builds LPS in O(m)O(m)O(m), then scans text in O(n)O(n)O(n).
- **Best-case time complexity:** `(n+m)`
- **Key point:** KMP is *deterministic*. It **guarantees** linear time in all cases (good for adversarial inputs).

**(BM) - Boyer–Moore**

- **Worst-case time complexity: `O(n*m)`** if pattern and text are repetitive
- **Best-case time complexity: `O(n/m)`** (almost sub-linear in practice).