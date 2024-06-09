[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/ecp4su41)

## Group Info
Group members: Matthew Chen  
Group name: Mogussy  
Topic: RSA Encryption/Decryption and Quadratic Sieve to crack RSA  

## Overview
This project implements RSA Encryption, Decryption, and Quadratic Sieve to crack RSA quickly for numbers less than 40 digits  
`create_keys.cpp` takes a specified number of bits and generates public and private keys with modulus with at least that many bits  
`encrypt_message.cpp` takes a public key and message and returns an encrypted version of that message  
`decrypt_message.cpp` takes a private key and message and returns the decrypted, original message  
`crack_message.cpp` takes a public key and an arbitrary bound EPS and returns the private key

## Instructions
First run `sudo apt-get install libgmp-dev libgmpxx4ldbl` to download GNU Multiple Precision Library  
Note: 
- C++ files should be compiled with `g++ prog.cpp -lgmp -lgmpxx`  
- Make sure version is C++17 or above

### How to generate RSA private/public key pairs
`make generate ARGS="[K]"`
- Generates public and private keys
- Uses two K bit prime numbers

### How to encrypt your message
`make encrypt ARGS="[N] [E] [M]"`
- N and E are the values from the public key
- M is the message number, make sure M < N

### How to decrypt your message
`make decrypt ARGS="[N] [D] [C]"`
- N and D are the values from the private key
- C is the encrypted message

### How to attempt to crack and obtain the private key from the public key
`make crack ARGS="[N] [E] [EPS]"`
- N and E are the values from the public key
- EPS is probability of getting a valid private key
    - Higher EPS means factors of N are more likely to be nontrivial and the private key is more likely to be correct
    - Tradeoff is the runtime, higher the EPS, the slower it gets