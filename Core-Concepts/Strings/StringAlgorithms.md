- Bruteforce pattenr searching
- Boyer Moree Algorithm

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
