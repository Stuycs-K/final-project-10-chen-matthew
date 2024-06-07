# RSA Encryption

## How does RSA work?
Our goal is to transfer a number that is less than a certain length over to the recipient  
RSA achieves this by taking advantage of the difficulty involved with factoring in order to create a hard-to-crack encryption method  

Firstly, we need 3 important numbers, our modulus, exponent, and "reversal exponent", which we will name N, E, and D respectively.  

Lets say Bob wants to send Alice an important number, lets call M  
Bob knows that Alice publicly reveals her "public key" which consists of numbers N and E.  
(Note that M should be less than N)  
Bob can convert his important number into a new number, say G, by raising M to E and then modding that by N  
Then, Bob can send G to Alice so if any third party somehow obtains G, they cannot obtain the original number M unless they're Alice  

How can Alice revert G back into M?  
Well, Alice has a magical number D with the property that if you raise G to D and then mod N once more, you will obtain M again!  
(There are proofs online to why this is true)  

Why does this work?
E is kind of arbitrary (but it's recommended to be big)  
N has to be a product of two, very large primes
D has to be the inverse of E mod lambda(n) where lambda(n) is Carmichael's lambda function

Because of *math*, this process gets us the same number as we started with so it is a valid and working encryption.  

## Why is it secure?
If we want to (maliciously) obtain the encrypted number, we would have to obtain D.  
In order to obtain D, we must factor N into its original two primes  
However, there does not exist a "fast" algorithm for factoring a big number  

Multiplying is usually agreed to be somewhere between O(n^2) and O(nlogn * loglog(n)) where n is the number of digits of our two factors  
In algorithm analysis, we would say multiplication is part of class P (which stands for polynomial). You can just think of it as "multiplication is fast"  

Factoring, is much more difficult and there currently does not exist an algorithm in class P that can factor efficiently  
In a sense, you can think of it as a oneway operation

In fact, if you can find an algorithm that factors a given number in class P, then you would instantly solve the P = NP conjecture, win a million dollars, and compromise the security of many many bank accounts.  

An informed reader may note that quantum computing could achieve a theoretical complexity in class P, but that is different from solving P = NP since quantum computers are different from Turing computers  

## What can we transfer using RSA?

In theory, you may transfer as large of a file as you want by splitting it into smaller chunks of bits, converting those bits into a number, and using RSA on that. However, this is not the most efficient as you may need to run RSA many times to transfer a large file

Usually, RSA is used to verify authenticity and ensure that the client is the intended user

# Quadratic Sieve

## Why is factoring difficult?

## How does Quadratic Sieve attempt to factor a large number N

## Compare Quadratic Sieve to Trial Division

# How to use