# Smallest window that contains all chars of string

```
input :  aabcbcdbca
output : dbca

input : aabcbcdbca
output : dbbca 
```

```java
import java.util.*;

public class Main1 {

    static private boolean isValid(TreeSet<Character> uniqChars, String curr){
        if(curr.length() < uniqChars.size()) return false;
        TreeSet<Character> set2 = new TreeSet<>();
        for(int i=0; i < curr.length(); i++){
            set2.add(curr.charAt(i));
        }
        if(uniqChars.size() == set2.size()) return true;
        return false;
    }

    public static void main(String ... arg){

        String str = "aabcbcdbbca";
        // String str = "aabcbcdbca";

        TreeSet<Character> uniqChars = new TreeSet<>();
        for(char i=0; i < str.length(); i++) uniqChars.add(str.charAt(i));

        String ans = ""; // minimize this
        for(int i=0; i < str.length(); i++){
            String curr = "";
            for(int j=i; j < str.length(); j++){
                curr += str.charAt(j);
                if( isValid(uniqChars, curr) == true ){
                    if(ans.equals(""))
                        ans = curr;
                    else if(ans.length() > curr.length())
                        ans = curr;
                }
            }
        }

        System.out.println(ans);
    }
    
}
```
