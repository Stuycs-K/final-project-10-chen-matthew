[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/ecp4su41)
# Mogussy

# THIS DOCUMENT IS REQUIRED
## Group Info
## Overview
## Instructions
First run `sudo apt-get install libgmp-dev libgmpxx4ldbl` to download GNU Multiple Precision Library
Note: C++ files should be compiled with `g++ prog.cpp -lgmp -lgmpxx`

how to use `create_keys.cpp`  
`g++ create_keys.cpp -o genkey -lgmp -lgmpxx`  
`./genkey 30` to create a 30 bit prime number

how to use `crack_message.cpp`  
`g++ crack_message.cpp -o crack -lgmp -lgmpxx`  
`./crack [N] [B] [EPS]`  
-N is number we want to factor
-B is smoothness bound (can be evaluated with a math formula to optimize runtime)
-EPS is probability of nontrivial factors