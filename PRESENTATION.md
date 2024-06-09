# RSA Encryption/Decryption and Cracking* with Quadratic Sieve

## How does RSA work?
Our goal is to transfer a number that is less than a certain length over to the recipient  
RSA achieves this by taking advantage of the difficulty involved with factoring in order to create a hard-to-crack encryption method  
<br>

### Necessary components
If I wanted to accept RSA encrypted messages, I need to set up my private and public keys  
Firstly, we need 3 important numbers, our modulus, exponent, and "reversal exponent", which we will name $n$, $E$, and $d$ respectively.  

How would we generate these numbers?
We start off with 2 *very* big primes, lets call $p$ and $q$ (the bigger, the safer)  
The product of these two big primes will be $n$  
<!-- typically rsa uses primes with thousands of bits, 2048 or 4096 -->

$E$ can be any arbitrary positive integer, as long as its big (usually we use $E = 2^{16}+1$)  
We want to evalulate $\lambda(n) = lcm(p-1,q-1)$ (this is Carmichael's lambda function)  
$d$ will be $d = E^{-1} \pmod{\lambda(n)}$  

$n$ and $E$ will both be publicly shared and our public key is the pair $(n,E)$  
$p$, $q$, and $d$ should not be shared and our private key is the pair $(n,d)$  

### How do we encrypt using RSA?
Let's say Bob wants to send Alice an important number, lets call $m$ (note $m < n$)  
Bob knows Alice's public key since she openly advertises it  
Bob can convert his important number into a new number, say $g$, by doing $g = m^E \pmod{n}$  
Then, Bob can send $g$ to Alice so if any third party somehow obtains $g$, they cannot obtain the original number $m$ unless they're Alice  
<br>

### How can Alice revert $g$ back into $m$?  
Well, $d$ has the special property that $m = g^d \pmod{n}$ so by simply repeating the exponentiation, we get back our original message  
<br>

<!--a brief proof-->
### Why does this work?
I claim that $(m^E)^d \equiv m \pmod{n}$  
<!--$(m^e)^d = m^{e \cdot d} \pmod{n}$  -->
The Carmichael function $\lambda(n)$ has the property that $a^{\lambda(n)} \equiv 1 \pmod{n}$  
Therefore, $a^{\lambda(n)k + r} \equiv (a^{\lambda(n)})^k \cdot a^r \equiv (1)^k \cdot a^r \equiv a^r \pmod{n}$  
Or in other words: $a^b = a^{b \pmod{\lambda(n)}} \pmod{n}$ for any integers $a$,$b$  

Also note that $E \cdot d = 1 \pmod{\lambda(n)}$ by definition of $d$  

Using this, our original expression becomes $(m^E)^d \equiv m^{Ed} \equiv m^{Ed \pmod{\lambda(n)}} \equiv m^1 \pmod{n}$  
<br>

## Why is it secure?
If we want to (maliciously) obtain the encrypted number, we would have to obtain $d$.  
In order to obtain $d$, we must factor $n$ into its original two primes $p$ and $q$  
However, there does not exist a "fast" algorithm for factoring a big number  

Multiplying is usually agreed to be somewhere between $\mathcal{O}(n^2)$ and $\mathcal{O}(n\log n \cdot \log \log(n))$ where n is the number of digits of our two factors<!--dont confuse n with other n-->  
In algorithm analysis, we would say multiplication is part of class P (which stands for polynomial). You can just think of it as "multiplication is fast"  

Factoring, is much more difficult and there currently does not exist an algorithm in class P that can factor efficiently  
In a sense, you can think of it as a oneway operation

(In fact, if you can find an algorithm that factors a given number in class P, then you would instantly solve the P = NP conjecture, win a million dollars, and compromise the security of many many bank accounts.)  

*An informed reader may note that quantum computing, which doesn't exist (yet), could achieve a theoretical complexity in class P, but that is different from solving P = NP since quantum computers are different from Turing computers*  
<br>

## What can we transfer using RSA?

In theory, you may transfer as large of a file as you want by splitting it into smaller chunks of bits, converting those bits into a number, and using RSA on that. However, this is not the most efficient as you may need to run RSA many times to transfer a large file

Usually, RSA is used to verify authenticity and ensure that the client is the intended user  
In fact, the setup you used to link your machine to your github account used RSA!  
<br>
<br>

# Quadratic Sieve
Although the complexity of factoring $n$ will never be polynomial, we can use other methods to shave off runtime and make larger sized numbers factorable  

## Naive approaches
### Trial Division
We can naively iterate from $2$ to $n$ and if we find a number that $n$ is divisible by, we will have our two factors  
An informed reader may notice that you only need to iterate from $2$ to $\sqrt{n}$ since one of the factors always has to be in that interval  
<br>

### Fermat's factorization method
If we can express $n$ as $n = a^2 - b^2$ then by algebra, $n = (a-b)(a+b)$ so we have our factors.  
We can manually iterate $a$ and determine whether $a^2-n$ is a perfect square.  
Although faster, it's still not efficient enough.
<br>

## How does Quadratic Sieve attempt to factor a large number n
Quadratic sieve takes inspiration from the method described above.  
We aim to find two integers such that $a^2 \equiv b^2 \pmod{n}$ since that means $(a-b)(a+b) = k \cdot n$ for some integer k and there's a good chance they're factors of $n$ instead of $k$.  
However, it's very rare to have two congruent perfect squares mod $n$ so instead, we look for a set of perfect squares such that their residues multiply to a perfect square    

Let's try an example  
If we have $n = ..........$, we can start evaluating squares and their residues starting from $\lceil{\sqrt{n}}\ \rceil$  


## Compare Quadratic Sieve to Trial Division

# How to use