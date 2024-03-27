# Generate all substrings with size k

```java
input : 
school  k=3

output : 
sch, cho, hoo, ool
```

## Approach - 1 (n*k)
```java
import java.util.*;
public class KsideSubstring {

    /*
        school  k=3
        ------
        sch, cho, hoo, ool
     */
    public static void main(String[] args){
        Scanner scn = new Scanner(System.in);
        String str = scn.next();
        int k = scn.nextInt();

        // print all substrings of size k of str
        int i=0, j = k-1;
        while(j < str.length()){
            String curr = str.substring(i, j+1);
            System.out.println(curr);
            i++;
            j++;
        }

    }
    
}

```
