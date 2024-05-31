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

### 5/26 At home
-reorganized math functions into `math_lib.cpp`
-cleaned up some code in other files

### 5/27 At home
-created `encrypt_message.cpp` and `decrypt_message.cpp`
-started working on `crack_message.cpp`

### 5/28 In class
-started working on my own BigInteger class

### 5/28 At home
-researched and found out there's GMP bignum library for C++

### 5/29 In class & At home
-spent time googling documentation and stackoverflow posts to set up the library (got nowhere though)

### 5/30 In class
-found a post using `sudo apt-get install libgmp-dev libgmpxx4ldbl`, still trying to set it up

### 5/30 At Home
-finally set up the library, started learning its documentation
-deleted `math_lib.cpp` and replaced functions it contained with built in library methods from GMP
-revised `encrypt_message.cpp`, `decrypt_message.cpp`, and `create_keys.cpp` with GMP library, now it works for any sized integer
-note: `crack_message.cpp` still in progress