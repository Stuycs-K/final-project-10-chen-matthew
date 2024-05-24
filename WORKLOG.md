# Work Log
(individual group)
### 5/22 In class
-added a c++ debug file for convenience  
-created miller rabin primality, wrote up some sieve to potentially test  

### 5/22 At home
-completed primality function, currently only works for primes below 2^31-1  
-tested function against results from sieve and large primes, passes all tests  

### 5/23 In class
-fixed some bugs with unsigned vs signed for rng() in `is_prime`
-created variables needed for RSA, started planning out how files are going to be organized

### 5/23 At home
-read into the specifics of quadratic sieve

### 5/24 In class
-created `extended_gcd` to calculate coefficients for linear diophantine equations
-used `extended_gcd` to create `modular_inverse` which calculates modular inverse of v (mod m)
-started writing `encrypt_message.cpp`
-might reorganize math functions into separate header