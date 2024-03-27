# Invert case of characters of string or Invert String

### Approach - 1 (using build in `Character` methods) 
```java
public class InvertString {

    // invert case of characters in a string
    public static void main(String[] args){
        String str = "hello_12_HELLO";  // output : HELLO_12_hello
        String ans = "";
        for(int i=0; i < str.length(); i++){
            char ch =  str.charAt(i);
            if(Character.isUpperCase(ch))
                ch = Character.toLowerCase(ch);
            else if(Character.isLowerCase(ch))
                ch = Character.toUpperCase(ch);
            else if(Character.isDigit(ch))
                ch = ch; // no change
            ans += ch;
        }

        System.out.println(ans);
    }
}

```
