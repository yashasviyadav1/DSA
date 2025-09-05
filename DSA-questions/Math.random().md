# Generating Random no using `Math.random()`

note : Math.random() returns a double value from 0.0000 to 9.99999 

### Print random nos between 0 to 1 (exclusive)
```java

class HelloWorld {
    public static void main(String[] args) {
        // print 5 random double nos between 0 to 1 (0 including 1 excluding)
        for(int i=0; i<5; i++){
            double random = Math.random();
            System.out.println(random);
        }
    }
}
/*
0.34310440533693254
0.9676569547514372
0.5992234752522859
0.4998478601347165
0.9373103687555537
*/
```

### ⭐Print random numbers from 0 to 10 (exl)
```java

class HelloWorld {
    public static void main(String[] args) {
       // print random numbers from 0 to 10(exclusive)
        for(int i=0; i<8; i++){
            int random = (int)(Math.random()*10);    // 0.5 * 10 -> 5 this way converted in range of 0 to 10
            System.out.println(random);
        }
    }
}
/*
6
6
4
4
5
9
5
2
*/
```

### Print random numbers in specified range of `mini` and `maxi`
```java

class HelloWorld {
    public static void main(String[] args) {
       // print random numbers from 6 to 10 (includsive)
       int mini = 6;
       int maxi = 10; 
       // step1 : find total numbers that lies in 6 to 10 (5)
       int range = maxi - mini + 1;
        for(int i=0; i<10; i++){
            // step2 : multiply Math.random() with range 'x' would give us a random number from 0 to x-1 and then add mini to it coz we need our random number to have mimimum value of 'mini'
            int random = (int)(Math.random() * range) + mini;
            System.out.println(random);
        }
    }
}
/*
10
6
10
6
6
6
8
10
8
10
*/
```
