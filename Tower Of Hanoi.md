# Tower Of Hanoi

![image](https://github.com/user-attachments/assets/3ce7f4a0-0447-4bc5-935c-3c12b7f28113)

## ✔️Approach - 1 (Recursion)
```java
class Hanoi {
    private void TOH(int n, int src, int dest, int helper, long[] steps){
        if(n == 0) return;
        steps[0]++;
        TOH(n-1, src, helper, dest, steps);
        System.out.println("move disk " + n + " from rod " + src + " to rod " + dest);
        TOH(n-1, helper, dest, src, steps);
    }
    public long toh(int n, int src, int dest, int helper) {
        long[] steps = new long[1];
        TOH(n, src, dest, helper, steps);
        return steps[0];
    }
}
```
