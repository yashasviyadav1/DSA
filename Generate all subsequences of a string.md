# Generate all subsequences of a string


```
Input : "abc";
Output : [, c, b, bc, a, ac, ab, abc]
```
# Approach -1 (recursive bruteforce)
```java
import java.util.*;
// Generate all subseq of a string 
// Bruteforce
// Time:O(2^n)
// Space:O(n)

class Main{
	public void solve(String str, List<String> allSubseq, String currSubseq, int index){
		if(index == str.length()){
			allSubseq.add(currSubseq);
			return;
		}

		solve(str, allSubseq,currSubseq, index+1);//not pick

		currSubseq += str.charAt(index);//pick
		solve(str, allSubseq, currSubseq, index+1);
		currSubseq = currSubseq.substring(0, currSubseq.length()-1); // backtrack-remove the last added element
	}

	public static void main(String ... args){
		
		// for n length string 2^n subseq are possible
		String str = "abc";
		Main obj = new Main();
		
		// generating all subsequences of string
		List<String> allSubseq = new ArrayList<>();
		String currSubseq = "";
		obj.solve(str, allSubseq, currSubseq, 0);

		System.out.print(allSubseq);
		
	}
		
}
```
