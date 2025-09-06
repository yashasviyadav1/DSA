
# **String Algorithms**:- 

For Pattern Searching :
- Bruteforce pattenr searching
- Boyer Moree Algorithm (BM)
- Knuth-Morris-Pratt Algo  (KMP)

For String/Data Compression :- 
- Huffman coding Algorithm (encoding and decoding)

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


<b>What is a "good suffix"?</b>

> When we match some characters from the right but then mismatch, the matched part is called a "good suffix". We want to find how far we can shift the pattern so that:

*Very important :-*
> Case 1: The good suffix aligns with another occurrence of the same <b>*substring*</b> in the pattern, OR Case 2: 
> The good suffix aligns with a prefix of the pattern

*Explanation :-*
> CASE 1 Explained : note that i wrote 'substring' in the above sentence and not prefix which means if we have good suffix = "ABC" from text = "HFKAJS[ABC]" and pattern = "CDABC[ABC]" now this good suffix is ABC from the text, now we search for a substring ABC present somewhere in the pattern we found it in the pattern at index 2 to 4 at CD(ABC)ABC so we shift the pattern to its right by = 3 steps 
 
> Case 2 Explained : now we have good string "ABC" from the text = HFKAJS[ABC] and pattern = BCL[ABC] now in this case case 1 failed because we could not find good suffix abc in any other position in the pattern so rather then searching for substring abc in pattern, now we will search for any other suffix of ABC (suffixes : ABC, BC, C) that is present as prefix of our pattern (prefixes : B, BC, BCL, ....etc)  now since BC sufix of good sufix matches with BC prefix of pattern so we will align them so move by  3 steps 

```java
Rule 1: Find the rightmost occurrence of the suffix elsewhere as substring in the pattern
				-> once found that align this new occurrence of the suffix present in text with this substring of the pattern (basically shifting)
				-> eg. in the below image good suffix T[3,4] = AB is found again in the pattern as substring at : Pattern[1,2] = AB so we will align this new Ab
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


### Now For pattern `MALXA`:
**Detailed Good Suffix Table Computing Analysis:**

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

### ⭐ Full Dry Run with example for Boyer-Moore Algorithm

**Problem Setup**
- **Text (T)**: HEXALXAIMALXAMEHE (length = 17)
- **Pattern (P)**: MALXA (length = 5)

Position indices:
```
Text:    H E X A L X A I M A L X A M A H E
Index:   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

Pattern: M A L X A
Index:   0 1 2 3 4
```

## Preprocessing Phase

### 1. Bad Character Heuristic Table

For each character in the alphabet, we find the rightmost occurrence in the pattern (excluding the last position for shifts).

**Pattern analysis**: M A L X A (indices 0,1,2,3,4)
- M: rightmost at index 0
- A: rightmost at index 1 (we have A at indices 1,4 but exclude last position 4)
- L: rightmost at index 2  
- X: rightmost at index 3
- Other characters: not present (-1)

**Bad Character Table**:
```
Character | Rightmost Index in Pattern
---------|-------------------------
M        | 0
A        | 1  
L        | 2
X        | 3
Others   | -1
```

**Bad Character Shift Formula**: 
shift = max(1, j - badChar[T[i+j]])
where j is the position of mismatch in pattern, T[i+j] is the mismatched character in text.

### 2. Good Suffix Heuristic Table

The good suffix heuristic handles cases where we've matched some suffix of the pattern but then hit a mismatch. Let me explain this step by step for pattern MALXA.

**What is a "good suffix"?**
When we match some characters from the right but then mismatch, the matched part is called a "good suffix". We want to find how far we can shift the pattern so that:
1. The good suffix aligns with another occurrence of the same substring in the pattern, OR
2. The good suffix aligns with a prefix of the pattern

**Step-by-step computation for MALXA:**

**Position 0**: No suffix matched yet (empty suffix "")
- When no characters are matched, we look for the longest prefix that appears elsewhere in the pattern
- For pattern MALXA: Does any prefix ("M", "MA", "MAL", "MALX") appear as a suffix?
  - "M" appears at position 0 only (not as suffix)
  - "MA" doesn't appear as suffix  
  - "MAL" doesn't appear as suffix
  - "MALX" doesn't appear as suffix
- Since no prefix appears elsewhere as a suffix, shift = 1 (minimal safe shift)

**Position 1**: Suffix "A" was matched, then mismatch at position 3
- Look for "A" elsewhere in pattern MALXA: A appears at position 1
- To align suffix "A" with the A at position 1: shift = 4 - 1 = 3
- Check if "A" matches as prefix: A ≠ M (first char), so no prefix match
- Shift = 3

**Position 2**: Suffix "XA" was matched, then mismatch at position 2  
- Look for "XA" elsewhere in pattern MALXA: "XA" doesn't appear elsewhere
- Check if any suffix of "XA" matches a prefix:
  - "A" vs prefix "M": no match
  - "XA" vs prefix "MA": no match
- Shift = pattern length = 5

**Position 3**: Suffix "LXA" was matched, then mismatch at position 1
- Look for "LXA" elsewhere in pattern: doesn't exist
- Check prefixes: no suffix of "LXA" matches prefix "M" or "MA"
- Shift = pattern length = 5

**Position 4**: Suffix "ALXA" was matched, then mismatch at position 0
- Look for "ALXA" elsewhere: doesn't exist  
- Check prefixes: no suffix of "ALXA" matches any prefix
- Shift = pattern length = 5

**Final Good Suffix Table**:
```
Mismatch at Position | Matched Suffix | Good Suffix Shift
--------------------|----------------|------------------
0                   | ""             | 1
1                   | "A"            | 3  
2                   | "XA"           | 5
3                   | "LXA"          | 5
4                   | "ALXA"         | 5
```

**Intuition**: The good suffix table tells us how far to shift when we've matched some characters from the right but then hit a mismatch. The goal is to avoid redundant comparisons by ensuring the matched part (good suffix) aligns with a compatible position in the pattern.

### Matching Phase - Dry Run

**Alignment 1: Text position 0**
```
Text:    H E X A L X A I M A L X A M A H E
Pattern: M A L X A
         ↑
```
Compare from right to left (pattern index 4 to 0):
- T[4] = L vs P[4] = A → **MISMATCH** (immediate mismatch, no suffix matched)
- Bad character shift for 'L': max(1, 4 - 2) = max(1, 2) = 2
- Good suffix shift: 1 (empty good suffix)
- **Shift = max(2, 1) = 2** (bad character heuristic dominates)

**Alignment 2: Text position 2**
```
Text:    H E X A L X A I M A L X A M A H E
Pattern:     M A L X A
             ↑
```
Compare from right to left:
- T[6] = A vs P[4] = A → **MATCH**
- T[5] = X vs P[3] = X → **MATCH** 
- T[4] = L vs P[2] = L → **MATCH**
- T[3] = A vs P[1] = A → **MATCH**
- T[2] = X vs P[0] = M → **MISMATCH**
- Good suffix "ALXA" was matched, then mismatch at position 0
- Bad character shift for 'X': max(1, 0 - 3) = max(1, -3) = 1
- Good suffix shift: goodSuffix[1] = 5 (suffix "ALXA" doesn't appear elsewhere)
- **Shift = max(1, 5) = 5**

**Alignment 3: Text position 7**
```
Text:    H E X A L X A I M A L X A M A H E
Pattern:               M A L X A
                       ↑
```
Compare from right to left:
- T[11] = X vs P[4] = A → **MISMATCH** (immediate mismatch, no suffix matched)
- Bad character shift for 'X': max(1, 4 - 3) = max(1, 1) = 1
- Good suffix shift: 1 (empty good suffix)
- **Shift = max(1, 1) = 1**

**Alignment 4: Text position 8**
```
Text:    H E X A L X A I M A L X A M A H E
Pattern:                 M A L X A
                         ↑
```
Compare from right to left:
- T[12] = A vs P[4] = A → **MATCH**
- T[11] = X vs P[3] = X → **MATCH**
- T[10] = L vs P[2] = L → **MATCH**
- T[9] = A vs P[1] = A → **MATCH**
- T[8] = M vs P[0] = M → **MATCH**
- **COMPLETE MATCH FOUND at position 8!**

### Results

**Pattern FOUND** at position 8 in the text!

```
Text:    H E X A L X A I M A L X A M A H E
                         M A L X A
                         ↑ match found here
```

### Summary of Shifts
1. Position 0 → Position 2 (shift of 2) - Bad character heuristic only
2. Position 2 → Position 7 (shift of 5) - Good suffix heuristic dominates
3. Position 7 → Position 8 (shift of 1) - Bad character heuristic only  
4. Position 8 → **MATCH FOUND**

Total comparisons made: 11 character comparisons
Total shifts: 3 shifts

The Boyer-Moore algorithm successfully found the pattern using a combination of bad character and good suffix heuristics, making fewer comparisons than a naive approach.

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

---
---
---

## **Huffman Coding Algorithm - String Compression**

***What is Huffman Coding?***

- Huffman Coding is a **lossless data compression algorithm**.
- It assigns **shorter codes to frequent characters** and **longer codes to less frequent characters**.
- Based on a **binary tree (Huffman Tree)**.
- It minimizes the **total number of bits** required to represent data.

***Steps of Huffman Coding***

1. **Frequency Calculation**
    
    Count the frequency of each character in the input string.
    
2. **Priority Queue (Min-Heap)**
    
    Create a priority queue (min-heap) of nodes, where each node stores:
    
    - character
    - frequency
    - left child
    - right child
3. **Build Huffman Tree**
    - Extract two nodes with the smallest frequency.
    - Create a new node with frequency = sum of the two nodes.
    - Insert this new node back into the priority queue.
    - Repeat until only one node remains (this becomes the root).
4. **Generate Huffman Codes**
    
    Traverse the tree:
    
    - Assign `0` when moving left
    - Assign `1` when moving right
        
        Collect codes for all characters.
        
5. **Encoding**
    
    Replace each character in the input string with its corresponding Huffman code.
    
6. **Decoding**
    
    Use the Huffman tree to decode the bit string back to original text.
    

***Example String:***

```
ABRACADABRA
```

---

***Step 1: Frequency Count***

| Character | Frequency |
| --- | --- |
| A | 5 |
| B | 2 |
| R | 2 |
| C | 1 |
| D | 1 |

---

***Step 2: Create Priority Queue (Min-Heap)***

We push each character as a leaf node with its frequency:

```
(C,1), (D,1), (B,2), (R,2), (A,5)
```

---

***Step 3: Build Huffman Tree***

note: while merging 2 nodes `A` and `B` we can insert any random char as value eg. `\0`  with freq as sum of 2 poped nodes, and this new node will have left child as `A` and right as `B` 

1. Extract 2 smallest → `(C,1)` & `(D,1)` → merge → new node `(CD,2)`
    
    Heap: `(CD,2), (B,2), (R,2), (A,5)`
    
2. Extract 2 smallest → `(B,2)` & `(R,2)` → merge → `(BR,4)`
    
    Heap: `(CD,2), (BR,4), (A,5)`
    
3. Extract 2 smallest → `(CD,2)` & `(BR,4)` → merge → `(CDBR,6)`
    
    Heap: `(CDBR,6), (A,5)`
    
4. Extract 2 smallest → `(A,5)` & `(CDBR,6)` → merge → `(Root,11)`
    
    Heap: `(Root,11)`
    

---

***Step 4: Assign Huffman Codes***

Traverse tree (Left = `0`, Right = `1`):

- now lets create a `map(character -> huffman code)` , so we do a DFS of the huffman tree and for every time we reach a leaf eg. `C` we have the `code` for that value `C` that we will put in the hashmap. eg. for C code is `100`  coz `right left left` will take us to C

```
              (Root,11)
              /       \
          (A,5)      (CDBR,6)
                     /      \
                (CD,2)     (BR,4)
                /   \      /    \
            (C,1) (D,1) (B,2)  (R,2)

```

Codes:

- A = `0`
- C = `100`
- D = `101`
- B = `110`
- R = `111`

we have this above map which will help at time of decoding (converting encoded string to original form)

---

***Step 5: Encode String***

Original: `ABRACADABRA`

Replace each character with its code:

```
A → 0
B → 110
R → 111
A → 0
C → 100
A → 0
D → 101
A → 0
B → 110
R → 111
A → 0
```

Encoded:

```
0 110 111 0 100 0 101 0 110 111 0
```

Final compressed bitstring:

```
encoded form = 01101110100010101101110
```

---

***Step 6: Decoding***

Take encoded string, traverse tree from root:

- `0` → A
- `110` → B
- `111` → R
- … repeat until full message recovered.

Decoded:

```
ABRACADABRA
```

### *Space Usage Comparison (Why Huffman is Optimal)*

Let’s take the example **`BANANA`** (length = 6).

**Character Frequencies**

- `B`: 1
- `A`: 3
- `N`: 2

**Fixed-length Encoding (naive)**

If we use **fixed 2-bit codes** (since 3 unique chars → need ⌈log₂3⌉ = 2 bits per char):

- Each character = 2 bits
- Total = `6 × 2 = 12 bits`

**Huffman Encoding**

From Huffman tree:

- `A → 0` (1 bit)
- `N → 10` (2 bits)
- `B → 11` (2 bits)

Now encode:

- `BANANA → B(11) A(0) N(10) A(0) N(10) A(0)`
- Encoded string = `11010100` (8 bits)

**Comparison**

- Fixed-length: **12 bits**
- Huffman: **8 bits**

➡️ **Savings = 33%** space reduction!

*note: here for theory purpose we taking for normal case (2 bits per char space) but in java each char is of `2 byte = 16 bits`  so considering that we saving lots of space*

---