# Generate all substrings of a string

```java
input : 
 school

output : 
 s, sc, sch, scho, schoo, school
 c, ch, cho, choo, chool
 h, ho, hoo, hool
 o, oo, ool
 o, ol
 l
 total substrings : 21
```

## Approach - 1 (iterative O(n^2))
```java
import java.util.*;
public class AllSubseq {

    // print all substrings of given string
    public static void main(String[] args){
        Scanner scn = new Scanner(System.in);
        String str = scn.next(); 
        int totalSubstr = 0;
        for(int i=0; i < str.length(); i++){
            for(int j=i; j < str.length(); j++){
                totalSubstr++;
                String curr = str.substring(i, j+1);
                System.out.println(curr);
            }
        }
        System.out.println("total substrings : " + totalSubstr);

    }
    
}

```
