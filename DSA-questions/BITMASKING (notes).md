# Bit Masking

The most popular 2 ways to represent integers are 

    1. Decimal (0,1,...9)

    2. Binary (0,1)



binary number is represented in 32 bits. (either 0's or 1's)

eg. integer 2 in binary will be `00000.......10` i.e 31 times 0's and single set bit (1) 



When we use bit masking for performing some operations such as addition subtraction multiplication, etc then it takes place directly on the bits of the numbers this way the operations performed will be relatively faster to normal operations because if we perform 1 + 2 then computer has to first convert given decimal to their binary forms and then perform the operation.

```cp
lets convert (101) decimal to decimal
101 => 1*(10^2) + 0*(10^1) + 1*(10^0) => 100 + 0 + 1 => 101

lets convert binary to decimal 
101 => 1*(2^2) + 0*(2^1) + 1*(2^0) => 4 + 2 + 0 =>  6 
```



## Binary Addition

how binary addition of 2 numbers takes place

```cpp
num1 = 5, num2 = 2 

binary of 5 = (101)
binary of 2 = (10) 

addition :
    1 0 1 
  +   1 0 
   -------
    1 1 1


binary 111 in decimal will be (1*2^2 + 1*2^1 + 1*2^0) => 4+2+1 => 7


5 + 2 = 7
```



## Binary Subtraction

now this is a bit more interesting 



lets say we want to find `12 - 7 = ?` now in binary we can only perform addition of bits, there is nothing like subtracktion of bits, so to solve this question we can write this in changed form i.e `12 + (-7)` so now we will find the binary of 12 and binary of -7 then we will add the 2 binary strings to get out result.



Que - but how do we get binary of `-7` ? 

easy, all we need to do is find the binary of `+7` then do the 2's complement of that binary string, and we will get -7 in binary.



Que - What is 2's complement of a number 

to find 2's complement of a number we have 2 steps :- 

- step 1 : invert all bits 

- step 2 : add 1 to the result from step 1 



```cpp
12 - 7 = ?

binary of 12 is "1100"
binary of 7 is "111"

actually binary of 12 is "00......1100"
actually binary of 7 is "00.......0111"

finding 2's complement of 7
1's complement (flip bits) = "11.......1000"

                11.......1000
               +            1
                --------------
                11.......1001  


2's complement : "11.......1001" = -7


lets add binary strings of -7 and 12 

        1 1 ........1 1 0 0 1 
    +   0 0 ........0 1 1 0 0 
        ---------------------
        0 0 ....0 0 0 0 1 0 1
                                

1 0 1 in decimal will be equal to 5 

12 - 7 = 5  

```



### Bitwise operators

- `&` and 

- `|` or

- `^` xor 

- `~` inverse 

- `>>` right shift 

- `<<` left shift 



we already know and and or, xor (same bits = 0, alternate bits = 1)

imp:- 

- when we perform 1 `left shift` on a number, then the number gets `multiplied by 2` 

- when we perform 1 `right shift` on a number, then the number gets `divided by 2`



#### Check if a number is odd or even using `bit-masking`

note that :- 

- even numbers have last bit `0`

- odd numbers have last bit `1`



if we perform `& 1` with any number then if the output is 1 that means number is odd and if output is 0 then that means number is even

```cpp
if(number & 1 == 1) 
    number is odd

if(number & 1 == 0)
    number is even
```



##### Swap 2 numbers without using 3rd variable ?

To perform this we will use xor `^` bitwise operator

we will do `a^b` 3 times 2 achieve this swap

```cpp
num1 = 5 
num2 = 7 
---------

binary of 5 is "101"
binary of 7 is "111"

====================
1st time:- (a = a^b) 

    1 0 1 
^   1 1 1 
    -----
      1 0  = a = 2 

now a = 2, b = 7 
======================
2nd time (b = a^b)

    0 1 0 
^   1 1 1 
    -----
    1 0 1  = b = 5 
=======================
now a = 2, b = 5 // note that b is swaped now, we are left with a 

3rd time (a = a^b)

    0 1 0 
^   1 0 1
    -----
    1 1 1 = a = 7 

now a = 7, b = 5 // both a and b are successfully swaped 
    
```




