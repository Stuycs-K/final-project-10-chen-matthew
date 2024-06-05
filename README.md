[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/ecp4su41)

## Group Info
Group members: Matthew Chen  
Group name: Mogussy  
Topic: RSA Encryption/Decryption and Quadratic Sieve to crack RSA (for relatively small primes)  

## Overview


## Instructions
First run `sudo apt-get install libgmp-dev libgmpxx4ldbl` to download GNU Multiple Precision Library  
Note: 
- C++ files should be compiled with `g++ prog.cpp -lgmp -lgmpxx`  
- Make sure version is C++17 or above

### How to use `create_keys.cpp`  
`g++ create_keys.cpp -o genkey -lgmp -lgmpxx`  
`./genkey [K]`  
- Generates public and private keys
- Uses two K bit prime numbers

### How to use `crack_message.cpp`  
`g++ crack_message.cpp -o crack -lgmp -lgmpxx`  
`./crack [N] [B] [EPS]`  
- N is number we want to factor  
- B is smoothness bound 
    - Can be evaluated with a math formula to optimize runtime
    - Higher smoothness bound means higher probability that numbers chosen to generate the exponent matrix will be B-smooth but tradeoff is each number needs to be iterated with more primes
    - Lower smoothness bound means less primes to iterate through per number but more numbers to iterate through since less of them will be B-smooth
- EPS is probability of nontrivial factors
    - Higher EPS means resulting numbers are more likely to be non-trivial factors of N (ie factors other than 1 and N) but also means more additional numbers to save into exponent matrix