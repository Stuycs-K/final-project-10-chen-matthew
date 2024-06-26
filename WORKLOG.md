# Work Log
(individual group)
### 5/22 In class
-added a c++ debug file for convenience  
-created miller rabin primality test, wrote up some sieve to potentially test  

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
-set up dependencies in file headers  

### 5/27 At home
-created `encrypt_message.cpp` and `decrypt_message.cpp`  
-started working on `crack_message.cpp`  

### 5/28 In class
-started working on my own BigInteger class  
-completed class functions and template  

### 5/28 At home
-researched and found out there's GMP bignum library for C++  
-looked at its compatibility and usage  

### 5/29 In class & At home
-spent time googling documentation and stackoverflow posts to set up the library (got nowhere though)  
-looked into GMP's implementations and specifics  

### 5/30 In class
-found a post using `sudo apt-get install libgmp-dev libgmpxx4ldbl`, still trying to set it up  

### 5/30 At Home
-finally set up the library, started learning its documentation  
-deleted `math_lib.cpp` and replaced functions it contained with built in library methods from GMP  
-revised `encrypt_message.cpp`, `decrypt_message.cpp`, and `create_keys.cpp` with GMP library, now it works for any sized integer  
-note: `crack_message.cpp` still in progress  

### 5/31 In class
-continue reading the specifics of quadratic sieve  
-created a summary of the steps required in quadratic sieve  
-researched its time complexity and its runtime limits  

### 6/1 At home
-started writing an implementation of quadratic sieve in `crack_message.cpp`  
-note that B is currently a constant  
-completed first sieve portion to obtain the factor base  
-written a bruteforce solution to get B-smooth numbers  
-put some defines in debug.cpp so gmp's method names are shorter  

### 6/3 In class & At home
-taught myself some linear algebra from a textbook to evaluate nullspaces for quadratic sieve  
-wrote up an algorithm pseudocode summary of finding nullspaces  

### 6/4 At home
-wrote up a function to evaluate nullspaces  
-edited that function to work on binary matrices and convert input matrix into row reduced echelon form  
-used that function in `crack_message` to evaluate nullspaces  
-used nullspace to find potential factors  
-edited `crack_message` and `create_keys` to take in command arguments (refer to README)  
-drafted up a makefile  

### 6/5 In class
-corrected makefile so that the dependencies work  
-added a make clean option for convenience  
-added some comments to `crack_message` so that it's clearer to read   
-wrote up an outline for `PRESENTATION.md`  

### 6/5 At home
-did testing on `crack_message`  
-used `create_keys` to generate 30, 40, 50 bit primes  
-`crack_message` works under 30 secs for   

### 6/6 At home
-did reading on alternate ways to find B-smooth numbers instead of bruteforcing  
-implemented `modulo_sqrt` using tonelli-shanks algorithm  
-optimized `crack_message` using different sieve method  
-added time stamps to analyze which code sections are taking the most time  

### 6/7 In class
-completed first 3 sections of `PRESENTATION.md`  
-will reformat with math font and formatting later  
-will also write a custom bitset to speed up `crack_message`   

### 6/8 At home
-fixed some small bugs in `crack_message` with index bounding  
-revised and reorganized `PRESENTATION.MD`  
-included LaTeX formatting to the math expressions  
-completed a proof for correctness of RSA  
-did some explanation for quadratic sieve explanation in `PRESENTATION.md`

### 6/9 At home
-Completed a section in the quadratic sieve presentation
-Reformatted all of the math and number expressions
-Edited `crack_message.cpp` to only print out time elapsed and the private key
-Removed debug statements
-Updated `README.md` to use makefiles instead of g++ compiling
-Included some images in `README.md` and `PRESENTATION.md`
-Finished recording and linked it to `README.md`